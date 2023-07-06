typedef struct _PEP_INFORMATION {
    USHORT Version;
    USHORT Size;
    PPEPCALLBACKNOTIFYDPM AcceptDeviceNotification;
    PPEPCALLBACKNOTIFYPPM AcceptProcessorNotification;
    PPEPCALLBACKNOTIFYACPI AcceptAcpiNotification;
} PEP_INFORMATION, *PPEP_INFORMATION;

typedef struct _PEP_KERNEL_INFORMATION_STRUCT_V3 {
    USHORT Version;
    USHORT Size;
    POHANDLE Plugin;
    PPOFXCALLBACKREQUESTWORKER RequestWorker;

    //
    // Callbacks for assisting processor idle state execution.
    //

    PPOFXCALLBACKENUMERATEUNMASKEDINTERRUPTS EnumerateUnmaskedInterrupts;
    PPOFXCALLBACKPROCESSORHALT ProcessorHalt;
    PPOFXCALLBACKREQUESTINTERRUPT RequestInterrupt;
    PPOFXCALLBACKCRITICALRESOURCE TransitionCriticalResource;

    //
    // Callbacks for runtime changes to processor and platform idle states.
    //

    PPOFXCALLBACKPROCESSORIDLEVETO ProcessorIdleVeto;
    PPOFXCALLBACKPLATFORMIDLEVETO PlatformIdleVeto;
    PPOFXCALLBACKUPDATEPROCESSORIDLESTATE UpdateProcessorIdleState;
    PPOFXCALLBACKUPDATEPLATFORMIDLESTATE UpdatePlatformIdleState;

    //
    // PEPv3 callbacks.
    //

    PPOFXCALLBACKREQUESTCOMMON RequestCommon;
} PEP_KERNEL_INFORMATION_STRUCT_V3, *PPEP_KERNEL_INFORMATION_STRUCT_V3;

NTSTATUS __fastcall PopFxRegisterPluginEx(
        _PEP_INFORMATION *PepInformation,
        _PEP_KERNEL_INFORMATION_STRUCT_V3 *KernelInformation,
        UINT64 Attributes)
{
  __int16 v3; // ax
  int v7; // ebx
  bool v8; // cf
  __int16 v10; // ax
  UINT8 *PoolWithTag; // rax
  UINT8 *v12; // r14
  _ETHREAD *CurrentThread; // rax
  UINT8 **v14; // rax
  __int64 v15; // rdx
  _ETHREAD *v16; // rbx
  NTSTATUS SessionId; // edx
  unsigned __int8 v18; // r13
  int v19; // er8
  bool v20; // zf
  __int64 v21; // rcx
  _KLOCK_ENTRY *v22; // rbp
  int v23; // eax
  unsigned int v24; // ecx
  __int64 v25; // rdx
  int v26; // [rsp+78h] [rbp+20h] BYREF

  v3 = *(_WORD *)Attributes;
  if ( *(_WORD *)Attributes > 3u )
    return -1073700860;
  switch ( v3 )
  {
    case 3:
      v8 = *(_WORD *)(Attributes + 2) < 0x60u;
      break;
    case 2:
      v8 = *(_WORD *)(Attributes + 2) < 0x58u;
      break;
    case 0:
      return -1073741811;
    default:
      goto LABEL_11;
  }
  if ( v8 )
    return -1073741811;
LABEL_11:
  if ( *(_WORD *)(Attributes + 2) < 0x38u )
    return -1073741811;
  v10 = *(_WORD *)PepInformation;
  if ( *(_WORD *)PepInformation > 3u )
    return -1073700859;
  if ( v10 == 3 )
  {
    if ( *((_WORD *)PepInformation + 1) < 0x20u || !*((_QWORD *)PepInformation + 1) && !*((_QWORD *)PepInformation + 3) )
      return -1073741811;
  }
  else if ( v10 != 2 || *((_WORD *)PepInformation + 1) < 0x18u || !*((_QWORD *)PepInformation + 1) )
  {
    return -1073741811;
  }
  PoolWithTag = (UINT8 *)ExAllocatePoolWithTag(NonPagedPoolNx, 0x1A8u, 0x4D584650u);
  v12 = PoolWithTag;
  if ( !PoolWithTag )
    return -1073741670;
  memset(PoolWithTag, 0, 0x1A8ui64);
  v7 = PopFxInitializeWorkPool(v12 + 120, (__int64)v12);
  if ( v7 >= 0 )
  {
    *((_DWORD *)v12 + 4) = *(unsigned __int16 *)PepInformation;
    *((_QWORD *)v12 + 3) = KernelInformation;
    *((_QWORD *)v12 + 12) = *((_QWORD *)PepInformation + 1);
    *((_QWORD *)v12 + 13) = *((_QWORD *)PepInformation + 2);
    if ( *(_WORD *)PepInformation >= 3u )
      *((_QWORD *)v12 + 14) = *((_QWORD *)PepInformation + 3);
    CurrentThread = (_ETHREAD *)KeGetCurrentThread();
    --CurrentThread->Tcb.KernelApcDisable;
    ExAcquirePushLockExclusiveEx((_EX_PUSH_LOCK *)&PopFxPluginLock, 0i64);
    v14 = (UINT8 **)PopFxDeviceRegisterHead;
    v15 = *(_QWORD *)PopFxDeviceRegisterHead;
    if ( *(_QWORD *)(*(_QWORD *)PopFxDeviceRegisterHead + 8i64) != PopFxDeviceRegisterHead )
      __fastfail(3u);
    *((_QWORD *)v12 + 1) = PopFxDeviceRegisterHead;
    *(_QWORD *)v12 = v15;
    *(_QWORD *)(v15 + 8) = v12;
    *v14 = v12;
    if ( ((unsigned int)KernelInformation & 0x80000000) != 0 )
      PopFxDeviceRegisterHead = (__int64)v12;
    if ( (_InterlockedExchangeAdd64((volatile signed __int64 *)&PopFxPluginLock, 0xFFFFFFFFFFFFFFFFui64) & 6) == 2 )
      ExfTryToWakePushLock((_EX_PUSH_LOCK *)&PopFxPluginLock);
    v26 = 0;
    v16 = (_ETHREAD *)KeGetCurrentThread();
    if ( MiGetSystemRegionType((UINT64)&PopFxPluginLock) == 1 )
      SessionId = MmGetSessionIdEx(v16->Tcb.ApcState.Process);
    else
      SessionId = -1;
    --v16->Tcb.SpecialApcDisable;
    v18 = ++v16->Tcb.AbAllocationRegionCount;
    v19 = ((char)v16->Tcb.AbEntrySummary | (char)v16->Tcb.AbOrphanedEntrySummary) ^ 0x3F;
    while ( 1 )
    {
      v20 = !_BitScanReverse((unsigned int *)&v21, v19);
      if ( v20 )
        break;
      v22 = &v16->Tcb.LockEntries[v21];
      v19 &= ~(1 << v21);
      if ( (v22->AcquiredByte & 1) != 0
        && (*(_DWORD *)&v22->LockState.0 & 1) == 0
        && (*(_QWORD *)&v22->LockState.0 & 0x7FFFFFFFFFFFFFFCi64) == ((unsigned __int64)&PopFxPluginLock & 0x7FFFFFFFFFFFFFFCi64)
        && v22->LockState.SessionId == SessionId )
      {
        v22->AcquiredByte &= ~1u;
        if ( v22->LockState.0 )
        {
          if ( v22 )
          {
            v22->CrossThreadReleasableAndBusyByte |= 2u;
            if ( (__int64)v22->LockState.LockState < 0 )
              KiAbEntryRemoveFromTree(v22);
            v23 = v22->BoostBitmap.AllFields & 0x1FFFF;
            v24 = v22->BoostBitmap.AllFields & 0xFFFE0000;
            v22->ThreadLocalFlags &= ~1u;
            v26 = v23;
            v22->BoostBitmap.AllFields = v24;
            v22->LockState.0 = 0i64;
            v25 = v22 - v16->Tcb.LockEntries;
            if ( v18 == 1 )
              v16->Tcb.AbEntrySummary |= 1 << v25;
            else
              _InterlockedOr8((volatile signed __int8 *)&v16->Tcb.AbOrphanedEntrySummary, 1 << v25);
            goto LABEL_50;
          }
          break;
        }
      }
    }
    if ( (*((_DWORD *)&v16->Tcb.0 + 1) & 0x10000) == 0 )
      KeBugCheckEx(0x162u, (ULONG_PTR)v16, (ULONG_PTR)&PopFxPluginLock, SessionId, 0);
LABEL_50:
    --v16->Tcb.AbAllocationRegionCount;
    KiAbThreadRemoveBoosts(v16, &PopFxPluginLock, (unsigned int *)&v26);
    v20 = v16->Tcb.SpecialApcDisable++ == -1;
    if ( v20 && ($F25F8C4BA33AF922A5F1AF68CD89DDDF *)v16->Tcb.ApcState.ApcListHead[0].Flink != &v16->Tcb.152 )
      KiCheckForKernelApcDelivery();
    KeLeaveCriticalRegionThread(KeGetCurrentThread());
    PopDiagTraceFxPluginRegistration(v12, (UINT8)KernelInformation, 0i64);
    *(_QWORD *)(Attributes + 32) = 0i64;
    *(_QWORD *)(Attributes + 40) = 0i64;
    *(_QWORD *)(Attributes + 24) = 0i64;
    v8 = *(_WORD *)Attributes < 2u;
    *(_QWORD *)(Attributes + 16) = PopFxRequestWorker;
    *(_QWORD *)(Attributes + 48) = PopFxTransitionCriticalResource;
    *(_QWORD *)(Attributes + 8) = v12;
    if ( !v8 )
    {
      *(_QWORD *)(Attributes + 56) = PopFxProcessorIdleVeto;
      *(_QWORD *)(Attributes + 64) = PopFxPlatformIdleVeto;
      *(_QWORD *)(Attributes + 72) = PopFxUpdateProcessorIdleState;
      *(_QWORD *)(Attributes + 80) = PopFxUpdatePlatformIdleState;
    }
    if ( *(_WORD *)PepInformation >= 3u )
    {
      *(_QWORD *)(Attributes + 88) = PopFxRequestCommon;
      if ( *(_WORD *)PepInformation == 3 )
      {
        if ( *((_QWORD *)PepInformation + 3) )
          PopFxAcpiPepRegistered = 1;
      }
    }
    return 0;
  }
  else
  {
    ExFreePoolWithTag(v12, 0x4D584650u);
  }
  return v7;
}

/*
all callbacks are stored in struct _IOMMU_INTERFACE_CALLBACK_RECORD and all entries of it are stored in IommuInterfaceStateChangeCallbackListHead

struct _IOMMU_INTERFACE_CALLBACK_RECORD {
    struct _LIST_ENTRY ListEntry;                                          
    VOID (*CallbackRoutine)(struct _IOMMU_INTERFACE_STATE_CHANGE* arg1, VOID* arg2); 
    VOID* CallbackContext;                                               
    struct _IOMMU_DMA_DEVICE* DmaDevice;                                    
    struct _IOMMU_INTERFACE_STATE_CHANGE LastReportedState;              
} IOMMU_INTERFACE_CALLBACK_RECORD, *PIOMMU_INTERFACE_CALLBACK_RECORD;
*/

__int64 __fastcall IommuRegisterInterfaceStateChangeCallback(
        void (*CallbackRoutine)(struct _IOMMU_INTERFACE_STATE_CHANGE* arg1, void* arg2);,
        __int64 a2,
        __int64 a3,
        _DWORD *a4)
{
  unsigned int v4; // ebx
  _QWORD *v9; // rax
  __int64 v10; // rdi
  __int64 v11; // rsi
  struct _KTHREAD *CurrentThread; // r13
  _KLOCK_ENTRIES *KernelAbEntries; // r15
  unsigned int AvailableEntryBitmap; // eax
  unsigned int v15; // ecx
  struct _KPRCB *CurrentPrcb; // rcx
  signed __int32 *SchedulerAssist; // r8
  signed __int32 v18; // eax
  signed __int32 v19; // ett
  int SessionId; // eax
  __int64 *v21; // rax
  unsigned int v24; // [rsp+88h] [rbp+20h]

  v4 = 0;
  if ( *a4 )
  {
    if ( *(_QWORD *)(a3 + 72) )
    {
      return (unsigned int)-1073741823;
    }
    else
    {
      v9 = (_QWORD *)HalpMmAllocCtxAlloc(a1, 48i64);
      v10 = (__int64)v9;
      if ( v9 )
      {
        *v9 = 0i64;
        v9[1] = 0i64;
        v9[4] = 0i64;
        v9[5] = 0i64;
        v9[2] = a1;
        v9[3] = a2;
        ObfReferenceObjectWithTag(*(_QWORD *)(a3 + 8), 1147953480i64);
        *(_QWORD *)(v10 + 32) = a3;
        v11 = 0i64;
        *(_QWORD *)(a3 + 72) = v10;
        CurrentThread = KeGetCurrentThread();
        _disable();
        KernelAbEntries = CurrentThread->KernelAbEntries;
        AvailableEntryBitmap = KernelAbEntries->AvailableEntryBitmap;
        if ( KernelAbEntries->AvailableEntryBitmap
          || (AvailableEntryBitmap = KiAbTryReclaimOrphanedEntries(
                                       &IommuInterfaceStateChangeCallbackPushLock,
                                       CurrentThread,
                                       CurrentThread->KernelAbEntries)) != 0 )
        {
          _BitScanForward(&v15, AvailableEntryBitmap);
          v24 = v15;
          KernelAbEntries->AvailableEntryBitmap = AvailableEntryBitmap & (unsigned __int8)~(1 << v15);
          CurrentPrcb = KeGetCurrentPrcb();
          SchedulerAssist = (signed __int32 *)CurrentPrcb->SchedulerAssist;
          if ( SchedulerAssist )
          {
            _m_prefetchw(SchedulerAssist);
            v18 = *SchedulerAssist;
            do
            {
              v19 = v18;
              v18 = _InterlockedCompareExchange(SchedulerAssist, v18 & 0xFFDFFFFF, v18);
            }
            while ( v19 != v18 );
            if ( (v18 & 0x200000) != 0 )
              KiRemoveSystemWorkPriorityKick(CurrentPrcb);
          }
          _enable();
          v11 = (__int64)&KernelAbEntries->Entries[v24];
          if ( (unsigned __int64)&IommuInterfaceStateChangeCallbackPushLock >= 0xFFFF800000000000ui64
            && byte_140EB06A8[(((unsigned __int64)&IommuInterfaceStateChangeCallbackPushLock >> 39) & 0x1FF) - 256] == 1 )
          {
            SessionId = MmGetSessionIdEx(CurrentThread->ApcState.Process);
          }
          else
          {
            SessionId = -1;
          }
          *(_DWORD *)(v11 + 8) = SessionId;
          *(_QWORD *)v11 = (unsigned __int64)&IommuInterfaceStateChangeCallbackPushLock & 0x7FFFFFFFFFFFFFFCi64;
        }
        if ( _interlockedbittestandset64((volatile signed __int32 *)&IommuInterfaceStateChangeCallbackPushLock, 0i64) )
          ExfAcquirePushLockExclusiveEx(
            &IommuInterfaceStateChangeCallbackPushLock,
            v11,
            &IommuInterfaceStateChangeCallbackPushLock);
        if ( v11 )
          *(_BYTE *)(v11 + 18) = 1;
        *(_DWORD *)(v10 + 40) = *a4;
        if ( (*a4 & 1) != 0 )
          *(_DWORD *)(v10 + 44) = HalpIommuDeviceGetDomainTypes(a3);
        a1(v10 + 40, a2);
        v21 = (__int64 *)qword_140E9F5E8;
        if ( *(__int64 **)qword_140E9F5E8 != &IommuInterfaceStateChangeCallbackListHead )
          __fastfail(3u);
        *(_QWORD *)v10 = &IommuInterfaceStateChangeCallbackListHead;
        *(_QWORD *)(v10 + 8) = v21;
        *v21 = v10;
        qword_140E9F5E8 = v10;
        if ( (_InterlockedExchangeAdd64(&IommuInterfaceStateChangeCallbackPushLock, 0xFFFFFFFFFFFFFFFFui64) & 6) == 2 )
          ExfTryToWakePushLock(&IommuInterfaceStateChangeCallbackPushLock);
        KeAbPostRelease(&IommuInterfaceStateChangeCallbackPushLock);
      }
      else
      {
        return (unsigned int)-1073741670;
      }
    }
  }
  else
  {
    return (unsigned int)-1073741582;
  }
  return v4;
}

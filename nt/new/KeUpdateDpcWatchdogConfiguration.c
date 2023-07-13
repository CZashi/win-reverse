__int64 __fastcall KeUpdateDpcWatchdogConfiguration(__int64 a1, unsigned int a2, unsigned int a3)
{
  struct _KTHREAD *CurrentThread; // rax
  struct _KTHREAD *v7; // r14
  __int64 v8; // rdi
  _KLOCK_ENTRIES *KernelAbEntries; // rsi
  unsigned int AvailableEntryBitmap; // eax
  unsigned int v11; // ecx
  struct _KPRCB *CurrentPrcb; // r8
  signed __int32 *SchedulerAssist; // rdx
  signed __int32 v14; // eax
  signed __int32 v15; // ett
  int SessionId; // eax
  int v17; // edi
  unsigned __int8 CurrentIrql; // si
  _DWORD *v19; // r9
  int v20; // eax
  unsigned int v21; // r14d
  unsigned int v22; // edi
  unsigned __int8 v23; // r10
  unsigned __int8 v24; // al
  struct _KPRCB *v25; // rdx
  _DWORD *v26; // r11
  int v27; // eax
  bool v28; // zf
  unsigned int v30; // [rsp+20h] [rbp-60h]
  __int128 v31; // [rsp+30h] [rbp-50h] BYREF
  __int128 v32; // [rsp+40h] [rbp-40h]
  __int128 v33[2]; // [rsp+50h] [rbp-30h] BYREF

  memset(v33, 0, sizeof(v33));
  CurrentThread = KeGetCurrentThread();
  v31 = 0i64;
  --CurrentThread->KernelApcDisable;
  v7 = KeGetCurrentThread();
  v8 = 0i64;
  v32 = 0i64;
  _disable();
  KernelAbEntries = v7->KernelAbEntries;
  AvailableEntryBitmap = KernelAbEntries->AvailableEntryBitmap;
  if ( KernelAbEntries->AvailableEntryBitmap
    || (AvailableEntryBitmap = KiAbTryReclaimOrphanedEntries(&KiDpcWatchdogConfigurationLock, v7, v7->KernelAbEntries)) != 0 )
  {
    _BitScanForward(&v11, AvailableEntryBitmap);
    v30 = v11;
    KernelAbEntries->AvailableEntryBitmap = AvailableEntryBitmap & (unsigned __int8)~(1 << v11);
    CurrentPrcb = KeGetCurrentPrcb();
    SchedulerAssist = (signed __int32 *)CurrentPrcb->SchedulerAssist;
    if ( SchedulerAssist )
    {
      _m_prefetchw(SchedulerAssist);
      v14 = *SchedulerAssist;
      do
      {
        v15 = v14;
        v14 = _InterlockedCompareExchange(SchedulerAssist, v14 & 0xFFDFFFFF, v14);
      }
      while ( v15 != v14 );
      if ( (v14 & 0x200000) != 0 )
        KiRemoveSystemWorkPriorityKick(CurrentPrcb);
    }
    _enable();
    v8 = (__int64)&KernelAbEntries->Entries[v30];
    if ( (unsigned __int64)&KiDpcWatchdogConfigurationLock >= 0xFFFF800000000000ui64
      && byte_140EB06A8[(((unsigned __int64)&KiDpcWatchdogConfigurationLock >> 39) & 0x1FF) - 256] == 1 )
    {
      SessionId = MmGetSessionIdEx(v7->ApcState.Process);
    }
    else
    {
      SessionId = -1;
    }
    *(_DWORD *)(v8 + 8) = SessionId;
    *(_QWORD *)v8 = (unsigned __int64)&KiDpcWatchdogConfigurationLock & 0x7FFFFFFFFFFFFFFCi64;
  }
  if ( _interlockedbittestandset64((volatile signed __int32 *)&KiDpcWatchdogConfigurationLock, 0i64) )
    ExfAcquirePushLockExclusiveEx(&KiDpcWatchdogConfigurationLock, v8, &KiDpcWatchdogConfigurationLock);
  if ( v8 )
    *(_BYTE *)(v8 + 18) = 1;
  v17 = KiValidateDpcWatchdogConfiguration(a1, a2, a3, &v31);
  if ( v17 >= 0 )
  {
    CurrentIrql = KeGetCurrentIrql();
    __writecr8(2ui64);
    if ( KiIrqlFlags && (KiIrqlFlags & 1) != 0 && CurrentIrql <= 0xFu )
    {
      v19 = KeGetCurrentPrcb()->SchedulerAssist;
      v20 = 4;
      if ( CurrentIrql != 2 )
        v20 = (-1i64 << (CurrentIrql + 1)) & 4;
      v19[5] |= v20;
    }
    if ( (v31 & 0x100) != 0 )
      KeDpcTimeoutMs = DWORD1(v31);
    if ( (v31 & 0x200) != 0 )
      KeDpcWatchdogPeriodMs = DWORD2(v31);
    if ( (v31 & 0x400) != 0 )
      KeDpcSoftTimeoutMs = HIDWORD(v31);
    if ( (v31 & 0x800) != 0 )
      KeDpcCumulativeSoftTimeoutMs = v32;
    if ( (v31 & 0x1000) != 0 )
      KeDpcWatchdogProfileSingleDpcThresholdMs = DWORD1(v32);
    if ( (v31 & 0x2000) != 0 )
      KeDpcWatchdogProfileCumulativeDpcThresholdMs = DWORD2(v32);
    v21 = KeDpcWatchdogProfileBufferSizeBytes;
    v22 = KeDpcWatchdogProfileBufferSizeBytes;
    if ( (v31 & 0x4000) != 0 )
    {
      v22 = HIDWORD(v32);
    }
    else if ( !KeDpcWatchdogProfileBufferSizeBytes
           && (KeDpcWatchdogProfileSingleDpcThresholdMs || KeDpcWatchdogProfileCumulativeDpcThresholdMs) )
    {
      v22 = 266240;
    }
    KeDpcWatchdogProfileBufferSizeBytes = v22;
    dword_140F6541C = v22 >> 3;
    KiApplyDpcVerificationScaleSettings();
    if ( KiIrqlFlags )
    {
      v24 = KeGetCurrentIrql();
      if ( (KiIrqlFlags & 1) != 0 && v24 <= v23 && CurrentIrql <= v23 && v24 >= 2u )
      {
        v25 = KeGetCurrentPrcb();
        v26 = v25->SchedulerAssist;
        v27 = ~(unsigned __int16)(-1i64 << (CurrentIrql + 1));
        v28 = (v27 & v26[5]) == 0;
        v26[5] &= v27;
        if ( v28 )
          KiRemoveSystemWorkPriorityKick(v25);
      }
    }
    __writecr8(CurrentIrql);
    KiCreateDpcLimitsProcessorConfiguration(v33, v21, v22);
    KeGenericProcessorCallback(&KeActiveProcessors, KiUpdateProcessorDpcWatchdogConfiguration, v33, 2i64);
    v17 = 0;
  }
  if ( (_InterlockedExchangeAdd64(&KiDpcWatchdogConfigurationLock, 0xFFFFFFFFFFFFFFFFui64) & 6) == 2 )
    ExfTryToWakePushLock(&KiDpcWatchdogConfigurationLock);
  KeAbPostRelease(&KiDpcWatchdogConfigurationLock);
  KeLeaveCriticalRegionThread(KeGetCurrentThread());
  return (unsigned int)v17;
}

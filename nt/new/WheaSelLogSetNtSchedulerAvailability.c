__int64 WheaSelLogSetNtSchedulerAvailability()
{
  struct _KTHREAD *CurrentThread; // rax
  struct _KTHREAD *v1; // rbp
  _KLOCK_ENTRY *v2; // rdi
  _KLOCK_ENTRIES *KernelAbEntries; // rsi
  unsigned int AvailableEntryBitmap; // eax
  unsigned int v5; // ecx
  struct _KPRCB *CurrentPrcb; // r8
  signed __int32 *SchedulerAssist; // rdx
  signed __int32 v8; // eax
  signed __int32 v9; // ett
  int SessionId; // eax
  unsigned int v12; // [rsp+40h] [rbp+8h]

  CurrentThread = KeGetCurrentThread();
  --CurrentThread->KernelApcDisable;
  v1 = KeGetCurrentThread();
  v2 = 0i64;
  _disable();
  KernelAbEntries = v1->KernelAbEntries;
  AvailableEntryBitmap = KernelAbEntries->AvailableEntryBitmap;
  if ( KernelAbEntries->AvailableEntryBitmap
    || (AvailableEntryBitmap = KiAbTryReclaimOrphanedEntries(&WheaIpmiContextLock, v1, v1->KernelAbEntries)) != 0 )
  {
    _BitScanForward(&v5, AvailableEntryBitmap);
    v12 = v5;
    KernelAbEntries->AvailableEntryBitmap = AvailableEntryBitmap & (unsigned __int8)~(1 << v5);
    CurrentPrcb = KeGetCurrentPrcb();
    SchedulerAssist = (signed __int32 *)CurrentPrcb->SchedulerAssist;
    if ( SchedulerAssist )
    {
      _m_prefetchw(SchedulerAssist);
      v8 = *SchedulerAssist;
      do
      {
        v9 = v8;
        v8 = _InterlockedCompareExchange(SchedulerAssist, v8 & 0xFFDFFFFF, v8);
      }
      while ( v9 != v8 );
      if ( (v8 & 0x200000) != 0 )
        KiRemoveSystemWorkPriorityKick(CurrentPrcb);
    }
    _enable();
    v2 = &KernelAbEntries->Entries[v12];
    if ( (unsigned __int64)&WheaIpmiContextLock >= 0xFFFF800000000000ui64
      && byte_140EB06A8[(((unsigned __int64)&WheaIpmiContextLock >> 39) & 0x1FF) - 256] == 1 )
    {
      SessionId = MmGetSessionIdEx(v1->ApcState.Process);
    }
    else
    {
      SessionId = -1;
    }
    v2->LockState.SessionId = SessionId;
    v2->LockState.0 = ($A1A49EE4C6E599293708B9EDC35F5B5E)((unsigned __int64)&WheaIpmiContextLock & 0x7FFFFFFFFFFFFFFCi64);
  }
  if ( _interlockedbittestandset64((volatile signed __int32 *)&WheaIpmiContextLock, 0i64) )
    ExfAcquirePushLockExclusiveEx(&WheaIpmiContextLock, v2, &WheaIpmiContextLock);
  if ( v2 )
    v2->AcquiredByte = 1;
  WheapSelLogSetNtSchedulerAvailabilityNoLock();
  if ( (_InterlockedExchangeAdd64(&WheaIpmiContextLock, 0xFFFFFFFFFFFFFFFFui64) & 6) == 2 )
    ExfTryToWakePushLock(&WheaIpmiContextLock);
  KeAbPostRelease(&WheaIpmiContextLock);
  return KeLeaveCriticalRegionThread(KeGetCurrentThread());
}

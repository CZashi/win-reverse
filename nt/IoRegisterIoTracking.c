NTSTATUS __stdcall IoRegisterIoTracking(_IO_TRACKING_SETTINGS *IoTrackerSettings, VOID **IoTracker)
{
  _QWORD *PoolWithTag; // rax
  _QWORD *v5; // rdi
  NTSTATUS result; // eax
  _ETHREAD *CurrentThread; // rax
  _QWORD *v8; // rax

  *IoTracker = 0i64;
  PoolWithTag = ExAllocatePoolWithTag(NonPagedPoolNx, 0x18u, 0x72546F49u);
  v5 = PoolWithTag;
  if ( !PoolWithTag )
    return -1073741670;
  *(_OWORD *)PoolWithTag = 0i64;
  PoolWithTag[2] = 0i64;
  PoolWithTag[2] = *((_QWORD *)IoTrackerSettings + 1);
  CurrentThread = (_ETHREAD *)KeGetCurrentThread();
  --CurrentThread->Tcb.SpecialApcDisable;
  ExAcquirePushLockExclusiveEx(&IopPerfIoTrackingLock, 0i64);
  v8 = (_QWORD *)qword_140C45978;
  if ( *(__int64 **)qword_140C45978 != &IopPerfIoTrackingListHead )
    __fastfail(3u);
  *v5 = &IopPerfIoTrackingListHead;
  v5[1] = v8;
  *v8 = v5;
  qword_140C45978 = (__int64)v5;
  if ( (_InterlockedExchangeAdd64((volatile signed __int64 *)&IopPerfIoTrackingLock, 0xFFFFFFFFFFFFFFFFui64) & 6) == 2 )
    ExfTryToWakePushLock(&IopPerfIoTrackingLock);
  KeAbPostRelease(&IopPerfIoTrackingLock);
  KiLeaveGuardedRegionUnsafe(KeGetCurrentThread());
  IopIrpExtensionControl(2ui64, 1ui64);
  IoPerfInit(2ui64);
  result = 0;
  *IoTracker = v5;
  return result;
}

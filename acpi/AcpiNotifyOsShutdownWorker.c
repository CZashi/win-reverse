int __fastcall AcpiNotifyOsShutdownWorker(__int64 a1)
{
  __int64 v2; // rcx
  int result; // eax

  ACPIInternalEvaluateOST(a1, 129i64, 129i64);
  v2 = AcpiShutdownNotification;
  *(_DWORD *)(AcpiShutdownNotification + 192) = 0;
  *(_BYTE *)v2 = 1;
  *(_QWORD *)(v2 + 200) = a1;
  ACPIInitShutdownInProgress();
  if ( AcpiNotifyOsShutdownCritical )
    return ZwInitiatePowerAction(PowerActionShutdownOff, PowerSystemSleeping3, 0x41000004u, 0);
  result = ZwInitiatePowerAction(PowerActionShutdownOff, PowerSystemSleeping3, 0x2000003u, 0);
  if ( result < 0 )
  {
    ACPIInternalEvaluateOST(a1, 129i64, 128i64);
    KeAcquireGuardedMutex(&AcpiShutdownInProgressWorkerLock);
    ACPIStopShutdownInProgress(AcpiShutdownNotification);
    return KeReleaseGuardedMutex(&AcpiShutdownInProgressWorkerLock);
  }
  return result;
}

__int64 __fastcall ACPINotifyOsShutdown(__int64 a1)
{
  __int64 v2; // rdx

  LOBYTE(v2) = KeAcquireSpinLockRaiseToDpc(&AcpiPowerLock);
  if ( AcpiNotifyOsShutdownInProgress )
  {
    KeReleaseSpinLock(&AcpiPowerLock, v2);
  }
  else
  {
    AcpiNotifyOsShutdownInProgress = 1;
    KeReleaseSpinLock(&AcpiPowerLock, v2);
    AcpiShutdownWorkItem = 0i64;
    qword_1C0081A70 = (__int64)ACPINotifyOsShutdownWorker;
    qword_1C0081A78 = a1;
    ExQueueWorkItem(&AcpiShutdownWorkItem, 1i64);
  }
  return 0i64;
}

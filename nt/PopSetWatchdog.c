// interesting for offensive purposes but it needs more analysis

_POP_WATCHDOG *__fastcall PopSetWatchdog(_POP_WATCHDOG *Instance, const _PO_WATCHDOG_CONFIG *Config, UINT8 Release)
{
  _POP_WATCHDOG *v5; // rbx
  unsigned __int64 v6; // r15
  unsigned int Param3; // er13
  unsigned __int8 v8; // di
  __int64 DurationMsec; // rax
  _POP_WATCHDOG *result; // rax
  __int64 v11; // rdx
  __int64 v12; // rax
  __int64 v13; // rax
  _LIST_ENTRY *Flink; // rcx
  _LIST_ENTRY *Blink; // rax
  char v16; // [rsp+60h] [rbp+8h]

  v16 = 0;
  v5 = Instance;
  v6 = 0i64;
  Param3 = 0;
  if ( Instance )
  {
    v8 = KeAcquireSpinLockRaiseToDpc(&PopWatchdogLock);
  }
  else
  {
    result = (_POP_WATCHDOG *)ExAllocatePoolWithTag(NonPagedPoolNx, 0x138u, 0x44574F50u);
    v5 = result;
    if ( !result )
      return result;
    memset((UINT8 *)result, 0, 0x138ui64);
    v5->Tag = 1146572624;
    v5->NoWorkers.Header.WaitListHead.Blink = &v5->NoWorkers.Header.WaitListHead;
    v5->NoWorkers.Header.WaitListHead.Flink = &v5->NoWorkers.Header.WaitListHead;
    *(_WORD *)((char *)&v5->NoWorkers.Header.Lock + 1) = 1536;
    v5->NoWorkers.Header.SignalState = 1;
    v5->Timer.Header.WaitListHead.Blink = &v5->Timer.Header.WaitListHead;
    v5->Timer.Header.WaitListHead.Flink = &v5->Timer.Header.WaitListHead;
    *(_QWORD *)&v5->Timer.Header.Lock = 0i64;
    v5->Timer.Header.Type = 8;
    v5->Timer.DueTime.QuadPart = 0i64;
    v5->Timer.Period = 0;
    v5->Timer.Processor = 0;
    v5->Dpc.DeferredRoutine = (void (__fastcall *)(_KDPC *, void *, void *, void *))PopWatchdogDpc;
    v5->Dpc.TargetInfoAsUlong = 275;
    v5->Dpc.DeferredContext = v5;
    v5->Dpc.DpcData = 0i64;
    v5->Dpc.ProcessorHistory = 0i64;
    v5->WorkItem.WorkerRoutine = (void (__fastcall *)(void *))PopWatchdogWorker;
    v5->WorkItem.Parameter = v5;
    v5->WorkItem.List.Flink = 0i64;
    v8 = KeAcquireSpinLockRaiseToDpc(&PopWatchdogLock);
    v13 = PopWatchdogList;
    if ( *(__int64 **)(PopWatchdogList + 8) != &PopWatchdogList )
      goto LABEL_23;
    v5->Entry.Flink = (_LIST_ENTRY *)PopWatchdogList;
    v5->Entry.Blink = (_LIST_ENTRY *)&PopWatchdogList;
    *(_QWORD *)(v13 + 8) = v5;
    PopWatchdogList = (__int64)v5;
  }
  if ( v5->Tag != 1146572624 )
    __fastfail(5u);
  DurationMsec = Config->DurationMsec;
  if ( (_DWORD)DurationMsec && !Release )
  {
    v11 = 10000 * DurationMsec;
    *(_OWORD *)&v5->Config.AttachSessionId = *(_OWORD *)&Config->DurationMsec;
    *(_OWORD *)&v5->Config.Param3 = *(_OWORD *)&Config->Param2;
    *(_OWORD *)&v5->StartTime = *(_OWORD *)&Config[1].DurationMsec;
    v5[1].Entry = *(_LIST_ENTRY *)&Config[1].Param2;
    *(_QWORD *)&v5[1].Tag = *(_QWORD *)&Config[2].DurationMsec;
    v12 = *(_QWORD *)&KUSER_SHARED_DATA.InterruptTime.LowPart;
    *(_QWORD *)&v5[1].NoWorkers.Header.Lock = *(_QWORD *)&KUSER_SHARED_DATA.InterruptTime.LowPart;
    v5->DeadlineTime = v11 + v12;
    v5[1].NoWorkers.Header.WaitListHead.Flink = (_LIST_ENTRY *)KeGetCurrentThread();
    v5->Active = 1;
    if ( !KiSetTimerEx(&v5->Timer, -v11, 0i64, 0i64, &v5->Dpc) )
    {
      v5->DpcMightRun = 1;
      PopUpdateWatchdogNoWorkersEvent(v5);
    }
    goto LABEL_11;
  }
  if ( v5->Config.Param1 == 412 && *(_QWORD *)&v5->Config.Param3 > 0x20ui64 )
  {
    Param3 = v5->Config.Param3;
    v16 = 1;
    v6 = (*(_QWORD *)&KUSER_SHARED_DATA.InterruptTime.LowPart - *(_QWORD *)&v5[1].NoWorkers.Header.Lock) / 0xAui64;
  }
  v5->Active = 0;
  if ( KeCancelTimer(&v5->Timer) )
  {
    v5->DpcMightRun = 0;
    PopUpdateWatchdogNoWorkersEvent(v5);
  }
  if ( !v5->NoWorkers.Header.SignalState )
  {
    KxReleaseSpinLock(&PopWatchdogLock);
    __writecr8(v8);
    KeWaitForSingleObject(&v5->NoWorkers, Executive, 0, 0, 0i64);
    v8 = KeAcquireSpinLockRaiseToDpc(&PopWatchdogLock);
  }
  if ( !Release )
    goto LABEL_11;
  Flink = v5->Entry.Flink;
  Blink = v5->Entry.Blink;
  if ( (_POP_WATCHDOG *)v5->Entry.Flink->Blink != v5 || (_POP_WATCHDOG *)Blink->Flink != v5 )
LABEL_23:
    __fastfail(3u);
  Blink->Flink = Flink;
  Flink->Blink = Blink;
  v5->Tag = 1330532174;
  ExFreePoolWithTag(v5, 0x44574F50u);
  v5 = 0i64;
LABEL_11:
  KxReleaseSpinLock(&PopWatchdogLock);
  __writecr8(v8);
  if ( v16 )
    PopCacheDisplayOnPhaseDuration(Param3, (_ETW_TP_EVENT_TIMER_EXPIRATION_END *)v6);
  return v5;
}

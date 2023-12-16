VOID __stdcall KiInitSystem()
{
  __int64 v0; // rcx
  _QWORD *v1; // rax

  if ( KiForceSymbolReferencesTrigger )
    KiForceSymbolReferences();
  v0 = 1024i64;
  LODWORD(xmmword_140E018F0) = 0;
  qword_140C31E98 = (__int64)&KeBugCheckCallbackListHead;
  KeBugCheckCallbackListHead = (INT64)&KeBugCheckCallbackListHead;
  KeBugCheckReasonCallbackListHead.Blink = &KeBugCheckReasonCallbackListHead;
  KeBugCheckReasonCallbackListHead.Flink = &KeBugCheckReasonCallbackListHead;
  qword_140C31EA8 = (__int64)&KeBugCheckAddRemovePagesCallbackListHead;
  KeBugCheckAddRemovePagesCallbackListHead = (_KBUGCHECK_REASON_CALLBACK_RECORD *)&KeBugCheckAddRemovePagesCallbackListHead;
  qword_140C31EC8 = (__int64)&KeBugCheckTriageDumpDataArrayListHead;
  KeBugCheckTriageDumpDataArrayListHead = (__int64)&KeBugCheckTriageDumpDataArrayListHead;
  KiProfileListHead.Blink = &KiProfileListHead;
  KiProfileListHead.Flink = &KiProfileListHead;
  qword_140C31D18 = (__int64)&KiProfileSourceListHead;
  KiProfileSourceListHead = (__int64)&KiProfileSourceListHead;
  KiSwapEvent.Header.WaitListHead.Blink = &KiSwapEvent.Header.WaitListHead;
  KiSwapEvent.Header.WaitListHead.Flink = &KiSwapEvent.Header.WaitListHead;
  *(_QWORD *)&KeServiceDescriptorTable = KiServiceTable;
  LODWORD(xmmword_140E018D0) = KiServiceLimit;
  *((_QWORD *)&xmmword_140E018D0 + 1) = KiArgumentTable;
  KiBalanceSetManagerPeriodicDpc.DeferredRoutine = (void (__fastcall *)(_KDPC *, void *, void *, void *))KiBalanceSetManagerDeferredRoutine;
  KiBalanceSetManagerPeriodicDpc.DeferredContext = &KiBalanceSetManagerPeriodicEvent;
  qword_140C31D70 = (__int64)&qword_140C31D68;
  qword_140C31D68 = (__int64)&qword_140C31D68;
  KiStackProtectNotifyEvent.Header.WaitListHead.Blink = &KiStackProtectNotifyEvent.Header.WaitListHead;
  KiStackProtectNotifyEvent.Header.WaitListHead.Flink = &KiStackProtectNotifyEvent.Header.WaitListHead;
  v1 = &KiAbTreeArray;
  KeBugCheckCallbackLock = 0i64;
  LOWORD(KiSwapEvent.Header.Lock) = 1;
  KiSwapEvent.Header.Size = 6;
  KiSwapEvent.Header.SignalState = 0;
  KiProcessInSwapListHead = 0i64;
  KiProcessOutSwapListHead = 0i64;
  KiStackInSwapListHead = 0i64;
  KeServiceDescriptorTableShadow = KeServiceDescriptorTable;
  xmmword_140CFBA50 = xmmword_140E018D0;
  xmmword_140CFBA60 = xmmword_140E018E0;
  xmmword_140CFBA70 = xmmword_140E018F0;
  KeServiceDescriptorTableFilter[0] = KeServiceDescriptorTable;
  xmmword_140CFBC10 = xmmword_140E018D0;
  xmmword_140CFBC20 = xmmword_140E018E0;
  xmmword_140CFBC30 = xmmword_140E018F0;
  KiBalanceSetManagerPeriodicDpc.TargetInfoAsUlong = 275;
  KiBalanceSetManagerPeriodicDpc.DpcData = 0i64;
  KiBalanceSetManagerPeriodicDpc.ProcessorHistory = 0i64;
  KiBalanceSetManagerPeriodicEvent = 1;
  byte_140C31D62 = 6;
  dword_140C31D64 = 0;
  LOWORD(KiStackProtectNotifyEvent.Header.Lock) = 0;
  KiStackProtectNotifyEvent.Header.Size = 6;
  KiStackProtectNotifyEvent.Header.SignalState = 0;
  do
  {
    *v1 = 0i64;
    v1[1] = 0i64;
    v1[2] = 0i64;
    v1 += 8;
    --v0;
  }
  while ( v0 );
  KiDynamicProcessorLock.Count = 1;
  KiDynamicProcessorLock.Event.Header.WaitListHead.Blink = &KiDynamicProcessorLock.Event.Header.WaitListHead;
  KiDynamicProcessorLock.Event.Header.WaitListHead.Flink = &KiDynamicProcessorLock.Event.Header.WaitListHead;
  KiSetVirtualHeteroClockIntervalRequestDpc.DeferredRoutine = (void (__fastcall *)(_KDPC *, void *, void *, void *))KiSetVirtualHeteroClockIntervalRequestDpcRoutine;
  KiDynamicProcessorLock.Owner = 0i64;
  KiDynamicProcessorLock.Contention = 0;
  LOWORD(KiDynamicProcessorLock.Event.Header.Lock) = 1;
  KiDynamicProcessorLock.Event.Header.Size = 6;
  KiDynamicProcessorLock.Event.Header.SignalState = 0;
  KiSetVirtualHeteroClockIntervalRequestDpc.TargetInfoAsUlong = 531;
  KiSetVirtualHeteroClockIntervalRequestDpc.DeferredContext = 0i64;
  KiSetVirtualHeteroClockIntervalRequestDpc.DpcData = 0i64;
  KiSetVirtualHeteroClockIntervalRequestDpc.ProcessorHistory = 0i64;
}

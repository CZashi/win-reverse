NTSTATUS __stdcall SbpWaitForVmbus()
{
  int result;
  VOID *NotificationEntry;
  _LARGE_INTEGER Timeout;

  NotificationEntry = 0;
  SbiVmbusArrivalEvent.Header.SignalState        = 0;
  SbiVmbusArrivalEvent.Header.WaitListHead.Blink = &SbiVmbusArrivalEvent.Header.WaitListHead;
  SbiVmbusArrivalEvent.Header.WaitListHead.Flink = &SbiVmbusArrivalEvent.Header.WaitListHead;
  LOWORD(SbiVmbusArrivalEvent.Header.Lock)       = 1;
  SbiVmbusArrivalEvent.Header.Size               = 6;
  
  result = IoRegisterPlugPlayNotification(
         EventCategoryDeviceInterfaceChange,
         1,
         VSMB_INTERFACE_GUID,
         PnpDriverObject,
         (PDRIVER_NOTIFICATION_CALLBACK_ROUTINE)SbpVmbusNotificationHandler,
         0,
         &NotificationEntry);
  
  if ( result >= 0 )
  {
    Timeout.QuadPart = -100000000i64;
    result = KeWaitForSingleObject(&SbiVmbusArrivalEvent, Executive, 0, 0, &Timeout);
    IoUnregisterPlugPlayNotification(NotificationEntry);
  }
  
  return result;
}

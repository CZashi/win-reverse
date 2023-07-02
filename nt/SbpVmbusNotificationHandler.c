NTSTATUS __stdcall SbpVmbusNotificationHandler(VOID *NotificationStructure, VOID *Context)
{
  __int64 v2; // rax

  v2 = *(_QWORD *)((char *)NotificationStructure + 4) - *(_QWORD *)&GUID_DEVICE_INTERFACE_ARRIVAL.Data1;
  if ( !v2 )
    v2 = *(_QWORD *)((char *)NotificationStructure + 12) - *(_QWORD *)GUID_DEVICE_INTERFACE_ARRIVAL.Data4;
  if ( !v2 )
    KeSetEvent(&SbiVmbusArrivalEvent, 0, 0);
  return 0;
}

NTSTATUS __stdcall HalpPostPnpInitialize()
{
  NTSTATUS result; // eax
  PVOID NotificationEntry; // [rsp+50h] [rbp+8h] BYREF

  NotificationEntry = 0i64;
  HalpInitializeSecondaryInterruptServices();
  KeInitializeEvent(&HalpDynamicDeviceInterfaceLock, SynchronizationEvent, 1u);
  
  result = IoRegisterPlugPlayNotification(
             EventCategoryDeviceInterfaceChange,
             1u,
             HalpDynamicDeviceInterfaces,
             HalpDriverObject,
             HalpDynamicDeviceInterfaceNotification,
             0i64,
             &NotificationEntry);
  HalpDynamicDevicesReady = 1;
  return result;
}

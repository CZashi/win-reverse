NTSTATUS __stdcall PoInitDriverServices()
{
  PVOID NotificationEntry; // [rsp+50h] [rbp+10h] BYREF

  NotificationEntry = 0i64;
  IoRegisterPlugPlayNotification(
    EventCategoryDeviceInterfaceChange,
    0,
    &GUID_DEVICE_THERMAL_ZONE,
    PnpDriverObject,
    (PDRIVER_NOTIFICATION_CALLBACK_ROUTINE)PopNotifyPolicyDevice,
    (PVOID)1,
    &NotificationEntry);
  NotificationEntry = 0i64;
  IoRegisterPlugPlayNotification(
    EventCategoryDeviceInterfaceChange,
    0,
    &GUID_DEVICE_BATTERY,
    PnpDriverObject,
    (PDRIVER_NOTIFICATION_CALLBACK_ROUTINE)PopNotifyPolicyDevice,
    (PVOID)2,
    &NotificationEntry);
  NotificationEntry = 0i64;
  IoRegisterPlugPlayNotification(
    EventCategoryDeviceInterfaceChange,
    0,
    &GUID_DEVICE_MEMORY,
    PnpDriverObject,
    (PDRIVER_NOTIFICATION_CALLBACK_ROUTINE)PopNotifyPolicyDevice,
    (PVOID)3,
    &NotificationEntry);
  NotificationEntry = 0i64;
  IoRegisterPlugPlayNotification(
    EventCategoryDeviceInterfaceChange,
    0,
    &GUID_DEVICE_ACPI_TIME,
    PnpDriverObject,
    (PDRIVER_NOTIFICATION_CALLBACK_ROUTINE)PopNotifyPolicyDevice,
    (PVOID)8,
    &NotificationEntry);
  NotificationEntry = 0i64;
  IoRegisterPlugPlayNotification(
    EventCategoryDeviceInterfaceChange,
    0,
    &GUID_DEVICE_FAN,
    PnpDriverObject,
    (PDRIVER_NOTIFICATION_CALLBACK_ROUTINE)PopNotifyPolicyDevice,
    (PVOID)9,
    &NotificationEntry);
  NotificationEntry = 0i64;
  return IoRegisterPlugPlayNotification(
           EventCategoryDeviceInterfaceChange,
           1u,
           &GUID_DEVINTERFACE_HPMI,
           PnpDriverObject,
           (PDRIVER_NOTIFICATION_CALLBACK_ROUTINE)PopCadHpmiPnpNotification,
           0i64,
           &NotificationEntry);
}

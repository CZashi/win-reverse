struct _POP_COOLING_EXTENSION
{
    struct _LIST_ENTRY Link;                                                //0x0
    struct _LIST_ENTRY RequestListHead;                                     //0x10
    struct _POP_RW_LOCK Lock;                                               //0x20
    struct _DEVICE_OBJECT* DeviceObject;                                    //0x30
    VOID* NotificationEntry;                                                //0x38
    UCHAR Enabled;                                                          //0x40
    UCHAR ActiveEngaged;                                                    //0x41
    UCHAR ThrottleLimit;                                                    //0x42
    UCHAR UpdatingToCurrent;                                                //0x43
    struct _KEVENT* RemovalFlushEvent;                                      //0x48
    struct _KEVENT* PnpFlushEvent;                                          //0x50
    struct _THERMAL_COOLING_INTERFACE Interface;                            //0x58
}; 


NTSTATUS __fastcall PopRegisterCoolingExtensionProtection(_POP_COOLING_EXTENSION *CoolingExtension)
{
  void **NotificationEntry; // r12
  bool v3; // zf
  int DeviceProperty; // ebx
  _DEVICE_OBJECT *DeviceAttachmentBaseRef; // rdi
  PVOID PoolWithTag; // rsi
  _UNICODE_STRING DestinationString; // [rsp+40h] [rbp-10h] BYREF
  UINT64 NumberOfBytes; // [rsp+80h] [rbp+30h] BYREF
  _FILE_OBJECT *FileObject; // [rsp+88h] [rbp+38h] BYREF
  _DEVICE_OBJECT *DeviceObject; // [rsp+90h] [rbp+40h] BYREF

  LODWORD(NumberOfBytes) = 0;
  NotificationEntry = &CoolingExtension->NotificationEntry;
  DeviceObject = 0i64;
  FileObject = 0i64;
  v3 = CoolingExtension->NotificationEntry == 0i64;
  DestinationString = 0i64;
  if ( !v3 )
    return 0;
  DeviceAttachmentBaseRef = IoGetDeviceAttachmentBaseRef(CoolingExtension->DeviceObject);
  if ( IoGetDeviceProperty(
         DeviceAttachmentBaseRef,
         DevicePropertyPhysicalDeviceObjectName,
         0,
         0i64,
         (PULONG)&NumberOfBytes) == -1073741789 )
  {
    PoolWithTag = ExAllocatePoolWithTag(PagedPool, NumberOfBytes, 0x6C6F4350u);
    if ( PoolWithTag )
    {
      DeviceProperty = IoGetDeviceProperty(
                         DeviceAttachmentBaseRef,
                         DevicePropertyPhysicalDeviceObjectName,
                         NumberOfBytes,
                         PoolWithTag,
                         (PULONG)&NumberOfBytes);
      if ( DeviceProperty >= 0 )
      {
        RtlInitUnicodeString(&DestinationString, (PCWSTR)PoolWithTag);
        DeviceProperty = IoGetDeviceObjectPointer(&DestinationString, 0x1F01FFu, &FileObject, &DeviceObject);
        if ( DeviceProperty >= 0 )
          DeviceProperty = IoRegisterPlugPlayNotification(
                             EventCategoryTargetDeviceChange,
                             0,
                             FileObject,
                             DeviceObject->DriverObject,
                             (PDRIVER_NOTIFICATION_CALLBACK_ROUTINE)PopCoolingExtensionPnpNotification,
                             CoolingExtension,
                             NotificationEntry);
        if ( FileObject )
          HalPutDmaAdapter((PADAPTER_OBJECT)FileObject);
      }
      ExFreePoolWithTag(PoolWithTag, 0x6C6F4350u);
    }
    else
    {
      DeviceProperty = -1073741670;
    }
  }
  else
  {
    DeviceProperty = -1073741823;
  }
  if ( DeviceAttachmentBaseRef )
    HalPutDmaAdapter((PADAPTER_OBJECT)DeviceAttachmentBaseRef);
  return DeviceProperty;
}

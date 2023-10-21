// no idea of what is this but looks like an executive based function to register a "Boot Device"? Just like extension hosts or ExRegisterCallback
// a more internal aspect of the function show us the _EX_BOOT_DEVICE_REGISTRATION structure to register the boot device and all registered boot devices are stored in nt!ExBootDeviceList

typedef struct _EX_BOOT_DEVICE_REGISTRATION
    USHORT Version
    PVOID DriverObject 
    PVOID DeviceObject
    PVOID IsBootDeviceReady
    PVOID Context 
} EX_BOOT_DEVICE_REGISTRATION, *PEX_BOOT_DEVICE_REGISTRATION;


NTSTATUS __stdcall ExRegisterBootDevice(_EX_BOOT_DEVICE_REGISTRATION *Registration, EX_BOOT_DEVICE_HANDLE__ **Handle)
{
  int v4; // ebx
  EX_BOOT_DEVICE_HANDLE__ *PoolWithTag; // rsi
  VOID *v6; // rcx
  unsigned __int64 v7; // rdi
  _QWORD *v8; // rax
  _QWORD *v9; // rcx
  _OBJECT_ATTRIBUTES ObjectAttributes; // [rsp+40h] [rbp-30h] BYREF
  void *ThreadHandle; // [rsp+B0h] [rbp+40h] BYREF
  PVOID Object; // [rsp+B8h] [rbp+48h] BYREF

  ThreadHandle = 0i64;
  v4 = 0;
  memset(&ObjectAttributes, 0, sizeof(ObjectAttributes));
  KeWaitForSingleObject(&ExExternalBootSupportInitializationEvent, Executive, 0, 0, 0i64);
  if ( !ExBootDeviceRemovalHandler )
  {
    ObjectAttributes.Length = 48;
    ObjectAttributes.RootDirectory = 0i64;
    ObjectAttributes.Attributes = 512;
    ObjectAttributes.ObjectName = 0i64;
    *(_OWORD *)&ObjectAttributes.SecurityDescriptor = 0i64;
    v4 = PsCreateSystemThread(&ThreadHandle, 0, &ObjectAttributes, 0i64, 0i64, ExpWaitForBootDevices, 0i64);
    if ( v4 >= 0 )
    {
      Object = 0i64;
      v4 = ObReferenceObjectByHandle(ThreadHandle, 0x1FFFFFu, 0i64, 0, &Object, 0i64);
      ExBootDeviceRemovalHandler = (PKTHREAD)Object;
      ZwClose(ThreadHandle);
      KeSetPriorityThread(ExBootDeviceRemovalHandler, 31);
    }
  }
  KeSetEvent(&ExExternalBootSupportInitializationEvent, 0, 0);
  if ( v4 >= 0 )
  {
    if ( *Registration != 1 || !*((_QWORD *)Registration + 1) || Registration[1] || !*((_QWORD *)Registration + 3) )
      v4 = -1073741811;
    if ( v4 >= 0 )
    {
      PoolWithTag = (EX_BOOT_DEVICE_HANDLE__ *)ExAllocatePoolWithTag(NonPagedPoolNx, 0x40u, 0x504E4442u);
      if ( !PoolWithTag )
        v4 = -1073741670;
      if ( v4 >= 0 )
      {
        ObfReferenceObjectWithTag(*((VOID **)Registration + 1), 0x746C6644ui64);
        v6 = (VOID *)*((_QWORD *)Registration + 2);
        if ( v6 )
          ObfReferenceObjectWithTag(v6, 0x746C6644ui64);
        memset((UINT8 *)PoolWithTag, 0, 0x40ui64);
        *(_DWORD *)PoolWithTag = 1347306562;
        *(_OWORD *)(PoolWithTag + 6) = *(_OWORD *)Registration;
        *(_OWORD *)(PoolWithTag + 10) = *((_OWORD *)Registration + 1);
        *((_QWORD *)PoolWithTag + 7) = *((_QWORD *)Registration + 4);
        v7 = (unsigned __int8)KeAcquireSpinLockRaiseToDpc(&ExBootDeviceListSpinLock);
        v8 = (_QWORD *)qword_140C191D8;
        v9 = PoolWithTag + 2;
        if ( *(__int64 **)qword_140C191D8 != &ExBootDeviceList )
          __fastfail(3u);
        *v9 = &ExBootDeviceList;
        *((_QWORD *)PoolWithTag + 2) = v8;
        *v8 = v9;
        qword_140C191D8 = (__int64)(PoolWithTag + 2);
        KxReleaseSpinLock(&ExBootDeviceListSpinLock);
        __writecr8(v7);
        *Handle = PoolWithTag;
      }
    }
  }
  return v4;
}

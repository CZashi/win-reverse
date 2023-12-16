NTSTATUS __fastcall IopInitializePlugPlayServices(_LOADER_PARAMETER_BLOCK *LoaderBlock, UINT64 Phase)
{
  _KEY_VALUE_FULL_INFORMATION *v3; // rbx
  unsigned int *v4; // rdi
  NTSTATUS result; // eax
  _DEVICE_OBJECT *v6; // rdx
  INT64 v7; // rcx
  INT64 v8; // r8
  INT64 v9; // r9
  _DEVICE_OBJECT *v10; // rdx
  INT64 v11; // rcx
  NTSTATUS CachedContextBaseKey; // ebx
  INT64 v13; // r8
  INT64 v14; // r9
  _DEVICE_OBJECT *v15; // rdx
  INT64 v16; // rcx
  INT64 v17; // r8
  INT64 v18; // r9
  _DEVICE_OBJECT *v19; // rdx
  INT64 v20; // rcx
  INT64 v21; // r8
  INT64 v22; // r9
  _DEVICE_OBJECT *v23; // rdx
  INT64 v24; // rcx
  INT64 v25; // r8
  INT64 v26; // r9
  HDRVDBCTX__ **v27; // rdx
  INT64 v28; // rcx
  VOID *v29; // rbx
  _HANDLE v30; // er8
  _LPGUID v31; // er9
  _DEVICE_OBJECT *v32; // rsi
  _DEVICE_OBJECT *v33; // rcx
  _PNP_DEVNODE_STATE *v34; // r8
  void *v35; // rdx
  const _GUID *v36; // r8
  UINT64 v37; // r9
  void *v38; // rdx
  const _GUID *v39; // r8
  UINT64 v40; // r9
  _LOADER_PERFORMANCE_DATA *p_LoaderPerformanceData; // rax
  _LOADER_PARAMETER_EXTENSION *Extension; // rcx
  HDRVDBCTX__ **v43; // rdx
  UINT8 Class; // [rsp+28h] [rbp-E0h]
  PUNICODE_STRING Classa; // [rsp+28h] [rbp-E0h]
  PUNICODE_STRING Classb; // [rsp+28h] [rbp-E0h]
  PUNICODE_STRING Classc; // [rsp+28h] [rbp-E0h]
  PUNICODE_STRING Classd; // [rsp+28h] [rbp-E0h]
  PUNICODE_STRING Classe; // [rsp+28h] [rbp-E0h]
  PUNICODE_STRING Classf; // [rsp+28h] [rbp-E0h]
  PUNICODE_STRING Classg; // [rsp+28h] [rbp-E0h]
  PUNICODE_STRING Classk; // [rsp+28h] [rbp-E0h]
  _OBJECT_ATTRIBUTES *Classh; // [rsp+28h] [rbp-E0h]
  UINT8 Classi; // [rsp+28h] [rbp-E0h]
  PUNICODE_STRING Classj; // [rsp+28h] [rbp-E0h]
  UINT64 CreateOptions; // [rsp+30h] [rbp-D8h]
  UINT64 CreateOptionsa; // [rsp+30h] [rbp-D8h]
  PULONG Disposition; // [rsp+38h] [rbp-D0h]
  PULONG Dispositiona; // [rsp+38h] [rbp-D0h]
  PULONG Dispositionc; // [rsp+38h] [rbp-D0h]
  PULONG Dispositionb; // [rsp+38h] [rbp-D0h]
  _EVENT_FILTER_DESCRIPTOR *Flags; // [rsp+40h] [rbp-C8h]
  UINT64 Flagsb; // [rsp+40h] [rbp-C8h]
  _EVENT_FILTER_DESCRIPTOR *Flagsa; // [rsp+40h] [rbp-C8h]
  UINT8 SystemFirmwareUpdated[8]; // [rsp+48h] [rbp-C0h] BYREF
  VOID *Handle; // [rsp+50h] [rbp-B8h] BYREF
  PVOID P; // [rsp+58h] [rbp-B0h] BYREF
  _UNICODE_STRING KeyName; // [rsp+60h] [rbp-A8h] BYREF
  void *KeyHandle; // [rsp+70h] [rbp-98h] BYREF
  _KEY_VALUE_FULL_INFORMATION *Information; // [rsp+78h] [rbp-90h] BYREF
  VOID *BaseHandle; // [rsp+80h] [rbp-88h] BYREF
  PVOID LoadVsmTime; // [rsp+88h] [rbp-80h] BYREF
  PVOID TcbLoaderStartTime; // [rsp+90h] [rbp-78h] BYREF
  PVOID PreloadEndTime; // [rsp+98h] [rbp-70h] BYREF
  VOID *BaseKeyHandle; // [rsp+A0h] [rbp-68h] BYREF
  _DEVICE_OBJECT *DeviceObject; // [rsp+A8h] [rbp-60h] BYREF
  unsigned int v77; // [rsp+B0h] [rbp-58h] BYREF
  int v78; // [rsp+B4h] [rbp-54h] BYREF
  _UNICODE_STRING v79; // [rsp+B8h] [rbp-50h] BYREF
  _UNICODE_STRING GuidString; // [rsp+C8h] [rbp-40h] BYREF
  _UNICODE_STRING v81; // [rsp+D8h] [rbp-30h] BYREF
  _UNICODE_STRING DestinationString; // [rsp+E8h] [rbp-20h] BYREF
  _OBJECT_ATTRIBUTES ObjectAttributes; // [rsp+F8h] [rbp-10h] BYREF
  EVENT_DESCRIPTOR v84; // [rsp+128h] [rbp+20h] BYREF
  _EVENT_DATA_DESCRIPTOR UserData; // [rsp+138h] [rbp+30h] BYREF
  _DEVICE_OBJECT **p_DeviceObject; // [rsp+158h] [rbp+50h]
  __int64 v87; // [rsp+160h] [rbp+58h]
  VOID **p_BaseKeyHandle; // [rsp+168h] [rbp+60h]
  __int64 v89; // [rsp+170h] [rbp+68h]
  PVOID *p_PreloadEndTime; // [rsp+178h] [rbp+70h]
  __int64 v91; // [rsp+180h] [rbp+78h]
  PVOID *p_TcbLoaderStartTime; // [rsp+188h] [rbp+80h]
  __int64 v93; // [rsp+190h] [rbp+88h]
  PVOID *p_LoadVsmTime; // [rsp+198h] [rbp+90h]
  __int64 v95; // [rsp+1A0h] [rbp+98h]
  VOID **p_BaseHandle; // [rsp+1A8h] [rbp+A0h]
  __int64 v97; // [rsp+1B0h] [rbp+A8h]
  _KEY_VALUE_FULL_INFORMATION **p_Information; // [rsp+1B8h] [rbp+B0h]
  __int64 v99; // [rsp+1C0h] [rbp+B8h]
  PVOID *p_P; // [rsp+1C8h] [rbp+C0h]
  __int64 v101; // [rsp+1D0h] [rbp+C8h]
  _UNICODE_STRING *v102; // [rsp+1D8h] [rbp+D0h]
  __int64 v103; // [rsp+1E0h] [rbp+D8h]

  BaseKeyHandle = 0i64;
  Handle = 0i64;
  BaseHandle = 0i64;
  *(_DWORD *)(&KeyName.MaximumLength + 1) = 0;
  DeviceObject = 0i64;
  v77 = 0;
  *(&ObjectAttributes.Length + 1) = 0;
  *(&ObjectAttributes.Attributes + 1) = 0;
  Information = 0i64;
  P = 0i64;
  LoadVsmTime = 0i64;
  TcbLoaderStartTime = 0i64;
  PreloadEndTime = 0i64;
  KeyHandle = 0i64;
  *(_DWORD *)(&v79.MaximumLength + 1) = 0;
  *(_DWORD *)(&GuidString.MaximumLength + 1) = 0;
  SystemFirmwareUpdated[0] = 0;
  DestinationString = 0i64;
  v81 = 0i64;
  if ( (_DWORD)Phase )
  {
    if ( (_DWORD)Phase != 1 )
      return -1073741584;
    result = PnpDiagInitialize((__int64)LoaderBlock, Phase);
    if ( result >= 0 )
    {
      PnpTraceInitialize();
      result = PiDcInit(1ui64);
      if ( result >= 0 )
      {
        result = PiUEventInit(
                   1ui64,
                   v38,
                   v39,
                   v40,
                   Class,
                   CreateOptions,
                   (UINT64)Disposition,
                   Flags,
                   *(PVOID *)SystemFirmwareUpdated);
        if ( result >= 0 )
        {
          p_LoaderPerformanceData = &LoaderBlock->Extension->LoaderPerformanceData;
          v84.Keyword = 80i64;
          *(_QWORD *)&v84.Id = p_LoaderPerformanceData;
          PnpDiagnosticTrace((_EVENT_DESCRIPTOR *)&KMPnPEvt_OsLoader_Time, 1ui64, &v84);
          if ( dword_140C02E30 > 4u && tlgKeywordOn((TraceLoggingHProvider)&dword_140C02E30, 0x400000000000ui64) )
          {
            Extension = LoaderBlock->Extension;
            DeviceObject = (_DEVICE_OBJECT *)Extension->LoaderPerformanceData.StartTime;
            p_DeviceObject = &DeviceObject;
            v87 = 8i64;
            BaseKeyHandle = (VOID *)Extension->LoaderPerformanceData.EndTime;
            p_BaseKeyHandle = &BaseKeyHandle;
            v89 = 8i64;
            PreloadEndTime = (PVOID)Extension->LoaderPerformanceData.PreloadEndTime;
            p_PreloadEndTime = &PreloadEndTime;
            v91 = 8i64;
            TcbLoaderStartTime = (PVOID)Extension->LoaderPerformanceData.TcbLoaderStartTime;
            p_TcbLoaderStartTime = &TcbLoaderStartTime;
            v93 = 8i64;
            LoadVsmTime = (PVOID)Extension->LoaderPerformanceData.LoadVsmTime;
            p_LoadVsmTime = &LoadVsmTime;
            v95 = 8i64;
            BaseHandle = (VOID *)Extension->LoaderPerformanceData.LaunchVsmTime;
            p_BaseHandle = &BaseHandle;
            v97 = 8i64;
            Information = (_KEY_VALUE_FULL_INFORMATION *)Extension->LoaderPerformanceData.LoadHypervisorTime;
            p_Information = &Information;
            v99 = 8i64;
            P = (PVOID)Extension->LoaderPerformanceData.LaunchHypervisorTime;
            p_P = &P;
            v101 = 8i64;
            *(_QWORD *)&v79.Length = Extension->ProcessorCounterFrequency;
            v102 = &v79;
            LODWORD(Classj) = 11;
            v103 = 8i64;
            tlgWriteTransfer_EtwWriteTransfer(
              (INT64)&dword_140C02E30,
              (UINT8 *)&byte_14002408B,
              0i64,
              0i64,
              (UINT64)Classj,
              &UserData);
          }
          TraceLoggingUnregister_EtwUnregister((_EVENT_FILTER_LEVEL_KW *)&dword_140C02E30);
          result = PiPnpRtlInit(1ui64, v43);
          if ( result >= 0 )
          {
            result = PiCslInitialize();
            if ( result >= 0 )
            {
              CachedContextBaseKey = PiDmaGuardInitialize(1i64);
              if ( CachedContextBaseKey >= 0 )
              {
                result = PiKsrInitialize();
                if ( result < 0 )
                  return result;
                PnpRequestDeviceAction(*((VOID **)IopRootDeviceNode + 4), 10, 0, 0i64, 0i64, 0i64, 0i64);
                KeInitializeEvent(&PnpShutdownEvent, NotificationEvent, 0);
                if ( (*((_DWORD *)LoaderBlock->Extension + 33) & 0x400) == 0 )
                  PpInitializeBootDDB(LoaderBlock, 1ui64);
                return 0;
              }
              return CachedContextBaseKey;
            }
          }
        }
      }
    }
  }
  else
  {
    PnPInitialized = 0;
    PnpSystemHiveLimits = 80;
    dword_140C50A54 = 90;
    CmRegisterSystemHiveLimitCallback(LoaderBlock);
    PnpSystemHiveTooLarge = 0;
    ObjectAttributes.ObjectName = &CmRegistryMachineHardwareDescriptionSystemName;
    ObjectAttributes.Length = 48;
    ObjectAttributes.RootDirectory = 0i64;
    ObjectAttributes.Attributes = 576;
    *(_OWORD *)&ObjectAttributes.SecurityDescriptor = 0i64;
    if ( ZwCreateKey(&KeyHandle, 0xF003Fu, &ObjectAttributes, 0, 0i64, 0, &v77) >= 0 )
    {
      if ( IopGetRegistryValue(KeyHandle, (wchar_t *)L"OldSystemBiosDate", 0i64, &Information) >= 0 )
      {
        v3 = Information;
        if ( Information )
        {
          if ( IopGetRegistryValue(KeyHandle, (wchar_t *)L"SystemBiosDate", 0i64, (_KEY_VALUE_FULL_INFORMATION **)&P) >= 0 )
          {
            v4 = (unsigned int *)P;
            if ( P )
            {
              RtlInitUnicodeString(&DestinationString, (PCWSTR)((char *)v3 + v3->DataOffset));
              RtlInitUnicodeString(&v81, (PCWSTR)((char *)v4 + v4[2]));
              PnpLogEvent((const VOID **)&DestinationString, (const VOID **)&v81, 1073741868, 0i64, 0);
              ExFreePoolWithTag(v4, 0);
            }
          }
          ExFreePoolWithTag(v3, 0);
        }
      }
      ZwClose(KeyHandle);
    }
    result = PnpDeviceCompletionQueueInitialize();
    if ( result >= 0 )
    {
      PiInitFirmwareResources(LoaderBlock);
      if ( (*((_DWORD *)LoaderBlock->Extension + 33) & 0x400) == 0 )
        PpInitializeBootDDB(LoaderBlock, 0i64);
      PipInitDeviceOverrideCache();
      KeInitializeEvent(&PnpSystemDeviceEnumerationComplete, NotificationEvent, 0);
      result = PiInitCacheGroupInformation();
      if ( result >= 0 )
      {
        KeInitializeSemaphore(&PpRegistrySemaphore, 1, 1);
        result = PnpInitializeLegacyBusInformationTable();
        if ( result >= 0 )
        {
          IopInitializeResourceMap(LoaderBlock);
          IopAllocateBootResourcesRoutine = (__int64)IopReportBootResources;
          IopInitReservedResourceList = 0i64;
          PnpDefaultInterfaceType = 1;
          ArbInitializeOsInaccessibleRange((unsigned int)MaxPhysicalAddressBits);
          CachedContextBaseKey = IopPortInitialize(v7, v6, v8, v9, &Classa->Length);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          CachedContextBaseKey = IopMemInitialize(v11, v10, v13, v14, &Classb->Length);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          CachedContextBaseKey = IopDmaInitialize(v16, v15, v17, v18, &Classc->Length);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          CachedContextBaseKey = IopIrqInitialize(v20, v19, v21, v22, &Classd->Length);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          CachedContextBaseKey = IopBusNumberInitialize(v24, v23, v25, v26, &Classe->Length);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          CachedContextBaseKey = PiPnpRtlInit(0i64, v27);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          PipMigratePnpState();
          CachedContextBaseKey = PiDmInit();
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          CachedContextBaseKey = PnpCtxGetCachedContextBaseKey(
                                   PiPnpRtlCtx,
                                   PNPCTX_BASE_KEY_TYPE_CONTROLSET,
                                   &BaseHandle);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          KeyName.Buffer = L"Control\\Pnp";
          *(_DWORD *)&KeyName.Length = 1572886;
          LODWORD(Classf) = 0;
          if ( IopCreateRegistryKeyEx(&Handle, BaseHandle, &KeyName, 0xF003Fui64, (UINT64)Classf, 0i64) >= 0 )
          {
            if ( IopGetRegistryValue(
                   Handle,
                   (wchar_t *)L"AsynchronousOptions",
                   0i64,
                   (_KEY_VALUE_FULL_INFORMATION **)&LoadVsmTime) >= 0 )
            {
              if ( *((_DWORD *)LoadVsmTime + 1) == 4 && *((_DWORD *)LoadVsmTime + 3) == 4 )
                PnpAsyncOptions = *(_DWORD *)((char *)LoadVsmTime + *((unsigned int *)LoadVsmTime + 2));
              ExFreePoolWithTag(LoadVsmTime, 0);
            }
            if ( IopGetRegistryValue(
                   Handle,
                   (wchar_t *)L"BootOptions",
                   0i64,
                   (_KEY_VALUE_FULL_INFORMATION **)&TcbLoaderStartTime) >= 0 )
            {
              if ( *((_DWORD *)TcbLoaderStartTime + 1) == 4 && *((_DWORD *)TcbLoaderStartTime + 3) == 4 )
                PnpBootOptions = *(_DWORD *)((char *)TcbLoaderStartTime + *((unsigned int *)TcbLoaderStartTime + 2));
              ExFreePoolWithTag(TcbLoaderStartTime, 0);
            }
            if ( IopGetRegistryValue(
                   Handle,
                   (wchar_t *)L"FindBestConfigurationTimeout",
                   0i64,
                   (_KEY_VALUE_FULL_INFORMATION **)&PreloadEndTime) >= 0 )
            {
              if ( *((_DWORD *)PreloadEndTime + 1) == 4 && *((_DWORD *)PreloadEndTime + 3) == 4 )
                PnpFindBestConfigurationTimeout = *(_DWORD *)((char *)PreloadEndTime
                                                            + *((unsigned int *)PreloadEndTime + 2));
              ExFreePoolWithTag(PreloadEndTime, 0);
            }
            PiDmaGuardProcessRegistry(Handle);
            IopQueryDeviceResetRegistrySettings(Handle);
            ZwClose(Handle);
          }
          *(_DWORD *)&KeyName.Length = 4063292;
          KeyName.Buffer = L"\\Registry\\Machine\\System\\Setup";
          if ( IopOpenRegistryKeyEx(&Handle, 0i64, &KeyName, 0x20019ui64) >= 0 )
          {
            PipUpdateSetupInProgress((_HANDLE)Handle);
            if ( IopGetRegistryValue(Handle, (wchar_t *)L"Upgrade", 0i64, (_KEY_VALUE_FULL_INFORMATION **)&P) >= 0 )
            {
              if ( *((_DWORD *)P + 1) == 4
                && *((_DWORD *)P + 3) == 4
                && *(_DWORD *)((char *)P + *((unsigned int *)P + 2)) )
              {
                PnpSetupUpgradeInProgress = 1;
              }
              ExFreePoolWithTag(P, 0);
            }
            if ( IopGetRegistryValue(Handle, (wchar_t *)L"RollbackActive", 0i64, (_KEY_VALUE_FULL_INFORMATION **)&P) >= 0 )
            {
              if ( *((_DWORD *)P + 1) == 4
                && *((_DWORD *)P + 3) == 4
                && *(_DWORD *)((char *)P + *((unsigned int *)P + 2)) )
              {
                PnpSetupRollbackActiveInProgress = 1;
              }
              ExFreePoolWithTag(P, 0);
            }
            if ( PnpSetupInProgress || PnpSetupOOBEInProgress )
            {
              qword_140C454F0 = (__int64)PipUpdateSetupInProgressCallback;
              qword_140C454F8 = (__int64)Handle;
              PnpSetupWorkItem = 0i64;
              PipUpdateSetupInProgressNotify((_HANDLE)Handle);
            }
            else
            {
              ZwClose(Handle);
            }
            Handle = 0i64;
          }
          CachedContextBaseKey = PipHardwareConfigInit(&LoaderBlock->Extension->HardwareConfigurationId);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          PipCheckSystemFirmwareUpdated(SystemFirmwareUpdated);
          CachedContextBaseKey = PiDcInit(0i64);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          CachedContextBaseKey = PiAuCreateSecurityObjects();
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          CachedContextBaseKey = PiDqInit();
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          CachedContextBaseKey = PpDevCfgInit();
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          PipResetDevices(v28);
          CachedContextBaseKey = CmCreateDevice(
                                   (HPNPCTX *)PiPnpRtlCtx,
                                   (WCHAR *)L"HTREE\\ROOT\\0",
                                   983103,
                                   &BaseKeyHandle,
                                   0i64,
                                   0);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          v29 = BaseKeyHandle;
          LODWORD(Flags) = 0;
          LODWORD(Dispositiona) = 78;
          LODWORD(Classg) = 1;
          CmSetDeviceRegProp(
            (HPNPCTX *)PiPnpRtlCtx,
            (WCHAR *)L"HTREE\\ROOT\\0",
            BaseKeyHandle,
            CM_REG_PROP_BASE_CONTAINERID,
            (UINT64)Classg,
            (UINT8 *)L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}",
            (UINT64)Dispositiona,
            (UINT64)Flags);
          LODWORD(Flagsb) = 0;
          LODWORD(Dispositionc) = 4;
          LODWORD(Classk) = 4;
          v78 = 0;
          CmSetDeviceRegProp(
            (HPNPCTX *)PiPnpRtlCtx,
            (WCHAR *)L"HTREE\\ROOT\\0",
            v29,
            CM_REG_PROP_CONFIGFLAGS,
            (UINT64)Classk,
            (UINT8 *)&v78,
            (UINT64)Dispositionc,
            Flagsb);
          ZwClose(v29);
          qword_140C44A18 = (__int64)&IopPendingEjects;
          IopPendingEjects = (PENDING_RELATIONS_LIST_ENTRY *)&IopPendingEjects;
          qword_140C44A28 = (__int64)&IopPendingSurpriseRemovals;
          IopPendingSurpriseRemovals = &IopPendingSurpriseRemovals;
          ExInitializeResourceLite(&IopDeviceTreeLock);
          ExInitializeResourceLite(&IopSurpriseRemoveListLock);
          ExInitializeResourceLite(&PnpDevicePropertyLock);
          ExInitializeResourceLite(&PiEngineLock);
          PnpSpinLock = 0i64;
          KeInitializeGuardedMutex(&PiResourceListLock);
          PnpRebuildPowerRelationsQueueLock.Count = 1;
          PnpRebuildPowerRelationsQueueLock.Event.Header.WaitListHead.Blink = &PnpRebuildPowerRelationsQueueLock.Event.Header.WaitListHead;
          PnpRebuildPowerRelationsQueueLock.Event.Header.WaitListHead.Flink = &PnpRebuildPowerRelationsQueueLock.Event.Header.WaitListHead;
          PnpRebuildPowerRelationsQueueLock.Owner = 0i64;
          PnpRebuildPowerRelationsQueueLock.Contention = 0;
          LOWORD(PnpRebuildPowerRelationsQueueLock.Event.Header.Lock) = 1;
          PnpRebuildPowerRelationsQueueLock.Event.Header.Size = 6;
          PnpRebuildPowerRelationsQueueLock.Event.Header.SignalState = 0;
          CachedContextBaseKey = PiDeviceDependencyInit();
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          CachedContextBaseKey = PnpInitializeDeviceActions();
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          PpProfileInit();
          IopWarmEjectPdo = 0i64;
          KeInitializeEvent(&IopWarmEjectLock, SynchronizationEvent, 1u);
          *(_DWORD *)&KeyName.Length = 2490404;
          KeyName.Buffer = L"\\Driver\\PnpManager";
          CachedContextBaseKey = IoCreateDriver((PHANDLE)&KeyName, (_ACCESS_MASK)PipPnPDriverEntry, v30, v31, Classh);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          CachedContextBaseKey = IoCreateDevice(PnpDriverObject, 0, 0i64, 4u, 0, 0, &DeviceObject);
          if ( CachedContextBaseKey < 0 )
            return CachedContextBaseKey;
          v32 = DeviceObject;
          v33 = DeviceObject;
          DeviceObject->Flags |= 0x1000u;
          CachedContextBaseKey = PipAllocateDeviceNode(v33, (_DEVICE_NODE **)&IopRootDeviceNode);
          if ( !IopRootDeviceNode )
          {
            IoDeleteDevice(v32);
            IoDeleteDriver(PnpDriverObject);
LABEL_73:
            if ( CachedContextBaseKey >= 0 )
            {
              CachedContextBaseKey = CmAddDeviceToContainer(
                                       (__int64)PiPnpRtlCtx,
                                       (WCHAR *)L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}",
                                       (__int64)L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}",
                                       (__int64)L"HTREE\\ROOT\\0",
                                       0i64);
              if ( CachedContextBaseKey >= 0 )
              {
                if ( SystemFirmwareUpdated[0] )
                  PiDcHandleSystemFirmwareUpdate();
                PnpInitializePnpWatchdogs();
                CachedContextBaseKey = PnpInitializeDeviceEvents();
                if ( CachedContextBaseKey >= 0 )
                {
                  PnpInitializeNotification();
                  CachedContextBaseKey = PnpBusTypeGuidInitialize();
                  if ( CachedContextBaseKey >= 0 )
                  {
                    KeInitializeEvent(&PnpReplaceEvent, SynchronizationEvent, 1u);
                    CachedContextBaseKey = PiSwInit();
                    if ( CachedContextBaseKey >= 0 )
                    {
                      CachedContextBaseKey = PiUEventInit(
                                               0i64,
                                               v35,
                                               v36,
                                               v37,
                                               Classi,
                                               CreateOptionsa,
                                               (UINT64)Dispositionb,
                                               Flagsa,
                                               *(PVOID *)SystemFirmwareUpdated);
                      if ( CachedContextBaseKey >= 0 )
                      {
                        CachedContextBaseKey = PiDaInit();
                        if ( CachedContextBaseKey >= 0 )
                        {
                          CachedContextBaseKey = PiDmaGuardInitialize(0i64);
                          if ( CachedContextBaseKey >= 0 )
                          {
                            PipProcessPendingOperations();
                            PnpRequestDeviceAction(*((VOID **)IopRootDeviceNode + 4), 10, 0, 0i64, 0i64, 0i64, 0i64);
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            return CachedContextBaseKey;
          }
          PipSetDevNodeFlags((_DEVICE_NODE *)IopRootDeviceNode, 0x131ui64);
          PipSetDevNodeUserFlags((_DEVICE_NODE *)IopRootDeviceNode, 0xAui64);
          *((_DWORD *)IopRootDeviceNode + 165) = -2;
          CachedContextBaseKey = PnpAllocateDeviceInstancePath((__int64)IopRootDeviceNode, 0x1Au);
          if ( CachedContextBaseKey >= 0 )
          {
            *(_DWORD *)&v79.Length = 1703960;
            v79.Buffer = (wchar_t *)L"HTREE\\ROOT\\0";
            PnpCopyDeviceInstancePath((__int64)IopRootDeviceNode, &v79);
            CachedContextBaseKey = PnpMapDeviceObjectToDeviceInstance(
                                     *((_QWORD *)IopRootDeviceNode + 4),
                                     (__int64)IopRootDeviceNode + 40);
            if ( CachedContextBaseKey >= 0 )
            {
              *(_DWORD *)&GuidString.Length = 5111884;
              GuidString.Buffer = (wchar_t *)L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}";
              RtlGUIDFromString(&GuidString, (GUID *)((char *)IopRootDeviceNode + 664));
              PnpQueryAndSaveDeviceNodeCapabilities((__int64)IopRootDeviceNode);
              PipSetDevNodeState((_DEVICE_NODE *)IopRootDeviceNode, DeviceNodeStarted, v34);
              goto LABEL_73;
            }
          }
          return CachedContextBaseKey;
        }
      }
    }
  }
  return result;
}

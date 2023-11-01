UINT8 __stdcall IoInitSystemPreDrivers(_LOADER_PARAMETER_BLOCK *LoaderBlock)
{
  unsigned __int64 v2; // r8
  int v3; // eax
  ULONG ActiveProcessorCount; // eax
  __int64 v5; // rcx
  unsigned int v6; // ebx
  UINT8 *v7; // rbx
  unsigned int v8; // eax
  __int64 v9; // rcx
  int v10; // eax
  INT64 v11; // rdx
  INT64 v12; // r8
  INT64 v13; // r9
  UINT8 v14; // bl
  INT64 v15; // rcx
  ULONG v16; // ebx
  NTSTATUS SystemDlls; // eax
  bool IsStateSeparationDevModeEnabled; // al
  INT64 Depth; // [rsp+28h] [rbp-E0h]
  UINT64 *Deptha; // [rsp+28h] [rbp-E0h]
  INT64 Depthb; // [rsp+28h] [rbp-E0h]
  const _WNF_STATE_NAME *v23; // [rsp+38h] [rbp-D0h]
  UINT64 v24; // [rsp+40h] [rbp-C8h]
  UINT64 Size; // [rsp+48h] [rbp-C0h] BYREF
  INT64 Tag; // [rsp+50h] [rbp-B8h] BYREF
  unsigned int ResultLength[2]; // [rsp+58h] [rbp-B0h] BYREF
  PVOID Object; // [rsp+60h] [rbp-A8h] BYREF
  _OBJECT_ATTRIBUTES ObjectAttributes; // [rsp+68h] [rbp-A0h] BYREF
  _UNICODE_STRING DestinationString; // [rsp+98h] [rbp-70h] BYREF
  _STRING NtDeviceName; // [rsp+A8h] [rbp-60h] BYREF
  _DRIVER_OBJECT *PreviousDriver; // [rsp+B8h] [rbp-50h] BYREF
  ULONG_PTR Context; // [rsp+C0h] [rbp-48h] BYREF
  ULONG v34; // [rsp+C4h] [rbp-44h]
  __int128 v35; // [rsp+C8h] [rbp-40h]
  __int64 v36; // [rsp+D8h] [rbp-30h]
  _IO_STATUS_BLOCK IoStatusBlock; // [rsp+E0h] [rbp-28h] BYREF
  _IO_PROC_INIT_VALUES InitValues; // [rsp+F0h] [rbp-18h] BYREF

  *(_QWORD *)&NtDeviceName.Length = 0x1000000i64;
  v36 = 0i64;
  PreviousDriver = 0i64;
  *(&ObjectAttributes.Length + 1) = 0;
  *(&ObjectAttributes.Attributes + 1) = 0;
  Tag = 0i64;
  v35 = 0i64;
  LOBYTE(Size) = 0;
  DestinationString = 0i64;
  NtDeviceName.Buffer = (char *)IoInitSystem_deviceNameBuffer;
  IoStatusBlock = 0i64;
  memset(&InitValues, 0, sizeof(InitValues));
  ExInitializeResourceLite(&IopDriverLoadResource);
  ExInitializeResourceLite(&IopDatabaseResource);
  ExInitializeResourceLite(&IopSecurityResource);
  ExInitializeResourceLite(&IopCrashDumpLock);
  ExInitializeResourceLite(&IopLiveDumpLock);
  ExInitializePushLock(&IopFilesystemDatabaseShutdownRundown);
  IopPerfIoTrackingLock.0 = 0i64;
  IopDiskFileSystemQueueHead.Blink = &IopDiskFileSystemQueueHead;
  IopDiskFileSystemQueueHead.Flink = &IopDiskFileSystemQueueHead;
  IopCdRomFileSystemQueueHead.Blink = &IopCdRomFileSystemQueueHead;
  IopCdRomFileSystemQueueHead.Flink = &IopCdRomFileSystemQueueHead;
  IopTapeFileSystemQueueHead.Blink = &IopTapeFileSystemQueueHead;
  IopTapeFileSystemQueueHead.Flink = &IopTapeFileSystemQueueHead;
  IopNetworkFileSystemQueueHead.Blink = &IopNetworkFileSystemQueueHead;
  IopNetworkFileSystemQueueHead.Flink = &IopNetworkFileSystemQueueHead;
  IopBootDriverReinitializeQueueHead.Blink = &IopBootDriverReinitializeQueueHead;
  IopBootDriverReinitializeQueueHead.Flink = &IopBootDriverReinitializeQueueHead;
  IopDriverReinitializeQueueHead.Blink = &IopDriverReinitializeQueueHead;
  IopDriverReinitializeQueueHead.Flink = &IopDriverReinitializeQueueHead;
  IopNotifyShutdownQueueHead.Blink = &IopNotifyShutdownQueueHead;
  IopNotifyShutdownQueueHead.Flink = &IopNotifyShutdownQueueHead;
  IopNotifyLastChanceShutdownQueueHead.Blink = &IopNotifyLastChanceShutdownQueueHead;
  IopNotifyLastChanceShutdownQueueHead.Flink = &IopNotifyLastChanceShutdownQueueHead;
  qword_140C45968 = (__int64)&IopFsNotifyChangeQueueHead;
  IopFsNotifyChangeQueueHead = (__int64)&IopFsNotifyChangeQueueHead;
  qword_140C45978 = (__int64)&IopPerfIoTrackingListHead;
  IopPerfIoTrackingListHead = (__int64)&IopPerfIoTrackingListHead;
  *(_QWORD *)&IoStatisticsLock = 0i64;
  IopFunctionPointerLock = 0i64;
  IopDiskIoAttributionTree = 0i64;
  IopUniqueDeviceObjectNumber = 0;
  IopIrpStackProfilerFlags = 0;
  v2 = __rdtsc() >> 4;
  v3 = 0;
  IopUniqueDriverObjectNumber = v2 % 0x64 + 10;
  if ( !IopLargeIrpStackLocations )
  {
    IopLargeIrpStackLocations = 14;
    v3 = 1;
    IopIrpStackProfilerFlags = 1;
  }
  if ( !IopMediumIrpStackLocations )
  {
    IopMediumIrpStackLocations = 4;
    IopIrpStackProfilerFlags = v3 | 2;
  }
  if ( (unsigned int)(IopIrpCompletionTimeoutInSeconds - 2) > 0x12A )
    IopIrpCompletionTimeoutInSeconds = 300;
  IopQueryProcessorInitValues(&InitValues);
  ExInitializeSystemLookasideList(
    &IopCompletionLookasideList,
    NonPagedPoolNx,
    0x38ui64,
    0x20706349ui64,
    InitValues.CompletionZoneSize,
    &ExSystemLookasideListHead);
  ExInitializeSystemLookasideList(
    &IopLargeIrpLookasideList,
    NonPagedPoolNx,
    InitValues.LargePacketSize,
    0x6C707249ui64,
    InitValues.LargeIrpZoneSize,
    &ExSystemLookasideListHead);
  ExInitializeSystemLookasideList(
    &IopMediumIrpLookasideList,
    NonPagedPoolNx,
    InitValues.MediumPacketSize,
    0x6D707249ui64,
    InitValues.MediumIrpZoneSize,
    &ExSystemLookasideListHead);
  ExInitializeSystemLookasideList(
    &IopSmallIrpLookasideList,
    NonPagedPoolNx,
    InitValues.SmallPacketSize,
    0x73707249ui64,
    InitValues.SmallIrpZoneSize,
    &ExSystemLookasideListHead);
  ExInitializeSystemLookasideList(
    &IopMdlLookasideList,
    NonPagedPoolNx,
    InitValues.MdlPacketSize,
    0x206C644Dui64,
    InitValues.MdlZoneSize,
    &ExSystemLookasideListHead);
  ExInitializeNPagedLookasideList(&IopSafeCompletionLookasideList, 0i64, 0i64, 0x200u, 0x20u, 0x73556F49u, 0);
  FsRtlInitExtraCreateParameterLookasideList(&IopSymlinkInfoLookasideList, 0, 0x11Eu, 0x69536F49u);
  ExInitializeNPagedLookasideList(&IopOplockFoExtLookasideList, 0i64, 0i64, 0x200u, 0x30u, 0x7443704Fu, 0);
  ActiveProcessorCount = KeQueryActiveProcessorCountEx(0xFFFFu);
  v5 = 0i64;
  v6 = ActiveProcessorCount;
  for ( ResultLength[0] = 0; (unsigned int)v5 < v6; ResultLength[0] = v5 )
  {
    IoInitializeProcessor(*(&KiProcessorBlock + v5), &InitValues);
    v5 = ResultLength[0] + 1;
  }
  IopErrorLogLock = 0i64;
  qword_140C459B8 = (__int64)&IopErrorLogListHead;
  IopErrorLogListHead = (__int64)&IopErrorLogListHead;
  if ( IopInitializeReserveIrps() )
  {
    if ( (IopIrpStackProfilerFlags & 3) != 0 )
    {
      IopIrpStackProfilerMinSizeThreshold = 400;
      IopIrpStackProfilerDpc.DeferredRoutine = (void (__fastcall *)(_KDPC *, void *, void *, void *))IopIrpStackProfilerDpcRoutine;
      IopIrpStackProfilerFlags |= 4u;
      IopIrpStackProfilerSampleSize = 2000;
      IopIrpStackProfilerDpc.TargetInfoAsUlong = 275;
      IopIrpStackProfilerDpc.DeferredContext = 0i64;
      IopIrpStackProfilerDpc.DpcData = 0i64;
      IopIrpStackProfilerDpc.ProcessorHistory = 0i64;
    }
    v7 = IopRevocationExtension;
    memset(IopRevocationExtension, 0, 0x58ui64);
    *(_DWORD *)v7 = 4;
    v8 = IopDiskIoAttributionBaseIoSize;
    if ( (unsigned int)IopDiskIoAttributionBaseIoSize >= 0x400000 )
    {
      v8 = 0x400000;
      IopDiskIoAttributionBaseIoSize = 0x400000;
    }
    if ( v8 <= 0x1000 )
      IopDiskIoAttributionBaseIoSize = 4096;
    ObjectAttributes.Length = 48;
    ObjectAttributes.ObjectName = &CmRegistryMachineSystemCurrentControlSetServicesEventLog;
    ObjectAttributes.RootDirectory = 0i64;
    ObjectAttributes.Attributes = 576;
    *(_OWORD *)&ObjectAttributes.SecurityDescriptor = 0i64;
    if ( ZwOpenKey((PHANDLE)&Tag, 0x20019u, &ObjectAttributes) < 0 )
    {
      IopErrorLogDisabledThisBoot = 1;
    }
    else
    {
      RtlInitUnicodeString(&DestinationString, L"Start");
      LODWORD(Depth) = 32;
      IopErrorLogDisabledThisBoot = NtQueryValueKey(
                                      (VOID *)Tag,
                                      &DestinationString,
                                      KeyValuePartialInformation,
                                      IoInitSystem_valueBuffer,
                                      Depth,
                                      (UINT64 *)ResultLength) < 0
                                 || dword_140D57944 != 4
                                 || dword_140D5794C == 4;
      ObCloseHandle((HANDLE)Tag, 0);
    }
    *(_QWORD *)&IopTimer.Header.Lock = 9i64;
    IopTimerQueueHead.Blink = &IopTimerQueueHead;
    IopTimerQueueHead.Flink = &IopTimerQueueHead;
    IopTimerLock = 0i64;
    IopTimerDpc.DeferredRoutine = (void (__fastcall *)(_KDPC *, void *, void *, void *))IopTimerDispatch;
    IopTimerDpc.DeferredContext = &IopTimerCount;
    IopTimer.Header.WaitListHead.Blink = &IopTimer.Header.WaitListHead;
    IopTimer.Header.WaitListHead.Flink = &IopTimer.Header.WaitListHead;
    qword_140C45B68 = (__int64)&IopDeadIrps;
    IopDeadIrps = (__int64)&IopDeadIrps;
    IopHardError.WorkerRoutine = (void (__fastcall *)(void *))IopHardErrorThread;
    qword_140C45C68 = (__int64)&qword_140C45C60;
    qword_140C45C60 = (__int64)&qword_140C45C60;
    stru_140C45C78.Header.WaitListHead.Blink = &stru_140C45C78.Header.WaitListHead;
    stru_140C45C78.Header.WaitListHead.Flink = &stru_140C45C78.Header.WaitListHead;
    IopKeepAliveTracker.WorkerRoutine = (void (__fastcall *)(void *))IopKeepAliveWorker;
    qword_140C45BE8 = (__int64)&qword_140C45BE0;
    qword_140C45BE0 = &qword_140C45BE0;
    IopTimerDpc.TargetInfoAsUlong = 275;
    IopTimerDpc.DpcData = 0i64;
    IopTimerDpc.ProcessorHistory = 0i64;
    IopTimer.DueTime.QuadPart = 0i64;
    IopTimer.Period = 0;
    IopTimer.Processor = 0;
    IopHardError.Parameter = 0i64;
    IopHardError.List.Flink = 0i64;
    qword_140C45C70 = 0i64;
    stru_140C45C78.Header.Type = 5;
    stru_140C45C78.Header.Size = 8;
    stru_140C45C78.Header.SignalState = 0;
    stru_140C45C78.Limit = 0x7FFFFFFF;
    byte_140C45C98 = 0;
    IopKeepAliveTracker.Parameter = 0i64;
    IopKeepAliveTracker.List.Flink = 0i64;
    qword_140C45BF0[0] = 0i64;
    byte_140C45C18 = 0;
    IopErrorLogSessionPending = 1;
    RtlInitUnicodeString(&DestinationString, L"\\Security\\TRKWKS_EVENT");
    ObjectAttributes.Length = 48;
    ObjectAttributes.ObjectName = &DestinationString;
    ObjectAttributes.RootDirectory = 0i64;
    ObjectAttributes.Attributes = 528;
    *(_OWORD *)&ObjectAttributes.SecurityDescriptor = 0i64;
    if ( NtCreateEvent((PHANDLE)&Tag, 0x1F0003u, &ObjectAttributes, NotificationEvent, 0) < 0 )
    {
      HeadlessKernelAddLogEntry(4ui64, 0i64);
    }
    else
    {
      Object = 0i64;
      ObReferenceObjectByHandle((HANDLE)Tag, 0, (POBJECT_TYPE)ExEventObjectType, 0, &Object, 0i64);
      IopLinkTrackingServiceEvent = (__int64)Object;
      IopMountCompletionEvent.Header.WaitListHead.Blink = &IopMountCompletionEvent.Header.WaitListHead;
      IopMountCompletionEvent.Header.WaitListHead.Flink = &IopMountCompletionEvent.Header.WaitListHead;
      stru_140C45CE0.Header.WaitListHead.Blink = &stru_140C45CE0.Header.WaitListHead;
      stru_140C45CE0.Header.WaitListHead.Flink = &stru_140C45CE0.Header.WaitListHead;
      IopLinkTrackingPortObject.Header.WaitListHead.Blink = &IopLinkTrackingPortObject.Header.WaitListHead;
      IopLinkTrackingPortObject.Header.WaitListHead.Flink = &IopLinkTrackingPortObject.Header.WaitListHead;
      LOWORD(IopMountCompletionEvent.Header.Lock) = 0;
      IopMountCompletionEvent.Header.Size = 6;
      IopMountCompletionEvent.Header.SignalState = 0;
      LOWORD(stru_140C45CE0.Header.Lock) = 0;
      stru_140C45CE0.Header.Size = 6;
      stru_140C45CE0.Header.SignalState = 0;
      LOWORD(IopLinkTrackingPortObject.Header.Lock) = 1;
      IopLinkTrackingPortObject.Header.Size = 6;
      IopLinkTrackingPortObject.Header.SignalState = 1;
      ObCloseHandle((HANDLE)Tag, 0);
      if ( IopCreateRootDirectories() )
      {
        if ( IopInitializeSessionNotifications() < 0 )
        {
          IopInitFailCode = 15;
        }
        else if ( IopInitializePlugPlayServices(LoaderBlock, 0i64) < 0 )
        {
          HeadlessKernelAddLogEntry(7ui64, 0i64);
          IopInitFailCode = 4;
        }
        else
        {
          KseInitialize(LoaderBlock, 0i64);
          PoInitDriverServices();
          ((void (*)(void))off_140C00AC0[0])();
          PnpMarkHalDeviceNode();
          if ( WMIInitialize(0i64, LoaderBlock) )
          {
            if ( !RtlIsStateSeparationEnabled()
              || (IsStateSeparationDevModeEnabled = CmIsStateSeparationDevModeEnabled(),
                  LOBYTE(v9) = 1,
                  IsStateSeparationDevModeEnabled) )
            {
              LOBYTE(v9) = 0;
            }
            v10 = ExpInitializeStateSeparationPhase0(v9);
            if ( (int)(v10 + 0x80000000) < 0 || v10 == -1073741637 )
            {
              EtwInitialize(0i64);
              if ( EtwRegister(&IoTraceProvider, (PETWENABLECALLBACK)IopEtwEnableCallback, 0i64, &IoTraceHandle) < 0 )
              {
                IopInitFailCode = 16;
              }
              else if ( EtwRegister(&IoMgrProvider, 0i64, 0i64, &IoMgrTraceHandle) < 0 )
              {
                IopInitFailCode = 11;
              }
              else
              {
                SeAuditBootConfiguration((_BOOT_ENTRY_OPTION *)LoaderBlock->Extension->BootOptions);
                BootApplicationPersistentDataProcess(1i64, v11, v12, v13, Deptha);
                BapdRecordFirmwareBootStats();
                KdInitialize(2i64, 0i64, &KdpContext);
                TraceLoggingRegisterEx_EtwRegister_EtwSetInformation(&dword_140C01A70);
                if ( !IopErrorLogDisabledThisBoot )
                {
                  v14 = KeAcquireSpinLockRaiseToDpc(&IopErrorLogLock);
                  if ( (__int64 *)IopErrorLogListHead == &IopErrorLogListHead )
                  {
                    IopErrorLogSessionPending = 0;
                  }
                  else
                  {
                    IopErrorLogWorkItem.Parameter = 0i64;
                    IopErrorLogWorkItem.WorkerRoutine = (void (__fastcall *)(void *))IopErrorLogThread;
                    IopErrorLogWorkItem.List.Flink = 0i64;
                    ExQueueWorkItem(&IopErrorLogWorkItem, DelayedWorkQueue);
                  }
                  KeReleaseSpinLock(&IopErrorLogLock, v14);
                }
                WheaInitialize(LoaderBlock, 0i64);
                if ( IopStoreArcInformation(LoaderBlock) >= 0 )
                {
                  if ( IopInitializePlugPlayServices(LoaderBlock, 1ui64) < 0 )
                  {
                    HeadlessKernelAddLogEntry(8ui64, 0i64);
                    IopInitFailCode = 5;
                  }
                  else
                  {
                    RtlInitializeGenericTableAvl(
                      &IoStatusBlockRangeTable,
                      (PRTL_AVL_COMPARE_ROUTINE)IopCompareIosbRanges,
                      (PRTL_AVL_ALLOCATE_ROUTINE)IopAllocateGenericTableEntry,
                      (PRTL_AVL_FREE_ROUTINE)IopFreeGenericTableEntry,
                      0i64);
                    IoStatusBlockRangeTableLock.Count = 1;
                    IoStatusBlockRangeTableLock.Event.Header.WaitListHead.Blink = &IoStatusBlockRangeTableLock.Event.Header.WaitListHead;
                    IoStatusBlockRangeTableLock.Event.Header.WaitListHead.Flink = &IoStatusBlockRangeTableLock.Event.Header.WaitListHead;
                    IoStatusBlockRangeTableLock.Owner = 0i64;
                    IoStatusBlockRangeTableLock.Contention = 0;
                    LOWORD(IoStatusBlockRangeTableLock.Event.Header.Lock) = 1;
                    IoStatusBlockRangeTableLock.Event.Header.Size = 6;
                    IoStatusBlockRangeTableLock.Event.Header.SignalState = 0;
                    KitpInitAitSampleRate(LoaderBlock);
                    if ( EtwRegister(&MS_Windows_AIT_Provider, 0i64, 0i64, &KitEtwHandle) < 0 )
                      KitEtwHandle = 0i64;
                    KseInitialize(LoaderBlock, 1ui64);
                    if ( HvlPhase2Initialize(LoaderBlock) >= 0 )
                    {
                      v34 = KeQueryActiveProcessorCountEx(0xFFFFu);
                      Context = v34;
                      KeIpiGenericCall((PKIPI_BROADCAST_WORKER)KeOptimizeSpecCtrlSettings, (ULONG_PTR)&Context);
                      VslpIumPhase4Initialize();
                      if ( PnpEtwHandle )
                        EtwWriteStartScenario(
                          PnpEtwHandle,
                          &KMPnPEvt_DriverInitPhase_Start,
                          &PnpDriverInitPhaseActivityId,
                          0i64,
                          0i64);
                      LOWORD(ActiveConnectListLock.Header.Lock) = 1;
                      qword_140C452C8 = (__int64)&ActiveConnectList;
                      ActiveConnectList = (__int64)&ActiveConnectList;
                      ActiveConnectListLock.Header.WaitListHead.Blink = &ActiveConnectListLock.Header.WaitListHead;
                      ActiveConnectListLock.Header.WaitListHead.Flink = &ActiveConnectListLock.Header.WaitListHead;
                      ActiveConnectListLock.Header.Size = 6;
                      ActiveConnectListLock.Header.SignalState = 1;
                      if ( IopInitializePassiveInterruptServices() >= 0 )
                      {
                        SecureDump_PrepareForInit(v15, &Size);
                        if ( ForceDumpDisabled || (_BYTE)Size )
                          CapsuleDumpAllowed = 0;
                        else
                          IopInitDumpCapsuleSupport();
                        if ( (_DWORD)ExLeapSecondDataLastParseResult )
                          EtwTraceLeapSecondDataParseFailure((unsigned int)ExLeapSecondDataLastParseResult);
                        EtwTraceLeapSecondDataUpdate(
                          0i64,
                          *(unsigned __int8 *)ExLeapSecondData,
                          *((unsigned int *)ExLeapSecondData + 1),
                          0i64);
                        IopInitializeIoRate();
                        *(_QWORD *)&PsAltSystemCallRegistrationLock = 0i64;
                        PsAltSystemCallHandlers[0] = (__int64)PsPicoAltSystemCallDispatch;
                        if ( IopInitializeBootDrivers(LoaderBlock, &PreviousDriver) )
                        {
                          if ( IopLoadBootHotPatches() < 0 )
                          {
                            IopInitFailCode = 21;
                          }
                          else
                          {
                            if ( !PoInitSystem(2ui64, LoaderBlock) )
                              KeBugCheck(0xA0u);
                            SmInitSystem(1ui64);
                            EtwInitialize(1ui64);
                            LOBYTE(Size) = 0;
                            if ( VslVsmEnabled )
                            {
                              LODWORD(Depthb) = 1;
                              if ( NtPowerInformation(PlatformInformation, 0i64, 0i64, &Size, Depthb) >= 0 )
                              {
                                if ( (_BYTE)Size )
                                {
                                  ExSubscribeWnfStateChange(
                                    &VslpIumCsWnfSubscription,
                                    &WNF_PO_SCENARIO_CHANGE,
                                    1ui64,
                                    0i64,
                                    (INT64 *)VslpConnectedStandbyWnfCallback,
                                    0i64,
                                    v23,
                                    v24,
                                    Size,
                                    (const _WNF_TYPE_ID *)Tag,
                                    *(PVOID *)ResultLength,
                                    Object);
                                  PoRegisterPowerSettingCallback(
                                    0i64,
                                    &GUID_LOW_POWER_EPOCH,
                                    (PPOWER_SETTING_CALLBACK)VslpConnectedStandbyPoCallback,
                                    0i64,
                                    0i64);
                                  PoRegisterPowerSettingCallback(
                                    0i64,
                                    &GUID_PDC_IDLE_RESILIENCY_ENGAGED,
                                    (PPOWER_SETTING_CALLBACK)VslpConnectedStandbyPoCallback,
                                    0i64,
                                    0i64);
                                }
                              }
                            }
                            IopInitializeSystemVariableService();
                            if ( !ForceDumpDisabled )
                            {
                              EtwRegister(
                                &LiveDumpProvGuid,
                                (PETWENABLECALLBACK)IopLiveDumpTracingControlCallback,
                                0i64,
                                &IopLiveDumpEtwRegHandle);
                              TraceLoggingRegisterEx_EtwRegister_EtwSetInformation(&dword_140C04498);
                            }
                            IopInitializeTriageDumpData();
                            if ( IopInitCrashDumpDuringSysInit(LoaderBlock) >= 0 )
                              IopRemoveDumpCapsuleSupport();
                            if ( !RtlIsStateSeparationEnabled() )
                              PpLastGoodDoBootProcessing();
                            v16 = NtGlobalFlag;
                            NtGlobalFlag |= 0x40000u;
                            SystemDlls = PsLocateSystemDlls();
                            NtGlobalFlag = v16;
                            if ( SystemDlls < 0 )
                            {
                              HeadlessKernelAddLogEntry(0xAui64, 0i64);
                              IopInitFailCode = 7;
                            }
                            else
                            {
                              PfSnBeginBootPhase(0i64);
                              if ( IopReassignSystemRoot(LoaderBlock, &NtDeviceName) )
                              {
                                if ( (unsigned __int8)IopProtectSystemPartition(LoaderBlock) )
                                {
                                  if ( NtVhdBootFile )
                                  {
                                    ObjectAttributes.ObjectName = (_UNICODE_STRING *)(PsLoadedModuleList + 72);
                                    ObjectAttributes.Length = 48;
                                    ObjectAttributes.RootDirectory = 0i64;
                                    ObjectAttributes.Attributes = 576;
                                    *(_OWORD *)&ObjectAttributes.SecurityDescriptor = 0i64;
                                    if ( ZwOpenFile((PHANDLE)&Tag, 0x80000000, &ObjectAttributes, &IoStatusBlock, 1u, 0) >= 0 )
                                    {
                                      Object = 0i64;
                                      if ( ObReferenceObjectByHandle((HANDLE)Tag, 0x80u, 0i64, 0, &Object, 0i64) >= 0 )
                                      {
                                        PpPagePathAssign((_FILE_OBJECT *)Object);
                                        HalPutDmaAdapter((PADAPTER_OBJECT)Object);
                                      }
                                      ZwClose((HANDLE)Tag);
                                    }
                                  }
                                  if ( WMIInitialize(1ui64, 0i64) )
                                  {
                                    WheaInitialize(LoaderBlock, 1ui64);
                                    return 1;
                                  }
                                }
                                else
                                {
                                  HeadlessKernelAddLogEntry(0xDui64, 0i64);
                                  IopInitFailCode = 10;
                                }
                              }
                              else
                              {
                                HeadlessKernelAddLogEntry(0xCui64, 0i64);
                                IopInitFailCode = 9;
                              }
                            }
                          }
                        }
                        else
                        {
                          HeadlessKernelAddLogEntry(9ui64, 0i64);
                          IopInitFailCode = 6;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        HeadlessKernelAddLogEntry(6ui64, 0i64);
        IopInitFailCode = 3;
      }
    }
  }
  else
  {
    IopInitFailCode = 1;
  }
  return 0;
}

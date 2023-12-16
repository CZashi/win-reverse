UINT8 __fastcall PoInitSystem(UINT64 Phase, _LOADER_PARAMETER_BLOCK *LoaderBlock)
{
  int v3; // ebx
  NTSTATUS TimebrokerServiceSid; // eax
  INT64 v6; // r8
  INT64 v7; // r8
  INT64 v8; // r8
  INT64 v9; // r8
  unsigned int v10; // ecx
  _LOADER_PARAMETER_EXTENSION *Extension; // rcx
  UINT64 v12; // rdx
  const wchar_t *v13; // r8
  CHAR *v14; // r9
  UINT64 v15; // rdx
  const wchar_t *v16; // r8
  CHAR *v17; // r9
  int v18; // ebx
  UINT8 v19; // di
  UINT64 v20; // rdx
  __int64 v21; // rdx
  EVENT_DESCRIPTOR *v22; // r8
  _LOADER_PARAMETER_EXTENSION *v23; // rdx
  bool v24; // zf
  UINT64 v25; // [rsp+20h] [rbp-50h]
  PVOID Free; // [rsp+28h] [rbp-48h]
  PVOID v27; // [rsp+30h] [rbp-40h]
  __int64 Buffer; // [rsp+40h] [rbp-30h] BYREF
  _LARGE_INTEGER PerformanceFrequency; // [rsp+48h] [rbp-28h] BYREF
  _ETW_TP_EVENT_TIMER_EXPIRATION_END NumberOfCallbackRegistration; // [rsp+50h] [rbp-20h] BYREF
  EM_RULE_STATE State; // [rsp+B0h] [rbp+40h] BYREF
  EM_RULE_STATE v32; // [rsp+C0h] [rbp+50h] BYREF
  EM_RULE_STATE v33; // [rsp+C8h] [rbp+58h] BYREF

  PopOsInitPhase = Phase;
  PerformanceFrequency.QuadPart = 0i64;
  v3 = Phase;
  memset(&NumberOfCallbackRegistration.Header.ThreadId, 0, 24);
  if ( !(_DWORD)Phase )
  {
    KeQueryPerformanceCounter(&PerformanceFrequency);
    PopQpcFrequency = PerformanceFrequency.QuadPart;
    PopComputeCounterShifts(
      (UINT64 *)PerformanceFrequency.QuadPart,
      &PpmPerformanceDistributionShift,
      (INT64)&PpmPerformanceCounterShift);
    PopComputeCounterShifts(
      (UINT64 *)0x989680,
      &PpmHvPerformanceDistributionShift,
      (INT64)&PpmHvPerformanceCounterShift);
    PopCsResiliencyStatsLock = 0i64;
    PopPowerAggregatorInitialize(0i64);
    qword_140C239E8 = (__int64)&PopIrpList;
    PopIrpList = (__int64)&PopIrpList;
    qword_140C239D8 = (__int64)&PopInrushIrpList;
    PopInrushIrpList = (__int64)&PopInrushIrpList;
    PopPowerEventLock.Thread = 0i64;
    PopPowerEventLock.Lock.Value = 0i64;
    PopSystemIdleLock.Thread = 0i64;
    PopSystemIdleLock.Lock.Value = 0i64;
    qword_140C24328 = 0i64;
    *(_QWORD *)&PopCoalRegistrationListLock = 0i64;
    PopDeepSleepDisengageReasonLock = 0i64;
    PopIrpLock = 0i64;
    ExInitializeNPagedLookasideList(&PopIrpDataLookaside, 0i64, 0i64, 0x200u, 0x100u, 0x72496F50u, 0);
    *(_QWORD *)&BootStatFileHandle = 0i64;
    BootStatFileHandleAcquired = 0;
    BootStatKeepHandleOpen = 0;
    BootStatDataCache = 0i64;
    BootStatDisableFlush = 0;
    PopBsdSkipLogging = 0;
    PopBsdUpdateLock.Thread = 0i64;
    PopBsdUpdateLock.Lock.Value = 0i64;
    PopInitializeWorkItem((INT64)&PopSetUserShutdownMarkerWorkItem, (INT64)PopSetUserShutdownMarkerWorker, 0i64);
    PopInitializeWorkItem((INT64)&PopClearUserShutdownMarkerWorkItem, (INT64)PopClearUserShutdownMarkerWorker, v6);
    PopInitializeWorkItem((INT64)&PopBsdUpdateWorkItem, (INT64)PopBsdUpdateWorker, v7);
    PopWdiCurrentScenarioInstanceId = 0i64;
    PopWdiCurrentScenario = (__int64)&NullGuid;
    PopInitializeWorkItem((INT64)&PopExternalMonitorUpdatedWorkItem, (INT64)PopExternalMonitorUpdatedWorker, v8);
    PopInitializeWorkItem((INT64)&PopRecordLidStateWorkItem, (INT64)PopRecordLidStateWorker, v9);
    PopInputSuppressionLock.Thread = 0i64;
    qword_140C24E68 = (__int64)&PopTransitionCheckpoints;
    PopTransitionCheckpoints = &PopTransitionCheckpoints;
    PopInputSuppressionLock.Lock.Value = 0i64;
    PopTransitionCheckpointLock.Thread = 0i64;
    PopTransitionCheckpointLock.Lock.Value = 0i64;
    PopMonitorOffDueToSleep = 0;
    PpmHeteroInitializeHgsSupport();
    PpmCheckCurrentPipelineId = 6;
    PpmCheckDpc.DeferredRoutine = (void (__fastcall *)(_KDPC *, void *, void *, void *))PpmCheckRun;
    PpmCheckDpc.TargetInfoAsUlong = 787;
    PpmCheckDpc.DeferredContext = 0i64;
    PpmCheckDpc.DpcData = 0i64;
    PpmCheckDpc.ProcessorHistory = 0i64;
    PpmCheckStartDpc.TargetInfoAsUlong = 787;
    PpmCheckStartDpc.DeferredRoutine = (void (__fastcall *)(_KDPC *, void *, void *, void *))PpmCheckPeriodicStart;
    PpmCheckStartDpc.DeferredContext = 0i64;
    PpmCheckStartDpc.DpcData = 0i64;
    PpmCheckStartDpc.ProcessorHistory = 0i64;
    TimebrokerServiceSid = PopInitializeIrpWorkers();
    if ( TimebrokerServiceSid < 0 )
      return TimebrokerServiceSid >= 0;
    PopIrpSerialLock = 0i64;
    qword_140C23A58 = (__int64)&qword_140C23A50;
    qword_140C23A50 = (__int64)&qword_140C23A50;
    qword_140C23A28 = (__int64)&PopIrpSerialList;
    PopIrpSerialList = (__int64)&PopIrpSerialList;
    qword_140C23A78 = (__int64)&PopRequestedIrps;
    PopRequestedIrps = (__int64)&PopRequestedIrps;
    PopTransitionLock.Header.WaitListHead.Blink = &PopTransitionLock.Header.WaitListHead;
    PopTransitionLock.Header.WaitListHead.Flink = &PopTransitionLock.Header.WaitListHead;
    qword_140C23A88 = (__int64)&PowerStateDisableReasonListHead;
    PowerStateDisableReasonListHead = (__int64)&PowerStateDisableReasonListHead;
    PopDisableSleepMutex.Event.Header.WaitListHead.Blink = &PopDisableSleepMutex.Event.Header.WaitListHead;
    PopDisableSleepMutex.Event.Header.WaitListHead.Flink = &PopDisableSleepMutex.Event.Header.WaitListHead;
    qword_140C24998 = (__int64)&PopDisableSleepList;
    PopDisableSleepList = (__int64)&PopDisableSleepList;
    qword_140C23A08 = 0i64;
    *(_QWORD *)&PpmIdlePolicyLock = 0i64;
    PpmIdleVetoLock = 0i64;
    PpmParkStateLock = 0i64;
    qword_140C4FDC8 = 0i64;
    word_140C23A48 = 1;
    byte_140C23A4A = 6;
    dword_140C23A4C = 1;
    PopWorkerLock = 0i64;
    LOWORD(PopTransitionLock.Header.Lock) = 1;
    PopTransitionLock.Header.Size = 6;
    PopTransitionLock.Header.SignalState = 1;
    PopDisableSleepMutex.Count = 1;
    PopDisableSleepMutex.Owner = 0i64;
    PopDisableSleepMutex.Contention = 0;
    LOWORD(PopDisableSleepMutex.Event.Header.Lock) = 1;
    PopDisableSleepMutex.Event.Header.Size = 6;
    PopDisableSleepMutex.Event.Header.SignalState = 0;
    PopInitShutdownList();
    v10 = PopIdleScanInterval;
    qword_140C23AB8 = (__int64)&PopIdleDetectList;
    PopIdleDetectList = (__int64)&PopIdleDetectList;
    PopDopeGlobalLock = 0i64;
    if ( PopIdleScanInterval )
    {
      if ( PopIdleScanInterval == -1 )
      {
        v10 = 30;
        PopIdleScanInterval = 30;
      }
      else if ( (unsigned int)PopIdleScanInterval > 0x12C )
      {
        v10 = 300;
        PopIdleScanInterval = 300;
      }
      PopIdleBackgroundIgnoreCount = (v10 + 59) / v10;
      PopBackgroundTaskIgnoreCount = (v10 + 179) / v10;
    }
    PopWorkerSpinLock = 0i64;
    PopPolicyWorker.WorkerRoutine = (void (__fastcall *)(void *))PopPolicyWorkerThread;
    PopPolicyWorker.List.Flink = 0i64;
    PopPolicyWorker.Parameter = (void *)0x80000000i64;
    PopWorkerStatus = -1;
    ExInitializeResourceLite(&PopPolicyLock);
    *(_QWORD *)&PopAwaymodeLock = 0i64;
    PopVolumeLock.Event.Header.WaitListHead.Blink = &PopVolumeLock.Event.Header.WaitListHead;
    PopVolumeLock.Event.Header.WaitListHead.Flink = &PopVolumeLock.Event.Header.WaitListHead;
    PopVolumeLock.Count = 1;
    PopPowerSettingCallbackReturned.Header.WaitListHead.Blink = &PopPowerSettingCallbackReturned.Header.WaitListHead;
    PopPowerSettingCallbackReturned.Header.WaitListHead.Flink = &PopPowerSettingCallbackReturned.Header.WaitListHead;
    qword_140C23B68 = (__int64)&PopVolumeDevices;
    PopVolumeDevices = (__int64)&PopVolumeDevices;
    qword_140C23BF8 = (__int64)&PopSwitches;
    PopSwitches = (__int64)&PopSwitches;
    qword_140C23BE8 = (__int64)&PopFans;
    PopFans = (__int64)&PopFans;
    PopVolumeLock.Owner = 0i64;
    PopVolumeLock.Contention = 0;
    LOWORD(PopVolumeLock.Event.Header.Lock) = 1;
    PopVolumeLock.Event.Header.Size = 6;
    PopVolumeLock.Event.Header.SignalState = 0;
    LOWORD(PopPowerSettingCallbackReturned.Header.Lock) = 0;
    PopPowerSettingCallbackReturned.Header.Size = 6;
    PopPowerSettingCallbackReturned.Header.SignalState = 0;
    qword_140C23BD8 = (__int64)&PopThermal;
    PopThermal = (INT64)&PopThermal;
    IoAddTriageDumpDataBlock(&PopThermal, 0x10ui64);
    qword_140C23BC8 = (__int64)&PopActionWaiters;
    PopActionWaiters = (__int64)&PopActionWaiters;
    PopResetActionDefaults();
    PopPolicy = &Policy;
    PopDefaultPolicy(&Policy);
    LODWORD(PopAdminPolicy) = 2;
    *(_QWORD *)((char *)&PopAdminPolicy + 4) = 5i64;
    HIDWORD(PopAdminPolicy) = -1;
    qword_140C23C10 = 0xFFFFFFFF00000000ui64;
    PopFullWake = 1;
    PopCoolingMode = 0;
    PlatformIdleStateIndex = 0x2FFFFFFFFi64;
    PpmInitPolicyConfiguration();
    PpmInitIdlePolicy();
    PpmPerfInitialize();
    PpmInitCoreParkingPolicy();
    PpmInitHeteroPolicy();
    PpmIdleRegisterDefaultStates();
    PopDeepSleepInitialize(0i64);
    PopInitializePowerSettings();
    PopInitilizeAcDcSettings();
    qword_140C22D68 = 0i64;
    PopPolicyDeviceLock = 0i64;
    PopBatteryInit();
    PopFanLock.Thread = 0i64;
    PopFanLock.Lock.Value = 0i64;
    PopThermalInit();
    PopCoolingExtensionLock.Thread = 0i64;
    qword_140C23098 = (__int64)&PopCoolingExtensionList;
    PopCoolingExtensionList = (_POP_COOLING_EXTENSION *)&PopCoolingExtensionList;
    qword_140C23DE8 = (__int64)PopShutdownHandler;
    PopCoolingExtensionLock.Lock.Value = 0i64;
    dword_140C23DE0 = 4;
    byte_140C23DE4 = 0;
    PopWakeSourceInit();
    *(_QWORD *)&PpmWmiIdleAccountingTimer.Header.Lock = 8i64;
    PpmWmiIdleAccountingTimer.Header.WaitListHead.Blink = &PpmWmiIdleAccountingTimer.Header.WaitListHead;
    PpmWmiIdleAccountingTimer.Header.WaitListHead.Flink = &PpmWmiIdleAccountingTimer.Header.WaitListHead;
    PpmWmiIdleAccountingDpc.DeferredRoutine = (void (__fastcall *)(_KDPC *, void *, void *, void *))PpmWmiIdleAccountingProcedure;
    PopAwayModeUserPresenceTimer.Header.WaitListHead.Blink = &PopAwayModeUserPresenceTimer.Header.WaitListHead;
    PopAwayModeUserPresenceTimer.Header.WaitListHead.Flink = &PopAwayModeUserPresenceTimer.Header.WaitListHead;
    PopUserPresentCompletedEvent.Header.WaitListHead.Blink = &PopUserPresentCompletedEvent.Header.WaitListHead;
    PopUserPresentCompletedEvent.Header.WaitListHead.Flink = &PopUserPresentCompletedEvent.Header.WaitListHead;
    *(_QWORD *)&PopAwayModeUserPresenceTimer.Header.Lock = 8i64;
    PopFxSystemLatencyLock.Event.Header.WaitListHead.Blink = &PopFxSystemLatencyLock.Event.Header.WaitListHead;
    PopFxSystemLatencyLock.Event.Header.WaitListHead.Flink = &PopFxSystemLatencyLock.Event.Header.WaitListHead;
    PpmWmiIdleAccountingTimer.DueTime.QuadPart = 0i64;
    PpmWmiIdleAccountingTimer.Period = 0;
    PpmWmiIdleAccountingTimer.Processor = 0;
    PpmWmiIdleAccountingDpc.TargetInfoAsUlong = 275;
    PpmWmiIdleAccountingDpc.DeferredContext = 0i64;
    PpmWmiIdleAccountingDpc.DpcData = 0i64;
    PpmWmiIdleAccountingDpc.ProcessorHistory = 0i64;
    PopUserPresentSetStatus = 0;
    PopAwayModeUserPresenceTimer.DueTime.QuadPart = 0i64;
    PopAwayModeUserPresenceTimer.Period = 0;
    PopAwayModeUserPresenceTimer.Processor = 0;
    LOWORD(PopUserPresentCompletedEvent.Header.Lock) = 1;
    PopUserPresentCompletedEvent.Header.Size = 6;
    PopUserPresentCompletedEvent.Header.SignalState = 0;
    LOWORD(PopFxSystemLatencyLock.Event.Header.Lock) = 1;
    PopFxSystemLatencyLock.Event.Header.Size = 6;
    PopFxSystemLatencyLock.Event.Header.SignalState = 1;
    PoFxInitPowerManagement();
    dword_140C23D2C = 0;
    qword_140C23D30 = 100i64;
    qword_140C23D38 = 100i64;
    dword_140C23D40 = 100;
    PopNetInitialize(0i64);
    PopInitializePowerButtonHold(0i64);
    PopRecorderInit();
    Extension = LoaderBlock->Extension;
    LOBYTE(PopFirmwareResetReason) = Extension->ResetReason.Supplied;
    if ( Extension->ResetReason.Supplied )
    {
      *((_QWORD *)&PopFirmwareResetReason + 1) = Extension->ResetReason.Basic.AsULONG64;
      xmmword_140C540C0 = *(_OWORD *)Extension->ResetReason.AdditionalInfo;
      xmmword_140C540D0 = *(_OWORD *)&Extension->ResetReason.AdditionalInfo[4];
    }
    TimebrokerServiceSid = PopCreateTimebrokerServiceSid();
    if ( TimebrokerServiceSid < 0 )
      return TimebrokerServiceSid >= 0;
    PopInitializeDirectedDrips(0i64);
    SshInitialize(0i64);
  }
  if ( v3 != 1 )
    goto LABEL_3;
  PopPowerAggregatorInitialize(1i64);
  if ( HviIsAnyHypervisorPresent() )
  {
    PpmExitLatencyCheckEnabled = 0;
    PpmExitLatencySamplingPercentage = 0;
  }
  if ( (unsigned int)PopAggressiveStandbyActionsRegValue < 4 )
    PopAggressiveStandbyEnabledActions = PopAggressiveStandbyActionsRegValue;
  PopUmpoInitializeChannel();
  PopUmpoInitializeMonitorChannel();
  *(_QWORD *)&PopPdcDeviceListLock = 0i64;
  PopEsInit();
  PopInitializePowerSettingCallbacks();
  TimebrokerServiceSid = PopEtInit();
  if ( TimebrokerServiceSid >= 0 )
  {
    TimebrokerServiceSid = PopPowerRequestInit();
    if ( TimebrokerServiceSid >= 0 )
    {
      TimebrokerServiceSid = PopInitializeHighPerfPowerRequest();
      if ( TimebrokerServiceSid >= 0 )
      {
        PopCheckPowerSourceAfterRtcWakeInitialize();
        PopWatchdogInit();
        PopInitializePowerButtonHold(1i64);
        TimebrokerServiceSid = PpmInitHeteroEngine();
        if ( TimebrokerServiceSid >= 0 )
        {
          PopInitDripsWakeAccounting();
          LODWORD(v25) = 2;
          TimebrokerServiceSid = EmpProviderRegister(
                                   0i64,
                                   (const _EM_ENTRY_REGISTRATION *)&PopEmEntry,
                                   1ui64,
                                   (const _EM_CALLBACK_REGISTRATION *)&PopEmCallback,
                                   v25,
                                   (VOID **)&NumberOfCallbackRegistration);
          if ( TimebrokerServiceSid >= 0 )
          {
            State = STATE_UNKNOWN;
            PopErrataDisablePrimaryDeviceFastResume = 0;
            EmClientQueryRuleState(&GUID_EM_RULE_DISABLE_DEVICE_FAST_RESUME, &State);
            if ( State != STATE_TRUE )
            {
LABEL_5:
              TimebrokerServiceSid = 0;
              return TimebrokerServiceSid >= 0;
            }
            PopErrataDisablePrimaryDeviceFastResume = 1;
LABEL_3:
            if ( v3 == 2 )
            {
              PoFxRegisterDebugger();
              HalReportResourceUsage(1ui64);
              PopBatteryInitPhaseTwo();
              TimebrokerServiceSid = EtwRegister(
                                       &PPM_ETW_PROVIDER,
                                       (PETWENABLECALLBACK)PpmEventTraceControlCallback,
                                       0i64,
                                       &PpmEtwHandle);
              if ( TimebrokerServiceSid < 0 )
                return TimebrokerServiceSid >= 0;
              PpmEtwRegistered = 1;
              KeRegisterProcessorChangeCallback((PPROCESSOR_CALLBACK_FUNCTION)PopNewProcessorCallback, 0i64, 0);
              PpmAcquireLock((_PPM_LOCK *)&PpmPerfPolicyLock);
              PopInitializeHeteroProcessors();
              PpmReleaseLock(&PpmPerfPolicyLock, v12, v13, v14);
              if ( PpmPerfArtificialDomainSetting != -1 )
                PpmPerfArtificialDomainEnabled = PpmPerfArtificialDomainSetting != 0;
              PpmIdleRegisterDefaultStates();
              PpmCheckInitProcessors(0i64);
              PpmAcquireLock(&PopFxSystemLatencyLock);
              PoFxSendSystemLatencyUpdate();
              PpmReleaseLock((wchar_t *)&PopFxSystemLatencyLock, v15, v16, v17);
              PopPdcCsCheckSystemVolumeDevice();
              PopUpdateBackgroundCoolingStatus(0);
              PopInitVideoWnfState();
            }
            if ( v3 != 3 )
              goto LABEL_5;
            TimebrokerServiceSid = PopDiagInitialize();
            if ( TimebrokerServiceSid < 0 )
              return TimebrokerServiceSid >= 0;
            SshInitialize(3i64);
            PopTriggerDiagTraceAoAcCapability();
            PopFanReportBootStartDevices();
            v18 = 2;
            v19 = 1;
            if ( PopSkipTickPolicy )
            {
              if ( PopSkipTickPolicy == 1 )
              {
                v19 = 0;
                if ( HalGetInterruptTargetInformation(
                       InterruptTargetTypeGlobal,
                       0i64,
                       (_HAL_INTERRUPT_TARGET_INFORMATION *)&NumberOfCallbackRegistration.Header.ThreadId) >= 0 )
                {
                  PopApicMode = NumberOfCallbackRegistration.Header.UserTime;
                  if ( PopCheckSkipTick() )
                  {
                    PoSkipTickMode = 0;
LABEL_37:
                    PpmInitIllegalThrottleLogging();
                    PopProcessBootstat(LoaderBlock);
                    if ( (unsigned __int8)off_140C008D0[0]()
                      || (unsigned int)(PoOffCrashConfigTable - 1) <= 1 && *(&PoOffCrashConfigTable + 1) )
                    {
                      PopDiagTraceAbnormalReset(*(&PoOffCrashConfigTable + 1));
                    }
                    PopIdleWakeInitialize();
                    PopAcquirePolicyLock();
                    PopUpdateUpgradeInProgress(0);
                    if ( InitIsWinPEMode )
                      PopLogSleepDisabled(0x10ui64, 0xFui64, 0i64, 0i64);
                    if ( PopCapabilities.AoAc )
                      PopLogSleepDisabled(0x11ui64, 7ui64, 0i64, 0i64);
                    v20 = 0i64;
                    if ( (LoaderBlock->Extension->BootFlags & 8) != 0 )
                    {
                      PopSecureLaunched = 1;
                      v20 = 4i64;
                    }
                    if ( (HvlpFlags & 2) == 0 && VslVsmEnabled )
                      v20 = 31i64;
                    if ( (_DWORD)v20 )
                      PopLogSleepDisabled(0x15ui64, v20, 0i64, 0i64);
                    PopDeepSleepInitialize(3ui64);
                    PopInitializePowerPolicySimulate();
                    if ( (PopSimulate & 1) != 0 )
                    {
                      PopCapabilities.SystemBatteriesPresent = 1;
                      PopCapabilities.BatteryScale[0].Granularity = 100;
                      PopCapabilities.BatteryScale[0].Capacity = 400;
                      PopCapabilities.BatteryScale[1].Granularity = 10;
                      PopCapabilities.BatteryScale[1].Capacity = 0xFFFF;
                      PopCapabilities.RtcWake = PowerSystemSleeping3;
                      PopCapabilities.DefaultLowLatencyWake = PowerSystemSleeping1;
                    }
                    if ( (PopSimulate & 2) != 0 )
                    {
                      *(_DWORD *)&PopCapabilities.PowerButtonPresent = 16843009;
                      *(_WORD *)&PopCapabilities.SystemS2 = 257;
                      PopCapabilities.SystemS4 = 1;
                      *(_WORD *)&PopCapabilities.FastSystemS4 = 257;
                    }
                    PopResetCurrentPolicies();
                    PopInitializeAdpm();
                    PopEsInit();
                    PopInitilizeAcDcSettings();
                    LODWORD(Buffer) = 1;
                    PopUpdateConsoleDisplayState(1, v21, v22);
                    LODWORD(v27) = 0;
                    LODWORD(Free) = 0;
                    ZwUpdateWnfStateData(
                      (_WNF_STATE_NAME *)&WNF_PO_PRIMARY_DISPLAY_VISIBLE_STATE,
                      &Buffer,
                      4ui64,
                      0i64,
                      0i64,
                      (UINT64)Free,
                      (UINT64)v27);
                    PopNetInitialize(3ui64);
                    PopReleasePolicyLock();
                    PopIdleInitAoAcDozeS4Timer();
                    PopCreateIdlePhaseWatchdog();
                    PopInitializeSystemIdleDetection();
                    PopInitializePreSleepNotifications();
                    v23 = LoaderBlock->Extension;
                    PopHiberLoaderScratchPages = v23->ResumePages;
                    PopHiberResumeXhciHandoffSkip = (*((_DWORD *)v23 + 33) & 0x10000000) != 0;
                    PopSetupHighPerfPowerRequest();
                    PpmEnableWmiInterface();
                    PopAcquirePolicyLock();
                    PopCoalescingInitialize();
                    PopReleasePolicyLock();
                    PopInitializeDirectedDrips(3i64);
                    ExInitializeResourceLite(&PopDripsWatchdogContext);
                    if ( PopPlatformAoAc )
                    {
                      if ( PopDripsWatchdogInitializeActions() < 0
                        || PopDripsWatchdogInitializeCallbackTimer() < 0
                        || PopDripsWatchdogInitializeDiagnosticTimer() < 0 )
                      {
                        goto LABEL_56;
                      }
                      dword_140C21228 |= 2u;
                    }
                    dword_140C21228 |= 1u;
LABEL_56:
                    PopSetupAudioEventNotification();
                    PopSetupMixedRealitytNotification();
                    PopSetupFullScrenVideoNotification();
                    PopSetupUserPresencePredictionNotification();
                    PopSetupSprActiveSessionChangeNotification();
                    PopSetupAirplaneModeNotification();
                    PopSetupBluetoothChargingNotification();
                    PopSetupMobileHotspotNotification();
                    PopThermalHandlePreviousShutdown();
                    PopCheckpointEfiRuntimeRedirected = (*(_DWORD *)&LoaderBlock->FirmwareInformation & 2) != 0;
                    TtmInit();
                    if ( PopPlatformAoAc )
                    {
                      v32 = STATE_UNKNOWN;
                      EmClientQueryRuleState(&EM_RULE_IGNORE_INCORRECT_LID_NOTIFICATIONS, &v32);
                      if ( v32 == STATE_TRUE )
                        PopErrataReportingIncorrectLidState = 1;
                      if ( PopPlatformAoAc )
                      {
                        if ( PopLidStateForInputSuppressionOverride != -1 )
                          PopIgnoreLidStateForInputSuppression = PopLidStateForInputSuppressionOverride != 0;
                        v33 = STATE_UNKNOWN;
                        EmClientQueryRuleState(&GUID_EM_RULE_ALLOW_INPUT_SUPPRESSION_NOTIFICATION, &v33);
                        PopEnableInputSuppression = v33 == STATE_TRUE;
                        if ( v33 != STATE_TRUE && PopEnableInputSuppressionOverride != -1 )
                          PopEnableInputSuppression = PopEnableInputSuppressionOverride != 0;
                      }
                    }
                    PopBatteryQueueWork(1i64);
                    PopSetupKsrCallbacks();
                    PopHiberEvaluateSkippingMemoryMapValidation();
                    PopReadErrataSkipMemoryOverwriteRequestControlLockAction();
                    goto LABEL_5;
                  }
                  v18 = 1;
                }
              }
              else
              {
                v18 = 0;
              }
            }
            PoSkipTickMode = v18;
            v24 = v18 == 2;
            if ( v18 != 2 )
            {
              if ( !v19 )
                goto LABEL_37;
              v24 = v18 == 2;
            }
            PopDiagTraceSkipTick(v24, v19);
            goto LABEL_37;
          }
        }
      }
    }
  }
  return TimebrokerServiceSid >= 0;
}

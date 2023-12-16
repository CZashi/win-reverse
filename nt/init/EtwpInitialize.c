VOID __fastcall EtwpInitialize(UINT64 Phase)
{
  ULONG_PTR v1; // esi
  NTSTATUS v2; // eax
  _WORD *v3; // rdi
  __int64 i; // rcx
  ULONG_PTR j; // edi
  _KPRCB *Prcb; // rax
  NTSTATUS v7; // eax
  UINT64 v8; // rdx
  __int64 v9; // rcx
  __int64 v10; // rax
  UINT64 MatchingChangeStamp; // [rsp+28h] [rbp-41h]
  UINT64 CheckStamp; // [rsp+30h] [rbp-39h]
  __int64 v13; // [rsp+40h] [rbp-29h] BYREF
  _UNICODE_STRING DestinationString; // [rsp+48h] [rbp-21h] BYREF
  INT64 v15[2]; // [rsp+58h] [rbp-11h] BYREF
  __int64 v16; // [rsp+68h] [rbp-1h]
  _OBJECT_ATTRIBUTES ObjectAttributes; // [rsp+70h] [rbp+7h] BYREF
  int v18; // [rsp+D8h] [rbp+6Fh] BYREF
  _LARGE_INTEGER BootTime; // [rsp+E0h] [rbp+77h] BYREF
  UINT64 BootTimeBias; // [rsp+E8h] [rbp+7Fh] BYREF

  v1 = KeNumberProcessors_0;
  BootTime.QuadPart = 0i64;
  BootTimeBias = 0i64;
  v16 = 0i64;
  *(_OWORD *)v15 = 0i64;
  if ( (_DWORD)Phase )
  {
    if ( (_DWORD)Phase == 1 )
      EtwpUpdateFileInfoDriverState(&PerfGlobalGroupMask, &PerfGlobalGroupMask, 1ui64, EtwpHostSiloState);
  }
  else
  {
    KeQueryBootTimeValues(&EtwpRefTimeSystem, &BootTime, &BootTimeBias);
    EtwpBootTime = BootTime.QuadPart - BootTimeBias;
    RtlGetMultiTimePrecise((INT64)v15);
    EtwpRefQpcDelta = 0i64;
    LODWORD(v10) = KeQueryPerformanceCounter(0i64);
    EtwpRefTimePerfCounter = v10;
    EtwpRefTimeCycle = __rdtsc();
    v2 = EtwpInitializeSecurity();
    if ( v2 < 0 )
      KeBugCheckEx(0x11Du, 1u, v2, 0, 0);
    v3 = (_WORD *)(&KUSER_SHARED_DATA + 896);
    for ( i = 9i64; i; --i )
      *v3++ = 0;
    for ( j = 0; j < v1; ++j )
    {
      Prcb = KeGetPrcb(j);
      v7 = EtwInitializeProcessor(Prcb);
      if ( v7 < 0 )
        KeBugCheckEx(0x11Du, 2u, v7, j, 0);
    }
    KeInitializeMutex(&EtwpGroupMaskMutex, 0);
    KeInitializeMutex(&EtwpCrimsonMaskMutex, 0);
    *(_QWORD *)&EtwpSecurityLock = 0i64;
    EtwpInitializeStackLookasideList();
    EtwpReadConfigParameters();
    EtwpInitializeRegistration();
    EtwpInitializePrivateSessionDemuxObject();
    EtwpInitializeRealTimeConnection();
    EtwCPUSpeedInMHz = KeGetPrcb(0i64)->MHz;
    KeQueryPerformanceCounter(&EtwPerfFreq);
    EtwpInitializeLastBranchTracing();
    EtwpInitializeProcessorTrace(v9, v8);
    dword_140C19690 = 0;
    EtwpAdjustBuffersWorkItem.WorkerRoutine = (void (__fastcall *)(void *))EtwpAdjustTraceBuffers;
    EtwpMdlTable = 0;
    qword_140C19688 = 0i64;
    EtwpAdjustBuffersWorkItem.Parameter = &EtwpBufferAdjustmentActive;
    dword_140C19684 = 12;
    EtwpBufferAdjustmentCount = 8;
    EtwpAdjustBuffersWorkItem.List.Flink = 0i64;
    KeInitializeTimer2((__int64)&EtwpMemInfoTimer, (__int64)EtwpLogMemInfoTimerCallback, 0i64, 8);
    EtwpInitializeProviderTraits();
    if ( !ExRegisterCallback(ExCbPowerState, EtwpPowerStateCallback, 0i64) )
      goto LABEL_22;
    v13 = 0i64;
    *(&ObjectAttributes.Length + 1) = 0;
    DestinationString = 0i64;
    *(&ObjectAttributes.Attributes + 1) = 0;
    if ( (int)KsrGetFirmwareInformation(&v13) >= 0 )
    {
      RtlInitUnicodeString(&DestinationString, L"\\Callback\\SoftRestart");
      ObjectAttributes.Length = 48;
      ObjectAttributes.ObjectName = &DestinationString;
      ObjectAttributes.RootDirectory = 0i64;
      ObjectAttributes.Attributes = 80;
      *(_OWORD *)&ObjectAttributes.SecurityDescriptor = 0i64;
      if ( ExCreateCallback(&EtwpKsrCallbackObject, &ObjectAttributes, 0, 1u) >= 0 )
        ExRegisterCallback(EtwpKsrCallbackObject, (PCALLBACK_FUNCTION)EtwpKsrCallback, 0i64);
    }
    EtwpLoadMicroarchitecturalPmcs();
    EtwpInitializeSiloAllowedGroupMask();
    if ( EtwInitializeSiloState(0i64) < 0 )
LABEL_22:
      KeBugCheck(0x11Du);
    *(&EtwpBugCheckCallback.State + 4) = 0;
    KeRegisterBugCheckReasonCallback(
      &EtwpBugCheckCallback,
      (PKBUGCHECK_REASON_CALLBACK_ROUTINE)EtwpBugCheckMultiPartCallback,
      KbCallbackSecondaryMultiPartDumpData,
      (PUCHAR)&EtwpComponentName);
    EtwRegister(
      &EventTracingProvGuid,
      (PETWENABLECALLBACK)EtwpTracingProvEnableCallback,
      0i64,
      &EtwpEventTracingProvRegHandle);
    WdipSemInitialize();
    PerfDiagInitialize();
    EtwpInitializeCoverage();
    EtwpInitializeCoverageSampler();
    EtwRegister(&KernelProvGuid, (PETWENABLECALLBACK)EtwpKernelProvEnableCallback, 0i64, &EtwKernelProvRegHandle);
    TlgRegisterAggregateProvider((UINT64 *)&dword_140C02BB0);
    EtwRegister(&PsProvGuid, (PETWENABLECALLBACK)EtwpCrimsonProvEnableCallback, (PVOID)1, &EtwpPsProvRegHandle);
    TlgRegisterAggregateProviderEx(
      (TraceLoggingHProvider)&dword_140C02B78,
      (TLG_PENABLECALLBACK)EtwpTraceLoggingProvEnableCallback,
      PsProvTraceLoggingGuid);
    EtwRegister(&NetProvGuid, (PETWENABLECALLBACK)EtwpCrimsonProvEnableCallback, (PVOID)0x10000, &EtwpNetProvRegHandle);
    EtwRegister(&DiskProvGuid, (PETWENABLECALLBACK)EtwpCrimsonProvEnableCallback, (PVOID)0x100, &EtwpDiskProvRegHandle);
    EtwRegister(
      &FileProvGuid,
      (PETWENABLECALLBACK)EtwpCrimsonProvEnableCallback,
      (PVOID)0x2000000,
      &EtwpFileProvRegHandle);
    EtwRegister(&RegistryProvGuid, (PETWENABLECALLBACK)EtwpRegTraceEnableCallback, 0i64, &EtwpRegTraceHandle);
    EtwRegister(
      &MemoryProvGuid,
      (PETWENABLECALLBACK)EtwpCrimsonProvEnableCallback,
      (PVOID)0x20000001,
      &EtwpMemoryProvRegHandle);
    EtwRegister(&MS_Windows_Kernel_AppCompat_Provider, 0i64, 0i64, &EtwAppCompatProvRegHandle);
    EtwRegister(&KernelAuditApiCallsGuid, 0i64, 0i64, &EtwApiCallsProvRegHandle);
    EtwRegister(&CVEAuditProviderGuid, 0i64, 0i64, &EtwCVEAuditProvRegHandle);
    EtwRegister(&ThreatIntProviderGuid, 0i64, 0i64, &EtwThreatIntProvRegHandle);
    EtwRegister(&MS_Windows_Security_LPAC_Provider, 0i64, 0i64, &EtwLpacProvRegHandle);
    EtwRegister(&MS_Windows_Security_Adminless_Provider, 0i64, 0i64, &EtwAdminlessProvRegHandle);
    EtwRegister(&SecurityMitigationsProviderGuid, 0i64, 0i64, &EtwSecurityMitigationsRegHandle);
    LODWORD(CheckStamp) = 0;
    LODWORD(MatchingChangeStamp) = 0;
    EtwpInitialized = 1;
    ZwUpdateWnfStateData(
      (_WNF_STATE_NAME *)&WNF_ETW_SUBSYSTEM_INITIALIZED,
      0i64,
      0i64,
      0i64,
      0i64,
      MatchingChangeStamp,
      CheckStamp);
    EtwpTraceSystemInitialization();
    v18 = 0;
    if ( ((int (__fastcall *)(__int64, __int64, int *, int *))off_140C00A68[0])(44i64, 4i64, &EtwpMaxPmcCounter, &v18) < 0 )
      EtwpMaxPmcCounter = 8;
    EtwpMaxProfilingSources = EtwpMaxPmcCounter;
  }
}

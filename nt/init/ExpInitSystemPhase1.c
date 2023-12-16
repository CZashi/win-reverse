CHAR __stdcall ExpInitSystemPhase1()
{
  char v0; // di
  unsigned int v1; // ebx
  char v2; // bl
  char v3; // di
  char v4; // bl
  char v5; // di
  char v6; // bl
  char v7; // di
  PVOID v8; // r9
  void *v9; // r9
  char v10; // al
  char v11; // bl
  bool v12; // al
  char v13; // bl
  _OWORD *PoolWithTag; // rax
  char v15; // al
  char v16; // bl
  CHAR v17; // di
  int v18; // eax
  UINT64 v19; // rdx
  UINT64 v20; // rdx
  UINT64 *ReturnedProductType; // [rsp+20h] [rbp-29h]
  UINT64 *ReturnedProductTypea; // [rsp+20h] [rbp-29h]
  int v24[2]; // [rsp+40h] [rbp-9h] BYREF
  __int64 v25; // [rsp+48h] [rbp-1h]
  __int64 v26; // [rsp+50h] [rbp+7h]
  VOID (__stdcall *v27)(INT64, _EX_RUNDOWN_REF **); // [rsp+58h] [rbp+Fh]
  _EX_HOST **v28; // [rsp+60h] [rbp+17h]
  int RegistrationInfo[2]; // [rsp+68h] [rbp+1Fh] BYREF
  __int64 v30; // [rsp+70h] [rbp+27h]
  __int64 v31; // [rsp+78h] [rbp+2Fh]
  VOID (__stdcall *v32)(_EX_HOST_CALLBACK_REASON, VOID *); // [rsp+80h] [rbp+37h]
  __int64 v33; // [rsp+88h] [rbp+3Fh]
  UINT64 v34; // [rsp+B0h] [rbp+67h] BYREF

  ExpSpinCycleCount = 0;
  if ( KeQueryMaximumProcessorCountEx(0xFFFFu) > 1 )
    ExpSpinCycleCount = 10240;
  *(_QWORD *)&ExpHostListLock = 0i64;
  qword_140D2DBD8 = (__int64)&ExpHostList;
  ExpHostList = (__int64)&ExpHostList;
  *(_QWORD *)&ExpKeyManipLock = 0i64;
  ExpSysDbgLock.0 = 0i64;
  *(_QWORD *)&ExpPlatformBinaryLock = 0i64;
  v0 = 1;
  v1 = 0;
  if ( ExpWorkerInitialization() < 0 )
    v0 = 0;
  if ( (_DWORD)KeNumberProcessors_0 )
  {
    do
      ExInitializeProcessor(*(&KiProcessorBlock + v1++), 0);
    while ( v1 < (unsigned int)KeNumberProcessors_0 );
  }
  v2 = ExpEventInitialization() ? v0 : 0;
  v3 = ExpMutantInitialization() ? v2 : 0;
  v4 = (unsigned __int8)ExpAeThresholdInitialization() != 0 ? v3 : 0;
  v5 = ExpInitializeCallbacks() != 0 ? v4 : 0;
  v6 = ExpSemaphoreInitialization() ? v5 : 0;
  v7 = ExpTimerInitialization() != 0 ? v6 : 0;
  ExpHpGCTimerPaged = (__int64)ExAllocateTimer(ExpHpGCTimerCallback, 0i64, (PVOID)8, v8, (UINT64)ReturnedProductType);
  if ( ExpHpGCTimerPaged
    && (ExpHpGCTimerNonPaged = (_EX_TIMER *)ExAllocateTimer(
                                              ExpHpGCTimerCallback,
                                              (_EX_TIMER *)1,
                                              (PVOID)8,
                                              v9,
                                              (UINT64)ReturnedProductTypea)) != 0i64 )
  {
    ExpHpGCScheduledNonPaged = 0;
    v10 = 1;
    ExpHpGCScheduledPaged = 0;
    ExpHpGCInitialized = 1;
  }
  else
  {
    v10 = 0;
  }
  v11 = v10 != 0 ? v7 : 0;
  v12 = ExpProfileInitialization();
  *(_QWORD *)&ExpUuidLock = 0i64;
  ExpUuidLastTimeAllocated = *(_QWORD *)&KUSER_SHARED_DATA.SystemTime.LowPart;
  v13 = v12 ? v11 : 0;
  if ( ExpKeyedEventInitialization() < 0 )
    v13 = 0;
  PoolWithTag = ExAllocatePoolWithTag(NonPagedPoolNx, 0x30u, 0x20666E57u);
  ExpWnfDispatcher = (__int64)PoolWithTag;
  if ( PoolWithTag )
  {
    *PoolWithTag = 0i64;
    PoolWithTag[1] = 0i64;
    PoolWithTag[2] = 0i64;
    *(_DWORD *)PoolWithTag = 3148040;
    *((_QWORD *)PoolWithTag + 3) = ExpWnfWorkItemRoutine;
    *((_QWORD *)PoolWithTag + 4) = 0i64;
    *((_QWORD *)PoolWithTag + 1) = 0i64;
    v15 = 1;
  }
  else
  {
    v15 = 0;
  }
  v16 = ExpWin32Initialization() ? (v15 != 0 ? v13 : 0) : 0;
  if ( ExpWorkerFactoryInitialization() < 0 )
    v16 = 0;
  v17 = ExpSaInitialize() != 0 ? v16 : 0;
  v18 = ExpMicrocodeInitialization(1i64);
  if ( (int)(v18 + 0x80000000) >= 0 && v18 != -1073741637 )
    v17 = 0;
  LODWORD(v34) = 0;
  if ( RtlGetProductInfo(6u, 0, 0, 0, (PULONG)&v34)
    && (_DWORD)v34 != -1412584499
    && (unsigned __int8)ExpGetProductInfoSuiteTypeMap((_EXP_PRODUCTINFO_SUITE_TYPE_MAP *)(unsigned int)v34)
    && KUSER_SHARED_DATA.NtProductType )
  {
    KUSER_SHARED_DATA.NtProductType = 0;
  }
  RegistrationInfo[1] = 5;
  v32 = ExpPcwHostCallback;
  v30 = 1i64;
  RegistrationInfo[0] = 65537;
  v31 = 0i64;
  v33 = 0i64;
  if ( ExRegisterHost(&ExpPcwExtensionHost, v19, RegistrationInfo) < 0 )
    ExpPcwExtensionHost = 0i64;
  if ( (_BYTE)HvlHypervisorConnected )
  {
    v24[1] = 1;
    v25 = 512i64;
    v27 = ExpCrossVmIntHostCallback;
    v26 = 0i64;
    if ( (HvlpFlags & 2) != 0 )
    {
      v24[0] = 196623;
      v28 = &ExpCrossVmIntExtensionHostRoot;
      if ( ExRegisterHost(&ExpCrossVmIntExtensionHostRoot, v20, v24) < 0 )
        ExpCrossVmIntExtensionHostRoot = 0i64;
    }
    else
    {
      v24[0] = 196624;
      v28 = &ExpCrossVmIntExtensionHostGuest;
      if ( ExRegisterHost(&ExpCrossVmIntExtensionHostGuest, v20, v24) < 0 )
        ExpCrossVmIntExtensionHostGuest = 0i64;
    }
  }
  ExpInitializeSvm();
  return v17;
}

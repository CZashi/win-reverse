__int64 __fastcall DriverEntry(__int64 a1, unsigned __int16 *a2)
{
  unsigned int v5; // eax
  __int64 v6; // rcx
  __int64 v7; // r8
  char v8; // r14
  __int64 PoolWithTag; // rax
  int RegistryParameters; // ebx
  __int64 v11; // rdx
  unsigned int v12; // eax
  __int64 v13; // rbx
  __int64 v14; // rax
  __int64 (__fastcall *v15)(_QWORD, __int64 (__fastcall *)()); // rax
  __int64 v16; // rcx
  int v17; // [rsp+30h] [rbp-188h]
  int v18; // [rsp+30h] [rbp-188h]
  char v19; // [rsp+34h] [rbp-184h]
  __int128 v20; // [rsp+38h] [rbp-180h] BYREF
  __int128 v21; // [rsp+48h] [rbp-170h] BYREF
  int v22[72]; // [rsp+60h] [rbp-158h] BYREF

  v19 = 0;
  if ( InitSafeBootMode )
    return 3221226335i64;
  v22[0] = 276;
  if ( (int)RtlGetVersion(v22) >= 0 )
  {
    v5 = v22[1];
    v6 = (unsigned int)v22[2];
  }
  else
  {
    v5 = 5;
    v6 = 0i64;
  }
  if ( v5 > 6 || v5 == 6 && (unsigned int)v6 >= 2 )
  {
    ExDefaultNonPagedPoolType = 512;
    ExDefaultMdlProtection = 0x40000000;
  }
  WPP_MAIN_CB = 0i64;
  qword_1C00117A8 = (__int64)&WPP_ThisDir_CTLGUID_MpFilter;
  qword_1C00117B0 = 0i64;
  qword_1C00117C0 = 0i64;
  qword_1C00117C8 = 1i64;
  WppLoadTracingSupport(v6);
  qword_1C00117C0 = 0i64;
  WppInitKm();
  if ( WPP_GLOBAL_Control != &WPP_GLOBAL_Control && (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) != 0 )
    WPP_SF_q(*((_QWORD *)WPP_GLOBAL_Control + 3), 10i64, &WPP_f3b7221d79003247a5da15a50dee3923_Traceguids, a1);
  McGenEventTracingRegister(
    &Microsoft_Antimalware_AMFilter,
    0i64,
    &Microsoft_Antimalware_AMFilter_Context,
    &qword_1C0011020);
  v20 = 0i64;
  v21 = 0i64;
  FltParseFileName(a2, 0i64, 0i64, &v20);
  RtlInitUnicodeString(&v21);
  LOBYTE(v7) = 1;
  v8 = RtlEqualUnicodeString(&v21, &v20, v7);
  PoolWithTag = ExAllocatePoolWithTag((unsigned int)ExDefaultNonPagedPoolType, 3264i64, 1684426829i64);
  MpData = PoolWithTag;
  if ( !PoolWithTag )
  {
    RegistryParameters = -1073741670;
    if ( WPP_GLOBAL_Control != &WPP_GLOBAL_Control && (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) != 0 )
    {
      WPP_SF_qD(
        *((_QWORD *)WPP_GLOBAL_Control + 3),
        12i64,
        &WPP_f3b7221d79003247a5da15a50dee3923_Traceguids,
        __readgsqword(0x188u),
        -1073741670);
      RegistryParameters = -1073741670;
    }
    goto LABEL_107;
  }
  memset(PoolWithTag, 0i64, 3264i64);
  *(_WORD *)MpData = -9728;
  *(_WORD *)(MpData + 2) = 3264;
  *(_BYTE *)(MpData + 1713) = v8;
  RegistryParameters = MpInitializeGlobals(a1, a2);
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 13i64;
    goto LABEL_106;
  }
  RegistryParameters = MpLoadRegistryParameters();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 14i64;
    goto LABEL_106;
  }
  MpSetDefaultConfigs();
  MpSetBufferLimits();
  MpInitializeBoostManager();
  RegistryParameters = MpInitializeProcessTable();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 15i64;
    goto LABEL_106;
  }
  RegistryParameters = MpInitBootSectorCache();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 16i64;
    goto LABEL_106;
  }
  v12 = dword_1C00114CC << 6;
  if ( dword_1C00114CC << 6 && !qword_1C0011520 )
  {
    v13 = v12;
    v14 = ExAllocatePoolWithTag(1i64, v12, 1883459661i64);
    qword_1C0011520 = v14;
    if ( v14 )
    {
      memset(v14, 0i64, v13);
      ExInitializeResourceLite(&unk_1C0011640);
    }
    else if ( WPP_GLOBAL_Control != &WPP_GLOBAL_Control && (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) != 0 )
    {
      _mm_lfence();
      WPP_SF_qD(
        *((_QWORD *)WPP_GLOBAL_Control + 3),
        17i64,
        &WPP_f3b7221d79003247a5da15a50dee3923_Traceguids,
        __readgsqword(0x188u),
        -1073741801);
    }
  }
  RegistryParameters = MpInitializeProcessExclusions();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 18i64;
    goto LABEL_106;
  }
  v18 = MpPowerStatusInitialize((_QWORD *)(MpData + 1720));
  if ( v18 < 0 && WPP_GLOBAL_Control != &WPP_GLOBAL_Control && (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) != 0 )
  {
    _mm_lfence();
    WPP_SF_qD(
      *((_QWORD *)WPP_GLOBAL_Control + 3),
      19i64,
      &WPP_f3b7221d79003247a5da15a50dee3923_Traceguids,
      __readgsqword(0x188u),
      v18);
  }
  RegistryParameters = MpTxfInitialize();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 20i64;
    goto LABEL_106;
  }
  RegistryParameters = MpAsyncInitialize();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 21i64;
    goto LABEL_106;
  }
  RegistryParameters = MpRegInitialize();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 22i64;
    goto LABEL_106;
  }
  RegistryParameters = MpInitializeDocOpenRules();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 23i64;
    goto LABEL_106;
  }
  RegistryParameters = MpFgInitialize();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 24i64;
    goto LABEL_106;
  }
  RegistryParameters = MpDlpInitialize();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 25i64;
    goto LABEL_106;
  }
  _mm_lfence();
  MpInitializeDriverInfo();
  RegistryParameters = MpInitializeFltMgr(a1);
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 26i64;
    goto LABEL_106;
  }
  RegistryParameters = MpCreateCommPorts();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 27i64;
    goto LABEL_106;
  }
  RegistryParameters = MpSetProcessNotifyRoutine();
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 28i64;
    goto LABEL_106;
  }
  RegistryParameters = PsSetLoadImageNotifyRoutine(MpLoadImageNotifyRoutine);
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 29i64;
    goto LABEL_106;
  }
  RegistryParameters = PsSetCreateThreadNotifyRoutine(MpCreateThreadNotifyRoutine);
  v17 = RegistryParameters;
  if ( RegistryParameters < 0 )
  {
    if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      goto LABEL_107;
    v11 = 30i64;
    goto LABEL_106;
  }
  v15 = *(__int64 (__fastcall **)(_QWORD, __int64 (__fastcall *)()))(MpData + 40);
  if ( v15 )
  {
    RegistryParameters = v15(0i64, MpCreateThreadNotifyRoutineEx);
    v17 = RegistryParameters;
    if ( RegistryParameters < 0 )
    {
      if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
        goto LABEL_107;
      v11 = 31i64;
      goto LABEL_106;
    }
  }
  MpSetImageVerificationCallback();
  MpSeqDetectCtxInitialize(v16, *(_QWORD *)(MpData + 16));
  v19 = 1;
  RegistryParameters = FltStartFiltering(*(_QWORD *)(MpData + 16));
  if ( RegistryParameters >= 0 )
  {
    MpUpdateRunningProcesses();
    RegistryParameters = MpObInitialize();
    v17 = RegistryParameters;
    if ( RegistryParameters >= 0 )
    {
      RegistryParameters = MpRegisterRegCallback();
      v17 = RegistryParameters;
      if ( RegistryParameters >= 0
        || WPP_GLOBAL_Control == &WPP_GLOBAL_Control
        || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
      {
        goto LABEL_107;
      }
      v11 = 33i64;
    }
    else
    {
      if ( WPP_GLOBAL_Control == &WPP_GLOBAL_Control || (*((_DWORD *)WPP_GLOBAL_Control + 11) & 1) == 0 )
        goto LABEL_107;
      v11 = 32i64;
    }
LABEL_106:
    _mm_lfence();
    RegistryParameters = v17;
    WPP_SF_qD(
      *((_QWORD *)WPP_GLOBAL_Control + 3),
      v11,
      &WPP_f3b7221d79003247a5da15a50dee3923_Traceguids,
      __readgsqword(0x188u),
      v17);
  }
LABEL_107:
  if ( RegistryParameters < 0 )
  {
    if ( MpData )
    {
      MpRemoveImageVerificationCallback();
      MpUnregisterRegCallback();
      MpObShutdown();
      PsRemoveCreateThreadNotifyRoutine(MpCreateThreadNotifyRoutine);
      if ( *(_QWORD *)(MpData + 40) )
        PsRemoveCreateThreadNotifyRoutine(MpCreateThreadNotifyRoutineEx);
      PsRemoveLoadImageNotifyRoutine(MpLoadImageNotifyRoutine);
      MpRemoveProcessNotifyRoutine();
      MpFreeCommPorts();
      MpFgAuditShutdown();
      MpTearDownFltMgr();
      if ( (v19 & 1) != 0 )
        MpSeqDetectCtxShutdown();
      MpCleanupDriverInfo();
      MpDlpCleanup();
      MpFgCleanup();
      MpCleanupCopyCache();
      MpCleanupDocOpenRules();
      MpRegShutdown();
      MpAsyncShutdown();
      MpTxfCleanup();
      MpPowerStatusUninitialize(*(_QWORD *)(MpData + 1720));
      *(_QWORD *)(MpData + 1720) = 0i64;
      MpShutdownProcessExclusions();
      MpDeleteBootSectorCache();
      MpShutdownProcessTable();
      MpShutdownBoostManager();
      MpFreeGlobals();
      ExFreePoolWithTag(MpData, 1684426829i64);
    }
    McGenEventTracingUnregister(&Microsoft_Antimalware_AMFilter_Context);
    WppCleanupKm();
  }
  return (unsigned int)RegistryParameters;
}

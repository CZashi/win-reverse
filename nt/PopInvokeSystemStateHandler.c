typedef enum {
    PowerStateSleeping1 = 0,
    PowerStateSleeping2 = 1,
    PowerStateSleeping3 = 2,
    PowerStateSleeping4 = 3,
    PowerStateShutdownOff = 4,
    PowerStateShutdownReset = 5,
    PowerStateSleeping4Firmware = 6,
    PowerStateMaximum = 7
} POWER_STATE_HANDLER_TYPE, *PPOWER_STATE_HANDLER_TYPE;

NTSTATUS __fastcall PopInvokeSystemStateHandler(POWER_STATE_HANDLER_TYPE Type, _POP_HIBER_CONTEXT *HiberContext)
{
  __int64 v3; // r15
  unsigned __int8 CurrentIrql; // r13
  int Next; // er12
  _POP_HIBER_CONTEXT *v6; // rbx
  NTSTATUS (__stdcall *v7)(_POP_HIBER_CONTEXT *); // rsi
  _POP_HIBER_CONTEXT *v8; // rdi
  UINT8 *v9; // rsi
  __int64 v10; // rbx
  __int64 v11; // rax
  __int64 v12; // rdi
  INT64 v13; // rcx
  void *ExtraMapVa; // rcx
  char v15; // bl
  char v16; // bl
  unsigned __int64 v17; // rax
  __int64 v18; // rcx
  char v19; // al
  __int64 v21; // rcx
  unsigned int i; // ebx
  int v23; // edi
  bool v24; // zf
  UINT64 Flag; // [rsp+20h] [rbp-E0h]
  unsigned __int64 v26; // [rsp+30h] [rbp-D0h] BYREF
  _GROUP_AFFINITY NewAffinity; // [rsp+38h] [rbp-C8h] BYREF
  unsigned __int64 v28; // [rsp+48h] [rbp-B8h] BYREF
  _KDPC dst; // [rsp+50h] [rbp-B0h] BYREF
  UINT8 DeferredContext[80]; // [rsp+90h] [rbp-70h] BYREF
  _EVENT_DATA_DESCRIPTOR EventData; // [rsp+E0h] [rbp-20h] BYREF
  _EVENT_DATA_DESCRIPTOR v32; // [rsp+F0h] [rbp-10h] BYREF
  __int64 v33[2]; // [rsp+100h] [rbp+0h] BYREF
  _SLIST_ENTRY v34[9]; // [rsp+110h] [rbp+10h] BYREF
  __int128 v35; // [rsp+1A0h] [rbp+A0h] BYREF
  __int64 v36; // [rsp+1B0h] [rbp+B0h]

  v3 = Type;
  NewAffinity = 0i64;
  memset((UINT8 *)&dst, 0, sizeof(dst));
  v26 = 0i64;
  CurrentIrql = 0;
  Next = -1073741823;
  memset(DeferredContext, 0, sizeof(DeferredContext));
  *(_DWORD *)&DeferredContext[40] = v3;
  v36 = 0i64;
  *(_QWORD *)DeferredContext = &v35;
  *(_QWORD *)&DeferredContext[32] = &PopPowerStateNotifyHandler;
  v35 = 0i64;
  if ( (_DWORD)v3 != 7 )
  {
    *(_QWORD *)DeferredContext = (char *)&PopPowerStateHandlers + 24 * v3;
    if ( !*(_QWORD *)(*(_QWORD *)DeferredContext + 8i64) )
      return -1073741632;
  }
  *(_DWORD *)&DeferredContext[48] = KeNumberProcessors_0;
  *(_DWORD *)&DeferredContext[60] = KeNumberProcessors_0;
  *(_DWORD *)&DeferredContext[56] = 1;
  if ( (unsigned int)(v3 - 4) > 1 && PopCheckpointSystemSleepEnabled )
  {
    v21 = *(unsigned int *)(*(_QWORD *)DeferredContext + 16i64);
    LODWORD(v21) = v21 | 0x40000;
    *(_QWORD *)(*(_QWORD *)DeferredContext + 16i64) = v21;
  }
  if ( ((_DWORD)v3 == 3 || (_DWORD)v3 == 6) && HiberContext )
  {
    v6 = HiberContext;
    *(_QWORD *)&DeferredContext[16] = HiberContext;
    v7 = PopSaveHiberContextWrapper;
    *(_QWORD *)&DeferredContext[24] = HiberContext;
    *(_QWORD *)&DeferredContext[8] = PopSaveHiberContextWrapper;
    v8 = HiberContext;
  }
  else
  {
    v6 = *(_POP_HIBER_CONTEXT **)&DeferredContext[24];
    v8 = *(_POP_HIBER_CONTEXT **)&DeferredContext[16];
    v7 = *(NTSTATUS (__stdcall **)(_POP_HIBER_CONTEXT *))&DeferredContext[8];
  }
  memset((UINT8 *)v34, 0, sizeof(v34));
  if ( HiberContext )
  {
    *(_QWORD *)&PopHibernateSystemContext = *(_QWORD *)DeferredContext;
    qword_140C503C0 = *(_QWORD *)&DeferredContext[32];
    dword_140C503C8 = *(_DWORD *)&DeferredContext[40];
    byte_140C503CC = DeferredContext[44];
    dword_140C503D0 = *(_DWORD *)&DeferredContext[48];
    qword_140C503A8 = (__int64)v7;
    v9 = (UINT8 *)&PopHibernateSystemContext;
    qword_140C503B0 = (__int64)v8;
    qword_140C503B8 = (__int64)v6;
    qword_140C503D8 = *(_QWORD *)&DeferredContext[56];
    RtlpInterlockedPushEntrySList(&stru_140C503E0, &v34[8]);
  }
  else
  {
    NewAffinity.Reserved[1] = 0;
    *(_DWORD *)&NewAffinity.Group = (unsigned __int16)((unsigned int)KiProcessorIndexToNumberMappingTable[0] >> 6);
    NewAffinity.Reserved[2] = 0;
    NewAffinity.Mask = 1i64 << (KiProcessorIndexToNumberMappingTable[0] & 0x3F);
    KeSetSystemGroupAffinityThread(&NewAffinity, 0i64);
    CurrentIrql = KeGetCurrentIrql();
    __writecr8(2ui64);
    KeInitializeDpc(&dst, PopInvokeStateHandlerTargetProcessor, DeferredContext);
    dst.Importance = 2;
    for ( i = 0; i < (unsigned int)KeNumberProcessors_0; ++i )
    {
      if ( i != KeGetCurrentPrcb()->Number )
      {
        v23 = *(_DWORD *)&DeferredContext[52];
        if ( !dst.DpcData )
          dst.Number = i + 1280;
        KeInsertQueueDpc(&dst, 0i64, 0i64);
        while ( v23 == *(_DWORD *)&DeferredContext[52] )
          _mm_pause();
      }
    }
    v9 = DeferredContext;
  }
  PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 2ui64);
  PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 3ui64);
  if ( TargetState == 4 )
  {
    v12 = 0i64;
    v10 = 1000000i64 * KeGetCurrentPrcb()->MHz;
  }
  else
  {
    v10 = PopQpcFrequency;
    LODWORD(v11) = KeQueryPerformanceCounter(0i64);
    v12 = v11;
  }
  if ( (PerfGlobalGroupMask.Masks[4] & 0x8000) != 0 )
  {
    EventData.Reserved = 0;
    EventData.Ptr = (unsigned __int64)v33;
    v33[0] = v12;
    v33[1] = v10;
    EventData.Size = 16;
    LODWORD(Flag) = 4200450;
    EtwTraceKernelEvent(&EventData, 1ui64, 0x80008000ui64, 0x1230ui64, Flag);
  }
  PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 4ui64);
  if ( HiberContext )
  {
    RtlpDebugPrintCallbacksActive = 0;
    if ( VfIsVerifierEnabled() )
    {
      LOBYTE(v13) = 1;
      VfNotifyOfHibernate(v13);
    }
  }
  PoAllProcIntrDisabled = 1;
  PopCheckpointSystemSleep(0x11u);
  if ( SLODWORD(v34[7].Next) >= 0 )
  {
    v9[44] = 1;
    PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 0xCui64);
    if ( (_DWORD)v3 != 3 && (_DWORD)v3 != 6 )
      off_140C008C8[0]();
    if ( HiberContext )
    {
      PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 5ui64);
      if ( (PopSimulateHiberBugcheck & 0x100) == 0 )
        MiUpdateUserMappings();
      PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 0xAui64);
    }
    PopCheckpointSystemSleep(0x12u);
    PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 6ui64);
    PopCheckpointSystemSleep(0x1Au);
    Next = (int)v34[7].Next;
    KeRebaselineInterruptTime();
    off_140C008B8[0]();
    if ( HiberContext && Next == 1073742484 )
      PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 7ui64);
    PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 8ui64);
    if ( HiberContext )
    {
      if ( Next == 1073742484 )
      {
        PopCheckpointSystemSleep(0x1Bu);
        PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 9ui64);
        PopCheckpointSystemSleep(0x20u);
      }
      MmInvalidateDumpAddresses(qword_140C23468, 0x13ui64);
      ExtraMapVa = HiberContext->ExtraMapVa;
      if ( ExtraMapVa )
        MmInvalidateDumpAddresses(ExtraMapVa, 16 * HiberContext->ProcessorCount);
      PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 0xAui64);
      if ( (PopSimulateHiberBugcheck & 0x100) == 0 )
      {
        MiUpdateUserMappings();
        MiConvertHiberPhasePages(0i64);
      }
      HiberContext->KernelPhaseVerificationActive = 0;
      PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 0xBui64);
    }
    v15 = PopDebugFlags;
    if ( (PopDebugFlags & 1) != 0 && (_BYTE)KdDebuggerEnabled )
      DbgBreakPointWithStatus(Next);
    if ( (v15 & 2) != 0 )
      KeBugCheckEx(0xA0u, 0xAu, 0, 0, 0);
    PopNoMoreInput = 0;
    if ( Next >= 0 )
    {
      ++PoPowerSequence;
      PopFullWake = 0;
      PopPendingUserPresenceDuringSystemSleep = 0;
      PopPendingUserPresenceMonitorOnReason = MonitorRequestReasonUnknown;
      LODWORD(AccumulatedIdleTime) = 1;
      if ( PoResumeFromHibernate )
      {
        _InterlockedOr(&PopPendingUserPresenceDuringSystemSleep, 1u);
        _InterlockedOr((volatile signed __int32 *)&PopPendingUserPresenceMonitorOnReason, 0x19u);
      }
    }
    v9[44] = 0;
    PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 0xCui64);
  }
  if ( HiberContext )
  {
    if ( Next == -1073741632 )
    {
      if ( (PopSimulate & 0x1000) == 0 )
      {
        while ( 1 )
          ;
      }
      HiberContext->Reset = 1;
    }
    else
    {
      PoHiberInProgress = 0;
      HiberContext->Status = Next;
      if ( !HiberContext->Reset )
      {
        if ( VfIsVerifierEnabled() )
          VfNotifyOfHibernate(0i64);
        if ( RtlpDebugPrintCallbackList == &RtlpDebugPrintCallbackList )
          RtlpDebugPrintCallbacksActive = 1;
        HiberContext->Status = 1073742484;
        goto LABEL_49;
      }
    }
    v24 = qword_140C23E00 == 0;
    *(_QWORD *)v9 = &unk_140C23DF8;
    *((_QWORD *)v9 + 3) = 0i64;
    if ( !v24 )
      PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 6ui64);
    HalReturnToFirmware(3);
  }
LABEL_49:
  KeRebaselineInterruptTime();
  KeRebaselineSystemTime();
  PopCheckpointSystemSleep(0x21u);
  PoAllProcIntrDisabled = 0;
  PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 0xDui64);
  if ( Next >= 0 )
  {
    if ( TargetState != 4 || PoResumeFromHibernate )
    {
      v16 = 0;
      LODWORD(v17) = KeQueryPerformanceCounter(0i64);
      v26 = v17;
      ((void (__fastcall *)(unsigned __int64 *, unsigned __int64 *))off_140C006A0[0])(
        &HiberPerf.TimeStampCounterAtSwitchTime,
        &HiberPerf.HalTscOffset);
    }
    else
    {
      v16 = 1;
      if ( !((unsigned __int8 (__fastcall *)(unsigned __int64 *, _QWORD))off_140C006A0[0])(&v26, 0i64) )
        v26 = 0i64;
    }
    if ( (PerfGlobalGroupMask.Masks[4] & 0x8000) != 0 )
    {
      v28 = v26;
      *(_QWORD *)&v32.Size = 8i64;
      v32.Ptr = (unsigned __int64)&v28;
      LODWORD(Flag) = 4200450;
      EtwTraceKernelEvent(&v32, 1ui64, 0x80008000ui64, 0x1231ui64, Flag);
    }
    if ( v16 )
    {
      v26 = v26 / (1000 * (unsigned __int64)KeGetCurrentPrcb()->MHz) * (PopQpcFrequency / 0x3E8);
      stru_140C23788.QuadPart = v26 - v12;
    }
  }
  PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 0xEui64);
  PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 0xFui64);
  PopIssueNextState((_POP_SYS_CONTEXT *)v9, (_POP_PROC_LOCAL_CONTEXT *)v34, 0x10ui64);
  if ( SLODWORD(v34[7].Next) >= 0 )
  {
    v18 = *(_QWORD *)v9;
    LODWORD(v34[7].Next) = 0;
    v19 = *(_BYTE *)(v18 + 5);
    if ( v19 != -1 )
      *(_BYTE *)(v18 + 5) = v19 + 1;
  }
  if ( HiberContext )
  {
    if ( !byte_140C23481 && Next == 1073742484 )
    {
      if ( byte_140C50390 )
        BgLibraryInitialize(Context, 0i64);
    }
  }
  else
  {
    __writecr8(CurrentIrql);
  }
  return (NTSTATUS)v34[7].Next;
}

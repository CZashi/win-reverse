VOID __fastcall KeClockInterruptNotify(_KTRAP_FRAME *TrapFrame, INT64 PreviousIrql)
{
  UINT8 v2; // r14
  struct _KPRCB *CurrentPrcb; // rsi
  char *v5; // r12
  UINT64 v6; // rax
  UINT64 v7; // rbx
  int v8; // eax
  char v9; // r13
  int v10; // eax
  CHAR ProcessorMode; // di
  __int64 v12; // rcx
  unsigned __int64 *v13; // rsi
  bool v14; // zf
  unsigned __int8 CurrentIrql; // bl
  unsigned __int8 v16; // bl
  unsigned __int64 v17; // rbx
  __int64 v18; // rax
  struct _KPRCB *v19; // rbx
  __int16 v20; // r15
  unsigned int LowPart; // er13
  _KHETERO_CPU_POLICY v22; // edx
  UINT64 PrcbFlags; // rcx
  INT64 EfficiencySchedulingClass; // r9
  _ETHREAD *CurrentThread; // rsi
  NTSTATUS SystemHeteroCpuPolicy; // edi
  _KNODE *ParentNode; // r14
  __int64 v28; // rdx
  __int64 v29; // r8
  unsigned __int64 v30; // rdx
  int v31; // er11
  unsigned __int64 v32; // rax
  __int64 v33; // r8
  unsigned __int8 v34; // al
  struct _KPRCB *v35; // rdi
  __int64 v36; // r8
  bool v37; // r15
  _KPRCBFLAG v38; // edx
  char v39; // al
  _KSCHEDULING_GROUP *volatile SchedulingGroup; // rcx
  char v41; // dl
  UINT64 v42; // r8
  char v43; // al
  unsigned __int64 v44; // rax
  unsigned __int8 v45; // bl
  UINT64 SpinCount; // [rsp+30h] [rbp-78h] BYREF
  UINT64 IdealSetOut; // [rsp+38h] [rbp-70h] BYREF
  UINT64 RequestedIncrement; // [rsp+40h] [rbp-68h] BYREF
  UINT64 DeliveredIncrement; // [rsp+48h] [rbp-60h] BYREF
  UINT64 AvailableSetOut; // [rsp+50h] [rbp-58h] BYREF
  UINT64 PreferredSetOut; // [rsp+58h] [rbp-50h] BYREF
  __int64 CurrentQpc[2]; // [rsp+60h] [rbp-48h] BYREF
  int v53; // [rsp+A0h] [rbp-8h]
  char v54; // [rsp+C0h] [rbp+18h]

  v2 = PreviousIrql;
  DeliveredIncrement = 0i64;
  CurrentPrcb = KeGetCurrentPrcb();
  v5 = 0i64;
  CurrentQpc[0] = 0i64;
  v54 = 0;
  RequestedIncrement = 0i64;
  if ( KiForceIdleDisabled )
  {
LABEL_16:
    ProcessorMode = TrapFrame->SegCs & 1;
    if ( CurrentPrcb->ClockOwner )
    {
      v12 = 3i64 * (unsigned int)KiClockTickTraceIndex;
      KiClockTickTraceIndex = ((_BYTE)KiClockTickTraceIndex + 1) & 0xF;
      v13 = (unsigned __int64 *)((char *)&KiClockTickTraces + 8 * v12);
      v14 = KiClockOwnerOneShotRequestState == 1;
      v13[1] = *(_QWORD *)&KUSER_SHARED_DATA.InterruptTime.LowPart;
      if ( v14 )
      {
        CurrentIrql = KeGetCurrentIrql();
        __writecr8(0xFui64);
        KiClockOwnerOneShotRequestState = 2;
        KiClockOwnerOneShotRequest = 0i64;
        __writecr8(CurrentIrql);
      }
      KiUpdateTime(ProcessorMode, v2);
      if ( KiClockOwnerOneShotRequestState == 2 )
      {
        v16 = KeGetCurrentIrql();
        __writecr8(0xFui64);
        KiSetClockIntervalToMinimumRequested();
        __writecr8(v16);
      }
      *v13 = KUSER_SHARED_DATA.BaselineInterruptTimeQpc;
      v17 = *(_QWORD *)&KUSER_SHARED_DATA.InterruptTime.LowPart;
      if ( KiClockState == ClockStatePendingPeriodic )
      {
        KiRestoreClockTickRate(*(INT64 *)&KUSER_SHARED_DATA.InterruptTime.LowPart, &RequestedIncrement);
        _InterlockedExchange((volatile __int32 *)&KiClockState, 0);
        KiEventClockStateChange(ClockStatePeriodic, ClockStatePendingPeriodic, &DeliveredIncrement, &RequestedIncrement);
      }
      v18 = v17 + (unsigned int)KeTimeIncrement;
      v13[2] = v17;
      KiClockTimerNextTickTime = v18;
      goto LABEL_83;
    }
    v19 = KeGetCurrentPrcb();
    v20 = v53;
    ++v19->ClockInterrupts;
    ++v19->InterruptLastCount;
    _disable();
    LowPart = KUSER_SHARED_DATA.TickCount.LowPart;
    if ( (v20 & 0x200) != 0 )
      _enable();
    KeAccumulateTicks(v19, v19->LastTick, KUSER_SHARED_DATA.TickCount.LowPart, v2, ProcessorMode);
    CurrentThread = v19->CurrentThread;
    v19->ClockKeepAlive = 1;
    if ( CurrentThread != v19->IdleThread )
    {
      if ( CurrentThread->Tcb.CycleTime >= CurrentThread->Tcb.QuantumTarget )
        goto LABEL_69;
      SystemHeteroCpuPolicy = CurrentThread->Tcb.SystemHeteroCpuPolicy;
      AvailableSetOut = 0i64;
      IdealSetOut = 0i64;
      PreferredSetOut = 0i64;
      if ( SystemHeteroCpuPolicy )
      {
        if ( (unsigned int)SystemHeteroCpuPolicy >= 5 )
          SystemHeteroCpuPolicy = KiConvertDynamicHeteroPolicy(CurrentThread, v22, v19);
        ParentNode = v19->ParentNode;
        KiGenerateHeteroSets(
          ParentNode,
          CurrentThread->Tcb.Affinity.Mask,
          (_KHETERO_CPU_POLICY)SystemHeteroCpuPolicy,
          &IdealSetOut,
          &PreferredSetOut,
          &AvailableSetOut);
        if ( (AvailableSetOut & v19->GroupSetMember) == 0
          || KiIsQosGroupingActive()
          && (v28 & v29) != 0
          && (unsigned int)(unsigned __int8)CurrentThread->Tcb.ThreadFlags2 - 1 <= 1
          && (v28 & v19->GroupSetMember) == 0 )
        {
          goto LABEL_69;
        }
        if ( (IdealSetOut & v19->GroupSetMember) == 0 )
        {
          if ( (v29 & ParentNode->IdleSmtSet) != 0 )
            v29 &= ParentNode->IdleSmtSet;
          if ( (v29 & IdealSetOut) != 0 )
            goto LABEL_69;
          v30 = v29 & PreferredSetOut & ~IdealSetOut;
          if ( (unsigned int)(SystemHeteroCpuPolicy - 3) <= 1 )
            EfficiencySchedulingClass = v19->PowerState.EfficiencySchedulingClass;
          else
            EfficiencySchedulingClass = v19->PowerState.PerformanceSchedulingClass;
          if ( v30 )
          {
            v31 = ParentNode->Affinity.Group << 6;
            do
            {
              _BitScanReverse64(&v32, v30);
              HIDWORD(SpinCount) = v32;
              v33 = (__int64)*(&KiProcessorBlock
                             + (unsigned int)KiProcessorNumberToIndexMappingTable[(unsigned int)(v31 + v32)]);
              v34 = (unsigned int)(SystemHeteroCpuPolicy - 3) <= 1 ? *(_BYTE *)(v33 + 33210) : *(_BYTE *)(v33 + 33209);
              if ( v34 > (unsigned __int8)EfficiencySchedulingClass )
                goto LABEL_69;
              v30 &= ~*(_QWORD *)(v33 + 200);
            }
            while ( v30 );
          }
        }
      }
      v35 = KeGetCurrentPrcb();
      PrcbFlags = (unsigned int)v35->PrcbFlags.PrcbFlags;
      if ( (PrcbFlags & 0x300) != 0 )
      {
        _disable();
        PrcbFlags = (unsigned int)v35->PrcbFlags.PrcbFlags;
        v36 = v35->PrcbFlags.PrcbFlags & 0xFFFFFCFF;
        v37 = (v20 & 0x200) != 0;
        if ( (unsigned __int8)PrcbFlags != LOBYTE(CurrentThread->Tcb.ThreadFlags2) )
        {
          v38.PrcbFlags = v36 | ((CurrentThread->Tcb.ThreadFlags2 & 3) << 8);
          v35->PrcbFlags = v38;
          v39 = PoSetProcessorQoS((INT64)v35, ((unsigned int)v38.PrcbFlags >> 8) & 3, v36, EfficiencySchedulingClass);
          LODWORD(v36) = v35->PrcbFlags.PrcbFlags;
          if ( !v39 )
          {
LABEL_55:
            if ( (v36 & 0x300) == 0 )
              KeUpdatePendingQosRequest((INT64)v35);
            if ( v37 )
              _enable();
            goto LABEL_61;
          }
          LODWORD(v36) = v36 & 0xFFFFFCFF;
        }
        v35->PrcbFlags.PrcbFlags = v36;
        goto LABEL_55;
      }
      if ( (unsigned __int8)PrcbFlags != LOBYTE(CurrentThread->Tcb.ThreadFlags2) )
        KeCheckAndApplyBamQos();
    }
LABEL_61:
    if ( KUSER_SHARED_DATA.TickCountQuad <= v19->GenerationTarget )
    {
      SchedulingGroup = CurrentThread->Tcb.SchedulingGroup;
      if ( !SchedulingGroup || (PrcbFlags = (UINT64)SchedulingGroup + v19->ScbOffset) == 0 )
      {
LABEL_77:
        if ( (int)(v19->ReadyScanTick - LowPart) < 0
          && (!KiShouldScanSharedReadyQueue(v19) || (v19->SharedReadyQueue->ReadySummary & 0x7FFE) == 0)
          && (v19->ReadySummary & 0x7FFE) == 0 )
        {
          v19->ReadyScanTick = LowPart + 75;
        }
LABEL_83:
        if ( !v54 )
          return;
        goto LABEL_84;
      }
      while ( 1 )
      {
        v41 = *(_BYTE *)(PrcbFlags + 112);
        v42 = PrcbFlags - v19->ScbOffset;
        v43 = v41 & 0x10;
        if ( (v41 & 4) != 0 )
        {
          if ( v43 )
            goto LABEL_74;
          if ( (v41 & 2) == 0 )
          {
            if ( *(__int64 *)(v42 + 48) <= 0 )
              break;
LABEL_74:
            v44 = *(_QWORD *)(PrcbFlags + 24);
LABEL_75:
            if ( *(_QWORD *)PrcbFlags >= v44 )
              break;
          }
        }
        else
        {
          if ( v43 )
          {
            v44 = *(_QWORD *)(PrcbFlags + 8);
            goto LABEL_75;
          }
          if ( (v41 & 2) == 0 && *(__int64 *)(v42 + 48) <= 0 )
            break;
        }
        PrcbFlags = *(_QWORD *)(PrcbFlags + 408);
        if ( !PrcbFlags )
          goto LABEL_77;
      }
    }
LABEL_69:
    v19->QuantumEnd = 1;
    if ( v19->NestingLevel )
    {
      v19->InterruptRequest = 1;
    }
    else
    {
      LOBYTE(PrcbFlags) = 2;
      HalRequestSoftwareInterrupt(PrcbFlags);
    }
    goto LABEL_83;
  }
  _disable();
  LODWORD(SpinCount) = 0;
  while ( _interlockedbittestandset64((volatile signed __int32 *)&KiForceIdleLock, 0i64) )
  {
    do
      KeYieldProcessorEx(&SpinCount);
    while ( KiForceIdleLock );
  }
  if ( CurrentPrcb->ClockOwner && KeIsForceIdleEngaged() )
  {
    LODWORD(v6) = RtlGetInterruptTimePrecise(CurrentQpc);
    v7 = v6;
    PoExecuteIdleCheck(v6);
    if ( KiForceIdleWatchdogResetCount == 32 )
    {
      off_140C008C0[0]();
      v8 = 0;
    }
    else
    {
      v8 = KiForceIdleWatchdogResetCount + 1;
    }
    KiForceIdleWatchdogResetCount = v8;
    if ( v7 - KiForceIdleActiveLastStartTime <= 0x1312D00 )
    {
      ++qword_140C31390;
      v9 = 1;
      v5 = (char *)&KiClockTickSkipTraces + 16 * (unsigned int)KiClockTickSkipTraceIndex;
      v54 = 1;
      v10 = ((_BYTE)KiClockTickSkipTraceIndex + 1) & 0xF;
      KiClockTickSkipTraceIndex = v10;
      *v5 = 0;
      *((_QWORD *)v5 + 1) = v7;
      goto LABEL_15;
    }
    KiResetForceIdle(2i64, 1);
  }
  v9 = 0;
LABEL_15:
  _InterlockedAnd64(&KiForceIdleLock, 0i64);
  _enable();
  if ( !v9 )
    goto LABEL_16;
LABEL_84:
  if ( KiClockOwnerOneShotRequestState == 1 )
  {
    v45 = KeGetCurrentIrql();
    __writecr8(0xFui64);
    KiClockOwnerOneShotRequestState = 2;
    KiSetClockIntervalToMinimumRequested();
    __writecr8(v45);
    if ( v5 )
      *v5 = 1;
    ++qword_140C31398;
  }
}

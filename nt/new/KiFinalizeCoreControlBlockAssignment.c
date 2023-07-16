char __fastcall KiFinalizeCoreControlBlockAssignment(__int64 a1)
{
  unsigned __int64 v1; // kr00_8
  unsigned __int64 v2; // rax
  char v3; // r14
  int v5; // ecx
  unsigned int v6; // edx
  __int64 v7; // rbp
  unsigned __int8 CurrentIrql; // r12
  _DWORD *SchedulerAssist; // r9
  __int64 v10; // rdx
  unsigned __int64 CurrentPrcb; // rdi
  _KI_RESCHEDULE_CONTEXT *v12; // rsi
  char v13; // r11
  unsigned int i; // r15d
  char v15; // al
  _KPRCB *Prcb; // rbx
  unsigned __int8 v17; // al
  __int64 v18; // rdx
  _KAFFINITY_EX *v19; // r14
  __int64 Group; // rcx
  unsigned __int64 GroupSetMember; // rdx
  _KSOFTWARE_INTERRUPT_BATCH *v22; // rsi
  __int64 *v23; // rbx
  char v24; // bp
  _KTHREAD *v25; // rsi
  _KLOCK_ENTRIES *UserAbEntries; // rcx
  void *SchedulerSharedSystemSlot; // rdx
  _KLOCK_ENTRIES *v28; // rax
  _BOOL8 v29; // r9
  _KLOCK_ENTRIES *KernelAbEntries; // rax
  __int64 v31; // rcx
  struct _KPRCB *v32; // rbp
  __int64 *v33; // rbx
  unsigned int v34; // ebx
  _KTHREAD *v35; // rbx
  unsigned __int64 v36; // rax
  __int64 v37; // r8
  unsigned __int64 v38; // rcx
  struct _KPRCB *v39; // rcx
  signed __int32 *v40; // r8
  signed __int32 v41; // eax
  signed __int32 v42; // ett
  __int64 v43; // r8
  bool v44; // zf
  unsigned __int8 v45; // al
  struct _KPRCB *v46; // rcx
  _DWORD *v47; // rdx
  unsigned __int8 v48; // al
  struct _KPRCB *v49; // r9
  _DWORD *v50; // r8
  int v51; // eax
  __int16 v52; // r15
  struct _KPRCB *v53; // rdx
  unsigned int SelfIpiRequestSummary; // ecx
  __int64 (__fastcall *v55)(_QWORD, int *, int *, __int64, int *); // rax
  __int64 v56; // rdx
  unsigned int *v57; // rbx
  unsigned __int64 v58; // rdi
  int v59; // ebp
  char v60; // si
  __int64 (__fastcall *v61)(_QWORD, int *, __int128 *, __int64, int *); // rax
  __int64 (__fastcall *v62)(_QWORD, int *, __int128 *, __int64, int *); // rax
  __int64 (__fastcall *v63)(_QWORD, int *, __int128 *, __int64, int *); // rax
  __int64 v65; // [rsp-20h] [rbp-368h] BYREF
  int v66[2]; // [rsp+10h] [rbp-338h] BYREF
  int v67[2]; // [rsp+18h] [rbp-330h] BYREF
  __int64 *v68; // [rsp+20h] [rbp-328h] BYREF
  __int64 *v69; // [rsp+28h] [rbp-320h] BYREF
  __int128 v70; // [rsp+30h] [rbp-318h] BYREF
  int v71; // [rsp+40h] [rbp-308h]
  int v72; // [rsp+48h] [rbp-300h] BYREF
  __int64 v73; // [rsp+50h] [rbp-2F8h] BYREF
  __int128 v74; // [rsp+58h] [rbp-2F0h] BYREF
  __int64 v75; // [rsp+68h] [rbp-2E0h]
  __int64 v76; // [rsp+70h] [rbp-2D8h] BYREF
  int v77[2]; // [rsp+78h] [rbp-2D0h] BYREF
  int v78[2]; // [rsp+80h] [rbp-2C8h] BYREF
  int v79[2]; // [rsp+88h] [rbp-2C0h] BYREF
  int v80[2]; // [rsp+90h] [rbp-2B8h] BYREF
  int v81[2]; // [rsp+98h] [rbp-2B0h] BYREF
  int v82[2]; // [rsp+A0h] [rbp-2A8h] BYREF
  unsigned __int64 v83; // [rsp+A8h] [rbp-2A0h] BYREF
  int v84; // [rsp+B0h] [rbp-298h] BYREF
  __int128 v85; // [rsp+B4h] [rbp-294h]
  __int128 v86; // [rsp+C8h] [rbp-280h] BYREF
  __int64 v87; // [rsp+E0h] [rbp-268h] BYREF
  __int64 v88[33]; // [rsp+E8h] [rbp-260h] BYREF
  __int64 v89; // [rsp+1F0h] [rbp-158h] BYREF
  __int64 v90[33]; // [rsp+1F8h] [rbp-150h] BYREF
  unsigned __int64 v91; // [rsp+340h] [rbp-8h]

  v1 = __readeflags();
  v91 = v1;
  v2 = (unsigned __int64)&v65 ^ _security_cookie;
  v3 = 0;
  v69 = 0i64;
  v5 = 0;
  v73 = 0i64;
  v6 = *(_DWORD *)(a1 + 36);
  if ( !v6 )
    return v2;
  while ( 1 )
  {
    LOBYTE(v2) = v5;
    v7 = KiProcessorBlock[v5];
    if ( *(_DWORD *)(v7 + 34844) == *(_DWORD *)(a1 + 34844) )
      break;
    if ( ++v5 >= v6 )
      return v2;
  }
  CurrentIrql = KeGetCurrentIrql();
  __writecr8(2ui64);
  if ( KiIrqlFlags && (KiIrqlFlags & 1) != 0 && CurrentIrql <= 0xFu )
  {
    SchedulerAssist = KeGetCurrentPrcb()->SchedulerAssist;
    if ( CurrentIrql == 2 )
      LODWORD(v10) = 4;
    else
      v10 = (-1i64 << (CurrentIrql + 1)) & 4;
    SchedulerAssist[5] |= v10;
  }
  CurrentPrcb = (unsigned __int64)KeGetCurrentPrcb();
  v12 = *(_KI_RESCHEDULE_CONTEXT **)(CurrentPrcb + 13032);
  memset_0(v12, 0i64, sizeof(_KI_RESCHEDULE_CONTEXT));
  KiAcquirePrcbLocksForIsolationUnit(v7, 1i64, &v73);
  v72 = 0;
  while ( _interlockedbittestandset64((volatile signed __int32 *)(a1 + 48), 0i64) )
  {
    do
      KeYieldProcessorEx(&v72);
    while ( *(_QWORD *)(a1 + 48) );
  }
  KiStartRescheduleContext(v12, &v73, 0i64);
  KiAdjustProcessorCoreControlBlockAssignment(*(_QWORD *)(v7 + 34904), a1);
  KiAdjustRescheduleContextForProcessorAddition(v12, a1);
  KiCommitRescheduleContext(v12, CurrentPrcb, 0i64, &v69);
  KiReleasePrcbLocksForIsolationUnit(&v73);
  if ( v13 )
  {
    for ( i = 0; i < v12->ProcessorCount; ++i )
    {
      v15 = v12->ProcessorEntries[i].___u6[0];
      Prcb = v12->ProcessorEntries[i].Prcb;
      if ( (v15 & 0x10) == 0 && ((v15 & 8) == 0 || !Prcb->IdleHalt) )
        goto LABEL_33;
      v17 = *(_BYTE *)(CurrentPrcb + 12761);
      if ( v17 )
      {
        if ( v17 != 1 )
        {
          v19 = (_KAFFINITY_EX *)(CurrentPrcb + 12768);
LABEL_28:
          Group = Prcb->Group;
          GroupSetMember = Prcb->GroupSetMember;
          if ( v19->Count > (unsigned __int16)Group )
          {
LABEL_31:
            v19->Bitmap[Group] |= GroupSetMember;
          }
          else if ( v19->Size > (unsigned __int16)Group )
          {
            v19->Count = Group + 1;
            goto LABEL_31;
          }
          v3 = 0;
          goto LABEL_33;
        }
        v18 = *(unsigned int *)(CurrentPrcb + 12764);
        if ( (_DWORD)v18 != Prcb->Number )
        {
          v19 = (_KAFFINITY_EX *)(CurrentPrcb + 12768);
          *(_BYTE *)(CurrentPrcb + 12761) = 2;
          KeAddProcessorAffinityEx(CurrentPrcb + 12768, v18);
          goto LABEL_28;
        }
      }
      else
      {
        *(_BYTE *)(CurrentPrcb + 12761) = 1;
        *(_DWORD *)(CurrentPrcb + 12764) = Prcb->Number;
      }
LABEL_33:
      if ( (v12->ProcessorEntries[i].___u6[0] & 2) != 0 )
        EtwTraceScheduleThread(v12->ProcessorEntries[i].NewThread, Prcb, 0i64);
      if ( (v12->ProcessorEntries[i].___u6[0] & 4) != 0 )
        KiHvEnlightenedGuestPriorityKick(CurrentPrcb, Prcb, (unsigned int)v12->ProcessorEntries[i].KickPriority);
      if ( (v12->ProcessorEntries[i].___u6[0] & 1) != 0 )
        _InterlockedAdd16(&v12->ProcessorEntries[i].NewThread->KeReferenceCount, 0xFFFFu);
    }
    v22 = (_KSOFTWARE_INTERRUPT_BATCH *)(CurrentPrcb + 12760);
    KiFlushSoftwareInterruptBatch(CurrentPrcb + 12760);
  }
  else
  {
    v22 = (_KSOFTWARE_INTERRUPT_BATCH *)(CurrentPrcb + 12760);
  }
  v23 = v69;
  v24 = 0;
  if ( v69 )
  {
    v69 = (__int64 *)*v69;
    do
    {
      KiDeferredReadySingleThread(CurrentPrcb, v23 - 27, &v69, 0i64);
      v23 = v69;
      ++v24;
      if ( v69 )
        v69 = (__int64 *)*v69;
      if ( (v24 & 0xF) == 0 )
        KiFlushSoftwareInterruptBatch(v22);
    }
    while ( v23 );
  }
  LOBYTE(v2) = KiFlushSoftwareInterruptBatch(v22);
  if ( CurrentIrql < 2u )
  {
    v25 = *(_KTHREAD **)(CurrentPrcb + 8);
    if ( *(_QWORD *)(CurrentPrcb + 16) )
    {
      UserAbEntries = v25->UserAbEntries;
      v68 = 0i64;
      if ( UserAbEntries )
      {
        SchedulerSharedSystemSlot = v25->SchedulerSharedSystemSlot;
        if ( SchedulerSharedSystemSlot )
          KiAbThreadSyncUserModeLockEntries(UserAbEntries, SchedulerSharedSystemSlot, v25);
      }
      v28 = v25->UserAbEntries;
      if ( v28 )
        v29 = (unsigned int)(1i64 << v28->EntryCount) - 1 == (v28->AvailableEntryBitmap | v28->OrphanedEntryBitmap);
      else
        v29 = 1i64;
      KernelAbEntries = v25->KernelAbEntries;
      v31 = KernelAbEntries->AvailableEntryBitmap | (unsigned int)KernelAbEntries->OrphanedEntryBitmap;
      if ( (unsigned int)(1i64 << KernelAbEntries->EntryCount) - 1 != (_DWORD)v31 || !v29 )
      {
        v32 = KeGetCurrentPrcb();
        v76 = 0i64;
        KiAbProcessThreadLocks(
          (_DWORD)v25,
          7,
          (unsigned int)&v68,
          (unsigned int)&v76,
          (__int64)&v32->AbSelfIoBoostsList);
        KiAbPropagateBoosts(&v76, &v32->AbSelfIoBoostsList, &v68);
        v33 = v68;
        if ( v68 )
        {
          v68 = (__int64 *)*v68;
          do
          {
            KiDeferredReadySingleThread(v32, v33 - 27, &v68, 0i64);
            v33 = v68;
            ++v3;
            if ( v68 )
              v68 = (__int64 *)*v68;
            if ( (v3 & 0xF) == 0 )
              KiFlushSoftwareInterruptBatch(&v32->DeferredDispatchInterrupts);
          }
          while ( v33 );
        }
        KiFlushSoftwareInterruptBatch(&v32->DeferredDispatchInterrupts);
      }
      v34 = 0;
      v83 = CurrentPrcb & 0xFFFFFFFFFFFFFFFEui64;
      while ( _interlockedbittestandset64((volatile signed __int32 *)(CurrentPrcb + 48), 0i64) )
      {
        do
        {
          if ( (++v34 & HvlLongSpinCountMask) == 0
            && (HvlEnlightenments & 0x40) != 0
            && (unsigned __int8)KiCheckVpBackingLongSpinWaitHypercall(v31) )
          {
            HvlNotifyLongSpinWait(v34);
          }
          else
          {
            _mm_pause();
          }
        }
        while ( *(_QWORD *)(CurrentPrcb + 48) );
      }
      v35 = *(_KTHREAD **)(CurrentPrcb + 16);
      *(_QWORD *)(CurrentPrcb + 16) = 0i64;
      _disable();
      *(_BYTE *)(CurrentPrcb + 32) = 1;
      v36 = __rdtsc();
      v37 = v36 - *(_QWORD *)(CurrentPrcb + 33152);
      *(_QWORD *)(CurrentPrcb + 33152) = v36;
      v25->CycleTime += v37;
      if ( v25 != *(_KTHREAD **)(CurrentPrcb + 24) )
      {
        v38 = ((v37 * (unsigned __int64)*(unsigned int *)(CurrentPrcb + 33208)) >> 16) + v25->CurrentRunTime;
        if ( v38 > 0xFFFFFFFF )
          LODWORD(v38) = -1;
        v25->CurrentRunTime = v38;
      }
      if ( (v25->Header.Size & 0xBE) != 0 )
      {
        LOBYTE(v29) = 1;
        KiEndThreadAccountingPeriodEx(CurrentPrcb, v25, v37, v29);
      }
      v39 = KeGetCurrentPrcb();
      v40 = (signed __int32 *)v39->SchedulerAssist;
      if ( v40 )
      {
        _m_prefetchw(v40);
        v41 = *v40;
        do
        {
          v42 = v41;
          v41 = _InterlockedCompareExchange(v40, v41 & 0xFFDFFFFF, v41);
        }
        while ( v42 != v41 );
        if ( (v41 & 0x200000) != 0 )
          KiRemoveSystemWorkPriorityKick(v39);
      }
      _enable();
      *(_QWORD *)(CurrentPrcb + 8) = v35;
      if ( v35->WaitBlockFill6[68] == 1 )
        v35->ReadyTime = v35->ReadyTime - v35->WaitBlock[2].SpareLong + MEMORY[0xFFFFF78000000320];
      v35->WaitBlockFill6[68] = 2;
      v25->WaitIrql = CurrentIrql;
      v25->WaitReason = 32;
      KiQueueReadyThread(CurrentPrcb, &v83, v25);
      LOBYTE(v43) = CurrentIrql;
      v44 = (unsigned __int8)KiSwapContext(v25, v35, v43) == 0;
    }
    else
    {
      v44 = (v25->MiscFlags & 0x40) == 0;
    }
    if ( !v44 )
    {
      if ( KiIrqlFlags )
      {
        v45 = KeGetCurrentIrql();
        if ( (KiIrqlFlags & 1) != 0 && (unsigned __int8)(v45 - 2) <= 0xDu )
        {
          v46 = KeGetCurrentPrcb();
          v47 = v46->SchedulerAssist;
          v44 = (v47[5] & 0xFFFF0003) == 0;
          v47[5] &= 0xFFFF0003;
          if ( v44 )
            KiRemoveSystemWorkPriorityKick(v46);
        }
      }
      __writecr8(1ui64);
      v25->MiscFlags &= ~0x40u;
      KiDeliverApc(0i64, 0i64, 0i64);
    }
    if ( KiIrqlFlags )
    {
      v48 = KeGetCurrentIrql();
      if ( (KiIrqlFlags & 1) != 0 && (unsigned __int8)(v48 - 2) <= 0xDu )
      {
        v49 = KeGetCurrentPrcb();
        v50 = v49->SchedulerAssist;
        v51 = ~(unsigned __int16)(-1i64 << (CurrentIrql + 1));
        v44 = (v51 & v50[5]) == 0;
        v50[5] &= v51;
        if ( v44 )
          KiRemoveSystemWorkPriorityKick(v49);
      }
    }
    LOBYTE(v2) = CurrentIrql;
    __writecr8(CurrentIrql);
    return v2;
  }
  if ( !*(_QWORD *)(CurrentPrcb + 16) )
    return v2;
  LOBYTE(v2) = *(_BYTE *)(CurrentPrcb + 13242);
  if ( (_BYTE)v2 )
    return v2;
  if ( *(_BYTE *)(CurrentPrcb + 32) )
  {
    *(_BYTE *)(CurrentPrcb + 6) = 1;
    return v2;
  }
  v52 = v91;
  if ( KiAmdTprLowerInterruptDelayDynamicWorkaround )
  {
    v53 = KeGetCurrentPrcb();
    _disable();
    SelfIpiRequestSummary = v53->SelfIpiRequestSummary;
    v53->SelfIpiRequestSummary = SelfIpiRequestSummary | 4;
    if ( !SelfIpiRequestSummary )
      __writemsr(0xC0010015, __readmsr(0xC0010015) | 0x100000000i64);
    if ( (v52 & 0x200) != 0 )
      _enable();
  }
  memset_0(v88, 0i64, 256i64);
  v85 = 0i64;
  if ( (*(_DWORD *)(HalpInterruptController + 244) & 0x40) != 0 && !HalpInterruptNoShorthand )
  {
    v84 = 3;
    v67[0] = -1;
    v67[1] = 1;
    v66[1] = *(_DWORD *)(HalpInterruptIpiLines + 20);
    v66[0] = *(_DWORD *)(HalpInterruptIpiLines + 16);
    v55 = *(__int64 (__fastcall **)(_QWORD, int *, int *, __int64, int *))(HalpInterruptController + 120);
    _disable();
    LOBYTE(v2) = v55(*(_QWORD *)(HalpInterruptController + 16), v66, &v84, 47i64, v67);
    if ( (v52 & 0x200) != 0 )
      _enable();
    return v2;
  }
  v87 = 2097153i64;
  memset_0(v88, 0i64, 256i64);
  LODWORD(v56) = KeGetPcr()->Prcb.Number;
  KeAddProcessorAffinityEx(&v87, v56);
  v66[0] = 0;
  v75 = 0i64;
  v86 = 0i64;
  v74 = 0i64;
  memset_0(v90, 0i64, 256i64);
  v71 = 0;
  v70 = 0i64;
  if ( qword_140EA1C68 )
  {
    LOBYTE(v2) = qword_140EA1C68(&v87, 47i64);
    return v2;
  }
  v89 = 2097153i64;
  memset_0(v90, 0i64, 256i64);
  KiAndAffinityEx(&HalpInterruptPhysicalTargets, &v87, &v89, WORD1(v89));
  if ( HalpInterruptClusterModeEnabled )
  {
    v57 = (unsigned int *)HalpInterruptClusterData;
    v67[0] = 0;
    while ( (unsigned __int64)v57 < HalpInterruptClusterDataEnd )
    {
      if ( (unsigned int)KeAndGroupAffinityEx(&v87, v57 + 2, &v86) )
      {
        v58 = v86;
        v59 = 0;
        LODWORD(v70) = 6;
        v60 = 0;
        *((_QWORD *)&v70 + 1) = *v57;
        LOWORD(v67[0]) = WORD4(v86);
        for ( BYTE2(v67[0]) = 0; v58; BYTE2(v67[0]) = v60 )
        {
          if ( (v58 & 1) != 0 )
          {
            v66[0] = KeGetProcessorIndexFromNumber(v67);
            v59 |= *(_DWORD *)(HalpInterruptTargets + 24i64 * (unsigned int)v66[0] + 12);
            HIDWORD(v70) = v59;
          }
          ++v60;
          v58 >>= 1;
        }
        v77[0] = -1;
        v77[1] = 1;
        v78[1] = *(_DWORD *)(HalpInterruptIpiLines + 20);
        v78[0] = *(_DWORD *)(HalpInterruptIpiLines + 16);
        v61 = *(__int64 (__fastcall **)(_QWORD, int *, __int128 *, __int64, int *))(HalpInterruptController + 120);
        _disable();
        LODWORD(v2) = v61(*(_QWORD *)(HalpInterruptController + 16), v78, &v70, 47i64, v77);
        if ( (v52 & 0x200) != 0 )
          _enable();
        if ( (v2 & 0x80000000) != 0i64 )
          return v2;
      }
      v57 += 6;
    }
    goto LABEL_141;
  }
  if ( HalpInterruptPhysicalModeOnly )
    goto LABEL_141;
  *((_QWORD *)&v74 + 1) = v88[0];
  *(_QWORD *)&v74 = &v87;
  LODWORD(v70) = 5;
  DWORD2(v70) = 0;
  while ( !(unsigned int)KeEnumerateNextProcessor(v66, &v74) )
  {
    if ( *(_DWORD *)(HalpInterruptTargets + 24i64 * (unsigned int)v66[0]) == 5 )
      DWORD2(v70) |= *(_DWORD *)(HalpInterruptTargets + 24i64 * (unsigned int)v66[0] + 8);
  }
  if ( !DWORD2(v70) )
    goto LABEL_141;
  v79[0] = -1;
  v79[1] = 1;
  v80[1] = *(_DWORD *)(HalpInterruptIpiLines + 20);
  v80[0] = *(_DWORD *)(HalpInterruptIpiLines + 16);
  v62 = *(__int64 (__fastcall **)(_QWORD, int *, __int128 *, __int64, int *))(HalpInterruptController + 120);
  _disable();
  LODWORD(v2) = v62(*(_QWORD *)(HalpInterruptController + 16), v80, &v70, 47i64, v79);
  if ( (v52 & 0x200) != 0 )
    _enable();
  if ( (v2 & 0x80000000) == 0i64 )
  {
LABEL_141:
    *((_QWORD *)&v74 + 1) = v90[0];
    *(_QWORD *)&v74 = &v89;
    v66[0] = 0;
    LOWORD(v75) = 0;
    do
    {
      LODWORD(v2) = KeEnumerateNextProcessor(v66, &v74);
      if ( (_DWORD)v2 )
        break;
      LODWORD(v70) = 4;
      v81[0] = -1;
      v81[1] = 1;
      DWORD2(v70) = *(_DWORD *)(HalpInterruptTargets + 24i64 * (unsigned int)v66[0] + 8);
      v82[1] = *(_DWORD *)(HalpInterruptIpiLines + 20);
      v82[0] = *(_DWORD *)(HalpInterruptIpiLines + 16);
      v63 = *(__int64 (__fastcall **)(_QWORD, int *, __int128 *, __int64, int *))(HalpInterruptController + 120);
      _disable();
      LODWORD(v2) = v63(*(_QWORD *)(HalpInterruptController + 16), v82, &v70, 47i64, v81);
      if ( (v52 & 0x200) != 0 )
        _enable();
    }
    while ( (v2 & 0x80000000) == 0i64 );
  }
  return v2;
}

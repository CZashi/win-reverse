NTSTATUS __stdcall KeWaitForMultipleObjects(
        ULONG Count,
        PVOID Object[],
        WAIT_TYPE WaitType,
        KWAIT_REASON WaitReason,
        KPROCESSOR_MODE WaitMode,
        BOOLEAN Alertable,
        PLARGE_INTEGER Timeout,
        PKWAIT_BLOCK WaitBlockArray)
{
  PKWAIT_BLOCK WaitBlock; // r12
  _ETHREAD *CurrentThread; // rsi
  unsigned __int8 CurrentIrql; // r11
  unsigned __int8 WaitIrql; // di
  struct _KPRCB *CurrentPrcb; // rbx
  unsigned __int8 v13; // r14
  struct _KPRCB *v14; // rcx
  _DWORD *v15; // rdx
  struct _KPRCB *v16; // r10
  volatile unsigned __int8 *p_BlockState; // rdi
  PVOID *__attribute__((__org_arrdim(0,0))) v18; // r11
  unsigned __int64 v19; // r8
  ULONG v20; // er14
  _KMUTANT *v21; // rbx
  _LIST_ENTRY *Blink; // rdx
  UINT64 v23; // r9
  _KDUE_TIME_TYPE v24; // ecx
  unsigned __int64 v25; // rax
  int v26; // edi
  unsigned int v27; // ebx
  unsigned __int64 v28; // r15
  NTSTATUS v29; // er14
  PVOID *__attribute__((__org_arrdim(0,0))) v30; // r11
  struct _KPRCB *v32; // rdi
  _KPRCB *v33; // r13
  void *v34; // rdx
  volatile __int64 WaitStatus; // r15
  VOID *AbWaitObject; // rcx
  _KWAIT_BLOCK *v37; // rbx
  VOID *v38; // rdi
  _LIST_ENTRY *Flink; // rcx
  _LIST_ENTRY *v40; // rax
  __int64 ThreadTimerDelay; // rdx
  unsigned __int64 v42; // rcx
  unsigned __int64 v43; // rbx
  _KWAIT_STATUS_REGISTER v44; // al
  struct _KPRCB *v45; // rbx
  struct _KPRCB *v46; // rdi
  unsigned __int8 v48; // r10
  _DWORD *SchedulerAssist; // rcx
  _DWORD *v50; // rcx
  _DWORD *v51; // rcx
  _DWORD *v52; // rcx
  unsigned __int64 v53; // rax
  char v54; // r14
  _DEVICE_OBJECT *v55; // rax
  UINT64 v56; // rdx
  UINT8 *v57; // r8
  _DEVICE_OBJECT *v58; // rdi
  __int64 v59; // rdi
  __int64 v60; // rax
  unsigned int v61; // er8
  unsigned __int64 v62; // rdx
  __int64 v63; // r9
  unsigned __int64 v64; // rdi
  _KLOCK_ENTRY *v65; // rbx
  __int64 v66; // rax
  _KLOCK_ENTRY *v67; // rbx
  NTSTATUS v68; // ebx
  struct _KPRCB *v69; // rbx
  _DWORD *v70; // rcx
  int v71; // eax
  _BYTE *v72; // rax
  struct _KPRCB *v73; // rdi
  _DWORD *v74; // rcx
  int v75; // eax
  void **v76; // [rsp+20h] [rbp-A9h]
  UINT8 v77; // [rsp+40h] [rbp-89h]
  _KDUE_TIME_TYPE TimeoutType; // [rsp+44h] [rbp-85h]
  _KPRCB *Prcb; // [rsp+50h] [rbp-79h]
  unsigned __int64 v81; // [rsp+58h] [rbp-71h]
  __int64 v82; // [rsp+58h] [rbp-71h]
  __int64 v83; // [rsp+58h] [rbp-71h]
  LONGLONG DueTime; // [rsp+68h] [rbp-61h]
  UINT64 SpinCount; // [rsp+70h] [rbp-59h] BYREF
  UINT64 v87; // [rsp+78h] [rbp-51h] BYREF
  int v88; // [rsp+80h] [rbp-49h]
  int v89; // [rsp+84h] [rbp-45h]
  UINT64 v90; // [rsp+88h] [rbp-41h] BYREF
  UINT64 v91; // [rsp+90h] [rbp-39h] BYREF
  UINT64 v92; // [rsp+98h] [rbp-31h] BYREF
  PVOID v93; // [rsp+A0h] [rbp-29h] BYREF
  _SINGLE_LIST_ENTRY ReadyList; // [rsp+A8h] [rbp-21h] BYREF
  _ETHREAD *v95; // [rsp+B0h] [rbp-19h]
  __int64 v96; // [rsp+B8h] [rbp-11h]
  char v97[8]; // [rsp+C0h] [rbp-9h]

  WaitBlock = WaitBlockArray;
  HIDWORD(SpinCount) = WaitReason;
  DueTime = 0i64;
  if ( Count == 1 )
    return KeWaitForSingleObject(*Object, WaitReason, WaitMode, Alertable, Timeout);
  CurrentThread = (_ETHREAD *)KeGetCurrentThread();
  v95 = CurrentThread;
  if ( WaitBlockArray )
  {
    if ( Count <= 0x40 )
      goto LABEL_5;
LABEL_119:
    KeBugCheck(0xCu);
  }
  if ( Count > 3 )
    goto LABEL_119;
  WaitBlock = CurrentThread->Tcb.WaitBlock;
LABEL_5:
  if ( WaitType == WaitAll )
    return KiWaitForAllObjects(*(UINT64 *)&Count, Object, WaitReason, WaitMode, Alertable, Timeout, WaitBlock);
  v93 = 0i64;
  v96 = 0i64;
  v77 = _bittestandreset((signed __int32 *)&CurrentThread->Tcb.116, 2u);
  if ( !v77 )
  {
    CurrentIrql = KeGetCurrentIrql();
    __writecr8(2ui64);
    CurrentThread->Tcb.WaitIrql = CurrentIrql;
  }
  if ( Timeout )
  {
    if ( Timeout->HighPart >= 0 )
    {
      DueTime = Timeout->QuadPart;
      TimeoutType = DueTimeAbsolute;
    }
    else
    {
      TimeoutType = DueTimeRelative;
      DueTime = *(_QWORD *)&KUSER_SHARED_DATA.InterruptTime.LowPart
              - KUSER_SHARED_DATA.InterruptTimeBias
              - (Timeout->QuadPart
               + CurrentThread->Tcb.RelativeTimerBias);
    }
  }
  else
  {
    TimeoutType = DueTimeNone;
  }
  while ( 1 )
  {
    WaitIrql = CurrentThread->Tcb.WaitIrql;
    while ( 1 )
    {
      CurrentThread->Tcb.MiscFlags &= ~0x10u;
      CurrentThread->Tcb.WaitRegister.Flags = 0;
      CurrentThread->Tcb.WaitMode = WaitMode;
      if ( Alertable )
        CurrentThread->Tcb.MiscFlags |= 0x10u;
      CurrentPrcb = KeGetCurrentPrcb();
      LODWORD(SpinCount) = 0;
      while ( _interlockedbittestandset64((volatile signed __int32 *)&CurrentThread->Tcb.ThreadLock, 0i64) )
      {
        do
          KeYieldProcessorEx(&SpinCount);
        while ( CurrentThread->Tcb.ThreadLock );
        SchedulerAssist = CurrentPrcb->SchedulerAssist;
        if ( SchedulerAssist && CurrentPrcb->NestingLevel <= 1u )
          ++SchedulerAssist[6];
      }
      if ( !CurrentThread->Tcb.ApcState.KernelApcPending || CurrentThread->Tcb.SpecialApcDisable || WaitIrql )
        break;
      KiReleaseThreadLockSafe((INT64)CurrentThread);
      __writecr8(1ui64);
      KiDeliverApc(0, 0i64, 0i64);
      KeGetCurrentIrql();
      __writecr8(2ui64);
      CurrentThread->Tcb.WaitIrql = 0;
    }
    v13 = BYTE4(SpinCount);
    if ( !Alertable )
    {
      if ( (CurrentThread->Tcb.ApcState.UserApcPendingAll & 2) != 0 && WaitMode )
        goto LABEL_110;
      goto LABEL_19;
    }
    if ( CurrentThread->Tcb.Alerted[WaitMode] )
    {
      CurrentThread->Tcb.Alerted[WaitMode] = 0;
      v68 = 257;
      goto LABEL_111;
    }
    if ( WaitMode
      && (unsigned __int8 *)CurrentThread->Tcb.ApcState.ApcListHead[1].Flink != &CurrentThread->Tcb.ApcStateFill[16] )
    {
      CurrentThread->Tcb.ApcState.UserApcPendingAll |= 2u;
LABEL_110:
      v68 = 192;
LABEL_111:
      KiReleaseThreadLockSafe((INT64)CurrentThread);
      KiCheckForThreadDispatch(KeGetCurrentPrcb(), WaitIrql);
      return v68;
    }
    if ( CurrentThread->Tcb.Alerted[0] )
    {
      CurrentThread->Tcb.Alerted[0] = 0;
      v68 = 257;
      goto LABEL_111;
    }
LABEL_19:
    CurrentThread->Tcb.WaitBlockFill6[68] = 5;
    CurrentThread->Tcb.WaitReason = v13;
    CurrentThread->Tcb.WaitBlock[2].SpareLong = KUSER_SHARED_DATA.TickCount.LowPart;
    CurrentThread->Tcb.ThreadLock = 0i64;
    v14 = KeGetCurrentPrcb();
    v15 = v14->SchedulerAssist;
    if ( v15 && v14->NestingLevel <= 1u )
      --v15[6];
    v16 = KeGetCurrentPrcb();
    p_BlockState = &WaitBlock->BlockState;
    v18 = Object;
    v19 = 0i64;
    Prcb = v16;
    v20 = 0;
    v81 = 0i64;
    do
    {
      LODWORD(v87) = 0;
      v21 = (_KMUTANT *)v18[v20];
      *((_BYTE *)p_BlockState - 1) = 1;
      *p_BlockState = 4;
      *(_WORD *)(p_BlockState + 1) = v20;
      *(_QWORD *)(p_BlockState + 7) = CurrentThread;
      *(_QWORD *)(p_BlockState + 15) = v21;
      if ( _interlockedbittestandset(&v21->Header.Lock, 7u) )
      {
        do
        {
          do
            KeYieldProcessorEx(&v87);
          while ( (v21->Header.LockNV & 0x80u) != 0 );
        }
        while ( _interlockedbittestandset(&v21->Header.Lock, 7u) );
        v18 = Object;
        v19 = v81;
        v16 = Prcb;
      }
      if ( (v21->Header.Type & 0x7F) == 2 )
      {
        if ( (v21->MutantFlags & 2) != 0 )
        {
          _bittestandset64((__int64 *)&v19, v20);
          v81 = v19;
        }
        if ( v21->Header.SignalState > 0
          || CurrentThread == v21->OwnerThread && v21->Header.Size == v16->DpcRoutineActive )
        {
          if ( v21->Header.SignalState == 0x80000000 )
          {
            _InterlockedAnd(&v21->Header.Lock, 0xFFFFFF7F);
            v69 = KeGetCurrentPrcb();
            HIDWORD(v90) = 0;
            while ( _interlockedbittestandset64((volatile signed __int32 *)&CurrentThread->Tcb.ThreadLock, 0i64) )
            {
              do
                KeYieldProcessorEx((UINT64 *)((char *)&v90 + 4));
              while ( CurrentThread->Tcb.ThreadLock );
              v70 = v69->SchedulerAssist;
              if ( v70 && v69->NestingLevel <= 1u )
              {
                v71 = v70[6] + 1;
                v70[6] = v71;
              }
            }
            LODWORD(v76) = v20;
            KiSatisfyThreadWait(Prcb, &CurrentThread->Tcb, v77, WaitBlock, (UINT64)v76);
            RtlRaiseStatus(-1073741423);
          }
          v46 = KeGetCurrentPrcb();
          LODWORD(v90) = 0;
          while ( _interlockedbittestandset64((volatile signed __int32 *)&CurrentThread->Tcb.ThreadLock, 0i64) )
          {
            do
              KeYieldProcessorEx(&v90);
            while ( CurrentThread->Tcb.ThreadLock );
            v52 = v46->SchedulerAssist;
            if ( v52 && v46->NestingLevel <= 1u )
              ++v52[6];
          }
          v33 = Prcb;
          if ( (CurrentThread->Tcb.WaitRegister.Flags & 7) == 0 )
          {
            CurrentThread->Tcb.WaitStatus = v20;
            CurrentThread->Tcb.AbWaitObject = 0i64;
            if ( v21->Header.SignalState-- == 1 )
              KiWaitSatisfyMutant(v21, &CurrentThread->Tcb, Prcb);
          }
          goto LABEL_43;
        }
      }
      else if ( v21->Header.SignalState > 0 )
      {
        v32 = KeGetCurrentPrcb();
        HIDWORD(v91) = 0;
        while ( _interlockedbittestandset64((volatile signed __int32 *)&CurrentThread->Tcb.ThreadLock, 0i64) )
        {
          do
            KeYieldProcessorEx((UINT64 *)((char *)&v91 + 4));
          while ( CurrentThread->Tcb.ThreadLock );
          v50 = v32->SchedulerAssist;
          if ( v50 && v32->NestingLevel <= 1u )
            ++v50[6];
        }
        if ( (CurrentThread->Tcb.WaitRegister.Flags & 7) == 0 )
        {
          CurrentThread->Tcb.WaitStatus = v20;
          CurrentThread->Tcb.AbWaitObject = 0i64;
          if ( (v21->Header.Type & 7) == 1 )
          {
            v21->Header.SignalState = 0;
          }
          else if ( (v21->Header.Type & 0x7F) == 5 )
          {
            --v21->Header.SignalState;
          }
        }
        v33 = Prcb;
LABEL_43:
        _InterlockedAnd(&v21->Header.Lock, 0xFFFFFF7F);
        goto LABEL_44;
      }
      Blink = v21->Header.WaitListHead.Blink;
      if ( Blink->Flink != &v21->Header.WaitListHead )
LABEL_50:
        __fastfail(3u);
      *(_QWORD *)(p_BlockState - 9) = Blink;
      *(_QWORD *)(p_BlockState - 17) = &v21->Header.WaitListHead;
      Blink->Flink = (_LIST_ENTRY *)(p_BlockState - 17);
      v21->Header.WaitListHead.Blink = (_LIST_ENTRY *)(p_BlockState - 17);
      _InterlockedAnd(&v21->Header.Lock, 0xFFFFFF7F);
      ++v20;
      p_BlockState += 48;
    }
    while ( v20 < Count );
    v23 = DueTime;
    v24 = TimeoutType;
    v25 = DueTime;
    if ( TimeoutType != DueTimeRelative )
      break;
    ThreadTimerDelay = CurrentThread->Tcb.ThreadTimerDelay;
    v42 = *(_QWORD *)&KUSER_SHARED_DATA.InterruptTime.LowPart
        - CurrentThread->Tcb.RelativeTimerBias
        - KUSER_SHARED_DATA.InterruptTimeBias;
    v25 = DueTime;
    if ( CurrentThread->Tcb.WaitMode
      && !CurrentThread->Tcb.WaitBlock[3].SpareLong
      && !CurrentThread->Tcb.WaitIrql
      && !CurrentThread->Tcb.ApcState.InProgressFlags
      && (_DWORD)ThreadTimerDelay )
    {
      v25 = DueTime + ThreadTimerDelay;
    }
LABEL_53:
    if ( v42 > v25 )
      goto LABEL_77;
    v24 = TimeoutType;
LABEL_28:
    v26 = 0;
    CurrentThread->Tcb.WaitBlockCount = Count;
    v27 = 0;
    v28 = 0i64;
    if ( v19 )
    {
      do
      {
        _BitScanForward64(&v53, v19);
        v54 = v53;
        HIDWORD(v87) = v53;
        v82 = v19 & ~(1i64 << v53);
        v55 = (_DEVICE_OBJECT *)KeAbPreAcquire(v18[v53], 0i64, 0i64);
        v58 = v55;
        if ( !v55 )
          break;
        v28 |= 1i64 << v54;
        KeAbPreWait(v55, v56, v57);
        v19 = v82;
        v18 = Object;
        v59 = (__int64)v58 - *((_QWORD *)&v58[2].Queue.Wcb.DeviceObject - 2 * LOBYTE(v58->AttachedDevice));
        v60 = v27++;
        v97[v60] = (2
                  * (((((unsigned __int128)(v59 * (__int128)0x2AAAAAAAAAAAAAABi64) >> 64) & 0x8000000000000000ui64) != 0i64)
                   + ((__int64)((unsigned __int128)(v59 * (__int128)0x2AAAAAAAAAAAAAABi64) >> 64) >> 4))) | 1;
      }
      while ( v82 );
      CurrentThread = v95;
      v26 = 0;
      v23 = DueTime;
      v24 = TimeoutType;
    }
    v76 = &v93;
    v29 = KiCommitThreadWait(&CurrentThread->Tcb, WaitBlock, v24, v23);
    v30 = Object;
    if ( v93 )
    {
      v61 = 0;
      v62 = v28;
      if ( v28 )
      {
        while ( 1 )
        {
          _BitScanForward64((unsigned __int64 *)&v63, v62);
          v62 &= ~(1i64 << v63);
          v88 = v63;
          if ( v93 == Object[v63] )
            break;
          ++v61;
          if ( !v62 )
            goto LABEL_134;
        }
        v28 &= ~(1i64 << v63);
        v64 = v61;
        v65 = &KeGetCurrentThread()->LockEntries[(unsigned __int8)v97[v61] >> 1];
        KeAbPreAcquire(Object[v63], v65, 0i64);
        v65->AcquiredByte |= 1u;
        if ( v64 >= 6 )
          _report_rangecheckfailure();
        v30 = Object;
        v97[v64] = 0;
        v26 = 0;
      }
LABEL_134:
      CurrentThread->Tcb.AbWaitObject = 0i64;
    }
    for ( ; v28; ++v26 )
    {
      _BitScanForward64((unsigned __int64 *)&v66, v28);
      v89 = v66;
      v28 &= ~(1i64 << v66);
      v83 = (unsigned int)v66;
      if ( !v97[v26] )
        ++v26;
      v67 = &KeGetCurrentThread()->LockEntries[(unsigned __int8)v97[v26] >> 1];
      KeAbPreAcquire(v30[(unsigned int)v66], v67, 0i64);
      KeAbPostReleaseEx(Object[v83], v67);
      v30 = Object;
    }
    if ( v29 != 256 )
      return v29;
    v77 = 0;
    v48 = KeGetCurrentIrql();
    __writecr8(2ui64);
    CurrentThread->Tcb.WaitIrql = v48;
  }
  if ( TimeoutType == DueTimeNone )
    goto LABEL_28;
  if ( DueTime )
  {
    v42 = *(_QWORD *)&KUSER_SHARED_DATA.SystemTime.LowPart;
    goto LABEL_53;
  }
LABEL_77:
  v45 = KeGetCurrentPrcb();
  LODWORD(v91) = 0;
  while ( _interlockedbittestandset64((volatile signed __int32 *)&CurrentThread->Tcb.ThreadLock, 0i64) )
  {
    do
      KeYieldProcessorEx(&v91);
    while ( CurrentThread->Tcb.ThreadLock );
    v51 = v45->SchedulerAssist;
    if ( v51 && v45->NestingLevel <= 1u )
      ++v51[6];
  }
  v33 = Prcb;
  if ( (CurrentThread->Tcb.WaitRegister.Flags & 7) == 0 )
  {
    CurrentThread->Tcb.WaitStatus = 258i64;
    CurrentThread->Tcb.AbWaitObject = 0i64;
  }
LABEL_44:
  CurrentThread->Tcb.WaitBlockFill6[68] = 2;
  CurrentThread->Tcb.ThreadLock = 0i64;
  v34 = KeGetCurrentPrcb()->SchedulerAssist;
  WaitStatus = CurrentThread->Tcb.WaitStatus;
  AbWaitObject = CurrentThread->Tcb.AbWaitObject;
  if ( AbWaitObject )
  {
    CurrentThread->Tcb.AbWaitObject = 0i64;
    v72 = KeAbPreAcquire(AbWaitObject, 0i64, 1ui64);
    if ( v72 )
      v72[26] |= 1u;
  }
  if ( v20 )
  {
    v37 = &WaitBlock[(unsigned __int8)v20];
    do
    {
      if ( WaitBlock->BlockState < 5u )
      {
        v38 = WaitBlock->Object;
        KiAcquireKobjectLockSafe(v38);
        if ( WaitBlock->BlockState == 4 )
        {
          Flink = WaitBlock->WaitListEntry.Flink;
          v40 = WaitBlock->WaitListEntry.Blink;
          if ( (PKWAIT_BLOCK)WaitBlock->WaitListEntry.Flink->Blink != WaitBlock || (PKWAIT_BLOCK)v40->Flink != WaitBlock )
            goto LABEL_50;
          v40->Flink = Flink;
          Flink->Blink = v40;
        }
        _InterlockedAnd((volatile signed __int32 *)v38, 0xFFFFFF7F);
      }
      ++WaitBlock;
    }
    while ( WaitBlock != v37 );
  }
  v43 = CurrentThread->Tcb.WaitIrql;
  v44.Flags = (unsigned __int8)CurrentThread->Tcb.WaitRegister;
  if ( (v44.Flags & 0x38) == 0 )
  {
    if ( v77 )
      KiCheckForThreadDispatch(v33, (unsigned __int8)v43);
    else
      __writecr8(v43);
    return WaitStatus;
  }
  if ( (v44.Flags & 0x18) != 0 )
  {
    if ( (v44.Flags & 8) != 0 )
      _interlockedbittestandset((volatile signed __int32 *)&CurrentThread->Tcb.116 + 1, 0xCu);
    ReadyList.Next = 0i64;
    v73 = KeGetCurrentPrcb();
    LODWORD(v92) = 0;
    while ( _interlockedbittestandset64((volatile signed __int32 *)&v33->PrcbLock, 0i64) )
    {
      do
        KeYieldProcessorEx(&v92);
      while ( v33->PrcbLock );
      v74 = v73->SchedulerAssist;
      if ( v74 && v73->NestingLevel <= 1u )
      {
        v75 = v74[6] + 1;
        v74[6] = v75;
      }
    }
    if ( !v33->NextThread )
      KiSelectNextThread(v33, &ReadyList);
    _InterlockedAnd64((volatile signed __int64 *)&v33->PrcbLock, 0i64);
    KiProcessDeferredReadyList(v33, &ReadyList, (unsigned __int8)v43);
    return WaitStatus;
  }
  LOBYTE(v34) = 1;
  KiCheckForThreadDispatch(v33, (UINT64)v34);
  KiDeliverApc(0, 0i64, 0i64);
  __writecr8(0i64);
  return WaitStatus;
}

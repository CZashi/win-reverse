NTSTATUS __stdcall NtWaitForWorkViaWorkerFactory(
        VOID *WorkerFactoryHandle,
        _FILE_IO_COMPLETION_INFORMATION *IoCompletionInformation,
        UINT64 Count,
        UINT64 *NumEntriesRemoved,
        _WORKER_FACTORY_DEFERRED_WORK *DeferredWork)
{
  unsigned int v5; // er15
  KPROCESSOR_MODE PreviousMode; // si
  __int64 v8; // rcx
  UINT8 *v9; // r8
  int v10; // er14
  PVOID v11; // rbx
  unsigned __int8 CurrentIrql; // r10
  _KSPIN_LOCK_QUEUE *v13; // rdx
  _QWORD *v14; // rdx
  __int64 v15; // rcx
  char *v16; // rsi
  _FILE_IO_COMPLETION_INFORMATION *v17; // rcx
  UINT64 *v18; // rdi
  _KSPIN_LOCK_QUEUE *volatile v19; // rax
  _PORT_MESSAGE *v20; // r15
  int v21; // edi
  HANDLE v22; // rcx
  _ETHREAD *v23; // rax
  unsigned int v24; // edi
  signed __int32 v25; // esi
  _ALPC_PORT *v26; // rbx
  _KEVENT *p_DesiredReferenceNoEvent; // rcx
  VOID *v28; // r9
  $CDF3C50EAE3A7D5A2EBBEF607A217773 *v29; // r13
  __int64 v30; // rbx
  _KPRCB *CurrentPrcb; // r10
  int SignalState; // eax
  int v33; // ecx
  _KWAIT_BLOCK *Flink; // rax
  _KPRCB *v35; // rbx
  _KWAIT_BLOCK *v36; // r12
  __int64 v37; // rax
  _KWAIT_BLOCK **Blink; // rcx
  unsigned __int8 WaitType; // al
  volatile __int64 WaitKey; // r14
  _ETHREAD *Thread; // rsi
  char v42; // di
  _KWAIT_STATUS_REGISTER v43; // al
  int v44; // ecx
  _KWAIT_STATUS_REGISTER v45; // al
  bool v46; // zf
  _KWAIT_STATUS_REGISTER v47; // al
  _DISPATCHER_HEADER *volatile Queue; // rcx
  void *SystemArgument1; // rdi
  _LIST_ENTRY *v51; // rdx
  _LIST_ENTRY *v52; // rcx
  volatile unsigned __int8 State; // al
  __int64 v54; // rcx
  _SINGLE_LIST_ENTRY *v55; // rax
  _KQUEUE *NotificationQueue; // rbx
  _LIST_ENTRY *p_WaitListHead; // rsi
  UINT8 v58; // r15
  struct _KPRCB *v59; // r14
  _ETHREAD *v60; // rdi
  int v61; // er8
  _LIST_ENTRY *v62; // rdx
  _ETHREAD *v63; // rcx
  __int64 v64; // rbx
  UINT8 *v65; // r8
  unsigned __int8 v66; // r10
  _KSPIN_LOCK_QUEUE *v67; // rdx
  bool v68; // al
  int *v69; // rdi
  _ETHREAD *v70; // r15
  unsigned int v71; // ecx
  _QWORD *v72; // rbx
  _ETHREAD **v73; // rax
  __int64 v74; // rax
  unsigned int v75; // edi
  VOID **v76; // rbx
  int v77; // ecx
  __int64 v78; // rbx
  int v79; // edx
  _KSPIN_LOCK_QUEUE *volatile Next; // rax
  PVOID *Object; // [rsp+20h] [rbp-208h]
  KPROCESSOR_MODE v83; // [rsp+40h] [rbp-1E8h]
  _KPRCB *Prcb; // [rsp+48h] [rbp-1E0h]
  int v85; // [rsp+50h] [rbp-1D8h]
  _KLOCK_QUEUE_HANDLE LockQueue; // [rsp+58h] [rbp-1D0h] BYREF
  _QWORD *v87; // [rsp+70h] [rbp-1B8h]
  UINT64 NumEntriesRemoveda; // [rsp+78h] [rbp-1B0h] BYREF
  UINT64 *v89; // [rsp+80h] [rbp-1A8h]
  PVOID v90; // [rsp+88h] [rbp-1A0h] BYREF
  _FILE_IO_COMPLETION_INFORMATION *v91; // [rsp+90h] [rbp-198h]
  PVOID v92; // [rsp+98h] [rbp-190h] BYREF
  int *v93; // [rsp+A0h] [rbp-188h]
  UINT64 *v94; // [rsp+A8h] [rbp-180h]
  _LIST_ENTRY **EntryArray; // [rsp+B0h] [rbp-178h]
  _ALPC_DEFERRED_MESSAGE_CONTEXT MessageContext[4]; // [rsp+B8h] [rbp-170h] BYREF
  HANDLE Handle[2]; // [rsp+C8h] [rbp-160h]
  UINT64 Flags; // [rsp+D8h] [rbp-150h]
  UINT64 SpinCount; // [rsp+E0h] [rbp-148h] BYREF
  UINT64 v100; // [rsp+E8h] [rbp-140h] BYREF
  _FILE_IO_COMPLETION_INFORMATION *IoCompletionInformationa; // [rsp+F0h] [rbp-138h]
  VOID *v102; // [rsp+F8h] [rbp-130h]
  _ALPC_DISPATCH_CONTEXT DispatchContext; // [rsp+100h] [rbp-128h] BYREF
  _KWAIT_BLOCK *v104; // [rsp+140h] [rbp-E8h]
  __int64 v105; // [rsp+148h] [rbp-E0h]
  _ETHREAD *CurrentThread; // [rsp+150h] [rbp-D8h]
  __int128 v107[8]; // [rsp+160h] [rbp-C8h] BYREF

  v94 = NumEntriesRemoved;
  v5 = Count;
  v85 = Count;
  IoCompletionInformationa = IoCompletionInformation;
  v93 = (int *)WorkerFactoryHandle;
  v91 = IoCompletionInformation;
  v89 = NumEntriesRemoved;
  *(_OWORD *)MessageContext = 0i64;
  *(_OWORD *)Handle = 0i64;
  Flags = 0i64;
  memset(&LockQueue, 0, sizeof(LockQueue));
  memset(v107, 0, sizeof(v107));
  LODWORD(NumEntriesRemoveda) = 0;
  v102 = 0i64;
  CurrentThread = (_ETHREAD *)KeGetCurrentThread();
  PreviousMode = CurrentThread->Tcb.PreviousMode;
  v83 = PreviousMode;
  EntryArray = (_LIST_ENTRY **)v107;
  if ( (unsigned int)(Count - 1) > 0x7FFFFFE )
  {
    v10 = -1073741811;
    goto LABEL_164;
  }
  if ( PreviousMode )
  {
    ProbeForWrite(IoCompletionInformation, 32 * Count, 8u);
    v8 = (__int64)v94;
    if ( (unsigned __int64)v94 >= 0x7FFFFFFF0000i64 )
      v8 = 0x7FFFFFFF0000i64;
    *(_DWORD *)v8 = *(_DWORD *)v8;
    if ( ((unsigned __int8)DeferredWork & 7) != 0 )
      ExRaiseDatatypeMisalignment();
    if ( (unsigned __int64)&DeferredWork[1] > 0x7FFFFFFF0000i64 || &DeferredWork[1] < DeferredWork )
      MEMORY[0x7FFFFFFF0000] = 0;
    *(_OWORD *)Handle = *(_OWORD *)&DeferredWork->AlpcSendMessage;
    Flags = *(_QWORD *)&DeferredWork->AlpcSendMessageFlags;
  }
  else
  {
    *(_OWORD *)Handle = *(_OWORD *)&DeferredWork->AlpcSendMessage;
    Flags = *(_QWORD *)&DeferredWork->AlpcSendMessageFlags;
  }
  v90 = 0i64;
  v10 = ObReferenceObjectByHandle(WorkerFactoryHandle, 2u, ExpWorkerFactoryObjectType, PreviousMode, &v90, 0i64);
  v11 = v90;
  v87 = v90;
  v102 = v90;
  if ( v10 >= 0 )
  {
    if ( v5 > 0x10 )
    {
      EntryArray = (_LIST_ENTRY **)ExAllocatePoolWithTag(NonPagedPoolNx, 8 * v5, 0x656E6F4Eu);
      if ( !EntryArray )
      {
        v5 = 16;
        v85 = 16;
        EntryArray = (_LIST_ENTRY **)v107;
      }
    }
    LockQueue.LockQueue.Lock = (unsigned __int64 *volatile)*((_QWORD *)v11 + 2);
    LockQueue.LockQueue.Next = 0i64;
    CurrentIrql = KeGetCurrentIrql();
    __writecr8(2ui64);
    LockQueue.OldIrql = CurrentIrql;
    v13 = (_KSPIN_LOCK_QUEUE *)_InterlockedExchange64((volatile __int64 *)LockQueue.LockQueue.Lock, (__int64)&LockQueue);
    if ( v13 )
      KxWaitForLockOwnerShip(&LockQueue.LockQueue, v13, v9);
    v14 = v87;
    v15 = v87[2];
    if ( *(_BYTE *)(v15 + 33) )
    {
      KeReleaseInStackQueuedSpinLockFromDpcLevel(&LockQueue);
      __writecr8(LockQueue.OldIrql);
      v10 = 128;
      goto LABEL_164;
    }
    v16 = (char *)v90;
    v93 = (int *)((char *)v90 + 312);
    if ( (*((_DWORD *)v90 + 78) & 0x200) != 0 )
    {
      ExpLeaveWorkerFactoryAwayMode((_EX_WORKER_FACTORY *)v90);
      v14 = v87;
      v15 = v87[2];
    }
    ++*(_DWORD *)(v15 + 28);
    v17 = (_FILE_IO_COMPLETION_INFORMATION *)(v16 + 284);
    v91 = (_FILE_IO_COMPLETION_INFORMATION *)(v16 + 284);
    v18 = (UINT64 *)(v16 + 288);
    v89 = (UINT64 *)(v16 + 288);
    while ( 1 )
    {
      if ( LODWORD(v17->KeyContext) < *(_DWORD *)v18 || *(_BYTE *)(v14[2] + 33i64) )
      {
        v10 = 258;
LABEL_137:
        --*(_DWORD *)(v87[2] + 28i64);
        if ( v10 == 258 )
        {
          --*(_DWORD *)v18;
          --*((_DWORD *)v16 + 73);
          ExpRemoveCurrentThreadFromThreadHistory((_EX_WORKER_FACTORY *)v16);
          v69 = v93;
        }
        else
        {
          v69 = v93;
          if ( (*v93 & 7) != 4 )
          {
            v70 = (_ETHREAD *)KeGetCurrentThread();
            v71 = 0;
            v16 = (char *)v90;
            v72 = (char *)v90 + 72;
            v73 = (_ETHREAD **)((char *)v90 + 72);
            while ( *v73 != v70 )
            {
              ++v71;
              ++v73;
              if ( v71 >= 4 )
              {
                ObfReferenceObjectWithTag(v70, 0x746C6644ui64);
                v74 = 0i64;
                while ( *v72 )
                {
                  v74 = (unsigned int)(v74 + 1);
                  ++v72;
                  if ( (unsigned int)v74 >= 4 )
                  {
                    v75 = *v69 & 7;
                    v76 = (VOID **)&v16[8 * v75];
                    ObfDereferenceObjectWithTag(v76[9], 0x746C6644ui64);
                    v76[9] = v70;
                    v77 = ((_BYTE)v75 + 1) & 3;
                    v69 = v93;
                    *v93 = *v93 & 0xFFFFFFF8 | v77;
                    goto LABEL_148;
                  }
                }
                *(_QWORD *)&v16[8 * v74 + 72] = v70;
                break;
              }
            }
          }
        }
LABEL_148:
        v78 = v87[2];
        if ( *(_DWORD *)v89 < LODWORD(v91->KeyContext) && !*(_DWORD *)(v78 + 28) )
        {
          if ( *((_DWORD *)v16 + 77) )
          {
            v79 = *v69 | 0x200;
            *v69 = v79;
            if ( !*(_DWORD *)(*(_QWORD *)(v78 + 8) + 4i64) )
            {
              if ( (v79 & 0x400) == 0 )
              {
                *v69 = v79 | 0x400;
                ObfReferenceObjectWithTag(v16, 0x746C6644ui64);
                KeRegisterObjectNotification(
                  *(VOID **)(v78 + 8),
                  &ExpWorkerFactoryManagerQueue,
                  (_KWAIT_BLOCK *)(v16 + 520));
              }
              goto LABEL_156;
            }
          }
          ExpWorkerFactoryCheckCreate((_EX_WORKER_FACTORY *)v16, &LockQueue, 0);
LABEL_161:
          if ( !v10 )
            *(_DWORD *)v94 = NumEntriesRemoveda;
          break;
        }
LABEL_156:
        _m_prefetchw(&LockQueue);
        Next = LockQueue.LockQueue.Next;
        if ( LockQueue.LockQueue.Next )
        {
LABEL_159:
          LockQueue.LockQueue.Next = 0i64;
          _InterlockedXor64((volatile signed __int64 *)&Next->Lock, 1ui64);
        }
        else if ( (_KLOCK_QUEUE_HANDLE *)_InterlockedCompareExchange64(
                                           (volatile signed __int64 *)LockQueue.LockQueue.Lock,
                                           0i64,
                                           (signed __int64)&LockQueue) != &LockQueue )
        {
          Next = KxWaitForLockChainValid(&LockQueue.LockQueue);
          goto LABEL_159;
        }
        __writecr8(LockQueue.OldIrql);
        goto LABEL_161;
      }
      _m_prefetchw(&LockQueue);
      v19 = LockQueue.LockQueue.Next;
      if ( !LockQueue.LockQueue.Next )
      {
        if ( (_KLOCK_QUEUE_HANDLE *)_InterlockedCompareExchange64(
                                      (volatile signed __int64 *)LockQueue.LockQueue.Lock,
                                      0i64,
                                      (signed __int64)&LockQueue) == &LockQueue )
          goto LABEL_29;
        v19 = KxWaitForLockChainValid(&LockQueue.LockQueue);
      }
      LockQueue.LockQueue.Next = 0i64;
      _InterlockedXor64((volatile signed __int64 *)&v19->Lock, 1ui64);
LABEL_29:
      __writecr8(LockQueue.OldIrql);
      if ( (Flags & 0x100000000i64) == 0 )
        goto LABEL_126;
      v20 = (_PORT_MESSAGE *)Handle[0];
      v21 = Flags;
      v22 = Handle[1];
      memset(&DispatchContext, 0, sizeof(DispatchContext));
      v23 = (_ETHREAD *)KeGetCurrentThread();
      --v23->Tcb.KernelApcDisable;
      *(_OWORD *)MessageContext = 0i64;
      v24 = v21 & 0xFFFF0000;
      if ( (v24 & 0x20000) != 0 )
        goto LABEL_121;
      v92 = 0i64;
      if ( ObReferenceObjectByHandle(v22, 1u, AlpcPortObjectType, v83, &v92, 0i64) < 0 )
        goto LABEL_121;
      if ( (v24 & 0x40000) != 0 )
      {
        v25 = _InterlockedIncrement((volatile signed __int32 *)v92 + 101);
        v26 = (_ALPC_PORT *)v92;
        if ( !*((_QWORD *)v92 + 51) )
          goto LABEL_41;
        ExAcquirePushLockExclusiveEx((_EX_PUSH_LOCK *)v92 + 44, 0i64);
        p_DesiredReferenceNoEvent = &v26->ReferenceNoWait->DesiredReferenceNoEvent;
        if ( p_DesiredReferenceNoEvent && v25 == p_DesiredReferenceNoEvent[1].Header.LockNV )
          KeSetEvent(p_DesiredReferenceNoEvent, 0, 0);
        if ( (_InterlockedExchangeAdd64((volatile signed __int64 *)&v26->PortObjectLock, 0xFFFFFFFFFFFFFFFFui64) & 6) == 2 )
          ExfTryToWakePushLock(&v26->PortObjectLock);
        KeAbPostRelease(&v26->PortObjectLock);
      }
      v26 = (_ALPC_PORT *)v92;
LABEL_41:
      DispatchContext.PortObject = v26;
      DispatchContext.Flags = v24 | 4;
      memset(&DispatchContext.TargetThread, 0, 24);
      if ( AlpcpSendMessage(&DispatchContext, v20, 0i64, v83) >= 0 )
      {
        *(_QWORD *)MessageContext = DispatchContext.TargetPort;
        *(_QWORD *)&MessageContext[2] = DispatchContext.PortObject;
        if ( DispatchContext.TargetPort )
        {
          if ( DispatchContext.SignalCompletion )
          {
            LOBYTE(v28) = 1;
            AlpcpQueueIoCompletionPort(
              DispatchContext.TargetPort,
              DispatchContext.PostedToCompletionList,
              1u,
              (UINT64)v28);
          }
          else
          {
            LODWORD(Object) = 1;
            KeReleaseSemaphoreEx(DispatchContext.TargetPort->Semaphore, 1i64, 1i64, v28, (UINT64)Object);
          }
        }
        else
        {
          if ( DispatchContext.TargetThread )
          {
            v29 = &DispatchContext.TargetThread->1160;
            v30 = KeGetCurrentIrql();
            v105 = v30;
            __writecr8(2ui64);
            CurrentPrcb = KeGetCurrentPrcb();
            Prcb = CurrentPrcb;
            LODWORD(SpinCount) = 0;
            if ( _interlockedbittestandset(&v29->KeyedWaitSemaphore.Header.Lock, 7u) )
            {
              do
              {
                do
                  KeYieldProcessorEx(&SpinCount);
                while ( (v29->KeyedWaitSemaphore.Header.LockNV & 0x80u) != 0 );
              }
              while ( _interlockedbittestandset(&v29->KeyedWaitSemaphore.Header.Lock, 7u) );
              CurrentPrcb = Prcb;
            }
            SignalState = v29->KeyedWaitSemaphore.Header.SignalState;
            v33 = SignalState + 1;
            if ( SignalState + 1 > v29->KeyedWaitSemaphore.Limit || v33 < SignalState )
            {
              KiReleaseKobjectLock(&v29->KeyedWaitSemaphore.Header.LockNV);
              __writecr8((unsigned __int8)v30);
              RtlRaiseStatus(-1073741753);
            }
            v29->KeyedWaitSemaphore.Header.SignalState = v33;
            if ( SignalState
              || (Flink = (_KWAIT_BLOCK *)v29->KeyedWaitSemaphore.Header.WaitListHead.Flink,
                  Flink == (_KWAIT_BLOCK *)&v29->AlpcWaitSemaphore.Header.WaitListHead) )
            {
              v35 = Prcb;
LABEL_57:
              _InterlockedAnd(&v29->KeyedWaitSemaphore.Header.Lock, 0xFFFFFF7F);
              KiExitDispatcher(v35, 1ui64, AdjustUnwait, 1i64, v105);
              goto LABEL_121;
            }
            while ( 2 )
            {
              v36 = Flink;
              v37 = (__int64)Flink->WaitListEntry.Flink;
              v104 = (_KWAIT_BLOCK *)v37;
              Blink = (_KWAIT_BLOCK **)v36->WaitListEntry.Blink;
              if ( *(_KWAIT_BLOCK **)(v37 + 8) != v36 || *Blink != v36 )
LABEL_135:
                __fastfail(3u);
              *Blink = (_KWAIT_BLOCK *)v37;
              *(_QWORD *)(v37 + 8) = Blink;
              WaitType = v36->WaitType;
              if ( WaitType == 1 )
              {
                WaitKey = v36->WaitKey;
                Thread = v36->Thread;
                v42 = 0;
                HIDWORD(SpinCount) = 0;
                while ( _interlockedbittestandset64((volatile signed __int32 *)&Thread->Tcb.ThreadLock, 0i64) )
                {
                  do
                    KeYieldProcessorEx((UINT64 *)((char *)&SpinCount + 4));
                  while ( Thread->Tcb.ThreadLock );
                }
                if ( Thread->Tcb.WaitBlockFill6[68] == 5 )
                {
                  v43.Flags = (unsigned __int8)Thread->Tcb.WaitRegister;
                  v44 = v43.Flags & 7;
                  if ( v44 == 1 || v44 == 4 )
                  {
                    Queue = Thread->Tcb.Queue;
                    if ( Queue )
                    {
                      if ( (Queue->Type & 0x7F) == 21 )
                      {
                        Thread->Tcb.QueuePriority = (unsigned __int8)Thread->Tcb.QueuePriority;
                        _InterlockedIncrement((volatile signed __int32 *)&Queue[22].WaitListHead + (unsigned int)Thread->Tcb.QueuePriority);
                      }
                      else
                      {
                        _InterlockedIncrement((volatile signed __int32 *)&Queue[1].WaitListHead.Blink);
                      }
                    }
                    SystemArgument1 = Thread->Tcb.SchedulerApc.SystemArgument1;
                    if ( SystemArgument1 )
                    {
                      LODWORD(v100) = 0;
                      while ( _interlockedbittestandset64((volatile signed __int32 *)SystemArgument1 + 7940, 0i64) )
                      {
                        do
                          KeYieldProcessorEx(&v100);
                        while ( *((_QWORD *)SystemArgument1 + 3970) );
                      }
                      if ( Thread->Tcb.SchedulerApc.SystemArgument1 )
                      {
                        v51 = Thread->Tcb.WaitListEntry.Flink;
                        v52 = Thread->Tcb.WaitListEntry.Blink;
                        if ( ($6BB4B88B9A35E741C1040E182991A89E *)v51->Blink != &Thread->Tcb.216
                          || ($6BB4B88B9A35E741C1040E182991A89E *)v52->Flink != &Thread->Tcb.216 )
                        {
                          goto LABEL_135;
                        }
                        v52->Flink = v51;
                        v51->Blink = v52;
                        Thread->Tcb.SchedulerApc.SystemArgument1 = 0i64;
                      }
                      _InterlockedAnd64((volatile signed __int64 *)SystemArgument1 + 3970, 0i64);
                    }
                    State = Thread->Tcb.State;
                    if ( State == 1 )
                      Thread->Tcb.MiscFlags |= 2u;
                    if ( State == 5 )
                    {
                      v54 = KUSER_SHARED_DATA.TickCount.LowPart - Thread->Tcb.WaitBlock[2].SpareLong;
                      if ( Thread->Tcb.WaitMode )
                        Thread->Tcb.UserWaitTime += v54;
                      else
                        Thread->Tcb.KernelWaitTime += v54;
                    }
                    Thread->Tcb.WaitBlockFill6[68] = 7;
                    v35 = Prcb;
                    v55 = Prcb->DeferredReadyListHead.Next;
                    Thread->Tcb.WaitListEntry.Flink = (_LIST_ENTRY *)v55;
                    Prcb->DeferredReadyListHead.Next = (_SINGLE_LIST_ENTRY *)&Thread->Tcb.216;
                    Thread->Tcb.WaitStatus = WaitKey;
                    Thread->Tcb.AbWaitObject = 0i64;
                    v42 = 1;
                  }
                  else
                  {
                    if ( (Thread->Tcb.WaitRegister.Flags & 7) == 0 )
                    {
                      v45.Flags = v43.Flags & 0xF8 | 2;
                      Thread->Tcb.WaitRegister = v45;
                      Thread->Tcb.WaitStatus = WaitKey;
                      Thread->Tcb.AbWaitObject = 0i64;
                      v42 = 1;
                      v36->BlockState = 0;
                      goto LABEL_71;
                    }
                    if ( v44 == 5 )
                    {
                      v47.Flags = v43.Flags & 0xF8 | 6;
                      Thread->Tcb.WaitRegister = v47;
                      goto LABEL_71;
                    }
                    v35 = Prcb;
                    if ( v44 == 3 )
                      v36->BlockState = 2;
                  }
                }
                else
                {
LABEL_71:
                  v35 = Prcb;
                }
                Thread->Tcb.ThreadLock = 0i64;
                ++v36->BlockState;
                if ( v42 )
                {
                  v46 = v29->KeyedWaitSemaphore.Header.SignalState-- == 1;
                  if ( v46 )
                    goto LABEL_57;
                }
              }
              else if ( WaitType == 2 )
              {
                v36->BlockState = 5;
                NotificationQueue = v36->NotificationQueue;
                v36->WaitListEntry.Flink = 0i64;
                p_WaitListHead = &NotificationQueue->Header.WaitListHead;
                v58 = 0;
                KeGetCurrentIrql();
                __writecr8(2ui64);
                v59 = KeGetCurrentPrcb();
                v60 = v59->CurrentThread;
                KiAcquireKobjectLockSafe(NotificationQueue);
                if ( p_WaitListHead->Flink != p_WaitListHead
                  && NotificationQueue->CurrentCount < NotificationQueue->MaximumCount
                  && ((_KQUEUE *)v60->Tcb.Queue != NotificationQueue || v60->Tcb.WaitReason != 15) )
                {
                  v58 = KiWakeQueueWaiter(v59, NotificationQueue, (INT64)v36);
                }
                if ( !v58 )
                {
                  v61 = NotificationQueue->Header.SignalState;
                  NotificationQueue->Header.SignalState = v61 + 1;
                  v62 = NotificationQueue->EntryListHead.Blink;
                  if ( v62->Flink != &NotificationQueue->EntryListHead )
                    goto LABEL_135;
                  v36->WaitListEntry.Flink = &NotificationQueue->EntryListHead;
                  v36->WaitListEntry.Blink = v62;
                  v62->Flink = &v36->WaitListEntry;
                  NotificationQueue->EntryListHead.Blink = &v36->WaitListEntry;
                  if ( !v61 && p_WaitListHead->Flink != p_WaitListHead )
                    KiWakeOtherQueueWaiters(v59, NotificationQueue);
                }
                _InterlockedAnd(&NotificationQueue->Header.Lock, 0xFFFFFF7F);
                v46 = v29->KeyedWaitSemaphore.Header.SignalState-- == 1;
                v35 = Prcb;
                if ( v46 )
                  goto LABEL_57;
              }
              else
              {
                KiTryUnwaitThread(CurrentPrcb, v36, 256i64, 0i64);
                v35 = Prcb;
              }
              Flink = v104;
              if ( v104 == (_KWAIT_BLOCK *)&v29->AlpcWaitSemaphore.Header.WaitListHead )
                goto LABEL_57;
              CurrentPrcb = Prcb;
              continue;
            }
          }
          if ( (DispatchContext.DirectEvent.Value & 1) != 0 )
          {
            if ( (DispatchContext.DirectEvent.Value & 0xFFFFFFFFFFFFFFFCui64) != 0 )
            {
              KeSetEvent((PRKEVENT)(DispatchContext.DirectEvent.Value & 0xFFFFFFFFFFFFFFFCui64), 0, 1u);
              if ( (DispatchContext.DirectEvent.Value & 2) != 0 )
                HalPutDmaAdapter((PADAPTER_OBJECT)(DispatchContext.DirectEvent.Value & 0xFFFFFFFFFFFFFFFCui64));
            }
            DispatchContext.DirectEvent.Value = 0i64;
          }
        }
      }
      else
      {
        HalPutDmaAdapter((PADAPTER_OBJECT)DispatchContext.PortObject);
      }
LABEL_121:
      v63 = (_ETHREAD *)KeGetCurrentThread();
      v46 = v63->Tcb.KernelApcDisable++ == -1;
      if ( v46
        && ($F25F8C4BA33AF922A5F1AF68CD89DDDF *)v63->Tcb.ApcState.ApcListHead[0].Flink != &v63->Tcb.152
        && !v63->Tcb.SpecialApcDisable )
      {
        KiCheckForKernelApcDelivery();
      }
      v18 = v89;
      v5 = v85;
LABEL_126:
      v64 = (__int64)v87;
      v10 = (unsigned int)IoRemoveIoCompletion(
                            *(VOID **)(v87[2] + 8i64),
                            IoCompletionInformationa,
                            EntryArray,
                            v5,
                            &NumEntriesRemoveda,
                            v83,
                            0i64,
                            1u);
      if ( (Flags & 0x100000000i64) != 0 )
      {
        AlpciDestroyDeferredMessageContext(MessageContext);
        HIDWORD(Flags) &= ~1u;
      }
      LockQueue.LockQueue.Lock = *(unsigned __int64 *volatile *)(v64 + 16);
      LockQueue.LockQueue.Next = 0i64;
      v66 = KeGetCurrentIrql();
      __writecr8(2ui64);
      LockQueue.OldIrql = v66;
      v67 = (_KSPIN_LOCK_QUEUE *)_InterlockedExchange64(
                                   (volatile __int64 *)LockQueue.LockQueue.Lock,
                                   (__int64)&LockQueue);
      if ( v67 )
        KxWaitForLockOwnerShip(&LockQueue.LockQueue, v67, v65);
      v16 = (char *)v90;
      if ( v10 != 258 )
        goto LABEL_137;
      v68 = ExpWorkerFactoryWantsToCreate((_EX_WORKER_FACTORY *)v90, WFCCWorkerLoop);
      v17 = v91;
      if ( !v68 && *(_DWORD *)v18 > *((_DWORD *)v16 + 70) && CurrentThread->IrpList.Flink == &CurrentThread->IrpList )
        goto LABEL_137;
      v14 = v87;
    }
  }
LABEL_164:
  if ( EntryArray != (_LIST_ENTRY **)v107 )
    ExFreeHeapPool((ULONG_PTR)EntryArray);
  if ( v102 )
    ObfDereferenceObjectWithTag(v102, 0x746C6644ui64);
  if ( (Flags & 0x100000000i64) != 0 )
    NtAlpcSendWaitReceivePort(Handle[1], (unsigned int)Flags, (_PORT_MESSAGE *)Handle[0], 0i64, 0i64, 0i64, 0i64, 0i64);
  return v10;
}

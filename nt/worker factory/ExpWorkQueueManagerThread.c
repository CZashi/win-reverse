VOID __stdcall ExpWorkQueueManagerThread()
{
  __int64 v0; // rcx
  char v1; // r12
  __int64 v2; // rdi
  _WORK_QUEUE_ITEM *v3; // r15
  _QWORD *PoolWithTag; // r14
  _ETHREAD *CurrentThread; // rbx
  char v6; // r13
  UINT64 v7; // rsi
  NTSTATUS v8; // eax
  _KDPC *v9; // r9
  signed int v10; // ebx
  __int64 v11; // r10
  __int64 v12; // rsi
  __int64 v13; // rdx
  int PoolDelayed; // eax
  _EX_WORK_QUEUE *v15; // rcx
  __int64 v16; // r8
  _KDPC *v17; // rcx
  __int64 j; // r8
  _KPRIQUEUE *v19; // rcx
  _ENODE *v20; // rcx
  NTSTATUS v21; // eax
  int v22; // eax
  __int64 i; // rbx
  __int64 v24; // rcx
  UINT64 v25; // r8
  __int64 v26; // rbx
  _KDPC *v27; // rsi
  NTSTATUS WorkerThread; // eax
  char v29; // [rsp+48h] [rbp-29h]
  UINT16 Count; // [rsp+4Ch] [rbp-25h] BYREF
  _ETHREAD *Thread; // [rsp+50h] [rbp-21h]
  UINT64 v32; // [rsp+58h] [rbp-19h]
  _EXT_SET_PARAMETERS_V0 Parameters; // [rsp+60h] [rbp-11h] BYREF
  _GROUP_AFFINITY Affinity; // [rsp+70h] [rbp-1h] BYREF
  PVOID Object[3]; // [rsp+80h] [rbp+Fh] BYREF

  v1 = 0;
  v29 = 1;
  v2 = v0;
  Count = 0;
  Affinity = 0i64;
  v3 = 0i64;
  PoolWithTag = ExAllocatePoolWithTag(NonPagedPoolNx, 0x10u, 0x6C577845u);
  if ( PoolWithTag )
  {
    v3 = (_WORK_QUEUE_ITEM *)ExAllocatePoolWithTag(NonPagedPoolNx, 0x20u, 0x6C577845u);
    if ( v3 )
    {
      v29 = 0;
    }
    else
    {
      ExFreePoolWithTag(PoolWithTag, 0);
      PoolWithTag = 0i64;
    }
  }
  CurrentThread = (_ETHREAD *)KeGetCurrentThread();
  Thread = CurrentThread;
  KeSetActualBasePriorityThread(&CurrentThread->Tcb, 12i64);
  Parameters.NoWakeTolerance = -1i64;
  *(_QWORD *)&Parameters.Version = 0i64;
  KeSetTimer2(
    (_KTIMER2 *)(v2 + 128),
    -((10000000i64 * (unsigned int)ExpWorkerThreadTimeoutInSeconds) >> 2),
    (10000000i64 * (unsigned int)ExpWorkerThreadTimeoutInSeconds) >> 2,
    &Parameters);
  v6 = 0;
  v7 = 10000000i64 * (unsigned int)ExpWorkerThreadTimeoutInSeconds;
  Object[0] = (PVOID)(v2 + 16);
  Object[1] = (PVOID)(v2 + 40);
  v32 = v7;
  Object[2] = (PVOID)(v2 + 104);
  while ( 1 )
  {
    v8 = KeWaitForMultipleObjects(3u, Object, WaitAny, Executive, 1, 0, 0i64, 0i64);
    v9 = 0i64;
    if ( !v8 )
      break;
    v22 = v8 - 1;
    if ( v22 )
    {
      if ( v22 == 1 )
      {
        for ( i = 0i64; i < 64; i += 8i64 )
        {
          v24 = *(_QWORD *)(*(_QWORD *)(*(_QWORD *)(*(_QWORD *)v2 + 8i64)
                                      + 8i64 * *(unsigned __int16 *)(*(_QWORD *)(v2 + 8) + 146i64))
                          + i);
          if ( (v24 & 1) == 0 )
          {
            if ( v24 )
            {
              if ( (*(_DWORD *)(v24 + 712) & 0x4000) == 0 && !*(_DWORD *)(v24 + 4) )
              {
                v25 = (*(_DWORD *)(v24 + 712) & 0x3FFFu) - ((2 * *(_DWORD *)(v24 + 716)) >> 1);
                if ( (_DWORD)v25 )
                {
                  KeTimeOutQueueWaiters((_DISPATCHER_HEADER *)v24, v7, v25);
                  v9 = 0i64;
                }
              }
            }
          }
        }
        CurrentThread = Thread;
      }
      LOBYTE(v11) = 1;
LABEL_15:
      if ( v6 )
        goto LABEL_25;
      goto LABEL_16;
    }
    v6 = 0;
    v26 = 0i64;
    v11 = 1i64;
    do
    {
      v27 = *(_KDPC **)(*(_QWORD *)(*(_QWORD *)(*(_QWORD *)v2 + 8i64)
                                  + 8i64 * *(unsigned __int16 *)(*(_QWORD *)(v2 + 8) + 146i64))
                      + 8 * v26);
      if ( ((unsigned __int8)v27 & (unsigned __int8)v11) != 0 )
        v27 = v9;
      if ( v27[11].TargetInfoAsUlong == *((_DWORD *)&v27[11].0 + 1)
        && ExpNewThreadNecessary((_EX_WORK_QUEUE *)v27, 0x3FFFi64) )
      {
        if ( (ExpWorkerQueueTestFlags & 2) != 0 )
          KeBugCheckEx(0x163u, ExpWorkerQueueTestFlags, 2u, 0, (ULONG_PTR)v9);
        if ( v26 == v11 && v29 == (_BYTE)v9 )
        {
          *(_DWORD *)PoolWithTag = v11;
          PoolWithTag[1] = v27;
          v3->WorkerRoutine = (void (__fastcall *)(void *))ExpIoPoolDeadlockWorker;
          v3->Parameter = PoolWithTag;
          v3->List.Flink = (_LIST_ENTRY *)v9;
          ExQueueWorkItem(v3, NormalWorkQueue);
          v29 = 1;
        }
        WorkerThread = ExpCreateWorkerThread((_ENODE *)v27, (_EX_WORK_QUEUE *)(v2 + 276));
        v9 = 0i64;
        v11 = 1i64;
        if ( WorkerThread < 0 )
          v1 = 1;
      }
      v26 += v11;
    }
    while ( v26 <= v11 );
LABEL_16:
    v16 = (__int64)v9;
    do
    {
      v17 = *(_KDPC **)(*(_QWORD *)(*(_QWORD *)(*(_QWORD *)v2 + 8i64)
                                  + 8i64 * *(unsigned __int16 *)(*(_QWORD *)(v2 + 8) + 146i64))
                      + v16);
      if ( ((unsigned __int8)v17 & (unsigned __int8)v11) != 0 )
        v17 = v9;
      *((_DWORD *)&v17[11].0 + 1) = v17[11].TargetInfoAsUlong;
      if ( ((__int64)v17[11].DpcListEntry.Next & 0x3FFF) >= SLODWORD(v17[11].ProcessorHistory) || v1 )
        v6 = v11;
      v16 += 8i64;
    }
    while ( v16 <= 8 );
    if ( v6 )
      KeSetCoalescableTimer((PKTIMER)(v2 + 40), (LARGE_INTEGER)-10000000i64, 0, 0xA0u, v9);
    CurrentThread = Thread;
LABEL_25:
    KeQueryNodeActiveAffinity(*(_WORD *)(*(_QWORD *)(v2 + 8) + 146i64), &Affinity, &Count);
    if ( CurrentThread->Tcb.UserAffinity.Group != Affinity.Group
      || CurrentThread->Tcb.UserAffinity.Mask != Affinity.Mask )
    {
      KeSetAffinityThread(&CurrentThread->Tcb, &Affinity);
    }
    v1 = 0;
    for ( j = 0i64; j < 64; j += 8i64 )
    {
      v19 = *(_KPRIQUEUE **)(*(_QWORD *)(*(_QWORD *)(*(_QWORD *)v2 + 8i64)
                                       + 8i64 * *(unsigned __int16 *)(*(_QWORD *)(v2 + 8) + 146i64))
                           + j);
      if ( ((unsigned __int8)v19 & 1) == 0 && v19 && v19->MaximumCount != Count )
        KeSetMaximumCountPriQueue(v19, Count);
    }
    CurrentThread = Thread;
    v7 = v32;
  }
  if ( !*(_DWORD *)(v2 + 272) )
  {
    v10 = 0;
    LODWORD(v11) = 1;
    v12 = 0i64;
    do
    {
      v13 = *(_QWORD *)(v2 + 8);
      if ( ((unsigned __int8)*(_QWORD *)(*(_QWORD *)(*(_QWORD *)(*(_QWORD *)v2 + 8i64)
                                                   + 8i64 * *(unsigned __int16 *)(v13 + 146))
                                       + v12) & (unsigned __int8)v11) != 0 )
      {
        PoolDelayed = ExpPartitionCreatePoolDelayed(*(_QWORD *)v2, v13, v10);
        v9 = 0i64;
        LODWORD(v11) = 1;
      }
      else
      {
        PoolDelayed = (int)v9;
      }
      if ( PoolDelayed < 0 )
      {
        v1 = v11;
      }
      else
      {
        v15 = *(_EX_WORK_QUEUE **)(*(_QWORD *)(*(_QWORD *)(*(_QWORD *)v2 + 8i64)
                                             + 8i64 * *(unsigned __int16 *)(*(_QWORD *)(v2 + 8) + 146i64))
                                 + v12);
        if ( ((unsigned __int8)v15 & (unsigned __int8)v11) == 0 )
        {
          if ( v15 )
          {
            if ( ExpNewThreadNecessary(v15, (unsigned int)v15->MaxThreads) )
            {
              v21 = ExpCreateWorkerThread(v20, (_EX_WORK_QUEUE *)(v2 + 276));
              v9 = 0i64;
              LODWORD(v11) = 1;
              if ( v21 < 0 )
                v1 = 1;
            }
          }
        }
      }
      v10 += v11;
      v12 += 8i64;
    }
    while ( v10 < 8 );
    CurrentThread = Thread;
    goto LABEL_15;
  }
  if ( PoolWithTag )
    ExFreePoolWithTag(PoolWithTag, 0);
  if ( v3 )
    ExFreePoolWithTag(v3, 0);
}

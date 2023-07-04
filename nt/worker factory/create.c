NTSTATUS __fastcall NtCreateWorkerFactory(
        _QWORD *WorkerFactoryHandleReturn,
        ACCESS_MASK DesiredAccess,          
        _OBJECT_ATTRIBUTES ObjectAttributes,
        int CompletionPortHandle,
        HANDLE WorkerProcessHandle,
        __int64 StartRoutine,
        __int64 StartRoutineParameter,
        int MaxThreadCount,
        __int64 StackReserve,
        __int64 StackCommit)
{
  char PreviousMode; // di
  __int64 v15; // rcx
  _IO_MINI_COMPLETION_PACKET_USER *PoolWithQuotaTag; // rax
  _IO_MINI_COMPLETION_PACKET_USER *v17; // rsi
  UINT8 v18; // dl
  NTSTATUS v19; // ebx
  _DISPATCHER_HEADER *v20; // rcx
  VOID *v21; // r14
  void *v22; // r8
  void *v23; // r9
  INT64 v24; // r9
  __int64 v25; // rax
  char *ExWorkerFactory; // rdi
  __int64 v27; // rcx
  __int64 v28; // rcx
  VOID *v29; // rcx
  NTSTATUS result; // eax
  POBJECT_HANDLE_INFORMATION HandleInformation; // [rsp+28h] [rbp-90h]
  POBJECT_HANDLE_INFORMATION v32; // [rsp+30h] [rbp-88h]
  UINT64 NonPagedPoolCharge; // [rsp+38h] [rbp-80h]
  HANDLE v34; // [rsp+58h] [rbp-60h] BYREF
  PVOID Object; // [rsp+60h] [rbp-58h] BYREF
  PVOID v36; // [rsp+68h] [rbp-50h] BYREF
  PVOID v37; // [rsp+70h] [rbp-48h] BYREF
  void *v38; // [rsp+78h] [rbp-40h] BYREF
  _EXT_SET_PARAMETERS_V0 Parameters; // [rsp+88h] [rbp-30h] BYREF

  v34 = 0i64;
  v37 = 0i64;
  v38 = 0i64;
  v36 = 0i64;
  PreviousMode = KeGetCurrentThread()->PreviousMode;
  if ( PreviousMode )
  {
    v15 = 0x7FFFFFFF0000i64;
    if ( (unsigned __int64)a1 < 0x7FFFFFFF0000i64 )
      v15 = (__int64)a1;
    *(_QWORD *)v15 = *(_QWORD *)v15;
  }
  PoolWithQuotaTag = (_IO_MINI_COMPLETION_PACKET_USER *)ExAllocatePoolWithQuotaTag((POOL_TYPE)520, 0x28u, 0x63577054u);
  v17 = PoolWithQuotaTag;
  if ( !PoolWithQuotaTag )
    return -1073741801;
  PoolWithQuotaTag->ListEntry.Flink = 0i64;
  PoolWithQuotaTag->KeyContext = 0i64;
  LOWORD(PoolWithQuotaTag->ApcContext) = 0;
  BYTE2(PoolWithQuotaTag->ApcContext) = 0;
  Object = 0i64;
  v19 = ObReferenceObjectByHandle(a4, 2u, IoCompletionObjectType, PreviousMode, &Object, 0i64);
  v20 = (_DISPATCHER_HEADER *)Object;
  v17->ListEntry.Blink = (_LIST_ENTRY *)Object;
  if ( v19 < 0 )
  {
LABEL_26:
    ExFreePoolWithTag(v17, 0);
    return v19;
  }
  KeDisableQueueingPriorityIncrement(v20, v18);
  v19 = ObReferenceObjectByHandleWithTag(
          Handle,
          0x2Au,
          (POBJECT_TYPE)PsProcessType,
          PreviousMode,
          0x66577845u,
          &v36,
          0i64);
  if ( v19 < 0 )
  {
LABEL_25:
    HalPutDmaAdapter((PADAPTER_OBJECT)v17->ListEntry.Blink);
    goto LABEL_26;
  }
  v21 = v36;
  if ( KeGetCurrentThread()->ApcState.Process != v36 )
  {
    v19 = -1073741811;
    goto LABEL_24;
  }
  v19 = ObOpenObjectByPointer(v36, 0x200u, 0i64, 0x2Au, (POBJECT_TYPE)PsProcessType, 0, &v34);
  if ( v19 < 0 )
  {
LABEL_24:
    ObfDereferenceObjectWithTag(v21, 0x66577845ui64);
    goto LABEL_25;
  }
  IoAllocateMiniCompletionPacket(ExpWorkerFactoryCompletionPacketRoutine, v17, v22, v23);
  *(_QWORD *)&v17->PacketType = v25;
  if ( !v25 )
  {
    v19 = -1073741801;
LABEL_23:
    ObCloseHandle(v34, 0);
    goto LABEL_24;
  }
  LODWORD(NonPagedPoolCharge) = 0;
  LODWORD(v32) = 0;
  LODWORD(HandleInformation) = 576;
  LOBYTE(v24) = PreviousMode;
  v19 = ObCreateObject(
          PreviousMode,
          ExpWorkerFactoryObjectType,
          a3,
          v24,
          0i64,
          (UINT64)HandleInformation,
          (UINT64)v32,
          NonPagedPoolCharge,
          &v37);
  if ( v19 < 0 )
  {
    IoFreeMiniCompletionPacket(*(_IO_MINI_COMPLETION_PACKET_USER **)&v17->PacketType);
    goto LABEL_23;
  }
  ExWorkerFactory = (char *)v37;
  *((_QWORD *)ExWorkerFactory + 2) = v17;
  *((_QWORD *)ExWorkerFactory + 14) = -10000000i64 * ExpWorkerFactoryThreadIdleTimeoutInSeconds;
  *((_DWORD *)ExWorkerFactory + 70) = 0;
  *((_DWORD *)ExWorkerFactory + 71) = a8;
  *((_DWORD *)ExWorkerFactory + 75) = 0;
  *((_QWORD *)ExWorkerFactory + 36) = 0i64;
  v27 = 0x10000i64;
  if ( a9 )
    v27 = a9;
  *((_QWORD *)v26 + 7) = v27;
  memset((UINT8 *)v26 + 120, 0, 0xA0ui64);
  *((_QWORD *)v26 + 39) = 0i64;
  v28 = 4096i64;
  if ( a10 )
    v28 = a10;
  *((_QWORD *)ExWorkerFactory + 8) = v28;
  *((_QWORD *)ExWorkerFactory + 3) = a6;
  *((_QWORD *)ExWorkerFactory + 4) = a7;
  *((_QWORD *)ExWorkerFactory + 38) = 0i64;
  *((_DWORD *)ExWorkerFactory + 80) = 0;
  *((_QWORD *)ExWorkerFactory + 5) = v34;
  *((_QWORD *)ExWorkerFactory + 6) = v21;
  *((_DWORD *)ExWorkerFactory + 74) = 0;
  *((_DWORD *)ExWorkerFactory + 142) = 0;
  *((_DWORD *)ExWorkerFactory + 128) = 1;
  KeInitializeTimer2((__int64)(ExWorkerFactory + 328), 0i64, 0i64, 8);
  ExpInitializeThreadHistory((_EX_WORKER_FACTORY *)ExWorkerFactory);
  *((_QWORD *)ExWorkerFactory + 13) = 0i64;
  ObfReferenceObject(v29);
  KeRegisterObjectNotification(ExWorkerFactory + 328, &ExpWorkerFactoryManagerQueue, (_KWAIT_BLOCK *)(ExWorkerFactory + 464));
  *(_QWORD *)&Parameters.Version = 0i64;
  Parameters.NoWakeTolerance = -1i64;
  
  KeSetTimer2((_KTIMER2 *)(ExWorkerFactory + 328), *((_QWORD *)ExWorkerFactory + 14), -*((_QWORD *)ExWorkerFactory + 14), &Parameters);
  result = ObInsertObject(ExWorkerFactory, 0i64, a2, 0, 0i64, &v38);
  if ( result >= 0 )
    *a1 = v38;
  return result;
}

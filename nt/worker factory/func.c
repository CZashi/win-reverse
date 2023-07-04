VOID __stdcall __noreturn ExpWorkerFactoryManagerThread(VOID *Context)
{
  PLIST_ENTRY v1; // rax
  PLIST_ENTRY v2; // rbx
  _LIST_ENTRY *Flink; // rdi
  unsigned int v4; // er8
  unsigned int Blink; // eax
  char v6; // di
  _KLOCK_QUEUE_HANDLE LockHandle; // [rsp+20h] [rbp-28h] BYREF

  memset(&LockHandle, 0, sizeof(LockHandle));
  while ( 1 )
  {
    while ( 1 )
    {
      v1 = KeRemoveQueue(&ExpWorkerFactoryManagerQueue, 0, 0i64);
      if ( v1 != (PLIST_ENTRY)&ExpWorkerFactoryThreadCreationBlock )
        break;
      ExpWorkerFactoryDeferredThreadCreation();
      KeRegisterObjectNotification(
        &ExpWorkerFactoryThreadCreationTimer,
        &ExpWorkerFactoryManagerQueue,
        &ExpWorkerFactoryThreadCreationBlock);
    }
    if ( !LODWORD(v1[3].Flink) )
      break;
    v2 = v1 - 29;
    Flink = v1[-28].Flink;
    KeAcquireInStackQueuedSpinLock((UINT64 *)Flink, &LockHandle);
    if ( !LODWORD(v2[19].Flink) )
    {
      v4 = (unsigned int)v2[18].Flink;
      Blink = (unsigned int)v2[17].Blink;
      if ( v4 > Blink )
        KeTimeOutQueueWaiters((_DISPATCHER_HEADER *)Flink->Blink, -(__int64)v2[7].Flink, v4 - Blink);
    }
    if ( BYTE1(Flink[2].Flink) )
    {
      v6 = 1;
    }
    else
    {
      v6 = 0;
      KeRegisterObjectNotification(&v2[20].Blink, &ExpWorkerFactoryManagerQueue, (_KWAIT_BLOCK *)&v2[29]);
    }
    KeReleaseInStackQueuedSpinLockFromDpcLevel(&LockHandle);
    __writecr8(LockHandle.OldIrql);
    if ( v6 )
LABEL_14:
      ObfDereferenceObjectWithTag(v2, 0x746C6644ui64);
  }
  v2 = (PLIST_ENTRY)((char *)v1 - 520);
  KeAcquireInStackQueuedSpinLock((UINT64 *)v1[-32].Blink, &LockHandle);
  LODWORD(v2[19].Blink) &= ~0x400u;
  
  if ( ((__int64)v2[19].Blink & 0x200) != 0 && (unsigned __int8)ExpTryEnterWorkerFactoryAwayMode((_EX_WORKER_FACTORY *)v2) ) {
    ExpWorkerFactoryCheckCreate((_EX_WORKER_FACTORY *)v2, &LockHandle, 0);
  }
  else {
    KeReleaseInStackQueuedSpinLockFromDpcLevel(&LockHandle);
    __writecr8(LockHandle.OldIrql);
  }
  goto LABEL_14;
}

NTSTATUS __stdcall ExpWorkerFactoryInitialization()
{
  int Timeout; 
  int ObjectType;
  _OBJECT_TYPE_INITIALIZER ObjectTypeInit;
  void *ThreadHandle; 

  Timeout = ExpWorkerFactoryThreadCreationTimeoutInSeconds;
  ThreadHandle = 0;
  if ( ExpWorkerFactoryThreadCreationTimeoutInSeconds ) {
    if ( (unsigned int)ExpWorkerFactoryThreadCreationTimeoutInSeconds > 0x258 ) {
      Timeout = 600;
      ExpWorkerFactoryThreadCreationTimeoutInSeconds = 600;
    }
  }
  else {
    Timeout = 1;
    ExpWorkerFactoryThreadCreationTimeoutInSeconds = 1;
  }
  if ( ExpWorkerFactoryThreadIdleTimeoutInSeconds ) {
    if ( (unsigned int)ExpWorkerFactoryThreadIdleTimeoutInSeconds > 0x258 )
      ExpWorkerFactoryThreadIdleTimeoutInSeconds = 600;
  }
  else {
    ExpWorkerFactoryThreadIdleTimeoutInSeconds = 1;
  }
  
  ExpWorkerFactoryDeferredMediumTimeout         = -1200000i64;
  ExpWorkerFactoryDeferredLongTimeout           = -10000000i64 * Timeout;
  ExpWorkerFactoryDeferredShortTimeout.QuadPart = -300000i64;
  
  if ( ((unsigned __int8)&ExpWorkerFactoryThreadCreationList & 0xF) != 0 )
    RtlRaiseStatus(-2147483646);
  
  ExpWorkerFactoryThreadCreationList = 0i64;
  KeInitializeQueue(&ExpWorkerFactoryManagerQueue, 0);
  
  *(_QWORD *)&ExpWorkerFactoryThreadCreationTimer.Header.Lock = 9;
  ExpWorkerFactoryThreadCreationTimer.Header.WaitListHead.Blink = &ExpWorkerFactoryThreadCreationTimer.Header.WaitListHead;
  ExpWorkerFactoryThreadCreationTimer.Header.WaitListHead.Flink = &ExpWorkerFactoryThreadCreationTimer.Header.WaitListHead;
  ExpWorkerFactoryThreadCreationTimer.DueTime.QuadPart = 0i64;
  ExpWorkerFactoryThreadCreationTimer.Period = 0;
  ExpWorkerFactoryThreadCreationTimer.Processor = 0;
  
  KeRegisterObjectNotification(
    &ExpWorkerFactoryThreadCreationTimer,
    &ExpWorkerFactoryManagerQueue,
    &ExpWorkerFactoryThreadCreationBlock);
  
  ExpWorkerFactoryThreadCreationState = 0;
  
  memset((UINT8 *)&ObjectTypeInit, 0, sizeof(dst));
  strcpy((char *)&ObjectTypeInit, "x");
  
  ObjectTypeInit.CloseProcedure            = (void (__fastcall *)(_EPROCESS *, void *, unsigned __int64, unsigned __int64))ExpCloseWorkerFactory;
  ObjectTypeInit.InvalidAttributes         = 256;
  ObjectTypeInit.DeleteProcedure           = (void (__fastcall *)(void *))ExpDeleteWorkerFactory;
  ObjectTypeInit.PoolType                  = NonPagedPoolNx;
  ObjectTypeInit.DefaultNonPagedPoolCharge = 576;
  ObjectTypeInit.GenericMapping            = (_GENERIC_MAPPING)ExpWorkerFactoryMapping;
  ObjectTypeInit.ValidAccessMask           = 983295;
  
  ObjectType = ObCreateObjectType( (_UNICODE_STRING *)&TypeName, &ObjectTypeInit, 0, &ExpWorkerFactoryObjectType );
  if ( ObjectType >= 0 ) 
  {
    ObjectType = PsCreateSystemThread(&ThreadHandle, 0x1FFFFFu, 0, 0, 0, ExpWorkerFactoryManagerThread, 0);
    
    if ( ObjectType >= 0 )
      ZwClose(ThreadHandle);
  }
  return ObjectType;
}

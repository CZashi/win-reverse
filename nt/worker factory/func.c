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

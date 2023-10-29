struct _WNF_PROCESS_CONTEXT
{
    struct _WNF_NODE_HEADER Header;                                         //0x0
    struct _EPROCESS* Process;                                              //0x8
    struct _LIST_ENTRY WnfProcessesListEntry;                               //0x10
    VOID* ImplicitScopeInstances[3];                                        //0x20
    struct _WNF_LOCK TemporaryNamesListLock;                                //0x38
    struct _LIST_ENTRY TemporaryNamesListHead;                              //0x40
    struct _WNF_LOCK ProcessSubscriptionListLock;                           //0x50
    struct _LIST_ENTRY ProcessSubscriptionListHead;                         //0x58
    struct _WNF_LOCK DeliveryPendingListLock;                               //0x68
    struct _LIST_ENTRY DeliveryPendingListHead;                             //0x70
    struct _KEVENT* NotificationEvent;                                      //0x80
}; 

NTSTATUS __fastcall ExpWnfCreateProcessContext(_EPROCESS *Process, _WNF_PROCESS_CONTEXT **ProcessContext)
{
  NTSTATUS v2; // ebx
  NTSTATUS v5; // er14
  UINT8 *PoolWithTag; // rax
  _WNF_PROCESS_CONTEXT *v7; // rdi
  _BYTE *v8; // rax
  _BYTE *v9; // rsi
  void **v10; // rcx
  _LIST_ENTRY *p_WnfProcessesListEntry; // rax
  _WNF_PROCESS_CONTEXT *WnfContext; // rcx

  v2 = 0;
  v5 = 0;
  PoolWithTag = (UINT8 *)ExAllocatePoolWithTag(PagedPool, 0x88u, 0x20666E57u);
  v7 = (_WNF_PROCESS_CONTEXT *)PoolWithTag;
  if ( PoolWithTag )
  {
    memset(PoolWithTag, 0, 0x88ui64);
    v7->Header = (_WNF_NODE_HEADER)8915206;
    v7->TemporaryNamesListHead.Blink = &v7->TemporaryNamesListHead;
    v7->TemporaryNamesListHead.Flink = &v7->TemporaryNamesListHead;
    v7->NotificationEvent = 0i64;
    v7->ProcessSubscriptionListHead.Blink = &v7->ProcessSubscriptionListHead;
    v7->ProcessSubscriptionListHead.Flink = &v7->ProcessSubscriptionListHead;
    v7->Process = Process;
    v7->DeliveryPendingListHead.Blink = &v7->DeliveryPendingListHead;
    v7->DeliveryPendingListHead.Flink = &v7->DeliveryPendingListHead;
    v8 = KeAbPreAcquire(&ExpWnfProcessesListLock, 0i64, 0i64);
    v9 = v8;
    if ( _interlockedbittestandset64((volatile signed __int32 *)&ExpWnfProcessesListLock, 0i64) )
      ExfAcquirePushLockExclusiveEx(&ExpWnfProcessesListLock, v8, &ExpWnfProcessesListLock);
    if ( v9 )
      v9[26] |= 1u;
    v10 = off_140D2C648;
    p_WnfProcessesListEntry = &v7->WnfProcessesListEntry;
    if ( *off_140D2C648 != &ExpWnfProcessesListHead )
      __fastfail(3u);
    p_WnfProcessesListEntry->Flink = (_LIST_ENTRY *)&ExpWnfProcessesListHead;
    v7->WnfProcessesListEntry.Blink = (_LIST_ENTRY *)v10;
    *v10 = p_WnfProcessesListEntry;
    off_140D2C648 = (void **)&v7->WnfProcessesListEntry.Flink;
    if ( (_InterlockedExchangeAdd64((volatile signed __int64 *)&ExpWnfProcessesListLock, 0xFFFFFFFFFFFFFFFFui64) & 6) == 2 )
      ExfTryToWakePushLock(&ExpWnfProcessesListLock);
    KeAbPostRelease(&ExpWnfProcessesListLock);
    if ( _InterlockedCompareExchange64((volatile signed __int64 *)&Process->WnfContext, (signed __int64)v7, 0i64) )
      ExpWnfDeleteProcessContext(v7, 1ui64);
  }
  else
  {
    v5 = -1073741670;
  }
  WnfContext = (_WNF_PROCESS_CONTEXT *)Process->WnfContext;
  *ProcessContext = WnfContext;
  if ( !WnfContext )
    return v5;
  return v2;
}

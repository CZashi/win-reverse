VOID __stdcall CmpPostNotify(
        _CM_NOTIFY_BLOCK *NotifyBlock,
        _UNICODE_STRING *Name,
        UINT64 Filter,
        INT64 Status,
        _LIST_ENTRY *PostListLockHeld,
        _LIST_ENTRY *ExternalKeyDeref,
        _LIST_ENTRY *ExternalDeferredPostAsync)
{
  _LIST_ENTRY *v8; // r14
  _LIST_ENTRY *v9; // rsi
  _LIST_ENTRY *p_PostList; // rdi
  unsigned __int64 v11; // r11
  INT64 Flink; // rbx
  _LIST_ENTRY *v13; // rax
  int v14; // ecx
  INT64 v15; // rdx
  _LIST_ENTRY **v16; // rax
  _LIST_ENTRY *v17; // rbx
  _LIST_ENTRY *v18; // rcx
  _LIST_ENTRY *Blink; // rax
  INT64 v20; // rax
  __int64 v21; // rax
  __int64 v22; // rdx
  _QWORD *v23; // rcx
  unsigned __int8 CurrentIrql; // r15
  wchar_t *v25; // rax
  __int64 v26; // rax
  __int128 v27; // [rsp+20h] [rbp-20h] BYREF
  __int128 v28; // [rsp+30h] [rbp-10h] BYREF
  int v29; // [rsp+78h] [rbp+38h]

  v29 = Status;
  v27 = 0i64;
  v28 = 0i64;
  if ( !ExternalKeyDeref )
  {
    *((_QWORD *)&v27 + 1) = &v27;
    *(_QWORD *)&v27 = &v27;
  }
  v8 = (_LIST_ENTRY *)&v27;
  if ( ExternalKeyDeref )
    v8 = ExternalKeyDeref;
  if ( !ExternalDeferredPostAsync )
  {
    *((_QWORD *)&v28 + 1) = &v28;
    *(_QWORD *)&v28 = &v28;
  }
  v9 = (_LIST_ENTRY *)&v28;
  if ( ExternalDeferredPostAsync )
    v9 = ExternalDeferredPostAsync;
  if ( !(_BYTE)PostListLockHeld )
  {
    ExAcquireFastMutexUnsafe(&CmpPostLock);
    LODWORD(Status) = v29;
  }
  p_PostList = &NotifyBlock->PostList;
  if ( p_PostList->Flink == p_PostList )
  {
    *((_DWORD *)NotifyBlock + 12) |= 0x80000000;
    if ( !(_BYTE)PostListLockHeld )
      ExReleaseFastMutexUnsafe(&CmpPostLock);
  }
  else
  {
    *((_DWORD *)NotifyBlock + 12) &= ~0x80000000;
LABEL_16:
    v11 = 1i64;
    while ( 1 )
    {
      Flink = (INT64)p_PostList->Flink;
      if ( p_PostList->Flink == p_PostList )
        break;
      v13 = *(_LIST_ENTRY **)Flink;
      if ( *(_LIST_ENTRY **)(Flink + 8) != p_PostList || v13->Blink != (_LIST_ENTRY *)Flink )
        goto LABEL_51;
      p_PostList->Flink = v13;
      v13->Blink = p_PostList;
      if ( (_DWORD)Status != 267 || (*(_DWORD *)(Flink + 56) & 0x10000) != 0 )
      {
        v14 = *(_DWORD *)(Flink + 56);
        if ( (v14 & 0x10000) == 0 )
        {
          v20 = Flink;
          do
          {
            v21 = *(_QWORD *)(v20 + 32);
            *(_DWORD *)(v21 + 24) &= ~0x10000u;
            v20 = v21 - 32;
          }
          while ( v20 != Flink );
          *(_DWORD *)(Flink + 56) |= 0x10000u;
          v14 = *(_DWORD *)(Flink + 56);
        }
        if ( (unsigned __int16)v14 != (_DWORD)v11 )
        {
          CmpCancelSubordinatePost((_VM_COUNTERS_EX *)Flink, v8);
          CmpAddToDelayedDeref(Flink, v15);
          v14 = *(_DWORD *)(Flink + 56);
        }
        if ( (unsigned __int16)v14 == (_DWORD)v11 )
        {
          v26 = *(_QWORD *)(Flink + 64);
          *(_QWORD *)Flink = 0i64;
          *(_DWORD *)(v26 + 24) = Status;
          KeSetEvent(*(PRKEVENT *)(Flink + 64), 0, 0);
          goto LABEL_31;
        }
        if ( (unsigned __int16)v14 == 2 )
        {
          KeInsertQueueApc(
            (_KAPC *)(*(_QWORD *)(Flink + 64) + 16i64),
            (VOID *)(unsigned int)Status,
            (VOID *)Flink,
            0i64);
LABEL_31:
          LODWORD(Status) = v29;
          goto LABEL_16;
        }
        if ( (unsigned int)(unsigned __int16)v14 - 3 <= (unsigned int)v11 )
        {
          CmpFreeSubordinatePost((_VM_COUNTERS_EX *)Flink);
          v16 = *(_LIST_ENTRY ***)(Flink + 24);
          v17 = (_LIST_ENTRY *)(Flink + 16);
          v18 = v17->Flink;
          if ( v17->Flink->Blink != v17
            || *v16 != v17
            || (*v16 = v18, v18->Blink = (_LIST_ENTRY *)v16, Blink = v9->Blink, Blink->Flink != v9) )
          {
LABEL_51:
            __fastfail(3u);
          }
          v17->Flink = v9;
          v17->Blink = Blink;
          Blink->Flink = v17;
          v9->Blink = v17;
          goto LABEL_31;
        }
      }
      else
      {
        v22 = *(_QWORD *)(Flink + 32);
        v23 = *(_QWORD **)(Flink + 40);
        if ( *(_QWORD *)(v22 + 8) != Flink + 32 )
          goto LABEL_51;
        if ( *v23 != Flink + 32 )
          goto LABEL_51;
        *v23 = v22;
        *(_QWORD *)(v22 + 8) = v23;
        CurrentIrql = KeGetCurrentIrql();
        __writecr8(v11);
        Name = *(_UNICODE_STRING **)(Flink + 16);
        v25 = *(wchar_t **)(Flink + 24);
        if ( Name->Buffer != (wchar_t *)(Flink + 16) || *(_QWORD *)v25 != Flink + 16 )
          goto LABEL_51;
        *(_QWORD *)v25 = Name;
        Name->Buffer = v25;
        __writecr8(CurrentIrql);
        if ( *(_DWORD *)(Flink + 56) != (_DWORD)v11 )
        {
          CmpAddToDelayedDeref(Flink, (INT64)v8);
          CmpFreePostBlock((_VM_COUNTERS_EX *)Flink);
          goto LABEL_31;
        }
      }
    }
    if ( !(_BYTE)PostListLockHeld )
      ExReleaseFastMutexUnsafe(&CmpPostLock);
    if ( !ExternalKeyDeref )
      CmpDelayedDerefKeys((VOID **)&v8->Flink);
    if ( !ExternalDeferredPostAsync )
      CmpSignalDeferredPosts(v9, Name, Filter);
  }
}

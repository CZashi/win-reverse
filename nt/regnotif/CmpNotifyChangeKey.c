_ETW_TP_EVENT_TIMER_CANCELLED *__fastcall CmpNotifyChangeKey(
        _ETW_TP_EVENT_TIMER_CANCELLED *retstr,
        _CM_KEY_BODY *KeyBody,
        _VM_COUNTERS_EX *PostBlock,
        _ETW_TP_EVENT_TIMER_EXPIRATION_END *CompletionFilter,
        _REAL_NOTIFY_SYNC *WatchTree,
        _EVENT_TRACE *Buffer,
        _ETW_TP_EVENT_TIMER_EXPIRATION_END *BufferSize,
        _VM_COUNTERS_EX *MasterPostBlock)
{
  int v8; // ebp
  char v10; // r12
  _LARGE_INTEGER SystemTime; // rdi
  _LARGE_INTEGER *v13; // rsi
  __int64 v14; // rcx
  _CM_KEY_CONTROL_BLOCK *v15; // rax
  _LIST_ENTRY *p_KeyBodyList; // rcx
  _CM_NOTIFY_BLOCK ***v17; // rcx
  _UNICODE_STRING *Flink; // rdx
  _CM_NOTIFY_BLOCK **p_NotifyBlock; // rax
  char *PoolWithQuotaTag; // rax
  _LARGE_INTEGER *QuadPart; // rdx
  _LARGE_INTEGER v23; // rax
  unsigned __int8 CurrentIrql; // si
  _ETHREAD *CurrentThread; // rcx
  _ETHREAD *v26; // rdx
  _CM_NOTIFY_BLOCK **v27; // rcx
  _QWORD *p_Flink; // rax
  _LIST_ENTRY *v29; // rdx
  _UNICODE_STRING **v30; // rax
  int v31[8]; // [rsp+0h] [rbp-A8h] BYREF
  _LIST_ENTRY *ExternalDeferredPostAsync; // [rsp+20h] [rbp-88h]

  v8 = (int)PostBlock;
  v10 = (char)CompletionFilter;
  if ( (retstr[1].Header.Marker & 9) != 0 )
  {
    CmpFreePostBlock((_VM_COUNTERS_EX *)KeyBody);
    return (_ETW_TP_EVENT_TIMER_CANCELLED *)3221225852i64;
  }
  SystemTime = retstr->Header.SystemTime;
  v13 = *(_LARGE_INTEGER **)(*(_QWORD *)&retstr->Header.ThreadId + 32i64);
  if ( !SystemTime.QuadPart )
  {
    PoolWithQuotaTag = (char *)ExAllocatePoolWithQuotaTag((POOL_TYPE)9, 0x58u, 0x626E4D43u);
    SystemTime.QuadPart = (LONGLONG)PoolWithQuotaTag;
    if ( !PoolWithQuotaTag )
    {
      CmpFreePostBlock((_VM_COUNTERS_EX *)KeyBody);
      return (_ETW_TP_EVENT_TIMER_CANCELLED *)3221225626i64;
    }
    *((_QWORD *)PoolWithQuotaTag + 4) = *(_QWORD *)&retstr->Header.ThreadId;
    *((_DWORD *)PoolWithQuotaTag + 12) = v8 & 0x3FFFFFFF | ((v10 & 1) << 30);
    *((_QWORD *)PoolWithQuotaTag + 3) = PoolWithQuotaTag + 16;
    *((_QWORD *)PoolWithQuotaTag + 2) = PoolWithQuotaTag + 16;
    retstr->Header.SystemTime.QuadPart = (LONGLONG)PoolWithQuotaTag;
    *((_QWORD *)PoolWithQuotaTag + 5) = retstr;
    SeCaptureSubjectContext((PSECURITY_SUBJECT_CONTEXT)(PoolWithQuotaTag + 56));
    QuadPart = v13 + 198;
    v23 = v13[198];
    if ( v23.QuadPart )
    {
      PostBlock = (_VM_COUNTERS_EX *)((*(_DWORD *)(*(_QWORD *)&retstr->Header.ThreadId + 8i64) >> 21) & 0x3FF);
      while ( 1 )
      {
        QuadPart = (_LARGE_INTEGER *)v23.QuadPart;
        if ( ((*(_DWORD *)(*(_QWORD *)(v23.QuadPart + 32) + 8i64) >> 21) & 0x3FFu) > (unsigned int)PostBlock )
          break;
        v23 = *(_LARGE_INTEGER *)v23.QuadPart;
        if ( !QuadPart->QuadPart )
          goto LABEL_17;
      }
      *(_QWORD *)SystemTime.QuadPart = v23.QuadPart;
      **(_LARGE_INTEGER **)(v23.QuadPart + 8) = SystemTime;
      *(_QWORD *)(SystemTime.QuadPart + 8) = *(_QWORD *)(v23.QuadPart + 8);
      *(_LARGE_INTEGER *)(v23.QuadPart + 8) = SystemTime;
    }
    else
    {
LABEL_17:
      *QuadPart = SystemTime;
      *(_QWORD *)SystemTime.QuadPart = 0i64;
      *(_QWORD *)(SystemTime.QuadPart + 8) = QuadPart;
    }
  }
  v14 = *(_QWORD *)(SystemTime.QuadPart + 16);
  v15 = (_CM_KEY_CONTROL_BLOCK *)(SystemTime.QuadPart + 16);
  if ( *(_QWORD *)(v14 + 8) != SystemTime.QuadPart + 16 )
    goto LABEL_29;
  *(_QWORD *)&KeyBody->Type = v14;
  KeyBody->KeyControlBlock = v15;
  *(_QWORD *)(v14 + 8) = KeyBody;
  p_KeyBodyList = &KeyBody->KeyBodyList;
  v15->RefCount = (unsigned __int64)KeyBody;
  if ( (*(_DWORD *)&KeyBody->Trans.0 & 0x10000) != 0 )
  {
    KeyBody->KeyBodyList.Blink = &KeyBody->KeyBodyList;
    p_KeyBodyList->Flink = p_KeyBodyList;
  }
  else
  {
    v29 = *(_LIST_ENTRY **)&BufferSize[1].Header.Marker;
    if ( (void **)v29->Flink != &BufferSize->SubQueue )
      goto LABEL_29;
    p_KeyBodyList->Flink = (_LIST_ENTRY *)&BufferSize->SubQueue;
    KeyBody->KeyBodyList.Blink = v29;
    v29->Flink = p_KeyBodyList;
    *(_QWORD *)&BufferSize[1].Header.Marker = p_KeyBodyList;
  }
  if ( (unsigned int)(unsigned __int16)*(_DWORD *)&KeyBody->Trans.0 - 3 <= 1 )
  {
    v17 = (_CM_NOTIFY_BLOCK ***)qword_140D2C6B8;
    Flink = (_UNICODE_STRING *)&CmpAsyncKernelPostList;
    p_NotifyBlock = &KeyBody->NotifyBlock;
    if ( *(INT64 **)qword_140D2C6B8 == &CmpAsyncKernelPostList )
    {
      *p_NotifyBlock = (_CM_NOTIFY_BLOCK *)&CmpAsyncKernelPostList;
      KeyBody->ProcessID = v17;
      *v17 = p_NotifyBlock;
      qword_140D2C6B8 = (__int64)&KeyBody->NotifyBlock;
      goto LABEL_9;
    }
LABEL_29:
    __fastfail(3u);
  }
  CurrentIrql = KeGetCurrentIrql();
  __writecr8(1ui64);
  CurrentThread = (_ETHREAD *)KeGetCurrentThread();
  if ( (CurrentThread->SameThreadApcFlags & 8) == 0 )
  {
    LOBYTE(CurrentThread->SameThreadApcFlags) |= 8u;
    _InterlockedOr(v31, 0);
    CurrentThread->PostBlockList.Blink = &CurrentThread->PostBlockList;
    CurrentThread->PostBlockList.Flink = &CurrentThread->PostBlockList;
  }
  v26 = (_ETHREAD *)KeGetCurrentThread();
  v27 = &KeyBody->NotifyBlock;
  if ( (*(_DWORD *)&KeyBody->Trans.0 & 0x10000) != 0 )
  {
    p_Flink = &v26->PostBlockList.Flink;
    Flink = (_UNICODE_STRING *)v26->PostBlockList.Flink;
    if ( (_QWORD *)Flink->Buffer != p_Flink )
      goto LABEL_29;
    *v27 = (_CM_NOTIFY_BLOCK *)Flink;
    KeyBody->ProcessID = p_Flink;
    Flink->Buffer = (wchar_t *)v27;
    *p_Flink = v27;
  }
  else
  {
    Flink = (_UNICODE_STRING *)&v26->1096;
    v30 = (_UNICODE_STRING **)Flink->Buffer;
    if ( *v30 != Flink )
      goto LABEL_29;
    *v27 = (_CM_NOTIFY_BLOCK *)Flink;
    KeyBody->ProcessID = v30;
    *v30 = (_UNICODE_STRING *)v27;
    Flink->Buffer = (wchar_t *)v27;
  }
  __writecr8(CurrentIrql);
LABEL_9:
  if ( *(int *)(SystemTime.QuadPart + 48) >= 0 )
    return (_ETW_TP_EVENT_TIMER_CANCELLED *)259;
  LOBYTE(ExternalDeferredPostAsync) = 1;
  CmpPostNotify(
    (_CM_NOTIFY_BLOCK *)SystemTime.QuadPart,
    Flink,
    (UINT64)PostBlock,
    268i64,
    ExternalDeferredPostAsync,
    0i64,
    0i64);
  return 0i64;
}

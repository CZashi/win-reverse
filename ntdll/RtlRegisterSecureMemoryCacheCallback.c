// https://learn.microsoft.com/en-us/windows/win32/api/winnt/nc-winnt-psecure_memory_cache_callback
// RtlRegisterSecureMemoryCacheCallback function is to monitors changes about secured memory range (nt!MmSecureVirtualMemory) like free/mem prot.
// getting through RtlpSecMemListHead linked list is ez, just search for PsecureMemoryCacheCallback in sec and return a ptr to the undoc struct containing entries :
/*
typedef struct _secure_mem_item {
    LIST_ENTRY                    lists;
    ULONG                         revision;
    ULONG                         reserved;
    PVOID                         callback; // callback defined in doc.
} secure_mem_item, *psecure_mem_item;
*/ 

NTSTATUS __fastcall RtlRegisterSecureMemoryCacheCallback(__int64 a1)
{
  NTSTATUS result; // eax
  __int64 Heap; // rax
  _QWORD *v4; // rbx
  void **v5; // rax


  // Retrieve the system range start address.
  result = NtQuerySystemInformation(SystemRangeStartInformation, &RtlSecureMemorySystemRangeStart, 8u, 0i64);
  
  if ( result >= 0 )
  {
    Heap = RtlAllocateHeap(NtCurrentPeb()->ProcessHeap, 0i64, 32i64);
    v4 = (_QWORD *)Heap;
    if ( Heap )
    {
      *(_DWORD *)(Heap + 16) = 1;
      *(_QWORD *)(Heap + 24) = a1;
      RtlAcquireSRWLockExclusive(&RtlpSecMemLock);
      v5 = off_180166A88;
      if ( *off_180166A88 != &RtlpSecMemListHead )
        __fastfail(3u);
      *v4 = &RtlpSecMemListHead;
      v4[1] = v5;
      *v5 = v4;
      off_180166A88 = (void **)v4;
      RtlReleaseSRWLockExclusive(&RtlpSecMemLock);
      return 0;
    }
    else
    {
      return -1073741801;
    }
  }
  return result;
}


__int64 __fastcall RtlpSecMemFreeVirtualMemory(__int64 a1, __int64 *a2, __int64 *a3)
{
  unsigned int v5; // esi

  v5 = ZwFreeVirtualMemory(-1i64);
  if ( v5 == -1073741755 && RtlFlushSecureMemoryCache(*a2, *a3) )
    return ZwFreeVirtualMemory(-1i64);
  else
    return v5;
}

char __fastcall RtlFlushSecureMemoryCache(__int64 a1, __int64 a2)
{
  char v4[12]; // [rsp+30h] [rbp-38h] BYREF
  int v5; // [rsp+3Ch] [rbp-2Ch]
  __int64 v6; // [rsp+40h] [rbp-28h]

  if ( RtlpSecMemListHead != &RtlpSecMemListHead )
  {
    if ( a2 )
      return RtlpCallSecureMemoryCallbacks(a1, a2);
    if ( (int)ZwQueryVirtualMemory(-1i64, a1, 3i64, v4, 48i64, 0i64) >= 0 && v5 != 0x10000 )
    {
      a2 = v6;
      return RtlpCallSecureMemoryCallbacks(a1, a2);
    }
  }
  return 0;
}


char __fastcall RtlpCallSecureMemoryCallbacks(__int64 a1, __int64 a2)
{
  char v4; // r14
  void **v5; // rsi
  _DWORD *v6; // rbx
  __int64 **v7; // rdi
  bool v8; // zf
  void ***v9; // rax
  __int64 **v10; // rax
  __int64 v11; // r8
  __int64 v12; // rax
  __int64 v14; // [rsp+20h] [rbp-10h] BYREF
  __int64 **v15; // [rsp+28h] [rbp-8h]

  v15 = (__int64 **)&v14;
  v14 = (__int64)&v14;
  v4 = 0;
  RtlAcquireSRWLockExclusive(&RtlpSecMemLock);
  v5 = (void **)RtlpSecMemListHead;
  if ( RtlpSecMemListHead != &RtlpSecMemListHead )
  {
    do
    {
      v6 = v5 + 2;
      v7 = (__int64 **)v5;
      ++*((_DWORD *)v5 + 4);
      RtlReleaseSRWLockExclusive(&RtlpSecMemLock);
      if ( ((unsigned __int8 (__fastcall *)(__int64, __int64))v5[3])(a1, a2) )
        v4 = 1;
      RtlAcquireSRWLockExclusive(&RtlpSecMemLock);
      v8 = (*v6)-- == 1;
      v5 = (void **)*v5;
      if ( v8 )
      {
        if ( v5[1] != v7
          || (v9 = (void ***)v7[1], *v9 != (void **)v7)
          || (*v9 = v5, v5[1] = v9, v10 = v15, *v15 != &v14) )
        {
LABEL_15:
          __fastfail(3u);
        }
        v7[1] = (__int64 *)v15;
        *v7 = &v14;
        *v10 = (__int64 *)v7;
        v15 = v7;
      }
    }
    while ( v5 != &RtlpSecMemListHead );
  }
  RtlReleaseSRWLockExclusive(&RtlpSecMemLock);
  while ( 1 )
  {
    v11 = v14;
    if ( (__int64 *)v14 == &v14 )
      return v4;
    if ( *(__int64 **)(v14 + 8) != &v14 )
      goto LABEL_15;
    v12 = *(_QWORD *)v14;
    if ( *(_QWORD *)(*(_QWORD *)v14 + 8i64) != v14 )
      goto LABEL_15;
    v14 = *(_QWORD *)v14;
    *(_QWORD *)(v12 + 8) = &v14;
    RtlFreeHeap(NtCurrentPeb()->ProcessHeap, 0i64, v11);
  }
}

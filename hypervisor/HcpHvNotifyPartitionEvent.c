__int64 __fastcall HcpHvNotifyPartitionEvent(_DWORD *a1)
{
  __int64 v1; // x8
  unsigned int v2; // w19
  int v3; // w8
  unsigned __int16 v4; // w0
  struct _TEB *i; // x8
  __int64 v6; // x8
  char v7; // w8
  unsigned __int64 v9[10]; // [xsp+30h] [xbp-50h] BYREF

  if ( *a1 == 1 )
  {
    v6 = *(_QWORD *)(*((_QWORD *)NtCurrentTeb() + 4181) + 216i64);
    if ( (v6 & 0x100000000000i64) != 0 )
      v2 = 0;
    else
      v2 = 6;
    if ( (v6 & 0x100000000000i64) != 0 && KdDebuggingEnabled )
    {
      if ( DbgGlobalContext != 1 && dword_F800000D7644 == 3 )
      {
        if ( (unsigned __int16)DbgNetReinitialize() )
          v7 = DbgGlobalContext;
        else
          v7 = 1;
        DbgGlobalContext = v7;
      }
      if ( (unsigned __int8)KdPollBreakIn() )
        KdBreakPointWithStatus();
    }
  }
  else
  {
    if ( *a1 != 2 )
      return 5;
    v1 = *(_QWORD *)(*((_QWORD *)NtCurrentTeb() + 4181) + 216i64);
    if ( (v1 & 0x100000000000i64) != 0 )
      v2 = 0;
    else
      v2 = 6;
    if ( (v1 & 0x100000000000i64) != 0 )
    {
      v3 = a1[1];
      if ( v3 == 1 )
      {
        do
        {
          _mm_prefetcht2(v3++, &HcpCrashdumpAction);
          _mm_prefetchnta((__int32)&unk_F80000110000, v3, &HcpCrashdumpAction);
        }
        while ( (unsigned int)&unk_F80000110000 );
        __dmb(0xBu);
        if ( v3 == 1 )
        {
          v4 = KeSuspendProcessors(0i64);
          v2 = v4;
          if ( !v4 )
          {
            for ( i = NtCurrentTeb(); ; _mm_prefetchnta(33448, (__int64)i, &ObpPartitionSuspendCount) )
            {
              _mm_prefetcht2((__int64)i, &ObpPartitionSuspendCount);
              i = (struct _TEB *)((char *)i + 1);
            }
          }
          return v2;
        }
        return 5;
      }
      if ( v3 == 2 )
      {
        if ( HcpCrashdumpInitiated )
        {
          **((_DWORD **)NtCurrentTeb() + 4180) = 5;
          return v2;
        }
        return 5;
      }
      if ( v3 != 3 || KeBugCheckData != 25 )
        return 5;
      _mm_prefetcht1(KeNumberProcessors, &KdCrashdumpProcessorBarrier);
      _mm_prefetcht1(KeNumberProcessors, &unk_F8000042F4FC);
      _mm_prefetcht1(1, &KeExitMinimalDispatchLoopFlag);
      if ( (unsigned __int8)CpuSetCopyAndExcludeProcessor(v9, KepActiveProcessors, *((_DWORD *)NtCurrentTeb() + 2)) )
        KepSendSpecialIpiRequest(v9, 5, 0i64, 0);
      return 0;
    }
  }
  return v2;
}

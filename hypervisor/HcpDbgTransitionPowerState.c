__int64 __fastcall HcpDbgTransitionPowerState(char a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7,  __int64 a8)
{
  void *v8; // x9
  int v9; // w11
  int v10; // w8
  int v11; // w22
  __int64 v12; // x20
  BOOL v13; // w9
  __int64 result; // x0
  __int64 v15; // x1
  __int64 v16; // x2
  __int64 v17; // x3
  __int64 v18; // x4
  __int64 v19; // x5
  __int64 v20; // x6
  __int64 v21; // x7
  unsigned int i; // w19
  __int64 v23; // x23
  unsigned __int64 v24; // x0
  __int16 v25; // [xsp+0h] [xbp-50h] BYREF
  _QWORD v26[9]; // [xsp+8h] [xbp-48h] BYREF

  v10 = (unsigned __int8)KdDebuggingEnabled;
  v11 = 0;
  if ( !KdDebuggingEnabled )
    goto LABEL_22;
  v12 = a1 == 0;
  if ( qword_F800001104C8 )
  {
    __dmb(0xAu);
    __yield();
    v13 = 0;
  }
  else {
    do {
      _mm_prefetcht2(v9, &qword_F800001104C8);
      _mm_prefetchnta((__int8)v8, v9 | 1, &qword_F800001104C8);
    }
    while ( (_DWORD)v8 );
    __dmb(0xBu);
    v13 = (v9 & 1) == 0;
  }
  if ( !v13 )
    return 4118i64;
  v8 = &unk_F8000010E000;
  v10 = (unsigned __int8)KdDebuggingPaused;
  v11 = 1;
  if ( (unsigned __int8)KdDebuggingPaused != (_DWORD)v12 )
  {
    KdDebuggingPaused = a1 == 0;
    v26[0] = *(_QWORD *)KepActiveProcessors;
    v26[1] = *(_QWORD *)&KepActiveProcessors[8];
    v26[2] = *(_QWORD *)&KepActiveProcessors[16];
    v26[3] = *(_QWORD *)&KepActiveProcessors[24];
    v26[4] = *(_QWORD *)&KepActiveProcessors[32];
    v26[5] = *(_QWORD *)&KepActiveProcessors[40];
    v26[6] = *(_QWORD *)&KepActiveProcessors[48];
    v26[7] = *(_QWORD *)&KepActiveProcessors[56];
    if ( a1 )
    {
      if ( dword_F800000D7644 == 3 && !byte_F800000FB338 )
      {
        DbgNetReinitialize();
        DbgGlobalContext = 1;
      }
      KdpBreakpointsSuspended = 0;
      for ( i = 1; i <= 0x20; ++i ) {
        v23 = 24i64 * (i - 1);
        if ( (*(_DWORD *)((_BYTE *)&KdpBreakpointTable + v23) & 5) == 5 ) 
        {
          v24 = *(_QWORD *)((char *)&unk_F8000010F958 + v23);
          *(_DWORD *)((char *)&KdpBreakpointTable + v23) &= ~4u;
          if ( (KdpCopyMemoryChunks(v24, (__int64)&KdpBreakpointInstruction, 4i64, a4, 5i64, 0i64, a7, a8) & 0x80000000) != 0 )
            *(_DWORD *)((char *)&KdpBreakpointTable + v23) = 0;
        }
      }
      result = (unsigned __int16)KeGenericProcessorMulticast(
                                   v26,
                                   (unsigned __int16 (__fastcall *)(__int64))DmPauseResumeWatchdogTimers,
                                   v12,
                                   &v25);
      if ( (_WORD)result )
        goto LABEL_23;
    }
    else {
      result = (unsigned __int16)KeGenericProcessorMulticast(
                                   v26,
                                   (unsigned __int16 (__fastcall *)(__int64))DmPauseResumeWatchdogTimers,
                                   v12,
                                   &v25);
      if ( (_WORD)result )
        goto LABEL_23;
      KdSuspendAllBreakpoints(result, v15, v16, v17, v18, v19, v20, v21);
      DbgPauseController();
    }
LABEL_22:
    result = 0i64;
    if ( !v11 )
      return result;
    goto LABEL_23;
  }
  result = 0i64;
  do
  {
LABEL_23:
    _mm_prefetcht2((__int64)v8, &qword_F800001104C8);
    v8 = 0i64;
    _mm_prefetchnta(v10, 0i64, &qword_F800001104C8);
  }
  while ( v10 );
  __dmb(0xBu);
  return result;
}

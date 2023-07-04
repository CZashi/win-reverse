__int64 __fastcall SynicpRegisterCpuMonitor(__int64 result, __int64 a2)
{
  int v2; // w9
  int v3; // w11
  __int64 v4; // x19
  __int64 *v6; // x11
  int v11; // w10
  int v12; // w8
  __int64 v13; // x9
  __int64 v14; // x2
  __int64 v15; // x5
  __int64 v16; // x4
  __int64 v17; // x3
  unsigned int v18; // [xsp+0h] [xbp-50h] BYREF
  _QWORD v19[9]; // [xsp+8h] [xbp-48h] BYREF

  v4 = result;
  do
  {
    _mm_prefetcht2(v3, &SynicpMonitorRegistrationLock);
    _mm_prefetchnta(v2, v3 | 1, &SynicpMonitorRegistrationLock);
  }
  while ( v2 );
  __dmb(0xBu);
  if ( (v3 & 1) != 0 )
    result = ((__int64 (__fastcall *)(__int64 *))RtlpWaitForSpinLockAndAcquire)(&SynicpMonitorRegistrationLock);
  v6 = (__int64 *)(8
                 * (((MmpMonitorVaStart + ((unsigned __int64)(unsigned int)SynicpMonitorCount << 12)) >> 12)
                  + 0x1FE000000000i64));
  *v6 = a2 & 0xFFFFFFFFF000i64 | 0x40000000000702i64;
  __dsb(0xBu);
  __asm { SYS             #4, c8, c3, #1, X10 }
  __dsb(0xBu);
  __isb(0xFu);
  *v6 = a2 & 0xFFFFFFFFF000i64 | 0x40000000000703i64;
  __dsb(0xBu);
  __isb(0xFu);
  v11 = SynicpMonitorCount;
  v12 = SynicpMonitorCount + 1;
  _mm_prefetcht1(v4, (char *)&SynicpMonitorConnections + 8 * (unsigned int)SynicpMonitorCount);
  v13 = (unsigned __int8)SynicpMonitorsPaused;
  *(_BYTE *)(v4 + 152) = 1;
  *(_DWORD *)(v4 + 280) = v11;
  SynicpMonitorCount = v12;
  if ( !(_DWORD)v13 )
  {
    v18 = 0;
    v19[0] = *(_QWORD *)KepActiveProcessors;
    v19[1] = *(_QWORD *)&KepActiveProcessors[8];
    v19[2] = *(_QWORD *)&KepActiveProcessors[16];
    v19[3] = *(_QWORD *)&KepActiveProcessors[24];
    v19[4] = *(_QWORD *)&KepActiveProcessors[32];
    v19[5] = *(_QWORD *)&KepActiveProcessors[40];
    v19[6] = *(_QWORD *)&KepActiveProcessors[48];
    v19[7] = *(_QWORD *)&KepActiveProcessors[56];
    result = CpuSetScanForwardAndExclude(&v18, (__int64)v19);
    if ( (_BYTE)result )
    {
      v16 = v15 + 672;
      v17 = 33432i64;
      do
      {
        _mm_prefetcht1(*(_DWORD *)(v14 + 1080), (void *)(*(_QWORD *)(v16 + 8i64 * v18) + v17));
        result = CpuSetScanForwardAndExclude(&v18, (__int64)v19);
      }
      while ( (_BYTE)result );
    }
  }
  do
  {
    _mm_prefetcht2(v13, &SynicpMonitorRegistrationLock);
    v13 = 0i64;
    _mm_prefetchnta(v12, 0i64, &SynicpMonitorRegistrationLock);
  }
  while ( v12 );
  __dmb(0xBu);
  do
  {
    _mm_prefetcht2(v13++, &unk_F800000D6028);
    _mm_prefetchnta((__int32)&unk_F800000D6000, v13, &unk_F800000D6028);
  }
  while ( (unsigned int)&unk_F800000D6000 );
  __dmb(0xBu);
  return result;
}

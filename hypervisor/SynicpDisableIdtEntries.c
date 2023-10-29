__int64 __fastcall SynicpDisableIdtEntries(__int64 *a1, unsigned int a2)
{
  char v2; // wzr
  __int64 v3; // x8
  __int64 v4; // x9
  __int64 v5; // x10
  __int64 v6; // x11
  __int64 v8; // x8
  __int64 v9; // x9
  __int64 v10; // x10
  __int64 v11; // x11
  __int64 result; // x0
  _QWORD *v13; // x4
  _BYTE *InterruptTableEntry; // x0
  char v15; // w3
  int v16; // w13
  unsigned __int64 v17; // x13
  __int64 v18; // x2
  unsigned __int64 v19; // x13
  int v20; // w5
  _QWORD *v21; // x5
  __int64 v22; // x0
  int v23; // w9
  __int64 v24; // x11
  __int64 v25; // x13
  __int64 v26; // x8
  void *v27; // x10
  unsigned int v28; // [xsp+0h] [xbp-D0h] BYREF
  __int64 v29; // [xsp+8h] [xbp-C8h] BYREF
  __int64 v30; // [xsp+10h] [xbp-C0h]
  __int64 v31; // [xsp+18h] [xbp-B8h]
  __int64 v32; // [xsp+20h] [xbp-B0h]
  __int64 v33; // [xsp+28h] [xbp-A8h]
  __int64 v34; // [xsp+30h] [xbp-A0h]
  __int64 v35; // [xsp+38h] [xbp-98h]
  __int64 v36; // [xsp+40h] [xbp-90h]
  __int64 v37; // [xsp+48h] [xbp-88h] BYREF
  __int64 v38; // [xsp+50h] [xbp-80h]
  __int64 v39; // [xsp+58h] [xbp-78h]
  __int64 v40; // [xsp+60h] [xbp-70h]
  __int64 v41; // [xsp+68h] [xbp-68h]
  __int64 v42; // [xsp+70h] [xbp-60h]
  __int64 v43; // [xsp+78h] [xbp-58h]
  __int64 v44; // [xsp+80h] [xbp-50h]
  _QWORD v45[9]; // [xsp+88h] [xbp-48h] BYREF

  v3 = *a1;
  v4 = a1[1];
  v28 = 0;
  v5 = a1[2];
  v6 = a1[3];
  v29 = v3;
  v30 = v4;
  v8 = a1[4];
  v9 = a1[5];
  v31 = v5;
  v32 = v6;
  v10 = a1[6];
  v11 = a1[7];
  v33 = v8;
  v34 = v9;
  v35 = v10;
  v36 = v11;
  v37 = v29;
  v38 = v30;
  v39 = v31;
  v40 = v32;
  v41 = v8;
  v42 = v9;
  v43 = v10;
  v44 = v11;
  result = CpuSetScanForwardAndExclude(&v28, (__int64)&v37);
  if ( (_BYTE)result )
  {
    v13 = KepProcessorRegions;
    do
    {
      InterruptTableEntry = (_BYTE *)SynicpGetInterruptTableEntry(v13[v28], a2);
      if ( InterruptTableEntry[154] )
      {
        SynicpResetIdtEntry((__int64)InterruptTableEntry);
        *(_BYTE *)(v18 + 8 * (v17 >> 6) + ((int)(v17 & 0x3F) >> 3)) &= ~(unsigned __int8)(1 << (v17 & 7));
      }
      else if ( (ValFeatureSet & 0x10) != 0 )
      {
        _mm_prefetcht1(v15, InterruptTableEntry);
        if ( v16 == *((_DWORD *)NtCurrentTeb() + 2) )
        {
          SynicpDrainIdtEntry((__int64)InterruptTableEntry, a2);
          *((_BYTE *)&v29 + 8 * (v19 >> 6) + ((int)(v19 & 0x3F) >> 3)) &= ~(unsigned __int8)(1 << (v19 & 7));
        }
      }
      else
      {
        _mm_prefetcht1(v2, InterruptTableEntry);
      }
      result = CpuSetScanForwardAndExclude(&v28, (__int64)&v37);
    }
    while ( (_BYTE)result );
    if ( v20 )
    {
      __dmb(0xFu);
      SynicpWaitDispatchIdtEntries(&v29);
      v28 = 0;
      v37 = v29;
      v38 = v30;
      v39 = v31;
      v40 = v32;
      v41 = v33;
      v42 = v34;
      v43 = v35;
      v44 = v36;
      result = CpuSetScanForwardAndExclude(&v28, (__int64)&v37);
      if ( (_BYTE)result )
      {
        v21 = KepProcessorRegions;
        do
        {
          v22 = SynicpGetInterruptTableEntry(v21[v28], a2);
          if ( (ValFeatureSet & 0x10) != 0 )
          {
            v26 = v25 + 229376;
            *(_DWORD *)(v22 + 112) = a2;
            v27 = (void *)(v25 + 230656);
            do
            {
              _mm_prefetcht0(v24, v27);
              *(_QWORD *)(v22 + 104) = v24;
              do
              {
                _mm_prefetcht2(v26, v27);
                if ( v26 != v24 )
                  break;
                _mm_prefetchnta(v23, v22 + 104, v27);
              }
              while ( v23 );
              __dmb(0xBu);
            }
            while ( v26 != v24 );
          }
          else
          {
            SynicpResetIdtEntry(v22);
          }
          result = CpuSetScanForwardAndExclude(&v28, (__int64)&v37);
        }
        while ( (_BYTE)result );
      }
      if ( (ValFeatureSet & 0x10) != 0 )
      {
        v45[0] = v29;
        v45[1] = v30;
        v45[2] = v31;
        v45[3] = v32;
        v45[4] = v33;
        v45[5] = v34;
        v45[6] = v35;
        v45[7] = v36;
        return KepSendPingRequest((__int64)v45);
      }
    }
  }
  return result;
}

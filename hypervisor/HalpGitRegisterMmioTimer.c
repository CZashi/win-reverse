__int64 __fastcall HalpGitRegisterMmioTimer(unsigned __int8 *a1, __int64 a2, __int64 a3)
{
  int v4; // w8
  __int64 result; // x0
  unsigned int v7; // w10
  int v8; // w11
  __int64 v9; // x10
  int v10; // w9
  int v11; // w8
  __int64 *v12; // x8
  __int64 v13; // x0
  int v14; // w8
  int v15; // w8
  int v16; // w8
  int v17; // w9
  int v18; // w8
  __int64 v19; // x2
  __int64 v20; // x3
  __int64 v21; // x10
  __int64 v22; // [xsp+10h] [xbp+10h] BYREF
  int v23[6]; // [xsp+18h] [xbp+18h] BYREF
  __int64 v24; // [xsp+30h] [xbp+30h]
  __int64 v25; // [xsp+38h] [xbp+38h]
  __int64 v26; // [xsp+40h] [xbp+40h]
  __int64 v27; // [xsp+48h] [xbp+48h]
  int v28[2]; // [xsp+50h] [xbp+50h] BYREF
  __int64 (__fastcall *v29)(__int64); // [xsp+58h] [xbp+58h]
  __int64 (__fastcall *v30)(__int64); // [xsp+68h] [xbp+68h]
  __int64 (__fastcall *v31)(__int64, int, __int64); // [xsp+70h] [xbp+70h]
  __int64 (__fastcall *v32)(__int64); // [xsp+78h] [xbp+78h]
  int *v33; // [xsp+A8h] [xbp+A8h]
  int v34; // [xsp+B0h] [xbp+B0h]
  int v35; // [xsp+B4h] [xbp+B4h]
  __int64 v36; // [xsp+B8h] [xbp+B8h]
  int v37; // [xsp+C4h] [xbp+C4h]
  int v38; // [xsp+CCh] [xbp+CCh]
  int v39; // [xsp+D0h] [xbp+D0h]
  BOOL v40; // [xsp+D4h] [xbp+D4h]
  int v41; // [xsp+D8h] [xbp+D8h]
  int v42; // [xsp+DCh] [xbp+DCh]
  __int64 v43; // [xsp+E0h] [xbp+E0h] BYREF

  v4 = *((_DWORD *)a1 + 9);
  result = 0i64;
  if ( (v4 & 1) == 0 )
  {
    __dsb(0xFu);
    v7 = *a1;
    if ( ((*(_DWORD *)(a2 + 8) >> (4 * v7)) & 1) != 0 )
    {
      v8 = *((_DWORD *)a1 + 6);
      __dsb(0xFu);
      v9 = v7 + 16i64;
      v10 = *(_DWORD *)(a2 + 4 * v9);
      __dsb(0xFu);
      *(_DWORD *)(a2 + 4 * v9) = v10 | 0x25;
      __dsb(0xFu);
      v11 = *(_DWORD *)(a2 + 4 * v9) & 0x25;
      if ( v11 == 37 )
        result = 0i64;
      else
        result = 3221225858i64;
      if ( v11 == 37 )
      {
        v12 = (__int64 *)v28;
        do
        {
          *v12 = 0i64;
          v12[1] = 0i64;
          v12 += 2;
        }
        while ( v12 != &v43 );
        v13 = *(_QWORD *)(a1 + 4);
        v28[1] = 144;
        v35 = 64;
        v33 = v23;
        v41 = 11;
        v36 = (unsigned int)HalpGitFrequency;
        v34 = 56;
        v14 = *a1;
        v29 = HalpGitInitialize;
        memset(v23, 0, sizeof(v23));
        v24 = 0i64;
        v25 = 0i64;
        v26 = 0i64;
        v42 = v14 + 2;
        v31 = HalpGitArmTimer;
        v32 = HalpGitStop;
        v27 = 0i64;
        v30 = HalpGitAcknowledgeInterrupt;
        v15 = *((_DWORD *)a1 + 9);
        v28[0] = 1;
        v16 = (v15 & 2) != 0 ? 2130464 : 2097696;
        v17 = *((_DWORD *)a1 + 5);
        v37 = v16;
        v18 = (v8 & 2) != 0 ? 2 : 1;
        v38 = v17;
        v39 = v18;
        v40 = (v8 & 1) != 0;
        result = ExtEnvMapIoSpace(v13, 0xFFDu, a3, &v22);
        if ( (result & 0x80000000) == 0 )
        {
          result = ExtEnvRegisterPermanentAddressUsage(*(_QWORD *)(a1 + 4), 0xFFDu, v19, v20);
          if ( (result & 0x80000000) == 0 )
          {
            v21 = v22;
            __dsb(0xFu);
            if ( HalpGitFrequency == *(_DWORD *)(v21 + 16) )
            {
              v25 = v21;
              v26 = a2;
              v23[0] = 3;
              LODWORD(v24) = 3;
              LODWORD(v27) = *a1;
              return HalpTimerRegister((__int64)v28);
            }
            else
            {
              return 3221225485i64;
            }
          }
        }
      }
    }
  }
  return result;
}

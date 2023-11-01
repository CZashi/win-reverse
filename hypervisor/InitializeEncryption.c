__int64 __fastcall InitializeEncryption(__int64 a1, __int64 a2)
{
  __int64 v2; // x20
  void *v4; // x9
  int v5; // w9
  char *v6; // x11
  int *v7; // x12
  int v8; // w10
  int v9; // t1
  int *v10; // x9
  __int64 v11; // x8
  char *v12; // x10
  __int64 v13; // x8
  int v15[2]; // [xsp+0h] [xbp-30h] BYREF
  char v16[40]; // [xsp+8h] [xbp-28h] BYREF

  v2 = KdNetData;
  if ( !KdNetData || !a2 || !*(_BYTE *)(a2 + 313) )
    return 3221225485i64;
  v4 = &unk_F80000110000;
  if ( (g_SymCryptFlags & 1) == 0 )
  {
    do
    {
      _mm_prefetcht2((__int32)v4, &g_SymCryptFlags);
      LODWORD(v4) = (unsigned int)v4 | 1;
      _mm_prefetchnta(g_SymCryptFlags, (__int32)v4, &g_SymCryptFlags);
    }
    while ( g_SymCryptFlags );
    __dmb(0xBu);
    v15[1] = 4915200;
    g_SymCryptCpuFeaturesPresentCheck = 0;
  }
  v5 = 0;
  v6 = v16;
  v7 = (int *)(a2 + 336);
  v8 = 8;
  do
  {
    v9 = *v7++;
    --v8;
    v5 |= v9;
    *(_DWORD *)v6 = ~v9;
    v6 += 4;
  }
  while ( v8 );
  v15[0] = v5;
  if ( !v5 || (unsigned int)SymCryptHmacSha256ExpandKey(v2 + 80, (__int64)v16, 0x20ui64) )
    return 3221225485i64;
  SymCryptAesExpandKeyInternal((__int64 *)(v2 + 160), (__int64 *)(a2 + 336), 32i64);
  if ( *(_DWORD *)(a2 + 316) )
    SymCryptAesExpandKeyInternal((__int64 *)(v2 + 656), (__int64 *)(a2 + 368), 32i64);
  v15[0] = 0;
  v10 = v15;
  v11 = 4i64;
  do
  {
    *(_BYTE *)v10 = 0;
    v10 = (int *)((char *)v10 + 1);
    --v11;
  }
  while ( v11 );
  v12 = v16;
  v13 = 32i64;
  do
  {
    *v12++ = 0;
    --v13;
  }
  while ( v13 );
  return 0i64;
}

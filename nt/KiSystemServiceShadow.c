__int64 __fastcall KiSystemServiceShadow()
{
  unsigned __int64 v0; // rsi
  _KIDTENTRY64 *v3; // rsi
  __int64 v5; // [rsp-28h] [rbp-28h] BYREF
  _KIDTENTRY64 v6; // [rsp-20h] [rbp-20h]
  _KIDTENTRY64 v7; // [rsp-10h] [rbp-10h]

  if ( (v6.OffsetLow & 1) != 0 )
  {
    __asm { swapgs }
    _mm_lfence();
    if ( !_bittest(MK_FP(__GS__, 36888i64), 1u) )
      __writecr3((unsigned __int64)&v5);
    __writegsqword(0x10u, v0);
    v3 = KeGetPcr()->IdtBase + 1056;
    v7 = v3[-1];
    v6 = v3[-2];
    v5 = *(&v3[-3].Alignment + 1);
    __writegsqword(0x10u, 0i64);
    return KiSystemService();
  }
  else
  {
    _mm_lfence();
    return KiSystemService();
  }
}

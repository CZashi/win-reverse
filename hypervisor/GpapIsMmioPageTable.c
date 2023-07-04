bool __fastcall GpapIsMmioPageTable(unsigned __int8 a1, int a2, unsigned __int64 a3)
{
  unsigned __int64 v4; // x10
  unsigned __int64 v5; // x8

  if ( a2 == 3 )
    return 0i64;
  v4 = *(_QWORD *)(8
                 * (((*(_QWORD *)(8
                                * (((*(_QWORD *)(GpapMmioData + 8 * (a2 + 4i64 * a1 + 15))
                                   + 8 * (a3 >> (9 * (unsigned __int8)a2 + 12))) >> 12)
                                 + 0x1FE000000000i64)) >> 12) & 0xFFFFFFFFFi64)
                  + 0x1FC000000000i64));
  v5 = HIDWORD(v4);
  if ( a2 > 1 )
    v5 = v4 >> 8;
  return (v5 & 0x400) != 0;
}

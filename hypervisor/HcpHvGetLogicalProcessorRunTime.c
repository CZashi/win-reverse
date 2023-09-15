__int64 __fastcall HcpHvGetLogicalProcessorRunTime(unsigned int *a1, __int64 *a2)
{
  __int64 result; // x0
  int v4; // w12
  __int64 v5; // x9
  __int64 v6; // x8
  __int64 v7; // [xsp+0h] [xbp-20h] BYREF
  __int64 v8; // [xsp+8h] [xbp-18h]
  __int64 v9; // [xsp+10h] [xbp-10h]

  v7 = 0i64;
  v8 = 0i64;
  v9 = 0i64;
  if ( (*(_QWORD *)(*((_QWORD *)NtCurrentTeb() + 4181) + 208i64) & 1) == 0 )
    return 6i64;
  if ( !(unsigned __int8)KeIsValidLpIndex(*a1) )
    return 65i64;
  LOWORD(result) = KeGenericProcessorCall(
                     dword_F800004352BC[8 * v4],
                     (unsigned __int16 (__fastcall *)(__int64))KeGetProcessorRuntime,
                     (__int64)&v7);
  v5 = v9;
  a2[1] = v8;
  a2[2] = 0i64;
  v6 = v7;
  result = (unsigned __int16)result;
  a2[3] = v5;
  *a2 = v6;
  return result;
}

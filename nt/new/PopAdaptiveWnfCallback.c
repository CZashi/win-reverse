__int64 __fastcall PopAdaptiveWnfCallback(__int64 a1, _QWORD *a2)
{
  bool v2; // zf
  __int64 result; // rax
  int v4; // r8d
  int v5; // r9d
  unsigned int v6; // [rsp+20h] [rbp-38h] BYREF
  char v7[8]; // [rsp+28h] [rbp-30h] BYREF
  __int128 v8; // [rsp+30h] [rbp-28h] BYREF

  v2 = *a2 == WNF_HPM_GLOBAL_HUMAN_PRESENCE_STATE;
  v8 = 0i64;
  if ( v2 )
  {
    v6 = 16;
    result = ExQueryWnfStateData(a1, v7, &v8, &v6);
    if ( (int)result < 0 )
      return result;
    if ( v6 < 0x10 )
      return 3221225485i64;
    if ( !PopConsoleSession || !DWORD2(v8) || SDWORD2(v8) >= 3 )
      return 0i64;
    PopAcquireAdaptiveLock(0i64);
    if ( DWORD2(v8) == 2 )
    {
      v4 = PopAdaptiveSensorInattentiveDisplayTimeout;
      if ( PopAdaptiveSensorInattentiveDisplayTimeout
        || PopAdaptiveSensorInattentiveDimTimeout != PopAdaptiveSensorInattentiveDisplayTimeout )
      {
        v5 = PopAdaptiveSensorInattentiveDimTimeout;
LABEL_16:
        qword_140E250C8 = v8;
        byte_140E250C0 = 1;
        dword_140E250D0 = v4;
        dword_140E250D4 = v5;
        PopDiagTraceAdaptiveOverrideTriggered(v8, 0i64);
LABEL_18:
        PopReleaseAdaptiveLock();
        return 0i64;
      }
    }
    else if ( DWORD2(v8) == 1 )
    {
      v4 = PopAdaptiveSensorAwayDisplayTimeout;
      if ( PopAdaptiveSensorAwayDisplayTimeout || PopAdaptiveSensorAwayDimTimeout != PopAdaptiveSensorAwayDisplayTimeout )
      {
        v5 = PopAdaptiveSensorAwayDimTimeout;
        goto LABEL_16;
      }
    }
    PopAdaptiveConsoleSessionOverrideClear(0i64);
    goto LABEL_18;
  }
  return 3221225659i64;
}

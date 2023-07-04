__int64 __fastcall HalpFindKnownHypervisorTimer(int a1)
{
  __int64 result; // x0

  result = HalpHvRegisteredTimerList;
  if ( (__int64 *)HalpHvRegisteredTimerList == &HalpHvRegisteredTimerList )
    return 0;
  while ( *(_DWORD *)(result + 340) != a1 )
  {
    result = *(_QWORD *)result;
    if ( (__int64 *)result == &HalpHvRegisteredTimerList )
      return 0i64;
  }
  return result;
}

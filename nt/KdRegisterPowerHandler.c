__int64 __fastcall KdRegisterPowerHandler(__int64 a1, __int64 a2, char **a3)
{
  _QWORD *PoolWithTag; // rax
  __int64 v7; // rbx
  unsigned __int8 CurrentIrql; // di
  __int64 *v10; // rax

  PoolWithTag = ExAllocatePoolWithTag(NonPagedPoolNx, 0x20u, 0x6F49644Bu);
  v7 = (__int64)PoolWithTag;
  if ( !PoolWithTag )
    return 3221225626i64;
  PoolWithTag[2] = a1;
  PoolWithTag[3] = a2;
  CurrentIrql = KeGetCurrentIrql();
  __writecr8(0xFui64);
  KxAcquireSpinLock(&KdpPowerSpinLock);
  v10 = (__int64 *)qword_140C40598;
  if ( *(__int64 **)qword_140C40598 != &KdpPowerListHead )
    __fastfail(3u);
  *(_QWORD *)v7 = &KdpPowerListHead;
  *(_QWORD *)(v7 + 8) = v10;
  *v10 = v7;
  qword_140C40598 = v7;
  KxReleaseSpinLock(&KdpPowerSpinLock);
  __writecr8(CurrentIrql);
  *a3 = (char *)v7;
  return 0i64;
}

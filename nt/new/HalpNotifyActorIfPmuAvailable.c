__int64 __fastcall HalpNotifyActorIfPmuAvailable(__int64 i)
{
  __int64 result; // rax
  struct _KTHREAD *CurrentThread; // rax
  __int64 v4; // rax
  __int64 v5; // rsi
  __int64 v6; // rcx
  void (__fastcall *v7)(__int64, int *); // rax
  __int64 v8; // rcx
  struct _KTHREAD *v9; // rax
  __int64 v10; // rax
  __int64 v11; // rsi
  __int64 v12; // rcx
  __int64 *v13; // rax
  int v14; // [rsp+48h] [rbp+10h] BYREF
  int v15; // [rsp+4Ch] [rbp+14h]

  result = (unsigned int)dword_140EA28A8;
  if ( dword_140EA28A8 )
    return result;
  result = (unsigned int)(dword_140EA28AC - 3);
  if ( (unsigned int)result > 1 )
    return result;
  CurrentThread = KeGetCurrentThread();
  --CurrentThread->KernelApcDisable;
  v4 = KeAbPreAcquire(&HalpPmuArbiter, 0i64, 0i64);
  v5 = v4;
  if ( _interlockedbittestandset64((volatile signed __int32 *)&HalpPmuArbiter, 0i64) )
    ExfAcquirePushLockExclusiveEx(&HalpPmuArbiter, v4, &HalpPmuArbiter);
  if ( v5 )
    *(_BYTE *)(v5 + 18) = 1;
  v6 = (unsigned int)(dword_140EA28AC - 3);
  if ( dword_140EA28AC != 3 )
  {
    if ( dword_140EA28AC == 4 && qword_140EA28F0 == PsGetCurrentThreadId(v6) )
      dword_140EA28AC = 5;
    goto LABEL_33;
  }
  if ( !dword_140EA28A8 )
  {
    if ( !i )
    {
      for ( i = qword_140EA28B0; (__int64 *)i != &qword_140EA28B0; i = *(_QWORD *)i )
      {
        if ( !*(_BYTE *)(i + 56) )
          goto LABEL_18;
      }
      goto LABEL_33;
    }
LABEL_18:
    dword_140EA28AC = 4;
    qword_140EA28F0 = PsGetCurrentThreadId(v6);
    dword_140EA28F8 = *(_DWORD *)(i + 32);
    ExAcquireRundownProtection_0(i + 48);
    if ( (_InterlockedExchangeAdd64(&HalpPmuArbiter, 0xFFFFFFFFFFFFFFFFui64) & 6) == 2 )
      ExfTryToWakePushLock(&HalpPmuArbiter);
    KeAbPostRelease(&HalpPmuArbiter);
    KeLeaveCriticalRegionThread(KeGetCurrentThread());
    v7 = *(void (__fastcall **)(__int64, int *))(i + 16);
    v8 = *(_QWORD *)(i + 24);
    v15 = 0;
    v14 = 524289;
    v7(v8, &v14);
    v9 = KeGetCurrentThread();
    --v9->KernelApcDisable;
    v10 = KeAbPreAcquire(&HalpPmuArbiter, 0i64, 0i64);
    v11 = v10;
    if ( _interlockedbittestandset64((volatile signed __int32 *)&HalpPmuArbiter, 0i64) )
      ExfAcquirePushLockExclusiveEx(&HalpPmuArbiter, v10, &HalpPmuArbiter);
    if ( v11 )
      *(_BYTE *)(v11 + 18) = 1;
    if ( dword_140EA28AC != 4 )
    {
      if ( dword_140EA28AC != 5 )
      {
LABEL_32:
        dword_140EA28F8 = 0;
        qword_140EA28F0 = 0i64;
        ExReleaseRundownProtection_0(i + 48);
        goto LABEL_33;
      }
      if ( !*(_BYTE *)(i + 56) )
      {
        v12 = *(_QWORD *)i;
        if ( *(_QWORD *)(*(_QWORD *)i + 8i64) != i || (v13 = *(__int64 **)(i + 8), *v13 != i) )
          __fastfail(3u);
        *v13 = v12;
        *(_QWORD *)(v12 + 8) = v13;
        *(_QWORD *)&xmmword_140EA2900 = i;
        *((_QWORD *)&xmmword_140EA2900 + 1) = KeQueryPerformanceCounter(0i64);
        dword_140EA28AC = 2;
        goto LABEL_32;
      }
    }
    dword_140EA28AC = 3;
    goto LABEL_32;
  }
LABEL_33:
  if ( (_InterlockedExchangeAdd64(&HalpPmuArbiter, 0xFFFFFFFFFFFFFFFFui64) & 6) == 2 )
    ExfTryToWakePushLock(&HalpPmuArbiter);
  KeAbPostRelease(&HalpPmuArbiter);
  return KeLeaveCriticalRegionThread(KeGetCurrentThread());
}

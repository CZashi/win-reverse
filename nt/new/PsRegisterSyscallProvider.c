// it's exported by the win11 kernel, maybe we can achieve some syscall interception tech like AltSyscall, Tracepoints (protected now) or ETW based hooking


__int64 __fastcall PsRegisterSyscallProvider(__int64 a1, __int64 a2, __int64 *a3)
{
  __int64 Pool2; // rax
  __int64 v8; // rbx
  int v9; // eax
  int v10; // esi
  int inserted; // edi
  __int64 v12; // rcx
  int v13[4]; // [rsp+20h] [rbp-A8h] BYREF
  char v14[8]; // [rsp+30h] [rbp-98h] BYREF
  __int64 v15; // [rsp+38h] [rbp-90h]

  v13[0] = -1;
  if ( !PspSyscallProvidersEnabled )
    return 3221225629i64;
  if ( *(_BYTE *)a2 != 1 )
    return 3221225561i64;
  Pool2 = ExAllocatePool2(256i64, 96i64, 1666413392i64);
  v8 = Pool2;
  if ( !Pool2 )
    return 3221225626i64;
  PspInitializeSyscallProvider(Pool2, a1, (__int128 *)(a2 + 4), *(_QWORD *)(a2 + 24));
  v9 = VslPublishSyscallProviderServiceTables(*(_QWORD *)(a1 + 24), v13);
  v10 = v13[0];
  inserted = v9;
  if ( v9 < 0 || (*(_DWORD *)(v8 + 92) = v13[0], inserted = PspInsertSyscallProvider((void **)v8), inserted < 0) )
  {
    if ( v10 != -1 )
    {
      memset_0(v14, 0i64, 104i64);
      v15 = *(_QWORD *)(a1 + 24);
      LOBYTE(v12) = 2;
      VslpEnterIumSecureMode(v12, 91i64, 0i64, v14);
    }
    ObfDereferenceObjectWithTag(*(_QWORD *)(v8 + 32), 1666413392i64);
    ExFreePoolWithTag(v8, 1666413392i64);
  }
  else
  {
    *a3 = v8;
    return 0;
  }
  return (unsigned int)inserted;
}


__int64 __fastcall PspInsertSyscallProvider(void **a1)
{
  struct _KTHREAD *CurrentThread; // rax
  __int64 v3; // rax
  __int64 v4; // rsi
  void **v5; // rax
  unsigned int v6; // edi
  __int64 v8; // [rsp+38h] [rbp+10h] BYREF

  v8 = 0i64;
  CurrentThread = KeGetCurrentThread();
  --CurrentThread->KernelApcDisable;
  v3 = KeAbPreAcquire(&PspSyscallProviderRegistrationLock, 0i64, 0i64);
  v4 = v3;
  if ( _interlockedbittestandset64((volatile signed __int32 *)&PspSyscallProviderRegistrationLock, 0i64) )
    ExfAcquirePushLockExclusiveEx(&PspSyscallProviderRegistrationLock, v3, &PspSyscallProviderRegistrationLock);
  if ( v4 )
    *(_BYTE *)(v4 + 18) = 1;
  if ( (unsigned int)PspLookupSyscallProviderByIdNoLock(a1 + 2, &v8) == -1073741275 )
  {
    v5 = off_140F7C328;
    if ( *off_140F7C328 != &PspSyscallProviders )
      __fastfail(3u);
    *a1 = &PspSyscallProviders;
    a1[1] = v5;
    *v5 = a1;
    off_140F7C328 = a1;
    v6 = 0;
  }
  else
  {
    v6 = -1073741771;
  }
  if ( (_InterlockedExchangeAdd64(&PspSyscallProviderRegistrationLock, 0xFFFFFFFFFFFFFFFFui64) & 6) == 2 )
    ExfTryToWakePushLock(&PspSyscallProviderRegistrationLock);
  KeAbPostRelease(&PspSyscallProviderRegistrationLock);
  KeLeaveCriticalRegionThread(KeGetCurrentThread());
  if ( v8 )
    PspDereferenceSyscallProvider(v8);
  return v6;
}

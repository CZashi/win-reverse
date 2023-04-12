void __fastcall __noreturn KiSystemStartup(__int64 a1)
{
  unsigned int *v1; // r10
  unsigned __int64 v3; // r8
  unsigned __int64 v4; // r8
  unsigned __int64 v5; // r8
  unsigned __int64 v6; // r8
  __int64 v7; // r8
  unsigned __int64 v9; // rdx
  void *v10; // rsp
  __int64 v11; // rax
  __int64 v12; // rcx
  __int64 v13; // rdx
  unsigned __int64 v14; // r8
  unsigned __int64 v15; // rax
  __int64 v16; // rax
  bool v17; // zf

  KeLoaderBlock_0 = a1;
  if ( !*(_DWORD *)(*(_QWORD *)(a1 + 136) + 36i64) )
    KdInitSystem(0xFFFFFFFFi64);
  v1 = *(unsigned int **)(KeLoaderBlock_0 + 136);
  _RDX = v1 - 96;
  *((_QWORD *)_RDX + 3) = _RDX;
  *((_QWORD *)_RDX + 4) = v1;
  v3 = __readcr0();
  *((_QWORD *)v1 + 32) = v3;
  v4 = __readcr2();
  *((_QWORD *)v1 + 33) = v4;
  v5 = __readcr3();
  *((_QWORD *)v1 + 34) = v5;
  v6 = __readcr4();
  *((_QWORD *)v1 + 35) = v6;
  __sgdt((char *)v1 + 342);
  v7 = *((_QWORD *)v1 + 43);
  *(_QWORD *)_RDX = v7;
  __sidt((char *)v1 + 358);
  *((_QWORD *)_RDX + 7) = *((_QWORD *)v1 + 45);
  __asm
  {
    str     word ptr [rdx+2F0h]
    sldt    word ptr [rdx+2F2h]
  }
  *v1 = 8064;
  _mm_setcsr(*v1);
  if ( !v1[9] )
    *(_WORD *)(v7 + 80) = 15360;
  if ( !VslVsmEnabled )
  {
    _AX = 0;
    __asm { lldt    ax }
  }
  *MK_FP(43, _RDX + 2) = *MK_FP(43, v7 + 66);
  *MK_FP(43, (char *)_RDX + 10) = *MK_FP(43, v7 + 68);
  *MK_FP(43, (char *)_RDX + 11) = *MK_FP(43, v7 + 71);
  *MK_FP(43, _RDX + 3) = *MK_FP(43, v7 + 72);
  v9 = (unsigned __int64)_RDX >> 32;
  __writemsr(0xC0000101, __PAIR64__(v9, (int)v1 - 384));
  __writemsr(0xC0000102, __PAIR64__(v9, (int)v1 - 384));
  if ( !*MK_FP(43, v1 + 9) )
  {
    _guard_dispatch_icall_fptr = guard_dispatch_icall;
    _guard_check_icall_fptr[0] = guard_check_icall;
  }
  KiInitializeBootStructures(KeLoaderBlock_0);
  if ( !*MK_FP(43, *MK_FP(43, KeLoaderBlock_0 + 136) + 36i64) )
    KdInitSystem(0i64);
  KiInitializeXSave(KeLoaderBlock_0, (unsigned int)*MK_FP(43, *MK_FP(43, KeLoaderBlock_0 + 136) + 36i64));
  __writecr8(0xFui64);
  v10 = alloca((unsigned int)KiXSaveAreaLength);
  v11 = KeLoaderBlock_0;
  v12 = *MK_FP(43, KeLoaderBlock_0 + 144);
  v13 = *MK_FP(43, KeLoaderBlock_0 + 152);
  if ( (KiKvaShadow & 1) != 0 )
  {
    v14 = *MK_FP(43, *MK_FP(43, &KeGetPcr()->IdtBase) + 4216i64);
    __writegsqword(0x9008u, v14);
  }
  else
  {
    v14 = *MK_FP(43, *MK_FP(43, &KeGetPcr()->TssBase) + 4i64);
  }
  __writegsqword(0x1A8u, v14);
  KiInitializeKernel(v12, v13, v14, *MK_FP(43, v11 + 136), *MK_FP(43, *MK_FP(43, v11 + 136) + 36i64), v11);
  if ( !*MK_FP(43, &KeGetPcr()->Prcb.Number) )
  {
    v15 = __rdtsc();
    v16 = __ROL8__(ExpSecurityCookieRandomData ^ __ROR8__(v15, 49) ^ v15, 16);
    LOWORD(v16) = 0;
    _security_cookie = __ROR8__(v16, 16);
    _security_cookie_complement = ~_security_cookie;
  }
  *MK_FP(43, &KeGetCurrentThread()->WaitBlockFill11[70]) = 2;
  do
  {
    v17 = KiBarrierWait == 0;
    _mm_pause();
  }
  while ( !v17 );
  KiIdleLoop();
}

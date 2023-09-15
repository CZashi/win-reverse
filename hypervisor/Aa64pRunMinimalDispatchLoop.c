void __fastcall Aa64pRunMinimalDispatchLoop(__int64 a1, __int64 a2, int a3)
{
  int v6; // w8
  unsigned int v11; // w19
  __int64 v12; // x9
  unsigned int v13; // w22
  unsigned int PendingHardwareInterrupt; // w19
  __int64 v15; // x0
  __int64 v16; // x1
  __int64 v17; // x2
  __int64 v18; // x3
  __int64 v19; // x4
  __int64 v20; // x5
  __int64 v21; // x6
  __int64 v22; // x7
  int v23; // w9
  __int128 v24; // q0
  __int128 v25; // q1
  __int128 v26; // q2
  __int128 v27; // q3
  __int128 v28; // q4
  __int128 v29; // q5
  __int128 v30; // q6
  __int128 v31; // q7
  __int64 v33; // x8
  __int64 v34; // x1
  __int64 v35; // x2
  __int16 v37; // w0
  char v38; // [xsp+0h] [xbp-10h]

  do
  {
    v6 = 1 << *(_BYTE *)(*(_QWORD *)(*((_QWORD *)NtCurrentTeb() + 4180) + 336i64) + 20i64);
    if ( (v6 & a3) != 0 )
    {
      a3 &= ~v6;
      ImpGenerateSyntheticException(a1 - 1088, 2);
    }
    __asm { SYS             #4, c8, c7, #6, X8 }
    __dsb(7u);
    __isb(0xFu);
    Aa64EnterAndExitGuest();
    v11 = *(_DWORD *)(a1 + 568);
    v12 = (*(_QWORD *)(a1 + 560) >> 7) & 3i64;
    v13 = v11 >> 26;
    if ( (_DWORD)v12 == 1 )
    {
      PendingHardwareInterrupt = KeGetPendingHardwareInterrupt();
      v15 = (*(__int64 (__fastcall **)(_QWORD, __int64))(HalpInterruptController + 56))(
              *(_QWORD *)(HalpInterruptController + 24),
              14i64);
      __asm { MSR             #7, #2 }
      if ( PendingHardwareInterrupt != -1 )
      {
        if ( (HalInterruptIdMask & PendingHardwareInterrupt) == 6 )
        {
          v33 = *(unsigned int *)(a2 + 33028);
          if ( (_DWORD)v33 )
            KeDispatchSpecialIpi(v15, v16, v17, v18, v19, v20, v21, v22, v33, v24, v25, v26, v27, v28, v29, v30, v31, v38);
          else
            KeIpiServiceRoutine(a2, 0i64);
          ImHandleNonmaskableInterrupt(*(_QWORD *)(a1 + 944));
          HalEndSystemInterrupt(a2, PendingHardwareInterrupt);
        }
        else
        {
          DmHandleInterruptIntercept((_QWORD *)a2, a1 - 1088);
        }
      }
    }
    else
    {
      if ( (_DWORD)v12 )
        goto LABEL_20;
      (*(void (__fastcall **)(_QWORD, __int64))(HalpInterruptController + 56))(
        *(_QWORD *)(HalpInterruptController + 24),
        14i64);
      __asm { MSR             #7, #2 }
      if ( v13 == 22 )
      {
        v37 = ValpMinimalDispatchLoopHypercallHandler(a1 - 1088, v34, v35);
        v23 = 0;
        if ( v37 == 2 )
        {
LABEL_20:
          DbgPrint("Clean up the minimal loop and reboot the system unconditionally\n");
          ValRebootProcessorUnconditional();
        }
      }
      else if ( v13 == 23 )
      {
        ImHandleSmc(
          *(_QWORD *)(a1 + 944),
          v11,
          *(_QWORD *)(a1 + 48),
          *(_QWORD *)(a1 + 64),
          *(_QWORD *)(a1 + 72),
          *(_QWORD *)(a1 + 80),
          *(_QWORD *)(a1 + 88),
          *(_QWORD *)(a1 + 96),
          *(_QWORD *)(a1 + 104));
      }
      else
      {
        Aa64ProcessUncommonIntercept(v11, a1);
      }
    }
    _mm_prefetcht0(v23, &KeExitMinimalDispatchLoopFlag);
  }
  while ( !v23 );
  DbgPrint("EXIT Minimal Loop\n");
}

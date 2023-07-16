__int64 __fastcall KiOptimizeSpecCtrlSettingsWorker(__int64 a1)
{
  struct _KPRCB *CurrentPrcb; // rbx
  char v2; // r12
  unsigned __int64 v4; // r14
  unsigned __int64 v5; // r13
  __int64 v6; // r9
  unsigned __int64 v7; // r11
  __int64 v8; // r8
  __int64 v9; // r10
  __int64 v10; // rdx
  __int64 v11; // rcx
  signed __int32 v12; // eax
  unsigned int v13; // edi
  unsigned int v14; // r15d
  __int64 v15; // rbx
  signed __int32 v16; // eax
  unsigned int v17; // edi
  unsigned int v18; // r15d
  int v19; // r14d
  __int64 v20; // rdx
  __int64 v21; // rdx
  __int64 v22; // r8
  signed __int32 v23; // eax
  unsigned int v24; // edi
  unsigned int v25; // r15d
  unsigned __int64 v26; // rax
  signed __int32 v28; // edx
  int v29; // r14d
  bool v30; // zf
  signed __int32 v31; // eax
  signed __int32 v32; // edx
  int v33; // r14d
  signed __int32 v34; // eax
  signed __int32 v35; // edx
  unsigned int v36; // ecx
  int v37; // r14d
  signed __int32 v38; // eax
  __int16 v39; // cx
  unsigned __int16 v40; // ax
  unsigned __int64 CoreProcessorSet; // rdi
  __int64 v42; // rdx
  char v43; // cl
  unsigned __int64 v44; // rax
  unsigned __int64 v45; // rax
  unsigned __int16 BpbKernelSpecCtrl; // ax
  signed __int32 v47[8]; // [rsp+0h] [rbp-38h] BYREF
  unsigned __int64 v48; // [rsp+20h] [rbp-18h]
  struct _KPRCB *v49; // [rsp+28h] [rbp-10h]
  int v50; // [rsp+80h] [rbp+48h] BYREF
  int v51; // [rsp+88h] [rbp+50h] BYREF
  int v52; // [rsp+90h] [rbp+58h] BYREF
  int v53; // [rsp+98h] [rbp+60h]

  CurrentPrcb = KeGetCurrentPrcb();
  v2 = 0;
  v49 = CurrentPrcb;
  LOBYTE(v4) = 0;
  v48 = 0i64;
  v5 = 0i64;
  if ( (KeFeatureBits2 & 0x20000000) != 0 )
  {
    v4 = __readmsr(0x50000001u);
    v48 = v4;
  }
  if ( ((CurrentPrcb->CoreProcessorSet - 1) & CurrentPrcb->CoreProcessorSet) != 0 )
    _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 2ui64);
  if ( HvlHypervisorConnected && (unsigned __int8)((__int64 (*)(void))HvlIsCoreSharingPossible)() )
    _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 2ui64);
  v6 = 128i64;
  if ( (KiFeatureSettings & 0x80u) != 0 )
    _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x10000000000ui64);
  if ( CurrentPrcb->CpuVendor == 1 )
  {
    KiDetectAmdNonArchSsbdSupport(CurrentPrcb, &KiSpeculationFeatures);
    v6 = 128i64;
  }
  v7 = 0x4000000000i64;
  v8 = 0x8000000000i64;
  if ( (KiSpeculationFeatures & 0x80) != 0 && (KiSpeculationFeatures & 0x100) == 0 )
  {
    if ( (KiFeatureSettings & 8) != 0 )
      goto LABEL_122;
    if ( (KiFeatureSettings & 0x10) == 0 )
      goto LABEL_14;
    if ( KiSsbdMsr != 72 )
LABEL_122:
      _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x4000000000ui64);
    else
      _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x8000000000ui64);
  }
LABEL_14:
  v9 = 4i64;
  v10 = 0x800000000i64;
  if ( (KiSpeculationFeatures & 4) == 0 )
    _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x800000000ui64);
  v11 = 0x400000000i64;
  if ( (KiFeatureSettings & 4) != 0 )
  {
    _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x400000000ui64);
  }
  else if ( (KiFeatureSettings & 1) != 0 )
  {
    _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x400000000ui64);
    if ( HvlHypervisorConnected )
    {
      if ( (HvlpFlags & 2) != 0
        && (unsigned __int8)HvlIsCoreSharingPossible(0x400000000i64, 0x800000000i64, 0x8000000000i64)
        && (KiSpeculationFeatures & 0x40) != 0 )
      {
        CurrentPrcb->BpbKernelSpecCtrl = 2;
        CurrentPrcb->BpbUserSpecCtrl = 2;
        CurrentPrcb->BpbRetpolineExitSpecCtrl = 2;
      }
    }
  }
  if ( a1 )
  {
    v50 = 0;
    v12 = _InterlockedDecrement((volatile signed __int32 *)a1);
    v13 = ~v12 & 0x80000000;
    if ( (v12 & 0x3FFFFFFF) != 0 )
    {
      v14 = 0;
      v15 = v9;
      while ( (*(_DWORD *)a1 & 0x80000000) != v13 )
      {
        if ( (++v14 & HvlLongSpinCountMask) == 0
          && (HvlEnlightenments & 0x40) != 0
          && (unsigned __int8)KiCheckVpBackingLongSpinWaitHypercall(v11) )
        {
          ++v2;
          if ( (unsigned __int8)KeCanUseHaltOnAddress() && (KiVelocityFlags & 0x20000) != 0 && (v2 & 1) == 0 )
          {
            v11 = *(_DWORD *)a1 & 0x80000000;
            v50 = *(_DWORD *)a1;
            v28 = v50;
            if ( (_DWORD)v11 != v13 )
            {
              do
              {
                v29 = v28 | 0x40000000;
                v31 = _InterlockedCompareExchange((volatile signed __int32 *)a1, v28 | 0x40000000, v28);
                v30 = v28 == v31;
                v28 = v31;
                if ( v30 )
                {
                  v50 = v29;
                  do
                  {
                    KiHaltOnAddress(a1, &v50, v15);
                    v28 = *(_DWORD *)a1;
                  }
                  while ( *(_DWORD *)a1 == v29 );
                }
                v50 = v28;
              }
              while ( (v28 & 0x80000000) != v13 );
            }
          }
          else
          {
            HvlNotifyLongSpinWait(v14);
          }
        }
        else
        {
          _mm_pause();
        }
      }
      CurrentPrcb = v49;
      v2 = 0;
      LOBYTE(v4) = v48;
    }
    else
    {
      v50 = _InterlockedExchange((volatile __int32 *)a1, *(_DWORD *)(a1 + 4) | v13);
      if ( (v50 & 0x40000000) == 0 )
        goto LABEL_32;
      _InterlockedOr(v47, 0);
      KiWakeAddressAll(a1, v10, v8);
    }
    LOWORD(v9) = 4;
    v7 = 0x4000000000i64;
    v8 = 0x8000000000i64;
    v10 = 0x800000000i64;
    v6 = 128i64;
  }
LABEL_32:
  if ( (KiSpeculationFeatures & 0x400000000i64) != 0 || ((unsigned __int64)KiSpeculationFeatures & v10) != 0 )
  {
    if ( ((unsigned __int64)KiSpeculationFeatures & v8) != 0 )
    {
      _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, v7);
      _InterlockedAnd64((volatile signed __int64 *)&KiSpeculationFeatures, 0xFFFFFF7FFFFFFFFFui64);
    }
    if ( ((unsigned __int64)KiSpeculationFeatures & v7) != 0 )
    {
      BpbKernelSpecCtrl = CurrentPrcb->BpbKernelSpecCtrl;
      if ( KiSsbdMsr == 72 )
        BpbKernelSpecCtrl |= v9;
      CurrentPrcb->BpbKernelSpecCtrl = BpbKernelSpecCtrl;
      CurrentPrcb->BpbUserSpecCtrl = BpbKernelSpecCtrl;
    }
  }
  else
  {
    _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x1000000000ui64);
    CurrentPrcb->BpbFeatures.AllFlags |= 2u;
    if ( (KiSpeculationFeatures & 1) != 0 )
    {
      v39 = 1;
      if ( (KiSpeculationFeatures & 0x4000) != 0 )
        v39 = 3;
      CurrentPrcb->BpbKernelSpecCtrl = v39;
      CurrentPrcb->BpbUserSpecCtrl = v39;
      CurrentPrcb->BpbRetpolineExitSpecCtrl = v39;
      v11 = 0x4000000000i64;
      if ( (KiSpeculationFeatures & 0x4000000000i64) != 0 || ((unsigned __int64)KiSpeculationFeatures & v8) != 0 )
      {
        v40 = CurrentPrcb->BpbKernelSpecCtrl;
        if ( KiSsbdMsr == 72 )
          v40 |= 4u;
        CurrentPrcb->BpbKernelSpecCtrl = v40;
        CurrentPrcb->BpbUserSpecCtrl = v40;
        CurrentPrcb->BpbRetpolineExitSpecCtrl = v40;
      }
      CurrentPrcb->BpbNmiSpecCtrl = 1;
      if ( ((KiSpeculationFeatures & 0x4000000000i64) != 0 || ((unsigned __int64)KiSpeculationFeatures & v8) != 0)
        && KiSsbdMsr == 72 )
      {
        CurrentPrcb->BpbNmiSpecCtrl |= 4u;
      }
      if ( (KiSpeculationFeatures & 0x4000) != 0 )
        CurrentPrcb->BpbNmiSpecCtrl |= 2u;
      if ( (KiSpeculationFeatures & 0x2000) != 0 )
        CurrentPrcb->BpbNmiSpecCtrl |= v6;
      if ( (KiSpeculationFeatures & 0x10000) != 0 && (KiSpeculationFeatures & 0x20000) != 0 )
      {
        CurrentPrcb->BpbKernelSpecCtrl |= 0x400u;
        CurrentPrcb->BpbRetpolineExitSpecCtrl |= 0x400u;
        CurrentPrcb->BpbUserSpecCtrl |= 0x400u;
        CurrentPrcb->BpbNmiSpecCtrl |= 0x400u;
      }
      CurrentPrcb->BpbFeatures.AllFlags ^= (CurrentPrcb->BpbFeatures.AllFlags ^ (16 * BYTE12(KiSpeculationFeatures))) & 0x30;
      if ( BYTE12(KiSpeculationFeatures) && (v4 & 1) != 0 )
        v5 = 1i64;
      if ( ((unsigned __int64)KiSpeculationFeatures & v8) == 0 )
        goto LABEL_87;
    }
    if ( (KiSpeculationFeatures & 0x10) != 0 )
    {
      CurrentPrcb->BpbNmiSpecCtrl = 1;
    }
    else if ( (KiSpeculationFeatures & 0x40) != 0 && (KiSpeculationFeatures & 2) != 0 )
    {
      CurrentPrcb->BpbNmiSpecCtrl = 2;
    }
    if ( (KiSpeculationFeatures & 0x4000) != 0 )
      CurrentPrcb->BpbNmiSpecCtrl |= 2u;
    if ( (KiSpeculationFeatures & 0x2000) != 0 )
      CurrentPrcb->BpbNmiSpecCtrl |= v6;
    v7 = 0x4000000000i64;
    if ( ((KiSpeculationFeatures & 0x4000000000i64) != 0 || ((unsigned __int64)KiSpeculationFeatures & v8) != 0)
      && KiSsbdMsr == 72 )
    {
      CurrentPrcb->BpbNmiSpecCtrl |= 4u;
    }
    if ( (KiSpeculationFeatures & 1) == 0 )
    {
      if ( a1 )
      {
        v51 = 0;
        v16 = _InterlockedDecrement((volatile signed __int32 *)a1);
        v17 = ~v16 & 0x80000000;
        if ( (v16 & 0x3FFFFFFF) != 0 )
        {
          v18 = 0;
          while ( (*(_DWORD *)a1 & 0x80000000) != v17 )
          {
            if ( (++v18 & HvlLongSpinCountMask) == 0
              && (HvlEnlightenments & 0x40) != 0
              && (unsigned __int8)KiCheckVpBackingLongSpinWaitHypercall(v11) )
            {
              ++v2;
              if ( (unsigned __int8)KeCanUseHaltOnAddress() && (KiVelocityFlags & 0x20000) != 0 && (v2 & 1) == 0 )
              {
                v11 = *(_DWORD *)a1 & 0x80000000;
                v51 = *(_DWORD *)a1;
                v32 = v51;
                if ( (_DWORD)v11 != v17 )
                {
                  do
                  {
                    v33 = v32 | 0x40000000;
                    v34 = _InterlockedCompareExchange((volatile signed __int32 *)a1, v32 | 0x40000000, v32);
                    v30 = v32 == v34;
                    v32 = v34;
                    if ( v30 )
                    {
                      v51 = v33;
                      do
                      {
                        KiHaltOnAddress(a1, &v51, 4i64);
                        v32 = *(_DWORD *)a1;
                      }
                      while ( *(_DWORD *)a1 == v33 );
                    }
                    v51 = v32;
                  }
                  while ( (v32 & 0x80000000) != v17 );
                }
              }
              else
              {
                HvlNotifyLongSpinWait(v18);
              }
            }
            else
            {
              _mm_pause();
            }
          }
          CurrentPrcb = v49;
          v2 = 0;
        }
        else
        {
          v51 = _InterlockedExchange((volatile __int32 *)a1, *(_DWORD *)(a1 + 4) | v17);
          if ( (v51 & 0x40000000) != 0 )
          {
            _InterlockedOr(v47, 0);
            KiWakeAddressAll(a1, v10, v8);
          }
        }
      }
      if ( (KiSpeculationFeatures & 0x20000000000i64) != 0 )
      {
        CurrentPrcb->BpbRetpolineState.AllFlags |= 4u;
        KeExitRetpoline(v11);
      }
      if ( (KiSpeculationFeatures & 2) != 0
        && (KiSpeculationFeatures & 0x4000) == 0
        && !HvlHypervisorConnected
        && ((KiSpeculationFeatures & 0x10) != 0 || (KiSpeculationFeatures & 0x40) != 0) )
      {
        _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x200000000ui64);
        CurrentPrcb->BpbFeatures.AllFlags |= 1u;
      }
      v19 = 0;
      if ( (KiSpeculationFeatures & 2) != 0
        && (KiSpeculationFeatures & 0x40) != 0
        && (KiSpeculationFeatures & 0x10) != 0 )
      {
        v20 = 0x10000000000i64;
        if ( (KiSpeculationFeatures & 0x4000) != 0 || (KiSpeculationFeatures & 0x10000000000i64) != 0 )
          goto LABEL_62;
        CoreProcessorSet = CurrentPrcb->CoreProcessorSet;
        if ( (unsigned int)RtlNumberOfSetBitsUlongPtr_0(CoreProcessorSet) == 2
          && (!HvlHypervisorConnected
           || !(unsigned __int8)HvlIsCoreSharingPossible(v11, v42, v8)
           || (HvlpFlags & 2) != 0 && (unsigned __int8)HvlIsStibpPairingRecommended()) )
        {
          v43 = CurrentPrcb->GroupIndex + 1;
          _BitScanForward64(&v44, __ROR8__(CoreProcessorSet, v43));
          v53 = v44;
          CurrentPrcb->PairPrcb = (_KPRCB *)KeGetPrcb((unsigned int)KiProcessorNumberToIndexMappingTable[64 * CurrentPrcb->Group + (((unsigned __int8)v44 + v43) & 0x3F)]);
          v19 = 1;
          CurrentPrcb->PairRegister = 6;
        }
      }
      v20 = 0x10000000000i64;
LABEL_62:
      if ( (KiFeatureSettings & 0x20) != 0 && (KiSpeculationFeatures & 2) != 0 && (KiSpeculationFeatures & 0x40) != 0
        || (KiSpeculationFeatures & 2) != 0
        && (KiSpeculationFeatures & 0x40) != 0
        && !v19
        && (KiSpeculationFeatures & 0x10000000000i64) == 0
        && HvlHypervisorConnected
        && (unsigned __int8)HvlIsCoreSharingPossible(v11, 0x10000000000i64, v8) )
      {
        _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x100000000ui64);
      }
      if ( (KiSpeculationFeatures & 2) != 0
        && (KiSpeculationFeatures & 0x40) != 0
        && (KiSpeculationFeatures & 0x4000) != 0
        && !v19
        && ((unsigned __int64)KiSpeculationFeatures & v20) == 0 )
      {
        _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x80000000000ui64);
      }
      if ( CurrentPrcb->CpuVendor == 1 && (KiSpeculationFeatures & 0x10) == 0 && (KiFeatureSettings & 0x40) == 0 )
      {
        _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x2000000000ui64);
LABEL_87:
        v7 = 0x4000000000i64;
        goto LABEL_88;
      }
      if ( (unsigned int)KiIsBranchConfusionPresent(CurrentPrcb, v20, v8, v6) )
      {
        _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, 0x8000ui64);
        if ( (unsigned int)KiIsBranchConfusionMitigationDesired((__int64)CurrentPrcb, &KiSpeculationFeatures) )
        {
          if ( (unsigned int)KiIsBranchConfusionMitigationSupported((__int64)CurrentPrcb, &KiSpeculationFeatures) )
            goto LABEL_67;
          v45 = 0x200000000000i64;
        }
        else
        {
          v45 = 0x100000000000i64;
        }
        _InterlockedOr64((volatile signed __int64 *)&KiSpeculationFeatures, v45);
      }
LABEL_67:
      if ( (KiSpeculationFeatures & 0x10000) != 0 && (KiSpeculationFeatures & 0x20000) != 0 )
      {
        CurrentPrcb->BpbKernelSpecCtrl |= 0x400u;
        CurrentPrcb->BpbRetpolineExitSpecCtrl |= 0x400u;
        CurrentPrcb->BpbUserSpecCtrl |= 0x400u;
        CurrentPrcb->BpbNmiSpecCtrl |= 0x400u;
      }
      CurrentPrcb->BpbFeatures.AllFlags ^= (CurrentPrcb->BpbFeatures.AllFlags ^ (16 * BYTE12(KiSpeculationFeatures))) & 0x30;
      if ( BYTE12(KiSpeculationFeatures) && (v48 & 1) != 0 )
        v5 = 1i64;
      if ( a1 )
      {
        v23 = _InterlockedDecrement((volatile signed __int32 *)a1);
        v24 = ~v23 & 0x80000000;
        if ( (v23 & 0x3FFFFFFF) != 0 )
        {
          v25 = 0;
          while ( (*(_DWORD *)a1 & 0x80000000) != v24 )
          {
            if ( (++v25 & HvlLongSpinCountMask) == 0
              && (HvlEnlightenments & 0x40) != 0
              && (unsigned __int8)((__int64 (*)(void))KiCheckVpBackingLongSpinWaitHypercall)() )
            {
              ++v2;
              if ( (unsigned __int8)KeCanUseHaltOnAddress() && (KiVelocityFlags & 0x20000) != 0 && (v2 & 1) == 0 )
              {
                v36 = *(_DWORD *)a1 & 0x80000000;
                v52 = *(_DWORD *)a1;
                v35 = v52;
                if ( v36 != v24 )
                {
                  do
                  {
                    v37 = v35 | 0x40000000;
                    v38 = _InterlockedCompareExchange((volatile signed __int32 *)a1, v35 | 0x40000000, v35);
                    v30 = v35 == v38;
                    v35 = v38;
                    if ( v30 )
                    {
                      v52 = v37;
                      do
                      {
                        KiHaltOnAddress(a1, &v52, 4i64);
                        v35 = *(_DWORD *)a1;
                      }
                      while ( *(_DWORD *)a1 == v37 );
                    }
                    v52 = v35;
                  }
                  while ( (v35 & 0x80000000) != v24 );
                }
              }
              else
              {
                HvlNotifyLongSpinWait(v25);
              }
            }
            else
            {
              _mm_pause();
            }
          }
          CurrentPrcb = v49;
        }
        else
        {
          v52 = _InterlockedExchange((volatile __int32 *)a1, *(_DWORD *)(a1 + 4) | v24);
          if ( (v52 & 0x40000000) != 0 )
          {
            _InterlockedOr(v47, 0);
            KiWakeAddressAll(a1, v21, v22);
          }
        }
      }
      KiUpdateSpeculationControl(KeGetCurrentThread()->ApcState.Process);
      goto LABEL_87;
    }
  }
LABEL_88:
  v26 = CurrentPrcb->BpbKernelSpecCtrl;
  CurrentPrcb->BpbCurrentSpecCtrl = v26;
  if ( (_WORD)v26 )
    __writemsr(0x48u, v26);
  if ( v5 )
    __writemsr(0x50000002u, v5);
  if ( ((unsigned __int64)KiSpeculationFeatures & v7) != 0 && KiSsbdMsr != 72 )
    __writemsr(KiSsbdMsr, KiSsbdBit | __readmsr(KiSsbdMsr));
  return 0i64;
}

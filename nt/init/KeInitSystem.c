NTSTATUS __fastcall KeInitSystem(UINT64 Phase, UINT8 a2)
{
  INT64 v2; // rax
  ULONG ActiveProcessorCount; // er15
  unsigned int v4; // edx
  unsigned __int64 v5; // rcx
  unsigned int v6; // er8
  unsigned int v7; // er9
  int v8; // eax
  unsigned __int64 v9; // rax
  ULONG v10; // edi
  _KPRCB **v11; // rsi
  _KPRCB *v12; // r14
  UINT64 v13; // rdx
  __int64 MHz; // r8
  unsigned __int64 v15; // rcx
  struct _KPRCB *CurrentPrcb; // r10
  INT64 v17; // r10
  _KPRCB *v18; // r10
  NTSTATUS v19; // eax
  __int64 v20; // rdx
  UINT64 v21; // rcx
  unsigned int v22; // eax
  _QWORD *PoolWithTag; // rax
  __int64 v24; // rcx
  unsigned __int8 CurrentIrql; // di
  int RegistrationInfo[2]; // [rsp+30h] [rbp-30h] BYREF
  __int64 v28; // [rsp+38h] [rbp-28h]
  int (__fastcall **v29)(_DEVICE_OBJECT *, _IRP *); // [rsp+40h] [rbp-20h]
  __int64 v30; // [rsp+48h] [rbp-18h]
  __int64 v31; // [rsp+50h] [rbp-10h]
  int v32; // [rsp+90h] [rbp+30h] BYREF
  char *v33; // [rsp+98h] [rbp+38h] BYREF

  switch ( (_DWORD)Phase )
  {
    case 0:
      CurrentPrcb = KeGetCurrentPrcb();
      if ( (KeFeatureBits2 & 0x8000) != 0 && KiDisableTsx && (CurrentPrcb->MsrIa32TsxCtrl & 3) != 3 )
      {
        v20 = CurrentPrcb->MsrIa32TsxCtrl | 3;
        CurrentPrcb->MsrIa32TsxCtrl = v20;
        __writemsr(0x122u, v20);
      }
      KiTsxSupported = KiDetectTsx();
      KeInitializeSchedulerAssist(v17);
      KeInitializeCatRegisters();
      v19 = KeInitializeTimerTable(v18);
      if ( v19 < 0 )
        KeBugCheckEx(0x31u, v19, 1u, 0, 0);
      LODWORD(v2) = KeMinimumIncrement;
      if ( KiHrIncrement < (unsigned int)KeMinimumIncrement || KiHrIncrement > KeMaximumIncrement )
        KiHrIncrement = KeMinimumIncrement;
      break;
    case 1:
      _InterlockedOr(dword_140D23E60, 0x8000u);
      _InterlockedOr(dword_140D2427C, 0x400000u);
      KiInitDynamicTraceSupport();
      ActiveProcessorCount = KeQueryActiveProcessorCountEx(0xFFFFu);
      KiClockKeepAliveCycle = (ActiveProcessorCount + (KeMaximumIncrement + 29999999) / KeMaximumIncrement - 1)
                            / ActiveProcessorCount;
      if ( HviIsAnyHypervisorPresent() )
      {
        if ( (_BYTE)HvlHypervisorConnected )
        {
          v21 = 0i64;
        }
        else
        {
          KeDpcWatchdogPeriod = 0;
          v21 = 1i64;
          KiDPCTimeout = 0;
        }
        KeRelaxTimingConstraints(v21);
      }
      v5 = (unsigned int)KeDpcWatchdogPeriod;
      if ( KeDpcWatchdogPeriod )
      {
        if ( (unsigned int)KeDpcWatchdogPeriod < 0x7D0 )
        {
          v5 = 2000i64;
          KeDpcWatchdogPeriod = 2000;
        }
        if ( (unsigned int)v5 > 0x3A980 )
        {
          v5 = 240000i64;
          KeDpcWatchdogPeriod = 240000;
        }
      }
      v6 = KiDPCTimeout;
      if ( KiDPCTimeout )
      {
        if ( (unsigned int)KiDPCTimeout < 0x14 )
        {
          v6 = 20;
          KiDPCTimeout = 20;
        }
        if ( v6 > 0x4E20 )
        {
          v6 = 20000;
          KiDPCTimeout = 20000;
        }
      }
      if ( ViVerifierEnabled )
      {
        v22 = KeVerifierDpcScalingFactor;
        if ( !KeVerifierDpcScalingFactor )
        {
          v22 = 1;
          KeVerifierDpcScalingFactor = 1;
        }
        if ( v22 > 0x64 )
        {
          v22 = 100;
          KeVerifierDpcScalingFactor = 100;
        }
        v5 = v22 * (unsigned int)v5;
        v6 *= v22;
        KeDpcWatchdogPeriod = v5;
        KiDPCTimeout = v6;
      }
      if ( (_DWORD)v5 )
      {
        if ( v6 )
        {
          if ( v6 < (unsigned int)v5 )
          {
            v7 = KeDpcWatchdogProfileOffset;
            if ( KeDpcWatchdogProfileOffset )
            {
              if ( (unsigned int)KeDpcWatchdogProfileOffset <= 0x3E8 )
              {
                v7 = 1000;
                KeDpcWatchdogProfileOffset = 1000;
              }
              if ( v7 > (unsigned int)v5 )
              {
                v7 = 10000;
                if ( (unsigned int)v5 <= 0x2710 )
                  v7 = 1000;
                KeDpcWatchdogProfileOffset = v7;
              }
              v8 = v5 - v7;
              KiDpcWatchdogProfileCumulativeDpcThreshold = v5 - v7;
              if ( (unsigned int)v5 - v7 < 0x3E8 )
              {
                KiDpcWatchdogProfileCumulativeDpcThreshold = 1000;
                v8 = 1000;
              }
              v9 = v6 * v8 / v5;
              if ( v9 > 0xFFFFFFFF )
                LODWORD(v9) = -1;
              KiDpcWatchdogProfileSingleDpcThreshold = v9;
              if ( v6 - (unsigned int)v9 > v7 )
                KiDpcWatchdogProfileSingleDpcThreshold = 0;
              v4 = v7 / 0x3E8;
              KiDpcWatchdogProfileArrayLength = 3328 * (v7 / 0x3E8);
              dword_140CFA32C = 3328 * (v7 / 0x3E8);
            }
          }
        }
      }
      v10 = 0;
      if ( ActiveProcessorCount )
      {
        v11 = &KiProcessorBlock;
        while ( 1 )
        {
          v12 = *v11;
          KiInitializeProcessor(*v11, v4);
          if ( KeThreadDpcEnable )
          {
            LODWORD(v2) = KiStartDpcThread(v12);
            if ( (int)v2 < 0 )
              break;
          }
          ++v10;
          ++v11;
          if ( v10 >= ActiveProcessorCount )
            goto LABEL_40;
        }
      }
      else
      {
LABEL_40:
        LODWORD(v2) = KiComputeNumaCosts();
        if ( (_BYTE)v2 )
        {
          SymCryptInitEnvWindowsKernelmodeWin8_1nLater();
          KiIntSteerInit();
          if ( (*(_QWORD *)&KeFeatureBits & 0x800000i64) != 0 && KUSER_SHARED_DATA.XState.EnabledSupervisorFeatures
            || KiIptMsrMask )
          {
            RegistrationInfo[1] = 6;
            v29 = &PopEmEntry.MajorFunction[27];
            v28 = 512i64;
            RegistrationInfo[0] = 65548;
            v30 = 0i64;
            v31 = 0i64;
            if ( ExRegisterHost(&KiSupervisorStateExtensionHost, v13, RegistrationInfo) < 0 )
              KiSupervisorStateExtensionHost = 0i64;
          }
          if ( KiInitMachineDependent() )
          {
            MHz = KiProcessorBlock->MHz;
            v15 = MHz * (unsigned __int64)KeMaximumIncrement / 0xA;
            KiShortExecutionCycles = v15 / 0xF0;
            KiCyclesPerClockQuantum = v15 / 3;
            KiDirectQuantumTarget = v15 / 3;
            KiLockQuantumTarget = 3 * (v15 / 3);
            _BitScanReverse64(&v15, 6000000 * MHz);
            KiFavoredCoreCycleTimeBits = v15;
            KdEncodeDataBlock();
            LODWORD(v2) = KeExpandKernelStackAndCalloutInternal(
                            (VOID (*)(void))KiVerifyScopesExecute,
                            0i64,
                            0xC000ui64,
                            2,
                            0i64);
            if ( (int)v2 < 0 )
              KeBugCheckEx(0x32u, v2, 0x5356694Bu, 0, 0);
            break;
          }
        }
      }
      LOBYTE(v2) = 0;
      return v2;
    case 2:
      LODWORD(v2) = TraceLoggingRegisterEx_EtwRegister_EtwSetInformation(&dword_140C01A70);
      break;
    case 3:
      LODWORD(v2) = KiInitializeReservedCpuSets();
      break;
    default:
      ExAcquireFastMutexUnsafe(&KiDynamicProcessorLock);
      MmFreeLoaderBlock();
      KeLoaderBlock_0 = 0i64;
      ExReleaseFastMutexUnsafe(&KiDynamicProcessorLock);
      KiInitializeVelocity();
      KiRegisterForDisableFgBoostDecayRegistryNotification();
      if ( !HviIsAnyHypervisorPresent() )
        KeEnableWatchdogTimeout = 1;
      v33 = 0i64;
      v32 = 0;
      if ( (HvlpFlags & 0x100000) != 0 )
      {
        PoolWithTag = ExAllocatePoolWithTag(NonPagedPoolNx, 0x4A0u, 0x4850654Bu);
        KiEpfHashTable = (__int64)PoolWithTag;
        if ( PoolWithTag )
        {
          v24 = 37i64;
          do
          {
            PoolWithTag[1] = PoolWithTag;
            *PoolWithTag = PoolWithTag;
            PoolWithTag[2] = 0i64;
            *((_DWORD *)PoolWithTag + 6) = 0;
            PoolWithTag += 4;
            --v24;
          }
          while ( v24 );
          KiEpfCompletionDpc.TargetInfoAsUlong = 275;
          KiEpfCompletionDpc.DeferredRoutine = (void (__fastcall *)(_KDPC *, void *, void *, void *))KiEpfCompletionDpcRoutine;
          KiEpfCompletionDpc.DeferredContext = 0i64;
          KiEpfCompletionDpc.DpcData = 0i64;
          KiEpfCompletionDpc.ProcessorHistory = 0i64;
          if ( (int)HvlSetupPhysicalFaultNotificationQueue(&v33, &v32) >= 0 )
          {
            KiEpfCompletionQueueSize = (unsigned int)(v32 - 16) >> 3;
            KiEpfCompletionQueue = (__int64)v33;
            CurrentIrql = KeGetCurrentIrql();
            __writecr8(2ui64);
            KiEpfDrainCompletionQueue();
            __writecr8(CurrentIrql);
          }
        }
      }
      v2 = KeFreeInitializationCode();
      break;
  }
  LOBYTE(v2) = 1;
  return v2;
}

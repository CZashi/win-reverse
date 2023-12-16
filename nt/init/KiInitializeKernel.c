VOID __stdcall KiInitializeKernel(
        _EPROCESS *Process,
        _ETHREAD *Thread,
        VOID *IdleStack,
        _KPRCB *Prcb,
        CHAR Number,
        _LOADER_PARAMETER_BLOCK *LoaderBlock)
{
  unsigned int v7; // er13
  unsigned __int64 FeatureBits; // rbx
  _KPRCB *v9; // r11
  unsigned int CoresPerPhysicalProcessor; // ebx
  unsigned int *p_LogicalProcessorsPerCore; // r12
  ULONG_PTR v12; // eax
  unsigned int v13; // ebx
  int v14; // er9
  unsigned int InitialApicId; // ecx
  int v16; // er10
  unsigned __int64 GroupSetMember; // rdx
  __int64 v18; // rcx
  int v19; // er8
  _KPRCB *v20; // r15
  char v21; // al
  _KPRCB *v22; // rax
  unsigned int v23; // ecx
  unsigned int v24; // eax
  int v25; // er15
  INT64 v26; // rbx
  char XSaveFeatureFlags; // al
  unsigned __int64 v28; // rbx
  unsigned __int64 v29; // r8
  _EPROCESS *v30; // r15
  _ETHREAD *v31; // rdi
  INT64 v32; // rdx
  INT64 v33; // r8
  _NLSTABLEINFO *v34; // r9
  _LOADER_PARAMETER_BLOCK *v35; // rbx
  int v36; // eax
  unsigned __int64 v37; // rax
  INT64 v38; // rbx
  unsigned __int64 v39; // rax
  unsigned __int64 v40; // rax
  UINT8 v41; // dl
  int v42; // eax
  unsigned __int64 v43; // rax
  unsigned __int64 v44; // rax
  unsigned __int64 v45; // rcx
  unsigned __int64 v46; // rax
  unsigned __int64 v47; // rcx
  unsigned __int64 v48; // rax
  UINT64 Flags; // [rsp+28h] [rbp-2E0h]
  char v50; // [rsp+30h] [rbp-2D8h]
  char v51; // [rsp+31h] [rbp-2D7h]
  INT64 v52; // [rsp+38h] [rbp-2D0h] BYREF
  int v53; // [rsp+40h] [rbp-2C8h]
  int v54; // [rsp+44h] [rbp-2C4h]
  _KPRCB *v55; // [rsp+48h] [rbp-2C0h]
  unsigned int v56; // [rsp+50h] [rbp-2B8h]
  int v57; // [rsp+54h] [rbp-2B4h]
  int v58; // [rsp+58h] [rbp-2B0h]
  ULONG_PTR v59; // [rsp+5Ch] [rbp-2ACh]
  unsigned __int64 v60; // [rsp+60h] [rbp-2A8h]
  _EPROCESS *Processa; // [rsp+68h] [rbp-2A0h]
  _LOADER_PARAMETER_BLOCK *v62; // [rsp+70h] [rbp-298h]
  _GROUP_AFFINITY GroupAffinity; // [rsp+78h] [rbp-290h] BYREF
  _KPRCB *v64; // [rsp+88h] [rbp-280h]
  VOID *KernelStack; // [rsp+90h] [rbp-278h]
  _ETHREAD *Threada; // [rsp+98h] [rbp-270h]
  _ETHREAD *v67; // [rsp+A0h] [rbp-268h]
  _KPRCB *v68; // [rsp+A8h] [rbp-260h]
  _LOADER_PARAMETER_BLOCK *v69; // [rsp+B0h] [rbp-258h]
  _HV_ARM64_HYPERVISOR_FEATURES HvFeaturesOut; // [rsp+B8h] [rbp-250h] BYREF
  UINT8 dst[512]; // [rsp+D0h] [rbp-238h] BYREF

  KernelStack = IdleStack;
  Threada = Thread;
  Processa = Process;
  v67 = Thread;
  v68 = Prcb;
  v62 = LoaderBlock;
  v69 = LoaderBlock;
  GroupAffinity = 0i64;
  HvFeaturesOut = 0i64;
  v7 = Number;
  if ( !Number )
    HvlPhase0Initialize(LoaderBlock);
  FeatureBits = Prcb->FeatureBits;
  v52 = FeatureBits;
  if ( (unsigned __int8)(Prcb->CpuVendor - 1) <= 2u )
    KiSetHardwareSpeculationControlFeatures((INT64)Prcb, FeatureBits);
  KiCheckMicrocode((INT64)Prcb);
  memset(dst, 0, sizeof(dst));
  _fxsave(dst);
  if ( Number )
  {
    if ( KiFpuLeakage )
      v52 = FeatureBits | 0x20000000000i64;
    KiSetPageAttributesTable();
    *(_DWORD *)&Prcb->PackageProcessorSet.Count = 1310721;
    Prcb->PackageProcessorSet.Reserved = 0;
    memset((UINT8 *)Prcb->PackageProcessorSet.Bitmap, 0, sizeof(Prcb->PackageProcessorSet.Bitmap));
    KeAddProcessorAffinityEx(&Prcb->PackageProcessorSet, (unsigned int)Number);
    v9 = Prcb;
    v55 = Prcb;
    CoresPerPhysicalProcessor = Prcb->CoresPerPhysicalProcessor;
    p_LogicalProcessorsPerCore = &Prcb->LogicalProcessorsPerCore;
    if ( CoresPerPhysicalProcessor == 1 && *p_LogicalProcessorsPerCore == 1 )
    {
      Prcb->CoreProcessorSet = Prcb->GroupSetMember;
      Prcb->PackageId = Prcb->InitialApicId;
    }
    else
    {
      v12 = *p_LogicalProcessorsPerCore;
      v13 = *p_LogicalProcessorsPerCore * CoresPerPhysicalProcessor;
      v56 = v13;
      v14 = ~(v13 - 1);
      v57 = v14;
      InitialApicId = Prcb->InitialApicId;
      v16 = v14 & InitialApicId;
      v58 = v14 & InitialApicId;
      Prcb->PackageId = v14 & InitialApicId;
      v59 = ~(v12 - 1);
      v53 = v59 & InitialApicId;
      GroupSetMember = Prcb->GroupSetMember;
      v60 = GroupSetMember;
      v50 = 0;
      v18 = 0i64;
      v54 = 0;
      if ( (_DWORD)KeNumberProcessors_0 )
      {
        v19 = v53;
        do
        {
          v64 = v9;
          v51 = v50;
          v20 = *(&KiProcessorBlock + v18);
          if ( (v20->InitialApicId & v14) == v16 )
          {
            KeAddProcessorAffinityEx(&Prcb->PackageProcessorSet, (unsigned int)v18);
            KeAddProcessorAffinityEx(&v20->PackageProcessorSet, (unsigned int)Number);
            v21 = v50;
            if ( !v50 )
              v21 = 1;
            v50 = v21;
            v22 = v20;
            if ( v51 )
              v22 = v64;
            v55 = v22;
            v23 = KeCountSetBitsAffinityEx(&v20->PackageProcessorSet);
            v13 = v56;
            if ( v23 > v56 )
              KeBugCheckEx(0x3Eu, (ULONG_PTR)v20, v23, v20->CoresPerPhysicalProcessor, v20->LogicalProcessorsPerCore);
            LODWORD(v18) = v54;
            GroupSetMember = v60;
            v19 = v53;
            v14 = v57;
            v16 = v58;
            v9 = v55;
          }
          if ( (v20->InitialApicId & v59) == v19 && v20->ParentNode == Prcb->ParentNode )
          {
            GroupSetMember |= v20->GroupSetMember;
            v60 = GroupSetMember;
            v20->CoreProcessorSet |= GroupSetMember;
          }
          v18 = (unsigned int)(v18 + 1);
          v54 = v18;
        }
        while ( (unsigned int)v18 < (unsigned int)KeNumberProcessors_0 );
      }
      v24 = KeCountSetBitsAffinityEx(&Prcb->PackageProcessorSet);
      if ( v24 > v13 )
        KeBugCheckEx(0x3Eu, (ULONG_PTR)Prcb, v24, Prcb->CoresPerPhysicalProcessor, *p_LogicalProcessorsPerCore);
      Prcb->CoreProcessorSet = v60;
    }
    v7 = Number;
    v25 = 65471;
  }
  else
  {
    KiDetectFpuLeakage();
    KiFpuLeakage = v36;
    if ( v36 )
      FeatureBits |= 0x20000000000ui64;
    if ( KiFlushPcid )
    {
      v37 = __readcr3();
      __writecr3(v37);
      if ( !KeGetCurrentThread()->ApcState.Process->Pcb.AddressPolicy )
        KiSetUserTbFlushPending();
    }
    else
    {
      v45 = __readcr4();
      if ( (v45 & 0x20080) != 0 )
      {
        __writecr4(v45 ^ 0x80);
        __writecr4(v45);
      }
      else
      {
        v46 = __readcr3();
        __writecr3(v46);
      }
    }
    KiSetPageAttributesTable();
    if ( KUSER_SHARED_DATA.ProcessorFeatures[12] )
      v38 = FeatureBits | 0x80000000;
    else
      v38 = FeatureBits & 0xFFFFFFFF3FFFFFFFui64 | 0x40000000;
    v52 = v38;
    v39 = __readcr4();
    __writecr4(v39 | 0x18);
    if ( KiFlushPcid )
    {
      v40 = __readcr3();
      __writecr3(v40);
      if ( !KeGetCurrentThread()->ApcState.Process->Pcb.AddressPolicy )
        KiSetUserTbFlushPending();
    }
    else
    {
      v47 = __readcr4();
      if ( (v47 & 0x20080) != 0 )
      {
        __writecr4(v47 ^ 0x80);
        __writecr4(v47);
      }
      else
      {
        v48 = __readcr3();
        __writecr3(v48);
      }
    }
    KiConfigureInitialNodes(Prcb);
    KiConfigureProcessorBlock(Prcb, v41);
    p_LogicalProcessorsPerCore = &Prcb->LogicalProcessorsPerCore;
    Prcb->PackageId = -(Prcb->CoresPerPhysicalProcessor * Prcb->LogicalProcessorsPerCore) & Prcb->InitialApicId;
    *(_DWORD *)&Prcb->PackageProcessorSet.Count = 1310721;
    Prcb->PackageProcessorSet.Reserved = 0;
    memset((UINT8 *)Prcb->PackageProcessorSet.Bitmap, 0, sizeof(Prcb->PackageProcessorSet.Bitmap));
    KeAddProcessorAffinityEx(&Prcb->PackageProcessorSet, 0i64);
    Prcb->CoreProcessorSet = Prcb->GroupSetMember;
    v55 = Prcb;
    v25 = 65471;
    v42 = 65471;
    if ( *(_DWORD *)&dst[28] )
      v42 = *(_DWORD *)&dst[28];
    KiMxCsrMask = v42;
    KeCompactServiceTable(KiServiceTable, KiArgumentTable, (unsigned int)KiServiceLimit, 0i64, 0x140000000ui64);
  }
  KiSetCacheInformation();
  PoInitializePrcb(Prcb);
  Prcb->ProcessorProfileControlArea = 0i64;
  Prcb->ProfileEventIndexAddress = &Prcb->ProfileEventIndexAddress;
  if ( KUSER_SHARED_DATA.XState.EnabledFeatures )
  {
    v26 = v52 | 0x800000;
    v52 |= 0x800000ui64;
    XSaveFeatureFlags = KeGetXSaveFeatureFlags();
    if ( (XSaveFeatureFlags & 8) != 0 )
    {
      v26 |= 0x8000ui64;
      v52 = v26;
    }
    if ( (XSaveFeatureFlags & 0x10) != 0 )
      v52 = v26 | 0x4000000000i64;
  }
  KiSetControlEnforcement((__int64)Prcb, &v52);
  v28 = v52;
  if ( v7 )
  {
    if ( *(_DWORD *)&dst[28] )
      v25 = *(_DWORD *)&dst[28];
    v29 = *(_QWORD *)&KeFeatureBits & 0xFFFFFFFF37FFFFFFui64 | 0x8000000;
    if ( (v52 & 0x8000000) == 0 )
      v29 = *(_QWORD *)&KeFeatureBits & 0xFFFFFFFF37FFFFFFui64;
    if ( Prcb->CpuVendor == 2 && Prcb->CpuType == 6 && Prcb->CpuModel == 23 && Prcb->CpuStepping == 10 )
    {
      v28 = v52 & 0xFFFFFFFFFFEFFFFFui64;
      v52 &= ~0x100000ui64;
      if ( (v55->FeatureBits & 0x100000) != 0 )
      {
        v28 |= 0x100000ui64;
        v52 = v28;
      }
    }
    if ( v28 != v29
      || v25 != KiMxCsrMask
      || KiProcessorBlock->CFlushSize != Prcb->CFlushSize
      || KiProcessorBlock->CoresPerPhysicalProcessor != Prcb->CoresPerPhysicalProcessor
      || KiProcessorBlock->LogicalProcessorsPerCore != *p_LogicalProcessorsPerCore )
    {
      KeBugCheckEx(0x3Eu, v28, v29, 0, 0);
    }
    __writecr8(2ui64);
    HvlEnlightenProcessor();
    v30 = Processa;
  }
  else
  {
    KeProcessorArchitecture = 9;
    KeProcessorLevel = Prcb->CpuType;
    KeProcessorRevision = Prcb->CpuStep;
    *(_QWORD *)&KeFeatureBits = v52;
    __writecr8(1ui64);
    KiFreezeExecutionLock = 0i64;
    KiInitSystem();
    qword_140C319F8 = (__int64)&KiProcessListHead;
    KiProcessListHead = (__int64)&KiProcessListHead;
    GroupAffinity.Reserved[1] = 0;
    GroupAffinity.Reserved[2] = 0;
    *(_DWORD *)&GroupAffinity.Group = (unsigned __int16)((unsigned int)KiProcessorIndexToNumberMappingTable[0] >> 6);
    GroupAffinity.Mask = 1i64 << (KiProcessorIndexToNumberMappingTable[0] & 0x3F);
    LODWORD(Flags) = 1;
    v30 = Processa;
    KeInitializeProcess(&Processa->Pcb, 0i64, &GroupAffinity, 0i64, 0i64, Flags);
    v30->Pcb.QuantumReset = 127;
    v43 = __rdtsc();
    KiWaitNever = __ROR8__(v43 ^ __ROL8__(v43, 43), v43 & 0xF);
    v44 = __rdtsc();
    KiWaitAlways = __ROL8__(__ROR8__(v44, 47) ^ v44, v44 & 0xF);
    HviGetHypervisorFeatures((_HV_X64_HYPERVISOR_FEATURES *)&HvFeaturesOut);
    if ( (*((_WORD *)&HvFeaturesOut + 6) & 0x1000) != 0 )
      KiNPIEPEnabled = 1;
  }
  if ( KiNPIEPEnabled )
    __writemsr(0x40000040u, 0xFui64);
  KiEnableXSave();
  KUSER_SHARED_DATA.TestRetInstruction = 195i64;
  KUSER_SHARED_DATA.ProcessorFeatures[2] = 1;
  KUSER_SHARED_DATA.ProcessorFeatures[3] = 1;
  KUSER_SHARED_DATA.ProcessorFeatures[6] = 1;
  KUSER_SHARED_DATA.ProcessorFeatures[8] = 1;
  KUSER_SHARED_DATA.ProcessorFeatures[9] = 1;
  KUSER_SHARED_DATA.ProcessorFeatures[10] = 1;
  KUSER_SHARED_DATA.ProcessorFeatures[14] = 1;
  if ( (v28 & 0x80000) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[13] = 1;
  if ( (v28 & 0x4000) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[7] = 1;
  if ( (v28 & 0x800000) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[17] = 1;
  if ( (v28 & 0x10000000) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[22] = 1;
  if ( (v28 & 0x4000000) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[20] = 1;
  if ( (v28 & 0x8000000) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[21] = 1;
  if ( (v28 & 0x100000000i64) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[28] = 1;
  if ( (v28 & 0x400000000i64) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[32] = 1;
  if ( (v28 & 0x800000000000i64) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[36] = 1;
  if ( (v28 & 0x1000000000000i64) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[37] = 1;
  if ( (v28 & 0x2000000000000i64) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[38] = 1;
  if ( (KUSER_SHARED_DATA.XState.EnabledFeatures & 4) != 0 && (v28 & 0x4000000000000i64) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[39] = 1;
  if ( (KUSER_SHARED_DATA.XState.EnabledFeatures & 4) != 0 && (v28 & 0x8000000000000i64) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[40] = 1;
  if ( (v28 & 0x10000000000000i64) != 0 && (KUSER_SHARED_DATA.XState.EnabledFeatures & 0xE0) != 0 )
    KUSER_SHARED_DATA.ProcessorFeatures[41] = 1;
  KUSER_SHARED_DATA.VirtualizationFlags = KiVirtFlags;
  v31 = Threada;
  KiInitializeIdleThread(&Threada->Tcb, KernelStack, &v30->Pcb, Prcb);
  if ( v7 )
  {
    if ( !HalpInitSystemPhase1(0i64) )
      KeBugCheck(0x5Cu);
    v35 = v62;
  }
  else
  {
    v35 = v62;
    InitBootProcessor(v62, v32, v33, v34);
  }
  KiCompleteKernelInit(Prcb, &v31->Tcb, v7);
  v35->Prcb = 0i64;
}

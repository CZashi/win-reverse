NTSTATUS __fastcall PspInitPhase0(_LOADER_PARAMETER_BLOCK *LoaderBlock)
{
  char *v1; // r9
  __int64 v3; // r10
  unsigned __int64 v4; // r8
  __int64 v5; // rax
  char v6; // cl
  __int64 v7; // rdx
  __int128 *v8; // r8
  __int64 v9; // r9
  int v10; // eax
  UINT64 v11; // rdi
  _RTL_RUN_ONCE *v12; // rcx
  _RTL_RUN_ONCE *v13; // rcx
  __int64 v14; // rax
  _RTL_RUN_ONCE *v15; // rcx
  _RTL_RUN_ONCE *v16; // rcx
  __int64 v17; // rax
  _RTL_RUN_ONCE *v18; // rcx
  _RTL_RUN_ONCE *v19; // rcx
  __int64 v20; // rax
  _EPROCESS *Process; // rcx
  _HANDLE_TABLE *HandleTable; // rax
  unsigned int *v23; // rdi
  int v24; // ebx
  INT64 v25; // rbx
  void *v26; // rcx
  _EPROCESS *v27; // rcx
  _OBJECT_NAME_INFORMATION *ImageFileName; // rcx
  UINT64 CreateFlags; // [rsp+20h] [rbp-E0h]
  VOID *SectionHandle; // [rsp+28h] [rbp-D8h]
  _UNICODE_STRING DestinationString; // [rsp+50h] [rbp-B0h] BYREF
  _OBJECT_TYPE_INITIALIZER dst; // [rsp+60h] [rbp-A0h] BYREF
  PVOID Object; // [rsp+E0h] [rbp-20h] BYREF
  void *ThreadHandle; // [rsp+E8h] [rbp-18h] BYREF
  UINT64 MitigationOptions[2]; // [rsp+F0h] [rbp-10h] BYREF
  __int64 v37; // [rsp+100h] [rbp+0h]
  INT64 v38[2]; // [rsp+110h] [rbp+10h] BYREF
  __int64 v39; // [rsp+120h] [rbp+20h]
  int v40; // [rsp+130h] [rbp+30h]
  char v41; // [rsp+134h] [rbp+34h] BYREF
  int v42; // [rsp+138h] [rbp+38h]
  char v43; // [rsp+13Ch] [rbp+3Ch]
  int v44; // [rsp+140h] [rbp+40h]
  char v45; // [rsp+144h] [rbp+44h]
  int v46; // [rsp+148h] [rbp+48h]
  char v47; // [rsp+14Ch] [rbp+4Ch]
  int v48; // [rsp+150h] [rbp+50h]
  char v49; // [rsp+154h] [rbp+54h]
  int v50; // [rsp+158h] [rbp+58h]
  char v51; // [rsp+15Ch] [rbp+5Ch]
  __int128 v52[2]; // [rsp+160h] [rbp+60h] BYREF

  PspMinimumWorkingSet += 30i64;
  v1 = &v41;
  PspMaximumWorkingSet += 300i64;
  ThreadHandle = 0i64;
  DestinationString = 0i64;
  v40 = 0;
  v52[0] = (__int128)_mm_load_si128((const __m128i *)&_xmm);
  v41 = 1;
  v3 = 6i64;
  v42 = 2;
  PspHardenedMitigationOptionsMap = 0i64;
  v43 = 3;
  v44 = 3;
  v45 = 1;
  v46 = 1;
  v47 = 1;
  v48 = 4;
  v49 = 1;
  v50 = 5;
  v51 = 1;
  v52[1] = (__int128)_mm_load_si128((const __m128i *)&_xmm);
  qword_140CFBC78 = 0i64;
  do
  {
    v4 = (unsigned int)(4 * *((_DWORD *)v1 - 1));
    v5 = (unsigned __int8)*v1;
    v6 = (4 * *(v1 - 4)) & 0x3F;
    v1 += 8;
    v4 >>= 6;
    v7 = (v5 << v6) | *((_QWORD *)&PspHardenedMitigationOptionsMap + v4) & ~(3i64 << v6);
    *((_QWORD *)&PspHardenedMitigationOptionsMap + v4) = v7;
    --v3;
  }
  while ( v3 );
  if ( (unsigned int)PspSystemMitigationOptionsLength < 0x18 )
    memset(
      (UINT8 *)(0x140000000i64 + (unsigned int)PspSystemMitigationOptionsLength + 13613520i64),
      0,
      24i64 - (unsigned int)PspSystemMitigationOptionsLength);
  LOBYTE(v7) = 1;
  *(_OWORD *)MitigationOptions = PspSystemMitigationOptions;
  PspSystemMitigationOptionsLength = 24;
  v37 = qword_140CFB9E0;
  if ( PspValidateMitigationOptions((UINT64)MitigationOptions, v7) < 0 )
  {
    PspSystemMitigationOptions = 0i64;
    qword_140CFB9E0 = 0i64;
  }
  v8 = v52;
  v9 = 8i64;
  do
  {
    v10 = *(_DWORD *)v8;
    v8 = (__int128 *)((char *)v8 + 4);
    *((_QWORD *)&PspSystemMitigationOptions + ((unsigned __int64)(unsigned int)(4 * v10) >> 6)) &= ~(3i64 << ((4 * v10) & 0x3F));
    --v9;
  }
  while ( v9 );
  v11 = (unsigned int)PspSystemMitigationAuditOptionsLength;
  if ( (unsigned int)PspSystemMitigationAuditOptionsLength < 0x18 )
    memset(
      &PspSystemMitigationAuditOptions + (unsigned int)PspSystemMitigationAuditOptionsLength,
      0,
      24i64 - (unsigned int)PspSystemMitigationAuditOptionsLength);
  *(_OWORD *)v38 = *(_OWORD *)&PspSystemMitigationAuditOptions;
  v39 = qword_140CFBB80;
  if ( PspValidateMitigationAuditOptions((INT64)v38) < 0 )
    memset(&PspSystemMitigationAuditOptions, 0, v11);
  v12 = (_RTL_RUN_ONCE *)&PspCreateThreadNotifyRoutine;
  do
  {
    CmSiRWLockInitialize(v12);
    v12 = v13 + 1;
  }
  while ( v14 != 1 );
  v15 = &PspCreateProcessNotifyRoutine;
  do
  {
    CmSiRWLockInitialize(v15);
    v15 = v16 + 1;
  }
  while ( v17 != 1 );
  v18 = (_RTL_RUN_ONCE *)&PspLoadImageNotifyRoutine;
  do
  {
    CmSiRWLockInitialize(v18);
    v18 = v19 + 1;
  }
  while ( v20 != 1 );
  PsChangeQuantumTable(0, (unsigned int)PsRawPrioritySeparation);
  PspActiveProcessLock = 0i64;
  qword_140C1E078 = (__int64)&PsActiveProcessHead;
  PsActiveProcessHead = (__int64)&PsActiveProcessHead;
  Process = KeGetCurrentThread()->ApcState.Process;
  PsIdleProcess = Process;
  Process->ProcessLock.Value = 0i64;
  ExInitializePushLock(&Process->RundownProtect);
  PsIdleProcess->Pcb.KernelTime = 0;
  memset((UINT8 *)&dst, 0, sizeof(dst));
  strcpy((char *)&dst, "x");
  *(_QWORD *)&dst.PoolType = 512i64;
  RtlInitUnicodeString(&DestinationString, L"Job");
  *(_QWORD *)&dst.ObjectTypeCode = 2048i64;
  dst.DeleteProcedure = (void (__fastcall *)(void *))PspJobDelete;
  dst.DefaultNonPagedPoolCharge = 1600;
  dst.CloseProcedure = (void (__fastcall *)(_EPROCESS *, void *, unsigned __int64, unsigned __int64))PspJobClose;
  dst.ValidAccessMask = 2031679;
  LOBYTE(dst.ObjectTypeFlags) = dst.ObjectTypeFlags & 0x77 | 8;
  dst.GenericMapping = (_GENERIC_MAPPING)PspJobMapping;
  LODWORD(HandleTable) = ObCreateObjectType(&DestinationString, &dst, 0i64, (_OBJECT_TYPE **)&PsJobType);
  if ( (int)HandleTable >= 0 )
  {
    LODWORD(HandleTable) = SeRegisterObjectTypeMandatoryPolicy((_OBJECT_TYPE *)PsJobType, 1ui64);
    if ( (int)HandleTable >= 0 )
    {
      dst.InvalidAttributes = 176;
      RtlInitUnicodeString(&DestinationString, L"Process");
      LOBYTE(dst.ObjectTypeFlags) |= 0xC2u;
      dst.DeleteProcedure = (void (__fastcall *)(void *))PspProcessDelete;
      dst.ObjectTypeCode = 32;
      dst.OpenProcedure = (int (__fastcall *)(_OB_OPEN_REASON, char, _EPROCESS *, void *, unsigned int *, unsigned int))PspProcessOpen;
      dst.DefaultPagedPoolCharge = 4096;
      dst.CloseProcedure = (void (__fastcall *)(_EPROCESS *, void *, unsigned __int64, unsigned __int64))PspProcessClose;
      dst.DefaultNonPagedPoolCharge = 2624;
      dst.ValidAccessMask = 0x1FFFFF;
      dst.RetainAccess = 1052672;
      dst.GenericMapping = (_GENERIC_MAPPING)PspProcessMapping;
      LODWORD(HandleTable) = ObCreateObjectType(&DestinationString, &dst, 0i64, (_OBJECT_TYPE **)&PsProcessType);
      if ( (int)HandleTable >= 0 )
      {
        LODWORD(HandleTable) = SeRegisterObjectTypeMandatoryPolicy((_OBJECT_TYPE *)PsProcessType, 3ui64);
        if ( (int)HandleTable >= 0 )
        {
          RtlInitUnicodeString(&DestinationString, L"Thread");
          LOBYTE(dst.ObjectTypeFlags) |= 0x80u;
          dst.DeleteProcedure = (void (__fastcall *)(void *))PspThreadDelete;
          dst.ObjectTypeCode = 4;
          dst.OpenProcedure = (int (__fastcall *)(_OB_OPEN_REASON, char, _EPROCESS *, void *, unsigned int *, unsigned int))PspThreadOpen;
          dst.DefaultPagedPoolCharge = 0;
          dst.DefaultNonPagedPoolCharge = 2200;
          dst.CloseProcedure = 0i64;
          dst.ValidAccessMask = 0x1FFFFF;
          dst.RetainAccess = 1054720;
          dst.GenericMapping = (_GENERIC_MAPPING)PspThreadMapping;
          LODWORD(HandleTable) = ObCreateObjectType(&DestinationString, &dst, 0i64, (_OBJECT_TYPE **)&PsThreadType);
          if ( (int)HandleTable >= 0 )
          {
            LODWORD(HandleTable) = SeRegisterObjectTypeMandatoryPolicy((_OBJECT_TYPE *)PsThreadType, 3ui64);
            if ( (int)HandleTable >= 0 )
            {
              RtlInitUnicodeString(&DestinationString, L"Partition");
              memset((UINT8 *)&dst, 0, sizeof(dst));
              LOBYTE(dst.ObjectTypeFlags) |= 0xCu;
              dst.OpenProcedure = (int (__fastcall *)(_OB_OPEN_REASON, char, _EPROCESS *, void *, unsigned int *, unsigned int))PspOpenPartitionHandle;
              strcpy((char *)&dst, "x");
              dst.CloseProcedure = (void (__fastcall *)(_EPROCESS *, void *, unsigned __int64, unsigned __int64))PspClosePartitionHandle;
              dst.InvalidAttributes = 16;
              dst.DeleteProcedure = (void (__fastcall *)(void *))PspDeletePartition;
              dst.ValidAccessMask = 2031619;
              dst.PoolType = NonPagedPoolNx;
              dst.GenericMapping = (_GENERIC_MAPPING)PspPartitionMapping;
              dst.DefaultNonPagedPoolCharge = 128;
              LODWORD(HandleTable) = ObCreateObjectType(&DestinationString, &dst, 0i64, &PsPartitionType);
              if ( (int)HandleTable >= 0 )
              {
                memset((UINT8 *)&dst, 0, sizeof(dst));
                strcpy((char *)&dst, "x");
                dst.PoolType = NonPagedPoolNx;
                LOBYTE(dst.ObjectTypeFlags) = dst.ObjectTypeFlags & 0x7D | 2;
                v23 = (unsigned int *)PspMemoryReserveObjectSizes;
                dst.InvalidAttributes = 176;
                v24 = 0;
                dst.GenericMapping = (_GENERIC_MAPPING)PspMemReserveMapping;
                dst.ValidAccessMask = 983043;
                do
                {
                  dst.DefaultNonPagedPoolCharge = *v23;
                  LODWORD(HandleTable) = ObCreateObjectType(
                                           (_UNICODE_STRING *)&PspMemoryReserveObjectNames[2 * v24],
                                           &dst,
                                           0i64,
                                           &PspMemoryReserveObjectTypes + v24);
                  if ( (int)HandleTable < 0 )
                    goto LABEL_40;
                  ++v24;
                  v23 += 2;
                }
                while ( v24 < 2 );
                RtlInitUnicodeString(&DestinationString, L"ActivityReference");
                memset((UINT8 *)&dst, 0, sizeof(dst));
                LOBYTE(dst.ObjectTypeFlags) |= 4u;
                strcpy((char *)&dst, "x");
                *(_QWORD *)&dst.PoolType = 0x800000001i64;
                dst.InvalidAttributes = 402;
                dst.GenericMapping = (_GENERIC_MAPPING)PspActivityReferenceMapping;
                dst.ValidAccessMask = 2031616;
                dst.CloseProcedure = (void (__fastcall *)(_EPROCESS *, void *, unsigned __int64, unsigned __int64))PspCloseActivityReference;
                LODWORD(HandleTable) = ObCreateObjectType(
                                         &DestinationString,
                                         &dst,
                                         0i64,
                                         &PspActivityReferenceObjectType);
                if ( (int)HandleTable >= 0 )
                {
                  if ( PspInitializeJobStructures() )
                  {
                    if ( PspInitializeSiloStructures() )
                    {
                      *(_QWORD *)&qword_140C130B0 = 0i64;
                      qword_140C130A8 = (__int64)&PspWorkingSetChangeHead;
                      PspWorkingSetChangeHead = (__int64)&PspWorkingSetChangeHead;
                      PspAffinityUpdateLock.0 = 0i64;
                      HandleTable = ExCreateHandleTable(0i64, 0i64);
                      PspCidTable = HandleTable;
                      if ( HandleTable )
                      {
                        CmSiRWLockInitialize((PRTL_RUN_ONCE)&PsWin32CallBack);
                        CmSiRWLockInitialize(&PsWin32NullCallBack);
                        LOBYTE(PspCidTable->Flags) |= 1u;
                        PsReaperWorkItem.WorkerRoutine = (void (__fastcall *)(void *))PspReaper;
                        qword_140C1E030 = (__int64)PspProcessRundownWorker;
                        PspProcessRundownCacheWorkItem.WorkerRoutine = (void (__fastcall *)(void *))PspProcessRundownWorkerSingle;
                        PsReaperListHead = 0i64;
                        PsReaperWorkItem.Parameter = 0i64;
                        PsReaperWorkItem.List.Flink = 0i64;
                        qword_140C1E038 = 0i64;
                        PspProcessRundownWorkItem = 0i64;
                        PspProcessRundownCacheWorkItem.Parameter = 0i64;
                        PspProcessRundownCacheWorkItem.List.Flink = 0i64;
                        PspBootAccessToken = (PVOID)(PsIdleProcess->Token.Value & 0xFFFFFFFFFFFFFFF0ui64);
                        LODWORD(HandleTable) = PspInitializeSystemPartitionPhase0();
                        if ( (int)HandleTable >= 0 )
                        {
                          v25 = PspSystemPartition;
                          LODWORD(SectionHandle) = 0;
                          LOBYTE(CreateFlags) = 0;
                          LODWORD(HandleTable) = PspCreateProcess(
                                                   (VOID **)(PspSystemPartition + 112),
                                                   0x1FFFFFui64,
                                                   0i64,
                                                   0i64,
                                                   CreateFlags,
                                                   SectionHandle,
                                                   0i64,
                                                   0i64);
                          if ( (int)HandleTable >= 0 )
                          {
                            v26 = *(void **)(v25 + 112);
                            Object = 0i64;
                            LODWORD(HandleTable) = ObReferenceObjectByHandle(
                                                     v26,
                                                     0,
                                                     (POBJECT_TYPE)PsProcessType,
                                                     0,
                                                     &Object,
                                                     0i64);
                            v27 = (_EPROCESS *)Object;
                            *(_QWORD *)(v25 + 104) = Object;
                            if ( (int)HandleTable >= 0 )
                            {
                              PsInitialSystemProcess = v27;
                              _InterlockedOr((volatile signed __int32 *)&v27->2512, 0x40000000u);
                              _InterlockedOr((volatile signed __int32 *)&PsInitialSystemProcess->2516, 0x2000u);
                              _InterlockedOr((volatile signed __int32 *)&PsInitialSystemProcess->2172, 0x1000u);
                              strcpy_s((CHAR *)PsIdleProcess->ImageFileName, 0xFui64, "Idle");
                              strcpy_s((CHAR *)PsInitialSystemProcess->ImageFileName, 0xFui64, "System");
                              PsInitialSystemProcess->SeAuditProcessCreationInfo.ImageFileName = (_OBJECT_NAME_INFORMATION *)ExAllocatePoolWithTag(NonPagedPoolNx, 0x10u, 0x61506553u);
                              LODWORD(HandleTable) = (_DWORD)PsInitialSystemProcess;
                              ImageFileName = PsInitialSystemProcess->SeAuditProcessCreationInfo.ImageFileName;
                              if ( ImageFileName )
                              {
                                *ImageFileName = 0i64;
                                LODWORD(HandleTable) = PsCreateSystemThread(
                                                         &ThreadHandle,
                                                         0x1FFFFFu,
                                                         0i64,
                                                         0i64,
                                                         0i64,
                                                         Phase1Initialization,
                                                         LoaderBlock);
                                if ( (int)HandleTable >= 0 )
                                {
                                  LODWORD(HandleTable) = ObCloseHandle(ThreadHandle, 0);
                                  if ( !VslVsmEnabled )
                                  {
LABEL_39:
                                    PsVmProcessorHostTransitionEvent.0 = 0i64;
                                    LOBYTE(HandleTable) = 1;
                                    return (int)HandleTable;
                                  }
                                  PspIumWorkItem.Parameter = 0i64;
                                  PspIumWorkItem.WorkerRoutine = (void (__fastcall *)(void *))PspIumWorker;
                                  PspIumWorkItem.List.Flink = 0i64;
                                  HandleTable = (_HANDLE_TABLE *)MmAllocateMappingAddress(0x1000u, 0x466D7356u);
                                  PspIumFreeMapping = HandleTable;
                                  if ( HandleTable )
                                  {
                                    PspIumLogBuffer = MmAllocateIndependentPagesEx(
                                                        0x2000ui64,
                                                        -1,
                                                        (_QWORD *)0xFFFFFFFFFFFFFFFFi64,
                                                        1u);
                                    PsIumResumeAfterHibernate();
                                    LODWORD(HandleTable) = VslGetNestedPageProtectionFlags();
                                    if ( ((unsigned __int8)HandleTable & 0x40) != 0 )
                                    {
                                      LODWORD(HandleTable) = PspSystemMitigationOptions;
                                      *(_QWORD *)&PspSystemMitigationOptions = PspSystemMitigationOptions & 0xFFFFFF0FFFFFFFFFui64 | 0x5000000000i64;
                                    }
                                    if ( PspIumLogBuffer )
                                    {
                                      *(&PspVsmLogCallbackRecord.State + 4) = 0;
                                      KeRegisterBugCheckReasonCallback(
                                        &PspVsmLogCallbackRecord,
                                        PspVsmLogBugCheckCallback,
                                        KbCallbackSecondaryDumpData,
                                        (PUCHAR)"SecureKernelFailureLog");
                                    }
                                    goto LABEL_39;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LABEL_40:
  LOBYTE(HandleTable) = 0;
  return (int)HandleTable;
}

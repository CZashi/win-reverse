NTSTATUS __stdcall NtNotifyChangeMultipleKeys(
        PVOID MasterKeyHandle,
        UINT64 Count,
        _OBJECT_ATTRIBUTES *SubordinateObjects,
        PVOID Event,
        PVOID ApcRoutine,
        PVOID a6,
        _IO_STATUS_BLOCK *Address,
        UINT64 PostBlock,
        PVOID ApcContext,
        _IO_STATUS_BLOCK *IoStatusBlock,
        INT64 CompletionFilter,
        UINT8 WatchTree,
        PVOID Buffer,
        UINT64 BufferSize,
        UINT8 Asynchronous)
{
  unsigned int v15; // er13
  _VM_COUNTERS_EX *v16; // r12
  int v17; // esi
  __int64 v18; // r8
  char PreviousMode; // cl
  NTSTATUS v20; // edi
  PADAPTER_OBJECT v21; // r14
  _VM_COUNTERS_EX *v22; // rax
  _VM_COUNTERS_EX *v23; // rsi
  int v24; // edx
  PVOID v25; // rcx
  PVOID *v26; // rax
  _CM_KEY_CONTROL_BLOCK **p_KeyControlBlock; // r15
  _CM_KEY_CONTROL_BLOCK *KeyControlBlock; // rcx
  _ETW_TP_EVENT_TIMER_EXPIRATION_END *v29; // r9
  CMHIVE *v30; // rcx
  _CM_KEY_CONTROL_BLOCK *v31; // rcx
  char v32; // r15
  _EWOW64PROCESS *WoW64Process; // rax
  bool v35; // r14
  _ETHREAD *CurrentThread; // rdx
  PVOID *v37; // r8
  __int64 v38; // r9
  CMHIVE *KeyHive; // rcx
  _DMA_OPERATIONS *DmaOperations; // rax
  CMHIVE *AllocateAdapterChannel; // rdx
  _ETW_TP_EVENT_TIMER_EXPIRATION_END *v42; // r9
  unsigned __int16 Machine; // ax
  _CM_KEY_CONTROL_BLOCK *v44; // rcx
  _VM_COUNTERS_EX *v45; // rcx
  CMHIVE *v46; // rcx
  _CM_KEY_CONTROL_BLOCK *v47; // rcx
  __int64 v48; // rcx
  _VM_COUNTERS_EX **v49; // rax
  void *CurrentIrql; // r11
  __int64 v51; // rdx
  _VM_COUNTERS_EX **v52; // rcx
  NTSTATUS v53; // eax
  unsigned __int8 v54; // di
  __int64 v55; // rax
  _VM_COUNTERS_EX **v56; // rcx
  __int64 v57; // rdx
  _VM_COUNTERS_EX **v58; // rcx
  __int64 v59; // rax
  _VM_COUNTERS_EX **v60; // rcx
  __int64 v61; // rdx
  _VM_COUNTERS_EX **v62; // rcx
  __int64 v63; // rax
  unsigned __int8 v64; // r15
  __int64 v65; // rax
  _VM_COUNTERS_EX **v66; // rcx
  __int64 v67; // rdx
  _VM_COUNTERS_EX **v68; // rcx
  __int64 v69; // rax
  _VM_COUNTERS_EX **v70; // rcx
  __int64 v71; // rdx
  _VM_COUNTERS_EX **v72; // rcx
  VOID **Object; // [rsp+20h] [rbp-208h]
  VOID **Objecta; // [rsp+20h] [rbp-208h]
  _OBJECT_HANDLE_INFORMATION *HandleInformation; // [rsp+28h] [rbp-200h]
  _OBJECT_HANDLE_INFORMATION *HandleInformationa; // [rsp+28h] [rbp-200h]
  PVOID v77; // [rsp+30h] [rbp-1F8h]
  _VM_COUNTERS_EX *v78; // [rsp+38h] [rbp-1F0h]
  _VM_COUNTERS_EX *v79; // [rsp+38h] [rbp-1F0h]
  PVOID v80; // [rsp+40h] [rbp-1E8h]
  char v81; // [rsp+42h] [rbp-1E6h]
  PVOID *BlockType; // [rsp+48h] [rbp-1E0h]
  int v84; // [rsp+50h] [rbp-1D8h]
  CM_KEY_BODY *KeyBody; // [rsp+58h] [rbp-1D0h] BYREF
  PVOID RundownRoutine; // [rsp+60h] [rbp-1C8h]
  PADAPTER_OBJECT DmaAdapter; // [rsp+68h] [rbp-1C0h] BYREF
  PVOID NormalRoutine; // [rsp+70h] [rbp-1B8h]
  VOID *Handle; // [rsp+78h] [rbp-1B0h]
  PVOID v90; // [rsp+80h] [rbp-1A8h]
  PVOID v91; // [rsp+88h] [rbp-1A0h] BYREF
  INT8 ApcMode[8]; // [rsp+90h] [rbp-198h]
  PVOID NormalContext; // [rsp+98h] [rbp-190h]
  int v94; // [rsp+A0h] [rbp-188h]
  _CM_PARSE_CONTEXT dst[2]; // [rsp+B0h] [rbp-178h] BYREF

  v90 = SubordinateObjects;
  v15 = Count;
  Handle = MasterKeyHandle;
  *(_QWORD *)ApcMode = Address;
  KeyBody = 0i64;
  NormalRoutine = 0i64;
  v16 = 0i64;
  NormalContext = 0i64;
  LOWORD(v17) = 1;
  LODWORD(BlockType) = 1;
  memset((UINT8 *)dst, 0, 0x128ui64);
  BYTE4(v80) = 0;
  RundownRoutine = 0i64;
  v94 = 0;
  LOBYTE(v80) = CmpAcquireShutdownRundown();
  if ( !(_BYTE)v80 )
    return -1073741431;
  v18 = 1i64;
  if ( v15 <= 1 )
  {
    BYTE3(v80) = v15 == 1;
    PreviousMode = KeGetCurrentThread()->PreviousMode;
    BYTE1(v80) = PreviousMode;
    if ( PreviousMode )
    {
      if ( (PostBlock & 0x10000000) != 0 )
      {
        if ( WatchTree && !ApcRoutine && Event )
        {
          v17 = 4;
LABEL_9:
          LODWORD(BlockType) = v17;
          goto LABEL_10;
        }
        goto LABEL_83;
      }
      WoW64Process = KeGetCurrentThread()->ApcState.Process->WoW64Process;
      v35 = 0;
      if ( WoW64Process )
      {
        Machine = WoW64Process->Machine;
        if ( Machine == 332 || Machine == 452 )
          v35 = 1;
      }
      BYTE4(v80) = v35;
      ProbeForWrite(Address, 8 * !v35 + 8, 4u);
      ProbeForWrite(IoStatusBlock, CompletionFilter, 4u);
      if ( v35 )
      {
        Address->Pointer = (void *)259;
      }
      else
      {
        Address->Status = 259;
        Address->Information = 0i64;
      }
      PreviousMode = BYTE1(v80);
      if ( WatchTree )
      {
        v17 = 2;
        goto LABEL_9;
      }
LABEL_10:
      if ( (_DWORD)PostBlock != (PostBlock & 0x1000000F) )
      {
        v20 = -1073741811;
        goto LABEL_39;
      }
      v20 = CmObReferenceObjectByHandle(Handle, 0x10ui64, (_OBJECT_TYPE *)v18, PreviousMode, (VOID **)&KeyBody, 0i64);
      if ( v20 < 0 )
      {
LABEL_39:
        CmpReleaseShutdownRundown();
        return v20;
      }
      v21 = 0i64;
      DmaAdapter = 0i64;
      if ( v15 == 1 )
      {
        LODWORD(dst[0].SymlinkCachedKcb) = -1;
        *(_QWORD *)&dst[1].CtxFlags = &dst[0].HiveMountWaitIndex;
        *(_QWORD *)&dst[0].HiveMountWaitIndex = &dst[0].HiveMountWaitIndex;
        memset((UINT8 *)&dst[1].OriginatingPoint, 0, 0x50ui64);
        LOBYTE(Object) = BYTE1(v80);
        v20 = CmObReferenceObjectByName((_OBJECT_ATTRIBUTES *)v90, 0i64, 16i64, v38, (INT64)Object, dst, &DmaAdapter);
        CmpCleanupParseContext(dst, 0);
        if ( v20 < 0 )
          goto LABEL_37;
        v21 = DmaAdapter;
        if ( KeyBody->KeyControlBlock->KeyHash.KeyHive == (_HHIVE *)DmaAdapter->AdapterObject.DmaHeader.DmaOperations->AllocateAdapterChannel )
        {
          HalPutDmaAdapter(DmaAdapter);
          v20 = -1073741811;
          goto LABEL_37;
        }
      }
      v22 = CmpAllocatePostBlock((_MI_IO_PFN_ENTRY)v17, (_ETW_TP_EVENT_TIMER_EXPIRATION_END *)0x10000, 0i64, 0i64);
      v23 = v22;
      Handle = v22;
      if ( !v22 )
      {
        if ( v15 == 1 )
          HalPutDmaAdapter(v21);
        goto LABEL_90;
      }
      if ( v15 == 1 )
      {
        v16 = CmpAllocatePostBlock((_MI_IO_PFN_ENTRY)BlockType, 0i64, (_CM_KEY_BODY *)v21, v22);
        NormalContext = v16;
        if ( !v16 )
        {
          HalPutDmaAdapter(v21);
          CmpFreePostBlock(v23);
LABEL_90:
          v20 = -1073741670;
          goto LABEL_37;
        }
      }
      v24 = (int)BlockType;
      if ( (_DWORD)BlockType != 1 )
      {
        if ( Event )
        {
          v91 = 0i64;
          v20 = ObReferenceObjectByHandle(Event, 2u, (POBJECT_TYPE)ExEventObjectType, SBYTE1(v80), &v91, 0i64);
          NormalRoutine = v91;
          if ( v20 < 0 )
          {
            if ( v15 != 1 )
            {
LABEL_93:
              v45 = v23;
LABEL_94:
              CmpFreePostBlock(v45);
              goto LABEL_37;
            }
LABEL_92:
            CmpFreePostBlock(v16);
            goto LABEL_93;
          }
          KeResetEvent((PRKEVENT)v91);
          v24 = (int)BlockType;
        }
        v25 = NormalRoutine;
        v26 = *(PVOID **)&v23[1].WorkingSetSize;
        if ( v24 == 2 )
        {
          v26[13] = Address;
          *(_QWORD *)(*(_QWORD *)&v23[1].WorkingSetSize + 8i64) = v25;
          CurrentThread = (_ETHREAD *)KeGetCurrentThread();
          v37 = (PVOID *)AlpcMessageDeleteProcedure;
          if ( ApcRoutine )
            v37 = (PVOID *)ApcRoutine;
          LOBYTE(v77) = ApcRoutine != 0i64 ? BYTE1(v80) : 0;
          KeInitializeApc(
            (_KAPC *)(*(_QWORD *)&v23[1].WorkingSetSize + 16i64),
            CurrentThread,
            CurrentApcEnvironment,
            CmpPostApc,
            (_KAPC *)CmpPostApcRunDown,
            v37,
            v77,
            a6,
            v80,
            BlockType,
            (PVOID *)Event,
            (PVOID *)KeyBody,
            RundownRoutine,
            (_KAPC *)DmaAdapter,
            NormalRoutine,
            Handle,
            v90,
            v91,
            ApcMode[0],
            NormalContext);
          v21 = DmaAdapter;
        }
        else
        {
          *v26 = NormalRoutine;
          if ( v24 != 4 )
          {
            *(_QWORD *)(*(_QWORD *)&v23[1].WorkingSetSize + 8i64) = ApcRoutine;
            *(_DWORD *)(*(_QWORD *)&v23[1].WorkingSetSize + 16i64) = (_DWORD)a6;
          }
        }
      }
      CmpLockRegistry();
      p_KeyControlBlock = &KeyBody->KeyControlBlock;
      KeyControlBlock = KeyBody->KeyControlBlock;
      if ( v15 == 1 )
        CmpLockTwoKcbsShared(KeyControlBlock, (_CM_KEY_CONTROL_BLOCK *)v21->AdapterObject.DmaHeader.DmaOperations);
      else
        CmpLockKcbShared(KeyControlBlock);
      if ( !CmpIsKeyDeletedForKeyBody(KeyBody, 0i64) )
      {
        if ( v15 != 1 )
        {
LABEL_26:
          CmLockHive((CMHIVE *)(*p_KeyControlBlock)->KeyHash.KeyHive);
          v84 = 1;
          goto LABEL_27;
        }
        if ( !CmpIsKeyDeletedForKeyBody((_CM_KEY_BODY *)v21, 0i64) )
        {
          KeyHive = (CMHIVE *)(*p_KeyControlBlock)->KeyHash.KeyHive;
          DmaOperations = v21->AdapterObject.DmaHeader.DmaOperations;
          AllocateAdapterChannel = (CMHIVE *)DmaOperations->AllocateAdapterChannel;
          if ( KeyHive < AllocateAdapterChannel )
          {
            CmLockHive(KeyHive);
            CmLockHive((CMHIVE *)v21->AdapterObject.DmaHeader.DmaOperations->AllocateAdapterChannel);
            v84 = 2;
          }
          else
          {
            if ( KeyHive == AllocateAdapterChannel )
              goto LABEL_26;
            CmLockHive((CMHIVE *)DmaOperations->AllocateAdapterChannel);
            CmLockHive((CMHIVE *)(*p_KeyControlBlock)->KeyHash.KeyHive);
            v84 = 3;
          }
          RundownRoutine = v21->AdapterObject.DmaHeader.DmaOperations->AllocateAdapterChannel;
LABEL_27:
          LOCK_POST_LIST();
          LOBYTE(v29) = (_BYTE)ApcContext;
          v20 = (unsigned int)CmpNotifyChangeKey(
                                (_ETW_TP_EVENT_TIMER_CANCELLED *)KeyBody,
                                (_CM_KEY_BODY *)v23,
                                (_VM_COUNTERS_EX *)(unsigned int)PostBlock,
                                v29,
                                (_REAL_NOTIFY_SYNC *)Object,
                                (_EVENT_TRACE *)HandleInformation,
                                (_ETW_TP_EVENT_TIMER_EXPIRATION_END *)v23,
                                v78);
          if ( v20 >= 0 )
          {
            v81 = BYTE3(v80);
            if ( v15 == 1 )
            {
              ObfReferenceObject(v21);
              if ( v20 )
              {
                LOBYTE(v42) = (_BYTE)ApcContext;
                v20 = (unsigned int)CmpNotifyChangeKey(
                                      (_ETW_TP_EVENT_TIMER_CANCELLED *)v21,
                                      (_CM_KEY_BODY *)v16,
                                      (_VM_COUNTERS_EX *)(unsigned int)PostBlock,
                                      v42,
                                      (_REAL_NOTIFY_SYNC *)Objecta,
                                      (_EVENT_TRACE *)HandleInformationa,
                                      (_ETW_TP_EVENT_TIMER_EXPIRATION_END *)v23,
                                      v79);
                v81 = BYTE3(v80);
                if ( v20 < 0 )
                {
                  v48 = *(_QWORD *)&v23->PeakVirtualSize;
                  v49 = *(_VM_COUNTERS_EX ***)&v23->PageFaultCount;
                  if ( *(_VM_COUNTERS_EX **)(*(_QWORD *)&v23->PeakVirtualSize + 8i64) != v23 )
                    goto LABEL_151;
                  if ( *v49 != v23 )
                    goto LABEL_151;
                  *v49 = (_VM_COUNTERS_EX *)v48;
                  *(_QWORD *)(v48 + 8) = v49;
                  CurrentIrql = (void *)KeGetCurrentIrql();
                  v90 = CurrentIrql;
                  __writecr8(1ui64);
                  v51 = *(_QWORD *)&v23->WorkingSetSize;
                  v52 = *(_VM_COUNTERS_EX ***)&v23->QuotaPagedPoolUsage;
                  if ( *(_VM_COUNTERS_EX **)(v51 + 8) != (_VM_COUNTERS_EX *)&v23->WorkingSetSize
                    || *v52 != (_VM_COUNTERS_EX *)&v23->WorkingSetSize )
                  {
                    goto LABEL_151;
                  }
                  *v52 = (_VM_COUNTERS_EX *)v51;
                  *(_QWORD *)(v51 + 8) = v52;
                  __writecr8((unsigned __int8)CurrentIrql);
                  v81 = BYTE3(v80);
                }
              }
              else
              {
                CmpFreePostBlock(v16);
                v81 = 0;
              }
            }
            UNLOCK_POST_LIST();
            if ( v84 != 1 )
            {
              if ( v84 != 2 )
              {
                CmUnlockHive((CMHIVE *)(*p_KeyControlBlock)->KeyHash.KeyHive);
                v30 = (CMHIVE *)RundownRoutine;
LABEL_31:
                CmUnlockHive(v30);
                v31 = *p_KeyControlBlock;
                if ( v15 == 1 )
                  CmpUnlockTwoKcbs(v31, (_CM_KEY_CONTROL_BLOCK *)v21->AdapterObject.DmaHeader.DmaOperations);
                else
                  CmpUnlockKcb((ULONG_PTR)v31);
                CmpUnlockRegistry();
                if ( v21 )
                  HalPutDmaAdapter(v21);
                if ( v20 < 0 )
                {
                  CmpFreePostBlock(v23);
                  if ( NormalRoutine )
                    HalPutDmaAdapter((PADAPTER_OBJECT)NormalRoutine);
                  goto LABEL_37;
                }
                if ( (_DWORD)BlockType != 1 )
                {
LABEL_37:
                  v32 = (char)v80;
                  goto LABEL_38;
                }
                CmpReleaseShutdownRundown();
                LOBYTE(v80) = 0;
                v53 = KeWaitForSingleObject(*(PVOID *)&v23[1].WorkingSetSize, Executive, SBYTE1(v80), 1u, 0i64);
                v20 = v53;
                if ( v53 != 257 && v53 != 192 )
                {
                  CmpLockRegistry();
                  LOCK_POST_LIST();
                  v54 = KeGetCurrentIrql();
                  __writecr8(1ui64);
                  if ( v81 )
                  {
                    v55 = *(_QWORD *)&v16->PeakVirtualSize;
                    if ( *(_QWORD *)&v16->PeakVirtualSize )
                    {
                      v56 = *(_VM_COUNTERS_EX ***)&v16->PageFaultCount;
                      if ( *(_VM_COUNTERS_EX **)(v55 + 8) != v16 || *v56 != v16 )
                        goto LABEL_151;
                      *v56 = (_VM_COUNTERS_EX *)v55;
                      *(_QWORD *)(v55 + 8) = v56;
                    }
                    v57 = *(_QWORD *)&v16->WorkingSetSize;
                    v58 = *(_VM_COUNTERS_EX ***)&v16->QuotaPagedPoolUsage;
                    if ( *(_VM_COUNTERS_EX **)(v57 + 8) != (_VM_COUNTERS_EX *)&v16->WorkingSetSize
                      || *v58 != (_VM_COUNTERS_EX *)&v16->WorkingSetSize )
                    {
                      goto LABEL_151;
                    }
                    *v58 = (_VM_COUNTERS_EX *)v57;
                    *(_QWORD *)(v57 + 8) = v58;
                  }
                  v59 = *(_QWORD *)&v23->PeakVirtualSize;
                  if ( *(_QWORD *)&v23->PeakVirtualSize )
                  {
                    v60 = *(_VM_COUNTERS_EX ***)&v23->PageFaultCount;
                    if ( *(_VM_COUNTERS_EX **)(v59 + 8) != v23 || *v60 != v23 )
                      goto LABEL_151;
                    *v60 = (_VM_COUNTERS_EX *)v59;
                    *(_QWORD *)(v59 + 8) = v60;
                  }
                  v61 = *(_QWORD *)&v23->WorkingSetSize;
                  v62 = *(_VM_COUNTERS_EX ***)&v23->QuotaPagedPoolUsage;
                  if ( *(_VM_COUNTERS_EX **)(v61 + 8) == (_VM_COUNTERS_EX *)&v23->WorkingSetSize
                    && *v62 == (_VM_COUNTERS_EX *)&v23->WorkingSetSize )
                  {
                    *v62 = (_VM_COUNTERS_EX *)v61;
                    *(_QWORD *)(v61 + 8) = v62;
                    __writecr8(v54);
                    UNLOCK_POST_LIST();
                    CmpUnlockRegistry();
                    v20 = *(_DWORD *)(*(_QWORD *)&v23[1].WorkingSetSize + 24i64);
                    v63 = *(_QWORD *)ApcMode;
                    **(_DWORD **)ApcMode = v20;
                    if ( BYTE4(v80) )
                      *(_DWORD *)(v63 + 4) = 0;
                    else
                      *(_QWORD *)(v63 + 8) = 0i64;
                    v32 = 0;
                    if ( v81 )
                      CmpFreePostBlock(v16);
                    CmpFreePostBlock(v23);
LABEL_38:
                    HalPutDmaAdapter((PADAPTER_OBJECT)KeyBody);
                    if ( !v32 )
                      return v20;
                    goto LABEL_39;
                  }
LABEL_151:
                  __fastfail(3u);
                }
                CmpLockRegistry();
                LOCK_POST_LIST();
                v64 = KeGetCurrentIrql();
                __writecr8(1ui64);
                if ( v81 )
                {
                  v65 = *(_QWORD *)&v16->PeakVirtualSize;
                  if ( *(_QWORD *)&v16->PeakVirtualSize )
                  {
                    v66 = *(_VM_COUNTERS_EX ***)&v16->PageFaultCount;
                    if ( *(_VM_COUNTERS_EX **)(v65 + 8) != v16 || *v66 != v16 )
                      goto LABEL_151;
                    *v66 = (_VM_COUNTERS_EX *)v65;
                    *(_QWORD *)(v65 + 8) = v66;
                  }
                  v67 = *(_QWORD *)&v16->WorkingSetSize;
                  v68 = *(_VM_COUNTERS_EX ***)&v16->QuotaPagedPoolUsage;
                  if ( *(_VM_COUNTERS_EX **)(v67 + 8) != (_VM_COUNTERS_EX *)&v16->WorkingSetSize
                    || *v68 != (_VM_COUNTERS_EX *)&v16->WorkingSetSize )
                  {
                    goto LABEL_151;
                  }
                  *v68 = (_VM_COUNTERS_EX *)v67;
                  *(_QWORD *)(v67 + 8) = v68;
                }
                v69 = *(_QWORD *)&v23->PeakVirtualSize;
                if ( *(_QWORD *)&v23->PeakVirtualSize )
                {
                  v70 = *(_VM_COUNTERS_EX ***)&v23->PageFaultCount;
                  if ( *(_VM_COUNTERS_EX **)(v69 + 8) != v23 || *v70 != v23 )
                    goto LABEL_151;
                  *v70 = (_VM_COUNTERS_EX *)v69;
                  *(_QWORD *)(v69 + 8) = v70;
                }
                v71 = *(_QWORD *)&v23->WorkingSetSize;
                v72 = *(_VM_COUNTERS_EX ***)&v23->QuotaPagedPoolUsage;
                if ( *(_VM_COUNTERS_EX **)(v71 + 8) != (_VM_COUNTERS_EX *)&v23->WorkingSetSize
                  || *v72 != (_VM_COUNTERS_EX *)&v23->WorkingSetSize )
                {
                  goto LABEL_151;
                }
                *v72 = (_VM_COUNTERS_EX *)v71;
                *(_QWORD *)(v71 + 8) = v72;
                __writecr8(v64);
                UNLOCK_POST_LIST();
                CmpUnlockRegistry();
                if ( !v81 )
                  goto LABEL_93;
                goto LABEL_92;
              }
              CmUnlockHive((CMHIVE *)RundownRoutine);
            }
            v30 = (CMHIVE *)(*p_KeyControlBlock)->KeyHash.KeyHive;
            goto LABEL_31;
          }
          UNLOCK_POST_LIST();
          if ( v84 != 1 )
          {
            if ( v84 != 2 )
            {
              CmUnlockHive((CMHIVE *)(*p_KeyControlBlock)->KeyHash.KeyHive);
              v46 = (CMHIVE *)RundownRoutine;
              goto LABEL_100;
            }
            CmUnlockHive((CMHIVE *)RundownRoutine);
          }
          v46 = (CMHIVE *)(*p_KeyControlBlock)->KeyHash.KeyHive;
LABEL_100:
          CmUnlockHive(v46);
          v47 = *p_KeyControlBlock;
          if ( v15 == 1 )
            CmpUnlockTwoKcbs(v47, (_CM_KEY_CONTROL_BLOCK *)v21->AdapterObject.DmaHeader.DmaOperations);
          else
            CmpUnlockKcb((ULONG_PTR)v47);
          CmpUnlockRegistry();
          if ( NormalRoutine )
            HalPutDmaAdapter((PADAPTER_OBJECT)NormalRoutine);
          if ( v15 != 1 )
            goto LABEL_37;
          v45 = v16;
          goto LABEL_94;
        }
      }
      v44 = *p_KeyControlBlock;
      if ( v15 == 1 )
        CmpUnlockTwoKcbs(v44, (_CM_KEY_CONTROL_BLOCK *)v21->AdapterObject.DmaHeader.DmaOperations);
      else
        CmpUnlockKcb((ULONG_PTR)v44);
      CmpUnlockRegistry();
      if ( NormalRoutine )
        HalPutDmaAdapter((PADAPTER_OBJECT)NormalRoutine);
      if ( v15 == 1 )
        CmpFreePostBlock(v16);
      CmpFreePostBlock(v23);
      v20 = -1073741444;
      goto LABEL_37;
    }
    if ( !WatchTree )
      goto LABEL_10;
    LOWORD(v17) = 3;
    LODWORD(BlockType) = 3;
    if ( !v15 )
      goto LABEL_10;
  }
LABEL_83:
  CmpReleaseShutdownRundown();
  return -1073741811;
}

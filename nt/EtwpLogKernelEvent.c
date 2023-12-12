VOID __stdcall EtwpLogKernelEvent(
        _EVENT_DATA_DESCRIPTOR *EventData,
        _ETW_SILODRIVERSTATE *SiloState,
        UINT64 LoggerId,
        UINT64 DataCount,
        UINT64 HookId,
        UINT64 Flag)
{
  __int64 v6; // r15
  unsigned int v7; // er13
  unsigned int v8; // esi
  _ETW_LOGGER_HANDLE v11; // bl
  __int64 v12; // r14
  _WMI_LOGGER_CONTEXT **EtwpLoggerContext; // rax
  _WMI_LOGGER_CONTEXT *v14; // r14
  unsigned int v15; // er15
  unsigned int v16; // er10
  __m128i v17; // xmm5
  __m128i v18; // xmm4
  int v19; // er15
  __int64 v20; // r9
  __m128i v21; // xmm3
  __m128i v22; // xmm0
  __int64 v23; // r9
  __int64 v24; // rdx
  __int64 v25; // rcx
  __m128i v26; // xmm3
  __m128i v27; // xmm3
  __m128i v28; // xmm4
  __m128i v29; // xmm4
  unsigned int *p_Size; // rcx
  __int64 v31; // rdx
  unsigned int v32; // eax
  CHAR *v33; // rax
  UINT8 *v34; // rax
  UINT8 *v35; // r12
  __int64 Size; // r14
  signed __int64 *v37; // roff
  signed __int64 v38; // rax
  __int64 v39; // rdx
  signed __int64 v40; // rtt
  unsigned int v41; // edx
  __int16 v42; // r15
  int v43; // esi
  int v44; // edi
  _ETHREAD *CurrentThread; // rax
  CHAR *v46; // rax
  UINT8 *v47; // r8
  CHAR *v48; // rax
  int v49; // er8
  _ETW_PMC_SUPPORT *PmcData; // rcx
  int v51; // edx
  _ETW_LBR_SUPPORT *LbrData; // rcx
  _ETW_IPT_SUPPORT *IptData; // rcx
  UINT64 Flags; // [rsp+20h] [rbp-50h]
  UINT64 v55; // [rsp+28h] [rbp-48h]
  unsigned int count; // [rsp+30h] [rbp-40h]
  _LARGE_INTEGER TimeStamp; // [rsp+38h] [rbp-38h] BYREF
  UINT8 *dst; // [rsp+40h] [rbp-30h]
  _WMI_LOGGER_CONTEXT *LoggerContext; // [rsp+48h] [rbp-28h]
  unsigned __int64 v60; // [rsp+50h] [rbp-20h]
  _ETW_BUFFER_HANDLE BufferHandle[4]; // [rsp+58h] [rbp-18h] BYREF
  __int64 v62; // [rsp+68h] [rbp-8h]
  unsigned int v64; // [rsp+C8h] [rbp+58h]

  v64 = DataCount;
  v6 = (unsigned int)LoggerId;
  v7 = 0;
  *(_OWORD *)BufferHandle = 0i64;
  v62 = 0i64;
  v8 = DataCount;
  TimeStamp.QuadPart = 0i64;
  v11.DereferenceAndLeave = 0;
  if ( (unsigned __int8)KeAreInterruptsEnabled() && KeGetCurrentIrql() < 2u )
  {
    CurrentThread = (_ETHREAD *)KeGetCurrentThread();
    --CurrentThread->Tcb.KernelApcDisable;
    v12 = v6;
    if ( !ExAcquireRundownProtectionCacheAwareEx(SiloState->EtwpLoggerRundown[v6], 1ui64) )
    {
      KeLeaveCriticalRegion();
      return;
    }
    v11.DereferenceAndLeave = 1;
  }
  else
  {
    v12 = v6;
  }
  EtwpLoggerContext = SiloState->EtwpLoggerContext;
  v60 = 8 * v12;
  v14 = EtwpLoggerContext[v12];
  LoggerContext = v14;
  if ( ((unsigned __int8)v14 & 1) != 0 )
  {
    EtwpCloseLogger((unsigned int)v6, SiloState, v11);
    return;
  }
  if ( v14 )
  {
    count = 0;
    v15 = 0;
    v16 = 0;
    if ( v8 )
    {
      if ( v8 >= 8 )
      {
        v17 = 0i64;
        v18 = 0i64;
        v19 = 2;
        do
        {
          v20 = v16;
          v16 += 8;
          v21 = _mm_unpacklo_epi32(_mm_cvtsi32_si128(EventData[v20].Size), _mm_cvtsi32_si128(EventData[v19].Size));
          v22 = _mm_cvtsi32_si128(EventData[v19 + 4].Size);
          v23 = (unsigned int)(v19 + 5);
          v24 = (unsigned int)(v19 + 3);
          v25 = (unsigned int)(v19 + 2);
          v26 = _mm_add_epi32(
                  _mm_unpacklo_epi32(
                    v21,
                    _mm_unpacklo_epi32(
                      _mm_cvtsi32_si128(EventData[v19 - 1].Size),
                      _mm_cvtsi32_si128(EventData[v19 + 1].Size))),
                  v17);
          v19 += 8;
          v17 = v26;
          v27 = _mm_add_epi32(
                  _mm_unpacklo_epi32(
                    _mm_unpacklo_epi32(_mm_cvtsi32_si128(EventData[v25].Size), v22),
                    _mm_unpacklo_epi32(_mm_cvtsi32_si128(EventData[v24].Size), _mm_cvtsi32_si128(EventData[v23].Size))),
                  v18);
          v18 = v27;
        }
        while ( v16 < (v8 & 0xFFFFFFF8) );
        v28 = _mm_add_epi32(v27, v17);
        v29 = _mm_add_epi32(v28, _mm_srli_si128(v28, 8));
        v15 = _mm_cvtsi128_si32(_mm_add_epi32(v29, _mm_srli_si128(v29, 4)));
        count = v15;
      }
      if ( v16 < v8 )
      {
        p_Size = &EventData[v16].Size;
        v31 = v8 - v16;
        do
        {
          v15 += *p_Size;
          p_Size += 4;
          --v31;
        }
        while ( v31 );
        count = v15;
      }
    }
    if ( (Flag & 0x100) != 0 )
    {
      LODWORD(Flags) = Flag;
      if ( (Flag & 0x10000000) != 0 )
      {
        v48 = EtwpReserveTraceBuffer(v14, v15 + 24, BufferHandle, &TimeStamp, Flags);
        if ( !v48 )
          goto LABEL_34;
        *(_DWORD *)v48 = (unsigned __int8)Flag | 0xC0040000;
        *((_LARGE_INTEGER *)v48 + 2) = TimeStamp;
        *((_WORD *)v48 + 2) = v15 + 24;
        *((_WORD *)v48 + 3) = HookId;
        *((_DWORD *)v48 + 2) = KeGetCurrentThread()[1].CurrentRunTime;
        *((_DWORD *)v48 + 3) = KeGetCurrentThread()->ApcState.Process->UniqueProcessId;
        v34 = (UINT8 *)(v48 + 24);
      }
      else
      {
        dst = (UINT8 *)KeGetCurrentThread();
        v46 = EtwpReserveTraceBuffer(v14, v15 + 32, BufferHandle, &TimeStamp, Flags);
        if ( !v46 )
          goto LABEL_34;
        v47 = dst;
        *(_DWORD *)v46 = (unsigned __int8)Flag | 0xC0020000;
        *((_LARGE_INTEGER *)v46 + 2) = TimeStamp;
        *((_WORD *)v46 + 2) = v15 + 32;
        *((_WORD *)v46 + 3) = HookId;
        *((_DWORD *)v46 + 2) = *((_DWORD *)v47 + 288);
        *((_DWORD *)v46 + 3) = *((_DWORD *)v47 + 286);
        *((_DWORD *)v46 + 6) = *((_DWORD *)v47 + 163);
        *((_DWORD *)v46 + 7) = *((_DWORD *)v47 + 183);
        v34 = (UINT8 *)(v46 + 32);
      }
    }
    else
    {
      v32 = v14->Flags;
      if ( (v32 & 0xC00) == 0 )
      {
LABEL_17:
        LODWORD(Flags) = Flag;
        v33 = EtwpReserveTraceBuffer(v14, v15 + 16, BufferHandle, &TimeStamp, Flags);
        if ( !v33 )
          goto LABEL_34;
        *((_LARGE_INTEGER *)v33 + 1) = TimeStamp;
        *(_DWORD *)v33 = (unsigned __int8)Flag | 0xC0110000;
        *((_WORD *)v33 + 2) = v15 + 16;
        *((_WORD *)v33 + 3) = HookId;
        v34 = (UINT8 *)(v33 + 16);
        goto LABEL_19;
      }
      if ( (v32 & 0x400) != 0 && (_WORD)HookId == 1316 )
      {
        LODWORD(v55) = Flag;
        v34 = (UINT8 *)EtwpReserveWithPebsIndex(v14, 0x524u, v15, BufferHandle, &TimeStamp, v55);
      }
      else
      {
        if ( (v32 & 0x800) == 0 )
          goto LABEL_17;
        v49 = 0;
        if ( !v14->PmcData->HookIdCount )
          goto LABEL_17;
        while ( 1 )
        {
          PmcData = v14->PmcData;
          if ( PmcData->HookId[v49] == (_WORD)HookId )
            break;
          if ( ++v49 >= PmcData->HookIdCount )
            goto LABEL_17;
        }
        LODWORD(v55) = Flag;
        v34 = (UINT8 *)EtwpReserveWithPmcCounters(v14, HookId, v15, BufferHandle, &TimeStamp, v55);
      }
    }
LABEL_19:
    dst = v34;
    if ( v34 )
    {
      v35 = v34;
      if ( v8 )
      {
        while ( 1 )
        {
          Size = EventData->Size;
          if ( (unsigned int)Size > v15 )
            break;
          memmove(v35, (const VOID *)EventData->Ptr, Size);
          v35 += Size;
          v15 -= Size;
          ++v7;
          ++EventData;
          if ( v7 >= v64 )
          {
            v14 = LoggerContext;
            goto LABEL_24;
          }
        }
        memset(dst, 0, count);
        v14 = LoggerContext;
        EtwpUpdateEventsLostCount(LoggerContext);
      }
LABEL_24:
      if ( (v14->LoggerMode & 0x80000) != 0
        && (!(_BYTE)KdDebuggerNotPresent && !KdPitchDebugger || KdEventLoggingPresent) )
      {
        EtwpSendTraceEvent(v14, BufferHandle);
      }
      if ( v14->CallbackContext )
        EtwpInvokeEventCallback();
      v37 = *(signed __int64 **)&BufferHandle[2];
      _m_prefetchw(*(const void **)&BufferHandle[2]);
      v38 = *v37;
      v39 = *(_QWORD *)BufferHandle;
      if ( ((unsigned __int64)*v37 ^ *(_QWORD *)BufferHandle) >= 0xF )
      {
LABEL_43:
        _InterlockedDecrement((volatile signed __int32 *)(v39 + 12));
      }
      else
      {
        while ( 1 )
        {
          v40 = v38;
          v38 = _InterlockedCompareExchange64(*(volatile signed __int64 **)&BufferHandle[2], v38 + 1, v38);
          if ( v40 == v38 )
            break;
          v39 = *(_QWORD *)BufferHandle;
          if ( ((unsigned __int64)v38 ^ *(_QWORD *)BufferHandle) >= 0xF )
            goto LABEL_43;
        }
      }
      v41 = v14->Flags;
      if ( (v41 & 0x80u) != 0 )
      {
        v42 = HookId;
        if ( _bittest((const signed __int32 *)v14->HookIdMap.Buffer, HookId & 0x1FFF) )
        {
          v43 = Flag;
          EtwpStackTraceDispatcher((UINT64)v14, &TimeStamp, 0i64, (unsigned int)Flag);
          v41 = v14->Flags;
LABEL_32:
          v44 = 0;
          if ( (v41 & 0x8000) != 0 )
          {
            v51 = 0;
            if ( v14->LbrData->HookIdCount )
            {
              while ( 1 )
              {
                LbrData = v14->LbrData;
                if ( LbrData->HookId[v51] == v42 )
                  break;
                if ( ++v51 >= LbrData->HookIdCount )
                  goto LABEL_33;
              }
              EtwpTraceLastBranchRecord(&v14->LoggerId, &TimeStamp, 0i64, v43);
            }
          }
LABEL_33:
          if ( (v14->Flags & 0x4000000) != 0 && v14->IptData->HookIdCount )
          {
            while ( 1 )
            {
              IptData = v14->IptData;
              if ( IptData->HookId[v44] == v42 )
                break;
              if ( ++v44 >= IptData->HookIdCount )
                goto LABEL_34;
            }
            EtwpTraceProcessorTrace((PVOID *)v14, (UINT64)&TimeStamp);
          }
          goto LABEL_34;
        }
      }
      else
      {
        v42 = HookId;
      }
      v43 = Flag;
      goto LABEL_32;
    }
LABEL_34:
    if ( v11.DereferenceAndLeave )
    {
      ExReleaseRundownProtectionCacheAwareEx(SiloState->EtwpLoggerRundown[v60 / 8], 1ui64);
      KeLeaveCriticalRegionThread(KeGetCurrentThread());
    }
  }
}

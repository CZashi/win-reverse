VOID __stdcall PopTransitionToSleep(VOID *Context)
{
  POWER_STATE_HANDLER_TYPE v1; // esi
  NTSTATUS v3; // eax
  UINT8 v4; // cl
  char v5; // r14
  CHAR v6; // r15
  int v7; // eax
  NTSTATUS v8; // eax
  NTSTATUS v9; // ecx
  _MM_MIRROR_DISPATCH MirrorDispatch[4]; // [rsp+30h] [rbp-30h] BYREF
  __int128 v11; // [rsp+40h] [rbp-20h]
  __int64 v12; // [rsp+50h] [rbp-10h]
  UINT8 LowSpace; // [rsp+90h] [rbp+30h] BYREF

  v1 = *((_DWORD *)Context + 18);
  v12 = 0i64;
  LowSpace = 0;
  *(_OWORD *)MirrorDispatch = 0i64;
  v11 = 0i64;
  *(_QWORD *)&qword_140C23510 = KeGetCurrentThread();
  if ( v1 == PowerStateSleeping4 || v1 == PowerStateSleeping4Firmware )
  {
    if ( (PopSimulateHiberBugcheck & 0x20) != 0 )
    {
      KeSetEvent((PRKEVENT)Context, 0, 1u);
      KeWaitForSingleObject((char *)Context + 24, Executive, 0, 0, 0i64);
      v9 = 0;
      goto LABEL_15;
    }
    v3 = PopEnlargeHiberFile(&LowSpace);
    v4 = LowSpace;
    LODWORD(v12) = 16;
    *(_QWORD *)MirrorDispatch = xHalPciEarlyRestore;
    if ( v3 < 0 )
      v4 = 1;
    *((_QWORD *)&v11 + 1) = 0i64;
    v5 = 0;
    *(_QWORD *)&MirrorDispatch[2] = PopEndMirroring;
    v6 = 0;
    *(_QWORD *)&v11 = PopMirrorPhysicalMemory;
    if ( v4 )
    {
      MmEmptyAllWorkingSets();
      v6 = 1;
      v7 = v12 | 1;
    }
    else if ( (Flags & 0x20) != 0 && PopEnableMinimalHiberFile || PopForceMinimalHiberFile )
    {
      MmEmptyAllWorkingSets();
      v6 = 1;
      v7 = v12 | 4;
    }
    else
    {
      if ( v1 == PowerStateSleeping4Firmware )
      {
        MmTrimFilePagesFromWorkingSets();
        v7 = v12 | 1;
        goto LABEL_11;
      }
      v7 = 20;
    }
    v5 = 1;
LABEL_11:
    LODWORD(v12) = v7;
    byte_140C2411C = v5;
    byte_140C2411D = v6;
    dword_140C24118 = v7;
    PopDiagTraceEventNoPayload(&POP_ETW_EVENT_FLUSHALLPAGES);
    if ( v5 )
      MmFlushAllPagesEx(v6);
    PopDiagTraceEventNoPayload(&POP_ETW_EVENT_FLUSHALLPAGES_END);
    PopHibernatePowerStateHandlerType = v1;
    PopSleeperHandoff = (PRKEVENT)Context;
    v8 = MmDuplicateMemory(MirrorDispatch);
    PopSleeperHandoff = 0i64;
    PopHibernatePowerStateHandlerType = PowerStateMaximum;
    goto LABEL_14;
  }
  KeSetEvent((PRKEVENT)Context, 0, 1u);
  KeWaitForSingleObject((char *)Context + 24, Executive, 0, 0, 0i64);
  v8 = PopInvokeSystemStateHandler(v1, *(_POP_HIBER_CONTEXT **)&HiberContext);
LABEL_14:
  v9 = v8;
LABEL_15:
  HiberPerf.SleeperThreadEnd = __rdtsc();
  *((_DWORD *)Context + 19) = v9;
  KeSetEvent((PRKEVENT)Context + 2, 0, 0);
}

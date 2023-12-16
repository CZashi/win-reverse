__int64 ACPIInterruptDispatchEventDpc()
{
  char v0; // r14
  size_t v1; // r15
  __int64 v2; // rdx
  size_t v3; // r8
  char v4; // al
  _BYTE *v5; // rcx
  unsigned int i; // ebx
  unsigned __int8 v7; // r10
  unsigned __int8 v8; // r13
  void *v9; // rcx
  unsigned int v10; // edi
  __int64 v11; // rbx
  unsigned __int8 v12; // si
  unsigned int v14; // r8d
  int v15; // edx
  unsigned __int8 v16; // cl
  unsigned int v17; // edi
  int v18; // eax
  unsigned int v19; // r12d
  int v20; // r12d
  unsigned int v21; // edx
  __int64 v22; // rcx
  unsigned __int8 v23; // [rsp+38h] [rbp-69h]
  unsigned int v24; // [rsp+3Ch] [rbp-65h]
  __int128 v25[6]; // [rsp+48h] [rbp-59h] BYREF
  char Dst[32]; // [rsp+A8h] [rbp+7h] BYREF

  v0 = 0;
  HIBYTE(v24) = 0;
  v1 = *((unsigned __int16 *)AcpiInformation + 51);
  KeAcquireSpinLockAtDpcLevel(&GpeTableLock);
  AcpiGpeDpcScheduled = 0;
  if ( !AcpiGpeDpcRunning )
  {
    AcpiGpeDpcRunning = 1;
    memset(v25, 0, 32);
    do
    {
      AcpiGpeWorkDone = 0;
      if ( (_DWORD)v1 )
      {
        v2 = 0i64;
        v3 = v1;
        do
        {
          v4 = *((_BYTE *)GpeRunMethod + v2);
          *((_BYTE *)GpeRunMethod + v2) = 0;
          *((_BYTE *)&v25[4] + v2) = v4;
          *((_BYTE *)&v25[2] + v2) = *((_BYTE *)GpeIsLevel + v2);
          v5 = GpeComplete;
          *((_BYTE *)v25 + v2) |= *((_BYTE *)GpeComplete + v2);
          v5[v2++] = 0;
          --v3;
        }
        while ( v3 );
      }
      memmove(Dst, GpeWakeEnable, v1);
      KeReleaseSpinLockFromDpcLevel(&GpeTableLock);
      for ( i = 0; i < (unsigned int)v1; v0 = 0 )
      {
        v7 = *((_BYTE *)&v25[2] + i);
        v8 = *((_BYTE *)&v25[4] + i);
        v23 = v7;
        while ( v8 )
        {
          v14 = *((unsigned __int16 *)AcpiInformation + 43);
          v15 = FirstSetLeftBit[v8];
          v16 = FirstSetLeftBit[v8];
          v17 = 1 << v16;
          v8 &= ~(unsigned __int8)(1 << v16);
          if ( i >= v14 + *((unsigned __int16 *)AcpiInformation + 49) )
          {
            KeBugCheckEx(165i64, 23i64, v15 + 8 * i);
            __debugbreak();
            JUMPOUT(0x1C0043330i64);
          }
          if ( i >= v14 )
            v18 = *((unsigned __int16 *)AcpiInformation + 50) + 8 * (i - v14);
          else
            v18 = 8 * i;
          v19 = v18 + v15;
          if ( ((unsigned __int8)v17 & *((_BYTE *)GpeHandlerType + i)) != 0 )
          {
            LOBYTE(v24) = i;
            BYTE1(v24) = 1 << v16;
            BYTE2(v24) = v7;
            byte_1C0081367 = ((unsigned __int8)v17 & v7) != 0 ? 76 : 69;
            byte_1C0081368 = HexDigit[(unsigned __int64)v19 >> 4];
            byte_1C0081369 = HexDigit[v19 & 0xF];
            if ( (int)AMLIGetNameSpaceObject(&unk_1C0081360) >= 0 )
            {
              v20 = AMLIAsyncEvalObject(0i64, 0i64, 0, 0i64, ACPIInterruptEventCompletion, v24);
              AMLIDereferenceHandleEx(0i64);
              if ( v20 < 0 )
              {
                KeAcquireSpinLockAtDpcLevel(&GpeTableLock);
                *((_BYTE *)GpeRunMethod + i) |= v17;
                if ( !AcpiGpeDpcScheduled )
                {
                  AcpiGpeDpcScheduled = 1;
                  KeSetTimer(&AcpiGpeTimer, -20000000i64, &AcpiGpeDpc);
                }
                KeReleaseSpinLockFromDpcLevel(&GpeTableLock);
              }
              else if ( v20 != 259 )
              {
                v0 |= v17;
              }
            }
          }
          else
          {
            if ( ((unsigned __int8)v17 & (unsigned __int8)Dst[i]) != 0 )
            {
              OSNotifyDeviceWakeByGPEEvent(v19, i, v17);
            }
            else
            {
              v21 = *(unsigned __int8 *)((unsigned int)ACPIGpeIndexToByteIndex(v19) + GpeMap);
              if ( v21 >= GpeVectorTableSize )
                goto LABEL_26;
              _mm_lfence();
              v22 = *((_QWORD *)GpeVectorTable + 2 * v21 + 1);
              if ( v22 )
              {
                (*(void (__fastcall **)(__int64, _QWORD))(v22 + 8))(v22, *(_QWORD *)(v22 + 16));
              }
              else if ( WPP_RECORDER_INITIALIZED != &WPP_RECORDER_INITIALIZED )
              {
                LOBYTE(v21) = 2;
                WPP_RECORDER_SF_D(
                  *((_QWORD *)WPP_GLOBAL_Control + 8),
                  v21,
                  22,
                  10,
                  (__int64)&WPP_f0951bc89be93806c5bfad28f4f33887_Traceguids,
                  v19);
              }
            }
            v0 |= v17;
          }
LABEL_26:
          v7 = v23;
        }
        *((_BYTE *)v25 + i++) |= v0;
      }
      KeAcquireSpinLockAtDpcLevel(&GpeTableLock);
    }
    while ( AcpiGpeWorkDone );
    v10 = 0;
    if ( (_DWORD)v1 )
    {
      v11 = 0i64;
      do
      {
        v12 = *((_BYTE *)v25 + v11);
        if ( (v12 & *((_BYTE *)&v25[2] + v11)) != 0 )
          ACPIWriteGpeStatusRegister(v10);
        v9 = GpePending;
        ++v10;
        *((_BYTE *)GpePending + v11) &= ~v12;
        *((_BYTE *)GpeCurEnable + v11) |= v12 & (*((_BYTE *)GpeWakeEnable + v11) | *((_BYTE *)GpeEnable + v11) & ~*((_BYTE *)GpeWakeHandler + v11));
        ++v11;
      }
      while ( v10 < (unsigned int)v1 );
    }
    LOBYTE(v9) = 1;
    AcpiGpeDpcRunning = 0;
    ACPIGpeEnableDisableEvents(v9);
  }
  return KeReleaseSpinLockFromDpcLevel(&GpeTableLock);
}

__int64 (__fastcall *HcpHypercallDispatchTable[3])() = { &HcpHvAcceptGpaPages, NULL, (__int64 (__fastcall *)())0x4000000000i64 };

_QWORD *__fastcall HcpDispatchHypercall(_QWORD *result, __int64 a2)
{
  _QWORD *v2; // x20
  __int64 v3; // x19
  __int64 v5; // x8
  __int64 v6; // x8
  __int64 v7; // x6
  __int64 v8; // x9
  __int64 v9; // x8
  int v10; // w8
  __int64 v11; // x10
  __int64 v12; // x9
  __int64 v13; // x11
  __int64 v14; // x8
  __int64 v15; // x2
  unsigned __int16 v16; // w0
  __int64 v17; // x4
  __int64 v18; // [xsp+10h] [xbp+10h] BYREF
  __int64 v19[3]; // [xsp+18h] [xbp+18h] BYREF

  LODWORD(v18) = 0;
  v2 = result;
  v3 = result[142];
  v5 = *(_QWORD *)(*((_QWORD *)NtCurrentTeb() + 4180) + 336i64);
  v19[0] = v3;
  v6 = *(_QWORD *)(result[44] + 2376i64 * *(unsigned __int8 *)(v5 + 20) + 4056);
  if ( !v6 )
  {
    if ( (unsigned int)(v3 & 0x7FFF) - 80 <= 1
      && (WORD2(v3) & 0xFFF) == 1
      && (v3 & 0x10000) != 0
      && result[144] == -1i64
      && (!(unsigned int)result[145] || result[145] == 4294967294i64) )
    {
      result = (_QWORD *)result[146];
      if ( (v3 & 0x7FFF) == 81 )
      {
        if ( (_DWORD)result == 589826 && (*(_QWORD *)(*((_QWORD *)NtCurrentTeb() + 4181) + 216i64) & 0x20) != 0 )
        {
          *(_QWORD *)(*(_QWORD *)(*((_QWORD *)NtCurrentTeb() + 4180) + 352i64)
                    + 2376i64 * *(unsigned __int8 *)(*(_QWORD *)(*((_QWORD *)NtCurrentTeb() + 4180) + 336i64) + 20i64)
                    + 4056) = v2[148];
LABEL_19:
          v18 = 0i64;
          v7 = *(unsigned __int8 *)(a2 + 8);
          v8 = v2[208];
          HIDWORD(v18) = 1;
          v2[142] = v18;
          v9 = v7 + v8;
LABEL_20:
          v2[208] = v9;
          goto LABEL_43;
        }
        goto LABEL_30;
      }
      if ( (_DWORD)result == 256 )
      {
LABEL_18:
        result = (_QWORD *)VpGetVirtualRegister128((__int64)result, v2 + 148);
        goto LABEL_19;
      }
      if ( (int)result > 511 )
      {
        if ( (int)result > 515 )
        {
          if ( (_DWORD)result == 589826 && (*(_QWORD *)(*((_QWORD *)NtCurrentTeb() + 4181) + 216i64) & 0x20) != 0 )
          {
            v2[148] = 0i64;
            goto LABEL_19;
          }
          goto LABEL_30;
        }
        goto LABEL_18;
      }
    }
LABEL_30:
    *(_DWORD *)(a2 + 20) = 0x2000000;
    *(_QWORD *)(a2 + 24) = 0i64;
    *(_DWORD *)a2 = 11;
    goto LABEL_43;
  }
  if ( (v3 & 0x8000) != 0 )
  {
    v18 = 2i64;
    v10 = 1;
LABEL_23:
    HIDWORD(v18) = v10;
    v11 = *(unsigned __int8 *)(a2 + 8);
    v12 = result[208];
    result[142] = v18;
    v9 = v11 + v12;
    goto LABEL_20;
  }
  if ( ((unsigned __int16)v3 & 0x7FFFu) >= 0xDE
    || (v3 & 0x7C000000) != 0
    || (v3 & 0xF00000000000i64) != 0
    || HIDWORD(v3) >= 0x10000000 )
  {
    v6 = 0i64;
  }
  if ( !v6 )
    goto LABEL_30;
  if ( (v19[0] & 0x8000) != 0 )
  {
    ++*(_QWORD *)(result[33] + 4608i64);
    if ( (*(_QWORD *)(result[44] + 216i64) & 0x10000000000000i64) == 0 )
    {
      v18 = 2i64;
      v10 = 0;
      goto LABEL_23;
    }
    result = (_QWORD *)ImSendHypercallInterceptMessage((__int64)result);
  }
  else
  {
    v13 = *((unsigned __int16 *)&unk_F80000443014 + 12 * (v3 & 0x7FFF)) + 512i64;
    ++*(_QWORD *)(result[33] + 8 * v13);
    if ( (*((_WORD *)&unk_F8000044300A + 12 * (v3 & 0x7FFF)) & 4) != 0 )
    {
      v14 = result[83];
      v18 = 0i64;
      v15 = *(_QWORD *)(v14 + 48);
      LODWORD(v18) = 0x7FFF;
      if ( (v3 & 0xFFFFFFFFFFFF8000ui64) == 0 )
      {
        result = (_QWORD *)((__int64 (__fastcall *)(_QWORD *, __int64, __int64))HcpHypercallDispatchTable[3 * (v3 & 0x7FFF)])(
                             result,
                             1i64,
                             v15);
        if ( !(_WORD)result )
          goto LABEL_43;
      }
      goto LABEL_30;
    }
    v19[1] = 0i64;
    v19[0] = (__int64)result;
    if ( (v3 & 0x10000) != 0 )
      v16 = HplDispatchFastHypercall((__int64)(result + 142), a2, v3, 24 * (v3 & 0x7FFF) + 0xF80000443000i64, &v18);
    else
      v16 = HplDispatchSlowHypercall(
              (__int64)result,
              (__int64)(result + 142),
              (__int64)v19,
              v3,
              (unsigned __int16 *)(24 * (v3 & 0x7FFF) + 0xF80000443000i64),
              &v18);
    result = (_QWORD *)HcpHandleHypercallCompletion(v3, a2, v16, v18, v17, v2 + 142);
  }
LABEL_43:
  if ( *(_BYTE *)(a2 + 8) )
    *(_QWORD *)(v2[83] + 576i64) = v2[208];
  return result;
}

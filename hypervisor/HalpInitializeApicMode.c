__int64 __fastcall HalpInitializeApicMode(__int64 a1)
{
  __int64 v1; // x23
  char *AcpiTable; // x0
  unsigned __int8 *v3; // x10
  unsigned __int64 v4; // x14
  __int64 v5; // x9
  unsigned __int8 *v6; // x11
  int v7; // w8
  unsigned int v8; // w15
  unsigned int v9; // w7
  unsigned int v10; // w12
  __int64 v11; // x13
  __int64 v12; // x19
  __int64 Memory; // x0
  __int64 result; // x0
  int v15; // w0
  int v16; // w24
  int v17; // w19
  char *v18; // x0
  bool v19; // w8
  char *v20; // x0
  __int64 v21; // x2
  __int64 v22; // x3
  __int64 v23; // x20
  unsigned __int64 v24; // x0
  unsigned __int8 *v25; // x22
  unsigned __int64 v26; // x21
  __int64 (__fastcall *v27)(__int64, unsigned int, __int64, __int64, __int64, unsigned int *); // x11
  __int64 (__fastcall *v28)(__int64, int); // x13
  __int64 (__fastcall *v29)(__int64, __int64, __int64); // x12
  __int64 (__fastcall *v30)(__int64, int); // x15
  __int64 (__fastcall *v31)(__int64, int *, _DWORD *); // x14
  __int64 (__fastcall *v32)(__int64, __int64, int *); // x6
  __int64 (__fastcall *v33)(__int64, __int64, __int64); // x7
  __int64 (__fastcall *v34)(__int64, _DWORD *, _DWORD *, char); // x4
  __int64 (__fastcall *v35)(__int64, int); // x5
  __int64 (__fastcall *v36)(__int64, int); // x2
  __int64 (__fastcall *v37)(__int64, unsigned int *, __int64, _BYTE *); // x3
  __int64 v38; // x9
  unsigned __int8 *v39; // x10
  int v40; // w8
  __int64 *v42; // x8
  int v43; // w27
  int v44; // w25
  unsigned __int64 v45; // x26
  int v46; // w8
  __int64 v47; // x1
  unsigned __int64 *v48; // x8
  __int64 v49; // x20
  __int64 v50; // x9
  __int64 v51; // x10
  __int64 v52; // x9
  __int64 v53; // x0
  int v54; // w8
  bool v55; // zf
  int v56; // w8
  unsigned int v57; // w1
  int v58; // w11
  __int64 *(__fastcall *v59)(__int64 *, unsigned int); // x10
  __int64 v60; // x8
  unsigned __int8 v61; // w9
  unsigned __int64 v62; // x10
  unsigned int v63; // w8
  int v64; // w8
  unsigned __int64 *v65; // [xsp+10h] [xbp+10h] BYREF
  __int64 (__fastcall *v66)(__int64, unsigned int, __int64, __int64, __int64, unsigned int *); // [xsp+18h] [xbp+18h]
  __int64 (__fastcall *v67)(__int64, __int64, __int64); // [xsp+20h] [xbp+20h]
  __int64 (__fastcall *v68)(__int64, int); // [xsp+28h] [xbp+28h]
  __int64 (__fastcall *v69)(__int64, int *, _DWORD *); // [xsp+30h] [xbp+30h]
  __int64 (__fastcall *v70)(__int64, int); // [xsp+38h] [xbp+38h]
  __int64 (__fastcall *v71)(__int64, __int64, __int64); // [xsp+40h] [xbp+40h]
  __int64 (__fastcall *v72)(__int64, __int64, int *); // [xsp+48h] [xbp+48h]
  __int64 (__fastcall *v73)(__int64, int); // [xsp+50h] [xbp+50h]
  __int64 (__fastcall *v74)(__int64, _DWORD *, _DWORD *, char); // [xsp+58h] [xbp+58h]
  __int64 (__fastcall *v75)(__int64, unsigned int *, __int64, _BYTE *); // [xsp+60h] [xbp+60h]
  __int64 (__fastcall *v76)(__int64, int); // [xsp+68h] [xbp+68h]
  int v77[2]; // [xsp+70h] [xbp+70h] BYREF
  __int64 (__fastcall *v78)(__int64, unsigned int, __int64, __int64, __int64, unsigned int *); // [xsp+78h] [xbp+78h]
  __int64 (__fastcall *v79)(__int64, __int64, __int64); // [xsp+80h] [xbp+80h]
  __int64 (__fastcall *v80)(__int64, int); // [xsp+88h] [xbp+88h]
  __int64 v81; // [xsp+90h] [xbp+90h]
  __int64 v82; // [xsp+98h] [xbp+98h]
  __int64 v83; // [xsp+A8h] [xbp+A8h]
  __int64 (__fastcall *v84)(__int64, int *, _DWORD *); // [xsp+B0h] [xbp+B0h]
  __int64 (__fastcall *v85)(__int64, int); // [xsp+B8h] [xbp+B8h]
  __int64 v86; // [xsp+C0h] [xbp+C0h]
  __int64 (__fastcall *v87)(__int64, __int64, __int64); // [xsp+C8h] [xbp+C8h]
  __int64 (__fastcall *v88)(__int64, __int64, int *); // [xsp+D0h] [xbp+D0h]
  __int64 (__fastcall *v89)(__int64, int); // [xsp+D8h] [xbp+D8h]
  __int64 v90; // [xsp+E0h] [xbp+E0h]
  __int64 (__fastcall *v91)(__int64, _DWORD *, _DWORD *, char); // [xsp+E8h] [xbp+E8h]
  __int64 v92; // [xsp+F0h] [xbp+F0h]
  __int64 v93; // [xsp+F8h] [xbp+F8h]
  __int64 (__fastcall *v94)(__int64, unsigned int *, __int64, _BYTE *); // [xsp+110h] [xbp+110h]
  __int64 (__fastcall *v95)(__int64, int); // [xsp+118h] [xbp+118h]
  int v96; // [xsp+128h] [xbp+128h]
  int v97; // [xsp+12Ch] [xbp+12Ch]
  int v98; // [xsp+130h] [xbp+130h]
  int v99; // [xsp+134h] [xbp+134h]
  int v100; // [xsp+138h] [xbp+138h]
  __int64 v101; // [xsp+13Ch] [xbp+13Ch] BYREF
  int v102; // [xsp+144h] [xbp+144h]

  v1 = a1 + *(unsigned int *)(a1 + 9772);
  AcpiTable = HalGetAcpiTable(1128878145);
  if ( AcpiTable )
  {
    v3 = (unsigned __int8 *)(AcpiTable + 44);
    v4 = (unsigned __int64)&AcpiTable[*((unsigned int *)AcpiTable + 1)];
    if ( (unsigned __int64)(AcpiTable + 46) <= v4 )
    {
      do
      {
        v5 = v3[1];
        if ( (unsigned int)v5 < 2 || (unsigned __int64)&v3[v5] > v4 )
          break;
        v6 = v3;
        v7 = *v3;
        v3 += v5;
        if ( v7 == 11 && (unsigned int)v5 >= 0x28 )
        {
          v8 = *((_DWORD *)v6 + 1);
          if ( v8 < 8 )
            HalpLUMPIDRMap[v8] = *(_QWORD *)(v6 + 68);
          v9 = *(_DWORD *)(v1 + 32);
          v10 = 0;
          if ( v9 )
          {
            while ( 1 )
            {
              v11 = v1 + 88i64 * v10;
              if ( v8 == *(_DWORD *)(v11 + 40) )
                break;
              if ( ++v10 >= v9 )
                goto LABEL_14;
            }
            *((_QWORD *)v6 + 6) = *(_QWORD *)(v11 + 88);
            *((_QWORD *)v6 + 5) = *(_QWORD *)(v11 + 80);
            *((_DWORD *)v6 + 14) = *(_DWORD *)(v11 + 96);
          }
        }
LABEL_14:
        ;
      }
      while ( (unsigned __int64)(v3 + 2) <= v4 );
    }
  }
  v12 = (unsigned int)(56 * KeNumberProcessorsAvailable);
  Memory = HalpMmAllocateMemory(56 * KeNumberProcessorsAvailable);
  HalpLocalUnitInfo = Memory;
  if ( !Memory )
    return 11i64;
  memset(Memory, 0, v12);
  HalpItsList = (__int64)&HalpItsList;
  qword_F800004286E8 = (__int64)&HalpItsList;
  v15 = HalpGic3Discover();
  if ( !(unsigned __int16)ExtNtToHvStatus(v15) )
    goto LABEL_52;
  v16 = 0;
  v17 = 0;
  v18 = HalGetAcpiTable(1346584902);
  if ( v18 )
    v19 = (unsigned int)memcmp((unsigned __int8 *)v18 + 10, "BOCHS ", 6i64) == 0;
  else
    v19 = 0;
  HalpEmulatedGic = v19;
  v20 = HalGetAcpiTable(1128878145);
  v23 = (__int64)v20;
  if ( v20 )
  {
    v24 = *((unsigned int *)v20 + 9);
    HalpGicLocalUnitPhysicalAddress = v24;
    if ( !v24 || (v16 = 1, v17 = ExtEnvRegisterPermanentAddressUsage(v24, 0x1000u, v21, v22), (v17 & 0x80000000) == 0) )
    {
      v25 = (unsigned __int8 *)(v23 + 44);
      v17 = -1073741275;
      v26 = v23 + *(unsigned int *)(v23 + 4);
      if ( v23 + 46 <= v26 )
      {
        v27 = HalpGicInitializeLocalUnit;
        v66 = HalpGicInitializeLocalUnit;
        v28 = HalpGicSetPriority;
        v29 = HalpGicInitializeIoUnit;
        v67 = HalpGicInitializeIoUnit;
        v68 = HalpGicSetPriority;
        v30 = HalpGicWriteEndOfInterrupt;
        v31 = HalpGicAcceptAndGetSource;
        v69 = HalpGicAcceptAndGetSource;
        v70 = HalpGicWriteEndOfInterrupt;
        v32 = HalpGicRequestInterrupt;
        v33 = HalpGicSetLineState;
        v71 = HalpGicSetLineState;
        v72 = HalpGicRequestInterrupt;
        v34 = HalpGicConvertId;
        v35 = HalpGicStartProcessor;
        v73 = HalpGicStartProcessor;
        v74 = HalpGicConvertId;
        v36 = HalpGicDeactivateInterrupt;
        v37 = HalpGicQueryAndGetSource;
        v75 = HalpGicQueryAndGetSource;
        v76 = HalpGicDeactivateInterrupt;
        do
        {
          v38 = v25[1];
          if ( (unsigned int)v38 < 2 || (unsigned __int64)&v25[v38] > v26 )
            break;
          v39 = v25;
          v40 = *v25;
          v25 += v38;
          if ( v40 == 12 && (unsigned int)v38 >= 0x18 )
          {
            v42 = (__int64 *)v77;
            v43 = *((_DWORD *)v39 + 4);
            v44 = *((_DWORD *)v39 + 1);
            v45 = *((_QWORD *)v39 + 1);
            do
            {
              *v42 = 0i64;
              v42[1] = 0i64;
              v42 += 2;
            }
            while ( v42 != (__int64 *)((char *)&v101 + 4) );
            *v42 = 0i64;
            v77[0] = 1;
            v77[1] = 216;
            v46 = *(_DWORD *)(v23 + 4);
            v97 = 3;
            v98 = v44;
            v101 = 0i64;
            v83 = 0i64;
            v84 = v31;
            v96 = v46 + 120;
            v102 = 0;
            v78 = v27;
            v79 = v29;
            v80 = v28;
            v81 = 0i64;
            v99 |= 0x77u;
            v100 = 15;
            v82 = 0i64;
            v85 = v30;
            v86 = 0i64;
            v87 = v33;
            v88 = v32;
            v89 = v35;
            v90 = 0i64;
            v91 = v34;
            v92 = 0i64;
            v93 = 0i64;
            v94 = v37;
            v95 = v36;
            v17 = ExtEnvRegisterPermanentAddressUsage(v45, 0x1000u, (__int64)v36, (__int64)v37);
            if ( (v17 & 0x80000000) == 0 )
            {
              v17 = HalpInterruptRegisterController((__int64)v77, v47, &v65);
              if ( (v17 & 0x80000000) == 0 )
              {
                v48 = v65;
                *v65 = v45;
                *((_DWORD *)v48 + 22) = v44;
                *((_DWORD *)v48 + 27) = v43;
                *((_DWORD *)v48 + 24) = 3;
                v48[14] = (unsigned __int64)(v48 + 15);
                memmove((__int64)(v48 + 15), v23, *(unsigned int *)(v23 + 4));
              }
            }
            if ( (v17 & 0x80000000) != 0 )
              goto LABEL_51;
            v27 = v66;
            v29 = v67;
            v28 = v68;
            v31 = v69;
            v30 = v70;
            v33 = v71;
            v32 = v72;
            v35 = v73;
            v34 = v74;
            v37 = v75;
            v36 = v76;
          }
        }
        while ( (unsigned __int64)(v25 + 2) <= v26 );
        if ( (v17 & 0x80000000) == 0 )
        {
          v49 = v23 + 44;
          do
          {
            v50 = *(unsigned __int8 *)(v49 + 1);
            if ( (unsigned int)v50 < 2 )
              break;
            if ( v50 + v49 > v26 )
              break;
            v51 = v49;
            v49 += v50;
            if ( !v16 && *(_BYTE *)v51 == 11 && (unsigned int)v50 >= 0x28 && (*(_DWORD *)(v51 + 12) & 1) != 0 )
            {
              v17 = ExtEnvRegisterPermanentAddressUsage(*(_QWORD *)(v51 + 32), 0x1000u, (__int64)v36, (__int64)v37);
              if ( (v17 & 0x80000000) != 0 )
                break;
            }
          }
          while ( v49 + 2 <= v26 );
        }
      }
    }
  }
LABEL_51:
  result = (unsigned __int16)ExtNtToHvStatus(v17);
  if ( !(_WORD)result )
  {
LABEL_52:
    v52 = HalpInterruptController;
    *(_DWORD *)(HalpInterruptController + 20) = KeNumberProcessorsAvailable;
    v53 = *(_QWORD *)(v1 + 16);
    HalpGicDPhysicalAddress = v53;
    if ( v53 )
    {
      v54 = *(_DWORD *)(v52 + 16);
      if ( v54 == 2 )
      {
        v57 = 4096;
      }
      else
      {
        v55 = v54 == 3;
        v56 = 0x40000;
        v57 = 0x10000;
        if ( v55 )
          v56 = 0x20000;
        HalpRedistMapSize = v56;
      }
      result = (unsigned __int16)HalMapIoSpaceWithStatus(v53, v57, 0, &HalGicd);
      if ( !(_WORD)result )
      {
        HalRequestSelfIpi = (__int64 (__fastcall *)(_QWORD))sub_F80000019240;
        v58 = *(_DWORD *)(HalpInterruptController + 16);
        v59 = v58 == 2 ? sub_F800000192C8 : (__int64 *(__fastcall *)(__int64 *, unsigned int))sub_F80000019320;
        HalRequestMulticastIpi = (__int64 (__fastcall *)(_QWORD, _QWORD))v59;
        if ( v58 == 2 || (result = (unsigned __int16)HalpMapRedistributors(), !(_WORD)result) )
        {
          if ( *(_DWORD *)(HalpInterruptController + 16) == 2 )
          {
            v60 = HalGicd;
            __dsb(0xFu);
            v61 = *(_BYTE *)(v60 + 2048);
            v62 = v61;
            if ( v61 )
              v63 = v61;
            else
              v63 = 1;
            LODWORD(v62) = __clz(__rbit(v63));
          }
          else
          {
            v62 = _ReadStatusReg(ARM64_SYSREG(3, 0, 0, 0, 5)) & 0xFF00FFFFFFi64;
          }
          HalpBspHwId = v62;
          result = 0i64;
          if ( *(_DWORD *)(HalpInterruptController + 16) == 2 )
            v64 = 1023;
          else
            v64 = 0xFFFFF;
          HalInterruptIdMask = v64;
        }
      }
    }
    else
    {
      return 5i64;
    }
  }
  return result;
}

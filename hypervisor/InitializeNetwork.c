__int64 InitializeNetwork()
{
  __int64 v0; // x19
  __int64 v1; // x20
  int TargetIPAddress; // w0
  __int64 result; // x0
  __int64 v4; // x11
  int v5; // w10
  int v6; // w1
  int v7; // w21
  __int16 v8; // w9
  const __int16 *v9; // x8
  __int64 v10; // x10
  __int16 v11; // w9
  int v12; // w8
  unsigned int v13; // w22
  int v14; // w21
  __int64 v15; // x20
  __int64 v16; // x25
  __int64 v17; // x9
  int v18; // w23
  unsigned int v19; // w10
  __int16 v20; // [xsp+30h] [xbp+10h] BYREF
  __int16 v21; // [xsp+32h] [xbp+12h] BYREF
  int v22; // [xsp+34h] [xbp+14h] BYREF
  int v23; // [xsp+38h] [xbp+18h] BYREF
  __int64 v24; // [xsp+40h] [xbp+20h] BYREF
  unsigned __int8 *v25; // [xsp+48h] [xbp+28h] BYREF

  v0 = KdNetData;
  v24 = -1i64;
  v1 = *(_QWORD *)(KdNetData + 56);
  if ( *(unsigned __int16 *)(KdNetData + 1200) != 65532 )
  {
    if ( *(_BYTE *)(v1 + 314) )
    {
      if ( (*(_DWORD *)(KdNetData + 44) & 1) == 0 && !*(_DWORD *)(v1 + 256) )
      {
        TargetIPAddress = GetTargetIPAddress(KdNetData);
        if ( (TargetIPAddress & 0x80000000) != 0 && !KdNetErrorString )
        {
          KdNetErrorStatus = TargetIPAddress;
          KdNetErrorString = (__int64)L"GetTargetIPAddress failed to acquire an IP address using DHCP.";
        }
      }
    }
    result = GenerateTargetIPAddress(v0);
    if ( (result & 0x80000000) != 0 )
    {
      if ( !KdNetErrorString )
      {
        KdNetErrorStatus = result;
        KdNetErrorString = (__int64)L"GenerateTargetIPAddress failed to acquire an unused IP address.";
      }
      return result;
    }
    v4 = *(_QWORD *)(v0 + 56);
    v5 = *(_DWORD *)(v4 + 288);
    if ( !v5 )
      return result;
    v6 = *(_DWORD *)(v0 + 1168);
    v7 = *(_DWORD *)(v4 + 288);
    if ( (v6 & 0xFFFF0000) != -1442971648 && *(_DWORD *)(v1 + 780) && ((v6 ^ v5) & *(_DWORD *)(v1 + 776)) != 0 )
      v7 = *(_DWORD *)(v1 + 780);
    if ( v5 == -1 || v5 == -1442906113 )
    {
      result = 0i64;
      v8 = WORD2(v24);
      *(_DWORD *)(v4 + 304) = v24;
      *(_WORD *)(v4 + 308) = v8;
    }
    else
    {
      result = GetNodeMacAddress(v0, v6, v7, v4 + 304, 2);
    }
    if ( (result & 0x80000000) != 0 )
    {
      KdNetErrorString = (__int64)L"InitializeNetwork failed to get the MAC address of the host debugger. Check the dbgsettings hostip!";
      if ( v7 == *(_DWORD *)(v1 + 780) )
        v9 = L"InitializeNetwork failed to get the ethernet address of the router gateway.";
      else
        v9 = L"InitializeNetwork failed to get the MAC address of the host debugger. Check the dbgsettings hostip!";
      KdNetErrorString = (__int64)v9;
      if ( (*(_DWORD *)(v0 + 1168) & 0xFFFF0000) != -1442971648 )
        return result;
      v10 = *(_QWORD *)(v0 + 56);
      if ( (*(_DWORD *)(v10 + 288) & 0xFFFF0000) != -1442971648 )
        return result;
      v11 = WORD2(v24);
      *(_DWORD *)(v10 + 304) = v24;
      *(_WORD *)(v10 + 308) = v11;
    }
  }
  if ( *(unsigned __int16 *)(v0 + 1200) != 65532 )
  {
    v12 = *(_DWORD *)(v0 + 44);
    KdNetInitialConnectTime = 0;
    KdNetInitialConnectAttempts = 0;
    v13 = 2;
    v14 = 125000;
    if ( (v12 & 1) != 0 && KdNetFirstBoot )
    {
      v13 = 24;
      v14 = 1000000;
    }
    do
    {
      EnableHostReconnect(v0, 3000000);
      v15 = *(_QWORD *)(v0 + 56);
      v23 = v14;
      v16 = 0i64;
      v20 = *(_WORD *)(v15 + 252);
      if ( *(_BYTE *)(v15 + 315)
        || !*(_QWORD *)(v0 + 1176)
        && *(_DWORD *)(v0 + 1172) == 0xFFFF
        && (*(_DWORD *)(v0 + 1168) & 0xFFFF0000) == -1442971648 )
      {
        v16 = v15 + 304;
      }
      v17 = v15;
      do
      {
        v21 = *(_WORD *)(v17 + 248);
        v18 = WaitForSpecificRxUdpPacketEx(
                (unsigned __int8 *)v0,
                (__int64)&v22,
                &v25,
                (unsigned int *)&v24,
                (__int64)&v23,
                v16,
                v0 + 1152,
                v15 + 288,
                v0 + 1168,
                &v20,
                &v21);
        if ( (v18 & 0x80000000) != 0 )
          break;
        v18 = DecryptKdPacket((_QWORD *)v0, (__int64 *)&v25, (int *)&v24);
        if ( (v18 & 0x80000000) != 0 )
        {
          ++KdNetRxKdPacketsHandedOff;
          ProcessUnhandledPackets((unsigned __int8 *)v0);
        }
        ReleaseRxPacket(v0);
        v17 = *(_QWORD *)(v0 + 56);
      }
      while ( !*(_DWORD *)(v17 + 316) );
      KdNetInitialConnectTime = KdNetInitialConnectTime - v23 + v14;
      v19 = ++KdNetInitialConnectAttempts;
    }
    while ( (v18 & 0x80000000) != 0 && v19 < v13 );
  }
  return 0i64;
}

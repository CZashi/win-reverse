BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  ULONG64 *v4; // rbx
  const GUID **v5; // rdi
  const GUID *v6; // r8
  CInterfaceMonitor *v7; // rcx
  __int64 v8; // rdx
  struct ATL::_ATL_OBJMAP_ENTRY *v9; // rdx
  struct ATL::_ATL_MODULE *v10; // rcx
  int v12; // ecx
  char v13; // al
  struct _TRACE_GUID_REGISTRATION v14; // xmm0
  signed int v15; // eax
  unsigned int v16; // ebx
  CInterfaceMonitor **v17; // rcx
  ATL::CComModule *v18; // rcx
  REGHANDLE v19; // rcx
  CInterfaceMonitor *v20; // rbx
  TRACEHANDLE v21; // rcx
  struct _TRACE_GUID_REGISTRATION TraceGuidReg; // [rsp+40h] [rbp-48h] BYREF

  if ( !fdwReason )
  {
    if ( NhpDllProcessAttachSucceeded == 1 )
    {
      NatHlpShutdownTimerManagement();
      NhResetComponentMode();
      DeleteCriticalSection(&g_RegistrationProtection);
      DeleteCriticalSection(&g_NATEventsProtection);
      AlgCleanupModule();
      DnsCleanupModule();
      DhcpCleanupModule();
      V2DhcpCleanupModule();
      DeleteCriticalSection(&DhcpV6GlobalInfoLock);
      DeleteCriticalSection(&DhcpV6InformInterfaceLock);
      TraceCompRef(
        (struct _COMPONENT_REFERENCE *)&DhcpV6InformComponentReference,
        "DELETE",
        dword_180098B70,
        byte_180098B74);
      DeleteCriticalSection(&DhcpV6InformComponentReference);
      NatCleanupModule();
      if ( WPP_GLOBAL_Control != (CInterfaceMonitor *)&WPP_GLOBAL_Control
        && (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0
        && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 6u )
      {
        WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 25i64, &WPP_e9dd5aa48a2f3015263a53cfeeae5727_Traceguids);
      }
      DeleteCriticalSection(&NhpTimerQueueLock);
      if ( WPP_GLOBAL_Control != (CInterfaceMonitor *)&WPP_GLOBAL_Control
        && (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0
        && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 6u )
      {
        WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 26i64, &WPP_e9dd5aa48a2f3015263a53cfeeae5727_Traceguids);
      }
      NhShutdownBufferManagement();
      WSACleanup();
      if ( NhpRtrmgrDll )
      {
        FreeLibrary(NhpRtrmgrDll);
        NhpRtrmgrDll = 0i64;
      }
      DeleteCriticalSection(&NhLock);
      DeleteCriticalSection(&IPv6AddressChangeNotifyLock);
      DeleteCriticalSection(&IPv6RouteChangeNotifyLock);
      DeleteCriticalSection(&PrivateIPv6PrefixLock);
      DeleteCriticalSection(&gInvalidDhcpv6LeaseInfoLock);
      DeleteCriticalSection(&g_csForceRoutingLock);
      if ( dword_1800986B8 )
      {
        DeleteCriticalSection(&gNatMain);
        dword_1800986B8 = 0;
      }
      if ( g_fAtlInitialized )
        ATL::CComModule::Term(v18);
      if ( g_bIpnathlpTraceloggingEnabled )
      {
        v19 = RegHandle;
        RegHandle = 0i64;
        dword_180097208 = 0;
        EventUnregister(v19);
        g_bIpnathlpTraceloggingEnabled = 0;
      }
    }
    v20 = WPP_GLOBAL_Control;
    if ( WPP_GLOBAL_Control == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 1;
    if ( (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0 && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 4u )
    {
      WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 31i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      v20 = WPP_GLOBAL_Control;
    }
    if ( v20 == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 1;
    if ( (*((_BYTE *)v20 + 28) & 8) != 0 && *((_BYTE *)v20 + 25) >= 4u )
    {
      WPP_SF_(*((_QWORD *)v20 + 2), 32i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      v20 = WPP_GLOBAL_Control;
    }
    if ( v20 == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 1;
    while ( v20 )
    {
      v21 = *((_QWORD *)v20 + 1);
      if ( v21 )
      {
        UnregisterTraceGuids(v21);
        *((_QWORD *)v20 + 1) = 0i64;
      }
      v20 = *(CInterfaceMonitor **)v20;
    }
    v17 = &WPP_GLOBAL_Control;
    WPP_GLOBAL_Control = (CInterfaceMonitor *)&WPP_GLOBAL_Control;
    goto LABEL_145;
  }
  if ( fdwReason != 1 )
    goto LABEL_112;
  NhpDllProcessAttachSucceeded = 0;
  DisableThreadLibraryCalls(hinstDLL);
  g_hDllInstance = hinstDLL;
  qword_180098678 = 0i64;
  v4 = (ULONG64 *)&WPP_MAIN_CB;
  WPP_REGISTRATION_GUIDS = (__int64)&WPP_ThisDir_CTLGUID_CtlGuid;
  WPP_GLOBAL_Control = (CInterfaceMonitor *)&WPP_MAIN_CB;
  v5 = (const GUID **)&WPP_REGISTRATION_GUIDS;
  WPP_MAIN_CB = 0i64;
  qword_180098680 = 1i64;
  do
  {
    v6 = *v5;
    TraceGuidReg.Guid = v6;
    TraceGuidReg.RegHandle = 0i64;
    ++v5;
    v4[4] = (ULONG64)v6;
    RegisterTraceGuidsW(WppControlCallback, v4, v6, 1u, &TraceGuidReg, 0i64, 0i64, v4 + 1);
    v4 = (ULONG64 *)*v4;
  }
  while ( v4 );
  if ( WPP_GLOBAL_Control != (CInterfaceMonitor *)&WPP_GLOBAL_Control
    && (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0
    && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 4u )
  {
    WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 10i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
  }
  InitializeCriticalSection(&NhLock);
  InitializeCriticalSection(&IPv6AddressChangeNotifyLock);
  InitializeCriticalSection(&IPv6RouteChangeNotifyLock);
  InitializeCriticalSection(&PrivateIPv6PrefixLock);
  InitializeCriticalSection(&gInvalidDhcpv6LeaseInfoLock);
  InitializeCriticalSection(&g_csForceRoutingLock);
  memset_0(&gNatMain, 0, 0x98ui64);
  InitializeCriticalSection(&gNatMain);
  dword_1800986B8 = 1;
  qword_180098740 = (__int64)&NhApplicationSettingsList; // note: ipnathlp!NatInstallApplicationSettings routine fills this list
  NhApplicationSettingsList = &NhApplicationSettingsList;
  qword_180098730 = (__int64)&NhDhcpReservationList; // note: ipnathlp!NhBuildDhcpReservations routine fills this list
  NhDhcpReservationList = &NhDhcpReservationList;
  NhInitializeBufferManagement();
  if ( NatHlpInitializeTimerManagement() )
  {
    v7 = WPP_GLOBAL_Control;
    if ( WPP_GLOBAL_Control == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 0;
    if ( (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0 && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 2u )
    {
      WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 11i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      v7 = WPP_GLOBAL_Control;
    }
    if ( v7 == (CInterfaceMonitor *)&WPP_GLOBAL_Control || (*((_BYTE *)v7 + 28) & 8) == 0 || *((_BYTE *)v7 + 25) < 6u )
      return 0;
    v8 = 12i64;
LABEL_90:
    WPP_SF_(*((_QWORD *)v7 + 2), v8, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
    return 0;
  }
  if ( !NatInitializeModule() )
  {
    v7 = WPP_GLOBAL_Control;
    if ( WPP_GLOBAL_Control == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 0;
    if ( (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0 && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 2u )
    {
      WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 13i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      v7 = WPP_GLOBAL_Control;
    }
    if ( v7 == (CInterfaceMonitor *)&WPP_GLOBAL_Control || (*((_BYTE *)v7 + 28) & 8) == 0 || *((_BYTE *)v7 + 25) < 6u )
      return 0;
    v8 = 14i64;
    goto LABEL_90;
  }
  if ( !DhcpInitializeModule() )
  {
    v7 = WPP_GLOBAL_Control;
    if ( WPP_GLOBAL_Control == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 0;
    if ( (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0 && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 2u )
    {
      WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 15i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      v7 = WPP_GLOBAL_Control;
    }
    if ( v7 == (CInterfaceMonitor *)&WPP_GLOBAL_Control || (*((_BYTE *)v7 + 28) & 8) == 0 || *((_BYTE *)v7 + 25) < 6u )
      return 0;
    v8 = 16i64;
    goto LABEL_90;
  }
  if ( !V2DhcpInitializeModule() )
  {
    v7 = WPP_GLOBAL_Control;
    if ( WPP_GLOBAL_Control == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 0;
    if ( (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0 && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 2u )
    {
      WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 17i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      v7 = WPP_GLOBAL_Control;
    }
    if ( v7 == (CInterfaceMonitor *)&WPP_GLOBAL_Control || (*((_BYTE *)v7 + 28) & 8) == 0 || *((_BYTE *)v7 + 25) < 6u )
      return 0;
    v8 = 18i64;
    goto LABEL_90;
  }
  if ( !DnsInitializeModule() )
  {
    v7 = WPP_GLOBAL_Control;
    if ( WPP_GLOBAL_Control == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 0;
    if ( (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0 && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 2u )
    {
      WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 19i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      v7 = WPP_GLOBAL_Control;
    }
    if ( v7 == (CInterfaceMonitor *)&WPP_GLOBAL_Control || (*((_BYTE *)v7 + 28) & 8) == 0 || *((_BYTE *)v7 + 25) < 6u )
      return 0;
    v8 = 20i64;
    goto LABEL_90;
  }
  if ( InitializeRegControlForICSIPv6() )
  {
    v7 = WPP_GLOBAL_Control;
    if ( WPP_GLOBAL_Control == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 0;
    if ( (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0 && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 2u )
    {
      WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 21i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      v7 = WPP_GLOBAL_Control;
    }
    if ( v7 == (CInterfaceMonitor *)&WPP_GLOBAL_Control || (*((_BYTE *)v7 + 28) & 8) == 0 || *((_BYTE *)v7 + 25) < 6u )
      return 0;
    v8 = 22i64;
    goto LABEL_90;
  }
  if ( !DhcpV6InitializeModule() )
  {
    v7 = WPP_GLOBAL_Control;
    if ( WPP_GLOBAL_Control == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 0;
    if ( (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0 && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 2u )
    {
      WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 23i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      v7 = WPP_GLOBAL_Control;
    }
    if ( v7 == (CInterfaceMonitor *)&WPP_GLOBAL_Control || (*((_BYTE *)v7 + 28) & 8) == 0 || *((_BYTE *)v7 + 25) < 6u )
      return 0;
    v8 = 24i64;
    goto LABEL_90;
  }
  if ( !AlgInitializeModule() )
  {
    v7 = WPP_GLOBAL_Control;
    if ( WPP_GLOBAL_Control == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 0;
    if ( (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0 && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 2u )
    {
      WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 25i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      v7 = WPP_GLOBAL_Control;
    }
    if ( v7 == (CInterfaceMonitor *)&WPP_GLOBAL_Control || (*((_BYTE *)v7 + 28) & 8) == 0 || *((_BYTE *)v7 + 25) < 6u )
      return 0;
    v8 = 26i64;
    goto LABEL_90;
  }
  if ( (int)InitializeBeaconSvr() < 0 )
  {
    v7 = WPP_GLOBAL_Control;
    if ( WPP_GLOBAL_Control == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
      return 0;
    if ( (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0 && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 2u )
    {
      WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 27i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      v7 = WPP_GLOBAL_Control;
    }
    if ( v7 == (CInterfaceMonitor *)&WPP_GLOBAL_Control || (*((_BYTE *)v7 + 28) & 8) == 0 || *((_BYTE *)v7 + 25) < 6u )
      return 0;
    v8 = 28i64;
    goto LABEL_90;
  }
  _Module = 248;
  qword_180098818 = (__int64)&ATL::GUID_ATLVer30;
  dword_180098800 = 769;
  v12 = ATL::AtlModuleInit(v10, v9, hinstDLL);
  if ( v12 >= 0 )
  {
    dword_180098840 = 1;
    v12 = 0;
    ATL::CComModule::m_libid = LIBID_IPNATHelperLib;
  }
  v13 = g_fAtlInitialized;
  NhpDllProcessAttachSucceeded = 1;
  g_bIpnathlpTraceloggingEnabled = 0;
  if ( v12 >= 0 )
    v13 = 1;
  g_fAtlInitialized = v13;
  v14 = (struct _TRACE_GUID_REGISTRATION)*((_OWORD *)off_180097210 - 1);
  xmmword_180097230 = 0i64;
  TraceGuidReg = v14;
  v15 = EventRegister((LPCGUID)&TraceGuidReg, tlgEnableCallback, &dword_180097208, &RegHandle);
  v16 = v15;
  if ( v15 )
  {
    v16 = (unsigned __int16)v15 | 0x80070000;
    if ( v15 <= 0 )
      v16 = v15;
  }
  else
  {
    EventSetInformation(RegHandle, 2i64, off_180097210, *(unsigned __int16 *)off_180097210);
  }
  if ( !v16 )
  {
    g_bIpnathlpTraceloggingEnabled = 1;
    goto LABEL_107;
  }
  v17 = (CInterfaceMonitor **)WPP_GLOBAL_Control;
  if ( WPP_GLOBAL_Control == (CInterfaceMonitor *)&WPP_GLOBAL_Control )
    return 1;
  if ( (*((_BYTE *)WPP_GLOBAL_Control + 28) & 8) != 0 && *((_BYTE *)WPP_GLOBAL_Control + 25) >= 2u )
  {
    WPP_SF_(*((_QWORD *)WPP_GLOBAL_Control + 2), 29i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
LABEL_107:
    v17 = (CInterfaceMonitor **)WPP_GLOBAL_Control;
  }
  if ( v17 != &WPP_GLOBAL_Control )
  {
    if ( (*((_BYTE *)v17 + 28) & 8) == 0 || *((_BYTE *)v17 + 25) < 4u )
    {
LABEL_145:
      if ( v17 != &WPP_GLOBAL_Control && (*((_BYTE *)v17 + 28) & 8) != 0 && *((_BYTE *)v17 + 25) >= 6u )
        WPP_SF_(v17[2], 33i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
      return 1;
    }
    WPP_SF_(v17[2], 30i64, &WPP_6ed462032f6537244bd9d5ce24e66027_Traceguids);
LABEL_112:
    v17 = (CInterfaceMonitor **)WPP_GLOBAL_Control;
    goto LABEL_145;
  }
  return 1;
}

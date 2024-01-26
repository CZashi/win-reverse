__int64 __fastcall UmpoNotifyInit(int a1)
{
  int WnfSerializationGroup; // eax

  if ( a1 )
  {
    if ( a1 == 1 )
    {
      if ( UmpoScmWnfSubscription )
        MicrosoftTelemetryAssertTriggeredNoArgs();
      WnfSerializationGroup = RtlAllocateWnfSerializationGroup();
      RtlSubscribeWnfStateChangeNotification(
        &UmpoScmWnfSubscription,
        WNF_SCM_AUTOSTART_STATE, // note: This event triggers to indicate SCM autostart state
        0i64,
        UmpoWnfScmPhaseCallback,
        0i64,
        0i64,
        WnfSerializationGroup,
        0);
      if ( UmpoProvEngineWnfSubscription )
        MicrosoftTelemetryAssertTriggeredNoArgs();
      RtlSubscribeWnfStateChangeNotification(
        &UmpoProvEngineWnfSubscription,
        WNF_PROV_TURN_COMPLETE, // note: Fired when a full set of packages are processed.
        0i64,
        UmpoWnfProvEngineTurnCallback,
        0i64,
        0i64,
        0,
        0);
      if ( UmpoBatterySaverWnfSubscription )
        MicrosoftTelemetryAssertTriggeredNoArgs();
      RtlSubscribeWnfStateChangeNotification(
        &UmpoBatterySaverWnfSubscription,
        WNF_PO_ENERGY_SAVER_STATE, // note: Triggered when Energy Saver state changes.
        0i64,
        UmpoWnfBatterySaverCallback,
        0i64,
        0i64,
        0,
        0);
      if ( UmpoBatteryInfoWnfSubscription )
        MicrosoftTelemetryAssertTriggeredNoArgs();
      RtlSubscribeWnfStateChangeNotification(
        &UmpoBatteryInfoWnfSubscription,
        WNF_PO_COMPOSITE_BATTERY, // note: Sent when the composite battery is updated.
        0i64,
        UmpoWnfBatteryInfoCallback,
        0i64,
        0i64,
        0,
        0);
      if ( qword_180022410 )
        qword_180022410();
    }
  }
  else
  {
    qword_1800221D8 = (__int64)&UmpoSettingList; // note: umpo!UmpoNotifyRegister routine fills the list
    UmpoSettingList = &UmpoSettingList;
    qword_1800221C8 = (__int64)&UmpoPdcPpmProfileClientList; // note: umpo!UmpoRegisterPpmProfileClient routine fills the list
    UmpoPdcPpmProfileClientList = &UmpoPdcPpmProfileClientList;
    InitializeCriticalSection(&UmpoSchemeLock);
    byte_180022268 = 1;
    InitializeCriticalSection(&UmpoNotification);
    byte_180022228 = 1;
  }
  return 0i64;
}

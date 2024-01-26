// registers WNF (PowerDynamicBrightnessSliderWnfCallback, PowerVideoInitializedWnfCallback, PowerBrightnessAlsWnfCallback, PowerBasicBrightnessEngineWnfCallback...) & PO notifications to monitors brightness (occurs at DIM engine init)

__int64 DimEngineRegisterPowerNotifications(void)
{
  unsigned int v0; // ebx
  NTSTATUS v1; // eax
  unsigned int v2; // edi
  NTSTATUS v3; // eax
  unsigned int v4; // edi
  NTSTATUS v5; // edi
  NTSTATUS v6; // eax
  unsigned int v7; // edi
  __int64 v9; // r9
  __int64 v10; // r9
  __int64 v11; // r9
  __int64 v12; // r9
  int v13; // [rsp+50h] [rbp+8h] BYREF

  v0 = 0;
  qword_180028F10 = (HPOWERNOTIFY)UmpoRegisterPowerForNotifications(&GUID_DEVICE_POWER_POLICY_VIDEO_BRIGHTNESS);
  if ( qword_180028F10 )
  {
    qword_180028F20 = (HPOWERNOTIFY)UmpoRegisterPowerForNotifications(&GUID_VIDEO_CURRENT_MONITOR_BRIGHTNESS);
    if ( qword_180028F20 )
    {
      if ( !(_BYTE)dword_180029113
        || (qword_180028F38 = (HPOWERNOTIFY)UmpoRegisterPowerForNotifications(&GUID_CONSOLE_DISPLAY_STATE)) != 0i64 )
      {
        v1 = RtlSubscribeWnfStateChangeNotification(
               &qword_180028F58,
               WNF_PO_DYNAMIC_BRIGHTNESS_SLIDER,
               0i64,
               PowerDynamicBrightnessSliderWnfCallback,
               &byte_180029112,
               0i64,
               0,
               0);
        v2 = v1;
        if ( v1 < 0 )
        {
          v9 = RtlNtStatusToDosError(v1);
          if ( (UmpoDebug & 1) != 0 )
            DbgPrint(
              "%s: Failed to register for the dynamic brightness slider state change (NTSTATUS: %08x) Error: %d\n",
              "DimEngineRegisterPowerNotifications",
              v2,
              v9);
        }
        else
        {
          v13 = 0;
          v3 = RtlQueryWnfStateData(
                 &v13,
                 WNF_PO_BASIC_BRIGHTNESS_ENGINE_DISABLED,
                 PowerBasicBrightnessEngineWnfCallback,
                 (char *)&word_180029110 + 1,
                 0i64);
          v4 = v3;
          if ( v3 < 0 )
          {
            v10 = RtlNtStatusToDosError(v3);
            if ( (UmpoDebug & 1) != 0 )
              DbgPrint(
                "%s: Failed to determine if the basic brightness engine should be enabled (NTSTATUS: %08x) Error: %d\n",
                "DimEngineRegisterPowerNotifications",
                v4,
                v10);
          }
          else if ( HIBYTE(word_180029110) )
          {
            if ( (UmpoDebug & 2) != 0 )
              DbgPrint("%s: The basic brightness engine is not needed!", "DimEngineRegisterPowerNotifications");
          }
          else
          {
            DimEngineInputs = (HPOWERNOTIFY)UmpoRegisterPowerForNotifications(&GUID_VIDEO_BRIGHTNESS_CAPABLE);
            if ( DimEngineInputs )
            {
              RegistrationHandle = (HPOWERNOTIFY)UmpoRegisterPowerForNotifications(&GUID_VIDEO_ADAPTIVE_DISPLAY_BRIGHTNESS);
              if ( RegistrationHandle )
              {
                qword_180028F18 = (HPOWERNOTIFY)UmpoRegisterPowerForNotifications(&GUID_DEVICE_POWER_POLICY_VIDEO_DIM_BRIGHTNESS);
                if ( qword_180028F18 )
                {
                  qword_180028F28 = (HPOWERNOTIFY)UmpoRegisterPowerForNotifications(&GUID_POWER_SAVING_STATUS);
                  if ( qword_180028F28 )
                  {
                    qword_180028F30 = (HPOWERNOTIFY)UmpoRegisterPowerForNotifications(&GUID_ENERGY_SAVER_BRIGHTNESS);
                    if ( qword_180028F30 )
                    {
                      v13 = 0;
                      v5 = RtlSubscribeWnfStateChangeNotification(
                             &qword_180028F40,
                             WNF_PO_BRIGHTNESS_ALS_OFFSET,
                             0i64,
                             PowerBrightnessAlsWnfCallback,
                             &dword_18002910C,
                             0i64,
                             0,
                             0);
                      if ( v5 < 0
                        || (v13 = 0,
                            v5 = RtlSubscribeWnfStateChangeNotification(
                                   &qword_180028F48,
                                   WNF_PO_VIDEO_INITIALIALIZED,
                                   0i64,
                                   PowerVideoInitializedWnfCallback,
                                   &word_180029110,
                                   0i64,
                                   0,
                                   0),
                            v5 < 0) )
                      {
                        v11 = RtlNtStatusToDosError(v5);
                        if ( (UmpoDebug & 1) != 0 )
                          DbgPrint(
                            "%s: Failed to subscribe for ALS updates(NTSTATUS: %08x), Error: %d\n",
                            "DimEngineRegisterPowerNotifications",
                            (unsigned int)v5,
                            v11);
                      }
                      else
                      {
                        v13 = 0;
                        v6 = RtlSubscribeWnfStateChangeNotification(
                               &qword_180028F50,
                               WNF_PO_BASIC_BRIGHTNESS_ENGINE_DISABLED,
                               0i64,
                               PowerBasicBrightnessEngineWnfCallback,
                               (char *)&word_180029110 + 1,
                               0i64,
                               0,
                               0);
                        v7 = v6;
                        if ( v6 < 0 )
                        {
                          v12 = RtlNtStatusToDosError(v6);
                          if ( (UmpoDebug & 1) != 0 )
                            DbgPrint(
                              "%s: Failed to subscribe for the basic brightness engine state change notifications (NTSTAT"
                              "US: %08x), Error: %d\n",
                              "DimEngineRegisterPowerNotifications",
                              v7,
                              v12);
                        }
                        else
                        {
                          return 1;
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
  return v0;
}

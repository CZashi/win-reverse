NTSTATUS __stdcall IoRegisterPlugPlayNotification(
        IO_NOTIFICATION_EVENT_CATEGORY EventCategory,
        ULONG EventCategoryFlags,
        PVOID EventCategoryData,
        PDRIVER_OBJECT DriverObject,
        PDRIVER_NOTIFICATION_CALLBACK_ROUTINE CallbackRoutine,
        PVOID Context,
        PVOID *NotificationEntry)
{
  NTSTATUS result; // eax
  __int32 v11; // ebx
  __int32 v12; // ebx
  __int32 v13; // ebx
  NTSTATUS restarted; // ebx
  _GUID *PoolWithTag; // rdi
  WCHAR *v16; // rsi
  WCHAR **v17; // rdx
  _FAST_MUTEX *v18; // rcx
  _GUID *v19; // r14
  char *v20; // rax
  char **v21; // rdx
  __int128 v22; // xmm1
  WCHAR *v23; // r14
  WCHAR *i; // rsi
  _EJOB *CurrentServerSilo; // rax
  int SessionIdFromSymbolicName; // eax
  _GUID **v27; // rax
  _ADAPTER_OBJECT *v28; // rcx
  ULONG v29; // edx
  WCHAR *SymbolicLinkList; // [rsp+30h] [rbp-50h] BYREF
  _UNICODE_STRING DestinationString; // [rsp+38h] [rbp-48h] BYREF
  int v32; // [rsp+48h] [rbp-38h] BYREF
  GUID v33; // [rsp+4Ch] [rbp-34h]
  __int128 v34; // [rsp+5Ch] [rbp-24h]
  int v35; // [rsp+6Ch] [rbp-14h]
  _UNICODE_STRING *p_DestinationString; // [rsp+70h] [rbp-10h]

  LODWORD(SymbolicLinkList) = EventCategoryFlags;
  *NotificationEntry = 0i64;
  result = ObReferenceObjectByPointerWithTag(DriverObject, 0, IoDriverObjectType, 0, 0x4E706E50u);
  if ( result >= 0 )
  {
    v11 = EventCategory - 1;
    if ( v11 )
    {
      v12 = v11 - 1;
      if ( v12 )
      {
        v13 = v12 - 1;
        if ( v13 )
        {
          if ( v13 != 1 )
          {
            restarted = -1073741585;
            goto LABEL_33;
          }
          restarted = PiRegisterKernelSoftRestartNotification(
                        (INT64)DriverObject,
                        CallbackRoutine,
                        (INT64)Context,
                        (PSTR *)NotificationEntry);
          goto LABEL_13;
        }
        SymbolicLinkList = 0i64;
        restarted = PnpGetRelatedTargetDevice((_FILE_OBJECT *)EventCategoryData, &SymbolicLinkList);
        if ( restarted < 0 )
          goto LABEL_33;
        PoolWithTag = (_GUID *)ExAllocatePoolWithTag(PagedPool, 0x70u, 0x43706E50u);
        if ( PoolWithTag )
        {
          restarted = PnpInitializeNotifyEntry(
                        (__int64)PoolWithTag,
                        3,
                        CallbackRoutine,
                        (__int64)Context,
                        (__int64)DriverObject,
                        (__int64)&PnpTargetDeviceNotifyLock);
          if ( restarted < 0 )
          {
            ExFreePoolWithTag(PoolWithTag, 0x43706E50u);
            v28 = (_ADAPTER_OBJECT *)*((_QWORD *)SymbolicLinkList + 4);
          }
          else
          {
            v16 = SymbolicLinkList;
            *(_QWORD *)&PoolWithTag[5].Data1 = EventCategoryData;
            *(_QWORD *)PoolWithTag[5].Data4 = *((_QWORD *)v16 + 4);
            restarted = PnpDeferNotification((__int64)PoolWithTag);
            if ( restarted >= 0 )
            {
              KeAcquireGuardedMutex(&PnpTargetDeviceNotifyLock);
              v17 = (WCHAR **)*((_QWORD *)v16 + 60);
              if ( *v17 == v16 + 236 )
              {
                *(_QWORD *)&PoolWithTag->Data1 = v16 + 236;
                v18 = &PnpTargetDeviceNotifyLock;
                *(_QWORD *)PoolWithTag->Data4 = v17;
                *v17 = (WCHAR *)PoolWithTag;
                *((_QWORD *)v16 + 60) = PoolWithTag;
LABEL_11:
                KeReleaseGuardedMutex(v18);
LABEL_12:
                *NotificationEntry = PoolWithTag;
                goto LABEL_13;
              }
              goto LABEL_47;
            }
            ExFreePoolWithTag(PoolWithTag, 0x43706E50u);
            v28 = (_ADAPTER_OBJECT *)*((_QWORD *)v16 + 4);
          }
          HalPutDmaAdapter(v28);
LABEL_13:
          if ( restarted >= 0 )
            return restarted;
LABEL_33:
          ObfDereferenceObjectWithTag(DriverObject, 0x4E706E50ui64);
          return restarted;
        }
        HalPutDmaAdapter(*((PADAPTER_OBJECT *)SymbolicLinkList + 4));
LABEL_38:
        restarted = -1073741670;
        goto LABEL_33;
      }
      PoolWithTag = (_GUID *)ExAllocatePoolWithTag(PagedPool, 0x60u, 0x44706E50u);
      if ( !PoolWithTag )
        goto LABEL_38;
      restarted = PnpInitializeNotifyEntry(
                    (__int64)PoolWithTag,
                    2,
                    CallbackRoutine,
                    (__int64)Context,
                    (__int64)DriverObject,
                    (__int64)&PnpDeviceClassNotifyLock);
      if ( restarted < 0 )
        goto LABEL_33;
      v19 = PoolWithTag + 5;
      PoolWithTag[5] = *(_GUID *)EventCategoryData;
      restarted = PnpDeferNotification((__int64)PoolWithTag);
      if ( restarted >= 0 )
      {
        KeAcquireGuardedMutex(&PnpDeviceClassNotifyLock);
        v20 = (char *)&PnpDeviceClassNotifyList
            + 16
            * ((v19->Data1
              + *(_DWORD *)&PoolWithTag[5].Data2
              + *(_DWORD *)PoolWithTag[5].Data4
              + *(_DWORD *)&PoolWithTag[5].Data4[4])
             % 0xD);
        v21 = (char **)*((_QWORD *)v20 + 1);
        if ( *v21 == v20 )
        {
          *(_QWORD *)&PoolWithTag->Data1 = v20;
          *(_QWORD *)PoolWithTag->Data4 = v21;
          *v21 = (char *)PoolWithTag;
          *((_QWORD *)v20 + 1) = PoolWithTag;
          KeReleaseGuardedMutex(&PnpDeviceClassNotifyLock);
          if ( ((unsigned __int8)SymbolicLinkList & 1) != 0 )
          {
            v22 = (__int128)*v19;
            SymbolicLinkList = 0i64;
            DestinationString = 0i64;
            v35 = 0;
            v32 = 3145729;
            v33 = GUID_DEVICE_INTERFACE_ARRIVAL;
            v34 = v22;
            restarted = IopGetDeviceInterfaces(PoolWithTag + 5, 0i64, 0i64, 0, &SymbolicLinkList, 0i64);
            if ( restarted < 0 )
              goto LABEL_33;
            v23 = SymbolicLinkList;
            for ( i = SymbolicLinkList; *i; i += ((unsigned __int64)DestinationString.Length >> 1) + 1 )
            {
              LODWORD(SymbolicLinkList) = 0;
              RtlInitUnicodeString(&DestinationString, i);
              p_DestinationString = &DestinationString;
              CurrentServerSilo = PsGetCurrentServerSilo();
              if ( *(_DWORD *)&PoolWithTag[1].Data2 != PsGetServerSiloServiceSessionId(CurrentServerSilo) )
              {
                SessionIdFromSymbolicName = IopGetSessionIdFromSymbolicName(p_DestinationString);
                if ( SessionIdFromSymbolicName != -1 && *(_DWORD *)&PoolWithTag[1].Data2 != SessionIdFromSymbolicName )
                  continue;
              }
              PnpNotifyDriverCallback((__int64)PoolWithTag, (__int64)&v32, &SymbolicLinkList);
            }
            ExFreePoolWithTag(v23, 0);
          }
          goto LABEL_12;
        }
        goto LABEL_47;
      }
      v29 = 1148218960;
    }
    else
    {
      PoolWithTag = (_GUID *)ExAllocatePoolWithTag(PagedPool, 0x50u, 0x39706E50u);
      if ( !PoolWithTag )
        goto LABEL_38;
      restarted = PnpInitializeNotifyEntry(
                    (__int64)PoolWithTag,
                    1,
                    CallbackRoutine,
                    (__int64)Context,
                    (__int64)DriverObject,
                    (__int64)&PnpHwProfileNotifyLock);
      if ( restarted < 0 )
        goto LABEL_33;
      restarted = PnpDeferNotification((__int64)PoolWithTag);
      if ( restarted >= 0 )
      {
        KeAcquireGuardedMutex(&PnpHwProfileNotifyLock);
        v27 = (_GUID **)qword_140D2DB58;
        if ( *(VOID ***)qword_140D2DB58 == &PnpProfileNotifyList )
        {
          *(_QWORD *)&PoolWithTag->Data1 = &PnpProfileNotifyList;
          v18 = &PnpHwProfileNotifyLock;
          *(_QWORD *)PoolWithTag->Data4 = v27;
          *v27 = PoolWithTag;
          qword_140D2DB58 = (__int64)PoolWithTag;
          goto LABEL_11;
        }
LABEL_47:
        __fastfail(3u);
      }
      v29 = 963669584;
    }
    ExFreePoolWithTag(PoolWithTag, v29);
    goto LABEL_13;
  }
  return result;
}

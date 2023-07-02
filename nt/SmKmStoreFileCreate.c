NTSTATUS __stdcall SmKmStoreFileCreate(
        _DRIVER_OBJECT *DriverObject,
        PVOID CreateParam,
        UINT64 RegionSize,
        UINT64 RegionAlignment,
        _LARGE_INTEGER *FileSizeInOut,
        INT64 *CallbackRoutine,
        PVOID a7,
        PVOID a8,
        UINT64 *PerformsFileIoInOut,
        _SMKM_FILE_INFO *FileInfo,
        UINT64 *DeviceSectorSize,
        UINT64 *TotalRegionsOut,
        UINT64 *VdlNotSetOut)
{
  _FILE_OBJECT *v13; // r13
  unsigned int v14; // ebx
  unsigned int v16; // er12
  unsigned int v17; // er15
  UINT64 v18; // r9
  unsigned __int64 v19; // rdi
  void *v20; // r14
  _FILE_OBJECT *v21; // rsi
  _LARGE_INTEGER v22; // rax
  int Status; // ebx
  NTSTATUS v24; // eax
  NTSTATUS v25; // eax
  unsigned int v26; // er13
  _SMC_CACHE_PARAMETERS *v27; // r8
  UINT64 v28; // r9
  __int128 v29; // xmm1
  _OWORD *v30; // rax
  __int128 v31; // xmm0
  __int128 v32; // xmm1
  UINT64 *v33; // rcx
  UINT64 FileInformationClass; // [rsp+20h] [rbp-E0h]
  UINT64 FileInformationClassa; // [rsp+20h] [rbp-E0h]
  UINT64 v37; // [rsp+28h] [rbp-D8h]
  UINT64 ExtentsRelativeToFile; // [rsp+30h] [rbp-D0h]
  BOOLEAN EnableHardErrors; // [rsp+50h] [rbp-B0h]
  _LARGE_INTEGER FileSize; // [rsp+58h] [rbp-A8h] BYREF
  UINT64 PerformsFileIo; // [rsp+60h] [rbp-A0h] BYREF
  int v42; // [rsp+68h] [rbp-98h]
  int v43; // [rsp+6Ch] [rbp-94h]
  _IO_STATUS_BLOCK IoStatusBlock; // [rsp+70h] [rbp-90h] BYREF
  unsigned int RegionSizea; // [rsp+80h] [rbp-80h]
  unsigned int RegionSize_4; // [rsp+84h] [rbp-7Ch]
  _LARGE_INTEGER FileInformation; // [rsp+88h] [rbp-78h] BYREF
  _LARGE_INTEGER v48; // [rsp+90h] [rbp-70h] BYREF
  PVOID NotificationEntry; // [rsp+98h] [rbp-68h] BYREF
  UINT8 dst[64]; // [rsp+A0h] [rbp-60h] BYREF
  PDRIVER_OBJECT DriverObjecta; // [rsp+E0h] [rbp-20h]
  _OWORD *v52; // [rsp+E8h] [rbp-18h]
  UINT64 *v53; // [rsp+F0h] [rbp-10h]
  _SMKM_FILE_INFO *v54; // [rsp+F8h] [rbp-8h]
  _LARGE_INTEGER *v55; // [rsp+100h] [rbp+0h]
  _DWORD *v56; // [rsp+108h] [rbp+8h]
  UINT64 *v57; // [rsp+110h] [rbp+10h]
  __int128 FsInformation; // [rsp+118h] [rbp+18h] BYREF
  __int64 v59; // [rsp+128h] [rbp+28h]
  __int128 v60; // [rsp+130h] [rbp+30h] BYREF
  __int64 v61; // [rsp+140h] [rbp+40h]

  v13 = 0i64;
  v14 = RegionSize;
  v52 = a8;
  v53 = PerformsFileIoInOut;
  v54 = FileInfo;
  v16 = RegionAlignment;
  v57 = DeviceSectorSize;
  DriverObjecta = PnpDriverObject;
  v61 = 0i64;
  v59 = 0i64;
  RegionSize_4 = RegionAlignment;
  RegionSizea = RegionSize;
  v55 = FileSizeInOut;
  v56 = a7;
  IoStatusBlock = 0i64;
  FileInformation.QuadPart = 0i64;
  v60 = 0i64;
  v48.QuadPart = 0i64;
  FsInformation = 0i64;
  NotificationEntry = 0i64;
  memset(dst, 0, sizeof(dst));
  v17 = *(_DWORD *)a7;
  v43 = 0;
  PerformsFileIo = v17;
  v42 = 0;
  EnableHardErrors = IoSetThreadHardErrorMode(0);
  if ( ((unsigned __int8)CreateParam & 1) != 0 )
  {
    v19 = (unsigned __int64)CreateParam & 0xFFFFFFFFFFFFFFFEui64;
    v20 = *(void **)v19;
    v21 = *(_FILE_OBJECT **)(v19 + 8);
    *(_QWORD *)&dst[40] = *(_QWORD *)(v19 + 40);
    *(_QWORD *)dst = v20;
    *(_QWORD *)&dst[8] = v21;
    memset((UINT8 *)v19, 0, 0x40ui64);
    CreateParam = 0i64;
    v22.QuadPart = -1i64;
    v13 = v21;
  }
  else
  {
    v22 = *FileSizeInOut;
    v21 = *(_FILE_OBJECT **)&dst[8];
    v20 = *(void **)dst;
  }
  FileSize = v22;
  if ( v16 > v14 )
  {
    Status = -1073741811;
    goto LABEL_40;
  }
  if ( CreateParam )
  {
    Status = SmKmStoreFileCreateForIoType(
               (_SMKM_FILE_INFO *)dst,
               (wchar_t *)CreateParam,
               &PerformsFileIo,
               v18,
               FileInformationClass);
    if ( Status < 0 )
      goto LABEL_40;
    v20 = *(void **)dst;
    v43 = 1;
    FileInformation = FileSize;
    v24 = ZwSetInformationFile(*(HANDLE *)dst, &IoStatusBlock, &FileInformation, 8u, FileEndOfFileInformation);
    v21 = *(_FILE_OBJECT **)&dst[8];
    Status = v24;
    if ( v24 == 259 )
    {
      KeWaitForSingleObject((PVOID)(*(_QWORD *)&dst[8] + 152i64), Executive, 0, 0, 0i64);
      Status = IoStatusBlock.Status;
    }
    if ( Status < 0 )
    {
LABEL_39:
      SmKmStoreFileDelete((_SMKM_FILE_INFO *)dst);
      goto LABEL_40;
    }
    v17 = PerformsFileIo;
    if ( (_DWORD)PerformsFileIo )
    {
      v48 = FileSize;
      v25 = ZwSetInformationFile(v20, &IoStatusBlock, &v48, 8u, FileValidDataLengthInformation);
      if ( v25 == 259 )
      {
        KeWaitForSingleObject(&v21->Event, Executive, 0, 0, 0i64);
        v25 = IoStatusBlock.Status;
      }
      if ( v25 < 0 )
        v42 = 1;
    }
LABEL_20:
    v26 = RegionSizea;
    if ( FileSize.QuadPart / RegionSizea < 0xFFFFFFFFi64 )
    {
      Status = ZwQueryVolumeInformationFile(v20, &IoStatusBlock, &FsInformation, 0x18u, FileFsSizeInformation);
      if ( Status == 259 )
      {
        KeWaitForSingleObject(&v21->Event, Executive, 0, 0, 0i64);
        Status = IoStatusBlock.Status;
      }
      if ( Status >= 0 )
      {
        if ( !HIDWORD(v59)
          || ((HIDWORD(v59) - 1) & HIDWORD(v59)) != 0
          || HIDWORD(v59) > RegionSize_4
          || HIDWORD(v59) > v26
          || HIDWORD(v59) > 0x1000 )
        {
          Status = -1070071787;
        }
        else
        {
          LODWORD(ExtentsRelativeToFile) = v17;
          LODWORD(FileInformationClassa) = RegionSize_4;
          Status = SmKmStoreFileGetExtents(
                     v20,
                     v21,
                     &FileSize,
                     v26,
                     FileInformationClassa,
                     v37,
                     ExtentsRelativeToFile,
                     (UINT64 *)((char *)&PerformsFileIo + 4),
                     (_SMKM_REGION_EXTENT **)&dst[48],
                     (UINT64 *)&dst[56]);
          if ( Status >= 0 )
          {
            if ( v17
              || (Status = SmKmStoreFileOpenVolume(
                             *(_FILE_OBJECT **)&dst[8],
                             (_FILE_OBJECT **)&dst[16],
                             (_DEVICE_OBJECT **)&dst[24]),
                  Status >= 0) )
            {
              if ( !CreateParam
                || (Status = SmKmStoreFileWriteHeader((_SMKM_FILE_INFO *)dst, v17, v27, v28), Status >= 0) )
              {
                Status = IoRegisterPlugPlayNotification(
                           EventCategoryTargetDeviceChange,
                           0,
                           *(PVOID *)&dst[8],
                           DriverObjecta,
                           (PDRIVER_NOTIFICATION_CALLBACK_ROUTINE)SmcVolumePnpNotification,
                           0i64,
                           &NotificationEntry);
                if ( Status >= 0 )
                {
                  v29 = *(_OWORD *)&dst[16];
                  *(_QWORD *)&dst[32] = NotificationEntry;
                  v30 = v52;
                  *v52 = *(_OWORD *)dst;
                  v31 = *(_OWORD *)&dst[32];
                  v30[1] = v29;
                  v32 = *(_OWORD *)&dst[48];
                  v30[2] = v31;
                  v30[3] = v32;
                  memset(dst, 0, sizeof(dst));
                  Status = 0;
                  *(_DWORD *)v53 = HIDWORD(v59);
                  *v54 = HIDWORD(PerformsFileIo);
                  *v55 = FileSize;
                  v33 = v57;
                  *v56 = v17;
                  *(_DWORD *)v33 = v42;
                  goto LABEL_40;
                }
              }
            }
          }
        }
      }
    }
    else
    {
      Status = -1073741811;
    }
    if ( !v43 )
      goto LABEL_40;
    goto LABEL_39;
  }
  Status = ZwQueryInformationFile(v20, &IoStatusBlock, &v60, 0x18u, FileStandardInformation);
  if ( Status == 259 )
  {
    KeWaitForSingleObject(&v13->Event, Executive, 0, 0, 0i64);
    Status = IoStatusBlock.Status;
  }
  if ( Status >= 0 )
  {
    FileSize = *(_LARGE_INTEGER *)((char *)&v60 + 8);
    goto LABEL_20;
  }
LABEL_40:
  SmKmFileInfoCleanup((_SMKM_FILE_INFO *)dst);
  IoSetThreadHardErrorMode(EnableHardErrors);
  return Status;
}

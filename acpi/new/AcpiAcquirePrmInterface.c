__int64 __fastcall AcpiAcquirePrmInterface(PCUNICODE_STRING SourceString, char a2, __int64 a3)
{
  int DeviceObjectPointer; // ebx
  unsigned __int16 v7; // bx
  int v9; // edx
  int v10; // r8d
  int v11; // r9d
  __int64 v12[5]; // [rsp+40h] [rbp-28h] BYREF
  __int64 v13; // [rsp+88h] [rbp+20h] BYREF

  v13 = 0i64;
  v12[0] = 0i64;
  DeviceObjectPointer = IoGetDeviceObjectPointer(SourceString, 2031616i64, &v13, v12);
  if ( DeviceObjectPointer >= 0 )
  {
    if ( a2 )
    {
      v7 = SourceString->Length + 2;
      stru_1C0081C60.Buffer = (wchar_t *)ExAllocatePool2(64i64, v7, 1181770561i64);
      if ( !stru_1C0081C60.Buffer )
        return 3221225626i64;
      stru_1C0081C60.Length = 0;
      stru_1C0081C60.MaximumLength = v7;
      RtlCopyUnicodeString(&stru_1C0081C60, SourceString);
    }
    DeviceObjectPointer = IoRegisterPlugPlayNotification(
                            3i64,
                            0i64,
                            v13,
                            qword_1C0081C70,
                            AcpiPrmTargetDeviceChangeCallback,
                            0i64,
                            &qword_1C0081C20);
    if ( DeviceObjectPointer >= 0 )
      DeviceObjectPointer = AcpiQueryPrmInterface(*(_QWORD *)(v13 + 8), v9, v10, v11, a3);
  }
  if ( v13 )
    ObfDereferenceObject();
  if ( DeviceObjectPointer < 0 )
  {
    if ( stru_1C0081C60.Buffer )
    {
      RtlFreeUnicodeString(&stru_1C0081C60);
      stru_1C0081C60.Buffer = 0i64;
      *(_DWORD *)&stru_1C0081C60.Length = 0;
    }
  }
  return (unsigned int)DeviceObjectPointer;
}

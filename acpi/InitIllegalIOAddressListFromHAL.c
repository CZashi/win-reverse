void InitIllegalIOAddressListFromHAL()
{
  int v0; // eax
  int v1; // eax
  size_t v2; // rbx
  void *PoolWithTag; // rax
  int v4; // edx
  int v5; // ecx
  unsigned int v6; // [rsp+40h] [rbp+8h] BYREF

  v6 = 0;
  if ( !gpBadIOAddressList )
  {
    v0 = HalDispatchTable->HalQuerySystemInformation(HalQueryAMLIIllegalIOPortAddresses, 0i64, 0i64, &v6);
    if ( v0 != -1073741820 )
    {
      if ( v0 == -1073741496 )
      {
        v4 = 0;
        v5 = 74;
      }
      else
      {
        v4 = v0;
        v5 = 73;
      }
      goto LABEL_17;
    }
    if ( !v6 )
    {
      v4 = 0;
      v5 = 75;
      goto LABEL_17;
    }
    gpBadIOAddressList = ExAllocatePoolWithTag(512i64, v6, 1231842625i64);
    if ( !gpBadIOAddressList )
    {
      LogError(3221225626i64);
      AcpiDiagTraceAmlError(0i64, 3221225626i64);
      v4 = 0;
      v5 = 71;
      goto LABEL_17;
    }
    v1 = HalDispatchTable->HalQuerySystemInformation(
           HalQueryAMLIIllegalIOPortAddresses,
           v6,
           gpBadIOAddressList,
           &v6);
    if ( v1 )
    {
      PrintDebugMessage(73, v1, 0, 0, 0i64);
      FreellegalIOAddressList();
      return;
    }
    if ( v6 / 0x18 != 1 )
    {
      v2 = 4i64 * (v6 / 0x18 - 1);
      PoolWithTag = (void *)ExAllocatePoolWithTag(512i64, v2, 1231842625i64);
      gpBadIOErrorLogDoneList = (__int64)PoolWithTag;
      if ( PoolWithTag )
      {
        memset(PoolWithTag, 0, v2);
        return;
      }
      LogError(3221225626i64);
      AcpiDiagTraceAmlError(0i64, 3221225626i64);
      v4 = 0;
      v5 = 72;
LABEL_17:
      PrintDebugMessage(v5, v4, 0, 0, 0i64);
    }
  }
}

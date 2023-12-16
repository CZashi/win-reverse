UINT8 __stdcall ObInitSystem()
{
  UINT16 v0; // di
  UINT16 v1; // bx
  struct _KPRCB *CurrentPrcb; // rax
  __int64 v3; // rcx
  _QWORD *v4; // rax
  unsigned int v5; // ebx
  unsigned int v6; // ebx
  _NPAGED_LOOKASIDE_LIST *v7; // rdi
  unsigned int v8; // eax
  __int128 *v9; // rbx
  VOID *v10; // rbx
  NTSTATUS v11; // eax
  PADAPTER_OBJECT v12; // rsi
  __int64 *i; // rbx
  __int64 v14; // rdx
  ULONG v16; // edx
  UINT64 v17; // rdx
  VOID *v18; // r9
  INT64 v19; // rax
  UINT8 Depth; // [rsp+28h] [rbp-E0h]
  _OBP_LOOKUP_CONTEXT *Deptha; // [rsp+28h] [rbp-E0h]
  UINT8 ListHead; // [rsp+30h] [rbp-D8h]
  PVOID Object; // [rsp+48h] [rbp-C0h] BYREF
  INT64 Tag; // [rsp+50h] [rbp-B8h] BYREF
  INT64 v25; // [rsp+58h] [rbp-B0h] BYREF
  _OBJECT_TYPE_INITIALIZER dst; // [rsp+68h] [rbp-A0h] BYREF
  _OBJECT_ATTRIBUTES ObjectAttributes; // [rsp+E8h] [rbp-20h] BYREF
  _OBP_LOOKUP_CONTEXT LookupContext; // [rsp+118h] [rbp+10h] BYREF
  _UNICODE_STRING DestinationString; // [rsp+140h] [rbp+38h] BYREF
  _UNICODE_STRING TypeName; // [rsp+150h] [rbp+48h] BYREF
  _UNICODE_STRING v31; // [rsp+160h] [rbp+58h] BYREF
  __int128 SecurityDescriptor[2]; // [rsp+170h] [rbp+68h] BYREF
  __int64 v33; // [rsp+190h] [rbp+88h]
  _ACL Acl; // [rsp+198h] [rbp+90h] BYREF

  v33 = 0i64;
  Tag = 0i64;
  memset(SecurityDescriptor, 0, sizeof(SecurityDescriptor));
  TypeName = 0i64;
  memset(&LookupContext, 0, sizeof(LookupContext));
  memset(&ObjectAttributes, 0, sizeof(ObjectAttributes));
  memset((UINT8 *)&dst, 0, sizeof(dst));
  v25 = 0i64;
  v31 = 0i64;
  DestinationString = 0i64;
  if ( (_BYTE)dword_140CFA19C )
  {
    v0 = 64;
    v1 = 32;
  }
  else
  {
    v0 = 32;
    v1 = 16;
  }
  if ( !(_DWORD)InitializationPhase )
  {
    ObHeaderCookie = ExGenRandom(0);
    ExInitializeSystemLookasideList(
      &ObpCreateInfoLookasideList,
      NonPagedPoolNx,
      0x40ui64,
      0x6943624Fui64,
      v0,
      &ExSystemLookasideListHead);
    ExInitializeSystemLookasideList(
      &ObpNameBufferLookasideList,
      PagedPool,
      0xF8ui64,
      0x6D4E624Fui64,
      v1,
      &ExSystemLookasideListHead);
    CurrentPrcb = KeGetCurrentPrcb();
    ObpPendingObjectDirectoryList = 0i64;
    CurrentPrcb->PPLookasideList[5].L = &ObpNameBufferLookasideList;
    CurrentPrcb->PPLookasideList[5].P = &ObpNameBufferLookasideList;
    CurrentPrcb->PPLookasideList[4].L = &ObpCreateInfoLookasideList;
    v3 = 256i64;
    CurrentPrcb->PPLookasideList[4].P = &ObpCreateInfoLookasideList;
    v4 = &unk_140D24A08;
    ObpRemoveObjectList = 0i64;
    ObpRemoveObjectWait.0 = 0i64;
    *(_QWORD *)&ObpPendingObjectDirectoryListLock = 0i64;
    do
    {
      *(v4 - 1) = 0i64;
      *v4 = 0i64;
      v4 += 2;
      --v3;
    }
    while ( v3 );
    ObpDefaultObject = 0;
    qword_140C258B0 = (__int64)&qword_140C258A8;
    qword_140C258A8 = (__int64)&qword_140C258A8;
    byte_140C258A2 = 6;
    dword_140C258A4 = 1;
    ObpKernelHandleTable = ExCreateHandleTable(0i64, 1ui64);
    KeGetCurrentThread()->ApcState.Process->ObjectTable = ObpKernelHandleTable;
    if ( !ObpKernelHandleTable )
      return 0;
    ObpRemoveObjectWorkItem.Parameter = 0i64;
    ObpRemoveObjectWorkItem.WorkerRoutine = (void (__fastcall *)(void *))ObpProcessRemoveObjectQueue;
    ObpRemoveObjectDpc.DeferredRoutine = (void (__fastcall *)(_KDPC *, void *, void *, void *))ObpProcessRemoveObjectDpcWorker;
    ObpRemoveObjectWorkItem.List.Flink = 0i64;
    ObpRemoveObjectDpc.TargetInfoAsUlong = 275;
    ObpRemoveObjectDpc.DeferredContext = 0i64;
    ObpRemoveObjectDpc.DpcData = 0i64;
    ObpRemoveObjectDpc.ProcessorHistory = 0i64;
    ObpInitInfoBlockOffsets();
    qword_140CFBE88 = (__int64)MmBadPointer;
    dst.InvalidAttributes = 256;
    strcpy((char *)&dst, "x");
    dst.PoolType = NonPagedPoolNx;
    RtlInitUnicodeString(&DestinationString, L"Type");
    LOBYTE(dst.ObjectTypeFlags) |= 0x24u;
    dst.ValidAccessMask = 983041;
    dst.DefaultNonPagedPoolCharge = 216;
    dst.GenericMapping = (_GENERIC_MAPPING)ObpTypeMapping;
    if ( ObCreateObjectType(&DestinationString, &dst, 0i64, (_OBJECT_TYPE **)&ObpTypeObjectType) < 0 )
      return 0;
    dst.PoolType = PagedPool;
    RtlInitUnicodeString(&TypeName, L"Directory");
    dst.DefaultNonPagedPoolCharge = 344;
    dst.ValidAccessMask = 983055;
    LOBYTE(dst.ObjectTypeFlags) = dst.ObjectTypeFlags & 0xD2 | 0xD;
    dst.CloseProcedure = (void (__fastcall *)(_EPROCESS *, void *, unsigned __int64, unsigned __int64))ObpCloseDirectoryObject;
    dst.DeleteProcedure = (void (__fastcall *)(void *))ObpDeleteDirectoryObject;
    dst.GenericMapping = (_GENERIC_MAPPING)ObpDirectoryMapping;
    if ( ObCreateObjectType(&TypeName, &dst, 0i64, &ObpDirectoryObjectType) < 0 )
      return 0;
    dst.CloseProcedure = 0i64;
    ObpDirectoryObjectType->TypeInfo.ValidAccessMask &= ~0x100000u;
    RtlInitUnicodeString(&v31, L"SymbolicLink");
    *((_BYTE *)&dst.1 + 1) |= 1u;
    dst.DeleteProcedure = (void (__fastcall *)(void *))ObpDeleteSymbolicLink;
    dst.DefaultNonPagedPoolCharge = 40;
    dst.ParseProcedure = (int (__fastcall *)(void *, void *, _ACCESS_STATE *, char, unsigned int, _UNICODE_STRING *, _UNICODE_STRING *, void *, _SECURITY_QUALITY_OF_SERVICE *, void **))ObpParseSymbolicLinkEx;
    dst.PoolType = PagedPool;
    dst.ValidAccessMask = 0xFFFFF;
    LOBYTE(dst.ObjectTypeFlags) = dst.ObjectTypeFlags & 0xF6 | 1;
    dst.GenericMapping = (_GENERIC_MAPPING)ObpSymbolicLinkMapping;
    if ( ObCreateObjectType(&v31, &dst, 0i64, &ObpSymbolicLinkObjectType) < 0 )
      return 0;
    ObpSymbolicLinkObjectType->TypeInfo.ValidAccessMask &= ~0x100000u;
    ObpInitStackTrace();
  }
  if ( (_DWORD)InitializationPhase != 1 )
    return 1;
  if ( ObInitServerSilo(0i64) >= 0 )
  {
    v5 = 0;
    if ( (_DWORD)KeNumberProcessors_0 )
    {
      while ( ObInitializeProcessor(*(&KiProcessorBlock + v5)) >= 0 )
      {
        if ( ++v5 >= (unsigned int)KeNumberProcessors_0 )
          goto LABEL_16;
      }
      return 0;
    }
LABEL_16:
    v6 = 0;
    v7 = &ObpWaitBlockLookaside;
    do
    {
      v8 = 14 * v6 + 24;
      if ( v8 >= 0x40 )
        v8 = 64;
      ExInitializeNPagedLookasideList(v7, 0i64, 0i64, 0x200u, 48 * v8, 0x6D57624Fu, 0);
      ++v6;
      ++v7;
    }
    while ( v6 < 4 );
    v9 = (__int128 *)SePublicDefaultUnrestrictedSd;
    if ( !ObpAuditBaseDirectories && !ObpAuditBaseObjects )
      goto LABEL_25;
    v16 = 4 * SeWorldSid->SubAuthorityCount + 28;
    if ( v16 < 0xFA
      && RtlCreateAcl(&Acl, v16, 2u) >= 0
      && RtlAddAuditAccessAce(&Acl, v17, 0x60000000ui64, v18, Depth, ListHead) >= 0
      && RtlGetAce(&Acl, 0, (PVOID *)&Tag) >= 0 )
    {
      v19 = Tag;
      if ( ObpAuditBaseDirectories )
        *(_BYTE *)(Tag + 1) |= 0xAu;
      if ( ObpAuditBaseObjects )
        *(_BYTE *)(v19 + 1) |= 9u;
      v9 = SecurityDescriptor;
      if ( RtlCreateSecurityDescriptor(SecurityDescriptor, 1u) >= 0
        && RtlSetDaclSecurityDescriptor(SecurityDescriptor, 1u, SePublicDefaultUnrestrictedDacl, 0) >= 0
        && RtlSetSaclSecurityDescriptor(SecurityDescriptor, 1u, &Acl, 0) >= 0 )
      {
LABEL_25:
        ObjectAttributes.Length = 48;
        ObjectAttributes.ObjectName = (_UNICODE_STRING *)&ObpRootDirectoryName;
        ObjectAttributes.RootDirectory = 0i64;
        ObjectAttributes.Attributes = 80;
        ObjectAttributes.SecurityDescriptor = v9;
        ObjectAttributes.SecurityQualityOfService = 0i64;
        if ( NtCreateDirectoryObject((VOID **)&v25, 0xF000Fui64, &ObjectAttributes) >= 0 )
        {
          v10 = (VOID *)v25;
          Object = 0i64;
          v11 = ObReferenceObjectByHandle((HANDLE)v25, 0, ObpDirectoryObjectType, 0, &Object, 0i64);
          ObpRootDirectoryObject = Object;
          if ( v11 >= 0 && ObpInitializeRootNamespace(0i64, v10, 0i64) >= 0 && NtClose(v10) >= 0 )
          {
            LookupContext.LockStateSignature = -60876;
            ObpLockDirectoryExclusive(&LookupContext, (_OBJECT_DIRECTORY *)ObpTypeDirectoryObject);
            v12 = ObpTypeObjectType;
            for ( i = *(__int64 **)&ObpTypeObjectType->AdapterObject.DmaHeader.Version;
                  i != (__int64 *)v12;
                  i = (__int64 *)*i )
            {
              if ( (*((_BYTE *)i + 58) & 2) != 0 )
                v14 = (__int64)i - ObpInfoMaskToOffset[*((_BYTE *)i + 58) & 3] + 32;
              else
                v14 = 0i64;
              if ( v14
                && !*(_QWORD *)v14
                && !ObpLookupDirectoryEntry(
                      (_OBJECT_DIRECTORY *)ObpTypeDirectoryObject,
                      (_UNICODE_STRING *)(v14 + 8),
                      0x40ui64,
                      (UINT8)&LookupContext,
                      Deptha)
                && (!i[9] && ObpInitObjectTypeSD(i + 10, 0i64) < 0
                 || !ObpInsertDirectoryEntry((_OBJECT_DIRECTORY *)ObpTypeDirectoryObject, i + 10, &LookupContext)) )
              {
                return 0;
              }
            }
            ObpReleaseLookupContext(&LookupContext);
            Object = &ObpLUIDDeviceMapsEnabled;
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

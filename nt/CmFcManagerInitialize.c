// nt!CmFcSystemManager global var looks interesting, needs more research

__int64 *CmFcManagerInitialize()
{
  void *v0; // rcx
  __int64 v1; // rdx
  __int64 v2; // rcx
  __int64 v3; // rdx
  __int64 v4; // rdx
  __int64 v5; // r9
  __int64 *result; // rax

  memset_0(CmFcSystemManager, 0i64, 872i64);
  CmSiRWLockInitialize(&qword_140E15AC8);
  CmSiRWLockInitialize(&qword_140E15AD0);
  v0 = &unk_140E15AE8;
  v1 = 3i64;
  do
  {
    CmFcpInitializeSectionState(v0, v1);
    v0 = (void *)(v2 + 24);
    v1 = v3 - 1;
  }
  while ( v1 );
  memset_0(&unk_140E15B30, 0i64, 184i64);
  RtlInitializeSwapReference(&unk_140E15B30);
  memset_0(&unk_140E15B48, 0i64, 72i64);
  memset_0(&unk_140E15B90, 0i64, 72i64);
  RtlInitializeSwapReference(&unk_140E15BF0);
  CmSiRWLockInitialize(&qword_140E15C08);
  dword_140E15C28 = 275;
  qword_140E15C60 = 0i64;
  qword_140E15C38 = 0i64;
  qword_140E15C40 = (__int64)CmFcpManagerDrainUsageNotificationsDpc;
  qword_140E15C48 = (__int64)CmFcSystemManager;
  CmpWorkItemInitialize(&unk_140E15C68, 4i64, CmFcpManagerDrainUsageNotificationsWorker, CmFcSystemManager);
  CmpWorkItemInitialize(&unk_140E15CB0, v4, CmFcpManagerRetryUsageNotificationsWorker, v5);
  CmSiRWLockInitialize(&qword_140E15CF0);
  result = &CmFcChangeNotificationsList;
  qword_140E15D00 = (__int64)&CmFcChangeNotificationsList;
  CmFcChangeNotificationsList = (__int64)&CmFcChangeNotificationsList;
  return result;
}

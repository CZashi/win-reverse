void __fastcall NtCreateProcessStateChange(_QWORD *a1, int a2, int a3, int a4, int a5)
{
  int v5; // r10d
  char PreviousMode; // r14
  __int64 v10; // rcx
  int v11; // ecx
  int v12; // r9d
  _QWORD *v13; // rcx
  __int64 v14; // [rsp+20h] [rbp-68h]
  __int64 v15; // [rsp+58h] [rbp-30h] BYREF
  __int64 v16; // [rsp+60h] [rbp-28h] BYREF
  __int64 v17[4]; // [rsp+68h] [rbp-20h] BYREF

  v5 = a4;
  v15 = 0i64;
  v17[0] = 0i64;
  v16 = 0i64;
  PreviousMode = KeGetCurrentThread()->PreviousMode;
  if ( PreviousMode )
  {
    v10 = 0x7FFFFFFF0000i64;
    if ( (unsigned __int64)a1 < 0x7FFFFFFF0000i64 )
      v10 = (__int64)a1;
    *(_QWORD *)v10 = *(_QWORD *)v10;
  }
  if ( !a5 )
  {
    LOBYTE(a4) = PreviousMode;
    if ( (int)ObpReferenceObjectByHandleWithTag(v5, 512, PsProcessType, a4, 1666216784, (__int64)&v15, 0i64, 0i64) >= 0 )
    {
      LOBYTE(v12) = PreviousMode;
      LOBYTE(v11) = PreviousMode;
      if ( (int)ObCreateObjectEx(v11, PspProcessStateChangeType, a3, v12, v14, 24, 0, 0, (__int64)v17, 0i64) >= 0 )
      {
        v13 = (_QWORD *)v17[0];
        *(_OWORD *)v17[0] = 0i64;
        v13[2] = 0i64;
        v13[1] = 0i64;
        *v13 = v15;
        *((_DWORD *)v13 + 4) = 0;
        v15 = 0i64;
        if ( (int)ObInsertObjectEx((_DWORD)v13, 0, a2, 0, 0, 0i64, (__int64)&v16) >= 0 )
        {
          *a1 = v16;
          v16 = 0i64;
        }
      }
    }
  }
  JUMPOUT(0x140A2CDADi64);
}

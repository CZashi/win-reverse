// Kernel Address Sanitizer (KASAN) is a dynamic memory safety error detector designed to find out-of-bounds and use-after-free bugs.
// they also added Kernel Concurrency Sanitizer (KCSAN) (nt!KcsanInitSystem) to detect data races.
// __asan* missing

void __fastcall KasanInitSystem(__int64 a1, int a2)
{
  int v2; // edx
  __int64 v3; // r9
  unsigned __int64 v4; // r8
  int v5; // eax
  unsigned __int64 v6; // r10
  unsigned __int64 v7; // rdx
  int v8; // r8d
  _QWORD *v9; // rbx
  _QWORD *v10; // rdi
  int ImageInternal; // eax

  if ( a2 )
  {
    byte_140F728F1 = 1;
    KasanDriverUnloadInfosLock = 0i64;
    v2 = *(_DWORD *)(a1 + 160);
    v3 = (unsigned int)(8 * v2 + 0x8000);
    v4 = *(_QWORD *)(a1 + 128) - (unsigned int)(2 * v2 + 0x2000);
    if ( byte_140F728F0 && 8 * v2 != -32768 )
    {
      if ( v4 < 0xFFFF800000000000ui64 )
      {
        v5 = -1073741585;
LABEL_15:
        KeBugCheckEx(497, 4, 5, v5, 0i64);
        __debugbreak();
      }
      if ( v4 + v3 < v4 )
      {
        v5 = -1073741675;
        goto LABEL_15;
      }
      v6 = (((qword_140F728F8 + ((v4 + 0x800000000000i64) >> 3)) >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64;
      v7 = (((qword_140F728F8 + ((v3 + v4 + 0x7FFFFFFFFFFFi64) >> 3)) >> 9) & 0x7FFFFFFFF8i64) - 0x98000000000i64;
      v8 = 4656;
      if ( KeGetCurrentIrql() != 2 )
        v8 = 560;
      if ( !(unsigned int)MiMakeZeroedPageTablesEx(v6, v7, v8, 19, 0) )
      {
        v5 = -1073741670;
        goto LABEL_15;
      }
    }
    qword_140F652E0 = qword_140F728F8 - 0x1FFFF00000000000i64;
    return;
  }
  qword_140F652E0 = (__int64)&KasaniBootShadow
                  - ((*(_QWORD *)(a1 + 128) - (unsigned __int64)(unsigned int)(2 * *(_DWORD *)(a1 + 160) + 0x2000)) >> 3);
  if ( (*(_DWORD *)(*(_QWORD *)(a1 + 240) + 3856i64) & 1) != 0 )
  {
    v9 = *(_QWORD **)(a1 + 16);
    v10 = (_QWORD *)(a1 + 16);
    for ( byte_140F728F0 = 1; v9 != v10; v9 = (_QWORD *)*v9 )
    {
      ImageInternal = KasanDriverLoadImageInternal(v9, 1i64, 1i64);
      if ( ImageInternal < 0 )
      {
        KeBugCheckEx(497, 4, 7, (_DWORD)v9, ImageInternal);
        JUMPOUT(0x140C135F6i64);
      }
    }
  }
  else
  {
    byte_140F728F0 = 0;
  }
}

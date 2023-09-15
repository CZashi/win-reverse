__int64 KepGenericProcessorMulticastHelper()
{
  unsigned __int16 v0; // w0
  int v1; // w9
  unsigned int v2; // w19
  void *v3; // x8

  v0 = KepGenericProcessorMulticastCallback(KepGenericProcessorMulticastParameter);
  v2 = v0;
  if ( v0 )  {
    _mm_prefetcht0(v1, &KepGenericProcessorMulticastStatus);
    if ( !v1 )
      _mm_prefetcht1(v0, &KepGenericProcessorMulticastStatus);
  }
  v3 = &unk_F8000043E000;
  do {
    _mm_prefetcht2((__int32)v3, &KepGenericProcessorMulticastRemainingWorkers);
    LODWORD(v3) = (_DWORD)v3 - 1;
    _mm_prefetchnta(v1, (__int32)v3, &KepGenericProcessorMulticastRemainingWorkers);
  }
  while ( v1 );
  __dmb(0xBu);
  if ( !(_DWORD)v3 )
    ThpSignalEvent(KepGenericProcessorMulticastCompletionEvent, 1i64, 0i64);
  return v2;
}

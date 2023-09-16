char __fastcall KiProcessNMI(_KTRAP_FRAME *TrapFrame, _KEXCEPTION_FRAME *KernelExceptionFrame)
{
  char NmiServiceResult;
  char CallbackHandled;
  int IsNmiBeingServiced
  struct _KPRCB *Prcb;
  int Number;
  __int64 Handled;
  _KNMI_HANDLER_CALLBACK *NmiListHead;
 
  HalPreprocessNmi(0);
  _mm_lfence();
  LOBYTE(IsNmiBeingServiced) = KiCheckForFreezeExecution(TrapFrame, KernelExceptionFrame);
  if ( !IsNmiBeingServiced )
  {
    Prcb = KeGetCurrentPrcb();
    Number = Prcb->Number;
    IsNmiBeingServiced = KeInterlockedSetProcessorAffinityEx(&KiNmiInProgress, Prcb->Number);
    if ( !IsNmiBeingServiced )
    {
      HalPreprocessNmi(1);
      NmiListHead = KiNmiCallbackListHead;
      NmiServiceResult = 0;
      if ( !KiNmiCallbackListHead )
        goto HalServiceNmi;
      do 
      {
        LOBYTE(Handled) = NmiServiceResult;
        CallbackHandled = (NmiListHead->NmiCallback)(NmiListHead->Context, Handled);
        NmiListHead = NmiListHead->Next;
        NmiServiceResult |= CallbackHandled;
      }
      while ( NmiListHead );
      if ( !NmiServiceResult )
      {
HalServiceNmi:
        while ( !KxTryToAcquireSpinLock(&KiNMILock) )
        {
          do
            KiCheckForFreezeExecution(TrapFrame, KernelExceptionFrame);
          while ( KiNMILock );
        }
        _InterlockedCompareExchange(&KiBugCheckActive, 1, 0);
        HalHandleNMI();
        _InterlockedCompareExchange(&KiBugCheckActive, 0, 1);
        KxReleaseSpinLock(&KiNMILock);
      }
      LOBYTE(IsNmiBeingServiced) = KeInterlockedClearProcessorAffinityEx(&KiNmiInProgress, Number);
    }
  }
  return IsNmiBeingServiced;
}

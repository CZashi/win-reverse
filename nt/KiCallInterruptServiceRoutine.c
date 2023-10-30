/*

Once executing on the ISR stack, the functions KiInterruptDispatch() and KiChainedDispatch() propagate execution to the next stage by calling 
KiInterruptSubDispatch() or KiScanInterruptObjectList() respectively. KiInterruptSubDispatch() calls KiCallInterruptServiceRoutine() for a single KINTERRUPT structure. 
KiScanInterruptObjectList() iterates through all the KINTERRUPT objects registered for a single vector using the list at KINTERRUPT.InterruptListEntry 
and calls KiCallInterruptServiceRoutine() for each KINTERRUPT structure in the chain. 

KiCallInterruptServiceRoutine() performs the following tasks:

- Marks the interrupt as active in KINTERRUPT.IsrDpcStats.IsrActive.
- Records the ISR start time in KINTERRUPT.IsrDpcStats.IsrTimeStart.
- Acquires the interrupt spinlock in KINTERRUPT.ActualLock.
- Calls the driver registered ISR in KINTERRUPT.ServiceRoutine.
- Records the ISR duration in KINTERRUPT.IsrDpcStats.IsrTime.
- If the ISR was interrupted by another one at a higher IRQL, it adjusts the IsrTime for accurate time accounting.
- Marks the interrupt as inactive in KINTERRUPT.IsrDpcStats.IsrActive.
- Increments the interrupt instance counter in IsrCount.

The driver registered ISR can tell the caller KiCallInterruptServiceRoutine() if it claimed the interrupt by returning TRUE.
This becomes important in the case of shared interrupts where the decision to call the ISR in the next KINTERRUPT in the chain depends on whether the current ISR has claimed the interrupt or not.

*/

UINT8 __fastcall KiCallInterruptServiceRoutine(_KINTERRUPT *Interrupt, UINT8 AcquireSpinlock)
{
  _BYTE *RedirectObject; // r9
  struct _KPRCB *CurrentPrcb; // rdi
  _QWORD *IsrDpcStats; // r14
  unsigned __int64 v7; // rax
  unsigned __int64 v8; // r12
  unsigned __int8 v9; // bp
  unsigned __int64 v10; // rax
  unsigned int DpcWatchdogSequenceNumber; // edx
  unsigned __int64 v12; // rcx
  unsigned __int64 *ActualLock; // rbp
  int v15; // edx
  unsigned int v16; // er8
  unsigned int FirstSetRightGroupAffinity; // eax
  unsigned __int64 v18; // rax

  if ( Interrupt->Vector - 48 <= 0x9F && !KiForceIdleDisabled )
  {
    if ( (_DWORD)KiForceIdleState == 4 )
    {
      KiResetForceIdle(1i64, 0);
    }
    else if ( (unsigned int)(KiForceIdleState - 1) <= 1 )
    {
      KiCheckAndRearmForceIdle();
    }
  }
  if ( !Interrupt->SynchronizeIrql )
  {
    v9 = Interrupt->ServiceRoutine(Interrupt, Interrupt->ServiceContext);
    return v9 != 0;
  }
  RedirectObject = Interrupt->RedirectObject;
  if ( RedirectObject && RedirectObject[16] )
  {
    v15 = 0;
    v16 = KiProcessorIndexToNumberMappingTable[KeGetPcr()->Prcb.Number];
    if ( v16 >> 6 == *((unsigned __int16 *)RedirectObject + 4) )
      v15 = 1;
    if ( ((unsigned int)(*(_QWORD *)RedirectObject >> (v16 & 0x3F)) & v15) == 0 )
    {
      FirstSetRightGroupAffinity = KeFindFirstSetRightGroupAffinity((_GROUP_AFFINITY *)Interrupt->RedirectObject);
      KiIntRedirectQueueRequestOnProcessor(FirstSetRightGroupAffinity, Interrupt->Vector);
      return 2;
    }
  }
  CurrentPrcb = KeGetCurrentPrcb();
  IsrDpcStats = CurrentPrcb->IsrDpcStats;
  Interrupt->IsrDpcStats.IsrActive = 1;
  CurrentPrcb->IsrDpcStats = &Interrupt->IsrDpcStats;
  v7 = __rdtsc();
  Interrupt->IsrDpcStats.IsrTimeStart = v7;
  v8 = v7;
  if ( AcquireSpinlock )
  {
    ActualLock = Interrupt->ActualLock;
    if ( _interlockedbittestandset64((volatile signed __int32 *)ActualLock, 0i64) )
      KxWaitForSpinLockAndAcquire(ActualLock);
  }
  v9 = Interrupt->ServiceRoutine(Interrupt, Interrupt->ServiceContext);
  if ( AcquireSpinlock )
    _InterlockedAnd64((volatile signed __int64 *)Interrupt->ActualLock, 0i64);
  v10 = __rdtsc();
  DpcWatchdogSequenceNumber = CurrentPrcb->DpcWatchdogSequenceNumber;
  v12 = v10 - Interrupt->IsrDpcStats.IsrTimeStart;
  if ( DpcWatchdogSequenceNumber != Interrupt->IsrDpcStats.DpcWatchdog.SequenceNumber )
  {
    Interrupt->IsrDpcStats.DpcWatchdog.SequenceNumber = DpcWatchdogSequenceNumber;
    Interrupt->IsrDpcStats.DpcWatchdog.IsrTime = 0i64;
    Interrupt->IsrDpcStats.DpcWatchdog.IsrCount = 0i64;
    Interrupt->IsrDpcStats.DpcWatchdog.DpcTime = 0i64;
    Interrupt->IsrDpcStats.DpcWatchdog.DpcCount = 0i64;
  }
  Interrupt->IsrDpcStats.IsrTime += v12;
  Interrupt->IsrDpcStats.DpcWatchdog.IsrTime += v12;
  if ( IsrDpcStats != (_QWORD *)1 )
  {
    v18 = v10 - v8;
    if ( *((_BYTE *)IsrDpcStats + 48) )
      IsrDpcStats[1] += v18;
    else
      IsrDpcStats[4] += v18;
  }
  CurrentPrcb->IsrDpcStats = IsrDpcStats;
  Interrupt->IsrDpcStats.IsrActive = 0;
  if ( v9 )
  {
    ++Interrupt->IsrDpcStats.IsrCount;
    ++Interrupt->IsrDpcStats.DpcWatchdog.IsrCount;
    return v9 != 0;
  }
  return 0;
}

char __fastcall HalMakeBeep(unsigned int Frequency)
{
  char result; // al
  char v3; // di
  unsigned __int8 v4; // al
  unsigned __int8 v5; // bl
  unsigned __int8 v6; // al
  unsigned __int8 v7; // bl

  result = HalpMiscIsLegacyPcType();
  if ( result )
  {
    v3 = 1;
    HalpAcquireCmosSpinLock();
    v4 = __inbyte(0x61u);
    v5 = v4;
    HalpIoDelay();
    __outbyte(0x61u, v5 & 0xFC);
    HalpIoDelay();
    if ( Frequency )
    {
      if ( 0x1234CF / Frequency <= 0xFFFF )
      {
        __outbyte(0x43u, 0xB6u);
        HalpIoDelay();
        WRITE_PORT_USHORT_PAIR(66i64, 66i64, (unsigned __int16)(0x1234CF / Frequency));
        HalpIoDelay();
        v6 = __inbyte(0x61u);
        v7 = v6;
        HalpIoDelay();
        __outbyte(0x61u, v7 | 3);
        HalpIoDelay();
      }
      else
      {
        v3 = 0;
      }
    }
    _InterlockedExchange(&HalpSystemHardwareLock, -1);
    if ( HalpSystemHardwareLockInterruptsEnabled )
      _enable();
    return v3;
  }
  return result;
}

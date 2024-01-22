beep is available from usermode using `kernel32!Beep` (\\Device\\Beep w NtCreateFile) & use IOCTLs to communicate with beep.sys but talking about IOCTLs and the driver is not interesting so the interesting function behind that is `nt!HalMakeBeep`  

- `nt!HalMakeBeep` routine  holds in ~45 lines and works with **CMOS (Complementary Metal-Oxide-Semiconductor) I/O ports** to read (`__inbyte`) and write (`__outbyte`), (`in`/`out` instructions) and takes one param to set the frequency of the beep that will comes out the internal speaker. `nt!HalpIoDelay` is called after each operations to I/O ports
  ![image](https://github.com/CZashi/win-reverse/assets/113217553/b14bfb53-378a-4d74-8a3d-b459d52edfa8)
  - it acquire CMOS lock (`nt!HalpSystemHardwareLock`) via `nt!HalpAcquireCmosSpinLock` routine
  - get bit 1 of port 61h & disconnect the speaker to the timer and disable the output pin so 0xFC or 1111 1100 for the two last bit 
  - Set a divider (0x1234CF) to the frequency while <= to 0xFFFF depending of the frequency provided
  - config the pit and writes it to *Timer 8253-5 (AT: 8254.2)* aka 43h so it will play the sound after reenabling speakergate
  - Reconnect the speaker to the timer and re-enable the output on port 61h

![image](https://github.com/CZashi/win-reverse/assets/113217553/606fb28f-70e9-4262-8790-d652d480b351)

> in the windows kernel there is a symbol called `nt!HalpSystemHardwareLockInterruptsEnabled` to track the state of interrupts in the context of CMOS (Re-enable interrupts if necessary with _enable) 

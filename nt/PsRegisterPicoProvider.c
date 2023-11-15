
/*
Pico Routines

- Create Pico processes and threads: PspCreatePicoProcess, PspCreatePicoThread
- Get and set PicoContext pointer (From EPROCESS & ETHREAD) : PspGetPicoProcessContext, PspGetPicoThreadContext
- Get and set CPU CONTEXT structure: PspGetContextThreadInternal, PspSetContextThreadInternal
- Destroy Pico processes and threads: PspTerminateThreadByPointer, PspTerminatePicoProcess
- Resume and suspend Pico processes and threads: PsResumeThread, PsSuspendThread
- Set user-mode FS and GS segment for Pico threads: PspSetPicoThreadDescriptorBase
*/

// • Pico Providers also “register” with PatchGuard, providing it with their internal list of system call handlers Essentially, this means that the Linux system calls are protected by PatchGuard, just like the NT ones
// Touching to PspPicoRegistrationDisabled / Force Unregister / Patching the callbacks (PspPicoProviderRoutines) 
  // / attempting to register a “fake” Pico Provider, or modifying key Pico Provider state  -> triggers Patchguard



typedef struct _PS_PICO_ROUTINES {
		SIZE_T Size;
		PPS_PICO_CREATE_PROCESS CreateProcess;
		PPS_PICO_CREATE_THREAD CreateThread;
		PPS_PICO_GET_PROCESS_CONTEXT GetProcessContext;
		PPS_PICO_GET_THREAD_CONTEXT GetThreadContext;
		PPS_GET_CONTEXT_THREAD_INTERNAL GetContextThreadInternal;
		PPS_SET_CONTEXT_THREAD_INTERNAL SetContextThreadInternal;
		PPS_TERMINATE_THREAD TerminateThread;
		PPS_RESUME_THREAD ResumeThread;
		PPS_PICO_SET_THREAD_DESCRIPTOR_BASE SetThreadDescriptorBase;
		PPS_SUSPEND_THREAD SuspendThread;
		PPS_PICO_TERMINATE_PROCESS TerminateProcess;
} PS_PICO_ROUTINES, *PPS_PICO_ROUTINES;

typedef struct _PS_PICO_PROVIDER_ROUTINES {
		SIZE_T Size;
		PPS_PICO_PROVIDER_SYSTEM_CALL_DISPATCH DispatchSystemCall;
		PPS_PICO_PROVIDER_THREAD_EXIT ExitThread;
		PPS_PICO_PROVIDER_PROCESS_EXIT ExitProcess;
		PPS_PICO_PROVIDER_DISPATCH_EXCEPTION DispatchException;
		PPS_PICO_PROVIDER_TERMINATE_PROCESS TerminateProcess;
		PPS_PICO_PROVIDER_WALK_USER_STACK WalkUserStack;
		CONST KADDRESS_RANGE_DESCRIPTOR *ProtectedRanges;
		PPS_PICO_GET_ALLOCATED_PROCESS_IMAGE_NAME GetAllocatedProcessImageName;
		ACCESS_MASK OpenProcess;
		ACCESS_MASK OpenThread;
} PS_PICO_PROVIDER_ROUTINES, *PPS_PICO_PROVIDER_ROUTINES;

NTSTATUS __stdcall PsRegisterPicoProvider(PS_PICO_PROVIDER_ROUTINES *ProviderRoutines, PS_PICO_ROUTINES *PicoRoutines)
{
  NTSTATUS result; // eax

  if ( *(_QWORD *)ProviderRoutines != 88i64 || *(_QWORD *)PicoRoutines != 96i64 )
    return STATUS_INFO_LENGTH_MISMATCH;
  if ( (ProviderRoutines[18] & 0xFFE00000) != 0 || (ProviderRoutines[19] & 0xFFE00000) != 0 )
    return STATUS_INVALID_PARAMETER;
  
  result = 0;
  if ( PspPicoRegistrationDisabled )
    return -1073741431;
  
  PspPicoProviderRoutines = *(_OWORD *)ProviderRoutines;
  xmmword_140C1DE50 = ProviderRoutines.DispatchSystemCall;
  xmmword_140C1DE60 = ProviderRoutines.ExitThread;
  xmmword_140C1DE70 = ProviderRoutines.ExitProcess;
  xmmword_140C1DE80 = ProviderRoutines.DispatchException;
  qword_140C1DE90 = ProviderRoutines.OpenThread;
  
  *(_QWORD *)&PspPicoProviderRanges = _mm_srli_si128((__m128i)xmmword_140C1DE70, 8).m128i_u64[0];
  
  PicoRoutines.CreateProcess = PspCreatePicoProcess;
  PicoRoutines.CreateThread = PspCreatePicoThread;
  PicoRoutines.GetProcessContext = PspGetPicoProcessContext;
  PicoRoutines.GetThreadContext = PspGetPicoThreadContext;
  PicoRoutines.GetContextThreadInternal = PspPicoGetContextThreadEx;
  PicoRoutines.SetContextThreadInternal = PspPicoSetContextThreadEx;
  PicoRoutines.TerminateThread = PspTerminateThreadByPointer;
  PicoRoutines.ResumeThread = PsResumeThread;
  PicoRoutines.SetThreadDescriptorBase = PspSetPicoThreadDescriptorBase;
  PicoRoutines.SuspendThread = PsSuspendThread;
  PicoRoutines.TerminateProcess = PspTerminatePicoProcess;
  PicoRoutines = 96i64;
  
  return result;
}

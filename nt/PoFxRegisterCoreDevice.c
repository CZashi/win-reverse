typedef struct _POP_FX_DRIVER_CALLBACKS
{
  /* 0x0000 */ void* ComponentActive /* function */;
  /* 0x0008 */ void* ComponentIdle /* function */;
  /* 0x0010 */ void* ComponentIdleState /* function */;
  /* 0x0018 */ void* DevicePowerRequired /* function */;
  /* 0x0020 */ void* DevicePowerNotRequired /* function */;
  /* 0x0028 */ void* PowerControl /* function */;
  /* 0x0030 */ void* ComponentCriticalTransition /* function */;
} POP_FX_DRIVER_CALLBACKS, *PPOP_FX_DRIVER_CALLBACKS; /* size: 0x0038 */

typedef struct _PO_FX_CORE_DEVICE {
    ULONG Version;
    ULONG ComponentCount;
    PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK ComponentActiveConditionCallback;
    PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK ComponentIdleConditionCallback;
    PPO_FX_COMPONENT_CRITICAL_TRANSITION_CALLBACK ComponentCriticalTransitionCallback;
    PPO_FX_COMPONENT_IDLE_STATE_CALLBACK ComponentIdleStateCallback;
    PVOID DeviceContext;
    _Field_size_full_(ComponentCount) PO_FX_COMPONENT Components[ANYSIZE_ARRAY];
} PO_FX_CORE_DEVICE, *PPO_FX_CORE_DEVICE;

NTSTATUS __stdcall PoFxRegisterCoreDevice(const _UNICODE_STRING *Id, _PO_FX_CORE_DEVICE *CoreDevice, POHANDLE__ **Handle)
{
  _PO_FX_COMPONENT_V2 *v6; // rdi
  _PO_FX_COMPONENT_V2 *v7; // rax
  _EX_PUSH_LOCK *v8; // rdx
  _LIST_ENTRY *v9; // rcx
  int v10; // ebx
  UINT64 ComponentCount; // [rsp+20h] [rbp-88h]
  _POP_FX_DRIVER_CALLBACKS Callbacks; // [rsp+50h] [rbp-58h] BYREF
  _POP_FX_DEVICE *FxDevice; // [rsp+B0h] [rbp+8h] BYREF

  memset((UINT8 *)&Callbacks, 0, sizeof(Callbacks));
  v6 = 0i64;
  FxDevice = 0i64;
  if ( Id && CoreDevice->Version == 1 && CoreDevice->ComponentCriticalTransitionCallback )
  {
    v7 = PopFxConvertV1Components(CoreDevice->Components, CoreDevice->ComponentCount);
    v6 = v7;
    if ( !v7 )
    {
      v10 = -1073741670;
      goto LABEL_9;
    }
    Callbacks.ComponentActive = (void (__fastcall *)(void *, unsigned int))CoreDevice->ComponentActiveConditionCallback;
    Callbacks.ComponentIdle = (void (__fastcall *)(void *, unsigned int))CoreDevice->ComponentIdleConditionCallback;
    Callbacks.ComponentIdleState = (void (__fastcall *)(void *, unsigned int, unsigned int))CoreDevice->ComponentIdleStateCallback;
    Callbacks.ComponentCriticalTransition = (void (__fastcall *)(void *, unsigned int, unsigned __int8))CoreDevice->ComponentCriticalTransitionCallback;
    
    LODWORD(ComponentCount) = CoreDevice->ComponentCount;
    v10 = PopFxRegisterDeviceWorker(0i64, Id, &Callbacks, v7, ComponentCount, CoreDevice->DeviceContext, 0, 0i64, &FxDevice);
    if ( v10 < 0 ) {
      FxDevice = 0i64;
    }
    else {
      PopFxInsertDevice(v9, v8, FxDevice);
      v10 = 0;
    }
  }
  else {
    v10 = -1073741811;
  }
  if ( v6 )
    ExFreePoolWithTag(v6, 0x4D584650u);
LABEL_9:
  *Handle = (POHANDLE__ *)FxDevice;
  return v10;
}

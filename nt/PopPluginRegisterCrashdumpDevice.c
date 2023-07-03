struct _POP_FX_DEVICE
{
    struct _LIST_ENTRY Link;                                                //0x0
    struct _IRP* Irp;                                                       //0x10
    struct _POP_IRP_DATA* IrpData;                                          //0x18
    unionvolatile _POP_FX_DEVICE_STATUS Status;                             //0x20
    volatile LONG PowerReqCall;                                             //0x24
    volatile LONG PowerNotReqCall;                                          //0x28
    struct _DEVICE_NODE* DevNode;                                           //0x30
    struct PEPHANDLE__* DpmContext;                                         //0x38
    struct _POP_FX_PLUGIN* Plugin;                                          //0x40
    struct PEPHANDLE__* PluginHandle;                                       //0x48
    struct _POP_FX_PLUGIN* AcpiPlugin;                                      //0x50
    struct PEPHANDLE__* AcpiPluginHandle;                                   //0x58
    struct _DEVICE_OBJECT* DeviceObject;                                    //0x60
    struct _DEVICE_OBJECT* TargetDevice;                                    //0x68
    struct _POP_FX_DRIVER_CALLBACKS Callbacks;                              //0x70
    VOID* DriverContext;                                                    //0xc0
    struct _LIST_ENTRY AcpiLink;                                            //0xc8
    struct _UNICODE_STRING DeviceId;                                        //0xd8
    volatile LONG CommonReferenceFlags;                                     //0xe8
    struct _IO_REMOVE_LOCK RemoveLock;                                      //0xf0
    struct _IO_REMOVE_LOCK AcpiRemoveLock;                                  //0x110
    struct _POP_FX_WORK_ORDER WorkOrder;                                    //0x130
    ULONGLONG IdleLock;                                                     //0x168
    struct _KTIMER IdleTimer;                                               //0x170
    struct _KDPC IdleDpc;                                                   //0x1b0
    ULONGLONG IdleTimeout;                                                  //0x1f0
    ULONGLONG IdleStamp;                                                    //0x1f8
    struct _DEVICE_OBJECT* NextIrpDeviceObject[2];                          //0x200
    union _POWER_STATE NextIrpPowerState[2];                                //0x210
    VOID (*NextIrpCallerCompletion[2])(struct _DEVICE_OBJECT* arg1, UCHAR arg2, union _POWER_STATE arg3, VOID* arg4, struct _IO_STATUS_BLOCK* arg5); //0x218
    VOID* NextIrpCallerContext[2];                                          //0x228
    struct _KEVENT IrpCompleteEvent;                                        //0x238
    UCHAR (*PowerOnDumpDeviceCallback)(struct _PEP_CRASHDUMP_INFORMATION* arg1); //0x250
    struct _POP_FX_ACCOUNTING Accounting;                                   //0x258
    volatile ULONG Flags;                                                   //0x338
    ULONG ComponentCount;                                                   //0x33c
    struct _POP_FX_COMPONENT** Components;                                  //0x340
    ULONG LogEntries;                                                       //0x348
    struct _POP_FX_LOG_ENTRY* Log;                                          //0x350
    volatile LONG LogIndex;                                                 //0x358
    struct _DRIVER_OBJECT* DripsWatchdogDriverObject;                       //0x360
    struct _POP_FX_DRIPS_WATCHDOG_CONTEXT DripsWatchdogContext;             //0x368
    ULONG DirectedTimeout;                                                  //0x390
    struct _POP_FX_WORK_ORDER DirectedWorkOrder;                            //0x398
    struct _POP_FX_WORK_ORDER_WATCHDOG_INFO DirectedWorkWatchdogInfo;       //0x3d0
    ULONGLONG DirectedLock;                                                 //0x480
    volatile LONG DirectedTransitionCallCount;                              //0x488
    struct _POP_FX_DEVICE_DIRECTED_TRANSITION_STATE DirectedTransitionState; //0x490
    struct _POP_DEVICE_POWER_PROFILE* PowerProfile;                         //0x4a0
    struct _UNICODE_STRING FriendlyName;                                    //0x4a8
    struct _WORK_QUEUE_ITEM ReportDevicePoweredOnPassiveWorkItem;           //0x4b8
    ULONGLONG RelationsLock;                                                //0x4d8
    ULONG IdleProviderCount;                                                //0x4e0
    struct _IRP* PendingDevicePowerIrp;                                     //0x4e8
    struct _LIST_ENTRY ExternalDependencies;                                //0x4f0
}; 

struct _POP_FX_PLUGIN
{
    struct _LIST_ENTRY Link;                                                //0x0
    ULONG Version;                                                          //0x10
    ULONGLONG Flags;                                                        //0x18
    struct _KQUEUE WorkQueue;                                               //0x20
    UCHAR (*AcceptDeviceNotification)(ULONG arg1, VOID* arg2);              //0x60
    UCHAR (*AcceptProcessorNotification)(struct PEPHANDLE__* arg1, ULONG arg2, VOID* arg3); //0x68
    UCHAR (*AcceptAcpiNotification)(ULONG arg1, VOID* arg2);                //0x70
    struct _POP_FX_WORK_POOL PluginWorkPool;                                //0x78
}; 

NTSTATUS __fastcall PopPluginRegisterCrashdumpDevice(POP_FX_PLUGIN *Plugin, PEPHANDLE *DeviceHandle, POP_FX_DEVICE *FxDevice)
{
  unsigned __int8 (__fastcall *AcceptDeviceNotification)(unsigned int, void *);
  NTSTATUS result;
  __int64 DeviceCallback[3];

  AcceptDeviceNotification = Plugin->AcceptDeviceNotification;
  result = 0;
  DeviceCallback[1] = (__int64)DeviceHandle;
  DeviceCallback[0] = 0;
  if ( !AcceptDeviceNotification( 25u, DeviceCallback ) || !DeviceCallback[0] )
    return 0xFFFFFFFFC00000BB;
  FxDevice->PowerOnDumpDeviceCallback = (unsigned __int8 (__fastcall *)(_PEP_CRASHDUMP_INFORMATION *))DeviceCallback[0];
  
  return result;
}

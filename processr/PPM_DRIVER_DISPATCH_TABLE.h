// https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/ntos/procpowr/ppm_driver_dispatch_table.htm (goat)

struct PPM_DRIVER_DISPATCH_TABLE
{
	ULONG InterfaceVersion;
	NTSTATUS (*RegisterPerfStates)(PROCESSOR_PERF_STATES *);	
	VOID (*UpdatePerfStates)(PROCESSOR_PERF_STATES_UPDATE *);	
	NTSTATUS (*RegisterPerfCap)(PROCESSOR_CAP *);
	NTSTATUS (*RegisterSpmSettings)(HANDLE);	
	NTSTATUS (*RegisterIdleStates)(PROCESSOR_IDLE_STATES_EX *);	
	NTSTATUS (*RegisterIdleDomains)(PROCESSOR_IDLE_DOMAINS const *);
	NTSTATUS (*RegisterPlatformStates)(PLATFORM_IDLE_STATES *);
	NTSTATUS (*RegisterCoordinatedStates)(COORDINATED_IDLE_STATES *;	
	NTSTATUS (*RegisterVetoList)(PREREGISTERED_VETO_LIST *);
	NTSTATUS (*RemoveVetoBias)(VOID);	
	NTSTATUS (*UpdateProcessorIdleVeto)(PROCESSOR_IDLE_VETO *);	
	NTSTATUS (*UpdatePlatformIdleVeto)(PLATFORM_IDLE_VETO *);
	NTSTATUS (*RegisterPerfStatesHv)(PROCESSOR_PERF_STATES_HV const *);
	NTSTATUS (*RegisterPerfCapHv)(PROCESSOR_PERF_CAP_HV const *);	
	NTSTATUS (*RegisterIdleStatesHv)(PROCESSOR_IDLE_STATES_HV const *);
	NTSTATUS (*RegisterPerfStatesCountersHv)(PROCESSOR_PERF_STATES_COUNTERS_HV const *);
	NTSTATUS (*SetProcessorPep)(PVOID);
	
	NTSTATUS (*ParkPereferenceNotification)(PVOID, PEP_PPM_PARK_SELECTION_V2 *);
	NTSTATUS (*ParkMaskNotification)(PVOID, PEP_PPM_PARK_MASK *);
	NTSTATUS (*IdleSelectNotification)(PVOID, PEP_PPM_IDLE_SELECT *);
	NTSTATUS (*QueryPlatformStateNotification)(PVOID, PEP_PPM_QUERY_PLATFORM_STATE *, BOOLEAN);	
	NTSTATUS (*QueryCoordinatedDependencyNotification)(PVOID, PEP_PPM_QUERY_COORDINATED_DEPENDENCY *);
	NTSTATUS (*NotifyLpiCoordinatedStatesNotification)(PVOID, PEP_PPM_LPI_COORDINATED_STATES *);
	
	VOID (*RegisterEnergyEstimation)(PROCESSOR_COMPUTE_ENERGY_ROUTINE *, PROCESSOR_SNAP_ENERGYCOUNTERS_ROUTINE *);
	NTSTATUS (*RequestProcessorHalt)(ULONG,  PVOID,  PROCESSOR_HALT_ROUTINE *);
	UCHAR (*GetHgsEnablementStatus)(VOID);
	VOID (*DispatchHgsInterrupt)(VOID);	
	NTSTATUS (*ReadHiddenProcessorMsr)(ULONG, ULONG, ULONG64 *);
	NTSTATUS (*WriteHiddenProcessorMsr)(ULONG,  ULONG, ULONG64, ULONG64);	
	NTSTATUS (*ReadHiddenProcessorIoPort)(ULONG, USHORT, USHORT, ULONG *);
	NTSTATUS (*WriteHiddenProcessorIoPort)(ULONG, USHORT, USHORT, ULONG, ULONG);
	ULONG (*QueryPackageId)(ULONG);
	ULONG (*QueryPackageProcessorCount)(ULONG);
}

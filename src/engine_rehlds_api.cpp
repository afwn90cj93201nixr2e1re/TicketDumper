#include "precompiled.h"

IRehldsApi* g_RehldsApi;
IRehldsHookchains* g_RehldsHookchains;

bool RehldsApi_TryInit(CSysModule* engineModule, char* failureReason){
	if (!engineModule)return false;
	CreateInterfaceFn ifaceFactory = Sys_GetFactory(engineModule);
	if (!ifaceFactory)return false;
	int retCode = 0;
	g_RehldsApi = (IRehldsApi*)ifaceFactory(VREHLDS_HLDS_API_VERSION, &retCode);
	if (!g_RehldsApi)return false;
	int majorVersion = g_RehldsApi->GetMajorVersion();
	int minorVersion = g_RehldsApi->GetMinorVersion();
	if (majorVersion != REHLDS_API_VERSION_MAJOR)return false;
	if (minorVersion < REHLDS_API_VERSION_MINOR)return false;
	g_RehldsHookchains = g_RehldsApi->GetHookchains();
	return true;
}

bool RehldsApi_Init()
{
	char failReason[2048];

#ifdef WIN32
	CSysModule* engineModule = Sys_LoadModule("swds.dll");
	if (!RehldsApi_TryInit(engineModule, failReason))
	{
		engineModule = Sys_LoadModule("filesystem_stdio.dll");
		if (!RehldsApi_TryInit(engineModule, failReason))return false;
	}
#else
	CSysModule* engineModule = Sys_LoadModule("engine_i486.so");
	if (!RehldsApi_TryInit(engineModule, failReason))return false;
#endif

	return true;
}

void UTIL_LogPrintf(const char *fmt, ...)
{
	va_list argptr;
	char string[1024];

	va_start(argptr, fmt);
	vsprintf(string, fmt, argptr);
	va_end(argptr);

	ALERT(at_logged, "%s", string);
}

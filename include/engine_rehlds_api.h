#ifndef _INCLUDE_REHLDS_API_H_
#define _INCLUDE_REHLDS_API_H_

#pragma once

extern IRehldsApi* g_RehldsApi;
extern IRehldsHookchains* g_RehldsHookchains;
extern bool RehldsApi_Init();

extern qboolean Steam_NotifyClientConnect(IRehldsHook_Steam_NotifyClientConnect *chain,IGameClient *client,const void *pvSteam2Key, unsigned int ucbSteam2Key);

#endif //_INCLUDE_REHLDS_API_H_

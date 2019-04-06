/**
 * =============================================================================
 * GiveNamedItemEx for SourceMod (C)2019 Matthew J Dunn.   All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */
Handle g_hGiveNamedItem = null;
Handle g_hGiveNamedItemPost = null;
Handle g_hGiveNamedItemCall = null;

stock void HookPlayer(int client)
{
	DHookEntity(g_hGiveNamedItem, false, client);
	DHookEntity(g_hGiveNamedItemPost, true, client);
	SDKHook(client, SDKHook_WeaponEquip, OnWeaponEquip);
}

stock void UnhookPlayer(int client)
{
	SDKUnHook(client, SDKHook_WeaponEquip, OnWeaponEquip);
}

public bool HookOnGiveNamedItem()
{
	Handle config = LoadGameConfigFile("sdktools.games");
	if(config == null)
	{
		LogError("Unable to load game config file: sdktools.games");
		return false;
	}
	
	int offset = GameConfGetOffset(config, "GiveNamedItem");
	if (offset == -1)
	{
		CloseHandle(config);
		LogError("Unable to find offset 'GiveNamedItem' in game data 'sdktools.games'");
		return false;
	}
	
	/* POST HOOK */
	g_hGiveNamedItemPost = DHookCreate(offset, HookType_Entity, ReturnType_CBaseEntity, ThisPointer_CBaseEntity, OnGiveNamedItemPost);
	if (g_hGiveNamedItemPost == INVALID_HANDLE)
	{
		CloseHandle(config);
		LogError("Unable to post hook 'int CCSPlayer::GiveNamedItem(char const*, int, CEconItemView*, bool)'");
		return false;
	}
	
	DHookAddParam(g_hGiveNamedItemPost, HookParamType_CharPtr, -1, DHookPass_ByVal);
	DHookAddParam(g_hGiveNamedItemPost, HookParamType_Int, -1, DHookPass_ByVal);
	DHookAddParam(g_hGiveNamedItemPost, HookParamType_Int, -1, DHookPass_ByVal);
	DHookAddParam(g_hGiveNamedItemPost, HookParamType_Bool, -1, DHookPass_ByVal);
	DHookAddParam(g_hGiveNamedItemPost, HookParamType_Unknown, -1, DHookPass_ByVal);
	
	/* PRE HOOK */
	g_hGiveNamedItem = DHookCreate(offset, HookType_Entity, ReturnType_CBaseEntity, ThisPointer_CBaseEntity, OnGiveNamedItemPre);
	if (g_hGiveNamedItem == INVALID_HANDLE)
	{
		CloseHandle(config);
		LogError("Unable to hook 'int CCSPlayer::GiveNamedItem(char const*, int, CEconItemView*, bool)'");
		return false;
	}
	
	DHookAddParam(g_hGiveNamedItem, HookParamType_CharPtr, -1, DHookPass_ByVal);
	DHookAddParam(g_hGiveNamedItem, HookParamType_Int, -1, DHookPass_ByVal);
	DHookAddParam(g_hGiveNamedItem, HookParamType_Int, -1, DHookPass_ByVal);
	DHookAddParam(g_hGiveNamedItem, HookParamType_Bool, -1, DHookPass_ByVal);
	DHookAddParam(g_hGiveNamedItem, HookParamType_Unknown, -1, DHookPass_ByVal);
	
	/* SDK CALLER */
	StartPrepSDKCall(SDKCall_Player);
	PrepSDKCall_SetFromConf(config, SDKConf_Virtual, "GiveNamedItem");
	PrepSDKCall_SetReturnInfo(SDKType_CBaseEntity, SDKPass_Pointer);
	PrepSDKCall_AddParameter(SDKType_String, SDKPass_Pointer);
	PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain);
	g_hGiveNamedItemCall = EndPrepSDKCall();
	
	if (g_hGiveNamedItemCall == null)
	{
		CloseHandle(config);
		LogError("Unable to create call 'int CCSPlayer::GiveNamedItem(int , char const*)'");
		return false;
	}
	
	CloseHandle(config);
	return true;
}
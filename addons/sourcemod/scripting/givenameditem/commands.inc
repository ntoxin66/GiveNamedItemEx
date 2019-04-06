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
public void RegisterCommands()
{
	RegConsoleCmd("sm_givenameditem_weaponprops", OnGetWeaponProps);
}

public Action OnGetWeaponProps(int client, int args)
{
	int entity = GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
	if (entity < 1)
		return Plugin_Handled;
		
	PrintToConsole(client, "------======> OnGetWeaponProps()");
	PrintToConsole(client, "-------=======> m_iEntityLevel=%d", GetEntProp(entity, Prop_Send, "m_iEntityLevel"));
	PrintToConsole(client, "-------=======> m_iItemIDHigh=%d", GetEntProp(entity, Prop_Send, "m_iItemIDHigh"));
	PrintToConsole(client, "-------=======> m_iItemIDLow=%d", GetEntProp(entity, Prop_Send, "m_iItemIDLow"));
	PrintToConsole(client, "-------=======> m_iAccountID=%d", GetEntProp(entity, Prop_Send, "m_iAccountID"));
	PrintToConsole(client, "-------=======> m_iEntityQuality=%d", GetEntProp(entity, Prop_Send, "m_iEntityQuality"));
	PrintToConsole(client, "-------=======> m_bInitialized=%d", GetEntProp(entity, Prop_Send, "m_bInitialized"));
	PrintToConsole(client, "-------=======> m_iOriginalTeamNumber=%d", GetEntProp(entity, Prop_Send, "m_iOriginalTeamNumber"));
	PrintToConsole(client, "-------=======> m_nFallbackPaintKit=%d", GetEntProp(entity, Prop_Send, "m_nFallbackPaintKit"));
	PrintToConsole(client, "-------=======> m_nFallbackSeed=%d", GetEntProp(entity, Prop_Send, "m_nFallbackSeed"));
	PrintToConsole(client, "-------=======> m_flFallbackWear=%d", GetEntProp(entity, Prop_Send, "m_flFallbackWear"));
	PrintToConsole(client, "-------=======> m_nFallbackStatTrak=%d", GetEntProp(entity, Prop_Send, "m_nFallbackStatTrak"));
	return Plugin_Handled;
}
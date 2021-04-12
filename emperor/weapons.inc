/*
 * SourceMod Entity Projects
 * by: Entity
 *
 * Copyright (C) 2020 Kőrösfalvi "Entity" Martin
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) 
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#if defined _emperor_weapons_included
	#endinput
#endif
#define _emperor_weapons_included

#define	FlashbangOffsetForHC			15

public char C_sWeapon[MAXPLAYERS + 1][11][64]; 
public int C_WeaponCount[MAXPLAYERS + 1] = 0;
public int C_FlashCounter[MAXPLAYERS + 1] = 0;

/**
* Check if a weapon is valid or not
*
* @param weaponEntity	Entity
*
* @return				True if valid, otherwise false
*/
stock bool EMP_IsValidWeapon(int weaponEntity)
{
	if (weaponEntity > 4096 && weaponEntity != INVALID_ENT_REFERENCE)
		weaponEntity = EntRefToEntIndex(weaponEntity);
	
	if (!IsValidEdict(weaponEntity) || !IsValidEntity(weaponEntity) || weaponEntity == -1)
		return false;
	
	char weaponClass[64];
	EMP_SetWeaponClassname(weaponEntity, weaponClass, sizeof(weaponClass));
	
	return StrContains(weaponClass, "weapon_") == 0;
}

/**
* Check if a weapon is grenade by weapon index
*
* @param weaponEntity	Entity
*
* @return				True if grenade, otherwise false
*/
stock bool EMP_IsWeaponGrenade(int weaponEntity)
{
	char weaponClass[64];
	if (EMP_SetWeaponClassname(weaponEntity, weaponClass, sizeof(weaponClass)))
	{
		if (EMP_IsWeaponGrenade(weaponClass))
			return true;
	}

	return false;
}

/**
* Check if a weapon is grenade by classname
*
* @param weaponClass	Weapon Class to check
*
* @return				True if grenade, otherwise false
*/
stock bool EMP_IsWeaponGrenade(const char[] weaponClass)
{
	if (EMP_StrEquals(weaponClass, "weapon_decoy") || EMP_StrEquals(weaponClass, "weapon_flashbang") ||EMP_StrEquals(weaponClass, "weapon_hegrenade") ||EMP_StrEquals(weaponClass, "weapon_incgrenade") ||EMP_StrEquals(weaponClass, "weapon_molotov") ||EMP_StrEquals(weaponClass, "weapon_smokegrenade") ||EMP_StrEquals(weaponClass, "weapon_tagrenade"))
		return true;
	else
		return false;
}

/**
* Strip all weapons from the target and save them
*
* @param target				Client index to Save and remvoe the weapons from.
*/
stock void EMP_SaveWeapons(int target)
{
	C_FlashCounter[target] = 0;
	int counter = 0;
	
	C_FlashCounter[target] = GetEntProp(target, Prop_Data, "m_iAmmo", _, FlashbangOffsetForHC);
	if (EMP_IsValidClient(target))
	{
		while (GetEntPropEnt(target, Prop_Data, "m_hActiveWeapon") != -1)
		{
			int temp_weapon = GetEntPropEnt(target, Prop_Data, "m_hActiveWeapon");
			if (Weapon_IsValid(temp_weapon))
			{
				char temp_weapon_name[64];
				EMP_SetWeaponClassname(temp_weapon, temp_weapon_name, sizeof(temp_weapon_name));
				PrintToChatAll("Debug: saved  %s for %N", temp_weapon_name, target);
				RemoveEntity(temp_weapon);

				C_sWeapon[target][counter] = temp_weapon_name;
				
				counter++; C_WeaponCount[target]++;
			}
		}
	}
	Client_RemoveAllWeapons(target);
}

/**
* Restore Saved Weapons of the target
*
* @param target				Client index to Restore the saved weapons to.
*/
stock void EMP_RestoreWeapons(int target)
{
	if (EMP_IsValidClient(target))
	{
		char weapon_class[32];
		for (int g = 0; g <= C_WeaponCount[target]; g++)
		{
			Format(weapon_class, sizeof(weapon_class), C_sWeapon[target][g]);
			if (!StrEqual(weapon_class, "weapon_flashbang"))
			{
				if (String_StartsWith(weapon_class, "weapon_"))
				{
					if (!Client_HasWeapon(target, weapon_class))
					{
						PrintToChatAll("Debug: add %s - (%s) for %N", weapon_class, C_sWeapon[target][g], target);
						EMP_GiveWeapon(target, weapon_class);
						FormatEx(C_sWeapon[target][g], sizeof(C_sWeapon[]), NULL_STRING);
					}
				}
			}
			else
			{
				for (int x = 1; x <= C_FlashCounter[target]; x++)
				{
					EMP_GiveWeapon(target, weapon_class);
					FormatEx(C_sWeapon[target][g], sizeof(C_sWeapon[]), NULL_STRING);
				}
			}
		}
		
		C_WeaponCount[target] = 0;
	}
}

/**
* Sets the ClassName of a weapon
*
* @param Weapon entity
* @param buffer
* @param size
*/
stock int EMP_SetWeaponClassname(int weapon, char[] classname, int maxLen)
{
	if(!GetEdictClassname(weapon, classname, maxLen))
		return -1;

	switch(GetEntProp(weapon, Prop_Send, "m_iItemDefinitionIndex"))
	{
		case 23 : return strcopy(classname, maxLen, "weapon_mp5sd"); 
		case 60 : return strcopy(classname, maxLen, "weapon_m4a1_silencer");
		case 61 : return strcopy(classname, maxLen, "weapon_usp_silencer");
		case 63 : return strcopy(classname, maxLen, "weapon_cz75a");
		case 64 : return strcopy(classname, maxLen, "weapon_revolver");
		case 500: return strcopy(classname, maxLen, "weapon_bayonet");
		case 503: return strcopy(classname, maxLen, "weapon_knife_css");
		case 505: return strcopy(classname, maxLen, "weapon_knife_flip");
		case 506: return strcopy(classname, maxLen, "weapon_knife_gut");
		case 507: return strcopy(classname, maxLen, "weapon_knife_karambit");
		case 508: return strcopy(classname, maxLen, "weapon_knife_m9_bayonet");
		case 509: return strcopy(classname, maxLen, "weapon_knife_tactical");
		case 512: return strcopy(classname, maxLen, "weapon_knife_falchion");
		case 514: return strcopy(classname, maxLen, "weapon_knife_survival_bowie");
		case 515: return strcopy(classname, maxLen, "weapon_knife_butterfly");
		case 516: return strcopy(classname, maxLen, "weapon_knife_push");
		case 517: return strcopy(classname, maxLen, "weapon_knife_cord");
		case 518: return strcopy(classname, maxLen, "weapon_knife_canis");
		case 519: return strcopy(classname, maxLen, "weapon_knife_ursus");
		case 520: return strcopy(classname, maxLen, "weapon_knife_gypsy_jackknife");
		case 521: return strcopy(classname, maxLen, "weapon_knife_outdoor");
		case 522: return strcopy(classname, maxLen, "weapon_knife_stiletto");
		case 523: return strcopy(classname, maxLen, "weapon_knife_widowmaker");
		case 525: return strcopy(classname, maxLen, "weapon_knife_skeleton");
		default: GetEntityClassname(weapon, classname, maxLen); 
	}
	return -1;
}

/**
* Gives the weapon by the class name to the client
*
 * @param client		Client Index.
 * @param className		Weapon Classname String.
 * @param switchTo		If set to true, the client will switch the active weapon to the new weapon.
 * @param primaryAmmo	Primary ammo stock value from the client, if -1 the value is untouched.
 * @param secondaryAmmo	Secondary ammo stock value from the client, if -1 the value is untouched.
 * @param primaryClip	Primary ammo value in the weapon clip, if -1 the value is untouched.
 * @param secondaryClip	Secondary ammo value in the weapon clip, if -1 the value is untouched.
 * @return				Entity Index of the given weapon on success, INVALID_ENT_REFERENCE on failure.
*/
stock int EMP_EquipWeapon(int client, const char[] className, bool switchTo=true, int primaryAmmo=-1, int secondaryAmmo=-1, int primaryClip=-1, int secondaryClip=-1)
{
	if (EMP_IsValidClient(client, true, false))
		return Client_GiveWeaponAndAmmo(client, className, switchTo, primaryAmmo, secondaryAmmo, primaryClip, secondaryClip);
	else
		return INVALID_ENT_REFERENCE;
}

/**
* Gives the weapon by the class name to the client (With the player's skin)
*
 * @param client		Client Index.
 * @param className		Weapon Classname String.
 * @return				Entity Index of the given weapon on success, INVALID_ENT_REFERENCE on failure.
*/
stock int EMP_GiveWeapon(int client, const char[] className)
{
	if (EMP_IsValidClient(client, true, false))
	{
		int weapon_index;
		if (!Client_HasWeapon(client, className))
		{
			weapon_index = GivePlayerItem(client, className);
			EquipPlayerWeapon(client, weapon_index);
		}
		
		return weapon_index;
	}
	else
		return INVALID_ENT_REFERENCE;
}

/**
* Equip the player with a knife (With the player's skin)
*
* @param client				Client index
*/
stock void EMP_EquipKnife(int client)
{
	if (EMP_IsValidClient(client, true, false))
	{
		if (!Client_HasWeapon(client, "weapon_knife"))
		{
			int knife_index = GivePlayerItem(client, "weapon_knife");
			EquipPlayerWeapon(client, knife_index);
		}
	}
}

/**
* Check if the given entity is a knife or not
*
* @param entity			Index of the entity
*
* @return				True if the entity is a knife, otherwise false.
*/
stock bool EMP_IsKnife(int entity)
{
	char classname[32];
	if(EMP_SetWeaponClassname(entity, classname, sizeof(classname)))
		return EMP_IsKnifeClass(classname);
	return false;
}

/**
* Check if the given classname is a knife or not
*
* @param classname		Entity's classname to check
*
* @return				True if the classname is a knife, otherwise false.
*/
stock bool EMP_IsKnifeClass(const char[] classname)
{
	if ((StrContains(classname, "knife") > -1 && strcmp(classname, "weapon_knifegg") != 0) || StrContains(classname, "bayonet") > -1)
		return true;
	return false;
}

/**
* Removes all kind of malee from the client
*
* @param client				Client index
*/
stock void EMP_RemoveKnife(int client)
{
    int knife_index;
    for (int i = 0; i < 6; i++)
    {
		knife_index = GetPlayerWeaponSlot(client, i);
		if(IsValidEntity(knife_index) && i == 2)
		{
			RemovePlayerItem(client, knife_index);
		}
	}
}

/**
* Sets totally zero ammo to a weapon
*
* @param client				Client index
* @param weapon				Weapon Index
*/
stock void EMP_SetZeroAmmo(int client, int weapon)
{ 
	if (Weapon_IsValid(weapon) && EMP_IsValidClient(client))
	{
		EMP_SetReserveAmmo(client, weapon, 0);
		EMP_SetClipAmmo(weapon, 0);
	}
}

/**
* Sets totally zero ammo to a weapon
*
* @param entity			Entity index
*/
stock void EMP_SetShootingSound(int entity, char[] sound)
{ 
	SetEntPropString(entity, Prop_Data, "m_iszShootSound", sound); 
}

/**
* Sets Primary ammo to the weapon
*
* @param client				Client index
* @param weapon				Weapon Index
* @param ammo				Ammo Count
*/
stock void EMP_SetReserveAmmo(int client, int weapon, int ammo)
{
	if (Weapon_IsValid(weapon) && EMP_IsValidClient(client) && (ammo >= 0))
	{
		if(GetEngineVersion() == Engine_CSGO)
			SetEntProp(client, Prop_Send, "m_iPrimaryReserveAmmoCount", ammo);
		else
		{
			int emp_g_Offset_Ammo = FindSendPropInfo("CCSPlayer", "m_iAmmo");
			int iAmmoType = GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType");
			
			if(iAmmoType != -1)
				SetEntData(client, emp_g_Offset_Ammo+(iAmmoType*4), ammo, _, true);
		}
	}
}

/**
* Sets Clip ammo to the weapon
*
* @param weapon				Weapon Index
* @param ammo				Ammo Count
*/
stock void EMP_SetClipAmmo(int weapon, int ammo)
{
	if (Weapon_IsValid(weapon))
	{
		SetEntProp(weapon, Prop_Send, "m_iClip1", ammo);
		SetEntProp(weapon, Prop_Send, "m_iClip2", ammo);
	}
}
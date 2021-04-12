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

#if defined _emperor_game_included
	#endinput
#endif
#define _emperor_game_included

stock bool EMP_IsWarmUpPeriod()
{
	return view_as<bool>(GameRules_GetProp("m_bWarmupPeriod"));
}

stock bool EMP_IsFreezeTime()
{
	return view_as<bool>(GameRules_GetProp("m_bFreezePeriod"));
}

stock void EMP_HintMessage(char[] Caption, int Timeout = 5, int HintTarget, char[] Color = "255,0,0")
{
	Event HintEvent = CreateEvent("instructor_server_hint_create", true);

	HintEvent.SetString("hint_caption", Caption);
	HintEvent.SetInt("hint_timeout", Timeout);
	HintEvent.SetString("hint_color", Color);
	HintEvent.SetInt("hint_activator_userid", HintTarget);

	HintEvent.Fire();
}

/* Available icons
"icon_bulb"
"icon_caution"
"icon_alert"
"icon_alert_red"
"icon_tip"
"icon_skull"
"icon_no"
"icon_run"
"icon_interact"
"icon_button"
"icon_door"
"icon_arrow_plain"
"icon_arrow_plain_white_dn"
"icon_arrow_plain_white_up"
"icon_arrow_up"
"icon_arrow_right"
"icon_fire"
"icon_present"
"use_binding"
*/
stock void EMP_AdvancedHintMessage(char[] HintName = "", int HintTarget, char[] cmd = "", int HintActivator = 0, int HintTimeout = 5, char[] HintIcon = "icon_tip", char[] HintCaption = "", bool BehindWalls = false, char[] HintColor = "255,0,0", float IconOffset = 0.0, float HintRange = 0.0, int HintFlag = 1)
{
	Event HintEvent = CreateEvent("instructor_server_hint_create", true);
	
	HintEvent.SetString("hint_name", HintName);
	HintEvent.SetString("hint_replace_key", HintName);
	HintEvent.SetInt("hint_target", HintTarget);
	HintEvent.SetInt("hint_activator_userid", HintActivator);
	HintEvent.SetInt("hint_timeout", HintTimeout);
	HintEvent.SetString("hint_icon_onscreen", HintIcon);
	HintEvent.SetString("hint_icon_offscreen", HintIcon);
	HintEvent.SetString("hint_caption", HintCaption);
	HintEvent.SetString("hint_activator_caption", HintCaption);
	HintEvent.SetString("hint_color", HintColor);
	HintEvent.SetFloat("hint_icon_offset", IconOffset);
	HintEvent.SetFloat("hint_range", HintRange);
	HintEvent.SetInt("hint_flags", HintFlag);
	HintEvent.SetString("hint_binding", cmd);
	HintEvent.SetBool("hint_forcecaption", BehindWalls);

	HintEvent.Fire(); 
}

stock bool EMP_IsMenuAction(Menu menu, MenuAction action)
{
	switch (action)
	{
		case MenuAction_End:
		{
			EMP_FreeHandle(menu);
			return false;
		}
		default:
		{
			return true;
		}
	}
}

stock int EMP_GetToday(int unix_timestamp = 0)
{
    char m_szDate[32];
    FormatTime(m_szDate, 32, "%Y%m%d", unix_timestamp == 0 ? GetTime() : unix_timestamp);
    return StringToInt(m_szDate);
}

stock int EMP_GetTodayHours(int unix_timestamp = 0)
{
    char m_szDate[32];
    FormatTime(m_szDate, 32, "%H", unix_timestamp == 0 ? GetTime() : unix_timestamp);
    return StringToInt(m_szDate);
}

stock void EMP_GetDate(int unix_timestamp = 0, const char[] format = "%Y/%m/%d %H:%M:%S", char[] buffer, int maxLen)
{
    FormatTime(buffer, maxLen, format, unix_timestamp == 0 ? GetTime() : unix_timestamp);
}
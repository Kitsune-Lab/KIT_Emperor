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

#if defined _emperor_variables_included
	#endinput
#endif
#define _emperor_variables_included

#define EMP_STRING(%1) %1, sizeof(%1)

stock float EMP_GetPercentage(any all, any count) 
{
    return RoundFloat(FloatMul((float(number) / float(count)), 100.0)); 
}

/**
* Returns a really random int
*
* @param min				Minimum to generate int
* @param max				Maximum to generate int
* @return					Returns the random int
*/
stock int EMP_GetRandomInt(int min = 0, int max = 2147483647)
{
    int random = GetURandomInt();

    if(random == 0)
        random++;

    return RoundToCeil(float(random) / (float(2147483647) / float(max - min + 1))) + min - 1;
}

/**
* Returns an escaped string
*
* @param string				String to escape
* @param maxlen				Length of String
* @param name				Name escape for Discord Support
* @return					Returns the escaped string
*/
stock void EMP_EscapeString(char[] string, int maxlen, bool name = false)
{
    //For Discord support
	if(name)
	{
		ReplaceString(string, maxlen, "everyone", "everyonｅ");
		ReplaceString(string, maxlen, "here", "herｅ");
		ReplaceString(string, maxlen, "discordtag", "dｉscordtag");
	}

	ReplaceString(string, maxlen, "#", "＃");
	ReplaceString(string, maxlen, "@", "＠");
	ReplaceString(string, maxlen, "_", "ˍ");
	ReplaceString(string, maxlen, "'", "＇");
	ReplaceString(string, maxlen, "`", "＇");
	ReplaceString(string, maxlen, "~", "∽");
	ReplaceString(string, maxlen, "\"", "＂");
}


stock float EMP_GetRandomFloat(float min = 0.0, float max = 5201314.0)
{
    return (GetURandomFloat() * (max  - min)) + min;
}

/**
* Converts Int to Bool
*
* @param input				The int to set to bool
* @return					return the bool value
*/
stock bool EMP_IntToBool(int input)
{
	return !!input;
}

/**
* Frees the handle correctly
*
* @param handle				The handle to free
*/
stock void EMP_FreeHandle(Handle &handle)
{
    if(handle != null)
    {
        delete handle;
    }
}

/**
* Stops the timer correctly
*
* @param timer				The timer to stop
*/
stock void EMP_StopTimer(Handle &handle)
{
    if(handle != null)
    {
        KillTimer(handle);
        handle = null;
    }
}

/**
* Generates a random string
*
* @param buffer				Buffer to save the string into
* @param maxLen				The maximum length of the string
*/
stock void EMP_RandomString(char[] buffer, int maxLen)
{
    maxLen--;

    char random[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int randlen = strlen(random) - 1;

    int n = 0;
    int c = 0;

    while(n < maxLen)
    {
        if(random[0] == '\0')
        {
            c = GetRandomInt(33, 126);
            buffer[n] = c;
        }
        else
        {
            c = GetRandomInt(0, randlen);
            buffer[n] = random[c];
        }

        n++;
    }

    buffer[maxLen] = '\0';
}

stock void EMP_RandomStringEx(const char[] random, char[] buffer, int maxLen)
{
    maxLen--;
    
    int randlen = strlen(random);

    int n = 0;
    int c = 0;

    while(n < maxLen)
    {
        c = GetRandomInt(0, randlen);
        buffer[n++] = random[c];
    }

    buffer[maxLen] = '\0';
}

/**
* Checks if the string equals
*
* @param input				String to set to lower case
* @param substring			Buffer to save the string into
* @param caseSensitive		Works as case sensitive
*/
stock bool EMP_StrEquals(const char[] string, char[] substring, bool caseSensitive = false)
{
    if (strcmp(string, substring, caseSensitive) == 0)
		return true;
	else
		return false;
}

stock void EMP_ToLower(const char[] input, char[] output, int size)
{
    size--;
    output[0] = '\0';
    int x = 0;
    while(input[x] != '\0' && x < size)
    {
        output[x] = CharToLower(input[x]);
        x++;
    }
    output[x] = '\0';
}

stock void EMP_ToUpper(const char[] input, char[] output, int size)
{
    size--;
    output[0] = '\0';
    int x = 0;
    while(input[x] != '\0' && x < size)
    {
        output[x] = CharToUpper(input[x]);
        x++;
    }
    output[x] = '\0';
}

/**
* Checks if the given string contains only numbers or not
*
* @param buffer				String of the command to check
* @return					True if only numbers, otherwise false
*/
stock bool EMP_IsInteger(char[] buffer)
{
    for (int i = 0; i < strlen(buffer); i++)
    {
        if (!IsCharNumeric(buffer[i]) )
            return false;
    }

    return true;    
}
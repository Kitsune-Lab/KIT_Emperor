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

#if defined _emperor_sql_included
	#endinput
#endif
#define _emperor_sql_included

/**
* Advanced Table Creation with Emperor
*
* @param databasae			Database to start the query with
* @param Callback			Callback to send the return (Default: No return)
* @param TableName			Table name
* @param Data				Column data
* @param Prefix				Prefix for the table (Default: No Prefix)
* @param Engine				Engien to use (Default: MyISAM)
* @param Charset			Charset to use (Default: utf8)
*/
stock void EMP_SQL_CreateTable(Database database, any Callback, char[] TableName, char[] Data, char[] Prefix = "", char[] Engine = "MyISAM", char[] Charset = "utf8")
{
    char EMP_QueryBuffer[2048];
	database.Format(EMP_STRING(EMP_QueryBuffer), "CREATE TABLE IF NOT EXISTS `%s%s`(%s) ENGINE = %s DEFAULT CHARSET = %s;", Prefix, TableName, Data, Engine, Charset);
	database.Query(Callback, EMP_QueryBuffer, DBPrio_High);
}

/**
* Delete Table
*
* @param databasae			Database to start the query with
* @param Callback			Callback to send the return (Default: No return)
* @param TableName			Table name
* @param Prefix				Prefix for the table (Default: No Prefix)
*/
stock void EMP_SQL_DeleteTable(Database database, any Callback, char[] TableName, char[] Prefix = "")
{
	char EMP_QueryBuffer[256];
	database.Format(EMP_STRING(EMP_QueryBuffer), "DROP TABLE `%s%s`;", Prefix, TableName);
	database.Query(Callback, EMP_QueryBuffer, DBPrio_High);
}

/**
* Advanced Delete Row
*
* @param databasae			Database to start the query with
* @param Callback			Callback to send the return (Default: No return)
* @param TableName			Table name
* @param Prefix				Prefix for the table (Default: No Prefix)
* @param Condition			Conditions to delete the row
*/
stock void EMP_SQL_DeleteRow(Database database, int client = 0, any Callback, char[] TableName, char[] Prefix = "", char[] Condition)
{
	char EMP_QueryBuffer[1024];
	database.Format(EMP_STRING(EMP_QueryBuffer), "DELETE FROM `%s%s` WHERE %s;", Prefix, TableName, Condition);
	database.Query(Callback, EMP_QueryBuffer, GetClientUserId(client));
}

/**
* Delete all rows
*
* @param databasae			Database to start the query with
* @param Callback			Callback to send the return (Default: No return)
* @param TableName			Table name
* @param Prefix				Prefix for the table (Default: No Prefix)
*/
stock void EMP_SQL_DeleteAllRow(Database database, any Callback, char[] TableName, char[] Prefix = "")
{
	char EMP_QueryBuffer[1024];
	database.Format(EMP_STRING(EMP_QueryBuffer), "DELETE FROM `%s%s`;", Prefix, TableName);
	database.Query(Callback, EMP_QueryBuffer);
}

/**
* Advanced Update
*
* @param databasae			Database to start the query with
* @param Callback			Callback to send the return (Default: No return)
* @param TableName			Table name
* @param Prefix				Prefix for the table (Default: No Prefix)
* @param Set				What to set and how
* @param Condition			Conditions to update row(s)
*/
stock void EMP_SQL_Update(Database database, int client = 0, char[] TableName, char[] Prefix = "", char[] Set, char[] Condition)
{
	char EMP_QueryBuffer[1024];
	database.Format(EMP_STRING(EMP_QueryBuffer), "UPDATE `%s%s` SET %s WHERE %s;", Prefix, TableName, Set, Condition);
	database.Query(EMP_Nothing_Callback, EMP_QueryBuffer, GetClientUserId(client));
}

stock char EMP_SQL_RandomInt(int min, int max)
{
	char buffer[128];
	FormatEx(buffer, sizeof(buffer), "(ABS(CHECKSUM(NEWID()) % (%d - %d - 1)) + %d)" max, min, min);
	return buffer;
}

/**
* Advanced Insert
*
* @param databasae			Database to start the query with
* @param Callback			Callback to send the return (Default: No return)
* @param TableName			Table name
* @param Prefix				Prefix for the table (Default: No Prefix)
* @param Set				What to set and how
* @param Condition			Conditions to update row(s)
*/
stock void EMP_SQL_Insert(Database database, int client = 0, any Callback, char[] TableName, char[] Prefix = "", char[] Colummns, char[] Values)
{
	char EMP_QueryBuffer[1024];
	database.Format(EMP_STRING(EMP_QueryBuffer), "INSERT INTO `%s%s` (%s) VALUES (%s);", Prefix, TableName, Colummns, Values);
	database.Query(Callback, EMP_QueryBuffer, GetClientUserId(client));
}

/**
* Advanced Select
*
* @param databasae			Database to start the query with
* @param Callback			Callback to send the return (Default: No return)
* @param TableName			Table name
* @param Prefix				Prefix for the table (Default: No Prefix)
* @param Select				What to select from a row(s)
* @param Condition			Conditions to select row(s)
*/
stock void EMP_SQL_Select(Database database, int client = 0, any Callback, char[] TableName, char[] Prefix = "", char[] Select = "*", char[] Condition = "")
{
	char EMP_QueryBuffer[512];
	if (strlen(Condition) > 0)
		database.Format(EMP_STRING(EMP_QueryBuffer), "SELECT %s FROM `%s%s` WHERE %s;", Select, Prefix, TableName, Condition);
	else
		database.Format(EMP_STRING(EMP_QueryBuffer), "SELECT %s FROM `%s%s`;", Select, Prefix, TableName);
	database.Query(Callback, EMP_QueryBuffer, GetClientUserId(client));
}

/**
* Zero Callback for no data
*/
public void EMP_Nothing_Callback(Database database, DBResultSet result, char[] error, any data)
{
	if(result == null)
		LogError("Error: %s", error);
}
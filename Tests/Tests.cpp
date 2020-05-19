// Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Tests.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include "common/SQLiteWrapper.h"
#include "common/Database.h"
#include "common/DatabaseException.h"
#include "common/PreparedStmt.h"
#include "Common/Security_Strings.h"

int main(int argc, char* argv[])
{
	SQLite::Database testDB("./testDB.sql");
	try
	{
		testDB.Open();
		testDB.SetBusyTimeout(100000);
	}
	catch (SQLite::DatabaseException ex)
	{
		std::cerr << ex.ToString() << std::endl;
	}



	SQLite::Database testDB2("./testDB2.sql");
	try
	{
		bool bret = testDB2.Open();
		if (bret == false)
		{
			std::cout << "Open failed" << std::endl;
			return 0;
		}

		testDB2.SetBusyTimeout(100000);
		testDB2.CreateAdminUser();
		testDB2.Close();

		SQLite::Database testDB2_bis("./testDB2.sql");
		//bret = testDB2_bis.Open();
		//if (bret == false)
		//{
		//	std::cout << "Open failed" << std::endl;
		//	return 0;
		//}
		std::string user = UFM_SQLITE_USER;
		std::string password = UFM_SQLITE_PASSWORD;
		bret = testDB2_bis.OpenEx(user.c_str(), password.c_str());
		if (bret == false)
		{
			std::cout << "OpenEx failed" << std::endl;
			return 0;
		}

		int rows = 0;
		int retValue = testDB2_bis.ExecuteCommand("create table testinsert ( pkey integer primary key, f2 text, f3 real);", rows);
		if (retValue != SQLITE_OK)
		{
			std::cout << "ExecuteCommand failed!" << std::endl;
		}
		testDB2_bis.Close();
	}
	catch (SQLite::DatabaseException ex)
	{
		std::cerr << ex.ToString() << std::endl;
	}


	try
	{
		int rows = 0;
		testDB.ExecuteCommand("create table testinsert ( pkey integer primary key, f2 text, f3 real);", rows);
	}
	catch (SQLite::DatabaseException ex)
	{
		std::cerr << ex.ToString() << std::endl;
	}

	try
	{
		for (int i = 0; i < 10; i++)
		{
			sqlite_int64 ID = testDB.InsertAndReturnID("insert into \"testinsert\" (\"f2\",\"f3\") values (\"toto\",\"777\")");
			std::cout << "Inserted row :" << ID << std::endl;
		}
	}
	catch (SQLite::DatabaseException ex)
	{
		std::cerr << ex.ToString() << std::endl;
	}

	try
	{
		int numrow = testDB.ExecuteScalar("select count(*) from \"testinsert\"");
		std::cout << "elements in table  : \"testinsert\" : " << numrow << std::endl;
	}
	catch (SQLite::DatabaseException ex)
	{
		std::cerr << ex.ToString() << std::endl;
	}

	try
	{
		int rows = 0;
		SQLite::PreparedStmt createTable;
		createTable = testDB.CreatePreparedStmt("create table \"testinsert3\" ( pkey integer primary key, txt text, value real);");
		createTable.Execute(rows);
		std::cout << " number of parameters : " << createTable.GetNumberOfParams() << std::endl;
		createTable.Close();
	}
	catch (SQLite::DatabaseException ex)
	{
		std::cerr << ex.ToString() << std::endl;
	}

	try
	{
		SQLite::PreparedStmt insertInTable;
		insertInTable = testDB.CreatePreparedStmt("insert into \"testinsert3\" (\"txt\",\"value\") values (?,?)");;

		for (int i = 0; i < 10; i++)
		{
			insertInTable.SetStringParameter(1, "aloha");
			insertInTable.SetDoubleParameter(2, 12.34 + i);
			long ID;
			ID = insertInTable.ExecuteAndGetID();
			std::cout << "Inserted row :" << ID << std::endl;
			insertInTable.Reset();
		}
		insertInTable.Close();
	}
	catch (SQLite::DatabaseException ex)
	{
		std::cerr << ex.ToString() << std::endl;
	}

	try
	{
		int numrow = testDB.ExecuteScalar("select count(*) from testinsert3");
		std::cout << "elements in table  : \"testinsert3\" : " << numrow << std::endl;

		SQLite::Query q;
		int rows;
		q = testDB.ExecuteQuery("select * from testinsert3", rows);
		std::string col0 = q.GetColumnName(0);
		std::string col1 = q.GetColumnName(1);
		std::string col2 = q.GetColumnName(2);
		std::cout << "columns: " << col0 << ", " << col1 << ", " << col2 << std::endl;
		while (!q.IsEOF())
		{
			int vcol0 = q.GetIntValue(0);
			std::string vcol1 = q.GetStringValue(1);
			double vcol2 = q.GetDoubleValue(2);

			std::cout << vcol0 << ", ";
			std::cout << vcol1 << ", ";
			std::cout << vcol2 << std::endl;

			q.MoveNext();
		}
	}
	catch (SQLite::DatabaseException ex)
	{
		std::cerr << ex.ToString() << std::endl;
	}

	try
	{
		testDB.Close();
	}
	catch (SQLite::DatabaseException ex)
	{
		std::cerr << ex.ToString() << std::endl;
	}
	return 0;
}



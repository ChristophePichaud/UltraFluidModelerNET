// sqlitelib_client.cpp : définit le point d'entrée pour l'application console.
//

#include <stdio.h>
#include <iostream>
#include "DataModule/Common/SQLite/Database.h"
#include "DataModule/Common/SQLite/DatabaseException.h"
#include "DataModule/Common/SQLite/PreparedStmt.h"

int main(int argc, char * argv[])
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
		for (int i=0; i<10;i++) 
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
		std::cout << " number of parameters : "<<createTable.GetNumberOfParams() << std::endl;
		createTable.Close();
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
    testDB.ExecuteQuery("select * from testinsert3", q);
    std::string col0 = q.GetColumnName(0);
    std::string col1 = q.GetColumnName(1);
    std::string col2 = q.GetColumnName(2);
    std::cout << "columns: " << col0 <<", " << col1 <<", " << col2 << std::endl;
    while( ! q.IsEOF() )
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
		SQLite::PreparedStmt insertInTable;
		insertInTable = testDB.CreatePreparedStmt("insert into \"testinsert3\" (\"txt\",\"value\") values (?,?)");;
		
		for (int i=0; i<10;i++) 
    {
			insertInTable.SetStringParameter(1,"aloha");
			insertInTable.SetDoubleParameter(2,12.34+i);
			long ID;
      insertInTable.ExecuteAndGetID(ID);
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
		testDB.Close();
	} 
  catch (SQLite::DatabaseException ex) 
  {
		std::cerr << ex.ToString() << std::endl;
	}
  return 0;
}


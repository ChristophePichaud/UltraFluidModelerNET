#include "pch.h"
#include <string>
#include "common/SQLiteWrapper.h"
#include "common/sqlite.h"
#include <sqlite/sqlite3.h>
#include <sqlite/sqlite3userauth.h>
#include "common/Database.h"
#include "common/DatabaseException.h"
#include "common/Query.h"
#include "common/PreparedStmt.h"
#include "Common/Security_Strings.h"

namespace SQLite
{

	Database::Database(void)
	{
		m_DatabaseFileName = "";
		m_bOpen = false;
		m_instance = NULL;

		sqlite3_enable_shared_cache(true);
	}

	Database::Database(std::string filename)
	{
		m_DatabaseFileName = filename;
		m_bOpen = false;
		m_instance = NULL;

		sqlite3_enable_shared_cache(true);
	}

	Database::~Database(void)
	{
		Close();
	}

	void Database::SetDatabaseName(std::string fileName)
	{
		m_DatabaseFileName = fileName;
	}

	void Database::AddUser(std::string user, std::string password)
	{
		sqlite3_user_add(m_instance, user.c_str(), password.c_str(), password.size(), TRUE);
	}

	bool Database::AuthenticateUser(std::string user, std::string password)
	{
		sqlite3_user_authenticate(m_instance, user.c_str(), password.c_str(), password.size());
		return true;
	}

	bool Database::IsOpen()
	{
		bool retValue = (m_instance != NULL);
		retValue &= m_bOpen;
		return retValue;
	}

	sqlite3_stmt* Database::PrepareQuery(std::string query)
	{
		if (!IsOpen())
		{
			DatabaseException::ReportUserError("preparing query <" + query + "> ", " unable to open database due to initialization problem");
		}
		sqlite3_stmt* retValue = 0;
		const char* szTail = 0;
		int retCode = sqlite3_prepare_v2(m_instance, query.c_str(), -1, &retValue, &szTail);
		if (retCode != SQLITE_OK)
		{
			ReportError("preparing query <" + query + "> ");
		}
		return retValue;
	}

	void Database::SetFileName(std::string filename)
	{
		m_DatabaseFileName = filename;
	}

	bool Database::CreateAdminUser()
	{
		int retValue = sqlite3_open_v2(m_DatabaseFileName.c_str(), &m_instance, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
		m_bOpen = (retValue == SQLITE_OK);
		if (!m_bOpen)
		{
			ReportError(" opening database file " + m_DatabaseFileName + " ");
		}

		std::string user = UFM_SQLITE_USER;
		std::string password = UFM_SQLITE_PASSWORD;

		retValue = sqlite3_user_add(m_instance, user.c_str(), password.c_str(), password.size(), TRUE);
		if (retValue == SQLITE_OK)
			return true;

		return false;
	}

	bool Database::Open()
	{
		int retValue = sqlite3_open_v2(m_DatabaseFileName.c_str(), &m_instance, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
		m_bOpen = (retValue == SQLITE_OK);
		if (!m_bOpen)
		{
			ReportError(" opening database file " + m_DatabaseFileName + " ");
		}
		return m_bOpen;
	}

	bool Database::OpenEx(std::string user, std::string password)
	{
		int retValue = sqlite3_open_v2(m_DatabaseFileName.c_str(), &m_instance, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
		m_bOpen = (retValue == SQLITE_OK);
		if (!m_bOpen)
		{
			ReportError(" opening database file " + m_DatabaseFileName + " ");
		}

		retValue = sqlite3_user_authenticate(m_instance, user.c_str(), password.c_str(), password.size());
		if (retValue == SQLITE_OK)
			return true;

		return false;
	}

	bool Database::Close()
	{
		if (m_bOpen)
		{
			int retValue = sqlite3_close(m_instance);
			if (retValue != SQLITE_OK)
			{
				ReportError(" closing database file " + m_DatabaseFileName + " ");
			}
			else
			{
				m_bOpen = false;
			}
		}
		return (!m_bOpen);
	}

	void Database::ReportError(std::string context)
	{
		int errorCode = sqlite3_errcode(m_instance);
		std::string errorMessage = sqlite3_errmsg(m_instance);
		DatabaseException::ReportError(context, errorCode, errorMessage);
	}

	int Database::ExecuteSQL(std::string sql, int& rows)
	{
		return ExecuteCommand(sql, rows);
	}
		
	int Database::ExecuteCommand(std::string command, int& rows)
	{
		int retValue = 0;
		rows = 0;
		if (!IsOpen())
		{
			DatabaseException::ReportUserError("executing command <" + command + "> ", " unable to open database due to initialization problem");
		}
		char* error = 0;
		int returnCode = sqlite3_exec(m_instance, command.c_str(), 0, 0, &error);
		if (returnCode == SQLITE_OK)
		{
			retValue = sqlite3_changes(m_instance);
			rows = sqlite3_total_changes(m_instance);
		}
		else
		{
			std::string temp = sqlite3_errmsg(m_instance);
			DatabaseException::ReportError(" executing <" + command + "> ", returnCode, temp);
		}
		if (error != NULL)
		{
			sqlite3_free(error);
		}
		return retValue;
	}

	Query Database::ExecuteQuery(std::string query, int& rows)
	{
		Query retValue;
		rows = 0;
		if (!IsOpen())
		{
			DatabaseException::ReportUserError("executing query <" + query + "> ", " unable to open database due to initialization problem");
		}
		sqlite3_stmt* stmt = PrepareQuery(query);
		int returnCode = sqlite3_step(stmt);
		if (returnCode == SQLITE_DONE)
		{	// no row returned by query
			retValue = Query(stmt, m_instance, true, true);
			rows = sqlite3_total_changes(m_instance);
		}
		else if (returnCode == SQLITE_ROW)
		{ // query returns row(s)
			retValue = Query(stmt, m_instance, false, true);
			rows = sqlite3_total_changes(m_instance);
		}
		else
		{ // error generated by query
			std::string temp = sqlite3_errmsg(m_instance);
			sqlite3_finalize(stmt);
			DatabaseException::ReportError(" executing query <" + query + "> ", returnCode, temp);
		}
		return retValue;
	}

	PreparedStmt Database::CreatePreparedStmt(std::string statement)
	{
		sqlite3_stmt* stmt = PrepareQuery(statement);
		return PreparedStmt(m_instance, stmt);
	}

	int Database::ExecuteScalar(std::string query)
	{
		int retValue = 0;
		if (!IsOpen()) {
			DatabaseException::ReportUserError("executing executeScalarQuery <" + query + "> ", " unable to open database due to initialization problem");
		}
		// perform query
		int rows = 0;
		Query result = ExecuteQuery(query, rows);
		// check if a result is returned or not
		if (result.IsEOF())
		{  // must have at least one row 
			DatabaseException::ReportUserError(" executeScalarQuery <" + query + "> ", " No row returned ");
		}
		if (result.GetNumberOfColumns() < 1)
		{ // and one column
			DatabaseException::ReportUserError(" executeScalarQuery <" + query + "> ", " No column returned ");
		}
		// if result is returned, get the first column value
		retValue = result.GetIntValue(0);
		return retValue;
	}

	sqlite_int64 Database::GetLastRowID()
	{
		sqlite_int64 retValue = 0;
		retValue = sqlite3_last_insert_rowid(m_instance);
		return retValue;
	}

	void Database::SetBusyTimeout(int timeout)
	{
		if (!IsOpen()) {
			DatabaseException::ReportUserError("executing setBusyTimeout ", " unable to open database due to initialization problem");
		}
		int returnCode = sqlite3_busy_timeout(m_instance, timeout);
		if (returnCode != SQLITE_OK)
		{
			ReportError("executing setBusyTimeout ");
		}
	}

	sqlite_int64 Database::InsertAndReturnID(std::string sqlinsert)
	{
		sqlite_int64 retValue = 0;
		if (!IsOpen())
		{
			DatabaseException::ReportUserError("executing insert <" + sqlinsert + "> ", " unable to open database due to initialization problem");
		}
		char* error = 0;
		int returnCode = sqlite3_exec(m_instance, sqlinsert.c_str(), 0, 0, &error);
		if (returnCode == SQLITE_OK)
		{
			retValue = sqlite3_last_insert_rowid(m_instance);
		}
		else
		{
			std::string temp = error;
			if (error != NULL)
			{
				sqlite3_free(error);
			}
			DatabaseException::ReportError(" executing <" + sqlinsert + "> ", returnCode, temp);
		}
		if (error != NULL)
		{
			sqlite3_free(error);
		}
		return retValue;

	}

}
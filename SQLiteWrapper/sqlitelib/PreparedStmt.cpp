#include "pch.h"
#include "common/SQLiteWrapper.h"
#include "common/sqlite.h"
#include "common/PreparedStmt.h"
#include "common/DatabaseException.h"
#include "common/Query.h"

namespace SQLite
{

	PreparedStmt::PreparedStmt(void)
	{
		m_statement = 0;
		m_instance = 0;
		m_NumberOfParameters = 0;
	}

	PreparedStmt::PreparedStmt(sqlite3* instance, sqlite3_stmt* stmt)
	{
		m_statement = stmt;
		m_instance = instance;
		if (m_statement != NULL)
		{
			m_NumberOfParameters = sqlite3_bind_parameter_count(m_statement);
		}
		else
		{
			m_NumberOfParameters = 0;
		}
	}

	PreparedStmt::~PreparedStmt(void)
	{
	}

	PreparedStmt& PreparedStmt::operator=(const PreparedStmt& right)
	{
		m_statement = right.m_statement;
		m_instance = right.m_instance;
		m_NumberOfParameters = right.m_NumberOfParameters;
		const_cast<PreparedStmt&>(right).SetNull();
		return *this;
	}

	void PreparedStmt::SetStringParameter(int index, std::string value)
	{
		if (!IsStmtOpen())
		{
			DatabaseException::ReportUserError(" setting string parameter ", "bad statement");
		}
		if (!CheckParameter(index))
		{
			DatabaseException::ReportUserError(" setting string parameter ", "bad index");
		}
		int returnCode = sqlite3_bind_text(m_statement, index, value.c_str(), -1, SQLITE_TRANSIENT);
		if (returnCode != SQLITE_OK)
		{
			std::string temp = sqlite3_errmsg(m_instance);
			DatabaseException::ReportError(" setting string parameter ", returnCode, temp);
		}
	}

	void PreparedStmt::SetIntegerParameter(int index, int value)
	{
		if (!IsStmtOpen())
		{
			DatabaseException::ReportUserError("setting integer parameter", "bad statement");
		}
		if (!CheckParameter(index))
		{
			DatabaseException::ReportUserError("setting integer parameter", "bad index");
		}
		int returnCode = sqlite3_bind_int(m_statement, index, value);
		if (returnCode != SQLITE_OK)
		{
			std::string temp = sqlite3_errmsg(m_instance);
			DatabaseException::ReportError(" setting integer parameter ", returnCode, temp);
		}
	}

	void PreparedStmt::SetDoubleParameter(int index, double value)
	{
		if (!IsStmtOpen())
		{
			DatabaseException::ReportUserError(" setting double parameter ", "bad statement");
		}
		if (!CheckParameter(index))
		{
			DatabaseException::ReportUserError(" setting double parameter ", "bad index");
		}
		int returnCode = sqlite3_bind_double(m_statement, index, value);
		if (returnCode != SQLITE_OK)
		{
			std::string temp = sqlite3_errmsg(m_instance);
			DatabaseException::ReportError(" setting double parameter ", returnCode, temp);
		}
	}

	void PreparedStmt::SetInt64Parameter(int index, sqlite_int64 value)
	{
		if (!IsStmtOpen())
		{
			DatabaseException::ReportUserError(" setting int64 parameter ", "bad statement");
		}
		if (!CheckParameter(index))
		{
			DatabaseException::ReportUserError(" setting int64 parameter ", "bad index");
		}
		int returnCode = sqlite3_bind_int64(m_statement, index, value);
		if (returnCode != SQLITE_OK) {
			std::string temp = sqlite3_errmsg(m_instance);
			DatabaseException::ReportError(" setting int64 parameter ", returnCode, temp);
		}
	}

	void PreparedStmt::SetNullParameter(int index)
	{
		if (!IsStmtOpen())
		{
			DatabaseException::ReportUserError(" setting null parameter ", "bad statement");
		}
		if (!CheckParameter(index))
		{
			DatabaseException::ReportUserError(" setting null parameter ", "bad index");
		}
		int returnCode = sqlite3_bind_null(m_statement, index);
		if (returnCode != SQLITE_OK) {
			std::string temp = sqlite3_errmsg(m_instance);
			DatabaseException::ReportError(" setting null parameter ", returnCode, temp);
		}
	}

	void PreparedStmt::Reset()
	{
		if (!IsStmtOpen())
		{
			DatabaseException::ReportUserError(" reset parameter ", "bad statement");
		}
		int returnCode = sqlite3_reset(m_statement);
		if (returnCode != SQLITE_OK)
		{
			std::string temp = sqlite3_errmsg(m_instance);
			DatabaseException::ReportError(" reset parameter ", returnCode, temp);
		}
	}

	void PreparedStmt::Close()
	{
		if (IsStmtOpen())
		{
			int returnCode = sqlite3_finalize(m_statement);
			if (returnCode != SQLITE_OK)
			{
				std::string temp = sqlite3_errmsg(m_instance);
				DatabaseException::ReportError(" closing statement ", returnCode, temp);
			}
			m_statement = NULL;
		}

	}
	int PreparedStmt::Execute(int& rows)
	{
		int retValue = 0;
		rows = 0;
		if (!IsOpen())
		{
			DatabaseException::ReportUserError(" executing statement ", "bad database");
		}
		if (!IsStmtOpen())
		{
			DatabaseException::ReportUserError(" executing statement ", "bad statement");
		}
		// executing command
		int returnCode = sqlite3_step(m_statement);
		if (returnCode == SQLITE_DONE) {
			retValue = sqlite3_changes(m_instance);
			rows = sqlite3_total_changes(m_instance);
		}
		else
		{
			std::string temp = sqlite3_errmsg(m_instance);
			DatabaseException::ReportError(" executing statement ", returnCode, temp);
		}
		return retValue;
	}

	sqlite_int64 PreparedStmt::ExecuteAndGetID()
	{
		long retValue = 0;
		if (!IsOpen())
		{
			DatabaseException::ReportUserError(" executing statement and getting ID ", "bad database");
		}
		if (!IsStmtOpen())
		{
			DatabaseException::ReportUserError(" executing statement and getting ID ", "bad statement");
		}
		// executing command
		int returnCode = sqlite3_step(m_statement);
		if (returnCode == SQLITE_DONE)
		{
			retValue = (long)sqlite3_last_insert_rowid(m_instance);
		}
		else
		{
			std::string temp = sqlite3_errmsg(m_instance);
			DatabaseException::ReportError(" executing statement and getting ID ", returnCode, temp);
		}
		return retValue;
	}

	Query PreparedStmt::ExecuteAndGetQuery()
	{
		Query retValue;
		if (!IsOpen())
		{
			DatabaseException::ReportUserError(" executing statement and getting query ", "bad database");
		}
		if (!IsStmtOpen())
		{
			DatabaseException::ReportUserError(" executing statement and getting query ", "bad statement");
		}
		int returnCode = sqlite3_step(m_statement);
		if (returnCode == SQLITE_DONE)
		{	// no row returned by query
			retValue = Query(m_statement, m_instance, true, false);
		}
		else if (returnCode == SQLITE_ROW)
		{ // query returns row(s)
			retValue = Query(m_statement, m_instance, false, false);
		}
		else
		{ // error generated by query
			std::string temp = sqlite3_errmsg(m_instance);
			DatabaseException::ReportError(" executing statement and getting query ", returnCode, temp);
		}
		return retValue;
	}

}
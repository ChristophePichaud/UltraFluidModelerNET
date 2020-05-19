#include "Query.h"

Query::Query(void)
{
  m_statement = NULL;
  m_instance = NULL;
  m_NbCols = 0;
  m_bEOF = true;
  m_bDestroyStatement = true;
}

Query::~Query(void)
{
  Close();
}

Query::Query(sqlite3_stmt* stmt, sqlite3* instance,bool norows, bool ownstatement) 
{
	m_statement = stmt;
	m_instance = instance;
	m_bDestroyStatement = ownstatement;
	m_bEOF = norows;
	//compute number of row
	m_NbCols = sqlite3_column_count(m_statement);
}

void Query::Close() 
{
	if ((IsStmtOpen())&&(m_bDestroyStatement)) 
  {
		int returnCode = sqlite3_finalize(m_statement);
		if (returnCode != SQLITE_OK) 
    {
			std::string temp = sqlite3_errmsg(m_instance);
			DatabaseException::ReportError(" closing query ",returnCode,temp);
		}
		m_statement = NULL;
		
	}
}

Query& Query::operator=(const Query& query) 
{
	m_statement = query.m_statement;	
	m_instance = query.m_instance;		
	m_NbCols = query.m_NbCols;					
	m_bEOF = query.m_bEOF;					
	m_bDestroyStatement = query.m_bDestroyStatement;

  const_cast<Query&>(query).SetNull();
	return *this;	
} 

Query::Query(const Query & query)
{
	m_statement = query.m_statement;	
	m_instance = query.m_instance;		
	m_NbCols = query.m_NbCols;					
	m_bEOF = query.m_bEOF;					
	m_bDestroyStatement = query.m_bDestroyStatement;

  const_cast<Query&>(query).SetNull();
}

std::string Query::GetColumnName(int index) 
{
	std::string retValue="";
	if (!IsStmtOpen()) 
  {
		DatabaseException::ReportUserError("getting column name", "bad statement");
	}
	if (IsColumnIndexValid(index)) 
  {
		retValue=sqlite3_column_name(m_statement, index);
	} 
  else 
  {
		DatabaseException::ReportUserError("getting column name", "bad column index");
	}
	return retValue;
}

ColumnType Query::GetColumnType(int index) 
{
	ColumnType retValue;
	if (!IsStmtOpen()) 
  {
		DatabaseException::ReportUserError("getting column type", "bad statement");
	}
	if (IsColumnIndexValid(index)) 
  {
		retValue.SetType(sqlite3_column_type(m_statement, index));
	} 
  else 
  {
		DatabaseException::ReportUserError("getting column type", "bad column index");
	}
	return retValue;
}

double Query::GetDoubleValue(int index) 
{
	double retValue;
	if (!IsStmtOpen()) 
  {
		DatabaseException::ReportUserError("getDoubleValue", "bad statement");
	}
	if (IsColumnIndexValid(index)) 
  {
		retValue=sqlite3_column_double(m_statement, index);
	} 
  else 
  {
		DatabaseException::ReportUserError("getDoubleValue", "bad column index");
	}
	return retValue; 
}        

int	Query::GetIntValue(int index)
{
	int retValue;
	if (!IsStmtOpen()) 
  {
		DatabaseException::ReportUserError("getIntValue", "bad statement");
	}
	if (IsColumnIndexValid(index)) 
  {
		retValue=sqlite3_column_int(m_statement, index);
	} 
  else 
  {
		DatabaseException::ReportUserError("getIntValue", "bad column index");
	}
	return retValue; 
}        

std::string Query::GetStringValue(int index)
{
	std::string retValue;
	if (!IsStmtOpen()) 
  {
		DatabaseException::ReportUserError("getStringValue", "bad statement");
	}
	if (IsColumnIndexValid(index)) 
  {
		retValue=std::string((const char *)sqlite3_column_text(m_statement, index));
	} 
  else 
  {
		DatabaseException::ReportUserError("getStringValue", "bad column index");
	}
	return retValue; 
}  

void Query::MoveNext() 
{
	if (!IsStmtOpen()) 
  {
		DatabaseException::ReportUserError("nextRecord", "bad statement");
	}
	int returnCode = sqlite3_step(m_statement); // avance next record
	
	if (returnCode == SQLITE_DONE) 
  {		// no more record
		m_bEOF = true;
	} 
  else if (returnCode == SQLITE_ROW) 
  {	// normal behavior
	} 
  else 
  {                                // error, reporting
		std::string temp = sqlite3_errmsg(m_instance);
		DatabaseException::ReportError(" closing query ",returnCode,temp);
	}
}


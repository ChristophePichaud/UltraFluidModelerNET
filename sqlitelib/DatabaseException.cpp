#include "DatabaseException.h"
#include <sqlite/sqlite3.h>
#include <sstream>
#include <iostream>

DatabaseException::DatabaseException(int code, std::string context, std::string message)
{
  m_ErrorCode = code;
  m_Context = context;
  m_ErrorMessage = message;

  m_ErrorCodeString = MatchErrorCode();
}

DatabaseException::DatabaseException(std::string context, std::string message)
{
  m_Context = context;
  m_ErrorMessage = message;
  m_ErrorCode = 0;
  m_ErrorCodeString = "no message";
}

DatabaseException::~DatabaseException(void)
{
}

std::string DatabaseException::MatchErrorCode() 
{
	std::string retValue ="";
	switch (m_ErrorCode) {
			
		case SQLITE_OK : retValue="SQLITE_ERROR";				/* Successful result */ 
			break;
		case SQLITE_ERROR : retValue="SQLITE_ERROR";			/* SQL error or missing database */ 
			break;
		case SQLITE_INTERNAL : retValue="SQLITE_INTERNAL";      /* NOT USED. Internal logic error in SQLite */ 
			break;
		case SQLITE_PERM : retValue="SQLITE_PERM";				/* Access permission denied */ 
			break;
		case SQLITE_ABORT : retValue="SQLITE_ABORT";			/* Callback routine requested an abort */ 
			break;
		case SQLITE_BUSY : retValue="SQLITE_BUSY";				/* The database file is locked */ 
			break;
		case SQLITE_LOCKED : retValue="SQLITE_LOCKED";			/* A table in the database is locked */ 
			break;
		case SQLITE_NOMEM  : retValue="SQLITE_NOMEM";			/* A malloc() failed */ 
			break;
		case SQLITE_READONLY : retValue="SQLITE_READONLY";		/* Attempt to write a readonly database */
			break;
		case SQLITE_INTERRUPT : retValue="SQLITE_INTERRUPT";	/* Operation terminated by sqlite3_interrupt()*/
			break;
		case SQLITE_IOERR : retValue="SQLITE_IOERR";			/* Some kind of disk I/O error occurred */ 
			break;
		case SQLITE_CORRUPT : retValue="SQLITE_CORRUPT";		/* The database disk image is malformed */ 
			break;
		case SQLITE_NOTFOUND : retValue="SQLITE_NOTFOUND";		/* NOT USED. Table or record not found */ 
			break;
		case SQLITE_FULL : retValue="SQLITE_FULL";				/* Insertion failed because database is full */
			break;
		case SQLITE_CANTOPEN : retValue="SQLITE_CANTOPEN";		/* Unable to open the database file */
			break;
		case SQLITE_PROTOCOL : retValue="SQLITE_PROTOCOL";		/* NOT USED. Database lock protocol error */
			break;
		case SQLITE_EMPTY : retValue="SQLITE_EMPTY";			/* Database is empty */
			break;
		case SQLITE_SCHEMA : retValue="SQLITE_SCHEMA";			/* The database schema changed */ 
			break;
		case SQLITE_TOOBIG : retValue="SQLITE_TOOBIG";			/* String or BLOB exceeds size limit */
			break;
		case SQLITE_CONSTRAINT : retValue="SQLITE_CONSTRAINT";	/* Abort due to constraint violation */
			break;
		case SQLITE_MISMATCH : retValue="SQLITE_MISMATCH";		/* Data type mismatch */
			break;
		case SQLITE_MISUSE : retValue="SQLITE_MISUSE";			/* Library used incorrectly */ 
			break;
		case SQLITE_NOLFS : retValue="SQLITE_NOLFS";			/* Uses OS features not supported on host */ 
			break;
		case SQLITE_AUTH : retValue="SQLITE_AUTH";				/* Authorization denied */
			break;
		case SQLITE_FORMAT : retValue="SQLITE_FORMAT";			/* Auxiliary database format error */ 
			break;
		case SQLITE_RANGE : retValue="SQLITE_RANGE";			/* 2nd parameter to sqlite3_bind out of range */ 
			break;
		case SQLITE_NOTADB : retValue="SQLITE_NOTADB";			/* File opened that is not a database file */ 
			break;
		case SQLITE_ROW : retValue="SQLITE_ROW";				/* sqlite3_step() has another row ready */ 
			break;
		case SQLITE_DONE : retValue="SQLITE_DONE";				/* sqlite3_step() has finished executing */
			break;
		default:
			retValue="UNKNOWN";
	}
	return retValue;
}

std::string DatabaseException::ToString()
{
	std::string retValue;  
	std::stringstream ss;
	ss << m_Context << "[" << m_ErrorCode << "] : [" << m_ErrorCodeString + "] : " << m_ErrorMessage << std::endl;
	retValue = ss.str();
	return retValue; 
}

bool DatabaseException::ReportError(std::string context, int code, std::string message)
{
	bool retValue = true;
	throw DatabaseException(code, context, message);
}

bool DatabaseException::ReportUserError(std::string context, std::string message)
{
	bool retValue = true;
	throw DatabaseException(context, message);
	return retValue;
}


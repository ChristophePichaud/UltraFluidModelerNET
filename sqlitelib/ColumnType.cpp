#include "ColumnType.h"
#include <sqlite/sqlite3.h>

ColumnType::ColumnType(void)
{
  m_bInteger = false;
  m_bFloat = false;
  m_bBlob = false;
  m_bNull = false;
  m_bText = false;
}

ColumnType::ColumnType(int type)
{
  SetType(type);
}

ColumnType::~ColumnType(void)
{
}

void ColumnType::SetType(int type)
{
	m_bInteger = (type==SQLITE_INTEGER);
	m_bFloat = (type==SQLITE_FLOAT);
	m_bBlob = (type==SQLITE_BLOB);
	m_bNull = (type==SQLITE_NULL);
	m_bText = (type==SQLITE_TEXT);
}

std::string ColumnType::ToString()
{
	std::string retValue="unknown";
	if(m_bInteger)	{retValue="integer";}	
	if(m_bFloat)		{retValue="float";}
	if(m_bBlob)		{retValue="blob";}
	if(m_bNull)		{retValue="null";}
	if(m_bText)		{retValue="text";}
	return retValue;
}
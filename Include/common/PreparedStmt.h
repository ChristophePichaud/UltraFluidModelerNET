#ifndef __PreparedStmt_H__
#define __PreparedStmt_H__

#include <sqlite/sqlite3.h>
#include <string>
#include "Query.h"

namespace SQLite
{

    class SQLITEWRAPPER_API PreparedStmt
    {
    public:
        PreparedStmt(void);
        PreparedStmt(sqlite3* instance, sqlite3_stmt* stmt);
        virtual ~PreparedStmt(void);

    public:
        PreparedStmt& operator=(const PreparedStmt& right);
        void SetStringParameter(int index, std::string value);
        void SetIntegerParameter(int index, int value);
        void SetDoubleParameter(int index, double value);
        void SetInt64Parameter(int index, sqlite_int64 value);
        void SetNullParameter(int index);
        void Reset();
        void Close();
        int Execute(int& rozs);
        sqlite_int64 ExecuteAndGetID();
        Query ExecuteAndGetQuery();

    protected:
        sqlite3_stmt* m_statement;
        sqlite3* m_instance;
        int m_NumberOfParameters;

    public:
        inline bool IsOpen() { return m_instance != NULL; }
        inline bool IsStmtOpen() { return m_statement != NULL; }
        inline void SetNull() { m_statement = NULL; }
        inline bool CheckParameter(int index) { return (index <= m_NumberOfParameters); };
        inline int  GetNumberOfParams() { return m_NumberOfParameters; }
    };

}

#endif //__PreparedStmt_H__

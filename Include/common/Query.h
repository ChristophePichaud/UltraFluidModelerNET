#ifndef __Query_H__
#define __Query_H__

#include <string>
#include <sqlite/sqlite3.h>
#include "common/ColumnType.h"
#include "common/DatabaseException.h"

namespace SQLite
{

    class SQLITEWRAPPER_API Query
    {
    public:
        Query(void);
        virtual ~Query(void);
        Query(sqlite3_stmt* stmt, sqlite3* instance, bool norows, bool ownstatement = true);
        Query(const Query& query);
        Query& operator=(const Query& query);

    protected:
        sqlite3_stmt* m_statement;
        sqlite3* m_instance;
        int m_NbCols;
        bool m_bEOF;
        bool m_bDestroyStatement;

    protected:
        inline bool IsOpen() { return m_instance != NULL; }
        inline bool IsStmtOpen() { return m_statement != NULL; }
        inline void SetNull() { m_statement = NULL; }

    public:
        inline bool IsEOF() { return m_bEOF; }
        inline bool IsColumnIndexValid(int index) { return (((index >= 0) && (index <= (m_NbCols - 1)))); }
        inline int GetNumberOfColumns() { return m_NbCols; }
        void Close();
        std::string GetColumnName(int index);
        ColumnType GetColumnType(int index);
        double GetDoubleValue(int index);
        int GetIntValue(int index);
        std::string GetStringValue(int index);
        void MoveNext();
    };

}

#endif //__Query_H__

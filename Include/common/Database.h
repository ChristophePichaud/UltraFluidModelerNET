#ifndef __Database_H__
#define __Database_H__

#include <string>
#include <sqlite/sqlite3.h>

namespace SQLite
{

    class Query;
    class PreparedStmt;

    class SQLITEWRAPPER_API Database
    {
    public:
        Database(void);
        Database(std::string filename);
        virtual ~Database(void);

    public:
        bool IsOpen();
        sqlite3_stmt* PrepareQuery(std::string query);
        void SetFileName(std::string filename);
        bool Open();
        bool Close();
        void ReportError(std::string context);
        int ExecuteCommand(std::string command, int& rows);
        Query ExecuteQuery(std::string query, int& rows);
        PreparedStmt CreatePreparedStmt(std::string statement);
        int ExecuteScalar(std::string query);
        sqlite_int64 GetLastRowID();
        void SetBusyTimeout(int timeout);
        sqlite_int64 InsertAndReturnID(std::string sqlinsert);

    protected:
        std::string m_DatabaseFileName;
        bool m_bOpen;
        sqlite3* m_instance;
    };

}
#endif //__Database_H__

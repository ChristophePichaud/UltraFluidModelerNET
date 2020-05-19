#ifndef __DatabaseException_H__
#define __DatabaseException_H__

#include <string>

namespace SQLite
{

    class SQLITEWRAPPER_API DatabaseException
    {
    public:
        DatabaseException(int code, std::string context, std::string message);
        DatabaseException(std::string context, std::string message);
        virtual ~DatabaseException(void);

    protected:
        int m_ErrorCode;
        std::string m_ErrorCodeString;
        std::string m_Context;
        std::string m_ErrorMessage;

        std::string MatchErrorCode();

    public:
        inline int GetErrorCode() { return m_ErrorCode; }
        inline std::string GetErrorCodeString() { return m_ErrorCodeString; }
        inline std::string GetContext() { return m_Context; }
        inline std::string GetErrorMessage() { return m_ErrorMessage; }

        std::string ToString();
        static bool ReportError(std::string context, int code, std::string message);
        static bool ReportUserError(std::string context, std::string message);
    };

}

#endif //__DatabaseException_H__

#ifndef __ColumnType_H__
#define __ColumnType_H__

#include <string>

namespace SQLite
{

    class SQLITEWRAPPER_API ColumnType
    {
    public:
      ColumnType(void);
      ColumnType(int type);
      virtual ~ColumnType(void);

    protected:
      bool m_bInteger;
      bool m_bFloat;
      bool m_bBlob;
      bool m_bNull;
      bool m_bText;

    public:
      inline bool IsInteger() { return m_bInteger; }
      inline bool IsFloat() { return m_bFloat; }
      inline bool IsBlob() { return m_bBlob; }
      inline bool IsNull() { return m_bNull; }
      inline bool IsText() { return m_bText; }

      void SetType(int type);
      std::string ToString();
	    ColumnType& operator= (const ColumnType& source);
    };

}

#endif //__ColumnType_H__

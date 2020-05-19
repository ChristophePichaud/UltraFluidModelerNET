// SQLiteWrapper.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "common/SQLiteWrapper.h"


// This is an example of an exported variable
SQLITEWRAPPER_API int nSQLiteWrapper=0;

// This is an example of an exported function.
SQLITEWRAPPER_API int fnSQLiteWrapper(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CSQLiteWrapper::CSQLiteWrapper()
{
    return;
}

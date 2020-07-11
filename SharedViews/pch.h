// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
using namespace std;


#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdlgs.h>			// MFC support for common dialogs
#include <afxdialogex.h>

#include "common/SQLiteWrapper.h"
#include "common/Database.h"
#include "common/DatabaseException.h"
#include "common/PreparedStmt.h"
#include "Common/Security_Strings.h"

#ifdef _WIN64
    #ifdef _DEBUG
        #pragma comment(lib, "sqlited.lib")
        #pragma comment(lib, "SQLiteWrapperd.lib")
    #else    
        #pragma comment(lib, "sqlite.lib")
        #pragma comment(lib, "SQLiteWrapper.lib")
    #endif
#endif

#endif //PCH_H

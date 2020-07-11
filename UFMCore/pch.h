// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS TRUE

// add headers that you want to pre-compile here
#include "framework.h"

#include <GdiPlus.h>
using namespace Gdiplus;

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
#include <afxwinappex.h>
#include <afxcontrolbars.h>     // MFC support for ribbons and control bars

//
// Boost section
//

#define BOOST_SERIALIZATION_DYN_LINK TRUE
#define BOOST_ALL_DYN_LINK TRUE

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/assume_abstract.hpp>
//using namespace boost;

#ifdef _WIN64
    #ifdef _DEBUG
        #pragma comment (lib, "boost_container-vc140-mt-gd.lib")
        #pragma comment (lib, "boost_serialization-vc140-mt-gd.lib")
        #pragma comment (lib, "boost_wserialization-vc140-mt-gd.lib")
    #else    
        #pragma comment (lib, "boost_container-vc140-mt.lib")
        #pragma comment (lib, "boost_serialization-vc140-mt.lib")
        #pragma comment (lib, "boost_wserialization-vc140-mt.lib")
    #endif
#endif


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


#include "cpprest/json.h"
    
#ifdef _WIN64
    #ifdef _DEBUG
        #pragma comment (lib, "cpprest_2_10d.lib")
    #else    
        #pragma comment (lib, "cpprest_2_10.lib")
    #endif
#endif

#define USE_SCINTILLA
#define SCI_NAMESPACE
#ifdef USE_SCINTILLA
#include <scintilla\platform.h>
#include <scintilla\scintilla.h>
#include <scintilla\SciLexer.h>
#endif


#ifdef _WIN64
    #ifdef _DEBUG
        #pragma comment(lib, "SharedViewsD.lib")
    #else    
        #pragma comment(lib, "SharedViews.lib")
    #endif
#endif


#define VERSION_COMMUNITY
#define MAX_SHAPES          50

#endif //PCH_H

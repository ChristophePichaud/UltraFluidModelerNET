// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the SQLITEWRAPPER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// SQLITEWRAPPER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SQLITEWRAPPER_EXPORTS
#define SQLITEWRAPPER_API __declspec(dllexport)
#else
#define SQLITEWRAPPER_API __declspec(dllimport)
#endif

// This class is exported from the dll
class SQLITEWRAPPER_API CSQLiteWrapper {
public:
	CSQLiteWrapper(void);
	// TODO: add your methods here.
};

extern SQLITEWRAPPER_API int nSQLiteWrapper;

SQLITEWRAPPER_API int fnSQLiteWrapper(void);

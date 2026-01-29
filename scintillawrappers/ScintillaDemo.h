#pragma once


#include "resource.h"


class CScintillaDemoApp : public CWinApp
{
public:
//Member variables
  Lexilla::CreateLexerFn m_pCreateLexer{nullptr};

protected:
//Methods
  BOOL InitInstance() override;
  int ExitInstance() override;
  [[nodiscard]] CString GetModuleFileName(_Inout_opt_ DWORD* pdwLastError = nullptr);
  [[nodiscard]] HMODULE LoadLibraryFromApplicationDirectory(_In_z_ LPCTSTR lpFileName);

//Message handlers
  afx_msg void OnAppAbout();

  DECLARE_MESSAGE_MAP()

//Member variables
  HINSTANCE m_hScintilla{nullptr};
  HINSTANCE m_hLexilla{nullptr};
};

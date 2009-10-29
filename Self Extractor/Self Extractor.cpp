// Self Extractor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Self Extractor.h"
#include "Self ExtractorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelfExtractorApp

BEGIN_MESSAGE_MAP(CSelfExtractorApp, CWinApp)
	//{{AFX_MSG_MAP(CSelfExtractorApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelfExtractorApp construction

CSelfExtractorApp::CSelfExtractorApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSelfExtractorApp object

CSelfExtractorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSelfExtractorApp initialization

BOOL CSelfExtractorApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CSelfExtractorDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

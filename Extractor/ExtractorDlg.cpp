// ExtractorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Extractor.h"
#include "ExtractorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtractorDlg dialog

CExtractorDlg::CExtractorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExtractorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExtractorDlg)
	m_strPath = "c:\\temp";
	m_strCurrFile = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExtractorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtractorDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Text(pDX, IDC_PATH, m_strPath);
	DDX_Text(pDX, IDC_CURR_FILE, m_strCurrFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExtractorDlg, CDialog)
	//{{AFX_MSG_MAP(CExtractorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_EXTRACT, OnExtract)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtractorDlg message handlers

BOOL CExtractorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Progress.SetShowText(TRUE); 
	m_Progress.SetStep(1);
	m_Progress.ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExtractorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CExtractorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CExtractorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExtractorDlg::OnBrowse() 
{
	CDirDialog	dlg;
	dlg.SetWindowTitle("Select Extraction Directory");
	dlg.SetSelDir(m_strPath);
	
	if(dlg.DoModal(this) == IDOK)
	{
		m_strPath = dlg.GetPathname();
		UpdateData(FALSE);
	}
}

void CExtractorDlg::OnExtract() 
{
	m_Progress.SetRange(0, m_Extractor.GetFileCount());
	m_Progress.ShowWindow(SW_SHOW);
	int ret = m_Extractor.ExtractAll(m_strPath, CExtractorDlg::ExtractCallBack, static_cast<void*>(this));
	m_Progress.ShowWindow(SW_HIDE);
	m_strCurrFile = "";
	UpdateData(FALSE);

	CString Msg;
	switch(ret)
	{
	case SUCCESS:
		Msg.Format("%d files extracted successfully", m_Extractor.GetFileCount());
		break;
	case INVALID_SIG:
	case NOTHING_TO_DO:
		Msg = "Archive contins no data";
		break;
	default:
		Msg = "Internal Error";
		break;
	}

	MessageBox(Msg);
}

void CExtractorDlg::ExtractCallBack(void *ExtractData, void* userData)
{
	CSEFileInfo* pData = static_cast<CSEFileInfo*>(ExtractData);
	CExtractorDlg* pDlg = static_cast<CExtractorDlg*>(userData);

	pDlg->m_strCurrFile = "Extracting " + pDlg->m_strPath + "\\";
	pDlg->m_strCurrFile += pData->GetFilename();
	pDlg->m_Progress.StepIt();
	pDlg->UpdateData(FALSE);
}

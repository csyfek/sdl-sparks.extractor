// Self ExtractorDlg.cpp : implementation file
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
// CSelfExtractorDlg dialog

CSelfExtractorDlg::CSelfExtractorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelfExtractorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelfExtractorDlg)
	m_strExePath = _T("");
	m_strExtractorPath = _T("");
	m_strCurrFile = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSelfExtractorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelfExtractorDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_EXEPATH, m_strExePath);
	DDX_Text(pDX, IDC_EXTRACTOR_PATH, m_strExtractorPath);
	DDX_Text(pDX, IDC_CURR_FILE, m_strCurrFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSelfExtractorDlg, CDialog)
	//{{AFX_MSG_MAP(CSelfExtractorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSEEXE, OnBrowseexe)
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_READ, OnRead)
	ON_BN_CLICKED(IDC_BROWSE_EXTRACTOR, OnBrowseExtractor)
	ON_BN_CLICKED(IDC_ADD_DIR, OnAddDir)
	ON_BN_CLICKED(IDC_ADD_FILES, OnAddFiles)
	ON_BN_CLICKED(IDC_CLEAR_LIST, OnClearList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelfExtractorDlg message handlers

BOOL CSelfExtractorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_strWorkingDir = GetWorkingDir(TRUE);

	ListView_SetExtendedListViewStyle(m_List, LVS_EX_FULLROWSELECT |
												LVS_EX_FLATSB |
												LVS_EX_GRIDLINES);

	m_List.InsertColumn(1, "Name", LVCFMT_LEFT, 200);
	m_List.InsertColumn(2, "Size (bytes)", LVCFMT_LEFT, 200);
	m_Progress.SetStep(1);
	m_Progress.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSelfExtractorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}


void CSelfExtractorDlg::OnPaint() 
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

HCURSOR CSelfExtractorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


CString CSelfExtractorDlg::GetWorkingDir(BOOL withBackSlash)
{
	char FullName[MAX_PATH+1];
	GetModuleFileName(NULL,FullName,MAX_PATH);
	CString Path(FullName);
	int num = Path.ReverseFind('\\');
	if(num != -1)
	{
		if(withBackSlash)
			num +=1;

		Path = Path.Left(num);
		return Path;
	}
	else
		return "";
}

void CSelfExtractorDlg::OnBrowseExtractor() 
{
	CFileDialog dlg(TRUE, "", "", 
					OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
					"Exe Files (*.exe)|*.exe|All Files (*.*)|*.*||", this);
 
	dlg.m_ofn.lpstrTitle = "Select the Extractor Executable";
 
	if(dlg.DoModal() == IDOK)
	{
		m_strExtractorPath = dlg.GetPathName();
		UpdateData(FALSE);
	}	
}

void CSelfExtractorDlg::OnBrowseexe() 
{
	CFileDialog dlg(FALSE,"*.exe", "Untitled.exe", 
					OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
					"Self-extracting Executables (*.exe)|*.exe|All Files (*.*)|*.*||", this);
 
	dlg.m_ofn.lpstrTitle = "Save As Self-Extracting Archive";

	if (dlg.DoModal() == IDOK)
	{
		m_strExePath = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CSelfExtractorDlg::OnCreate() 
{
	if(m_strExePath.IsEmpty())
	{
		MessageBox("You need to select an output Exe before you can create the SFX");
		return;
	}

	m_Progress.SetRange(0, m_Extractor.GetFileCount());
	m_Progress.ShowWindow(SW_SHOW);
	UpdateData(FALSE);
	int ret = 0;
	if(m_strExtractorPath.IsEmpty())
		ret = m_Extractor.Create(IDR_SFX_EXE, m_strExePath, CSelfExtractorDlg::AddCallBack, (void*)this);
	else
		ret = m_Extractor.Create(m_strExtractorPath, m_strExePath, CSelfExtractorDlg::AddCallBack, (void*)this);
	
	m_Progress.SetPos(0);
	m_Progress.ShowWindow(SW_HIDE);
	m_strCurrFile = "";
	UpdateData(FALSE);
	switch(ret)
	{
	case NOTHING_TO_DO:
		MessageBox("You must add some files to the extractor");
		break;
	case SUCCESS:
		MessageBox("Archive Created Successfully");
		break;
	default:
		MessageBox("Unknown Error");
		break;
	}
}

void CSelfExtractorDlg::OnRead() 
{
	CFileDialog dlg(TRUE, "", "", 
					OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
					"Self Extracting Files (*.exe)|*.exe|All Files (*.*)|*.*||", this);
 
	dlg.m_ofn.lpstrTitle = "Select the Self Extracting file";
 
	if(dlg.DoModal() == IDOK)
	{
		int ret = m_Extractor.ReadTOC(dlg.GetPathName());
		if(ret == SUCCESS)
		{
			UpdateList();
		}
		else if(ret == INVALID_SIG)
		{
			CString Temp;
			Temp.LoadString(IDS_INVALID_FORMAT);
			MessageBox(Temp);
		}
	}
}

void CSelfExtractorDlg::OnAddDir() 
{
	CDirDialog dlg;
	dlg.SetWindowTitle("Select Directory");
	
	if(dlg.DoModal() == IDOK)
	{
		CString Path = dlg.GetPathname();
		Path += "\\*.*";

		CFileFind	finder;

		BOOL bContinue = finder.FindFile(Path);

		while(bContinue)
		{
			bContinue = finder.FindNextFile();
			m_Extractor.AddFile(finder.GetFilePath());
		}

		UpdateList();
	}
}

void CSelfExtractorDlg::OnAddFiles() 
{
	CFileDialog dlg(TRUE, "", "", 
					OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT, 
					"All Files (*.*)|*.*||", this);
 
	char cbBuffer[10240];
	dlg.m_ofn.nMaxFile = 10240;
	dlg.m_ofn.lpstrFile = cbBuffer;
	dlg.m_ofn.lpstrTitle = "Add Files";

	if(dlg.DoModal() == IDOK)
	{
		POSITION pos;
		for (pos = dlg.GetStartPosition(); pos != NULL;)
		{
			CString Path = dlg.GetNextPathName(pos);
			m_Extractor.AddFile(Path);
		}
	}
	UpdateList();
}

void CSelfExtractorDlg::UpdateList()
{
	m_List.DeleteAllItems();

	for(int i = 0; i < m_Extractor.GetFileCount(); i++)
	{
		m_List.InsertItem(i, m_Extractor.GetItem(i).GetFilename());
		CString Temp;
		Temp.Format("%d", m_Extractor.GetItem(i).GetFileSize());
		m_List.SetItemText(i, 1, Temp);
	}

	UpdateData(FALSE);
}

void CSelfExtractorDlg::AddCallBack(void* CallbackData, void *userData)
{
	CSEFileInfo* pData = static_cast<CSEFileInfo*>(CallbackData);
	CSelfExtractorDlg* pDlg = static_cast<CSelfExtractorDlg*>(userData);
	
	pDlg->m_strCurrFile = "Adding " + pData->GetPathname();
	pDlg->m_Progress.StepIt();
	pDlg->UpdateData(FALSE);
}

void CSelfExtractorDlg::OnClearList() 
{
	m_Extractor.Reset();
	UpdateList();
}

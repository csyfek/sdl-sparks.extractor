// Self ExtractorDlg.h : header file
//

#if !defined(AFX_SELFEXTRACTORDLG_H__5C3D7755_497B_11D3_A8BC_0050043A01C0__INCLUDED_)
#define AFX_SELFEXTRACTORDLG_H__5C3D7755_497B_11D3_A8BC_0050043A01C0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SelfExtractor.h"
#include "DirDialog.h"
#include "TextProgressCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSelfExtractorDlg dialog

class CSelfExtractorDlg : public CDialog
{
// Construction
public:
	CSelfExtractorDlg(CWnd* pParent = NULL);	// standard constructor

	CString GetWorkingDir(BOOL withBackSlash = FALSE);
	void UpdateList();

	static void AddCallBack(void* CallbackData, void* Data);

	CSelfExtractor	m_Extractor;
	CString m_strWorkingDir;

// Dialog Data
	//{{AFX_DATA(CSelfExtractorDlg)
	enum { IDD = IDD_SELFEXTRACTOR_DIALOG };
	CTextProgressCtrl	m_Progress;
	CListCtrl	m_List;
	CString	m_strExePath;
	CString	m_strExtractorPath;
	CString	m_strCurrFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelfExtractorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSelfExtractorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowseexe();
	afx_msg void OnBrowsezip();
	afx_msg void OnCreate();
	afx_msg void OnRead();
	afx_msg void OnBrowseExtractor();
	afx_msg void OnAddDir();
	afx_msg void OnAddFiles();
	afx_msg void OnClearList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELFEXTRACTORDLG_H__5C3D7755_497B_11D3_A8BC_0050043A01C0__INCLUDED_)

; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSelfExtractorDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Self Extractor.h"

ClassCount=3
Class1=CSelfExtractorApp
Class2=CSelfExtractorDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_SELFEXTRACTOR_DIALOG (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_SELFEXTRACTOR_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))

[CLS:CSelfExtractorApp]
Type=0
HeaderFile=Self Extractor.h
ImplementationFile=Self Extractor.cpp
Filter=N

[CLS:CSelfExtractorDlg]
Type=0
HeaderFile=Self ExtractorDlg.h
ImplementationFile=Self ExtractorDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_CURR_FILE

[CLS:CAboutDlg]
Type=0
HeaderFile=Self ExtractorDlg.h
ImplementationFile=Self ExtractorDlg.cpp
Filter=D

[DLG:IDD_SELFEXTRACTOR_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CSelfExtractorDlg

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SELFEXTRACTOR_DIALOG (English (U.S.))]
Type=1
Class=CSelfExtractorDlg
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDC_EXTRACTOR_PATH,edit,1350631552
Control3=IDC_EXEPATH,edit,1350631552
Control4=IDC_BROWSE_EXTRACTOR,button,1342242816
Control5=IDC_BROWSEEXE,button,1342242816
Control6=IDC_CREATE,button,1342242816
Control7=IDC_READ,button,1342242816
Control8=IDC_LIST,SysListView32,1350631425
Control9=IDC_PROGRESS,msctls_progress32,1350565888
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_ADD_FILES,button,1342242816
Control13=IDC_ADD_DIR,button,1342242816
Control14=IDC_CLEAR_LIST,button,1342242816
Control15=IDC_CURR_FILE,static,1342308352


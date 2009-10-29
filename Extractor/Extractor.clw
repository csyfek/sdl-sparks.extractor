; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CExtractorDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Extractor.h"

ClassCount=3
Class1=CExtractorApp
Class2=CExtractorDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_EXTRACTOR_DIALOG
Resource4=IDD_EXTRACTOR_DIALOG (English (U.S.))

[CLS:CExtractorApp]
Type=0
HeaderFile=Extractor.h
ImplementationFile=Extractor.cpp
Filter=N

[CLS:CExtractorDlg]
Type=0
HeaderFile=ExtractorDlg.h
ImplementationFile=ExtractorDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_CURR_FILE

[CLS:CAboutDlg]
Type=0
HeaderFile=ExtractorDlg.h
ImplementationFile=ExtractorDlg.cpp
Filter=D

[DLG:IDD_EXTRACTOR_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CExtractorDlg

[DLG:IDD_EXTRACTOR_DIALOG (English (U.S.))]
Type=1
Class=CExtractorDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_EXTRACT,button,1342242816
Control3=IDC_BROWSE,button,1342242816
Control4=IDC_PATH,edit,1350631552
Control5=IDC_PROGRESS,msctls_progress32,1350565888
Control6=IDC_CURR_FILE,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889


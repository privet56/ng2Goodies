; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWinsDlg
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "wins.h"
LastPage=0

ClassCount=12
Class1=CDlgProcesses
Class2=CHyperLink
Class3=CIPProcTree
Class4=CRenameDlg
Class5=CWinsApp
Class6=CAboutDlg
Class7=CWinsDlg
Class8=CWinsListCtrl

ResourceCount=9
Resource1=IDR_TASKBARMENU
Resource2=IDD_FLASHDLG
Resource3=IDD_WINDOWS_DLG
Resource4=IDD_EFFICIENCY_DLG
Resource5=IDD_WINS_DIALOG
Resource6=IDD_ABOUTBOX
Class9=CDlgWindows
Resource7=IDD_RENAME_DLG
Class10=CDlgFlash
Resource8=IDD_PROCESSES_DLG
Class11=CDlgEfficiency
Class12=CAllProcCtrl
Resource9=IDR_LISTMENU

[CLS:CDlgProcesses]
Type=0
BaseClass=CDialog
HeaderFile=DlgProcesses.h
ImplementationFile=DlgProcesses.cpp

[CLS:CHyperLink]
Type=0
BaseClass=CStatic
HeaderFile=HyperLink.h
ImplementationFile=HyperLink.cpp

[CLS:CIPProcTree]
Type=0
BaseClass=CTreeCtrl
HeaderFile=IPProcTree.h
ImplementationFile=IPProcTree.cpp

[CLS:CRenameDlg]
Type=0
BaseClass=CDialog
HeaderFile=RenameDlg.h
ImplementationFile=RenameDlg.cpp

[CLS:CWinsApp]
Type=0
BaseClass=CWinApp
HeaderFile=wins.h
ImplementationFile=wins.cpp
Filter=T

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=winsDlg.cpp
ImplementationFile=winsDlg.cpp
LastObject=CAboutDlg

[CLS:CWinsDlg]
Type=0
BaseClass=CDialog
HeaderFile=winsDlg.h
ImplementationFile=winsDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_TREE

[CLS:CWinsListCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=WinsListCtrl.h
ImplementationFile=WinsListCtrl.cpp

[DLG:IDD_PROCESSES_DLG]
Type=1
Class=CDlgProcesses
ControlCount=1
Control1=IDC_PROC_TREE,SysTreeView32,1350649911

[DLG:IDD_RENAME_DLG]
Type=1
Class=CRenameDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT,edit,1350631552

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342406657
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EMAIL_ST,static,1342308609

[DLG:IDD_WINS_DIALOG]
Type=1
Class=CWinsDlg
ControlCount=11
Control1=ID_SHOW_B,button,1342242817
Control2=ID_HIDE_B,button,1342242817
Control3=IDC_LIST,SysListView32,1350633485
Control4=IDC_INFO_ST,static,1342308610
Control5=ID_REFRESH_B,button,1342242817
Control6=ID_RENAME_B,button,1342242817
Control7=ID_EXIT_B,button,1342242817
Control8=ID_CLOSEAPP_B,button,1342242817
Control9=IDC_RAHMEN_ST,button,1342177287
Control10=IDC_TREE,SysTreeView32,1073807415
Control11=IDC_TREE_CHK,button,1342242819

[MNU:IDR_LISTMENU]
Type=1
Class=?
CommandCount=0

[DLG:IDD_WINDOWS_DLG]
Type=1
Class=CDlgWindows
ControlCount=1
Control1=IDC_WIN_TREE,SysTreeView32,1350649911

[MNU:IDR_TASKBARMENU]
Type=1
Class=?
CommandCount=0

[CLS:CDlgWindows]
Type=0
HeaderFile=DlgWindows.h
ImplementationFile=DlgWindows.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgWindows
VirtualFilter=dWC

[DLG:IDD_FLASHDLG]
Type=1
Class=CDlgFlash
ControlCount=4
Control1=IDC_TOP_B,static,1342179342
Control2=IDC_LEFT_B,static,1476395022
Control3=IDC_BOTTOM_B,static,1476395022
Control4=IDC_RIGHT_B,static,1476395022

[CLS:CDlgFlash]
Type=0
HeaderFile=DlgFlash.h
ImplementationFile=DlgFlash.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgFlash
VirtualFilter=dWC

[DLG:IDD_EFFICIENCY_DLG]
Type=1
Class=CDlgEfficiency
ControlCount=2
Control1=IDCANCEL,button,1342242816
Control2=IDC_SCOPE_D,static,1342308352

[CLS:CDlgEfficiency]
Type=0
HeaderFile=DlgEfficiency.h
ImplementationFile=DlgEfficiency.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgEfficiency
VirtualFilter=dWC

[CLS:CAllProcCtrl]
Type=0
HeaderFile=AllProcCtrl.h
ImplementationFile=AllProcCtrl.cpp
BaseClass=CTreeCtrl
Filter=W


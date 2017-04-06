# Microsoft Developer Studio Project File - Name="wins" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=wins - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "wins.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "wins.mak" CFG="wins - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "wins - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "wins - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wins - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MT /W3 /GX /O2 /I "D:\_Projekt.lfd\shi\infopilot\IPView\shivlib" /I "D:\_Projekt.lfd\shi\infopilot\IPLib" /I "D:\_Projekt.lfd\shi\SHIGuiLib\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 infopilotlibrary.lib shivlib.lib imagehlp.lib SHIGuiLib.lib /nologo /subsystem:windows /incremental:yes /machine:I386 /libpath:"D:\_Projekt.lfd\shi\infopilot\IPLib\Release" /libpath:"D:\_Projekt.lfd\shi\infopilot\IPView\shivlib\Release" /libpath:"D:\_Projekt.lfd\shi\SHIGuiLib\Release\\"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "wins - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "D:\_Projekt.lfd\shi\infopilot\IPView\shivlib" /I "D:\_Projekt.lfd\shi\infopilot\IPLib" /I "D:\_Projekt.lfd\shi\SHIGuiLib\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 infopilotlibrary_d.lib shivlib_d.lib imagehlp.lib SHIGuiLib_d.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"D:\_Projekt.lfd\shi\infopilot\IPLib\debug" /libpath:"D:\_Projekt.lfd\shi\infopilot\IPView\shivlib\debug" /libpath:"D:\_Projekt.lfd\shi\SHIGuiLib\DebugMFCstatic"

!ENDIF 

# Begin Target

# Name "wins - Win32 Release"
# Name "wins - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AllProcCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CpuUsage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEfficiency.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFlash.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProcesses.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWindows.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\IPProcTree.cpp
# End Source File
# Begin Source File

SOURCE=.\ModulVer.cpp
# End Source File
# Begin Source File

SOURCE=.\OScopeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\RenameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemTray.cpp
# End Source File
# Begin Source File

SOURCE=.\wins.cpp
# End Source File
# Begin Source File

SOURCE=.\wins.rc
# End Source File
# Begin Source File

SOURCE=.\winsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WinsListCtrl.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AllProcCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CpuUsage.h
# End Source File
# Begin Source File

SOURCE=.\DlgEfficiency.h
# End Source File
# Begin Source File

SOURCE=.\DlgFlash.h
# End Source File
# Begin Source File

SOURCE=.\DlgProcesses.h
# End Source File
# Begin Source File

SOURCE=.\DlgWindows.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\IPProcTree.h
# End Source File
# Begin Source File

SOURCE=.\ModulVer.h
# End Source File
# Begin Source File

SOURCE=.\OScopeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\PerfCounters.h
# End Source File
# Begin Source File

SOURCE=.\RenameDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemTray.h
# End Source File
# Begin Source File

SOURCE=.\SystemTraySDK.h
# End Source File
# Begin Source File

SOURCE=.\wins.h
# End Source File
# Begin Source File

SOURCE=.\winsDlg.h
# End Source File
# Begin Source File

SOURCE=.\WinsListCtrl.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\imglist1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wins.ico
# End Source File
# Begin Source File

SOURCE=.\res\wins.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project

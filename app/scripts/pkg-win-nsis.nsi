;------------ Compress ------------
;SetCompressor /SOLID LZMA
;SetCompress force

;------------ Defines ------------
!define PRODUCT_NAME            "DevAssistant"
!define PRODUCT_VERSION         "1.0.0.0"
!define PRODUCT_COMPANY         "coder4869"
!define LICENSE_FILE            "..\data\doc\License.txt"
!define INSTALL_ICON            "..\data\resource\logo.ico"
!define UNINSTALL_ICON          "..\data\resource\uninstall.ico"
!define COMPANY_WEB             "http://www.yourcompany.com"
!define PRODUCT_REG_AUTORUN_KEY "${PRODUCT_NAME}"

;------------ File Properties ------------
VIProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey FileDescription   "${PRODUCT_NAME} Installer"
VIAddVersionKey FileVersion       "${PRODUCT_VERSION}"
VIAddVersionKey ProductName       "${PRODUCT_NAME} Installer" 
VIAddVersionKey ProductVersion    "${PRODUCT_VERSION}"
VIAddVersionKey CompanyName       "${PRODUCT_COMPANY}"
VIAddVersionKey LegalCopyright    "Copyright (C) 2018-2025 ${PRODUCT_COMPANY}"

;------------ Use Modern UI ------------
!include "MUI2.nsh"

;------------ Output file, Install-path, Admin-authority ------------
;General
  ;Properly display all languages (Installer will not work on Windows 95, 98 or ME!)
  Unicode true

  ;Name and file
  Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
  OutFile "${PRODUCT_NAME}-Installer-v${PRODUCT_VERSION}.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\${PRODUCT_COMPANY}\${PRODUCT_NAME}"
  
  ;Get installation folder from registry if available
  ;InstallDirRegKey HKCU "Software\Modern UI Test" ""

  ;Request Application Privileges
  RequestExecutionLevel admin

;------------ Interface Settings ------------
  !define MUI_ABORTWARNING

  ;------------ Install Page ---------------
  ;https://blog.csdn.net/patdz/article/details/8541622
  !define      MUI_ICON             "${INSTALL_ICON}"
  !define      MUI_UNICON           "${UNINSTALL_ICON}"
  !define      MUI_FINISHPAGE_RUN   "$INSTDIR\bin64\${PRODUCT_NAME}.exe"  ; Run exe tips for finish page

  !insertmacro MUI_PAGE_WELCOME                       ; Add welcome page
  !insertmacro MUI_PAGE_LICENSE    "${LICENSE_FILE}"  ; Include a license file if needed
  !insertmacro MUI_PAGE_COMPONENTS                    ; Add components selection page
  !insertmacro MUI_PAGE_DIRECTORY                     ; Add install dir page
  !insertmacro MUI_PAGE_INSTFILES                     ; Add install files display page
  !insertmacro MUI_PAGE_FINISH                        ; Add finish page

  ;------------ Uninstall Page ---------------
  !define       MUI_UNWELCOMEPAGE_TITLE   "卸载程序"
  !define       MUI_UNWELCOMEPAGE_TEXT    "您确定要卸载此程序吗？"
  !insertmacro  MUI_UNPAGE_WELCOME
  !insertmacro  MUI_UNPAGE_CONFIRM
  !insertmacro  MUI_UNPAGE_INSTFILES
  !insertmacro  MUI_UNPAGE_FINISH

  ;------------ Languages ------------
  !define       MUI_LANGDLL_ALLLANGUAGES    ; Show all languages
  !insertmacro  MUI_LANGUAGE  "SimpChinese"
  !insertmacro  MUI_LANGUAGE  "English"
  
;------------ Reserve Files ------------
  ;If you are using solid compression, files that are required before
  ;the actual installation should be stored first in the data block,
  ;because this will make your installer start faster.
  
  !insertmacro MUI_RESERVEFILE_LANGDLL

;------------ Installer Sections ------------
Section "Install ${PRODUCT_NAME}"
  SectionIn RO
  SetOutPath "$INSTDIR"
  
  ; Copy Files
  File /r "..\bin64\*"
  RMDir /r "$INSTDIR\lib"
  RMDir /r "$INSTDIR\logs"
  Rename "$INSTDIR\Release" "$INSTDIR\bin64"

  ; Create Uninstaller
  WriteUninstaller "$INSTDIR\bin64\Uninstall.exe"
  
  ; Add Uninstaller to Start Menu (Optional)
  CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
  CreateShortCut  "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk" "$INSTDIR\bin64\Uninstall.exe"

  ; Add program to Start Menu && Desktop && QuickLaunch
  SetShellVarContext all
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\bin64\${PRODUCT_NAME}.exe"
  CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk"     "$INSTDIR\bin64\${PRODUCT_NAME}.exe"
  CreateShortCut "$QUICKLAUNCH\${PRODUCT_NAME}.lnk" "$INSTDIR\bin64\${PRODUCT_NAME}.exe"

  ; Register the software in Add/Remove Programs
  ; RightAction add to HKEY_CLASSES_ROOT
  ;WriteRegStr        HKCR "*.bat\shell\${PRODUCT_NAME}"               ""      '"bat文件处理"'                              ; For *.bat's DisplayName
  ;WriteRegStr        HKCR "*.bat\shell\${PRODUCT_NAME}"               "Icon"  '"$INSTDIR\data\Resource\logo.ico"'          ; For *.bat's icon
  ;WriteRegExpandStr  HKCR "*.bat\shell\${PRODUCT_NAME}\command"       ""      '"$INSTDIR\bin64\${PRODUCT_NAME}.exe" "%1"'  ; For *.bat
  WriteRegStr         HKCR "*\shell\${PRODUCT_NAME}"                   ""      '"文件处理"'                                  ; For AllFiles's DisplayName
  WriteRegStr         HKCR "*\shell\${PRODUCT_NAME}"                   "Icon"  '"$INSTDIR\data\Resource\logo.ico"'          ; For AllFiles's icon
  WriteRegExpandStr   HKCR "*\shell\${PRODUCT_NAME}\command"           ""      '"$INSTDIR\bin64\${PRODUCT_NAME}.exe" "%1"'  ; For AllFiles
  WriteRegStr         HKCR "Directory\shell\${PRODUCT_NAME}"           ""      '"文件夹处理"'                                ; For Directory's DisplayName
  WriteRegStr         HKCR "Directory\shell\${PRODUCT_NAME}"           "Icon"  '"$INSTDIR\data\Resource\logo.ico"'          ; For Directory's icon
  WriteRegExpandStr   HKCR "Directory\shell\${PRODUCT_NAME}\command"   ""      '"$INSTDIR\bin64\${PRODUCT_NAME}.exe" "%1"'  ; For Directory
  WriteRegStr         HKCR "Folder\shell\${PRODUCT_NAME}"              ""      '"文件夹处理"'                                ; For Folder's DisplayName
  WriteRegStr         HKCR "Folder\shell\${PRODUCT_NAME}"              "Icon"  '"$INSTDIR\data\Resource\logo.ico"'          ; For Folder's icon
  WriteRegExpandStr   HKCR "Folder\shell\${PRODUCT_NAME}\command"      ""      '"$INSTDIR\bin64\${PRODUCT_NAME}.exe" "%1"'  ; For Folder

  ; add to HKEY_LOCAL_MACHINE
  ;AutoRun
  WriteRegStr   HKLM "Software\Microsoft\Windows\CurrentVersion\Run" "${PRODUCT_REG_AUTORUN_KEY}" '"$INSTDIR\bin64\${PRODUCT_NAME}.exe" /min' 
  ;Clean the previous uninstall information
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
  ;Generate the new uninstall information
  WriteRegStr   HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "DisplayName"      "${PRODUCT_NAME}"
  WriteRegStr   HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "UninstallString"  "$INSTDIR\bin64\Uninstall.exe"
  WriteRegStr   HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "InstallLocation"  "$INSTDIR"
  WriteRegStr   HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "Publisher"        "${PRODUCT_COMPANY}"
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "NoModify"         1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "NoRemove"         0
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "EstimatedSize"    1024              ; Size in KB
  WriteRegStr   HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "Version" "${PRODUCT_VERSION}"       ; Version of your software
  WriteRegStr   HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}" "URLInfoAbout"     "${COMPANY_WEB}"  ; Optional: URL to your software's info
  
  ; Optionally add a registry entry for your application (e.g., to set a default value)
  ;WriteRegStr HKCU "Software\${PRODUCT_NAME}" "SomeSetting" "SomeValue"
  
  ; Run program after installation
  ;ExecWait '"$INSTDIR\Updater.exe" -deleteservice'
  ;Exec "$INSTDIR\bin64\${PRODUCT_NAME}.exe"

SectionEnd

;------------ Installer Start Function ------------
; "FindProcDLL" requires third-party plugin
Function .onInit
  ;FindProcDLL::FindProc "${PRODUCT_NAME}.exe"
  ;IntCmp $R0 1 0 TestNotRunning
  ;  MessageBox MB_OK|MB_ICONEXCLAMATION "Please close Test first" /SD IDOK
  ;  Abort
  ;TestNotRunning:

  !insertmacro MUI_LANGDLL_DISPLAY          ; Language selection page
FunctionEnd

;------------ UnInstaller Start Function ------------
Function un.onInit
  ;${If} $R0 = 0
  ;  MessageBox MB_OK "检测到${PRODUCT_NAME}正在运行，请先退出程序再卸载!" /SD IDOK
  ;  Abort
  ;${EndIf}
FunctionEnd

;------------ Languages ------------
;Descriptions
  ;Language strings
  ;LangString DESC_SecTest ${LANG_SIMPCHINESE} "Test主程序"
  ;LangString DESC_SecTest ${LANG_ENGLISH} "Test main program"

  ;Assign language strings to sections
  ;!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  ;  !insertmacro MUI_DESCRIPTION_TEXT ${SecTest} $(DESC_SecTest)
  ;!insertmacro MUI_FUNCTION_DESCRIPTION_END

;------------ Uninstaller Section ------------
Section "Uninstall"
  ; Remove Shortcuts
  SetShellVarContext all
  Delete "$DESKTOP\${PRODUCT_NAME}.lnk"
  Delete "$QUICKLAUNCH\${PRODUCT_NAME}.lnk"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk"

  ; Remove Registry Entries
  ;DeleteRegKey HKCR "*.bat\shell\${PRODUCT_NAME}"     ; For *.bat
  DeleteRegKey  HKCR "*\shell\${PRODUCT_NAME}"         ; For AllFiles
  DeleteRegKey  HKCR "Directory\shell\${PRODUCT_NAME}" ; For Directory
  DeleteRegKey  HKCR "Folder\shell\${PRODUCT_NAME}"    ; For Folder

  ;Clean AutoRun
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Run\" "${PRODUCT_REG_AUTORUN_KEY}"
  ;Clean uninstall information
  DeleteRegKey  HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
  DeleteRegKey  HKCU "Software\${PRODUCT_NAME}"


  ;uninstall Service(stop)
  Exec '"$INSTDIR\${PRODUCT_NAME}.exe" -uninstall'

  ; Delete Files
  ;Delete "$INSTDIR\${PRODUCT_NAME}.exe"
  ;Delete "$INSTDIR\Uninstall.exe"
  
  ; Remove Directory
  RMDir /r "$SMPROGRAMS\${PRODUCT_NAME}"
  RMDir /r "$INSTDIR\.."
SectionEnd
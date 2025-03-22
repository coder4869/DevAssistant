#include "LogicLib.nsh"
!include "WordFunc.nsh"
!addplugindir "Plugins"

; ------------- check installed -------------
Function CheckInstall
    ; Get paramters
    Var /GLOBAL PRODUCT_VERSION
    Var /GLOBAL PRODUCT_NAME
    Pop $R0 ; PRODUCT_VERSION
    Pop $R1 ; PRODUCT_NAME
    StrCpy $PRODUCT_VERSION "$R0"
    StrCpy $PRODUCT_NAME    "$R1"

    ; Read reg values
    Var /GLOBAL RegReadVersion
    Var /GLOBAL RegReadLocation
    SetRegView 64
    ReadRegStr  $RegReadVersion  HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$PRODUCT_NAME" "Version"
    ReadRegStr  $RegReadLocation HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$PRODUCT_NAME" "InstallLocation"
    
    ; Not Installed, installContinue 
    StrCmp $RegReadVersion "" 0 +3
        MessageBox MB_OK "当前无已安装版本，欢迎使用本软件" ;注册表项不存在或值为空
        Goto done

    ; Installed, Compare Version
    ${VersionCompare} "$RegReadVersion" "$PRODUCT_VERSION" $R0
    IntCmp $R0 1 isold isSame isnew
    isold: ; $R0 == 1
        MessageBox MB_YESNO "当前安装版本较旧（v$PRODUCT_VERSION），已安装版本较新（$RegReadVersion），是否继续？" IDYES installGo IDNO installStop
        installGo:
            ExecWait    "$RegReadLocation\bin64\Uninstall.exe"
            Goto done
        installStop:
            Quit
    isSame: ; $R0 == 0
        MessageBox MB_OK "当前版本（v$PRODUCT_VERSION）已安装，安装结束！"
        Quit
    isnew: ; $R0 == 2
        MessageBox MB_YESNO "已安装旧版本（v$RegReadVersion），当前版本 v$PRODUCT_VERSION，是否继续安装？若继续安装，会先卸载旧版本！" IDYES true IDNO false 
        true:
            ExecWait    "$RegReadLocation\bin64\Uninstall.exe"
            Goto done
        false:
            Quit
    done:
FunctionEnd

;demo:
; !insertmacro CheckInstalled  ${PRODUCT_NAME} ${PRODUCT_VERSION}
!macro CheckInstalled name version
    Push "${name}"
    Push "${version}"
    Call CheckInstall
!macroend

; ------------- vc_redist -------------
Function CheckVCRedist
    ; Get paramters
    Var /GLOBAL INSTALL_DIR
    Pop $R0 ; INSTALL_DIR
    StrCpy $INSTALL_DIR "$R0"
    
    SetOutPath "$INSTALL_DIR\temp"
    
    ; get vc_redist
    File /r "vc_redist\*"

    SetRegView 64
    ReadRegDWORD $R1 HKLM "Software\Microsoft\VisualStudio\14.0\VC\Runtimes\x64" "Installed"
    ${If} $R1 != 1
        MessageBox MB_OK "未安装VS2019-x64运行时库，进行安装"
        ExecWait    "$INSTALL_DIR\temp\vc_redist.x64.exe"
        ;ExecWait   '"$INSTALL_DIR\temp\vc_redist.x64.exe" /quiet /norestart' $0  
        Goto done
    ${Else}
        ;MessageBox MB_OK "已安装VS2019-x64运行时库"
        Goto done
    ${EndIf}

    done:
        RMDir /r "$INSTALL_DIR\temp"
        SetRegView lastused ; recover reg view
FunctionEnd

;demo:
; !insertmacro CheckVCRedistEnv $INSTDIR
!macro CheckVCRedistEnv install_dir
    Push "${install_dir}"
    Call CheckVCRedist
!macroend

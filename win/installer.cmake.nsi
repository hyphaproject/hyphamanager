###
# Copyright (c) 2009, Paul Gideon Dann
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
###

!include "MUI.nsh"

!define EXE_BUILD_NAME "@CMAKE_PROJECT_NAME@.exe"
!define EXE_INSTALL_NAME "@PROJECT_LONGNAME@.exe"
!define APP_LONGNAME "@PROJECT_LONGNAME@"
!define APP_VERSION "@PROJECT_VERSION@"

!define DIST_DIR "@CMAKE_RUNTIME_OUTPUT_DIRECTORY@"
!define SOURCE_DIR "@CMAKE_SOURCE_DIR@"

Name "${APP_LONGNAME}"
OutFile "${APP_LONGNAME} ${APP_VERSION} Setup.exe"
!define ORGANISATION_NAME "${APP_LONGNAME} Project"
InstallDir "$PROGRAMFILES\${APP_LONGNAME}"
!define APP_REGISTRY_KEY "Software\${APP_LONGNAME}"
!define UNINSTALL_REGISTRY_KEY "${APP_LONGNAME}"
InstallDirRegKey HKLM "${APP_REGISTRY_KEY}" ""
SetCompressor /SOLID lzma

# Request admin privileges
RequestExecutionLevel admin

# Variables
Var StartMenuFolder

# Interface Settings
!define MUI_ABORTWARNING
#!define MUI_ICON "${SOURCE_DIR}\win\installer-icon.ico"
#!define MUI_HEADERIMAGE_BITMAP "${SOURCE_DIR}\win\installer-header.bmp" # Size: 150x57
#!define MUI_WELCOMEFINISHPAGE_BITMAP "${SOURCE_DIR}\win\installer-welcome.bmp" # Size: 164x314
#!define MUI_UNWELCOMEFINISHPAGE_BITMAP "${SOURCE_DIR}\win\installer-welcome.bmp"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "${SOURCE_DIR}\LICENCE"
!insertmacro MUI_PAGE_DIRECTORY
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "${APP_LONGNAME}"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKLM"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${APP_REGISTRY_KEY}"
!define START_MENU_REGISTRY_VALUE "Start Menu Folder"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${START_MENU_REGISTRY_VALUE}"
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
!insertmacro MUI_PAGE_INSTFILES
!define MUI_FINISHPAGE_RUN "$INSTDIR\${EXE_INSTALL_NAME}"
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

# Languages
!insertmacro MUI_LANGUAGE "English"

#==
# Installation
#==
Section Install
  SetOutPath "$INSTDIR"

  File "${SOURCE_DIR}\LICENCE"

  # App files
  File "/oname=${EXE_INSTALL_NAME}" "${DIST_DIR}\${EXE_BUILD_NAME}"
  # Plugins
  SetOutPath "$INSTDIR\plugins"
  File "${DIST_DIR}\plugins\alarm.dll"
  File "${DIST_DIR}\plugins\blechuhr.dll"
  File "${DIST_DIR}\plugins\dht11.dll"
  File "${DIST_DIR}\plugins\dooropener.dll"
  File "${DIST_DIR}\plugins\email.dll"
  File "${DIST_DIR}\plugins\espeak.dll"
  File "${DIST_DIR}\plugins\explorenfc.dll"
  File "${DIST_DIR}\plugins\fingerprintzfm.dll"
  File "${DIST_DIR}\plugins\flame.dll"
  File "${DIST_DIR}\plugins\lightsensor.dll"
  File "${DIST_DIR}\plugins\rfid.dll"
  File "${DIST_DIR}\plugins\rpianalogsensor.dll"
  File "${DIST_DIR}\plugins\rpiled.dll"
  File "${DIST_DIR}\plugins\rpigpio.dll"
  File "${DIST_DIR}\plugins\rpipir.dll"
  File "${DIST_DIR}\plugins\serverstatus.dll"
  File "${DIST_DIR}\plugins\video.dll"
  File "${DIST_DIR}\plugins\videocontrol.dll"
  File "${DIST_DIR}\plugins\watersensor.dll"
  File "${DIST_DIR}\plugins\wifi.dll"
  SetOutPath "$INSTDIR"

  # MinGW Runtimes
  #File "${DIST_DIR}\libgcc_s_dw2-1.dll"
  #File "${DIST_DIR}\libstdc++-6.dll"
  #File "${DIST_DIR}\libwinpthread-1.dll"

  # ICU Unicode Libraries used by Qt
  File "${DIST_DIR}\icudt53.dll"
  File "${DIST_DIR}\icuin53.dll"
  File "${DIST_DIR}\icuuc53.dll"

  # Qt Libraries
  File "${DIST_DIR}\Qt5Core.dll"
  File "${DIST_DIR}\Qt5Gui.dll"
  File "${DIST_DIR}\Qt5Multimedia.dll"
  File "${DIST_DIR}\Qt5MultimediaWidgets.dll"
  File "${DIST_DIR}\Qt5Network.dll"
  File "${DIST_DIR}\Qt5OpenGL.dll"
  File "${DIST_DIR}\Qt5Positioning.dll"
  File "${DIST_DIR}\Qt5PrintSupport.dll"
  File "${DIST_DIR}\Qt5Qml.dll"
  File "${DIST_DIR}\Qt5Quick.dll"
  File "${DIST_DIR}\Qt5Sensors.dll"
  File "${DIST_DIR}\Qt5Sql.dll"
  File "${DIST_DIR}\Qt5Svg.dll"
  File "${DIST_DIR}\Qt5WebChannel.dll"
  File "${DIST_DIR}\Qt5WebKit.dll"
  File "${DIST_DIR}\Qt5WebKitWidgets.dll"
  File "${DIST_DIR}\Qt5Widgets.dll"

    # Poco Libraries
    File "${DIST_DIR}\PocoFoundation.dll"
    File "${DIST_DIR}\PocoNet.dll"

    # Other Libraries and Files
    File "${DIST_DIR}\libmysql.dll"
    File "${DIST_DIR}\qt_de.qm"
    File "${DIST_DIR}\msvcp120.dll"
    File "${DIST_DIR}\msvcr120.dll"

  # Translations
  SetOutPath "$INSTDIR\i18n"
  #File "${DIST_DIR}\i18n\*.qm"

  # Qt Plugins
  SetOutPath "$INSTDIR\platforms"
  File "${DIST_DIR}\platforms\qwindows.dll"
  SetOutPath "$INSTDIR\sqldrivers"
  File "${DIST_DIR}\sqldrivers\qsqlite.dll"
  File "${DIST_DIR}\sqldrivers\qsqlmysql.dll"
  File "${DIST_DIR}\sqldrivers\qsqlodbc.dll"
  File "${DIST_DIR}\sqldrivers\qsqlpsql.dll"
  SetOutPath "$INSTDIR\imageformats"
  File "${DIST_DIR}\imageformats\qico.dll"
  File "${DIST_DIR}\imageformats\qjpeg.dll"
  File "${DIST_DIR}\imageformats\qsvg.dll"
  SetOutPath "$INSTDIR\iconengines"
  File "${DIST_DIR}\iconengines\qsvgicon.dll"

  # Uninstaller
  WriteRegStr HKLM "${APP_REGISTRY_KEY}" "" $INSTDIR
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  !define UNINSTALL_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTALL_REGISTRY_KEY}"
  WriteRegStr HKLM "${UNINSTALL_KEY}" "DisplayName" "${APP_LONGNAME}"
  WriteRegStr HKLM "${UNINSTALL_KEY}" "UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr HKLM "${UNINSTALL_KEY}" "QuietUninstallString" "$INSTDIR\Uninstall.exe /S"
  WriteRegStr HKLM "${UNINSTALL_KEY}" "DisplayIcon" "$INSTDIR\${EXE_INSTALL_NAME}"
  WriteRegStr HKLM "${UNINSTALL_KEY}" "DisplayVersion" "${APP_VERSION}"
  WriteRegStr HKLM "${UNINSTALL_KEY}" "Publisher" "${ORGANISATION_NAME}"

  # Menu folder
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\${APP_LONGNAME}.lnk" "$INSTDIR\${EXE_INSTALL_NAME}"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

#==
# Uninstallation
#==
Section Uninstall
  Delete "$INSTDIR\LICENCE"

  # App files
  Delete "$INSTDIR\${EXE_INSTALL_NAME}"

    #Plugins
        Delete "$INSTDIR\plugins\alarm.dll"
    Delete "$INSTDIR\plugins\blechuhr.dll"
    Delete "$INSTDIR\plugins\dht11.dll"
    Delete "$INSTDIR\plugins\dooropener.dll"
    Delete "$INSTDIR\plugins\email.dll"
    Delete "$INSTDIR\plugins\espeak.dll"
    Delete "$INSTDIR\plugins\explorenfc.dll"
    Delete "$INSTDIR\plugins\fingerprintzfm.dll"
        Delete "$INSTDIR\plugins\flame.dll"
        Delete "$INSTDIR\plugins\lightsensor.dll"
    Delete "$INSTDIR\plugins\rfid.dll"
    Delete "$INSTDIR\plugins\rpianalogsensor.dll"
        Delete "$INSTDIR\plugins\rpiled.dll"
    Delete "$INSTDIR\plugins\rpigpio.dll"
    Delete "$INSTDIR\plugins\rpipir.dll"
    Delete "$INSTDIR\plugins\serverstatus.dll"
    Delete "$INSTDIR\plugins\video.dll"
    Delete "$INSTDIR\plugins\videocontrol.dll"
    Delete "$INSTDIR\plugins\watersensor.dll"
    Delete "$INSTDIR\plugins\wifi.dll"
    RMDir "$INSTDIR\plugins"

  # MinGW Runtimes
  #Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  #Delete "$INSTDIR\libstdc++-6.dll"
  #Delete "$INSTDIR\libwinpthread-1.dll"

  # ICU Unicode Libraries used by Qt
  Delete "$INSTDIR\icudt53.dll"
  Delete "$INSTDIR\icuin53.dll"
  Delete "$INSTDIR\icuuc53.dll"

  # Qt Libraries
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Multimedia.dll"
  Delete "$INSTDIR\Qt5MultimediaWidgets.dll"
  Delete "$INSTDIR\Qt5Network.dll"
  Delete "$INSTDIR\Qt5OpenGL.dll"
  Delete "$INSTDIR\Qt5Positioning.dll"
  Delete "$INSTDIR\Qt5PrintSupport.dll"
  Delete "$INSTDIR\Qt5Qml.dll"
  Delete "$INSTDIR\Qt5Quick.dll"
  Delete "$INSTDIR\Qt5Sensors.dll"
  Delete "$INSTDIR\Qt5Sql.dll"
  Delete "$INSTDIR\Qt5Svg.dll"
  Delete "$INSTDIR\Qt5WebChannel.dll"
  Delete "$INSTDIR\Qt5WebKit.dll"
  Delete "$INSTDIR\Qt5WebKitWidgets.dll"
  Delete "$INSTDIR\Qt5Widgets.dll"

    # Poco Libraries
    Delete "$INSTDIR\PocoFoundation.dll"
    Delete "$INSTDIR\PocoNet.dll"

    # Other Libraries and Files
    Delete "$INSTDIR\libmysql.dll"
    Delete "$INSTDIR\qt_de.qm"
    Delete "$INSTDIR\msvcp120.dll"
    Delete "$INSTDIR\msvcr120.dll"

  # Translations
  #Delete "$INSTDIR\i18n\*.qm"
  RMDir "$INSTDIR\i18n"

  # Qt Plugins

  Delete "$INSTDIR\platforms\qwindows.dll"
  RMDir "$INSTDIR\platforms"
  Delete "$INSTDIR\sqldrivers\qsqlite.dll"
  Delete "$INSTDIR\sqldrivers\qsqlmysql.dll"
  Delete "$INSTDIR\sqldrivers\qsqlodbc.dll"
  Delete "$INSTDIR\sqldrivers\qsqlpsql.dll"
  RMDir "$INSTDIR\sqldrivers"

  Delete "$INSTDIR\imageformats\qico.dll"
  Delete "$INSTDIR\imageformats\qjpeg.dll"
  Delete "$INSTDIR\imageformats\qsvg.dll"
  RMDir "$INSTDIR\imageformats"

  Delete "$INSTDIR\iconengines\qsvgicon.dll"
  RMDir "$INSTDIR\iconengines"

  # Menu folder
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
  Delete "$SMPROGRAMS\$StartMenuFolder\${APP_LONGNAME}.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"

  # Uninstaller
  Delete "$INSTDIR\Uninstall.exe"
  RMDir "$INSTDIR"
  DeleteRegKey /ifempty HKLM "${APP_REGISTRY_KEY}"
  DeleteRegKey /ifempty HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTALL_REGISTRY_KEY}"
SectionEnd

# vim: ft=nsis

; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "QAutoRouter"
#define MyAppVersion "0.0.4"
#define MyAppPublisher "EightBitGeek"
#define MyAppURL "http://qautorouter.sourceforge.net"
#define MyAppExeName "qa.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{E3C4D206-DB22-441C-9B5A-6CE56F792C0D}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
LicenseFile=LICENSE
;OutputDir=.\
OutputBaseFilename=qautorouter-setup
;SetupIconFile=autorouter.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "..\qautorouter-build-desktop-Qt_4_8_1_for_Desktop_-_MinGW__Qt_SDK__Debug\qautorouter\debug\qa.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\qautorouter-build-desktop-Qt_4_8_1_for_Desktop_-_MinGW__Qt_SDK__Debug\specctra\debug\specctra.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\qautorouter-build-desktop-Qt_4_8_1_for_Desktop_-_MinGW__Qt_SDK__Debug\plugins\simplerouter\debug\simplerouter.dll"; DestDir: "{app}\plugins"; Flags: ignoreversion
Source: "C:\QtSDK\mingw\bin\mingwm10.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\QtSDK\mingw\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\QtSDK\Desktop\Qt\4.8.1\mingw\lib\QtNetworkd4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\QtSDK\Desktop\Qt\4.8.1\mingw\lib\QtCored4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\QtSDK\Desktop\Qt\4.8.1\mingw\lib\QtGuid4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\qautorouter\examples\spi4.dsn"; DestDir: "{app}\examples"; Flags: ignoreversion
Source: "..\qautorouter\examples\alu.dsn"; DestDir: "{app}\examples"; Flags: ignoreversion
Source: "..\qautorouter\examples\brisc1-registers.dsn"; DestDir: "{app}\examples"; Flags: ignoreversion
Source: "..\qautorouter\examples\broken\PA10.dsn"; DestDir: "{app}\examples\broken"; Flags: ignoreversion
Source: "..\qautorouter\examples\broken\AT2XTKBD.dsn"; DestDir: "{app}\examples\broken"; Flags: ignoreversion
Source: "..\qautorouter\examples\broken\DSKY.dsn"; DestDir: "{app}\examples\broken"; Flags: ignoreversion
Source: "..\qautorouter\examples\broken\MSXCart.dsn"; DestDir: "{app}\examples\broken"; Flags: ignoreversion
Source: "..\qautorouter\examples\broken\OPL2.dsn"; DestDir: "{app}\examples\broken"; Flags: ignoreversion
Source: "..\qautorouter\examples\broken\P112.dsn"; DestDir: "{app}\examples\broken"; Flags: ignoreversion
Source: "..\qautorouter\examples\broken\ppide.dsn"; DestDir: "{app}\examples\broken"; Flags: ignoreversion
Source: "..\qautorouter\examples\broken\SCSI2IDE.dsn"; DestDir: "{app}\examples\broken"; Flags: ignoreversion
Source: "..\qautorouter\examples\broken\sd.dsn"; DestDir: "{app}\examples\broken"; Flags: ignoreversion
Source: "..\qautorouter\examples\broken\XT-IDE.dsn"; DestDir: "{app}\examples\broken"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, "&", "&&")}}"; Flags: nowait postinstall skipifsilent


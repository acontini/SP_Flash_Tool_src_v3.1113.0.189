# ---------------------------------------------------------------------------
!if !$d(BCB)
BCB = $(MAKEDIR)\..
!endif

# ---------------------------------------------------------------------------
# IDE SECTION
# ---------------------------------------------------------------------------
# The following section of the project makefile is managed by the BCB IDE.
# It is recommended to use the IDE to change any of the values in this
# section.
# ---------------------------------------------------------------------------

VERSION = BCB.06.00
# ---------------------------------------------------------------------------
PROJECT = output\Flash_tool.exe
OBJFILES = output\Flash_tool.obj output\main.obj output\DA_Option.obj \
    output\tboot_1.obj output\ext_mem1.obj output\OK_Wnd.obj output\about.obj \
    output\RB_Option.obj output\DL_Go.obj output\RB_Go.obj \
    output\frm_FormatOption.obj output\frm_BootROMStartCmdRetry.obj \
    output\com_util.obj output\frm_COM_Option.obj \
    output\frm_SecuritySetting.obj output\frm_OTPSetting.obj \
    output\frm_ParameterReadSetting.obj output\BromDLLProcAddr.obj \
    output\BromDLLWrapper.obj output\Utility.obj output\ConsoleMode.obj \
    output\XGetopt.obj output\argcargv.obj output\CommandLineArguments.obj \
    output\Config.obj output\Setting.obj output\XMLDocumentImpl.obj \
    output\XMLDocument.obj output\XMLNodeImpl.obj output\XMLNode.obj \
    output\Command.obj output\FlashToolCommand.obj output\Logger.obj \
    output\MSXML2_TLB.obj output\frm_IMEIDownload.obj \
    output\WMMETA_Wrapper.obj output\frm_FourInOne.obj output\frm_Process.obj \
    output\frm_Splash.obj output\GlobalData.obj output\ImageMapRule.obj \
    output\FileUtils.obj output\ErrorLookup.obj output\AndroidImageInfo.obj \
    output\version.obj output\NvramBackupMap.obj output\updater.obj \
    output\FlashAllInOneAPIs.obj output\PlatformInfo.obj output\Platforms.obj \
    output\FlashToolUSB.obj output\CommandConnect.obj \
    output\FlashToolStorageConfig.obj output\OperationIndicator.obj \
    output\HandleManger.obj output\HintMessageHandle.obj \
    output\NandAutoFormatArg.obj output\NandLayoutParameter.obj \
    output\AutoFormatArg.obj output\AutoFormatArgFactory.obj \
    output\SearchUSB.obj output\DownloadImageChecksum.obj \
    output\EMMCAutoFormatArg.obj output\RegionFormatArg.obj \
    output\FirmwareUpgradeConfig.obj output\RegionFormatSetting.obj \
    output\RegionFormatCommand.obj output\CloneInfoHandle.obj \
    output\ReadbackCommand.obj output\ReadbackSetting.obj \
    output\WriteMemoryCommand.obj output\WriteMemorySetting.obj \
    output\CommandConfig.obj output\SCIReadbackArg.obj \
    output\WriteMemoryArg.obj output\frm_encript.obj \
    output\SDMMCAutoFormatArg.obj output\BackupConfig.obj
RESFILES = Flash_tool.res
MAINSOURCE = Flash_tool.cpp
RESDEPEN = $(RESFILES) main.dfm DA_Option.dfm ext_mem1.dfm OK_Wnd.dfm about.dfm \
    RB_Option.dfm DL_Go.dfm RB_Go.dfm frm_FormatOption.dfm \
    frm_BootROMStartCmdRetry.dfm frm_COM_Option.dfm frm_SecuritySetting.dfm \
    frm_OTPSetting.dfm frm_ParameterReadSetting.dfm frm_IMEIDownload.dfm \
    frm_FourInOne.dfm frm_Process.dfm frm_Splash.dfm frm_encript.dfm
LIBFILES = lib\eboot.lib lib\FlashToolLib.lib lib\META_DLL.lib lib\SLA_Challenge.lib \
    lib\SPMETA_DLL.lib
IDLFILES = 
IDLGENFILES = 
LIBRARIES = vclx.lib bcbsmp.lib vcl.lib rtl.lib
PACKAGES = rtl.bpi vcl.bpi vclx.bpi bcbsmp.bpi qrpt.bpi dbrtl.bpi vcldb.bpi \
    bdertl.bpi ibsmp.bpi vcldbx.bpi teeui.bpi teedb.bpi tee.bpi teeqr.bpi \
    ibxpress.bpi bcbie.bpi vclie.bpi inetdb.bpi inet.bpi nmfast.bpi dclocx.bpi \
    bcb2kaxserver.bpi DCLUSR.bpi
SPARELIBS = rtl.lib vcl.lib bcbsmp.lib vclx.lib
DEFFILE = 
OTHERFILES = 
# ---------------------------------------------------------------------------
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
USERDEFINES = _CLEAN
SYSDEFINES = NO_STRICT
INCLUDEPATH = "D:\Program Files\Borland\CBuilder6\Projects";"C:\Program Files\Borland\CBuilder6\Projects";$(BCB)\include;$(BCB)\include\vcl;$(BCB)\Include\Atl;BootRom;.
LIBPATH = "D:\Program Files\Borland\CBuilder6\Projects";"C:\Program Files\Borland\CBuilder6\Projects";$(BCB)\lib;$(BCB)\Lib\Obj;.
WARNINGS= -w-par
PATHCPP = .;
PATHASM = .;
PATHPAS = .;
PATHRC = .;
PATHOBJ = .;$(LIBPATH)
# ---------------------------------------------------------------------------
CFLAG1 = -O2 -H=c:\PROGRA~1\borland\CBUILD~1\lib\vcl60.csm -Hc -Vx -Ve -X- -a8 -5 \
    -b -k- -vi -c -tW -tWM
IDLCFLAGS = -I"D:\Program Files\Borland\CBuilder5\Projects\." \
    -I"C:\Program Files\Borland\CBuilder5\Projects\." -I$(BCB)\include \
    -I$(BCB)\include\vcl -src_suffix cpp -boa
PFLAGS = -N2output -N0output -$Y- -$L- -$D- -$A8 -v -JPHNE -M
RFLAGS = 
AFLAGS = /mx /w2 /zn
LFLAGS = -Ioutput -D"" -H:0x1000000 -Hc:0x1000000 -S:0x1000000 -Sc:0x1000000 -aa \
    -Tpe -x -Gn -w
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj sysinit.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cp32mt.lib
# ---------------------------------------------------------------------------
!ifdef IDEOPTIONS

[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0

[Version Info Keys]
CompanyName=
FileDescription=
FileVersion=1.0.0.0
InternalName=
LegalCopyright=
LegalTrademarks=
OriginalFilename=
ProductName=
ProductVersion=1.0.0.0
Comments=

[Debugging]
DebugSourceDirs=$(BCB)\source\vcl

!endif





# ---------------------------------------------------------------------------
# MAKE SECTION
# ---------------------------------------------------------------------------
# This section of the project file is not used by the BCB IDE.  It is for
# the benefit of building from the command-line using the MAKE utility.
# ---------------------------------------------------------------------------

.autodepend
# ---------------------------------------------------------------------------
!if "$(USERDEFINES)" != ""
AUSERDEFINES = -d$(USERDEFINES:;= -d)
!else
AUSERDEFINES =
!endif

!if !$d(BCC32)
BCC32 = bcc32
!endif

!if !$d(CPP32)
CPP32 = cpp32
!endif

!if !$d(DCC32)
DCC32 = dcc32
!endif

!if !$d(TASM32)
TASM32 = tasm32
!endif

!if !$d(LINKER)
LINKER = ilink32
!endif

!if !$d(BRCC32)
BRCC32 = brcc32
!endif


# ---------------------------------------------------------------------------
!if $d(PATHCPP)
.PATH.CPP = $(PATHCPP)
.PATH.C   = $(PATHCPP)
!endif

!if $d(PATHPAS)
.PATH.PAS = $(PATHPAS)
!endif

!if $d(PATHASM)
.PATH.ASM = $(PATHASM)
!endif

!if $d(PATHRC)
.PATH.RC  = $(PATHRC)
!endif

!if $d(PATHOBJ)
.PATH.OBJ  = $(PATHOBJ)
!endif
# ---------------------------------------------------------------------------
$(PROJECT): $(OTHERFILES) $(IDLGENFILES) $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) -L$(LIBPATH) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES)
!
# ---------------------------------------------------------------------------
.pas.hpp:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.pas.obj:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.cpp.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.cpp.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.asm.obj:
    $(BCB)\BIN\$(TASM32) $(AFLAGS) -i$(INCLUDEPATH:;= -i) $(AUSERDEFINES) -d$(SYSDEFINES:;= -d) $<, $@

.rc.res:
    $(BCB)\BIN\$(BRCC32) $(RFLAGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -fo$@ $<



# ---------------------------------------------------------------------------





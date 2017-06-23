/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/

#ifndef _FLASHTOOL_COMMAND_H
#define _FLASHTOOL_COMMAND_H

#include <string>
#include <vector>
#include <set>  
#include "Command.h"
#include "Setting.h"
#include "general.h"
#include "metaapp_common.h"
#include "eboot\interface.h"
#include "com_enum.h"
#include "com_util.h"
#include "oxdevicequery.h"

#include "BromDLLWrapper.h"
#include "NonCopyable.h"
#include "FlashToolTypedefs.h"


class PrepareDLHandleCommand : public Command
{
public:
    PrepareDLHandleCommand(const ConsoleMode::DownloadSetting &downloadSetting) 
	               : m_DownloadSetting(downloadSetting) {};
	virtual ~PrepareDLHandleCommand() {};
	virtual int Execute();
	
private:
    const ConsoleMode::DownloadSetting m_DownloadSetting;
};

class DownloadCommand : public Command
{
public:
    DownloadCommand(const ConsoleMode::GeneralSetting  &generalSetting,
                    const ConsoleMode::DownloadSetting &downloadSetting);
    virtual ~DownloadCommand();

public:
    virtual int Execute();

private:
    const ConsoleMode::GeneralSetting  m_GeneralSetting;
    const ConsoleMode::DownloadSetting m_DownloadSetting;
#if 0   
    int DLFlashBin( void );
#endif
    int DLYuSuFlashBin( void );
};

class FormatCommand : public Command
{
public:
    FormatCommand(const ConsoleMode::GeneralSetting &generalSetting,
                  const ConsoleMode::FormatSetting  &formatSetting);
    virtual ~FormatCommand();

public:
    virtual int Execute();

private:
    const ConsoleMode::GeneralSetting m_GeneralSetting;
    const ConsoleMode::FormatSetting  m_FormatSetting;
};

class ResetToFactoryDefaultCommand : public Command
{
public:
    ResetToFactoryDefaultCommand(
                    const ConsoleMode::GeneralSetting &generalSetting,
                    const ConsoleMode::ResetToFactoryDefaultSetting
                                            &resetToFactoryDefaultSetting);
    virtual ~ResetToFactoryDefaultCommand();

public:
    virtual int Execute();

private:
    const ConsoleMode::GeneralSetting m_GeneralSetting;
    const ConsoleMode::ResetToFactoryDefaultSetting
                                        m_ResetToFactoryDefaultSetting;
};

class BackupCommand : public Command
{
public:
    BackupCommand(const ConsoleMode::GeneralSetting &generalSetting,
                  const ConsoleMode::BackupSetting &backupSetting);
    virtual ~BackupCommand();

public:
    virtual int Execute();

private:
    bool CreateDirectory(const std::wstring &directoryPath);

private:
    const ConsoleMode::GeneralSetting m_GeneralSetting;
    const ConsoleMode::BackupSetting  m_BackupSetting;
};

class BT_WIFI_IMEI_NVRAMCommand : public Command
{
public:
    BT_WIFI_IMEI_NVRAMCommand(const ConsoleMode::GeneralSetting &generalSetting,
                              const ConsoleMode::Write_BT_WIFI_IMEI_NVRAM_Setting &backupSetting);
    virtual ~BT_WIFI_IMEI_NVRAMCommand(){};

public:
    virtual int Execute();

private:
    bool CreateDirectory(const std::wstring &directoryPath);

    bool SP_BootAsMetaWrapper(int p_comport, int* p_BootStop);

    META_RESULT ArgMETAConnectWithTargetInMETA( int com_port,
                                        META_ConnectInMETA_Req  &META_ConnectInMETA_Req ,
                                        META_ConnectInMETA_Report  &META_ConnectInMETA_Report);

    META_RESULT  ModemNVRAMInit( AnsiString database );

    META_RESULT  ApNVRAMInit(const int meta_handle, AnsiString database );

private:
    const ConsoleMode::GeneralSetting m_GeneralSetting;
    const ConsoleMode::Write_BT_WIFI_IMEI_NVRAM_Setting  m_setting;
};


class RestoreCommand: public Command
{
public:
    RestoreCommand(const ConsoleMode::GeneralSetting &generalSetting,
                   const ConsoleMode::RestoreSetting &restoreSetting);
    virtual ~RestoreCommand();

public:
    virtual int Execute();

private:
    const ConsoleMode::GeneralSetting m_GeneralSetting;
    const ConsoleMode::RestoreSetting m_RestoreSetting;
};

class ReadbackCommand: public Command
{
public:
	ReadbackCommand(const ConsoleMode::GeneralSetting &generalSetting,
		const ConsoleMode::ReadbackSetting &reabackSetting);
	virtual ~ReadbackCommand();

	virtual int Execute();
private:
	const ConsoleMode::GeneralSetting m_GeneralSetting;
	const ConsoleMode::ReadbackSetting m_ReabackSetting;
};
#endif // _FLASHTOOL_COMMAND_H

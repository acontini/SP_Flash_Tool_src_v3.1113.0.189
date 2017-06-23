/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include <vector>
#include "Setting.h"
#include "SharedPtr.h"


class Command;

namespace ConsoleMode
{
    class ConfigType
    {
    public:

        static const ConfigType META_4IN1;
        static const ConfigType DOWNLOAD;
        static const ConfigType FORMAT;
        static const ConfigType READBACK;
        static const ConfigType RTFD;
        static const ConfigType DOWNLOAD_FORMAT;
        static const ConfigType DOWNLOAD_RTFD;
        static const ConfigType BACKUP_DOWNLOAD_RESTORE;
        static const ConfigType BACKUP_DOWNLOAD_FORMAT_RESTORE;
        static const ConfigType BACKUP_DOWNLOAD_RTFD_RESTORE;
        static const ConfigType BACKUP_FORMAT_RESTORE;
        static const ConfigType BACKUP_RTFD_RESTORE;
	static const ConfigType FORMAT_DOWNLOAD;

    private:
        explicit ConfigType(const std::wstring &name);

    public:
        std::wstring GetName() const;

    private:
        const std::wstring m_Name;
    };

    class CommandLineArguments;

    class Config
    {
    public:
        Config();
        explicit Config(const CommandLineArguments &commandLineArguments);
        ~Config();

    public:
        void LoadFile(const std::wstring &filename);
        void SaveFile(const std::wstring &filename,
                      const ConfigType &type) const;

        void SetGeneralSetting(const GeneralSetting &generalSetting);
        void AddCommandSetting(const CommandSetting &commandSetting);
        SharedPtr<Command> CreateCommand() const;
        const GeneralSetting * GetGeneralSetting(void) const {
            return m_GeneralSetting;
            }
        void Dump() const;

    private:
        // FIXME
        GeneralSetting *m_GeneralSetting;

        typedef std::vector<SharedPtr<CommandSetting> > CommandSettings;
        CommandSettings m_CommandSettings;
    };
}

#endif // _CONFIG_H

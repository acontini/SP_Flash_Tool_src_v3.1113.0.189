/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/

#include <atlbase.h>
#include <cassert>
#include <stdexcept>

#include "Config.h"
#include "CommandLineArguments.h"
#include "FlashToolCommand.h"
#include "Setting.h"
#include "XMLDocument.h"


using std::runtime_error;
using std::string;
using std::vector;
using std::wstring;
using ConsoleMode::CommandLineArguments;
using ConsoleMode::Config;
using ConsoleMode::ConfigType;
using ConsoleMode::CommandSetting;
using ConsoleMode::GeneralSetting;
using XML::Document;
using XML::Node;


const ConfigType ConfigType::META_4IN1(L"META-4IN1");
const ConfigType ConfigType::DOWNLOAD(L"download");
const ConfigType ConfigType::FORMAT(L"format");
const ConfigType ConfigType::READBACK(L"readback");
const ConfigType ConfigType::RTFD(L"RtFD");
const ConfigType ConfigType::DOWNLOAD_FORMAT(L"download-format");
const ConfigType ConfigType::DOWNLOAD_RTFD(L"download-RtFD");
const ConfigType ConfigType::BACKUP_DOWNLOAD_RESTORE(L"backup-download-restore");
const ConfigType ConfigType::BACKUP_DOWNLOAD_FORMAT_RESTORE(
                                        L"BAckup-download-format-restore");
const ConfigType ConfigType::BACKUP_DOWNLOAD_RTFD_RESTORE(
                                        L"backup-download-RtFD-restore");
const ConfigType ConfigType::BACKUP_FORMAT_RESTORE(L"backup-format-restore");
const ConfigType ConfigType::BACKUP_RTFD_RESTORE(L"backup-RtFD-restore");

const ConfigType ConfigType::FORMAT_DOWNLOAD(L"format-download");

static const wstring DOCUMENT_ROOT_NODE_NAME(L"flashtool-config");
static const wstring DOCUMENT_VERSION(L"1.0");

ConfigType::ConfigType(const wstring &name)
    : m_Name(name)
{
}

wstring ConfigType::GetName() const
{
    return m_Name;
}

Config::Config()
    : m_GeneralSetting(NULL),
      m_CommandSettings()
{
}

Config::Config(const CommandLineArguments &commandLineArguments)
    : m_GeneralSetting(NULL),
      m_CommandSettings()
{
    USES_CONVERSION;
    LoadFile(commandLineArguments.GetConfigFilename());
    assert(m_GeneralSetting != NULL);

    if (!commandLineArguments.GetComPort().empty())
    {
        // Overwrite the COM port setting defined in the config file
        m_GeneralSetting->SetComPort(commandLineArguments.GetComPort());
	m_GeneralSetting->SetPortType(L"USB");      
    }

    if (!commandLineArguments.GetDownloadAgentFilename().empty())
    {
        // Overwrite the download agent setting defined in the config file
        m_GeneralSetting->SetDownloadAgentFilePath(
                commandLineArguments.GetDownloadAgentFilename());
    }
}

Config::~Config()
{
    if (m_GeneralSetting != NULL)
    {
        delete m_GeneralSetting;
    }
}

void Config::LoadFile(const wstring &filename)
{
    Document document(filename);
    const Node rootNode = document.GetRootNode();
    assert(rootNode.GetName() == DOCUMENT_ROOT_NODE_NAME);
    assert(rootNode.GetNumChildNodes() == 1);

    const wstring documentVersion(rootNode.GetAttribute(L"version"));

    if (documentVersion == L"1.0")
    {
        document.Validate(L"ConsoleMode_v1_0.xsd");
    }
    else if (documentVersion.empty())
    {
        throw runtime_error(string("No configuration version specified"));
    }
    else
    {
        USES_CONVERSION;
        throw runtime_error(string("Unrecognized configuration version: ") +
                            W2CA(documentVersion.c_str()));
    }

    const Node operationNode = rootNode.GetChildNode(0);
    const unsigned int numSettingNodes = operationNode.GetNumChildNodes();

    // We should have at least two setting nodes, including one
    // "general-setting" node.
    assert(numSettingNodes >= 2);

    //
    // Get general setting 
    //
    const Node generalSettingNode = operationNode.GetChildNode(0);
    assert(generalSettingNode.GetName() == L"general-setting");

    if (m_GeneralSetting != NULL)
    {
        delete m_GeneralSetting;
    }

    m_GeneralSetting = new GeneralSetting(generalSettingNode);

    //
    // Get command settings
    //
    m_CommandSettings.clear();

    for (unsigned int childIndex=1; childIndex<numSettingNodes; ++childIndex)
    {
        const Node settingNode = operationNode.GetChildNode(childIndex);
        CommandSetting *commandSetting;

        if (settingNode.GetName() == L"download-setting")
        {
            m_CommandSettings.push_back(
                SharedPtr<CommandSetting>(new DownloadSetting(settingNode)));
        }
        else if (settingNode.GetName() == L"META-4IN1-setting")
        {
            m_CommandSettings.push_back(
                SharedPtr<CommandSetting>(new Write_BT_WIFI_IMEI_NVRAM_Setting(settingNode)));
        }
        else if (settingNode.GetName() == L"format-setting")
        {
            m_CommandSettings.push_back(
                    SharedPtr<CommandSetting>(new FormatSetting(settingNode)));
        }
        else if (settingNode.GetName() == L"reset-to-factory-default-setting")
        {
            m_CommandSettings.push_back(
                    SharedPtr<CommandSetting>(
                            new ResetToFactoryDefaultSetting(settingNode)));
        }
        else if (settingNode.GetName() == L"backup-setting")
        {
            m_CommandSettings.push_back(
                    SharedPtr<CommandSetting>(new BackupSetting(settingNode)));
        }
        else if (settingNode.GetName() == L"bt_wifi_imei_nvram_setting")
        {
            m_CommandSettings.push_back(
                    SharedPtr<CommandSetting>(new Write_BT_WIFI_IMEI_NVRAM_Setting(settingNode)));
        }
        else if (settingNode.GetName() == L"restore-setting")
        {
            m_CommandSettings.push_back(
                SharedPtr<CommandSetting>(new RestoreSetting(settingNode)));
        }
        else if (settingNode.GetName() == L"readback-setting")
        {
            m_CommandSettings.push_back(
                SharedPtr<CommandSetting>(new ReadbackSetting(settingNode)));
        }
        else
        {
            USES_CONVERSION;
            throw runtime_error(string("Unrecognized setting: ") +
                                W2CA(settingNode.GetName().c_str()));
        }
    }
}

void Config::SaveFile(const wstring &filename,
                      const ConfigType &type) const
{
    if ((m_GeneralSetting == NULL) || (m_CommandSettings.size() == 0))
    {
        // ...
    }

    Document document(L"1.0", L"UTF-8", DOCUMENT_ROOT_NODE_NAME);
    
	Node rootNode = document.GetRootNode();
    rootNode.SetAttribute(L"version", DOCUMENT_VERSION);

    Node operationNode = rootNode.AppendChildNode(type.GetName());
    m_GeneralSetting->SaveXML(operationNode);

    for (CommandSettings::const_iterator it = m_CommandSettings.begin();
         it != m_CommandSettings.end();
         ++it)
    {
        (*it)->SaveXML(operationNode);
    }

    document.Beautify();
    document.Save(filename);
}

void Config::SetGeneralSetting(const GeneralSetting &generalSetting)
{
    if (m_GeneralSetting != NULL)
    {
        delete m_GeneralSetting;
    }

    m_GeneralSetting = new GeneralSetting(generalSetting);
}

void Config::AddCommandSetting(const CommandSetting &commandSetting)
{
    m_CommandSettings.push_back(
            SharedPtr<CommandSetting>(commandSetting.Clone()));
}

SharedPtr<Command> Config::CreateCommand() const
{
    if ((m_GeneralSetting == NULL) || (m_CommandSettings.size() == 0))
    {
        // ...
    }

    SharedPtr<MacroCommand> macroCommand(new MacroCommand);

    for (CommandSettings::const_iterator it = m_CommandSettings.begin();
         it != m_CommandSettings.end();
         ++it)
    {
        macroCommand->Add((*it)->CreateCommand(*m_GeneralSetting));
		
	//look for download setting
	const DownloadSetting *dlSetting = dynamic_cast<const DownloadSetting *>(it->get());
	if(dlSetting != NULL){
            macroCommand->AddPreCommand(SharedPtr<PrepareDLHandleCommand>(
            new PrepareDLHandleCommand(*dlSetting)));
        }
    }

    return macroCommand;
}

void Config::Dump() const
{
    if (m_GeneralSetting != NULL)
    {
        m_GeneralSetting->Dump();
    }

    for (CommandSettings::const_iterator it = m_CommandSettings.begin();
         it != m_CommandSettings.end();
         ++it)
    {
        (*it)->Dump();
    }
}

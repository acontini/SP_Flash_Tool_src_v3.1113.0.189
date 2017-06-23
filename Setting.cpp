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
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include "FlashToolCommand.h"
#include "Logger.h"
#include "Setting.h"
#include "XMLNode.h"
#include "GlobalData.h"
#include "Utility.h"
#include "FlashToolTypedefs.h"

using ConsoleMode::BackupSetting;
using ConsoleMode::Write_BT_WIFI_IMEI_NVRAM_Setting;
using ConsoleMode::CommandSetting;
using ConsoleMode::DownloadSetting;
using ConsoleMode::FormatSetting;
using ConsoleMode::GeneralSetting;
using ConsoleMode::ResetToFactoryDefaultSetting;
using ConsoleMode::RestoreSetting;
using ConsoleMode::ReadbackSetting;
using XML::Node;
using std::dec;
using std::endl;
using std::hex;
using std::setfill;
using std::setw;
using std::vector;
using std::wostringstream;
using std::wstring;

static void ThrowSettingError(const wstring &nodeName)
{
    USES_CONVERSION;
    throw std::runtime_error(std::string("Unrecognized setting: ") +
                             W2CA(nodeName.c_str()));
}

GeneralSetting::GeneralSetting(const Node &node)
    : m_ComPort(),
      m_PortType(L"NONE"),
      m_CheckBasebandVersion(true),
      m_DownloadAgentFilePath(),
      m_AuthenticationFilePath(),
      m_sleepTime(10000)
{
    LoadXML(node);
}

GeneralSetting::GeneralSetting(bool logsEnable,
                               const wstring &comPort,
                               const std::wstring &flash_operation,
                               bool checkBasebandVersion,
                               const wstring &downloadAgentFilePath,
                               const wstring &authenticationFilePath,
                               const std::wstring &scertFilePath,
                               unsigned int sleepTime)
    : m_LogsEnable(logsEnable),
      m_ComPort(comPort),
      m_PortType(L"NONE"),
      m_flash_operation(flash_operation),
      m_CheckBasebandVersion(checkBasebandVersion),
      m_DownloadAgentFilePath(downloadAgentFilePath),
      m_AuthenticationFilePath(authenticationFilePath),
      m_SCertFilePath(scertFilePath),
      m_sleepTime(sleepTime)
{
}

GeneralSetting::~GeneralSetting()
{
}

wstring GeneralSetting::GetComPort() const
{
    return m_ComPort;
}

wstring GeneralSetting::GetPortType() const
{
    return m_PortType;
}

void GeneralSetting::SetComPort(const wstring &comPort)
{
    m_ComPort = comPort;
}

void GeneralSetting::SetPortType(const  wstring & portType)
{
    m_PortType = portType;
}

bool GeneralSetting::IsCheckBasebandVersionEnabled() const
{
    return m_CheckBasebandVersion;
}

wstring GeneralSetting::GetDownloadAgentFilePath() const
{
    return m_DownloadAgentFilePath;
}

void GeneralSetting::SetDownloadAgentFilePath(
                        const wstring &downloadAgentFilePath)
{
    m_DownloadAgentFilePath = downloadAgentFilePath;
}


HW_StorageType_E GeneralSetting::Get_flash_operation() const
{
     return m_flash_type;
}

wstring GeneralSetting::GetAuthenticationFilePath() const
{
    return m_AuthenticationFilePath;
}

wstring GeneralSetting::GetSCertFilePath() const
{
	return m_SCertFilePath;
}

bool GeneralSetting::IsLogsEnabled() const
{
    return m_LogsEnable;
}

unsigned int GeneralSetting::GetSleepTime() const
{
    return m_sleepTime;
}

#if 0
wstring GeneralSetting::GetFlashBinFilePath() const
{
    return m_FlashBinFilePath;
}
#endif

void GeneralSetting::Dump() const
{
    USES_CONVERSION;

    Logger::GetLogger() << Logger::Info <<endl 
           << "[General setting]"    << endl
           << "    Logs record enable = " << (m_LogsEnable ? "Yes" : "No") << endl
           << "    COM port = "      << W2CA(m_ComPort.c_str()) << endl
           << "    Operation Type =" << W2CA(m_flash_operation.c_str())  << endl
           << "    Check bbchip hw ver = "
           << (m_CheckBasebandVersion ? "Yes" : "No") << endl
           << "    DA filepath = "
           << W2CA(m_DownloadAgentFilePath.c_str()) << endl
           << "    Auth filepath = "
           << W2CA(m_AuthenticationFilePath.c_str()) << endl
		   << "    Security Certification filepath = "
		   << W2CA(m_SCertFilePath.c_str()) << endl;

    if (!m_AuthenticationFilePath.empty())
    {
    	Logger::GetLogger() << "    Authentication filepath = "
               << W2CA(m_AuthenticationFilePath.c_str()) << endl;
    }
}

void GeneralSetting::LoadXML(const Node &node)
{
    for (unsigned int childIndex=0;
         childIndex<node.GetNumChildNodes();
         ++childIndex)
    {
        const Node childNode = node.GetChildNode(childIndex);

        if (childNode.GetName() == L"flash-operation")
        {
            m_flash_operation = childNode.GetText();
			
	      if (m_flash_operation == L"NOR")
            {
                  m_flash_type= HW_STORAGE_NOR;
            }
            else if (m_flash_operation == L"NAND")
            {
                  m_flash_type = HW_STORAGE_NAND;
            }
	     else if (m_flash_operation == L"EMMC")
	     {
                  m_flash_type = HW_STORAGE_EMMC;
	     }
           else
           {
                  ThrowSettingError(childNode.GetName());
	     }
        }
        else if ( childNode.GetName() == L"logs-enable" )
        {
            m_LogsEnable = ((childNode.GetText() == L"TRUE") || 
                (childNode.GetText() == L"true"));
        }
        else if (childNode.GetName() == L"com-port")
        {
            m_ComPort = childNode.GetText();
        }
        else if (childNode.GetName() == L"check-bbchip-hardware-version")
        {
            m_CheckBasebandVersion = (childNode.GetText() == L"true");
        }
        else if (childNode.GetName() == L"download-agent-file-path")
        {
            m_DownloadAgentFilePath = childNode.GetText();
        }
        else if (childNode.GetName() == L"authentication-file-path")
        {
            m_AuthenticationFilePath = childNode.GetText();
        }
        else if (childNode.GetName() == L"security-certification-file-path")
        {
            m_SCertFilePath = childNode.GetText();
        }
	  else if (childNode.GetName() == L"sleep-time")
	  {
            ::swscanf(childNode.GetText().c_str(),
                      L"%u",
                      &m_sleepTime);
	  }
        else
        {
            ThrowSettingError(childNode.GetName());
        }
    }
}

void GeneralSetting::SaveXML(Node &node) const
{
    Node rootNode(node.AppendChildNode(L"general-setting"));

    rootNode.AppendChildNode(L"logs-enable", m_LogsEnable ? L"true" : L"false");

    rootNode.AppendChildNode(L"flash-operation", m_flash_operation);

    rootNode.AppendChildNode(L"com-port", m_ComPort);

    rootNode.AppendChildNode(
                L"check-bbchip-hardware-version",
                m_CheckBasebandVersion ? L"true" : L"false");

    rootNode.AppendChildNode(L"download-agent-file-path",
                             m_DownloadAgentFilePath);
	
    //default sleep 1s to wait for target reset.
    wostringstream sleep;
        sleep<< dec
               << m_sleepTime;

    rootNode.AppendChildNode(L"sleep-time", sleep.str());
#if 0
    rootNode.AppendChildNode(L"flash-bin-file-path",
                             m_FlashBinFilePath);
#endif
    if (m_AuthenticationFilePath.empty())  {
        rootNode.AppendChildNode(L"authentication-file-path");
    } else  {
        rootNode.AppendChildNode(L"authentication-file-path",
                                 m_AuthenticationFilePath);
    }

    if (m_SCertFilePath.empty())  {
        rootNode.AppendChildNode(L"security-certification-file-path");
    } else  {
        rootNode.AppendChildNode(L"security-certification-file-path",
                                 m_SCertFilePath);
    }
}

DownloadSetting::Download_Item::Download_Item(std::wstring _name,
                                              std::wstring _path)
                                              :name(_name),
                                              path(_path)
{
}

DownloadSetting::DownloadSetting(const Node &node)
    : m_ScatterFilePath(),
      m_WatchdogInterval(15000),
      m_DownloadList(),
      m_AutoFormatEnabled(false),
      m_ManualFormatBeginAddress(0),
      m_ManualFormatLength(0),
      m_DADLAllWithChksum(true),
      m_DADLAutoDetect(true),
      m_WatchdogTimerEnabled(false)
{
    LoadXML(node);
}

DownloadSetting::DownloadSetting(const wstring &scatterFilePath,
                                 const std::wstring &dl_operation,
                                 const std::wstring &dl_os,
                                 const vector<DownloadSetting::Download_Item> downloadList,
                                 bool autoFormatEnabled,
                                 unsigned int manualFormatBeginAddress,
                                 unsigned int manualFormatLength,
                                 bool watchdogTimerEnabled,
								 bool daDLAll,
								 bool daDLHighSpeed,
								 bool daDLWithoutBat,
								 bool daDLAllWithChksum,
								 bool daDLAutoDetect)
    : m_ScatterFilePath(scatterFilePath),
      m_dl_operation(dl_operation),
      m_dl_os(dl_os),
      m_WatchdogInterval(15000),
      m_DownloadList(downloadList),
      m_AutoFormatEnabled(autoFormatEnabled),
      m_ManualFormatBeginAddress(manualFormatBeginAddress),
      m_ManualFormatLength(manualFormatLength),
      m_WatchdogTimerEnabled(watchdogTimerEnabled),
	  m_DADLAll(daDLAll),
	  m_DADLHighSpeed(daDLHighSpeed),
	  m_DADLWithoutBat(daDLWithoutBat),
          m_DADLAllWithChksum(daDLAllWithChksum),
          m_DADLAutoDetect(daDLAutoDetect)
{
}

DownloadSetting::~DownloadSetting()
{
}

wstring DownloadSetting::GetScatterFilePath() const
{
    return m_ScatterFilePath;
}

std::vector<DownloadSetting::Download_Item> DownloadSetting::GetDownloadList() const
{
    return m_DownloadList;
}

bool DownloadSetting::IsAutoFormatEnabled() const
{
    return m_AutoFormatEnabled;
}

bool DownloadSetting::IsManualFormatEnabled() const
{
    return (m_ManualFormatLength != 0);
}

unsigned int DownloadSetting::GetManualFormatBeginAddress() const
{
    return m_ManualFormatBeginAddress;
}

unsigned int DownloadSetting::GetManualFormatLength() const
{
    return m_ManualFormatLength;
}

bool DownloadSetting::IsWatchdogTimerEnabled() const
{
    return m_WatchdogTimerEnabled;
}

void DownloadSetting::LoadXML(const Node &node)
{
    USES_CONVERSION;   

	for (unsigned int childIndex=0;
         childIndex<node.GetNumChildNodes();
         ++childIndex)
    {
        const Node childNode = node.GetChildNode(childIndex);

        if (childNode.GetName() == L"scatter-file-path")
        {
            m_ScatterFilePath = childNode.GetText();
			std::string scatterFile = W2CA(m_ScatterFilePath.c_str());
            /* Adapt new storage layout file, 2012/12/22 { */
#if 0
			std::string error_hint;
			g_platform_info.initByScatterFile(scatterFile, error_hint, false);
			if(!g_platform_info.is_scatter_file_valid()){
				//assert(0 && error_hint.c_str());
				LOGE("scatter file is invalidate: %s",scatterFile.c_str());
			} else if (!g_platform_info.is_storage_type_support()){
				LOGW(error_hint.c_str());
			}
#endif
            /* Adapt new storage layout file, 2012/12/22 } */
        }
        else if (childNode.GetName() == L"download-operation")
        {
            m_dl_operation = childNode.GetText();
        }
        else if (childNode.GetName() == L"download-os")
        {
            m_dl_os = childNode.GetText();
        }
        else if (childNode.GetName() == L"watchdog-time-interval")
        {
            ::swscanf(childNode.GetText().c_str(),
                      L"%u",
                      &m_WatchdogInterval);
        }
        else if (childNode.GetName() == L"download-list")
        {
            LoadDownloadList(childNode);
        }
        else if (childNode.GetName() == L"auto-format-FAT-setting")
        {
            m_AutoFormatEnabled = true;
        }
        else if (childNode.GetName() == L"manual-format-setting")
        {
            LoadManualFormatSetting(childNode);
        }
        else if (childNode.GetName() == L"enable-watchdog-timer")
        {
            m_WatchdogTimerEnabled = true;
        }
		else if(childNode.GetName() == L"da-download-setting") 
		{			
			for (unsigned int grandChildIndex=0;
				grandChildIndex<childNode.GetNumChildNodes();
				++grandChildIndex) {
					const Node grandChildNode = childNode.GetChildNode(grandChildIndex);
					if( L"da-download-all" == grandChildNode.GetName()) {
						m_DADLAll = (L"true" == grandChildNode.GetText() || L"TRUE" == childNode.GetText()) ? true : false;
						if (!m_DADLAll) {
							m_DADLHighSpeed = false;
							m_DADLWithoutBat = false;
							break;
						}
					} else if( L"da-download-highspeed" == grandChildNode.GetName() ) {
						m_DADLHighSpeed = (L"true" == grandChildNode.GetText() ||
							L"TRUE" == grandChildNode.GetText()) ? true : false;
					} else if (L"da-download-without-battery" == grandChildNode.GetName()) {
						m_DADLWithoutBat = (L"true" == grandChildNode.GetText() ||
							L"TRUE" == grandChildNode.GetText()) ? true : false;
					} else if(L"da-download-all-with-chksum" == grandChildNode.GetName()){
                                      m_DADLAllWithChksum = (L"true" == grandChildNode.GetText() ||
							L"TRUE" == grandChildNode.GetText()) ? true : false;
					} else if(L"da-download-all-auto-detect" == grandChildNode.GetName()){
                                      m_DADLAutoDetect= (L"true" == grandChildNode.GetText() ||
							L"TRUE" == grandChildNode.GetText()) ? true : false;
					}
			}
		}
        else
        {
            ThrowSettingError(childNode.GetName());
        }
    }
}

std::wstring DownloadSetting::GetDLOperation()  const
{
    return m_dl_operation;
}

std::wstring DownloadSetting::GetDLOS()  const
{
    return m_dl_os;
}

unsigned int DownloadSetting::GetWatchdogInterval() const
{
    return m_WatchdogInterval;
}

void DownloadSetting::SaveXML(Node &node) const
{
    Node rootNode(node.AppendChildNode(L"download-setting"));

    rootNode.AppendChildNode(L"scatter-file-path", m_ScatterFilePath);

    rootNode.AppendChildNode(L"download-operation", m_dl_operation);

    rootNode.AppendChildNode(L"download-os", m_dl_os);
    
    wostringstream watchdogInterval;
    watchdogInterval << dec
        << m_WatchdogInterval;
    rootNode.AppendChildNode(L"watchdog-time-interval", watchdogInterval.str());

    Node childNode(rootNode.AppendChildNode(L"download-list"));

    for (vector<Download_Item>::const_iterator it = m_DownloadList.begin();
         it != m_DownloadList.end();
         ++it)
    {
        Node rom_childNode(childNode.AppendChildNode(L"download-rom-item"));

        rom_childNode.AppendChildNode(L"download-item", (*it).name);
        rom_childNode.AppendChildNode(L"download-file-path", (*it).path);
    }

    if (IsAutoFormatEnabled())
    {
        rootNode.AppendChildNode(L"auto-format-FAT-setting");
    }
    else if (IsManualFormatEnabled())
    {
        Node childNode(rootNode.AppendChildNode(L"manual-format-setting"));

        wostringstream address;
        address << hex << "0x"
                << setfill('0') << setw(8)
                << m_ManualFormatBeginAddress;
        childNode.AppendChildNode(L"begin-address", address.str());

        wostringstream length;
        length << hex << "0x" 
               << setfill('0') << setw(8)
               << m_ManualFormatLength;
        childNode.AppendChildNode(L"length", length.str());
    }

    if (IsWatchdogTimerEnabled())
    {
        rootNode.AppendChildNode(L"enable-watchdog-timer");
    }

	if (IsDADownloadAll()) {
		Node daNode = rootNode.AppendChildNode(L"da-download-setting");
		daNode.AppendChildNode(L"da-download-all", L"true");
		daNode.AppendChildNode(L"da-download-highspeed", IsDADownloadHighSpeed() ? L"true" : L"false");
		daNode.AppendChildNode(L"da-download-without-battery", IsDADownloadWithoutBattery() ? L"true" : L"false");
		daNode.AppendChildNode(L"da-download-all-with-chksum", IsDADownloadAllWithChksum() ? L"true" : L"false");
		daNode.AppendChildNode(L"da-download-all-auto-detect", IsDADLAutoDetect() ? L"true" : L"false");
	} else {
		Node daNode = rootNode.AppendChildNode(L"da-download-setting");
        daNode.AppendChildNode(L"da-download-all", L"false");
		daNode.AppendChildNode(L"da-download-highspeed", L"false");
		daNode.AppendChildNode(L"da-download-without-battery", L"false");
		daNode.AppendChildNode(L"da-download-all-with-chksum", L"false");
		daNode.AppendChildNode(L"da-download-all-auto-detect", L"false");
		
	}
}

SharedPtr<Command> DownloadSetting::CreateCommand(
                                const GeneralSetting &generalSetting) const
{
    return SharedPtr<Command>(new DownloadCommand(generalSetting, *this));
}

DownloadSetting* DownloadSetting::Clone() const
{
    return new DownloadSetting(*this);
}

void DownloadSetting::Dump() const
{
    USES_CONVERSION;

    Logger::GetLogger() << Logger::Info
           << "[Download setting]"   << endl
           << "    Scatter filepath = "
           << W2CA(m_ScatterFilePath.c_str()) << endl;

	if(this->IsDADownloadAll()) {
		Logger::GetLogger() << Logger::Info
		<<"[DA Download Setting]" <<endl
		<<" DA Download All = "<<"Yes"<<endl
		<<" DA Download Enable High Speed= "
		<<((this->IsDADownloadHighSpeed()) ? "Yes" : "No")<<endl
		<<" DA Download without battery= "
		<<((this->IsDADownloadWithoutBattery()) ? "Yes" : "No")<<endl;
	}

    if (m_DownloadList.size() > 0)
    {
    	Logger::GetLogger() << " Download list = ";

        for (vector<Download_Item>::const_iterator it = m_DownloadList.begin();
             it != m_DownloadList.end();
             ++it)
        {
            Logger::GetLogger() << W2CA((*it).name.c_str()) << " ";
        }

        Logger::GetLogger() << endl;
    }

    if (m_AutoFormatEnabled)
    {
        Logger::GetLogger() << "    Auto format enabled = Yes" << endl;
    }
    else if (IsManualFormatEnabled())
    {
        Logger::GetLogger() << hex;
        Logger::GetLogger() << "    Manual format begin address = "
               << DumpHex(m_ManualFormatBeginAddress)<< endl;
        Logger::GetLogger() << "    Manual format length = "
               << DumpHex(m_ManualFormatLength)<<endl;
        Logger::GetLogger() << dec;
    }

    if (m_WatchdogTimerEnabled)
    {
        Logger::GetLogger() << "    Watchdog timer enabled = Yes" << endl;
    }
}


void DownloadSetting::LoadDownloadList(const Node &node)
{
    for (unsigned int childIndex=0;
         childIndex<node.GetNumChildNodes();
         ++childIndex)
    {
        const Node childNode = node.GetChildNode(childIndex);

        if (childNode.GetName() == L"download-rom-item")
        {
            const Node childNode_0 = childNode.GetChildNode(0);
            const Node childNode_1 = childNode.GetChildNode(1);

            if(   childNode_0.GetName() == L"download-item"
               && childNode_1.GetName() == L"download-file-path")
            {
                m_DownloadList.push_back(Download_Item(childNode_0.GetText(), /*item*/
                                                       childNode_1.GetText() /*path*/));
            }
            else
            {
                ThrowSettingError(childNode.GetName());
            }
        }
        else
        {
            ThrowSettingError(childNode.GetName());
        }
    }
}

void DownloadSetting::LoadManualFormatSetting(const Node &node)
{
    for (unsigned int childIndex=0;
         childIndex<node.GetNumChildNodes();
         ++childIndex)
    {
        const Node childNode = node.GetChildNode(childIndex);

        if (childNode.GetName() == L"begin-address")
        {
            // check result?
            ::swscanf(childNode.GetText().c_str(),
                      L"%X",
                      &m_ManualFormatBeginAddress);
        }
        else if (childNode.GetName() == L"length")
        {
            ::swscanf(childNode.GetText().c_str(),
                      L"%X",
                      &m_ManualFormatLength);
        }
        else
        {
            ThrowSettingError(childNode.GetName());
        }
    }
}



FormatSetting::FormatSetting(const Node &node)
    : m_AutoFormatEnabled(false),
      m_AutoFormatFlag(FORMAT_ALL_EXP_BL),
      m_StorageType(HW_STORAGE_NOR),
      m_ManualFormatBeginAddress(0),
      m_ManualFormatLength(0),
      m_WatchdogTimerEnabled(false),
      m_WatchdogInterval(15000)
{
    LoadXML(node);
}

FormatSetting::FormatSetting(bool autoFormatEnabled,
                             HW_StorageType_E storageType,
                             unsigned long long manualFormatBeginAddress,
                             unsigned long long manualFormatLength,
                             bool watchdogTimerEnabled,
                             unsigned int watchdogInterval,
				   bool isPhysicallyFormat,
                             NandAutoFormat_E autoFormatFlag)
    : m_AutoFormatEnabled(autoFormatEnabled),
      m_AutoFormatFlag(autoFormatFlag),
      m_StorageType(storageType),
      m_ManualFormatBeginAddress(manualFormatBeginAddress),
      m_ManualFormatLength(manualFormatLength),
      m_WatchdogTimerEnabled(watchdogTimerEnabled),
      m_WatchdogInterval(watchdogInterval),
      m_IsPhysicallyFormat(isPhysicallyFormat)
{
}

FormatSetting::~FormatSetting()
{
}

bool FormatSetting::IsAutoFormatEnabled() const
{
    return m_AutoFormatEnabled;
}

bool FormatSetting::IsManualFormatEnabled() const
{
    return (m_ManualFormatLength != 0);
}

HW_StorageType_E FormatSetting::GetStorageType() const
{
    return m_StorageType;
}

unsigned long long FormatSetting::GetManualFormatBeginAddress() const
{
    return m_ManualFormatBeginAddress;
}

unsigned long long FormatSetting::GetManualFormatLength() const
{
    return m_ManualFormatLength;
}

bool FormatSetting::IsWatchdogTimerEnabled() const
{
    return m_WatchdogTimerEnabled;
}

bool FormatSetting::IsPhysicallyFormat() const
{
	return m_IsPhysicallyFormat;
}

unsigned int FormatSetting::GetWatchdogInterval() const
{
    return m_WatchdogInterval;
}

NandAutoFormat_E FormatSetting::GetAutoFormatFlag() const
{
    return m_AutoFormatFlag;
}
void FormatSetting::LoadXML(const Node &node)
{
    for (unsigned int childIndex=0;
         childIndex<node.GetNumChildNodes();
         ++childIndex)
    {
        const Node childNode = node.GetChildNode(childIndex);

        /*if (childNode.GetName() == L"auto-format-FAT-setting")
        {
            m_AutoFormatEnabled = true;
        }*/
        if(childNode.GetName() == L"auto-format-setting")
        {
            m_AutoFormatEnabled = true;
            LoadAutoFormatSetting(childNode);
        }
        else if (childNode.GetName() == L"manual-format-setting")
        {
            m_AutoFormatEnabled = false;
            LoadManualFormatSetting(childNode);
        }
	  else if (childNode.GetName() == L"is-physical-format")
	  {
	      m_IsPhysicallyFormat = (L"true" == childNode.GetText() || L"TRUE" == childNode.GetText() ) ? true : false;
	  }
        else if (childNode.GetName() == L"enable-watchdog-timer")
        {
            m_WatchdogTimerEnabled = (L"true" == childNode.GetText() || L"TRUE" == childNode.GetText()) ? true : false;
        }
        else if (childNode.GetName() == L"watchdog-time-interval")
        {
            ::swscanf(childNode.GetText().c_str(),
                      L"%u",
                      &m_WatchdogInterval);
        }
        else
        {
            ThrowSettingError(childNode.GetName());
        }
    }
}

void FormatSetting::SaveXML(Node &node) const
{
    Node rootNode(node.AppendChildNode(L"format-setting"));

    if (IsAutoFormatEnabled())
    {
        //rootNode.AppendChildNode(L"auto-format-FAT-setting");
        Node childNode(rootNode.AppendChildNode(L"auto-format-setting"));
        if(m_AutoFormatFlag == FORMAT_ALL)
        {
              childNode.AppendChildNode(L"auto-format-flag", L"FORMAT_ALL");
        }
        else if(m_AutoFormatFlag == FORMAT_ALL_EXP_BL)
        {
              childNode.AppendChildNode(L"auto-format-flag", L"FORMAT_ALL_EXP_BL");
        }
        else
        {
              assert(0);
        }
    }
    else if (IsManualFormatEnabled())
    {
        Node childNode(rootNode.AppendChildNode(L"manual-format-setting"));

        if (m_StorageType == HW_STORAGE_NOR)
        {
            childNode.AppendChildNode(L"storage", L"NOR");
        }
        else if (m_StorageType == HW_STORAGE_NAND)
        {
            childNode.AppendChildNode(L"storage", L"NAND");
        }
	 else if(m_StorageType == HW_STORAGE_EMMC)
	 {
            childNode.AppendChildNode(L"storage", L"SDMMC");
	 }
        else
        {
            assert(0);
        }

        wostringstream address;
        address << hex << "0x"
                << setfill('0') << setw(8)
                << m_ManualFormatBeginAddress;
        childNode.AppendChildNode(L"begin-address", address.str());

        wostringstream length;
        length << hex << "0x" 
               << setfill('0') << setw(8)
               << m_ManualFormatLength;
        childNode.AppendChildNode(L"length", length.str());

    }
    else
    {
        assert(0);
    }

	if(IsPhysicallyFormat()) {
		rootNode.AppendChildNode(L"is-physical-format", L"true");
	} else {
		rootNode.AppendChildNode(L"is-physical-format", L"false");
	}

    if (IsWatchdogTimerEnabled())
    {
        rootNode.AppendChildNode(L"enable-watchdog-timer", L"true");
    }

    wostringstream watchdogInterval;
    watchdogInterval << dec
        << m_WatchdogInterval;
    rootNode.AppendChildNode(L"watchdog-time-interval", watchdogInterval.str());
}

SharedPtr<Command> FormatSetting::CreateCommand(
                                const GeneralSetting &generalSetting) const
{
    return SharedPtr<Command>(new FormatCommand(generalSetting, *this));
}

FormatSetting* FormatSetting::Clone() const
{
    return new FormatSetting(*this);
}

void FormatSetting::Dump() const
{
    USES_CONVERSION;

    Logger::GetLogger() << Logger::Info
           << "[Format setting]" << endl;

    if (m_AutoFormatEnabled)
    {
    	Logger::GetLogger() << "    Auto format enabled = Yes" << endl;
       Logger::GetLogger()<< "     Auto Format Flag = ";
       if(m_AutoFormatFlag == FORMAT_ALL)
       {
            Logger::GetLogger()<<"Format Whole Flash"<<endl;
       }
       else if(m_AutoFormatFlag == FORMAT_ALL_EXP_BL)
       {
            Logger::GetLogger()<<"Format Whole Flash Except Bootloader"<<endl;
       }
    }
    else if (IsManualFormatEnabled())
    {
        Logger::GetLogger() << "    Storage = ";

        if (m_StorageType == HW_STORAGE_NOR)
        {
            Logger::GetLogger() << "NOR" << endl;
        }
        else if (m_StorageType == HW_STORAGE_NAND)
        {
            Logger::GetLogger() << "NAND" << endl;
        }
	 else if(m_StorageType == HW_STORAGE_EMMC)
	 {
            Logger::GetLogger() << "EMMC" << endl;
	 }
	 else if(m_StorageType == HW_STORAGE_SDMMC)
	 {
            Logger::GetLogger() << "SDMMC" << endl;
	 }
        else
        {
            assert(0);
        }

        Logger::GetLogger() << hex;
        Logger::GetLogger() << "    Manual format begin address = "
               << DumpHex(m_ManualFormatBeginAddress)<<endl;
        Logger::GetLogger() << "    Manual format length = "
               << DumpHex(m_ManualFormatLength)<<endl;
        Logger::GetLogger() << dec;
    }

	Logger::GetLogger() <<"    Physically Format = "
		<< (m_IsPhysicallyFormat ? "Yes" : "No")
		<<endl;

    if (m_WatchdogTimerEnabled)
    {
        Logger::GetLogger() << "    Watchdog timer enabled = Yes" << endl;
        Logger::GetLogger() << "    Watchdog timer interval: "
               << GetWatchdogInterval() << "ms"<<endl;
    }
    else
    {
        LOGI("    Watchdog timer enabled = No");
    }
}

void FormatSetting::LoadAutoFormatSetting(const Node &node)
{
     for(unsigned int childIndex=0;
          childIndex<node.GetNumChildNodes();
          ++childIndex)
    {
         const Node childNode = node.GetChildNode(childIndex);
         if(childNode.GetName() == L"auto-format-flag")
         {
              if(childNode.GetText() == L"FORMAT_ALL")
              {
                   m_AutoFormatFlag = FORMAT_ALL;
              }
              else if(childNode.GetText() == L"FORMAT_ALL_EXP_BL")
              {
                   m_AutoFormatFlag = FORMAT_ALL_EXP_BL;
              }
              else
              {
                   ThrowSettingError(childNode.GetName());
              }
         }
    }
}

void FormatSetting::LoadManualFormatSetting(const Node &node)
{
    for (unsigned int childIndex=0;
         childIndex<node.GetNumChildNodes();
         ++childIndex)
    {
        const Node childNode = node.GetChildNode(childIndex);

        if (childNode.GetName() == L"storage")
        {
            if (childNode.GetText() == L"NOR")
            {
                m_StorageType = HW_STORAGE_NOR;
            }
            else if (childNode.GetText() == L"NAND")
            {
                m_StorageType = HW_STORAGE_NAND;
            }
	     else if (childNode.GetText() == L"EMMC")
	     {
                m_StorageType = HW_STORAGE_EMMC;
	     }
	     else if(childNode.GetText() == L"SDMMC")
	     {
                m_StorageType = HW_STORAGE_SDMMC;
	     }
            else
            {
                ThrowSettingError(childNode.GetName());
            }
        }
        else if (childNode.GetName() == L"begin-address")
        {
            // check result?
            ::swscanf(childNode.GetText().c_str(),
                      L"%X",
                      &m_ManualFormatBeginAddress);
        }
        else if (childNode.GetName() == L"length")
        {
            ::swscanf(childNode.GetText().c_str(),
                      L"%X",
                      &m_ManualFormatLength);
        }
        else
        {
            ThrowSettingError(childNode.GetName());
        }
    }
}

ResetToFactoryDefaultSetting::ResetToFactoryDefaultSetting(const Node &node)
    : m_ReconnectToMETAMode(false)
{
    LoadXML(node);
}

ResetToFactoryDefaultSetting::ResetToFactoryDefaultSetting(
                                            bool reconnectToMETAMode)
    : m_ReconnectToMETAMode(reconnectToMETAMode)
{
}

ResetToFactoryDefaultSetting::~ResetToFactoryDefaultSetting()
{
}

bool ResetToFactoryDefaultSetting::ShouldReconnectToMETAMode() const
{
    return m_ReconnectToMETAMode;
}

void ResetToFactoryDefaultSetting::LoadXML(const Node &node)
{
    for (unsigned int childIndex=0;
         childIndex<node.GetNumChildNodes();
         ++childIndex)
    {
        const Node childNode = node.GetChildNode(childIndex);

        if (childNode.GetName() == L"reconnect-to-META-mode")
        {
            m_ReconnectToMETAMode = true;
        }
        else
        {
            ThrowSettingError(childNode.GetName());
        }
    }
}

void ResetToFactoryDefaultSetting::SaveXML(Node &node) const
{
    Node rootNode(node.AppendChildNode(L"reset-to-factory-default-setting"));

    if (ShouldReconnectToMETAMode())
    {
        rootNode.AppendChildNode(L"reconnect-to-META-mode");
    }
}

SharedPtr<Command> ResetToFactoryDefaultSetting::CreateCommand(
                                    const GeneralSetting &generalSetting) const
{
    return SharedPtr<Command>(
                new ResetToFactoryDefaultCommand(generalSetting, *this));
}

ResetToFactoryDefaultSetting* ResetToFactoryDefaultSetting::Clone() const
{
    return new ResetToFactoryDefaultSetting(*this);
}

void ResetToFactoryDefaultSetting::Dump() const
{
    Logger::GetLogger() << Logger::Info
           << "[ResetToFactoryDefault setting]"   << endl;

    if (m_ReconnectToMETAMode)
    {
        Logger::GetLogger() << "    Reconnecting to META mode = Yes" << endl;
    }
}

BackupSetting::BackupSetting(const Node &node)
    : m_IniFilePath(),
      m_BackupDirectoryPath(),
      m_WatchdogTimerEnabled(false)
{
    LoadXML(node);
}

Write_BT_WIFI_IMEI_NVRAM_Setting::Write_BT_WIFI_IMEI_NVRAM_Setting(const Node &node)
{
    LoadXML(node);
}

BackupSetting::BackupSetting(const wstring &iniFilePath,
                             const wstring &backupDirectoryPath,
                             bool watchdogTimerEnabled)
    : m_IniFilePath(iniFilePath),
      m_BackupDirectoryPath(backupDirectoryPath),
      m_WatchdogTimerEnabled(watchdogTimerEnabled)
{
}




Write_BT_WIFI_IMEI_NVRAM_Setting::Write_BT_WIFI_IMEI_NVRAM_Setting
                            (
                             const std::wstring &m_is_write_IMEI1,
                             const std::wstring &m_is_write_IMEI2,
                             const std::wstring &m_is_write_WiFi,
                             const std::wstring &m_is_write_BT,                             
                             const std::wstring &m_asModem_Database,
                             const std::wstring &m_asAP_Database,
                             const std::wstring &m_asIMEI1_Number,
                             const std::wstring &m_asIMEI2_Number,
                             const std::wstring &m_asBT_Address,
                             const std::wstring &m_asWiFi_Address)
    : m_is_write_IMEI1(m_is_write_IMEI1),
      m_is_write_IMEI2(m_is_write_IMEI2),
      m_is_write_WiFi(m_is_write_WiFi),
      m_is_write_BT(m_is_write_BT),      
      m_asModem_Database(m_asModem_Database),
      m_asAP_Database(m_asAP_Database),
      m_asIMEI1_Number(m_asIMEI1_Number),
      m_asIMEI2_Number(m_asIMEI2_Number),
      m_asBT_Address(m_asBT_Address),
      m_asWiFi_Address(m_asWiFi_Address)
{
}

BackupSetting::~BackupSetting()
{
}
Write_BT_WIFI_IMEI_NVRAM_Setting::~Write_BT_WIFI_IMEI_NVRAM_Setting()
{
}

wstring BackupSetting::GetIniFilePath() const
{
    return m_IniFilePath;
}

wstring BackupSetting::GetBackupDirectoryPath() const
{
    return m_BackupDirectoryPath;
}

bool BackupSetting::IsWatchdogTimerEnabled() const
{
    return m_WatchdogTimerEnabled;
}

void BackupSetting::LoadXML(const Node &node)
{
    for (unsigned int childIndex=0;
         childIndex<node.GetNumChildNodes();
         ++childIndex)
    {
        const Node childNode = node.GetChildNode(childIndex);

        if (childNode.GetName() == L"ini-file-path")
        {
            m_IniFilePath = childNode.GetText();
        }
        else if (childNode.GetName() == L"backup-directory-path")
        {
            m_BackupDirectoryPath = childNode.GetText();
        }
        else if (childNode.GetName() == L"enable-watchdog-timer")
        {
            m_WatchdogTimerEnabled = true;
        }
        else
        {
            ThrowSettingError(childNode.GetName());
        }
    }
}

void BackupSetting::SaveXML(Node &node) const
{
    Node rootNode(node.AppendChildNode(L"backup-setting"));

    rootNode.AppendChildNode(L"ini-file-path", m_IniFilePath);
    rootNode.AppendChildNode(L"backup-directory-path", m_BackupDirectoryPath);

    if (IsWatchdogTimerEnabled())
    {
        rootNode.AppendChildNode(L"enable-watchdog-timer");
    }
}

void Write_BT_WIFI_IMEI_NVRAM_Setting::LoadXML(const Node &node)
{
    for (unsigned int childIndex=0;
         childIndex<node.GetNumChildNodes();
         ++childIndex)
    {
        const Node childNode = node.GetChildNode(childIndex);

        if (childNode.GetName() == L"is-write-IMEI1")
        {
            m_is_write_IMEI1 = childNode.GetText();
        }
        else if (childNode.GetName() == L"is-write-IMEI2")
        {
            m_is_write_IMEI2 = childNode.GetText();
        }
        else if (childNode.GetName() == L"is-write-WiFi")
        {
            m_is_write_WiFi = childNode.GetText();
        }
        else if (childNode.GetName() == L"is-write-BT")
        {
            m_is_write_BT = childNode.GetText();
        }        
        else if (childNode.GetName() == L"modem-database")
        {
           m_asModem_Database = childNode.GetText();
        }
        else if (childNode.GetName() == L"ap-database")
        {
           m_asAP_Database = childNode.GetText();
        }
        else if (childNode.GetName() == L"IMEI1-number")
        {
           m_asIMEI1_Number = childNode.GetText();
        }
        else if (childNode.GetName() == L"IMEI2-number")
        {
           m_asIMEI2_Number = childNode.GetText();
        }
        else if (childNode.GetName() == L"bt-address")
        {
           m_asBT_Address = childNode.GetText();
        }
        else if (childNode.GetName() == L"witi-address")
        {
           m_asWiFi_Address = childNode.GetText();
        }
        else
        {
            ThrowSettingError(childNode.GetName());
        }
    }
}

void Write_BT_WIFI_IMEI_NVRAM_Setting::SaveXML(Node &node) const
{
    Node rootNode(node.AppendChildNode(L"META-4IN1-setting"));

    rootNode.AppendChildNode(L"is-write-IMEI1", m_is_write_IMEI1);
    rootNode.AppendChildNode(L"is-write-IMEI2", m_is_write_IMEI2);
    rootNode.AppendChildNode(L"is-write-WiFi", m_is_write_WiFi);
    rootNode.AppendChildNode(L"is-write-BT", m_is_write_BT);
    rootNode.AppendChildNode(L"modem-database", m_asModem_Database);
    rootNode.AppendChildNode(L"ap-database", m_asAP_Database);
    rootNode.AppendChildNode(L"IMEI1-number", m_asIMEI1_Number);
    rootNode.AppendChildNode(L"IMEI2-number", m_asIMEI2_Number);
    rootNode.AppendChildNode(L"bt-address", m_asBT_Address);
    rootNode.AppendChildNode(L"witi-address", m_asWiFi_Address);
}

SharedPtr<Command> BackupSetting::CreateCommand(
                                const GeneralSetting &generalSetting) const
{
    return SharedPtr<Command>(new BackupCommand(generalSetting, *this));
}

SharedPtr<Command> Write_BT_WIFI_IMEI_NVRAM_Setting::CreateCommand(
                                const GeneralSetting &generalSetting) const
{
    return SharedPtr<Command>(new BT_WIFI_IMEI_NVRAMCommand(generalSetting, *this));
}

BackupSetting* BackupSetting::Clone() const
{
    return new BackupSetting(*this);
}

Write_BT_WIFI_IMEI_NVRAM_Setting* Write_BT_WIFI_IMEI_NVRAM_Setting::Clone() const
{
    return new Write_BT_WIFI_IMEI_NVRAM_Setting(*this);
}

void BackupSetting::Dump() const
{
    USES_CONVERSION;

    Logger::GetLogger() << Logger::Info
           << "[Backup setting]"   << endl
           << "    Ini file path = "
           << W2CA(m_IniFilePath.c_str()) << endl
           << "    Backup directory path = "
           << W2CA(m_BackupDirectoryPath.c_str()) << endl;

    if (m_WatchdogTimerEnabled)
    {
        Logger::GetLogger() << "    Watchdog timer enabled = Yes" << endl;
    }
}

void Write_BT_WIFI_IMEI_NVRAM_Setting::Dump() const
{
    USES_CONVERSION;

    Logger::GetLogger() << Logger::Info
           << "[BT_WIFI_IMEI_NVRAM setting]"   << endl;
}

RestoreSetting::RestoreSetting(const Node &node)
    : m_ReconnectToMETAMode(false),
      m_IniFilePath(),
      m_RestoreDirectoryPath()
{
    LoadXML(node);
}

RestoreSetting::RestoreSetting(bool reconnectToMETAMode,
                               const wstring &iniFilePath,
                               const wstring &restoreDirectoryPath)
    : m_ReconnectToMETAMode(reconnectToMETAMode),
      m_IniFilePath(iniFilePath),
      m_RestoreDirectoryPath(restoreDirectoryPath)
{
}

RestoreSetting::~RestoreSetting()
{
}

bool RestoreSetting::ShouldReconnectToMETAMode() const
{
    return m_ReconnectToMETAMode;
}

wstring RestoreSetting::GetIniFilePath() const
{
    return m_IniFilePath;
}

wstring RestoreSetting::GetRestoreDirectoryPath() const
{
    return m_RestoreDirectoryPath;
}

void RestoreSetting::LoadXML(const Node &node)
{
    for (unsigned int childIndex=0;
         childIndex<node.GetNumChildNodes();
         ++childIndex)
    {
        const Node childNode = node.GetChildNode(childIndex);

        if (childNode.GetName() == L"reconnect-to-META-mode")
        {
            m_ReconnectToMETAMode = true;
        }
        else if (childNode.GetName() == L"ini-file-path")
        {
            m_IniFilePath = childNode.GetText();
        }
        else if (childNode.GetName() == L"restore-directory-path")
        {
            m_RestoreDirectoryPath = childNode.GetText();
        }
        else
        {
            ThrowSettingError(childNode.GetName());
        }
    }
}

void RestoreSetting::SaveXML(Node &node) const
{
    Node rootNode(node.AppendChildNode(L"restore-setting"));

    rootNode.AppendChildNode(L"ini-file-path", m_IniFilePath);
    rootNode.AppendChildNode(L"restore-directory-path", m_RestoreDirectoryPath);

    if (ShouldReconnectToMETAMode())
    {
        rootNode.AppendChildNode(L"reconnect-to-META-mode");
    }
}

SharedPtr<Command> RestoreSetting::CreateCommand(
                                const GeneralSetting &generalSetting) const
{
    return SharedPtr<Command>(new RestoreCommand(generalSetting, *this));
}

RestoreSetting* RestoreSetting::Clone() const
{
    return new RestoreSetting(*this);
}

void RestoreSetting::Dump() const
{
    USES_CONVERSION;

    Logger::GetLogger() << Logger::Info
           << "[Restore setting]" << endl;

    if (m_ReconnectToMETAMode)
    {
        Logger::GetLogger() << "    Reconnecting to META mode = Yes" << endl;
    }

    Logger::GetLogger() << "    Ini file path = "
           << W2CA(m_IniFilePath.c_str()) << endl
           << "    Restore directory path = "
           << W2CA(m_RestoreDirectoryPath.c_str()) << endl;
}

//ReadbackSetting implements

static const WCHAR* READBACK_FLAG_E[NUTL_READ_FLAG_END];
static void InitReadbackFlag( void )
{
    READBACK_FLAG_E[NUTL_READ_PAGE_SPARE] = L"PageSpare";
    READBACK_FLAG_E[NUTL_READ_PAGE_ONLY] = L"PageOnly";
    READBACK_FLAG_E[NUTL_READ_SPARE_ONLY] = L"SpareOnly";
    READBACK_FLAG_E[NUTL_READ_PAGE_WITH_ECC] = L"PageWithECC";
    READBACK_FLAG_E[NUTL_VERIFY_AFTER_PROGRAM] = L"VerifyAfterProgram";
	READBACK_FLAG_E[NUTL_READ_FLAG_END] = L"UnKnown";
}

ReadbackSetting::Readback_Item::Readback_Item(unsigned short _index,
											  bool _enable,
											  NUTL_ReadFlag_E _flag, 
											  unsigned int _start_addr, 
											  unsigned int _length, 
											  std::wstring _path)
											  :index(_index),
											  flag(_flag),
											  start_addr(_start_addr),
											  length(_length),
											  path(_path)
{
}

ReadbackSetting::ReadbackSetting(const XML::Node &node)
: m_ReadbackList(),
m_IsphysicalReadback(false)
{
	InitReadbackFlag();
	InitRBFlagMap();
	LoadXML(node);
}


ReadbackSetting::ReadbackSetting(const vector<ReadbackSetting::Readback_Item> readbackList,
								 bool isphysicalReadback)
    : m_ReadbackList(readbackList),
	m_IsphysicalReadback(isphysicalReadback)
{
	InitReadbackFlag();
	InitRBFlagMap();
}

ReadbackSetting::~ReadbackSetting()
{
}

std::vector<ReadbackSetting::Readback_Item> ReadbackSetting::GetReadbackList() const
{
	return m_ReadbackList;
}

void ReadbackSetting::LoadXML(const XML::Node &node)
{
	for(unsigned int index = 0; index < node.GetNumChildNodes(); ++index) {
		const XML::Node childNode = node.GetChildNode(index);
		if ( L"readback-list" == childNode.GetName() ) {
		    LoadReadbackList(childNode);
		} else if ( L"is-physical-readback"){
             m_IsphysicalReadback = (L"true" == childNode.GetText() || L"TRUE" == childNode.GetText()) ? true : false;
	    }else {
			ThrowSettingError(childNode.GetName());
		}
	}
}

void ReadbackSetting::SaveXML(XML::Node &node) const
{
	XML::Node rootNode(node.AppendChildNode(L"readback-setting"));
	rootNode.AppendChildNode( L"is-physical-readback",
                m_IsphysicalReadback ? L"true" : L"false");
	XML::Node childNode(rootNode.AppendChildNode(L"readback-list"));

	wostringstream rb_start_address;
	wostringstream rb_length;

	for (vector<Readback_Item>::const_iterator it = m_ReadbackList.begin();
		it != m_ReadbackList.end(); ++it)	{
			Node rom_childNode(childNode.AppendChildNode(L"readback-rom-item"));
			rom_childNode.AppendChildNode(L"readback-index", 
				NumberToWString(it->GetReadbackIndex()));
			rom_childNode.AppendChildNode(L"readback-enable",
				it->GetReadbackEnable() ? L"true" : L"false");
			rom_childNode.AppendChildNode(L"readback-flag",
				READBACK_FLAG_E[it->GetReadbackFlag()]);

            //Flush and clear wostringstream
			rb_start_address.str(L"");
			rb_start_address << hex << "0x" 
				<< setfill('0') << setw(8)
				<< it->GetReadbackStartAddr();
			rom_childNode.AppendChildNode(L"start-address", rb_start_address.str());

			rb_length.str(L"");
			rb_length << hex << "0x"
				<< setfill('0') << setw(8)
				<< it->GetReadbackLength();
			rom_childNode.AppendChildNode(L"readback-length", rb_length.str());

			rom_childNode.AppendChildNode(L"download-file-path", it->GetReadbackPath());
	}

}

SharedPtr<Command> ReadbackSetting::CreateCommand (
	const GeneralSetting &generalsetting) const
{
	return SharedPtr<Command>(new ReadbackCommand(generalsetting, *this));
}

ReadbackSetting* ReadbackSetting::Clone() const
{
	return new ReadbackSetting(*this);
}

void ReadbackSetting::Dump() const
{
	USES_CONVERSION;

	Logger::GetLogger() <<Logger::Info
		<<"[Readback Setting]"<<endl;
	
	if(m_ReadbackList.size() > 0) {
		Logger::GetLogger() <<Logger::Info
			<<"Physical Readback enable: "
			<<(IsPhysicalReadbackEnabled() ? "Yes" : "No")<<endl
			<<"Readback List:"<<endl;
		for(std::vector<Readback_Item>::const_iterator it = m_ReadbackList.begin();
			it != m_ReadbackList.end(); it++) {
				Logger::GetLogger() <<Logger::Info
					<<"==========================="<<endl
					<<"Rom index: "<<NumberToString(it->GetReadbackIndex()).c_str()<<endl
					<<"Rom readback enable: "<< (it->GetReadbackEnable() ? "Yes" : "No")<<endl
					<<"Readback flag index: "<< it->GetReadbackFlag()<<endl
					<<"Readback flag: "<<W2CA(READBACK_FLAG_E[it->GetReadbackFlag()])<<endl
					<<"Readback start address: "<<DumpHex(it->GetReadbackStartAddr()).c_str()<<endl
					<<"Readback length: "<<DumpHex(it->GetReadbackLength()).c_str()<<endl
					<<"Reaback path: "<<W2CA(it->GetReadbackPath().c_str())<<endl
					<<"==========================="<<endl;
		}
	}

}

void ReadbackSetting::LoadReadbackList(const XML::Node &node)
{
	unsigned int u_start_addr =0;
	unsigned int u_length = 0;

	for (unsigned int index = 0; index < node.GetNumChildNodes(); ++index) {
		const XML::Node childNode = node.GetChildNode(index);
		if (L"readback-rom-item" == childNode.GetName()) {
			Node rom_index = childNode.GetChildNode(0);
			Node rb_enable = childNode.GetChildNode(0);
            Node rb_flag = childNode.GetChildNode(0);
			Node rb_start_addr = childNode.GetChildNode(0);
			Node rb_length = childNode.GetChildNode(0);
			Node rb_path = childNode.GetChildNode(0);
			for (unsigned int childIndex = 0; childIndex < childNode.GetNumChildNodes(); ++childIndex) {
				if (L"readback-index" == childNode.GetChildNode(childIndex).GetName()) {
					rom_index= childNode.GetChildNode(childIndex);
				}else if(L"readback-enable" == childNode.GetChildNode(childIndex).GetName()) {
					rb_enable = childNode.GetChildNode(childIndex);
			    }else if (L"readback-flag" == childNode.GetChildNode(childIndex).GetName()) {
					rb_flag = childNode.GetChildNode(childIndex);
				} else if (L"start-address" == childNode.GetChildNode(childIndex).GetName()) {
					rb_start_addr = childNode.GetChildNode(childIndex);
				} else if (L"readback-length" == childNode.GetChildNode(childIndex).GetName()) {
				    rb_length = childNode.GetChildNode(childIndex);
				} else if (L"download-file-path" == childNode.GetChildNode(childIndex).GetName()) {
					rb_path = childNode.GetChildNode(childIndex);
				} else {
					ThrowSettingError(childNode.GetName());
				}
			}

			::swscanf(rb_start_addr.GetText().c_str(), L"%X", &u_start_addr);
			::swscanf(rb_length.GetText().c_str(), L"%X", &u_length);
            
			m_ReadbackList.push_back(
				Readback_Item(
				WStringToNumber<unsigned short>(rom_index.GetText()),
				(L"true" == rb_enable.GetText()) ||  (L"TRUE" == rb_enable.GetText()),
				FindRBFlagType(rb_flag.GetText()),
				u_start_addr,
				u_length,
				rb_path.GetText()));
		}
	}
}

void ReadbackSetting::InitRBFlagMap(void)
{
	m_RBFlagMap[L"PageSpare"] = NUTL_READ_PAGE_SPARE;
	m_RBFlagMap[L"PageOnly"] = NUTL_READ_PAGE_ONLY;
	m_RBFlagMap[L"SpareOnly"] = NUTL_READ_SPARE_ONLY;
	m_RBFlagMap[L"PageWithECC"] = NUTL_READ_PAGE_WITH_ECC;
	m_RBFlagMap[L"VerifyAfterProgram"] = NUTL_VERIFY_AFTER_PROGRAM;
	m_RBFlagMap[L"UnKnown"] = NUTL_READ_FLAG_END;
}

/*
return related NUTL_ReadFlag_E according to rb_flag string;
return NUTL_READ_FLAG_END if mapping relationship is not found
*/
NUTL_ReadFlag_E ReadbackSetting::FindRBFlagType(const std::wstring& rb_flag)
{
	std::map<std::wstring, NUTL_ReadFlag_E>::const_iterator it = m_RBFlagMap.find(rb_flag.c_str());
	if ( it != m_RBFlagMap.end() ) {
		return it->second;
	} else {
		return NUTL_READ_FLAG_END;
	}
}

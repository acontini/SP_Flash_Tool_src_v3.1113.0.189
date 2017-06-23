/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/

#ifndef _SETTING_H
#define _SETTING_H

#include <string>
#include <vector>
#include <map>
#include "DOWNLOAD.H"
#include "SharedPtr.h"
#include "XMLSerializable.h"
#include "FlashToolTypedefs.h"

class Command;
class XML::Node;

namespace ConsoleMode
{
    class GeneralSetting : public XML::Serializable
    {
    public:
        explicit GeneralSetting(const XML::Node &node);
        GeneralSetting(bool logsEnable,
                       const std::wstring &comPort,
                       const std::wstring &flash_operation,
                       bool checkBasebandVersion,
                       const std::wstring &downloadAgentFilePath,
                       const std::wstring &authenticationFilePath,
                       const std::wstring &scertFilePath,
                       const unsigned int sleepTime = 1000);
        virtual ~GeneralSetting();

    public:

        HW_StorageType_E Get_flash_operation() const;

        std::wstring GetComPort() const;
        void SetComPort(const std::wstring &comPort);
	 std::wstring GetPortType() const;
	 void SetPortType(const std::wstring &portType);

        bool IsCheckBasebandVersionEnabled() const;

        std::wstring GetDownloadAgentFilePath() const;
        void SetDownloadAgentFilePath(
                const std::wstring &downloadAgentFilePath);

        std::wstring GetAuthenticationFilePath() const;
		std::wstring GetSCertFilePath() const;

        bool IsLogsEnabled() const;
	  unsigned int GetSleepTime() const;
#if 0
        std::wstring GetFlashBinFilePath() const;
#endif
        void Dump() const;

    // XML::Serializable interface
    public:
        virtual void LoadXML(const XML::Node &node);
        virtual void SaveXML(XML::Node &node) const;

    private:
        std::wstring m_flash_operation;
        HW_StorageType_E m_flash_type;
        std::wstring m_ComPort;
	 //used to auto test
	  std::wstring m_PortType; //usb, uart...if none, do not use this.
        bool m_CheckBasebandVersion;
        std::wstring m_DownloadAgentFilePath;
        std::wstring m_AuthenticationFilePath;
        std::wstring m_SCertFilePath;
        bool m_LogsEnable;
	  unsigned int m_sleepTime;
    };

    class CommandSetting : public XML::Serializable
    {
    public:
        virtual ~CommandSetting() {}

    protected:
        CommandSetting() {}

    public:
        virtual SharedPtr<Command> CreateCommand(
                            const GeneralSetting &generalSetting) const = 0;

        // Virtual copy constructor
        virtual CommandSetting* Clone() const = 0;

        // For debugging purpose
        virtual void Dump() const = 0;
    };

    class DownloadSetting : public CommandSetting
    {
    public:

        class   Download_Item{
        public:
            Download_Item(){};
            Download_Item(std::wstring _name,
                          std::wstring _path);
            /*:name(_name),
             path(_path)
             {};*/

            std::wstring   name;
            std::wstring   path;
        };

        explicit DownloadSetting(const XML::Node &node);
        DownloadSetting(const std::wstring &scatterFilePath,
                        const std::wstring &dl_operation,
                        const std::wstring &dl_os,
                        const std::vector<DownloadSetting::Download_Item> downloadList,
                        bool autoFormatEnabled,
                        unsigned int manualFormatBeginAddress,
                        unsigned int manualFormatLength,
                        bool watchdogTimerEnabled,
						bool daDLAll,
						bool daDLHighSpeed,
						bool daDLWithoutBat,
						bool daDLAllWithChksum,
						bool daDLAutoDetect = true);
        virtual ~DownloadSetting();

    public:
        std::wstring GetScatterFilePath() const;
        std::wstring GetDLOperation() const;
        std::wstring GetDLOS()  const;
        unsigned int GetWatchdogInterval() const;  
        //std::vector<std::wstring> GetDownloadList() const;
        std::vector<DownloadSetting::Download_Item>  GetDownloadList() const;
        bool IsAutoFormatEnabled() const;
        bool IsManualFormatEnabled() const;
        unsigned int GetManualFormatBeginAddress() const;
        unsigned int GetManualFormatLength() const;
        bool IsWatchdogTimerEnabled() const;

		bool IsDADownloadAll() const {
			return m_DADLAll;
		}
		bool IsDADownloadHighSpeed() const {
			return m_DADLHighSpeed;
		}
		bool IsDADownloadWithoutBattery() const {
			return m_DADLWithoutBat;
		}
		bool IsDADownloadAllWithChksum() const {
                   return m_DADLAllWithChksum;
		}
		bool IsDADLAutoDetect() const{
                   return m_DADLAutoDetect;
		}

    // XML::Serializable interface
    public:
        virtual void LoadXML(const XML::Node &node);
        virtual void SaveXML(XML::Node &node) const;

    // CommandSetting interface
    public:
        virtual SharedPtr<Command> CreateCommand(
                            const GeneralSetting &generalSetting) const;
        virtual DownloadSetting* Clone() const;
        virtual void Dump() const;

    private:
        void LoadDownloadList(const XML::Node &node);
        void LoadManualFormatSetting(const XML::Node &node);

    private:
        std::wstring m_ScatterFilePath;

        std::wstring m_dl_operation;

        // associate with "download-os"
        std::wstring m_dl_os; //"Android" or "WM"
        unsigned int m_WatchdogInterval;

        std::vector<Download_Item> m_DownloadList;
  
        bool m_AutoFormatEnabled;
        unsigned long long m_ManualFormatBeginAddress;
        unsigned long long m_ManualFormatLength;
        bool m_WatchdogTimerEnabled;
		bool m_DADLAll;
		bool m_DADLHighSpeed;
		bool m_DADLWithoutBat;
		bool m_DADLAllWithChksum;
		bool m_DADLAutoDetect;
    };

    class FormatSetting : public CommandSetting
    {
    public:
        explicit FormatSetting(const XML::Node &node);

        // FIXME: bad interface
        FormatSetting(bool autoFormatEnabled,
                      HW_StorageType_E storageType,
                      unsigned long long manualFormatBeginAddress,
                      unsigned long long manualFormatLength,
                      bool watchdogTimerEnabled,
                      unsigned int m_WatchdogInterval,
		      bool isPhysicallyFormat,
                      NandAutoFormat_E autoFormatFlag = FORMAT_ALL_EXP_BL);
        virtual ~FormatSetting();

    public:
        bool IsAutoFormatEnabled() const;
        bool IsManualFormatEnabled() const;
        HW_StorageType_E GetStorageType() const;
        unsigned long long GetManualFormatBeginAddress() const;
        unsigned long long GetManualFormatLength() const;
        bool IsWatchdogTimerEnabled() const;
        unsigned int GetWatchdogInterval() const;
		bool IsPhysicallyFormat() const;
	 NandAutoFormat_E GetAutoFormatFlag() const;  

    // XML::Serializable interface
    public:
        virtual void LoadXML(const XML::Node &node);
        virtual void SaveXML(XML::Node &node) const;

    // CommandSetting interface
    public:
        virtual SharedPtr<Command> CreateCommand(
                            const GeneralSetting &generalSetting) const;
        virtual FormatSetting* Clone() const;
        virtual void Dump() const;

    private:
        void LoadManualFormatSetting(const XML::Node &node);
        void LoadAutoFormatSetting(const XML::Node &node);

    private:
        // FIXME: NOR or NAND
        bool m_AutoFormatEnabled;
        NandAutoFormat_E m_AutoFormatFlag;
        HW_StorageType_E m_StorageType;
        unsigned long long m_ManualFormatBeginAddress;
        unsigned long long m_ManualFormatLength;
        bool m_WatchdogTimerEnabled;
        unsigned int m_WatchdogInterval;
		bool m_IsPhysicallyFormat;
    };

    class ResetToFactoryDefaultSetting : public CommandSetting
    {
    public:
        explicit ResetToFactoryDefaultSetting(const XML::Node &node);
        ResetToFactoryDefaultSetting(bool reconnectToMETAMode);
        virtual ~ResetToFactoryDefaultSetting();

    public:
        bool ShouldReconnectToMETAMode() const; // bad name

    // XML::Serializable interface
    public:
        virtual void LoadXML(const XML::Node &node);
        virtual void SaveXML(XML::Node &node) const;

    // CommandSetting interface
    public:
        virtual SharedPtr<Command> CreateCommand(
                            const GeneralSetting &generalSetting) const;
        virtual ResetToFactoryDefaultSetting* Clone() const;
        virtual void Dump() const;

    private:
        bool m_ReconnectToMETAMode;
    };

     //BT WIFI IMEI NVRAM also called 4 in 1
    class Write_BT_WIFI_IMEI_NVRAM_Setting : public CommandSetting
    {
    public:
        explicit Write_BT_WIFI_IMEI_NVRAM_Setting(const XML::Node &node);
        Write_BT_WIFI_IMEI_NVRAM_Setting(
                                         const std::wstring &m_is_write_IMEI1,
                                         const std::wstring &m_is_write_IMEI2,
                                         const std::wstring &m_is_write_WiFi,
                                         const std::wstring &m_is_write_BT,                                         
                                         const std::wstring &m_asModem_Database,
                                         const std::wstring &m_asAP_Database,
                                         const std::wstring &m_asIMEI1_Number,
                                         const std::wstring &m_asIMEI2_Number,
                                         const std::wstring &m_asBT_Address,
                                         const std::wstring &m_asWiFi_Address);
        virtual ~Write_BT_WIFI_IMEI_NVRAM_Setting();

    public:


    // XML::Serializable interface
    public:
        virtual void LoadXML(const XML::Node &node);
        virtual void SaveXML(XML::Node &node) const;

    // CommandSetting interface
    public:
        virtual SharedPtr<Command> CreateCommand(
                            const GeneralSetting &generalSetting) const;
        virtual Write_BT_WIFI_IMEI_NVRAM_Setting* Clone() const;
        virtual void Dump() const;

        std::wstring m_is_write_IMEI1;
        std::wstring m_is_write_IMEI2;
        std::wstring m_is_write_WiFi;
        std::wstring m_is_write_BT;
        std::wstring m_asModem_Database;
        std::wstring m_asAP_Database;
        std::wstring m_asIMEI1_Number;
        std::wstring m_asIMEI2_Number;
        std::wstring m_asBT_Address;
        std::wstring m_asWiFi_Address;
    };

    class BackupSetting : public CommandSetting
    {
    public:
        explicit BackupSetting(const XML::Node &node);
        BackupSetting(const std::wstring &iniFilePath,
                      const std::wstring &backupDirectoryPath,
                      bool watchdogTimerEnabled);
        virtual ~BackupSetting();

    public:
        std::wstring GetIniFilePath() const;
        std::wstring GetBackupDirectoryPath() const;
        bool IsWatchdogTimerEnabled() const;

    // XML::Serializable interface
    public:
        virtual void LoadXML(const XML::Node &node);
        virtual void SaveXML(XML::Node &node) const;

    // CommandSetting interface
    public:
        virtual SharedPtr<Command> CreateCommand(
                            const GeneralSetting &generalSetting) const;
        virtual BackupSetting* Clone() const;
        virtual void Dump() const;

    private:
        std::wstring m_IniFilePath;
        std::wstring m_BackupDirectoryPath;
        bool m_WatchdogTimerEnabled;
    };

    class RestoreSetting : public CommandSetting
    {
    public:
        explicit RestoreSetting(const XML::Node &node);
        RestoreSetting(bool reconnectToMETAMode,
                       const std::wstring &iniFilePath,
                       const std::wstring &restoreDirectoryPath);
        virtual ~RestoreSetting();

    public:
        bool ShouldReconnectToMETAMode() const; // bad name
        std::wstring GetIniFilePath() const;
        std::wstring GetRestoreDirectoryPath() const;

    // XML::Serializable interface
    public:
        virtual void LoadXML(const XML::Node &node);
        virtual void SaveXML(XML::Node &node) const;

    // CommandSetting interface
    public:
        virtual SharedPtr<Command> CreateCommand(
                            const GeneralSetting &generalSetting) const;
        virtual RestoreSetting* Clone() const;
        virtual void Dump() const;

    private:
        bool m_ReconnectToMETAMode;
        std::wstring m_IniFilePath;
        std::wstring m_RestoreDirectoryPath;
    };

	class ReadbackSetting : public CommandSetting
	{
	public:

		class   Readback_Item{
		public:
			Readback_Item(){};
			Readback_Item(unsigned short _index,
				bool _enable,
				NUTL_ReadFlag_E _flag,
				unsigned int _start_addr,
				unsigned int _length,
				std::wstring _path);

			unsigned short GetReadbackIndex(void) const {
				return index;
			}
			void SetReadbackIndex(unsigned short _index) {
				index = _index;
			}

			bool GetReadbackEnable(void) const {
				return enable;
			}
			void SetReadbackEnable(bool _enable) {
				enable = _enable;
			}

			NUTL_ReadFlag_E GetReadbackFlag(void) const {
				return flag;
			}
			void SetReadbackFlag(NUTL_ReadFlag_E _flag) {
				flag = _flag;
			}

			unsigned long long GetReadbackStartAddr(void) const {
				return start_addr;
			} 
			void SetReadbackStartAddr(unsigned long long _start_addr) {
				start_addr = _start_addr;
			} 

			unsigned int GetReadbackLength(void) const {
				return length;
			}
			void SetReadbackLength(unsigned int _length) {
				length = _length;
			}

			std::wstring GetReadbackPath(void) const {
				return path;
			}
			void SetReadbackPath(const std::wstring& _path) {
				path = _path;
			}

		private:
			unsigned short index;
			bool enable;
			NUTL_ReadFlag_E flag;
			unsigned long long start_addr;
			unsigned int length;
			std::wstring   path;
		};

		explicit ReadbackSetting(const XML::Node &node);
		ReadbackSetting(const std::vector<ReadbackSetting::Readback_Item> readbackList, bool isphysicalReadback);
		virtual ~ReadbackSetting();

	public:
		std::vector<ReadbackSetting::Readback_Item>  GetReadbackList() const;

		bool IsPhysicalReadbackEnabled() const {
			return m_IsphysicalReadback;
		}
		// XML::Serializable interface
	public:
		virtual void LoadXML(const XML::Node &node);
		virtual void SaveXML(XML::Node &node) const;

		// CommandSetting interface
	public:
		virtual SharedPtr<Command> CreateCommand(
			const GeneralSetting &generalSetting) const;
		virtual ReadbackSetting* Clone() const;
		virtual void Dump() const;

	private:
		void LoadReadbackList(const XML::Node &node);
		void InitRBFlagMap(void);
		NUTL_ReadFlag_E FindRBFlagType(const std::wstring& rb_flag);

	private:
		std::vector<Readback_Item> m_ReadbackList;
		bool m_IsphysicalReadback;
		std::map<std::wstring, NUTL_ReadFlag_E> m_RBFlagMap;
	};

};
#endif // _SETTING_H

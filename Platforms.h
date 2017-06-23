/*
 * Platforms.h
 *
 *  Created on: May 5, 2011
 *      Author: MTK81019
 */

#ifndef PLATFORMS_H_
#define PLATFORMS_H_

#include <iostream>
#include <map>

#include "XMLSerializable.h"

using std::string;

class Platform : public XML::Serializable
{
public:
	Platform();

    virtual void LoadXML(const XML::Node &node);
    virtual void SaveXML(XML::Node &node) const;

    std::string Dump() const;

    //getters
	string getName() const{
		return name;
	}
	string getSimpleName() const{
		return simple_name;
	}
	bool supportUSBDownload() const{
		return usb_download_support;
	}
    bool supportDLAutoDetectBattery() const{
        return dl_auto_detect_battery;
    }
	bool supportNandUtil() const{
		return nand_util_support;
	}
	bool supportBackupRestore() const{
		return backup_restore_support;
	}
	bool supportDADownloadAll() const{
		return da_dl_all_support;
	}
	bool isDefaultNotSwitchSpeed()const{
		return default_do_not_switch_speed;
	}
	bool supportUSBHighSpeed() const{
		return usb_highspeed_support;
	}
	bool supportLogicalAddress() const{
		return logical_addr_support;
	}
	bool supportImageLock() const{
		return image_lock_support;
	}
	bool supportAutoFormat() const{
		return auto_format_support;
	}
	bool doesAlertNoCOMPort() const{
		return alert_no_com_port;
	}
	bool doesUSBDLControlBit() const{
		return usb_dl_control_bit;
	}
	unsigned int getDefaultBMTBlocks() const{
		return default_bmt_blocks;
	}
    bool supportFirmwareUpgrade() const {
        return firmware_upgrade_enable;
    }
    void setChipSupported(bool is_support) {
        is_chip_supported = is_support;
    }
    bool isChipSupported() const {
        return is_chip_supported;
    }
	bool isDefaultSetFormatLength() const {
		return is_default_set_format_length;
	}
	bool IsAutoPollingEnable(void) const {
		return this->is_auto_polling_enable_;
	}
	unsigned int AutoPollingUpperLimit(void) const {
		return this->auto_polling_upper_limit_;
	}
	bool supportAutoFormatAll()
      {
            return this->support_auto_format_all_;
	}
private:
	bool parseBoolean(const std::wstring &value);

	string name;
	string simple_name;
	bool usb_download_support;
	bool nand_util_support;
	bool backup_restore_support;
	bool image_lock_support;
	bool da_dl_all_support;
	bool usb_highspeed_support;
	bool logical_addr_support;
	bool alert_no_com_port;
	bool auto_format_support;
	bool usb_dl_control_bit;
	unsigned int default_bmt_blocks;
    bool firmware_upgrade_enable;
    bool default_do_not_switch_speed;
    //Judge scatter load is supported by platform.xml
    bool is_chip_supported;
	//Modify to support auto detect battery
	bool dl_auto_detect_battery;
	//Enable set defalut format length
	bool is_default_set_format_length;
	//Auto Polling
	bool is_auto_polling_enable_;
	unsigned int auto_polling_upper_limit_;
	bool support_auto_format_all_;
};


class PlatformTable
{
public:
	PlatformTable(const std::wstring &filename);

	Platform queryByScatter(const std::string &scatter);
	Platform queryByChipName(const std::string &chipName);
	Platform queryBySimpleName(const  string & simpleName);

private:
	void LoadFile(const std::wstring &filename);

	//parse out 'MT65XX' from scatter file name
	std::string parseScatterName(const std::string &value);

	//parse out 'MT65XX_SXX' from chip name
	std::string parseChipName(const std::string &value);

	std::map<std::string, Platform> nameMap;
	std::map<std::string, Platform> simpleNameMap;

	friend PlatformTable& GetPlatformTable();
};

PlatformTable& GetPlatformTable();

#endif /* PLATFORMS_H_ */

#ifndef FIRMWARE_UPGRADE_CONFIG_H
#define FIRMWARE_UPGRADE_CONFIG_H

#include "RegionFormatSetting.h"
#include "NandLayoutParameter.h"
#include "Command.h"

#include <list>

class FirmwareUpgradeConfig
{
public:
	FirmwareUpgradeConfig();
	~FirmwareUpgradeConfig();

	void AddSettings(const RegionFormatSetting *region_setting);
	SharedPtr<Command> CreateCommand(NandLayoutParameter &para);

private:

	std::list<SharedPtr<RegionFormatSetting> > region_format_settings;
};

#endif
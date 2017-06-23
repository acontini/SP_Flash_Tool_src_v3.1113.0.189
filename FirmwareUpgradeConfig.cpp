#include "FirmwareUpgradeConfig.h"

FirmwareUpgradeConfig::FirmwareUpgradeConfig()
{}

FirmwareUpgradeConfig::~FirmwareUpgradeConfig()
{}

void FirmwareUpgradeConfig::AddSettings(const RegionFormatSetting *region_setting)
{
      region_format_settings.push_back(
           SharedPtr<RegionFormatSetting>(region_setting->Clone()));

}

SharedPtr<Command> FirmwareUpgradeConfig::CreateCommand(NandLayoutParameter &para)
{
      SharedPtr<MacroCommand> cmd(new MacroCommand());

     for(std::list<SharedPtr<RegionFormatSetting> >::const_iterator it = region_format_settings.begin();
	    it != region_format_settings.end(); ++it)
   {
          cmd->AddOperCommand((*it)->CreateCommand(para));
   }

   return cmd;
}






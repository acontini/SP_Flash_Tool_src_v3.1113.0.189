
#include "BackupConfig.h"
#include "Logger.h"
#include "FlashToolErrorCodeDef.h"
#include "GlobalData.h"
#include "main.h"

#include <inifiles.hpp>

BackupConfig::BackupConfig(const std::string &backupFolder)
 :backup_folder_(backupFolder){
               
}
BackupConfig::~BackupConfig()
{}

int BackupConfig::InitBackupInfoTable()
{ 
    bool isExist = true;
    
    int ret = S_DONE;

    PART_INFO partiInfo;
    memset(&partiInfo, 0, sizeof(PART_INFO));

    backup_map_.clear();
    backup_roms_.clear();

   ret = SetupBackupItems();

   ret = SetupTargetLayoutMap();

   if(!is_target_layout_map_ready_)
   {
          LOGE("Get PMT fail.");
	   ret = FT_UPGRADE_GET_PMT_FAIL;
   }else{ 

    BackupItem backupItem;

    std::list<ROM_INFO>::iterator it = backup_roms_.begin();
 
    for(; it != backup_roms_.end(); ++it)
    {
        isExist = SearchPartitionInfoInMap((*it).name, &partiInfo);
	  if(!isExist)
 	  {
              if(strstr((*it).name, "NVRAM") != NULL)
              {
                 LOGE("NVRAM infomation could not find!");
		    ret = FT_UPGRADE_BACKUP_ROM_NOT_EXSIT;
		    break;
		 }

	       LOG("partition (%s) is not exist in target.", (*it).name);

		 continue;
	  } 	  

      	  backupItem.set_file_path(backup_folder_ + "\\" + (*it).name +".img");
	  LOGD("item name(%s), file name(%s)", (*it).name, backupItem.file_path().c_str());		
          backupItem.set_chksum_file(backup_folder_ + "\\" +(*it).name+".chksum");
	  LOGD("item name(%s), chksum file name(%s)", (*it).name, backupItem.chksum_file().c_str());	

	  backupItem.set_length(partiInfo.image_length);
	  backupItem.set_start_addr(partiInfo.begin_addr);
	  backupItem.set_partition_name((*it).name);
          backupItem.set_rom_type((*it).rom_type);

	  backup_map_.insert(pair<std::string, BackupItem>((*it).name, backupItem));
    }}

    return ret;
}

std::list<ROM_INFO> BackupConfig:: backup_roms()
{
     	//std::list<std::string> backup_roms_tmp;
	//Attention: allocate space for dest vector before std::copy
       //	backup_roms_tmp.clear();
	//backup_roms_tmp.resize(backup_roms_.size());
       //	std::copy(backup_roms_.begin(), backup_roms_.end(), backup_roms_tmp.begin());
	return backup_roms_;
}

bool BackupConfig::QueryBackupItemByPartitionName(std::string partition_name, BackupItem *backup_item)
{
      bool is_found = false;

      std::map<std::string, BackupItem>::iterator it = backup_map_.begin();
      for(; it!= backup_map_.end(); it++)
      	{
             if(it->first == partition_name)
             {
                  backup_item->set_chksum_file(it->second.chksum_file());
		     backup_item->set_file_path(it->second.file_path());
		     backup_item->set_length(it->second.length());
		     backup_item->set_partition_name(it->second.partition_name());
		     backup_item->set_start_addr(it->second.start_addr());
                  backup_item->set_rom_type(it->second.rom_type());
		     is_found = true;

		     break;
		}
      }

      return is_found;
}

int BackupConfig::SetupTargetLayoutMap()
{
    assert( NULL != g_ft_handle);
    int ret = 0;
    unsigned int rom_count = 0;
    std::string name;
    PART_INFO* p_part_info = NULL;
    PART_INFO part_info;
    memset(&part_info, 0, sizeof(PART_INFO));

    if(target_layout_map_.size() != 0)
    {
         target_layout_map_.clear();
	   LOGD("clear old data in the map.");
    }

    do {
        ret = FlashTool_ReadPartitionCount(g_ft_handle, &rom_count);
        if( S_DONE != ret ) {
			LOG("ERROR: %s():  FlashTool_ReadPartitionCount() failed, error code is(%d).", __FUNC__, ret);
			is_target_layout_map_ready_ = false;
            break;
        }
		
        p_part_info = new PART_INFO[rom_count];
        ret = FlashTool_ReadPartitionInfo(g_ft_handle, p_part_info, rom_count);
     	if( S_DONE != ret ) {
            LOG("ERROR: %s(): FlashTool_ReadPartitionInfo() failed!, error code(%d).", __FUNC__, ret);
            is_target_layout_map_ready_ = false;
    		break;
    	}

        for(unsigned int i = 0; i < rom_count; i++){
			part_info.begin_addr = p_part_info[i].begin_addr;
			part_info.image_length = p_part_info[i].image_length;
		      //name = p_part_info[i].name;

			LOGD("partition name(%s)", p_part_info[i].name);
			target_layout_map_.insert(std::make_pair<std::string, PART_INFO>(p_part_info[i].name, part_info));
        }
        is_target_layout_map_ready_ = true;
        LOG("%s(): target layout map is ready.", __FUNC__);
    }while(0);

    if( NULL != p_part_info ){
        delete[] p_part_info;
        p_part_info = NULL;
    }

    return ret;

}

bool BackupConfig::SearchPartitionInfoInMap(const std::string& name, PART_INFO *p_part_info)
{
	assert(p_part_info != NULL);
	std::map<std::string, PART_INFO>::const_iterator it = target_layout_map_.begin();
	while(it != target_layout_map_.end()) {
		
		if(it->first.find(name) != std::string::npos) {
			p_part_info->begin_addr = it->second.begin_addr;
			p_part_info->image_length = it->second.image_length;
			LOG("%s(): Obtain %s partition info: begin_addr(0x%I64x), length(0x%I64x).",
					__FUNC__, name.c_str(), p_part_info->begin_addr, p_part_info->image_length);
			break;
		}
		it++;
	}
	if (it == target_layout_map_.end()) {
		LOG("ERROR: %s(): Could not find %s in the layout table.", __FUNC__, name.c_str());
		return false;
	}

	return true;
}

int BackupConfig::SetupBackupItems()
{
    unsigned short rom_count;
    ROM_INFO rom_infos[MAX_LOAD_SECTIONS];

    int ret = S_DONE;

    if(!DL_GetCount(g_pCurNode->m_dl_handle, &rom_count))
    {
          if(!DL_Rom_GetInfoAll(g_pCurNode->m_dl_handle, rom_infos, MAX_LOAD_SECTIONS))
          {
               for(int i = 0; i < rom_count; i++)
               {
                    if(rom_infos[i].operation_type == OPER_PROTECTED ||
                         rom_infos[i].operation_type == OPER_BINREGION)
                    {
                          backup_roms_.push_back(rom_infos[i]);
                          LOGD("Rom(%s), oper type(%d)",
                                     rom_infos[i].name, rom_infos[i].rom_type);
                    }
               }
          }
    }

    return ret;
}




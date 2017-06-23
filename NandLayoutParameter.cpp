/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/
#include "NandLayoutParameter.h"
#include "SharedPtr.h"
#include "Logger.h"
#include "FlashToolErrorCodeDef.h"
#include "Utility.h"

#ifdef __BORLANDC__
#pragma warn -8004
#endif

using std::string;
using std::vector;

const unsigned short NandLayoutParameter::kVitaltemsCount(3);
const std::string NandLayoutParameter::kVisibleMark("_NODL");
const std::string NandLayoutParameter::kRsvMark("_RSV_");
const std::string NandLayoutParameter::kBMTMark("BMTPOOL");

NandLayoutParameter::NandLayoutParameter(const DL_HANDLE_T dl_handle, 
		const FLASHTOOL_API_HANDLE_T flashtool_handle,
		const unsigned short compare_count) :
dl_handle_(dl_handle),
flashtool_handle_(flashtool_handle),
compare_items_count_(compare_count),
load_items_count_(0),
target_items_count_(0),
is_nand_layout_matched_(false),
is_load_layout_map_ready_(false),
is_target_layout_map_ready_(false)
{
    if(NULL != this->dl_handle_)
    {
        SetupLoadLayoutMap( this->dl_handle_);
        LOG("%s(): Dump load layout...", __FUNC__);
        DumpLayoutMap(load_layout_map_);
    }
    if ( NULL != this->flashtool_handle_) { 
        SetupTargetLayoutMap( this->flashtool_handle_);
        LOG("%s(): Dump target layout...", __FUNC__);
        DumpLayoutMap(target_layout_map_);
    } else {
	LOG("%s(): flashtool_handle_ is NULL!", __FUNC__);
    }
}

NandLayoutParameter::~NandLayoutParameter(void)
{
}

bool NandLayoutParameter::is_nand_layout_matched(void)
{
	return this->is_nand_layout_matched_ = CompareIsNandLayoutMatched();
}

inline void NandLayoutParameter::set_compare_items_count(unsigned short count) 
{
	this->compare_items_count_ = count;	
}

void NandLayoutParameter::DumpLayoutMap(const std::vector<RomInfoPair>& layout_map)
{
	if (layout_map.empty()) {
		LOG("%s(): The map is empty.", __FUNC__);
	} else {
		vector<RomInfoPair>::const_iterator it = layout_map.begin();
		for(; it != layout_map.end(); it++) {
			LOG("%s(): Key(%s), Value(0x%I64x).", __FUNC__, it->first.c_str(), it->second);
		}
	}
}

bool NandLayoutParameter::CompareVisibleLayoutMatched(void)
{
    bool is_match = false;

    compare_items_count_ = load_items_count_ <= target_items_count_?load_items_count_:target_items_count_;
    LOG("%s(): compare items count(%d).", __FUNC__, compare_items_count_);

	if ( !load_layout_map_.empty() && !target_layout_map_.empty() ) {
		vector<RomInfoPair>::const_iterator load_it = load_layout_map_.begin();
		vector<RomInfoPair>::const_iterator target_it = target_layout_map_.begin();
		for (int i = 0; i < compare_items_count_; i++, load_it++, target_it++) {
				if ( (load_it->first != target_it->first) ||
				     (load_it->second.start_addr != target_it->second.start_addr) ) {
					if(load_it->first.find(kVisibleMark) == std::string::npos)
					{
					       LOG("%s(): NOT MATCH: load item key(%s), value(0x%I64x), "
						       "target item key(%s), value(0x%I64x).",
						       __FUNC__, 
						       load_it->first.c_str(), load_it->second.start_addr,
						       target_it->first.c_str(), target_it->second.start_addr);
						   
					       return is_match;
					}
				}
		}
		
		is_match = true;
		LOG("%s(): Layout of load and target are matched.", __FUNC__);
	} else {
		LOG("ERROR: %s(): load layout or target layout is empty!", __FUNC__);
	}

	return is_match;
}
bool NandLayoutParameter::CompareIsNandLayoutMatched(void)
{
	bool is_match = false;

      //remove rom count comparsion for "_RSV_" partitions
	#if 0
	if( load_items_count_ != target_items_count_)
	{
	         LOG("%s(): NOT MATCH: load item count is not match: load count(%d), target count(%d).", __FUNC__,load_items_count_, target_items_count_);
                return is_match;
	}
	#endif

	compare_items_count_ = load_items_count_ <= target_items_count_?load_items_count_:target_items_count_;
	LOG("%s(): compare items count(%d).", __FUNC__, compare_items_count_);

	if ( !load_layout_map_.empty() && !target_layout_map_.empty() ) {
		vector<RomInfoPair>::const_iterator load_it = load_layout_map_.begin();
		vector<RomInfoPair>::const_iterator target_it = target_layout_map_.begin();
		for (int i = 0; i < compare_items_count_; i++, load_it++, target_it++) {
				if ( (load_it->first != target_it->first) ||
						(load_it->second.start_addr != target_it->second.start_addr) ) {
					if(load_it->first.find(kRsvMark) == std::string::npos &&load_it->first.find(kBMTMark) == std::string::npos)
					{
					      LOG("%s(): NOT MATCH: load item key(%s), value(0x%I64x), "
						"target item key(%s), value(0x%I64x).",
						__FUNC__, 
						load_it->first.c_str(), load_it->second.start_addr,
						target_it->first.c_str(), target_it->second.start_addr);
					      return is_match;
					}
				}
		}
		is_match = true;
		LOG("%s(): Layout of load and target are matched.", __FUNC__);
	} else {
		LOG("ERROR: %s(): load layout or target layout is empty!", __FUNC__);
	}

	return is_match;
}

void NandLayoutParameter::SetupLoadLayoutMap(const DL_HANDLE_T dl_handle)
{
    assert( NULL != dl_handle );

	unsigned short rom_count = 0;
	ROM_INFO rom_infos[MAX_LOAD_SECTIONS]; 
	memset(&rom_infos, 0, sizeof(ROM_INFO)*MAX_LOAD_SECTIONS);
	PartitionInfo part_info;
	memset(&part_info, 0, sizeof(PartitionInfo));

	if ( !DL_GetCount(dl_handle, &rom_count) ) {

             load_items_count_ = rom_count;
		
		if( !DL_Rom_GetInfoAll(dl_handle, rom_infos, MAX_LOAD_SECTIONS) ) {
			for (unsigned short i = 0;/* i < rom_count-1*/i<rom_count; i++) {
				string rom_name(rom_infos[i].name);
				string non_dl_flag("__NODL_");
				part_info.start_addr = rom_infos[i].begin_addr;
				if (rom_infos[i].item_is_visable ==0 ||
                              rom_name.find("NVRAM") != string::npos ||
                              rom_name.find("PRO_INFO") != string::npos ||
                              rom_name.find("PROTECT_F") != string::npos ||
                              rom_name.find("PROTECT_S") != string::npos) {
				    //__NODL_ partition in brom.dll for instance, __NODL_NVRAM, 0x00100000 = (0x00100000->0x00000000) 
				    part_info.length = rom_infos[i+1].begin_addr - rom_infos[i].begin_addr;
				} else {
				    part_info.length = rom_infos[i].end_addr - rom_infos[i].begin_addr;
				}
				load_layout_map_.push_back(std::make_pair(rom_name, part_info));
			}
			is_load_layout_map_ready_ = true;
			LOG("%s(): load layout map is ready.", __FUNC__);
		} else {
			is_load_layout_map_ready_ = false;
			LOG("ERROR: %s(): Obtain rom infos by DL_Rom_GetInfoAll() failed!", __FUNC__);
		}
	} else {
		is_load_layout_map_ready_ = false;
		LOG("ERROR: %s(): Obtain rom count by DL_GetCount() failed!", __FUNC__);
	}

}

void NandLayoutParameter::SetupTargetLayoutMap(const FLASHTOOL_API_HANDLE_T flashtool_handle)
{
    assert( NULL != flashtool_handle );
    int ret = 0;
    unsigned int rom_count = 0;
    PART_INFO* p_part_info = NULL;
	PartitionInfo part_info;
	memset(&part_info, 0, sizeof(PartitionInfo));

    do {
        ret = FlashTool_ReadPartitionCount(flashtool_handle, &rom_count);
        if( S_DONE != ret ) {
			LOG("ERROR: %s():  FlashTool_ReadPartitionCount() failed, error code is(%d).", __FUNC__, ret);
			is_target_layout_map_ready_ = false;
            break;
        }

        target_items_count_ = rom_count;
		
        p_part_info = new PART_INFO[rom_count];
        ret = FlashTool_ReadPartitionInfo(flashtool_handle, p_part_info, rom_count);
     	if( S_DONE != ret ) {
            LOG("ERROR: %s(): FlashTool_ReadPartitionInfo() failed!, error code(%d).", __FUNC__, ret);
            is_target_layout_map_ready_ = false;
    		break;
    	}

        for(unsigned int i = 0; i < rom_count; i++){
			part_info.start_addr = p_part_info[i].begin_addr;
			part_info.length = p_part_info[i].image_length;
			target_layout_map_.push_back(std::make_pair(p_part_info[i].name, part_info));
        }
        is_target_layout_map_ready_ = true;
        LOG("%s(): target layout map is ready.", __FUNC__);
    }while(0);

    if( NULL != p_part_info ){
        delete[] p_part_info;
        p_part_info = NULL;
    }

}

bool NandLayoutParameter::SearchPartitionInfoInMap(
		const std::vector<RomInfoPair>& layout_table,
		const std::string& name,
		PartitionInfo* p_part_info/*out*/)
{
	assert(p_part_info != NULL);
	vector<RomInfoPair>::const_iterator it = layout_table.begin();

	while(it != layout_table.end()) {
		
		if(it->first.find(name) != std::string::npos) {
			p_part_info->start_addr = it->second.start_addr;
			p_part_info->length = it->second.length;
			LOG("%s(): Obtain %s partition info: start_addr(0x%I64x), length(0x%I64x).",
					__FUNC__, name.c_str(), p_part_info->start_addr, p_part_info->length);
			break;
		}
		it++;
	}
	if (it == layout_table.end()) {
		LOG("ERROR: %s(): Could not find %s in the layout table.", __FUNC__, name.c_str());
		return false;
	}

	return true;
}

bool NandLayoutParameter::QueryPartitionInfobyName(const std::string& name, PartitionInfo* p_part_info)
{
	assert(p_part_info != NULL);
	if (is_target_layout_map_ready_){
		LOG("%s(): Begin to search target PMT.", __FUNC__);
		return SearchPartitionInfoInMap(target_layout_map_, name, p_part_info);
	} else if(is_load_layout_map_ready_){
		LOG("WARNING: %s(): Begin to search load scatter file instead of PMT.", __FUNC__);
		return SearchPartitionInfoInMap(load_layout_map_, name, p_part_info);
	} else {
		LOG("ERROR: %s(): None layout table is ready!", __FUNC__);
		return false;
	}
}

unsigned int NandLayoutParameter::QueryRSVNumberByName(void)
{
     vector<RomInfoPair>::const_iterator it = target_layout_map_.begin();
     for(; it!= target_layout_map_.end(); ++it)
     {
            LOGD("Check region(%s)", it->first.c_str());
	 
            if(it->first.find(kRsvMark) != std::string::npos || (CheckIfRSVByAddr(it->second.start_addr)))
            {
                   LOGD("Regin Name(%s),Rsv Block Number(%I64x)", it->first.c_str(), it->second.start_addr);
                   return it->second.start_addr & 0x0000FFFF;
	     } 
	     else if(it->first.find(kBMTMark) != std::string::npos || (CheckIfRSVByAddr(it->second.start_addr)))
	     {
                   LOGD("Regin Name(%s),Rsv Block Number(%I64x)", it->first.c_str(), it->second.start_addr) ;
                   return it->second.start_addr & 0x0000FFFF;
	     }
     }

     //if no rsv partition, return 0
     LOGD("No RSV region!");
     return 0; 
}

bool NandLayoutParameter::SearchPartitionByName(const std::string& name)
{
	vector<RomInfoPair>::const_iterator it = target_layout_map_.begin();
	while(it != target_layout_map_.end()) {
		
		if(it->first.find(name) != std::string::npos) {
			LOG("%s(): Obtain %s partition info", __FUNC__, name.c_str());
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

int NandLayoutParameter::isSizeChanged(const  std::string & partition)
{
      PartitionInfo part_info_old;
      PartitionInfo part_info_new;

      bool ret = true;

      //get partition info in PMT
      ret = SearchPartitionInfoInMap(target_layout_map_, partition, &part_info_old);
      if(!ret && partition.find("NVRAM"))
      {
             LOGE("NARAM is not found in PMT, no calibration data.");
             return FT_UPGRADE_BACKUP_ROM_NOT_EXSIT;
      }
      
      //get partition info in new load 
      ret = SearchPartitionInfoInMap(load_layout_map_, partition, &part_info_new);
      if(!ret && partition.find("NVRAM"))
      {
             LOGE("NARAM is not found in new scatter, no place can restore it.");
             return FT_UPGRADE_BACKUP_ROM_NOT_EXSIT;
      }

      //change, true; not change, false
      ret = (part_info_old.length != part_info_new.length);
      LOGD("old length(%I64X), new length(%I64X)", part_info_old.length, part_info_new.length);

      return (ret == true)?FT_UPGRADE_BACKUP_SIZE_CHANGE:FT_SUCCESS;
      
}



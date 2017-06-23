/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/
#ifndef NAND_MANAGER_H
#define NAND_MANAGER_H

#include <string>
#include <vector>
//#include <map>
#include "flashtool.h"
#include "NonCopyable.h"

typedef struct {
	unsigned long long start_addr;
	unsigned long long length;
}PartitionInfo;

typedef enum
{
      PARTITION_EXIST = 0,
      PARTITION_INVISIBLE,
      PARTITION_NOT_EXIST,
      PARTITION_ENABLE,
      PARTITION_DISABLE,
      LAYOUT_NOT_EXIST
}PartitionExistStatus;

class NandLayoutParameter : private NonCopyable
{	
public:
	//PRELOADER+DSP_BL+__NODL_NVRAM
	static const unsigned short kVitaltemsCount;
	static const std::string kVisibleMark;
	static const std::string kRsvMark;
	static const std::string kBMTMark;

private:
	//Disable map auto sort by pair & vector
	typedef std::pair<std::string, PartitionInfo> RomInfoPair;

public:
	explicit NandLayoutParameter(const DL_HANDLE_T dl_handle, 
		const FLASHTOOL_API_HANDLE_T flashtool_handle,
		const unsigned short compare_count = kVitaltemsCount);

	~NandLayoutParameter(void);

	bool CompareIsNandLayoutMatched(void);
	bool CompareVisibleLayoutMatched(void);
	//setters & getters
	void set_compare_items_count(unsigned short count);
	bool is_nand_layout_matched(void);
        int isSizeChanged(const  std::string & partition); 
	bool is_load_layout_map_ready(void) const {
		return is_load_layout_map_ready_;
	}
	bool is_target_layout_map_ready(void) const {
		return is_target_layout_map_ready_;
	}

	bool isSizeChanged(const std::string &partition) const;

	bool QueryPartitionInfobyName(const std::string& name, PartitionInfo* p_part_info/*out*/);
	unsigned int QueryRSVNumberByName(void);
	bool SearchPartitionByName(const std::string& name);
private:
	void SetupLoadLayoutMap(const DL_HANDLE_T dl_handle);
	void SetupTargetLayoutMap(const FLASHTOOL_API_HANDLE_T flashtool_handle);
	void DumpLayoutMap(const std::vector<RomInfoPair>& layout_map);
	bool SearchPartitionInfoInMap(
			const std::vector<RomInfoPair>& layout_table,
			const std::string& name,
			PartitionInfo* p_part_info/*out*/);

private:
	DL_HANDLE_T dl_handle_;
	FLASHTOOL_API_HANDLE_T flashtool_handle_;
	unsigned short compare_items_count_;
	unsigned short load_items_count_;
	unsigned short target_items_count_;
	bool is_nand_layout_matched_;
	bool is_load_layout_map_ready_;
	bool is_target_layout_map_ready_;

	std::vector<RomInfoPair> load_layout_map_;
	std::vector<RomInfoPair> target_layout_map_;
//	std::map<std::string, PartitionInfo> load_layout_map_;
//	std::map<std::string, PartitionInfo> target_layout_map_;
		
};

#endif //NAND_MANAGER_H

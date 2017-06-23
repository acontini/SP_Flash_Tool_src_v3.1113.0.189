/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/
#ifndef OPERATION_INDICATOR_H
#define OPERATION_INDICATOR_H

#include <string>
#include <map>

typedef enum {
	NVRAM_NO_ACTION = 0,
	NVRAM_FOUR_IN_ONE = 1,
	NVRAM_FOUR_IN_ONE_WITH_FORMAT = 2,
	NVRAM_FIRMWARE_UPGRADE = 3,
}NvramOperation;

class OperationIndicator
{
public:
	enum DADLType {
		//Units: Full/High(0/1), Tens: WithBat/WithoutBat(0/1), Hundreds: AutoDetBat/Not_AutoDetBat(1/0)
		DA_DL_ALL_FULL_SPEED_WITH_BAT = 0,
		DA_DL_ALL_HIGH_SPEED_WITH_BAT = 1,
		DA_DL_ALL_FULL_SPEED_WITHOUT_BAT = 2,
		DA_DL_ALL_HIGH_SPEED_WITHOUT_BAT = 3,
		DA_DL_ALL_FULL_SPEED_AUTO_DETECT_BAT = 4,
		DA_DL_ALL_HIGH_SPEED_AUTO_DETECT_BAT =5
	};

public:
	OperationIndicator(void);
	OperationIndicator(const bool is_da_dl_all,
		const bool is_da_high_speed,
		const bool is_da_dl_without_bat,
		const bool is_da_dl_auto_detect_bat,
		const NvramOperation nvram_op);

	~OperationIndicator(void);

	void SetDADLAttr(const bool is_da_high_speed, const bool is_da_dl_without_bat, const bool is_da_dl_auto_detect_bat);
	void SetNvramOp(const NvramOperation nvram_op) {
		nvram_op_ = nvram_op;
	}
	void SetDADLALL(const bool is_da_dl_all) {
		is_da_dl_all_ = is_da_dl_all;
	}
	
	std::string GetDADLHint();
	std::string QueryNvramOperationHint(const NvramOperation nvram_op); 

	std::string NvramOperationToString(const NvramOperation nvram_op);
	std::string DADLTypeToString(const DADLType da_dl_type);

private:
	void InitDADLHintMap();
	void InitNvramOperationHintMap();
	std::string QueryDADLHint(const DADLType da_dl_type);

private:
	bool is_da_dl_all_;
	bool is_da_high_speed_;
	bool is_da_dl_without_bat_;
	bool is_da_dl_auto_detect_bat_;
	NvramOperation nvram_op_;
	DADLType da_dl_type_;
    
	std::map<DADLType, std::string> da_dl_hint_;
	std::map<NvramOperation, std::string> nvram_op_hint_;

};

#endif //OPERATION_INDICATOR_H
#include <assert.h>
#include "RegionFormatSetting.h"
#include "PlatformInfo.h"
#include "GlobalData.h"
#include "AutoFormatArgFactory.h"
#include "Utility.h"
#include "Logger.h"
#include "main.h"


const std::string RegionFormatSetting::BMT_KEY("BMTPOOL");
const unsigned int RegionFormatSetting::MTK_DEBUG_SIZE_FLAG(512);
const unsigned int RegionFormatSetting::BLOCK_SIZE(131072);

RegionFormatSetting::RegionFormatSetting():
is_do_partitial_format(false)
{}

RegionFormatSetting:: RegionFormatSetting(const std::string &image_name):
is_do_partitial_format(false),
image_name_(image_name)
{

}

RegionFormatSetting::~RegionFormatSetting()
{}

SharedPtr<Command> RegionFormatSetting::CreateCommand(NandLayoutParameter &para) const
{
     SharedPtr<RegionFormatCommand> cmd(new RegionFormatCommand(ft_handle));
     LOG("%s(): Create region format command...", __FUNC__);
     HW_StorageType_E hw_storage_type = g_platform_info.getFlashToolStorageConfig().GetStorageType();

     cmd->region_format_arg_.set_format_addr_type(NUTL_ADDR_LOGICAL);
     cmd->region_format_arg_.set_storage_type(hw_storage_type);
     cmd->region_format_arg_.set_validation((_BOOL)is_validation);
     cmd->region_format_arg_.set_erase_flag(erase_flag);
     cmd->region_format_arg_.set_format_statistics_cb(NULL);
     cmd->region_format_arg_.set_cb_format_statistics_arg(cb_format_statistics_arg);
     cmd->region_format_arg_.set_format_report_cb(cb_format_report);
     cmd->region_format_arg_.set_cb_format_report_arg(cb_format_report_arg);
     cmd->region_format_arg_.set_format_report_init_cb(cb_format_report_init);
     cmd->region_format_arg_.set_cb_format_report_init_arg(cb_format_report_init_arg);
     cmd->region_format_arg_.set_auto_format_fat(_FALSE);

	 
     //Erase regions according to PMT
	
    // NandLayoutParameter layout_info(g_pCurNode->m_dl_handle, g_ft_handle);
     PartitionInfo part_info;
	memset(&part_info, 0, sizeof(PartitionInfo));
	para.QueryPartitionInfobyName(image_name_, &part_info);

	U64 start_addr = part_info.start_addr;
	U64 len = part_info.length;
        if (image_name_.find(BMT_KEY) == std::string::npos 
			&& len < MTK_DEBUG_SIZE_FLAG) {
				//Adjust last partition length
				len = this->CalcWholeStorageSize(&(conn_result->m_da_report)) - start_addr;
		}
		cmd->region_format_arg_.set_format_start_address(start_addr);
		cmd->region_format_arg_.set_format_length(len);
		LOGD("Region name(%s), start addr(0x%I64x), length(0x%I64x).", 
			 image_name_.c_str(), start_addr, len);
    

    return cmd;
        
}

RegionFormatSetting* RegionFormatSetting::Clone() const
{
    return new RegionFormatSetting(*this);
}

unsigned long long RegionFormatSetting::CalcWholeStorageSize(DA_REPORT_T *da_report) const {
	assert(NULL != da_report);

      NandLayoutParameter layout_info(g_pCurNode->m_dl_handle, g_ft_handle);
	unsigned int rsv_number = 0;
	
      rsv_number = layout_info.QueryRSVNumberByName();
	LOGD("rsv_number(%d)", rsv_number);
	
	if (S_DONE == da_report->m_nand_ret) {
		//NAND remove BMT region
		return da_report->m_nand_flash_size - 
		          (g_platform_info.getNandReservedBlocks() *
    			    da_report->m_nand_pagesize *
    			    da_report->m_nand_pages_per_block);
		
	} else if(S_DONE == da_report->m_emmc_ret) {
		//EMMC
		return da_report->m_emmc_boot1_size
			+ da_report->m_emmc_boot2_size
			+ da_report->m_emmc_rpmb_size
			+ da_report->m_emmc_gp1_size
			+ da_report->m_emmc_gp2_size
			+ da_report->m_emmc_gp3_size
			+ da_report->m_emmc_gp4_size 
			+ da_report->m_emmc_ua_size
			- rsv_number * BLOCK_SIZE;
	} else if (S_DONE == da_report->m_sdmmc_ret) {
		//SDMMC
		return da_report->m_sdmmc_ua_size - rsv_number * BLOCK_SIZE;
	} else {
		assert( 0 && "Not supported storage");
		return 0;
	}
}





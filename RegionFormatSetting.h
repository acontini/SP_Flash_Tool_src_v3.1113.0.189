#ifndef REGION_FORMAT_SETTING_H_
#define REGION_FORMAT_SETTING_H_

#include "RegionFormatCommand.h"
#include "NandLayoutParameter.h"
#include "Flashtool_api.h"

class RegionFormatSetting
{
public:
     	static const std::string BMT_KEY;
	static const unsigned int MTK_DEBUG_SIZE_FLAG;
	static const unsigned int BLOCK_SIZE;
	
public:
	RegionFormatSetting();
	explicit RegionFormatSetting(const std::string &image_name);
	~RegionFormatSetting();

      SharedPtr<Command> CreateCommand(NandLayoutParameter &para) const;

      void set_format_report_cb(const CALLBACK_FORMAT_PROGRESS &cb)
      	{
              this->cb_format_report = cb;
	}

	void set_format_report_init_cb(const CALLBACK_FORMAT_PROGRESS_INIT &cb)
	{
              this->cb_format_report_init = cb;
	}

       void set_format_statistics_cb(const CALLBACK_FORMAT_STATISTICS &cb)
       {
              this->cb_format_statistics = cb;
	}
	
	void set_cb_format_report_init_arg(void* host_pointer) 
       {
              this->cb_format_report_init_arg = host_pointer;
       }

       void set_cb_format_report_arg(void* host_pointer) 
       {
              this-> cb_format_report_arg = host_pointer;
       }

       void set_cb_format_statistics_arg(void* host_pointer)
       {
              this->cb_format_statistics_arg= host_pointer;
       }

	void set_if_do_partitial_format(bool isParti)
		{
              this->is_do_partitial_format = isParti;
	}

	void set_erase_flag(const NUTL_EraseFlag_E erase_flag)
	{
             this->erase_flag= erase_flag;
	}
	void set_is_validation(const bool isValidation)
	{
              this->is_validation = isValidation;
	}
	void set_dl_handle(const DL_HANDLE_T &dl_handle)
	{
              this->dl_handle= dl_handle;
	}
	void set_ft_handle(const FLASHTOOL_API_HANDLE_T ft_handle)
	{
              this->ft_handle= ft_handle;
	}
	void set_conn_result(FlashTool_Connect_Result *cn_result)
	{
             this->conn_result = cn_result;
	}
       RegionFormatSetting* Clone() const;

private:
	unsigned long long CalcWholeStorageSize(DA_REPORT_T *da_report) const ;

private:
	CALLBACK_FORMAT_STATISTICS cb_format_statistics;
       void *cb_format_statistics_arg;
	CALLBACK_FORMAT_PROGRESS cb_format_report;
	void *cb_format_report_arg;
	CALLBACK_FORMAT_PROGRESS_INIT cb_format_report_init;	
	void *cb_format_report_init_arg;
	bool is_do_partitial_format;
	NUTL_EraseFlag_E erase_flag;
	bool is_validation;
	FlashTool_Connect_Result *conn_result;
       FLASHTOOL_API_HANDLE_T  ft_handle;
	DL_HANDLE_T dl_handle;
	std::string image_name_;
};

#endif


#ifndef sregion_format_arg_H_
#define sregion_format_arg_H_

#include <list>
#include <map>
#include <string>
#include "Flashtool_api.h"

typedef struct
{
  std::string img_name;
  FlashTool_Format_Arg format_arg;
}S_RegionFormatArg;

class RegionFormatArg
{
public:
	RegionFormatArg();
	~RegionFormatArg();

       S_RegionFormatArg getRegionArg(void) const {return this->sregion_format_arg_;}
	

	void set_format_report_cb(const CALLBACK_FORMAT_PROGRESS &cb)
      	{
              this->sregion_format_arg_.format_arg.m_cb_format_report = cb;
	}

	void set_format_report_init_cb(const CALLBACK_FORMAT_PROGRESS_INIT &cb)
	{
              this->sregion_format_arg_.format_arg.m_cb_format_report_init = cb;
	}

       void set_format_statistics_cb(const CALLBACK_FORMAT_STATISTICS &cb)
       {
              this->sregion_format_arg_.format_arg.m_cb_format_statistics = cb;
	}

	void set_cb_format_report_init_arg(void* host_pointer) 
       {
              this->sregion_format_arg_.format_arg.m_cb_format_report_init_arg = host_pointer;
       }

       void set_cb_format_report_arg(void* host_pointer) 
       {
              this-> sregion_format_arg_.format_arg.m_cb_format_report_arg = host_pointer;
       }

       void set_cb_format_statistics_arg(void* host_pointer)
       {
              this-> sregion_format_arg_.format_arg.m_cb_format_statistics_arg = host_pointer;
       }

	void set_format_start_address(const U64 start_addr)
	{
              this-> sregion_format_arg_.format_arg.m_format_cfg.m_format_begin_addr = start_addr;
	}

	void set_format_length(const U64 length)
	{
              this-> sregion_format_arg_.format_arg.m_format_cfg.m_format_length= length;
	}

	 void set_format_addr_type(const NUTL_AddrTypeFlag_E &addrType)
       {
             this->sregion_format_arg_.format_arg.m_format_cfg.m_AddrType = addrType;
       }

	 void set_validation(const _BOOL validation) 
       {
              this->sregion_format_arg_.format_arg.m_format_cfg.m_validation = validation;
       }
        void set_storage_type(const HW_StorageType_E storage_type)
       {
              this->sregion_format_arg_.format_arg.m_storage_type = storage_type;
       }
        void set_erase_flag(const NUTL_EraseFlag_E erase_flag) 
       {
               this->sregion_format_arg_.format_arg.m_erase_flag = erase_flag;
       }

	 void set_auto_format_fat(_BOOL isAutoFmtFat) 
       {
               this->sregion_format_arg_.format_arg.m_format_cfg.m_auto_format_fat = isAutoFmtFat;
       }

	void set_image_name(const std::string &name)
	{
              this->sregion_format_arg_.img_name = name;
	}

       void Dump();
	
private:
	S_RegionFormatArg sregion_format_arg_;
};

#endif



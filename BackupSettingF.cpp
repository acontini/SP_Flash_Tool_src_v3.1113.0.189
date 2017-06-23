#include "BackupSettingF.h"

#include "FileUtils.h"
#include "GlobalData.h"
#include "FlashAllInOneAPIs.h"  
#include "FlashToolErrorCodeDef.h"
#include "Utility.h"

#define backupInfoCount (sizeof(backupInfoTable)/sizeof(S_Backup_Info))
S_Backup_Info backupInfoTable[] = 
{
   {"__NODL_NVRAM", "binRegion.img", "chksum_binRegion"},
   {"__NODL_PRO_INFO", "proInfo.img", "chksum_proInfo"}
};  

void BackupInfo::Dump()
{
     LOGD("partition_name(%s), file_path(%s), start_addr(0x%I64X), length(0x%X)",
                partition_name_.c_str(), file_path_.c_str(), start_addr_, length_);
}

std::list<BackupInfo> BackupSettingF::backup_table()
{
      	std::list<BackupInfo> backup_table_tmp;
	//Attention: allocate space for dest vector before std::copy
	backup_table_tmp.clear();

        for(std::list<BackupInfo>::iterator it = backup_table_.begin();
              it != backup_table_.end(); ++it)
        {       
	      backup_table_tmp.push_back(*it);
        }

	 for(std::list<BackupInfo>::iterator it = backup_table_tmp.begin();
              it != backup_table_tmp.end(); ++it)
        {       
	       LOGD("after pust:partition_name(%s), file_path(%s), start_addr(0x%I64X), length(0x%X)",
              it->partition_name().c_str(), it->file_path().c_str(),it->start_addr(), it->length());
        }


	return backup_table_tmp;     
}

int BackupSettingF::InitBackupTable()
{
    std::string file_path;
    std::string chksum_file_path;
    std::string parti_name;

    int ret = S_DONE;

    backup_table_.clear();

    PART_INFO part_info;

    for(int i=0; i<backupInfoCount; i++)
    {
            parti_name = backupInfoTable[i].parti_name;
	     file_path = backup_folder_ + "\\"+ backupInfoTable[i].file_name;
	     chksum_file_path = backup_folder_ + "\\" + backupInfoTable[i].chksum_name;

             LOGD("backupInfoCount(%d)", backupInfoCount);
	   
	   ret = GetPartitionInfo(g_ft_handle, backupInfoTable[i].parti_name, part_info);
	   if(ret != S_DONE)
	   {
               LOGD("Get Partition Info fail, ret(%d).", ret);
   
		  if(ToUppercaseString(backupInfoTable[i].parti_name).find("NVRAM") != std::string::npos)
               {
                      LOGE("Partition Name(%s).", backupInfoTable[i].parti_name);
			   break;
	        }
	        else
	        {
	               LOGD("Partition Name(%s).", backupInfoTable[i].parti_name);
			  ret = S_DONE;
                      continue;
		 }
	   }

           BackupInfo info(parti_name, file_path, chksum_file_path, part_info.begin_addr, part_info.image_length);
           backup_table_.push_back(info);

   }       
    return ret;
}







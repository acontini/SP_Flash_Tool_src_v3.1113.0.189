#ifndef BACKUP_CONFIG_H_
#define BACKUP_CONFIG_H_

#include <stdio.h>
#include <list>
#include <string>
#include <map>
#include "NandLayoutParameter.h"
#include "flashtool_handle.h"

using std::string;

class BackupItem{
public:
         BackupItem(){}
         explicit BackupItem(const std::string &partiName, const std::string &filePath, const std::string &chksumFile,
	                                 U64 startAddr, unsigned int len, ROM_TYPE &rom_type)
     : partition_name_(partiName),
       file_path_(filePath),
       chksum_file_(chksumFile),
       start_addr_(startAddr),
       length_(len),
       rom_type_(rom_type)
       {
            Dump();
	}

      ~BackupItem() {}
public:
	void set_partition_name(const std::string &partition_name)
	{
               partition_name_ = partition_name;
	}

	void set_file_path(const std::string &file_path)
	{
              file_path_ = file_path;
	}

	void set_chksum_file(const std::string &chksum_file)
	{
             chksum_file_ = chksum_file;
	}

	void set_start_addr(U64 start_addr)
	{
             start_addr_ = start_addr;
	}

	void set_length(unsigned int length)
	{
             length_ = length;
	}

       void set_rom_type(ROM_TYPE &rom_type)
       {
             rom_type_ = rom_type;
	}
	std::string partition_name() const
	{
		return partition_name_;
	}

	std::string file_path() const
	{
		return file_path_;
	}

	std::string chksum_file() const
	{
	     return chksum_file_;
	}

	U64 start_addr() const
	{
            return start_addr_;
	}

	unsigned int length() const
	{
            return length_;
	}

     	ROM_TYPE rom_type() const
      {
            return rom_type_;
	}      
	void Dump();
	
private:
	std::string partition_name_;
	std::string file_path_;
	std::string chksum_file_;
	U64 start_addr_;
	unsigned int length_;	
	ROM_TYPE rom_type_;
};

class BackupConfig{

public:
        BackupConfig(const std::string &backupFolder);
        ~BackupConfig();

	std::list<ROM_INFO> backup_roms();

      bool QueryBackupItemByPartitionName(std::string partition_name, BackupItem *backup_item);

      int InitBackupInfoTable();

      int SetupBackupItems();

private:
	int SetupTargetLayoutMap();
	bool SearchPartitionInfoInMap(const std::string& name, PART_INFO *p_part_info);

private:
	std::map<std::string, BackupItem> backup_map_;
	std::string backup_folder_;
	bool is_target_layout_map_ready_;
	std::map<std::string, PART_INFO> target_layout_map_;
	std::list<ROM_INFO> backup_roms_;
};
#endif


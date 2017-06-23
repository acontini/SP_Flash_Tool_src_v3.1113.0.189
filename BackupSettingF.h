#ifndef BACKUP_SETTING_F_H_
#define BACKUP_SETTING_F_H_

#include <string>
#include <list>
#include "flashtool_api.h"
#include "main.h"

typedef struct{
    char parti_name[32];
    char file_name[32];
    char chksum_name[32];
}S_Backup_Info;

class BackupInfo{
public:
         BackupInfo(){}
         explicit BackupInfo(const std::string &partiName, const std::string &filePath, const std::string &chksumFile,
	                                 U64 startAddr, unsigned int len)
     : partition_name_(partiName),
       file_path_(filePath),
       chksum_file_(chksumFile),
       start_addr_(startAddr),
       length_(len)
       {
            Dump();
	}

      ~BackupInfo() {}
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

	std::string partition_name() const
	{
             LOGD("partition_name(%s)", partition_name_);
		return partition_name_;
	}

	std::string file_path() const
	{
             LOGD("file_path(%s)", file_path_);
		return file_path_;
	}

	std::string chksum_file() const
	{
            LOGD("chksum_file(%s)", chksum_file_);
	     return chksum_file_;
	}

	U64 start_addr() const
	{
	     LOGD("start_addr(%I64x)", start_addr_);
            return start_addr_;
	}

	unsigned int length() const
	{
	     LOGD("length(%x)", length_);
            return length_;
	}
	void Dump();
	
private:
	std::string partition_name_;
	std::string file_path_;
	std::string chksum_file_;
	U64 start_addr_;
	unsigned int length_;	
};

class BackupSettingF{
public:
	BackupSettingF(const std::string &backupFolder)
        :backup_folder_(backupFolder){
               
	}

	~BackupSettingF() {}
public:
      int InitBackupTable();
	std::list<BackupInfo> backup_table(void);
	
private:
	std::list <BackupInfo> backup_table_;
	std::string backup_folder_;	 
};
#endif



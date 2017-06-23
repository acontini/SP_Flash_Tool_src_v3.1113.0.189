#ifndef CLONEINFO_HANDLE_H_
#define CLONEINFO_HANDLE_H_

#include "XMLSerializable.h"
#include "NandLayoutParameter.h"

#include <string>
#include <map>
#include <set>
#include "Logger.h"

class NandLayoutParameter;
class CloneInfoItem:public XML::Serializable
{
public:
     CloneInfoItem(void);
     ~CloneInfoItem(void);

    std::string partition_name (void) const
    {
           return this->partition_name_;
    }

    std::string image_path(void) const
    {
           return this->image_path_;
    }

    unsigned char chksum_value(void) const
    {
           return this->chksum_value_;
    }

    unsigned long long start_addr(void) const
    {
           return this->partition_info_.start_addr;
    }

    unsigned long long partition_len(void) const
    {
           return this->partition_info_.length;
    }

    void set_partition_name(const std::string &partition_name)
    {
          this->partition_name_  = partition_name;
    }

    void set_image_path(const std::string &image_path)
    {
         LOGD("image_path(%s)", image_path.c_str());
         this->image_path_ = image_path;
    }

    void set_chksum_value(unsigned char chksum_value)
    {
         this->chksum_value_ = chksum_value;
    }

    void set_start_addr(unsigned long long start_addr)
    {
         this->partition_info_.start_addr = start_addr;
    }

    void set_partition_len(unsigned long long len)
    {
         this->partition_info_.length = len;
    }

    virtual void LoadXML(const XML::Node &node);
    virtual void SaveXML(XML::Node &node) const;
	
private:
     std::string partition_name_;
     std::string image_path_;
     unsigned char chksum_value_;
     PartitionInfo partition_info_;

     friend class CloneInfoHandle;
	
};

class CloneInfoHandle
{
public:
	CloneInfoHandle();
	explicit CloneInfoHandle(const std::string &filename);
	~CloneInfoHandle(void);

	virtual void LoadFile(const std::wstring &filename);
	virtual void SaveFile(const std::string &filename) const;

	void AddCloneInfoItem(const CloneInfoItem &cloneinfo);
	void RemoveCloneInfoItem(CloneInfoItem &cloneinfo);

	void UpdateCloneInfoTable(CloneInfoItem &cloneinfo);
	bool QueryCloneInfoByPartitionName(const std::string &partition_name, CloneInfoItem *p_clone_info);	

	unsigned int GetCloneInfoCount (void) const
	{
              return CloneInfo_table.size();
	}

	std::set<std::string> partition_name_set(void) ;

private:
	std::map<std::string, CloneInfoItem> CloneInfo_table;
	std::set<std::string> PartitionName_set;
};

CloneInfoHandle& GetCloneInfoHandle(std::string filename);

#endif



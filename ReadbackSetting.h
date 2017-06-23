#ifndef SCI_READBACK_SETTING_H_
#define  SCI_READBACK_SETTING_H_

#include "SharedPtr.h"
#include "Command.h"
#include "flashtool_api.h"
#include "MacroSetting.h"

#include <vector>

class ReadbackItem
{
public:
    ReadbackItem(unsigned int index, bool enable,
                  unsigned long long addr, unsigned int len,
                 const std::string &path,
                 NUTL_ReadFlag_E read_flag = NUTL_READ_PAGE_SPARE,
                 NUTL_AddrTypeFlag_E addr_flag = NUTL_ADDR_LOGICAL)
        :index_(index), enable_(enable),
          addr_(addr), len_(len), path_(path),
          read_flag_(read_flag), addr_flag_(addr_flag)
    {}	

    unsigned int index() const { return index_; }
    bool enable() const { return enable_; }

    unsigned long long addr() const { return addr_; }
    unsigned int len() const { return len_; }
    std::string path() const { return path_; }

    NUTL_ReadFlag_E read_flag() const { return read_flag_; }
    NUTL_AddrTypeFlag_E addr_flag() const { return addr_flag_; }

private:
    unsigned int index_;
    bool enable_;
    unsigned int addr_;
    unsigned int len_;
    std::string path_;

    NUTL_ReadFlag_E read_flag_;
    NUTL_AddrTypeFlag_E addr_flag_;
	
};

class SCIReadbackSetting:public MacroSetting
{
public:
	SCIReadbackSetting();
	~SCIReadbackSetting();

	virtual SharedPtr<Command> CreateCommand(FLASHTOOL_API_HANDLE_T ft_handle) const;

	virtual SCIReadbackSetting* Clone(void) const;
	virtual void Dump(void) const;


	int InitialRBHandle(const ReadbackItem &rb_item);

       std::vector<ReadbackItem> GetReadbackList(void) const { return this->rb_item_list;}
	
	//setters
	void set_file_path(const std::string &filepath)
	{
              this->file_path_ = filepath;
	}

	void set_start_addr(unsigned long long startAddr)
	{
             this->start_addr_ = startAddr;
	}

	void set_length(unsigned int len)
	{
             this->length_ = len;
	}

	void set_cb_readback_init(CALLBACK_READBACK_PROGRESS_INIT cb)
      {
             cb_readback_init_ = cb;
      }

	void set_cb_readback_init_arg(void *usr_arg)
	{
            cb_readback_init_arg_ = usr_arg;
	}

	void set_cb_readback_progress_arg(void *usr_arg)
	{
            cb_readback_arg_ = usr_arg;
	}
	
       void set_cb_readback_progress(CALLBACK_READBACK_PROGRESS cb)
      {
             cb_readback_progress_ = cb;
      }

      void set_storage_type(HW_StorageType_E type)
      {
              storage_type_ = type;
      }

      void set_readback_handle(RB_HANDLE_T &rb_handle)
     {
             readback_handle_ = rb_handle;
     }

private:
	std::string file_path_;
	unsigned long long start_addr_;
	unsigned int length_;

	HW_StorageType_E storage_type_;

       CALLBACK_READBACK_PROGRESS_INIT cb_readback_init_;
       CALLBACK_READBACK_PROGRESS cb_readback_progress_;

	 void *cb_readback_init_arg_;
	 void *cb_readback_arg_;

	std::vector<ReadbackItem> rb_item_list;
	RB_HANDLE_T readback_handle_;
       
};

#endif


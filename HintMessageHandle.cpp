
#include "HintMessageHandle.h"
#include <string>
#include "Logger.h"

using std::string;
using std::map;

#define HintMessageInfoCount (sizeof(HintMessageInfoTable)/sizeof(HintMessageInfo))

HintMessageInfo HintMessageInfoTable[] =
{   /*item name,                            hint message,                 offset_x, offset_y, ifShowHint*/
	{"PRELOADER", "PRELOADER is unchecked, which may result in boot failure.", 160, 34, 1},
	{"DSP_BL", "DSP_BL is unchecked, which may result in boot failure.", 160, 54, 1},
	{"UBOOT", "", 0, 0, 0},
	{"BOOTIMG", "", 0, 0, 0},
	{"RECOVERY", "", 0, 0, 0},
	{"SEC_RO", "", 0, 0, 0},
	{"LOGO", "", 0, 0, 0},
	{"ANDROID", "", 0, 0, 0},
	{"USRDATA", "", 0, 0, 0}
};

HintMessageHandle::HintMessageHandle():
    offset_x_(0), offset_y_(0), is_show_hint_(false)
{
	this->InitHintInfoTable();
}

void HintMessageHandle::InitHintInfoTable()
{
	for(int i = 0; i < HintMessageInfoCount; i++) {
		hint_map_[HintMessageInfoTable[i].item_name] = HintMessageInfoTable[i];
	}
}

bool HintMessageHandle::QueryHintInfo(const std::string& image_name)
{
	bool is_found = false;
	std::map<std::string, HintMessageInfo>::iterator it =  hint_map_.find(image_name);
	if (it != hint_map_.end()) {
		is_found = true;
		hint_message_ = it->second.hint_message;
		offset_x_ = it->second.offset_x;
		offset_y_ = it->second.offset_y;
		is_show_hint_ = (1 == it->second.ifShowHint) ? true : false;
	}
	return is_found;
}

void HintMessageHandle::Dump(void)
{
	LOGD("hint_message_(%s).", this->hint_message_.c_str());
	LOGD("offset_x_(%d), offset_y_(%d), is_show_hint_(%d).",
			this->offset_x_, this->offset_y_, this->is_show_hint_);
}



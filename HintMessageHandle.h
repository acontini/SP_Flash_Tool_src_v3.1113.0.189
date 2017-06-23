#ifndef _HINTMESSAGEHANDLE_H_
#define _HINTMESSAGEHANDLE_H_

#define MAX_ITEM_NUMBER 9

#include <string>
#include <map>

typedef struct
{
	char item_name[10];
	char hint_message[256];	
	int offset_x;
	int offset_y;
	bool ifShowHint; /*if true, show hint; if false, don't show hint*/
	
} HintMessageInfo;

class HintMessageHandle
{
public:
	HintMessageHandle();
        ~HintMessageHandle() {}

    std::string hint_message(void) {
    	return this->hint_message_;
    }
    int offset_x(void) const {
    	return this->offset_x_;
    }
    int offset_y(void) const {
    	return this->offset_y_;
    }
    bool is_show_hint(void) const {
    	return this->is_show_hint_;
    }

    bool QueryHintInfo(const std::string& image_name);

    void Dump(void);

private:
    void InitHintInfoTable(void);

private:
	std::map<std::string, HintMessageInfo> hint_map_;
	std::string hint_message_;
	int offset_x_;
	int offset_y_;
	bool is_show_hint_;
};
#endif


#ifndef __IMAGE_MAP_RULE_H
#define __IMAGE_MAP_RULE_H

#include <string>
#include <list>
#include <map>
#include <set>
#include <algorithm>

#include "XMLSerializable.h"

using std::list;
using std::map;
using std::string;
using std::pair;
using std::wstring;

typedef int ImageType; 
typedef int ImageFormat;

extern const ImageType UNKNOWN_TYPE;
extern const ImageFormat UNKNOWN_BROM_FMT;
extern const ImageFormat UNKNOWN_FMT;

class ImageItem : public XML::Serializable
{
public:
    ImageItem() : 
	    type_name_("??"),
	    image_type_(UNKNOWN_TYPE), 
		brom_format_(UNKNOWN_BROM_FMT),
        eboot_format_(UNKNOWN_FMT),
		is_bootloader_(false),
        is_format_effective_(false),
        is_uncheckable_(false)
		{}

    virtual void LoadXML(const XML::Node &node);
    virtual void SaveXML(XML::Node &node) const;

    bool isPrefixMatch(const string &name);
    bool isSuffixMatch(const string &name);

    //Getters
	std::string type_name(void) const {
		return type_name_;
	}
	int image_type(void) const {
		return image_type_;
	}
	int brom_format(void) const {
		return brom_format_;
	}
	int eboot_format(void) const {
		return eboot_format_;
	}
	bool is_bootloader(void) const {
		return is_bootloader_;
	}
	bool is_format_effective(void) const {
		return is_format_effective_;
	}
	bool is_uncheckable(void) const{
             return is_uncheckable_;
	}
	/**
	Attention: Obtain list data from function statck.
	The list data should be copy to local function statck before using!
	**/
	std::list<std::string> scatters(void) ;
	std::list<std::string> prefixes(void) ;
	std::list<std::string> suffixes(void) ;
	//Setters
	void set_type_name(const std::string& name) {
		type_name_ = name;
	}
	void set_image_type(const int type) {
		image_type_ = type;
	}
	void set_brom_format(const int brom_fmt) {
		brom_format_ = brom_fmt;
	}
	void set_eboot_format(const int eboot_fmt) {
		eboot_format_ = eboot_fmt;
	}
	void set_is_bootloader(const std::string& type_name) {
		is_bootloader_ = (type_name == std::string("PRELOADER") ||
			type_name == std::string("DSP_BL")) ? true : false;
	}
	void set_is_format_effective_(const int eboot_format) {
		is_format_effective_ = (eboot_format != UNKNOWN_FMT) ? true : false;
	}
	void set_is_uncheckable(const bool uncheckable){
            is_uncheckable_ = uncheckable;
	}

	void Dump(void);
private:
	std::string ImageTypeToString(const int img_type);
	std::string BromFormatTypeToString(const int brom_fmt);
	std::string EbootFormatTypeToString(const int eboot_fmt);
private:
    list<string> scatters_;
    list<string> prefixes_;
    list<string> suffixes_;
	std::string type_name_;
	int image_type_;
	int brom_format_;
	int eboot_format_;
	bool is_bootloader_;
	bool is_format_effective_;
	bool is_uncheckable_; //add to decide if the image can be unchecked when firmware upgrade
};

class ImageMapRule
{
public:
	ImageType queryType(const string &scatter);
	ImageItem getImageItem(ImageType type);
	std::set<ImageType> image_type_set(void);

	//int getImageSeq(ImageType type) { return sequenceMap[type]; }
private:
	ImageMapRule(const wstring &filename){ LoadFile(filename); };
	void LoadFile(const wstring &filename);

	map<string,ImageType> scatterMap;
	map<ImageType,ImageItem> imageItemMap;
	std::set<ImageType> image_type_set_;
	//map<ImageType,int> sequenceMap;
private:
	friend ImageMapRule& GetImageMapRule();
};

ImageMapRule& GetImageMapRule();

#endif

/*
 * ImageMapRule.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: MTK81019
 */

#include "ImageMapRule.h"
#include "FileUtils.h"
#include "Utility.h"
#include "Logger.h"
#include "eboot/interface.h"
#include "Flashtool_handle.h"

#include "XMLDocument.h"
#include <atlbase.h>
#include <sstream>

using XML::Node;
using XML::Document;

const ImageType UNKNOWN_TYPE = DM_IMG_TYPE_UNKNOWN;
const ImageFormat UNKNOWN_BROM_FMT = UNKNOWN_BIN;
const ImageFormat UNKNOWN_FMT = DM_IMG_FORMAT_UNKNOWN;

void ImageItem::LoadXML(const XML::Node &node) {
	USES_CONVERSION;
	this->scatters_.clear();
	this->prefixes_.clear();
	this->suffixes_.clear();
	for (unsigned int childIndex = 0; childIndex < node.GetNumChildNodes(); ++childIndex) {
		const Node childNode = node.GetChildNode(childIndex);
        wstring nodeName = childNode.GetName();
		if (nodeName == L"scatter") {
			scatters_.push_back(W2CA(childNode.GetText().c_str()));
		} else if (nodeName == L"prefix") {
			prefixes_.push_back(W2CA(childNode.GetText().c_str()));
		} else if (nodeName == L"suffix"){
			suffixes_.push_back(W2CA( childNode.GetText().c_str()));
		}
	}
}

void ImageItem::SaveXML(XML::Node &node) const {
	//Not Implemented, cause we need not save it
}

bool ImageItem::isPrefixMatch(const string &name) {
	for (list<string>::const_iterator it = prefixes_.begin(); it
			!= prefixes_.end(); ++it) {
		if (name.find(*it) == 0)
			return true;
	}
	return false;
}

bool ImageItem::isSuffixMatch(const string & name){
      if(suffixes_.size() == 0)
      	{
      	       LOGW("No suffixes for this image file.");
             return false;
	}

      unsigned int pos = 0;

      pos = name.find_first_of("."); //"." is the seperator between filename and suffix

	for(list<string>::const_iterator it = suffixes_.begin(); 
	        it != suffixes_.end(); ++it)
	{
            if (name.find(*it, pos) != std::string::npos)
	      {
	           LOGD("Matched, file is %s, suffix is %s, continue to find files...", name.c_str(), (*it).c_str());
	           return true;
		}
      }

      LOGD("This file name does not contain specific suffix.");
      return false;
}

std::list<std::string> ImageItem::scatters(void) {
	std::list<std::string> scatters_tmp;
	//Attention: allocate space for dest vector before std::copy
	scatters_tmp.clear();
	scatters_tmp.resize(scatters_.size());
	std::copy(scatters_.begin(), scatters_.end(), scatters_tmp.begin());
	return scatters_tmp;
}

std::list<std::string> ImageItem::prefixes(void) {
	std::list<std::string> prefixs_tmp;
	//Attention: allocate space for dest vector before std::copy
	prefixs_tmp.clear();
	prefixs_tmp.resize(prefixes_.size());
	std::copy(prefixes_.begin(), prefixes_.end(), prefixs_tmp.begin());
	return prefixs_tmp;
}

void ImageItem::Dump(void) {
	LOG("%s(): ====================================.", __FUNC__);
	LOG("%s(): type_name_(%s).", __FUNC__, this->type_name().c_str());
	LOG("%s(): image_type_(%s), enum(%d).", __FUNC__, 
		this->ImageTypeToString(this->image_type()).c_str(), this->image_type());
	LOG("%s(): brom_format_(%s), enum(%d).", __FUNC__,
		this->BromFormatTypeToString(this->brom_format()).c_str(), this->brom_format());
	LOG("%s(): eboot_format_(%s), enum(%d).", __FUNC__,
		this->EbootFormatTypeToString(this->eboot_format()).c_str(), this->eboot_format());
	LOG("%s(): is_bootloader_(%s).", __FUNC__,
		this->is_bootloader() ? "true" : "false");
	LOG("%s(): is_format_effective_(%s).", __FUNC__,
		this->is_format_effective() ? "true" : "false");
	LOG("%s(): is_uncheckable_(%s)", __FUNC__,
		this->is_uncheckable() ? "true" : "false");
	list<string>::iterator it;
	for (it = this->prefixes_.begin(); it != this->prefixes_.end(); it++) {
		LOG("%s(): prefxes(%s).", __FUNC__, it->c_str());
	}
	for( it = this->suffixes_.begin(); it != this->suffixes_.end(); it++) {
             LOG("%s(): suffixes(%s).", __FUNC__, it->c_str());
	}
}

std::string ImageItem::BromFormatTypeToString(const int brom_fmt) {
	switch (brom_fmt) {
		ENUM_TO_CASE_STRING(NORMAL_ROM);
		ENUM_TO_CASE_STRING(RESOURCE_BIN);
		ENUM_TO_CASE_STRING(ENFB_BIN);
		ENUM_TO_CASE_STRING(UA_BIN);
		ENUM_TO_CASE_STRING(BL_BIN);
		ENUM_TO_CASE_STRING(SV5_BL_BIN);
		ENUM_TO_CASE_STRING(YAFFS_IMG);
		default:
			return string("??");
	}
}
std::string ImageItem::EbootFormatTypeToString(const int eboot_fmt)  {
	switch (eboot_fmt) {
		ENUM_TO_CASE_STRING(DM_IMG_FORMAT_FAT);
		ENUM_TO_CASE_STRING(DM_IMG_FORMAT_YAFFS2);
		default:
			return string("??");
	}
}
std::string ImageItem::ImageTypeToString(const int img_type) {
	switch (img_type) {
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_LOGO);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_BOOTIMG);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_ANDROID);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_USRDATA);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_RECOVERY);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_UBOOT);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_AUTHEN_FILE);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_SECSTATIC);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_EU_FT_INFORM);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_FT_LOCK_INFORM);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_PT_TABLE_INFORM);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_CUST_IMAGE1);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_CUST_IMAGE2);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_CUST_IMAGE3);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_CUST_IMAGE4);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_DA);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_JUMP_ADDR);
	    ENUM_TO_CASE_STRING(DM_IMG_TYPE_DA_VERIFY_INFORM);
        default:
			return string("??");
	}
}

void ImageMapRule::LoadFile(const wstring &filename) {
	Document document(filename);
	const Node rootNode = document.GetRootNode();
	assert(rootNode.GetName() == L"image-map");

	const unsigned int numImageNodes = rootNode.GetNumChildNodes();

	//Pre-definition for image item filling by xml file
	ImageItem image;
	wstring img_type_name;
	wstring brom_fmt;
	wstring eboot_fmt;
        wstring attr_img_type;
	string scatterName;
	bool uncheckable;

	USES_CONVERSION;
	for (unsigned int childIndex = 0; childIndex < numImageNodes; ++childIndex) {
		const Node imageNode = rootNode.GetChildNode(childIndex);
		if (wstring(L"image") != imageNode.GetName()) {
			continue;
		}
		image.LoadXML(imageNode);

		img_type_name = imageNode.GetAttribute(L"type_name");
		image.set_type_name(W2CA(img_type_name.c_str()));
		image.set_is_bootloader(image.type_name());
		brom_fmt = imageNode.GetAttribute(L"brom_format");
		image.set_brom_format(WStringToNumber<int>(brom_fmt));
		eboot_fmt = imageNode.GetAttribute(L"eboot_format");
		image.set_eboot_format(WStringToNumber<int>(eboot_fmt));
		image.set_is_format_effective_(image.eboot_format());
		attr_img_type = imageNode.GetAttribute(L"img_type");
		image.set_image_type(WStringToNumber<int>(attr_img_type));
		uncheckable =((wstring(L"true") == imageNode.GetAttribute(L"uncheckable").c_str()) ||
			(wstring(L"TRUE") == imageNode.GetAttribute(L"uncheckable").c_str())) ? true : false;
		image.set_is_uncheckable(uncheckable);
            /*USES_CONVERSION;
             wstring attrSequence = imageNode.GetAttribute(L"sequence");
             std::istringstream iss(W2CA(attrSequence.c_str()));
             iss>>image.sequence;*/
           /**The list data should be copyed to local function statck before using!**/
		list<string> image_scatter_tmp = image.scatters();
		for(list<string>::iterator it = image_scatter_tmp.begin();
			it != image_scatter_tmp.end(); ++it){
				scatterName = *it;				
				scatterMap.insert(pair<string,ImageType>(*it, image.image_type()));
        }
		imageItemMap.insert(pair<ImageType,ImageItem>(image.image_type(), image));
		this->image_type_set_.insert(image.image_type());
        //sequenceMap.insert(pair<ImageType,int>(image.type,image.sequence));
	}
}

ImageType ImageMapRule::queryType(const string &scatter){
	if(scatterMap.find(scatter) == scatterMap.end()){
		return UNKNOWN_TYPE;
	}
	return scatterMap[scatter];
}

ImageItem ImageMapRule::getImageItem(ImageType type){
	return imageItemMap[type];
}

std::set<ImageType> ImageMapRule::image_type_set(void) {
	std::set<ImageType> img_type_set_tmp;
	std::set<ImageType>::iterator it;
	for (it = this->image_type_set_.begin(); it != this->image_type_set_.end(); it++) {
		LOG("%s(): ImageType(%d).", __FUNC__, *it);
		img_type_set_tmp.insert(*it);
	}
	return img_type_set_tmp;
}

ImageMapRule& GetImageMapRule(){
	std::string image_map_xml = FileUtils::GetAppDirectory() + "\\image_map.xml";
	assert(FileUtils::IsFileExist(image_map_xml)&&"image_map.xml does not exist under tool folder!");
	static ImageMapRule currentRule(L"image_map.xml");
	return currentRule;
}

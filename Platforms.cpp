/*
 * Platforms.cpp
 *
 *  Created on: May 5, 2011
 *      Author: MTK81019
 */

#include "Platforms.h"

#include "XMLDocument.h"
#include <atlbase.h>
#include <sstream>
#include <cassert>

#include <algorithm>
#include <cctype>
#include <string>

#include "Logger.h"
#include "FileUtils.h"
#include "Utility.h"

using XML::Node;
using XML::Document;

Platform::Platform() : name(), simple_name(){
	usb_download_support = true;
	nand_util_support = false;
	backup_restore_support = false;
	image_lock_support = false;
	da_dl_all_support = true;
	usb_highspeed_support = false;
	logical_addr_support = false;
	alert_no_com_port = false;
	auto_format_support = false;
	default_bmt_blocks = 0;
    firmware_upgrade_enable = false;
    is_chip_supported = false;
    default_do_not_switch_speed = true;
	this->is_auto_polling_enable_ = false;
	this->auto_polling_upper_limit_ = 0;
}

void Platform::LoadXML(const XML::Node &node) {
	USES_CONVERSION;
	std::wstring temp;

	temp = node.GetAttribute(L"name");
	this->name = W2CA(temp.c_str());

	temp = node.GetAttribute(L"simple_name");
	this->simple_name = W2CA(temp.c_str());

	temp = node.GetAttribute(L"usb_download_support");
	this->usb_download_support = parseBoolean(temp);

    temp = node.GetAttribute(L"dl_auto_detect_battery");
    this->dl_auto_detect_battery = parseBoolean(temp);

	temp = node.GetAttribute(L"nand_util_support");
	this->nand_util_support = parseBoolean(temp);

	temp = node.GetAttribute(L"backup_restore_support");
	this->backup_restore_support = parseBoolean(temp);

	temp = node.GetAttribute(L"image_lock_support");
	this->image_lock_support = parseBoolean(temp);

	temp = node.GetAttribute(L"da_dl_all_support");
	this->da_dl_all_support = parseBoolean(temp);

	temp = node.GetAttribute(L"usb_highspeed_support");
	this->usb_highspeed_support = parseBoolean(temp);

	temp = node.GetAttribute(L"alert_no_com_port");
	this->alert_no_com_port = parseBoolean(temp);

	temp = node.GetAttribute(L"auto_format_support");
	this->auto_format_support = parseBoolean(temp);

	temp = node.GetAttribute(L"usb_dl_control_bit");
	this->usb_dl_control_bit = parseBoolean(temp);

	temp = node.GetAttribute(L"logical_addr_support");
	this->logical_addr_support = parseBoolean(temp);

	temp = node.GetAttribute(L"firmware_upgrade_enable");
	this->firmware_upgrade_enable = parseBoolean(temp);

	temp = node.GetAttribute(L"default_do_not_switch_speed");
	this->default_do_not_switch_speed = parseBoolean(temp);

	temp = node.GetAttribute(L"default_bmt_blocks");
	std::istringstream iss(W2CA(temp.c_str()));
	iss>>this->default_bmt_blocks;

	temp = node.GetAttribute(L"is_default_set_format_length");
	this->is_default_set_format_length = parseBoolean(temp);

	temp = node.GetAttribute(L"is_auto_polling_enable");
	this->is_auto_polling_enable_ = parseBoolean(temp);

       temp = node.GetAttribute(L"auto_format_all_support");
       this->support_auto_format_all_ = parseBoolean(temp);

	temp = node.GetAttribute(L"auto_polling_upper_limit");
	//iss.str(W2CA(temp.c_str()));
	::swscanf(temp.c_str(),
                      L"%u",
                      &auto_polling_upper_limit_);
}

void Platform::SaveXML(XML::Node &node) const {
	assert(0 && "Unsupported operation.");
}

std::string Platform::Dump() const {
	std::string content("\n-------------dumping platform config-------------\n");
	content.append("name:").append(name).append("\n");
	content.append("simple_name:").append(simple_name).append("\n");
	content.append("-----------------------------------------------\n");
	return content;
}

bool Platform::parseBoolean(const std::wstring &value){
	if(value == L"true" || value == L"True" || value == L"TRUE"){
		return true;
	}else if(value == L"false" || value == L"False" || value == L"FALSE"){
		return false;
	}else{
		assert(0 && "Invalid format for boolean value in XML document.");
		return false;
	}
}

std::string PlatformTable::parseScatterName(const std::string &value){
	LOG("PlatformTable::parseScatterName() : %s", value.c_str());

	std::map<std::string, Platform>::const_iterator it;
	for(it = simpleNameMap.begin(); it != simpleNameMap.end(); ++it){
		std::string name = it->first;
		if(value.find(name) != std::string::npos)
			return name;

		std::string lowerName(name);
		std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(),std::tolower);
		LOG("lower name = %s",lowerName.c_str());

		if(value.find(lowerName) != std::string::npos)
			return name;
	}
	return "";
}

std::string PlatformTable::parseChipName(const std::string &value){
	std::map<std::string, Platform>::const_iterator it;
	for(it = nameMap.begin(); it != nameMap.end(); ++it){
		std::string name = it->first;
		if(value.find(name) != std::string::npos)
			return name;

		std::string lowerName(name);
		std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(),std::tolower);
		LOG("PlatformTable::parseChipName(): Lower name = %s",lowerName.c_str());

		if(value.find(lowerName) != std::string::npos)
			return name;
	}
	return "";
}


PlatformTable::PlatformTable(const std::wstring &filename){
	LoadFile(filename);
}

void PlatformTable::LoadFile(const std::wstring &filename){
	Document document(filename);
	const Node rootNode = document.GetRootNode();
	assert(rootNode.GetName() == L"platform-table");

	const unsigned int numNodes = rootNode.GetNumChildNodes();
	for (unsigned int childIndex = 0; childIndex < numNodes; ++childIndex) {
		const Node plNode = rootNode.GetChildNode(childIndex);
		Platform pl;
		pl.LoadXML(plNode);

		nameMap[pl.getName()] = pl;
		simpleNameMap[pl.getSimpleName()] = pl;
	}
}

Platform PlatformTable::queryByScatter(const std::string &scatter){
    std::string simpleName = parseScatterName(scatter);
    Platform platform; 

	if(simpleNameMap.find(simpleName) != simpleNameMap.end()){
		platform = simpleNameMap[simpleName];
        platform.setChipSupported(true);
	} else {
	    platform.setChipSupported(false);
	}
	return platform;  //throw exception
}

Platform PlatformTable::queryBySimpleName(const std::string &simpleName){
    Platform platform; 

	if(simpleNameMap.find(simpleName) != simpleNameMap.end()){
		platform = simpleNameMap[simpleName];
        platform.setChipSupported(true);
	} else {
	    platform.setChipSupported(false);
	}
	return platform;  //throw exception
}

Platform PlatformTable::queryByChipName(const std::string &chipName){
	std::string name = parseChipName(chipName);
    Platform platform; 

	if(nameMap.find(name) != nameMap.end()){
        platform = nameMap[name];
        platform.setChipSupported(true);
	} else {
	    platform.setChipSupported(false);
	}
	return platform;  //throw exception
}

PlatformTable& GetPlatformTable(){
	std::string pl_xml = FileUtils::GetAppDirectory() + "\\platform.xml";
	assert(FileUtils::IsFileExist(pl_xml)&&"platform.xml does not exist under tool folder!");
	static PlatformTable plTable(L"platform.xml");
	return plTable;
}

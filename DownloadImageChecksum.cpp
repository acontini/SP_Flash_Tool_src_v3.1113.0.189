#include <vcl.h>
#pragma hdrstop

#include <inifiles.hpp>
#include <exception>
#include "DownloadImageChecksum.h"
#include "Logger.h"
#include "FileUtils.h"
#include "GlobalData.h"

#ifdef __BORLANDC__
#pragma warn -8004
#endif

using std::string;
using std::map;

const std::string DownloadImageChecksum::kChecksumFileName("\\Checksum.INI");

DownloadImageChecksum::DownloadImageChecksum(void) :
    check_sum_ini_(NULL),
	is_do_checksum_(true),
	is_checksum_file_ready_(false)
{
	this->set_checksum_file_path_by_load();
	if (!this->LoadIniFile()) {
		LOGE("Load %s file error!", this->kChecksumFileName.c_str());
	} else {
		is_checksum_file_ready_ = true;
		InitChecksumMap();
	}
}

DownloadImageChecksum::~DownloadImageChecksum(void)
{
}

bool DownloadImageChecksum::LoadIniFile(void)
{
	string checksum_file;
	if (this->checksum_file_path_.empty()) {
		LOGW("%s is not found in load folder, the file in tool folder will be tried to use.",
			this->kChecksumFileName.c_str());
		checksum_file = FileUtils::GetAppDirectory() + kChecksumFileName;
	} else {
		checksum_file = this->checksum_file_path_;
	}
	if (!FileUtils::IsFileExist(checksum_file)) {
		LOGE("checksum_file(%s) is not found!", checksum_file.c_str());
		return false;
	} else {
	    LOGD("checksum_file(%s).", checksum_file.c_str());
	}

	try {
		check_sum_ini_ = new TIniFile(checksum_file.c_str());
	} catch (...) {
		LOGE("%s could not be found or opened!", this->kChecksumFileName.c_str());
		return false;
	}
	return true;
}

void DownloadImageChecksum::UnLoadIniFile(void)
{
	if ( NULL != check_sum_ini_) {
		delete check_sum_ini_;
		check_sum_ini_ = NULL;
	}
}

void DownloadImageChecksum::InitChecksumMap(void)
{
	//Check if do checksum
	this->is_do_checksum_  = check_sum_ini_->ReadBool ( "IsEnableChecksum", "CHECKSUM_SWITCH", true);
	//Load checksum reference values    
	TStringList* str_list = NULL;
	try {
		str_list = new TStringList;
		this->check_sum_ini_->ReadSection("CheckSum", str_list);
		unsigned int check_sum = 0;
		int checksum_items_count = str_list->Count;
		for ( int i = 0; i < checksum_items_count; i++) {
		    check_sum = strtoul(check_sum_ini_->ReadString("CheckSum", str_list->Strings[i], "0x00000000").c_str(), NULL, 16);
			image_checksum_map_.insert(std::make_pair(str_list->Strings[i].c_str(), check_sum));
		}
	} catch (const std::exception& ex) {
		if (NULL != str_list) {
		    delete str_list;
			str_list = NULL;
		}
		LOGE("Init image_checksum_map_ failed, reason(%s).", ex.what());
	}

	if (NULL != str_list) {
		delete str_list;
		str_list = NULL;
	}
}

void DownloadImageChecksum::Dump()
{
	map<string, unsigned int>::iterator it;
	for (it = image_checksum_map_.begin(); it != image_checksum_map_.end(); it++) {
		LOG("%s(): image_key(%s), checksum_value(%u).", __FUNC__, it->first.c_str(), it->second);
	}
}

unsigned int DownloadImageChecksum::QueryChecksumValueByImageName(const std::string& img_name)
{
	map<string, unsigned int>::iterator it = this->image_checksum_map_.find(img_name);
	if ( it != this->image_checksum_map_.end() ) {
		return it->second;
	} else {
		LOG("ERROR: %s(): Could not found the key(%s).", __FUNC__, img_name.c_str());
		return 0;
	}
}

void DownloadImageChecksum::set_checksum_file_path_by_load(void) 
{
	if (!g_platform_info.load_path().empty()) {
		std::string checksum_file = g_platform_info.load_path() + kChecksumFileName;
		if (FileUtils::IsFileExist(checksum_file)) {
	        this->checksum_file_path_ = checksum_file;
		} else {
			LOGW("checksum_file(%s) is not found in load folder!", checksum_file.c_str());
		}
	} else {
		LOGW("load_path is empty!");
	}
}

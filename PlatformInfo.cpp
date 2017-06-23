/*
 * PlatformInfo.cpp
 *
 *  Created on: Apr 22, 2011
 *      Author: MTK81019
 */

#include <assert.h>
#include "PlatformInfo.h"
#include "Logger.h"
#include "Utility.h"
#pragma warn -8004

const int PlatformInfo::DEFAULT_BMT_BLOCKS_MT6573 = 80;
const int PlatformInfo::DEFAULT_PMT_BLOCKS_MT6573(2);

PlatformInfo::PlatformInfo() {
	m_BMT_blocks = 0;
	m_DA_DL_all_enabled = false;
	is_scatter_file_valid_ = true;
	is_storage_type_support_ = true;
	initStorageOperationTable();
}

PlatformInfo::~PlatformInfo() {
}

void PlatformInfo::initByScatterFile(const std::string &scatterFile, std::string& error_hint, bool isSCI) {

      Platform new_platform;
      std::string platformStr;

	if(isSCI)
	{
	     new_platform = GetPlatformTable().queryByScatter(m_current_scatter);
	}
	else{
	platformStr = scatterFile;

	int dpos = scatterFile.find_last_of('\\');
	if (dpos != std::string::npos) {
		platformStr = scatterFile.substr(dpos + 1);
	}
	  
           new_platform = GetPlatformTable().queryByScatter(platformStr);	
		
	}
	   
	//Set load path for handling files in load folder
	set_load_path(scatterFile);	

    if(!new_platform.isChipSupported()) {
    	error_hint = "Error: Initializing scatter file failed. Please check the name of scatter file which you load is legal.";
    	LOGE("Scatter file which is loaded is not be supported!");
    	this->is_scatter_file_valid_ = false;
        return;
    } else {
    	this->is_scatter_file_valid_ = true;
    }

	m_BMT_blocks = new_platform.getDefaultBMTBlocks();
	m_DA_DL_all_enabled = new_platform.supportDADownloadAll();
	m_current_scatter = new_platform.getSimpleName();

	if(m_platform.getName() != new_platform.getName()){
		m_platform = new_platform;
		LOG("PlatformInfo::initByScatterFile(): notifying OBs with new platform: %s", m_platform.getSimpleName().c_str());
		notifyObservers();
	}
	LOGD(m_platform.Dump().c_str());

	std::string error_msg;
	std::string storage; 
	if(isSCI){
	storage = m_storage;
	LOG("%s: storage(%s)", __FUNC__, m_storage.c_str());
	}else{
	storage = JudgeStorageOperation(platformStr);
	}
	
	if (!m_storage_config.QueryStorage(m_platform.getSimpleName(), storage, error_msg)) {
        error_hint = error_msg;
        LOGW("%s.", error_msg.c_str());
        this->is_storage_type_support_ = false;
        notifyObservers();
	} else {
		this->is_storage_type_support_ = true;
		if (m_storage_config.IsOperationChangend(m_platform.getSimpleName(), storage)){
	        notifyObservers();
		}
	}
}

void PlatformInfo::InitByPlatCfgInfo(const DL_PlatformInfo & plat_cfg_info, std::string& error_hint, bool isSCI) {
    assert(NULL != &plat_cfg_info); 
    Platform new_platform;
    std::string chip_name(plat_cfg_info.m_szBBChipType);
	std::string storage(plat_cfg_info.m_szStorageType);
    //TODO: Add for SCI operation

    new_platform = GetPlatformTable().queryByScatter(chip_name);	
	   
	//TODO: Set load path for handling files in load folder

    if(!new_platform.isChipSupported()) {
    	error_hint = "Error: Initializing scatter file failed. Please check the name of scatter file which you load is legal.";
    	LOGE("Scatter file which is loaded is not be supported!");
    	this->is_scatter_file_valid_ = false;
        return;
    } else {
    	this->is_scatter_file_valid_ = true;
    }

	m_BMT_blocks = new_platform.getDefaultBMTBlocks();
	m_DA_DL_all_enabled = new_platform.supportDADownloadAll();
	m_current_scatter = new_platform.getSimpleName();

	if(m_platform.getName() != new_platform.getName()){
		m_platform = new_platform;
		LOG("PlatformInfo::initByScatterFile(): notifying OBs with new platform: %s", m_platform.getSimpleName().c_str());
		notifyObservers();
	}
	LOGD(m_platform.Dump().c_str());

	if (!m_storage_config.QueryStorage(m_platform.getSimpleName(), storage, error_hint)) {
        LOGW("%s.", error_hint.c_str());
        this->is_storage_type_support_ = false;
        notifyObservers();
	} else {
		this->is_storage_type_support_ = true;
		if (m_storage_config.IsOperationChangend(m_platform.getSimpleName(), storage)){
	        notifyObservers();
		}
	}
}

void PlatformInfo::setChipName(const std::string &chipName) {
	LOG("PlatformInfo::setChipName() : %s", chipName.c_str());

	Platform new_platform = GetPlatformTable().queryByChipName(chipName);
	m_current_chip = new_platform.getName();

	if(isPlatformMatched()){
		m_platform = new_platform;
	}else{
		//scatter platform is not matched with current chip
		//TODO: throw exception.
		LOG("Platform not matched! scatter: %s, chip: %s.", m_current_scatter.c_str(), m_current_chip.c_str());
	}

	LOGD(m_platform.Dump().c_str());
}

bool PlatformInfo::isPlatformMatched() {
	return m_current_chip.find(m_current_scatter) != std::string::npos;
}

bool PlatformInfo::isStorageMatched(const std::string &targetStorage) {
      m_target_storage = targetStorage;
      m_storage = this->getFlashToolStorageConfig().GetStorageName();
			
	LOGD("targetStorage(%s), loadStorage(%s).", targetStorage.c_str(), m_storage.c_str());
	return (m_target_storage == m_storage);
}

void PlatformInfo::notifyObservers(){
	for(std::list<IPlatformOb*>::const_iterator it = observers.begin();
			it != observers.end(); ++it){
		(*it)->onPlatformChanged();
	}
}
std::string PlatformInfo::getTargetStorageName() const{
       LOG("%s: GetTargetStorageName(): %s.", __FUNC__, m_target_storage.c_str());
	 return m_target_storage;
}
std::string PlatformInfo::getLoadPlatformName() const{
	LOG("PlatformInfo::getLoadPlatformName(): %s",m_current_scatter.c_str());
	return m_current_scatter;
}

std::string PlatformInfo::getTargetPlatformName() const{
	LOG("PlatformInfo::getTargetPlatformName(): %s",m_current_chip.c_str());
	return m_current_chip;
}

void PlatformInfo::setDADownloadAllEnabled(bool enabled){
	m_DA_DL_all_enabled = enabled;
	notifyObservers();
}

void PlatformInfo::initStorageOperationTable(void) {
	m_storage_oper_table_.push_back("NAND");
	m_storage_oper_table_.push_back("EMMC");
	m_storage_oper_table_.push_back("SDMMC");
}

std::string PlatformInfo::JudgeStorageOperation(const std::string& scatt) {
	std::string oper = "NAND";
	std::string tmp = ToUppercaseString(scatt);
	for (std::vector<std::string>::const_iterator it = m_storage_oper_table_.begin();
			it != m_storage_oper_table_.end(); it++) {
		if (tmp.find(*it) != std::string::npos) {
			oper = *it;
			break;
		}
	}
	//If the other storage type could not be found,
	//nand type will be returned
	return oper;
}

void PlatformInfo::set_load_path(const std::string& path)
{
	this->load_path_ = path;
	}

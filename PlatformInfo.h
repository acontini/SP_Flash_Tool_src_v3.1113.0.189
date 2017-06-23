/*
 * PlatformInfo.h
 *
 *  Created on: Apr 22, 2011
 *      Author: MTK81019
 */

#ifndef PLATFORMINFO_H_
#define PLATFORMINFO_H_

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Platforms.h"
#include "FlashToolStorageConfig.h"
#include "FlashToolTypedefs.h"
#include "flashtool_handle.h"

class IPlatformOb{
public:
	virtual void onPlatformChanged() = 0;
};

class PlatformInfo{
public:
	static const int DEFAULT_BMT_BLOCKS_MT6573;
	static const int DEFAULT_PMT_BLOCKS_MT6573;
	
	PlatformInfo();
	~PlatformInfo();

	//called when load a scatter file, will update UI accordingly
	void initByScatterFile(const std::string &scatterFile, std::string& error_hint, bool isSCI);
	void InitByPlatCfgInfo(const DL_PlatformInfo &plat_cfg_info, std::string& error_hint, bool isSCI);

	//called @ runtime when get DA report, will update platform config, but will not update UI
	void setChipName(const std::string &chipName);
       //for SCI Download
	void setSimpleName(const std::string &simpleName)
	{
               m_current_scatter = simpleName;
	}
	
	bool isPlatformMatched();
	bool isStorageMatched(const std::string &targetStorage);

	bool isDADownloadAllEnabled() const{
		return m_DA_DL_all_enabled && m_platform.supportDADownloadAll();
	}

	void setDADownloadAllEnabled(bool enabled);

	std::string getLoadPlatformName() const;

	std::string getTargetPlatformName() const;
	std::string getTargetStorageName() const;

	void setBMTBlocks(unsigned int blocks){
		m_BMT_blocks = blocks;
	}
	unsigned int getBMTBlocks() const{
		return m_BMT_blocks;
	}

	unsigned int getNandReservedBlocks() const {
		return (m_BMT_blocks + PlatformInfo::DEFAULT_PMT_BLOCKS_MT6573);
	}

	void addObserver(IPlatformOb *ob){
		observers.push_back(ob);
	}

	Platform getPlatformConfig() const{
		return m_platform;
	}

	FlashToolStorageConfig getFlashToolStorageConfig() const {
		return m_storage_config;
	}

	bool is_scatter_file_valid(void) const {
		return is_scatter_file_valid_;
	}

	bool is_storage_type_support(void) const {
		return is_storage_type_support_;
	}

        void setStorage(const std::string &storage)
	{
              m_storage = storage;
	}

	std::string load_path(void) const {
		return this->load_path_;
	}

	void set_load_path(const std::string& path);

private:
	void initUsbHighSpeedChipMap();
	void notifyObservers();
	//20110825 modify for nand/emmc/sdmmc storage type switch
	void initStorageOperationTable(void);

private:
    std::string JudgeStorageOperation(const std::string& scatt);
	Platform m_platform;
	FlashToolStorageConfig m_storage_config;
	unsigned int m_BMT_blocks;
	bool m_DA_DL_all_enabled;
	std::string m_current_scatter;  //MT6573
	std::string m_current_chip;   //MT6573_S0X
	std::string m_storage; //EMMC,NAND...
	std::string m_target_storage;
	std::list<IPlatformOb *> observers;
	//20110825 add map for nand/emmc/sdmmc storage type switch
	std::vector<std::string> m_storage_oper_table_;
	bool is_scatter_file_valid_;
	bool is_storage_type_support_;
	//add a column to obtain load folder location
	std::string load_path_;
};


#endif /* PLATFORMINFO_H_ */

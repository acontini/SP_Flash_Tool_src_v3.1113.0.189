#include "FlashToolStorageConfig.h"
#include "Utility.h"
#include "Logger.h"
#include "flashtool.h"
#include "XMLDocument.h"
#include "FileUtils.h"

#include <atlbase.h>
#include <cassert>
#include <sstream>

#ifdef __BORLANDC__
#pragma warn -8004
#endif

using std::string;
using std::wstring;
using std::map;
using std::vector;
using XML::Node;
using XML::Document;

const wstring FlashToolStorageTable::kStoragePlatformName(L"name");
const wstring FlashToolStorageAttrTable::kStorageTypeNameAttr(L"type-name");
const wstring FlashToolStorageAttrTable::kStorageIsSupportAttr(L"is-support");
const wstring FlashToolStorageAttrTable::kStorageIsSupportAutoFmtAttr(L"is-support-auto-format");
const wstring FlashToolStorageAttrTable::kStorageHWTypeAttr(L"hw-storage-type");
const wstring FlashToolStorageAttrTable::kStorageMEMTypeAttr(L"mem-storage-type");
//modification for 64bit format addressing
const wstring FlashToolStorageAttrTable::kStorageHWBitAttr(L"storage-addressing-type");
const wstring FlashToolStorageTable::kStorageRootNode(L"storage-setting");
const wstring FlashToolStorageTable::kStorageSettingFile(L"storage_setting.xml");

FlashToolStorageAttrTable::FlashToolStorageAttrTable() :
    	    is_support_(false),
			is_support_auto_fmt_(false),
    	    storage_type_(HW_STORAGE_NAND),
    	    memory_type_(HW_MEM_NAND),
    	    storage_addressing_type_(8)
{
	InitStorageTypeMap();
	InitMemoryTypeMap();
}

void FlashToolStorageAttrTable::InitStorageTypeMap(void)
{
	storage_type_map_["HW_STORAGE_NOR"] = HW_STORAGE_NOR;
	storage_type_map_["HW_STORAGE_NAND"] = HW_STORAGE_NAND;
	storage_type_map_["HW_STORAGE_EMMC"] = HW_STORAGE_EMMC;
	storage_type_map_["HW_STORAGE_SDMMC"] = HW_STORAGE_SDMMC;
}

void FlashToolStorageAttrTable::InitMemoryTypeMap(void)
{
	memory_type_map_["HW_MEM_NOR"] = HW_MEM_NOR;
	memory_type_map_["HW_MEM_NAND"] = HW_MEM_NAND;
	memory_type_map_["HW_MEM_EXT_SRAM"] = HW_MEM_EXT_SRAM;
	memory_type_map_["HW_MEM_EXT_DRAM"] = HW_MEM_EXT_DRAM;
	memory_type_map_["HW_MEM_EMMC"] = HW_MEM_EMMC;
	memory_type_map_["HW_MEM_SDMMC"] = HW_MEM_SDMMC;
}

void FlashToolStorageAttrTable::LoadXML(const XML::Node& node)
{
	USES_CONVERSION;
	this->storage_name_ = W2CA(node.GetAttribute(kStorageTypeNameAttr).c_str());
	this->is_support_ = ((wstring(L"true") == node.GetAttribute(kStorageIsSupportAttr).c_str()) ||
			(wstring(L"TRUE") == node.GetAttribute(kStorageIsSupportAttr).c_str())) ? true : false;
	this->is_support_auto_fmt_ = ((wstring(L"true") == node.GetAttribute(kStorageIsSupportAutoFmtAttr).c_str()) ||
			(wstring(L"TRUE") == node.GetAttribute(kStorageIsSupportAutoFmtAttr).c_str())) ? true : false;
	//get storage_addressing_type_ value from XML file
	string str_addressing_type_ = W2CA(node.GetAttribute(kStorageHWBitAttr).c_str());	
	this->storage_addressing_type_ = atoi(str_addressing_type_.c_str());
		string storage_type = W2CA(node.GetAttribute(kStorageHWTypeAttr).c_str());
	string memory_type = W2CA(node.GetAttribute(kStorageMEMTypeAttr).c_str());
    std::map<std::string, HW_StorageType_E>::const_iterator it_storage = storage_type_map_.find(storage_type);
    assert(it_storage != storage_type_map_.end());
    this->storage_type_ = it_storage->second;
    std::map<std::string, HW_MemoryType_E>::const_iterator it_memory = memory_type_map_.find(memory_type);
    assert(it_memory != memory_type_map_.end());
    this->memory_type_ = it_memory->second;
}

void FlashToolStorageAttrTable::SaveXML(Node& node) const
{
	assert(0 && "Not support!");
}
FlashToolStorageTable::FlashToolStorageTable(const wstring& file_name)
{
    LoadFile(file_name);
}

void FlashToolStorageTable::LoadFile(const wstring& file_name)
{
	USES_CONVERSION;
	Document document(file_name);
	const Node root_node = document.GetRootNode();
	assert(root_node.GetName() == FlashToolStorageTable::kStorageRootNode);

	FlashToolStorageInfo storage_info;
	FlashToolStorageAttrTable storage_attr;
	Node child_node = root_node.GetChildNode(0);
	const unsigned int num_child_node = root_node.GetNumChildNodes();
	unsigned int num_grandchild_node = 0;
	std::string platform;
	StorageAttrMap storage_attr_table;
	for (unsigned int i = 0; i < num_child_node; i++) {
		child_node = root_node.GetChildNode(i);
		platform = (W2CA(child_node.GetAttribute(kStoragePlatformName).c_str()));
        num_grandchild_node = child_node.GetNumChildNodes();
        for(unsigned int j = 0; j < num_grandchild_node; j++) {
        	storage_attr.LoadXML(child_node.GetChildNode(j));
        	storage_info.set_storage_name(storage_attr.storage_name());
        	storage_info.set_is_support(storage_attr.is_support());
			storage_info.set_is_support_auto_format(storage_attr.is_support_auto_fmt());
        	storage_info.set_storage_type(storage_attr.storage_type());
        	storage_info.set_memory_type(storage_attr.memory_type());
		storage_info.set_storage_addressing_type(storage_attr.storage_addressing_type());
		        	storage_attr_table[storage_info.storage_name()]= storage_info;
        	storage_operation_map_[storage_info.storage_type()] = storage_info.storage_name();
        }
        this->platform_storage_table_.push_back(std::make_pair(platform, storage_attr_table));
        //Clear storage attribute map for next platform storage vector content
        storage_attr_table.clear();
	}
	Dump();
}

void FlashToolStorageTable::Dump(void)
{
	std::vector<PlatformOperPair>::iterator it_plat_oper;
	StorageAttrMap::iterator it_storage_attr_map;
	it_plat_oper = platform_storage_table_.begin();
	//platform vector
	for(; it_plat_oper != platform_storage_table_.end(); it_plat_oper++) {
		LOGD("platform(%s).",it_plat_oper->first.c_str());
		it_storage_attr_map = it_plat_oper->second.begin();
		//storage vector
		for(; it_storage_attr_map != it_plat_oper->second.end(); it_storage_attr_map++) {
			LOGD("storage type(%s) -> is_support(%s), is_support_auto_format(%s), storage_type_(%s), memory_type_(%s), storage_addressing_type_(%d).",
					it_storage_attr_map->first.c_str(),
					it_storage_attr_map->second.is_support() ? "true" : "false",
					it_storage_attr_map->second.is_support_auto_format() ? "true" : "false",
					HWStorageTypeToString(it_storage_attr_map->second.storage_type()),
					HWMemoryTypeToString(it_storage_attr_map->second.memory_type()),
					it_storage_attr_map->second.storage_addressing_type());
		}
	}
	std::map<HW_StorageType_E, std::string>::const_iterator it_storage_type_name_map = storage_operation_map_.begin();
	for(; it_storage_type_name_map != storage_operation_map_.end(); it_storage_type_name_map++) {
		LOGD("Storage type(%s) -> Storage name(%s).",
				HWStorageTypeToString(it_storage_type_name_map->first),
				it_storage_type_name_map->second.c_str());
	}
}

bool FlashToolStorageTable::QueryStorageInfo(
		const string& platform,
		const string& storage_name,
		FlashToolStorageInfo& storage_info) {
	LOGD("platform(%s), storage_name(%s) to be queried.", platform.c_str(), storage_name.c_str());
	bool is_platform_found = false;
	bool is_storage_name_found = false;
	std::vector<PlatformOperPair>::iterator it_plat_vector = platform_storage_table_.begin();
	StorageAttrMap::iterator it_storage_attr_map;
	for (; it_plat_vector != platform_storage_table_.end(); it_plat_vector++) {
		LOGD("platform(%s) in the table.", it_plat_vector->first.c_str());
		if (platform == it_plat_vector->first) {
			LOGD("%s is matched.", it_plat_vector->first.c_str());
			is_platform_found = true;
			it_storage_attr_map = it_plat_vector->second.find(storage_name);
			if (it_storage_attr_map != it_plat_vector->second.end()) {
				is_storage_name_found = true;
				storage_info.set_is_support(it_storage_attr_map->second.is_support());
				LOGD("%s type is matched, and (%s) be supported.",
						storage_name.c_str(),
						storage_info.is_support() ? "Yes" : "No");
				if(storage_info.is_support()) {
				storage_info.set_storage_name(it_storage_attr_map->second.storage_name());
				storage_info.set_storage_type(it_storage_attr_map->second.storage_type());
				storage_info.set_memory_type(it_storage_attr_map->second.memory_type());
				storage_info.set_is_support_auto_format(it_storage_attr_map->second.is_support_auto_format());
				storage_info.set_storage_addressing_type(it_storage_attr_map->second.storage_addressing_type());
								} else {
					storage_info.set_storage_name("NAND");
					storage_info.set_storage_type(HW_STORAGE_NAND);
					storage_info.set_memory_type(HW_MEM_NAND);
					storage_info.set_is_support_auto_format(true);
					storage_info.set_storage_addressing_type(8);
									}
			} else {
				//default nand is applied
				storage_info.set_is_support(false);
				storage_info.set_storage_name("NAND");
				storage_info.set_storage_type(HW_STORAGE_NAND);
				storage_info.set_memory_type(HW_MEM_NAND);
				storage_info.set_storage_addressing_type(8);
			}
			break;
		}
	}
	return (is_platform_found && is_storage_name_found);
}

std::map<HW_StorageType_E, std::string> FlashToolStorageTable::storage_operation_map(void)
{
	//Note: For std::map don't use assignment return
	//Reason: The elements contained in the object before the call are dropped after assignment
	std::map<HW_StorageType_E, std::string> tmp_map;
	std::map<HW_StorageType_E, std::string>::iterator it_storage_oper_map = storage_operation_map_.begin();
	for(; it_storage_oper_map != storage_operation_map_.end(); it_storage_oper_map++) {
		tmp_map[it_storage_oper_map->first] = it_storage_oper_map->second;
	}
	return tmp_map;
}

//Singleton FlashToolStorageTable
FlashToolStorageTable& GetFlashToolStorageTable()
{
	std::string usb_xml = FileUtils::GetAppDirectory() + "\\" + WStr2Str(FlashToolStorageTable::kStorageSettingFile);
	assert(FileUtils::IsFileExist(usb_xml) && "storage_setting.xml does not exist under tool folder!");

	static FlashToolStorageTable storage_table(FlashToolStorageTable::kStorageSettingFile);
	return storage_table;
}

FlashToolStorageConfig::FlashToolStorageConfig() :
	platform_("MT6516"),
	storage_name_("NAND"),
	memory_type_(HW_MEM_NAND),
	storage_type_(HW_STORAGE_NAND),
	is_support_auto_format_(false),
	storage_addressing_type_(8)
{
}

FlashToolStorageConfig::FlashToolStorageConfig(const FlashToolStorageConfig &storage)
{
	this->platform_ = storage.platform_;
	this->storage_name_ = storage.storage_name_;
	this->storage_type_ = storage.storage_type_;
	this->memory_type_ = storage.memory_type_;
	this->is_support_auto_format_ = storage.is_support_auto_format_;
	this->storage_addressing_type_ = storage.storage_addressing_type_;
}

FlashToolStorageConfig& FlashToolStorageConfig::operator =(const FlashToolStorageConfig &storage)
{
	if ( this == &storage) {
		return* this;
	} else {
		this->platform_ = storage.platform_;
		this->storage_name_ = storage.storage_name_;
		this->storage_type_ = storage.storage_type_;
		this->memory_type_ = storage.memory_type_;
		this->is_support_auto_format_ = storage.is_support_auto_format_;
		this->storage_addressing_type_ = storage.storage_addressing_type_;
		return *this;
	}
}

FlashToolStorageConfig::~FlashToolStorageConfig()
{}

bool FlashToolStorageConfig::QueryStorage(
		const string& platform,
		const string& storage_name,
		string& error_msg)
{
	FlashToolStorageTable storage_table = GetFlashToolStorageTable();
	FlashToolStorageInfo storage_info;
	storage_table.QueryStorageInfo(platform, storage_name, storage_info);
	this->platform_ = platform;
	this->storage_name_ = storage_info.storage_name();
	this->storage_type_ = storage_info.storage_type();
	this->memory_type_ = storage_info.memory_type();
	this->is_support_auto_format_ = storage_info.is_support_auto_format();
	this->storage_addressing_type_ = storage_info.storage_addressing_type();
	if (storage_info.is_support()) {
		LOGD("(%s) is supported by (%s).",
				platform.c_str(),
				storage_info.storage_name().c_str());
	} else {
		std::ostringstream oss;
		oss << storage_name << " is not supported by "
			<< platform << ", default \""
			<< storage_info.storage_name() << "\" storage type is applied!";
		LOGW("%s.", oss.str().c_str());
		error_msg = oss.str();
	}
	return storage_info.is_support();
}

void FlashToolStorageConfig::Dump()
{
	std::ostringstream tmp_oss;
	tmp_oss << "Storage name("
		<<GetStorageName().c_str()
		<<"), StorageType("
		<<HWStorageTypeToString(GetStorageType())
		<<"), MemoryType("
		<<HWMemoryTypeToString(GetMemoryType())
		<<"), IsSupportAutoFormat("
		<<(this->IsSupportAutoFormat() ? "true" : "false")
		<<"), AddressingType("
		<<GetAddressingType()
		<<").";
	LOGD("%s", tmp_oss.str().c_str());	
}

std::string FlashToolStorageConfig::QueryStorageNameByStorageType(const HW_StorageType_E type)
{
	FlashToolStorageTable storage_table = GetFlashToolStorageTable();
	std::map<HW_StorageType_E, std::string> tmp_map = storage_table.storage_operation_map();
	map<HW_StorageType_E, string>::const_iterator it = tmp_map.find(type);
	if ( it != storage_table.storage_operation_map().end() ) {
		return it->second;
	} else {
		return string("Unknown");
	}
}

bool FlashToolStorageConfig::IsOperationChangend(const string& platform, const string& storage_name)
{
	bool is_operation_change = false;
	static std::string platform_history;
	static std::string storage_name_history;
	LOGD("Old platform(%s), storage type(%s).",
			platform_history.c_str(),
			storage_name_history.c_str());
	if ((platform != platform_history) || (storage_name != storage_name_history)) {
		is_operation_change = true;
	}
	LOGD("New platform(%s), storage type(%s).", platform.c_str(), storage_name.c_str());
	platform_history = platform;
	storage_name_history = storage_name;
	return is_operation_change;
}



#include "FlashToolUSB.h"
#include "XMLDocument.h"
#include <atlbase.h>
#include <cassert>
#include "Logger.h"
#include "FileUtils.h"
#include "Utility.h"

using XML::Node;
using XML::Document;
using std::string;
using std::map;

//USB Port names
const std::string FlashToolUSB::BOOTROM_VCOM("BOOTROM_VCOM");
const std::string FlashToolUSB::PRELOADER_VCOM("PRELOADER_VCOM");
const std::string FlashToolUSB::DA_HIGHSPEED_VCOM("DA_HIGHSPEED_VCOM");
const std::string FlashToolUSB::GADGET_VCOM("GADGET_VCOM");
const std::string FlashToolUSB::COMPOSITE_PRELOADER_VCOM("COMPOSITE_PRELOADER_VCOM");
const std::string FlashToolUSB::COMPOSITE_DA_VCOM("COMPOSITE_DA_VCOM");
//USB Item attribute
const std::wstring FlashToolUSB::USB_NAME(L"name");
const std::wstring FlashToolUSB::USB_PID(L"pid");
const std::wstring FlashToolUSB::USB_VID(L"vid");
const std::wstring FlashToolUSB::USB_GUID_TYPE(L"guid-type");
const std::wstring FlashToolUSB::USB_PORT_GUID_CLASS(L"port-guid-class");
const std::wstring FlashToolUSB::USB_PORT_GUID_INTERFACE(L"port-guid-interface");
//USB Table usb_setting.xml
const std::wstring FlashToolUSBTable::USB_SETTING_FILE(L"usb_setting.xml");
const std::wstring FlashToolUSBTable::USB_ROOT_NODE(L"usb-setting");

//USBSer
DEFINE_GUID(GUID_ANDROID_DL_USB2SER, 0xA5DCBF10L,0x6530,0x11D2,0x90,0x1F,0x00,0xC0,0x4F,
                            0xB9,0x51,0xED);
DEFINE_GUID(GUID_PORT_CLASS_USB2SER, 0x4D36E978L,0xE325,0x11CE,0xBF,0xC1,0x08,0x00,0x2B,
			0xE1,0x03,0x18);

FlashToolUSB::FlashToolUSB(void)
{
}

FlashToolUSB::~FlashToolUSB(void)
{
}

void FlashToolUSB::LoadXML(const XML::Node &node)
{
	USES_CONVERSION;
	Node childNode = node;
	const unsigned int numNodes = node.GetNumChildNodes();
	m_USBName = W2CA(node.GetAttribute(FlashToolUSB::USB_NAME).c_str());
	for (unsigned int childIndex = 0; childIndex < numNodes; ++childIndex) {
		childNode = node.GetChildNode(childIndex);
		if ( FlashToolUSB::USB_PID == childNode.GetName() ) {
			m_USBPID = W2CA(childNode.GetText().c_str());
		} else if (FlashToolUSB::USB_VID == childNode.GetName() ) {
			m_USBVID = W2CA(childNode.GetText().c_str());
		} else if (FlashToolUSB::USB_GUID_TYPE == childNode.GetName() ) {
			m_USBGUIDType = W2CA(childNode.GetText().c_str());
		} else {
			LOGW("Invalid usb item type(%s)!", W2CA(childNode.GetText().c_str()));
		}
	}
}

void FlashToolUSB::SaveXML(XML::Node &node) const
{
	assert(0 && "Unsupported operation.");
}

void FlashToolUSBTable::InitializeUSBGUIDMAP(void)
{
	USES_CONVERSION;
	m_USBGUIDMap.clear();
	m_USBGUIDMap.insert(std::make_pair(W2CA(FlashToolUSB::USB_PORT_GUID_INTERFACE.c_str()), 
		(GUID*)&GUID_ANDROID_DL_USB2SER));
	m_USBGUIDMap.insert(std::make_pair(W2CA(FlashToolUSB::USB_PORT_GUID_CLASS.c_str()), 
		(GUID*)&GUID_PORT_CLASS_USB2SER));
}


FlashToolUSBTable::FlashToolUSBTable(const std::wstring &fileName)
{
	LoadFile(fileName);
    InitializeUSBGUIDMAP();
}

void FlashToolUSBTable::LoadFile(const std::wstring &fileName)
{
	USES_CONVERSION;
	Document document(fileName);
	const Node rootNode = document.GetRootNode();
	assert(rootNode.GetName() == FlashToolUSBTable::USB_ROOT_NODE);

	FlashToolUSB usbPort;
	Node childNode = rootNode.GetChildNode(0);
	const unsigned int numNodes = rootNode.GetNumChildNodes();
	string usbName;
	for (unsigned int childIndex = 0; childIndex < numNodes; ++childIndex) {
        childNode = rootNode.GetChildNode(childIndex);
		usbPort.LoadXML(childNode);		
		usbName = W2CA(childNode.GetAttribute(FlashToolUSB::USB_NAME).c_str());
		m_FlashToolUSBMap.insert( std::make_pair( usbName, usbPort) );
		m_FlashToolPIDUSBMap.insert( std::make_pair(usbPort.GetUSBPID(), usbPort) );
	}
	Dump();
}

void FlashToolUSBTable::Dump()
{
	map<std::string, FlashToolUSB>::const_iterator it = m_FlashToolUSBMap.begin();
	for(; it != m_FlashToolUSBMap.end(); it++) {
		LOG("FlashToolUSBTable::Dump(): USB Name(%s), USB PID(%s), USB VID(%s), USB GUID Type(%s).",
			it->second.GetUSBName().c_str(),
			it->second.GetUSBPID().c_str(),
			it->second.GetUSBVID().c_str(),
			it->second.GetUSBGUIDType().c_str());
	}
}

bool FlashToolUSBTable::QueryUSBItemByName(const std::string &name, FlashToolUSB &usb_port)
{
	bool isFind = false;
	map<std::string, FlashToolUSB>::const_iterator it = m_FlashToolUSBMap.find(name.c_str());
	if ( it != m_FlashToolUSBMap.end() ) {
		isFind = true;
		usb_port = m_FlashToolUSBMap[name];
	} else {
		LOG("ERROR: FlashToolUSBTable::QueryUSBItemByName(): %s failed!", name.c_str());
	}
	return isFind;
}

bool FlashToolUSBTable::QueryUSBItemByPID(const std::string& pid, FlashToolUSB &usb_port)
{
	bool isFind = false;
	map<std::string, FlashToolUSB>::const_iterator it = m_FlashToolPIDUSBMap.find(pid.c_str());
	if ( it != m_FlashToolPIDUSBMap.end() ) {
		isFind = true;
		usb_port = it->second;
	} else {
		LOG("ERROR: FlashToolUSBTable::QueryUSBItemByPID(): %s failed!", pid.c_str());
	}
	return isFind;
}

bool FlashToolUSBTable::QueryUSBGUIDByPID(const std::string& pid, GUID* p_guid)
{
	assert(p_guid != NULL);

	bool isFind = false;
    FlashToolUSB usb_port;
	if ( !QueryUSBItemByPID(pid, usb_port) ) {
		LOG("ERROR: FlashToolUSBTable::QueryUSBGUIDByPID(): QueryUSBItemByPID(): PID(%s) failed!", 
			pid.c_str());
	} else {
		//LOG("FlashToolUSBTable::QueryUSBItemByPID() succeed, USB Port(%s), PID(%s), VID(%s).", 
		//	usb_port.GetUSBName().c_str(), usb_port.GetUSBPID().c_str(), usb_port.GetUSBVID().c_str());
		map<std::string, GUID*>::const_iterator it = this->m_USBGUIDMap.find(usb_port.GetUSBGUIDType().c_str());
		if ( it != this->m_USBGUIDMap.end()) {
			isFind = true;
			memcpy(p_guid, it->second, sizeof(GUID));
			//LOG("FlashToolUSBTable::QueryUSBGUIDByPID() succeed.");
		} else {
			LOG("ERROR: FlashToolUSBTable::QueryUSBGUIDByPID(): USB name (%s), guid-type(%s) failed!", 
				usb_port.GetUSBName().c_str(), usb_port.GetUSBGUIDType().c_str());
		}
	}
	return isFind;
}

FlashToolUSBTable& GetFlashToolUSBTable()
{
	std::string usb_xml = FileUtils::GetAppDirectory() + "\\" + WStr2Str(FlashToolUSBTable::USB_SETTING_FILE);
	assert(FileUtils::IsFileExist(usb_xml) && "usb_setting.xml does not exist under tool folder!");

	static FlashToolUSBTable usbTable(FlashToolUSBTable::USB_SETTING_FILE);
	return usbTable;
}
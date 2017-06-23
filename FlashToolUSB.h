#ifndef _FLASHTOOLUSB_H
#define _FLASHTOOLUSB_H

#include <map>
#include <string>
#include "XMLSerializable.h"
//Two headers below are for USB GUID
#include <objbase.h>
#include <initguid.h>

class FlashToolUSB : public XML::Serializable
{
public:
	FlashToolUSB(void);
	~FlashToolUSB(void);

    virtual void LoadXML(const XML::Node &node);
    virtual void SaveXML(XML::Node &node) const;

	std::string GetUSBPID() const {
		return m_USBPID;
	}
	std::string GetUSBVID() const {
		return m_USBVID;
	}

	std::string GetUSBName() const {
		return m_USBName;
	}
	
	std::string GetUSBGUIDType() const {
		return m_USBGUIDType;
	}

public:
	static const std::string BOOTROM_VCOM;
	static const std::string PRELOADER_VCOM; //Single
	static const std::string COMPOSITE_PRELOADER_VCOM;//Composite
	static const std::string DA_HIGHSPEED_VCOM;
	static const std::string GADGET_VCOM;
	static const std::string COMPOSITE_DA_VCOM;
private:
	std::string m_USBName;
	std::string m_USBPID;
	std::string m_USBVID;
	std::string m_USBGUIDType;

	static const std::wstring USB_NAME;
	static const std::wstring USB_PID;
	static const std::wstring USB_VID;
	static const std::wstring USB_GUID_TYPE;
	static const std::wstring USB_PORT_GUID_CLASS;
	static const std::wstring USB_PORT_GUID_INTERFACE;

	friend class FlashToolUSBTable;
};

class FlashToolUSBTable
{
public:
	explicit FlashToolUSBTable(const std::wstring& fileName);
	bool QueryUSBItemByName(const std::string& name, FlashToolUSB& usb_port);
	bool QueryUSBGUIDByPID(const std::string& pid, GUID* p_guid);
private:
	bool QueryUSBItemByPID(const std::string& pid, FlashToolUSB& usb_port);
	void InitializeUSBGUIDMAP(void);
	void LoadFile(const std::wstring& fileName);
	void Dump(void);
private:
	std::map<std::string, FlashToolUSB> m_FlashToolUSBMap;
	std::map<std::string, FlashToolUSB> m_FlashToolPIDUSBMap;
	std::map<std::string, GUID*> m_USBGUIDMap;

	static const std::wstring USB_SETTING_FILE;
	static const std::wstring USB_ROOT_NODE;

	friend FlashToolUSBTable& GetFlashToolUSBTable();
};

FlashToolUSBTable& GetFlashToolUSBTable();

#endif//_FLASHTOOLUSB_H
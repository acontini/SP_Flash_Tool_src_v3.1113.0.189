#include <time.h>
#include <stdlib.h>

#include "SearchUSB.h"
#include "brom.h"
#include "eboot\interface.h"
#include "Logger.h"
#include "FlashToolUSB.h"

#ifdef __BORLANDC__
#pragma warn -8004
#endif

using std::string;
using std::vector;

const unsigned int SearchUSB::kDefaultTimeoutSecond(30);

SearchUSB::SearchUSB(
					 int* const stop_flag,
					 const bool is_with_timeout,
					 const unsigned int timeout) :
        kStopFlag_(stop_flag),
		is_with_timeout_(is_with_timeout),
		timeout_count_(timeout)
{
}

SearchUSB::~SearchUSB(void)
{
}

void SearchUSB::AddUSBPort(const std::string &pid, const std::string &vid)
{
	USBPidVidPair usb_pid_vid_pair;
	usb_pid_vid_pair.first = pid;
	usb_pid_vid_pair.second = vid;
	this->usb_port_pool_.push_back(usb_pid_vid_pair);
}

void SearchUSB::Dump(void)
{
	LOGD("USB ports count(%d).", this->usb_port_pool_.size());
	std::vector<USBPidVidPair>::iterator it;
	for (it = this->usb_port_pool_.begin(); it !=this->usb_port_pool_.end(); it++) {
		LOGD("USB port pid(%s), vid(%s).", it->first.c_str(), it->second.c_str());
	}		
}

bool SearchUSB::ExecuteToSearch(void) 
{
    bool is_found = false;
	time_t start = 0;
	time_t finish = 0;
	do {
		if (* (this->kStopFlag_) == BOOT_STOP) {
			LOGD("User press stop button.");
			break;
		} else {
			if (this->is_with_timeout_) {
				 //Get start time
				time(&start);
				if (SearchUSBPortPool()) {
					is_found = true;
					break;
				}
				//Get current time
				time(&finish);
				if ( difftime(finish, start) > this->timeout_count_ ) {
					LOGW("Timeout(%u s) for searching USB port!", this->timeout_count_);
					break;
				}
			} else {
				if (SearchUSBPortPool()) {
					is_found = true;
					break;
				}
			}
		}
	}while(1);

	return is_found;
}

bool SearchUSB::SearchUSBPortPool(void)
{
	bool is_found = false;
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	unsigned long	device_number = 0;
	GUID usb_guid;
	char usb_port_name[_MAX_PATH] = "0";
	char usb_symblic_name[_MAX_PATH] = "0";
	unsigned long	port_name_real_length;
	unsigned long	symbolic_name_length;

	std::vector<USBPidVidPair>::iterator it;
	for ( it = this->usb_port_pool_.begin(); it != this->usb_port_pool_.end(); it++) {
		//Scan time interval among USB ports pool
		Sleep(300);		
		if (!usb_table.QueryUSBGUIDByPID(it->first, &usb_guid)) {
			LOGW("Query GUID by USB PID(%s) falied.", it->first.c_str());
			continue;
		}
		device_number = GetDeviceNumber(usb_guid, it->first.c_str(), it->second.c_str());
		if ( 0 == device_number) {
			//LOGW("Device, which is described by PID(%s), VID(%s), could not be found!", 
			//	it->first.c_str(), it->second.c_str());
			continue;
		} else {
			//TODO: Expend the method to support MDT
			if ( GetPresentDevicePath(usb_guid, it->first.c_str(), it->second.c_str(),
				0, //index
				usb_port_name, _MAX_PATH, &port_name_real_length, 
				usb_symblic_name, _MAX_PATH, &symbolic_name_length) ) {
					LOGD("USB with PID(%s) and VID(%s) is found.", it->first.c_str(), it->second.c_str());
					LOGD("USB port name(%s), and its symbolic name(%s).", usb_port_name, usb_symblic_name);
					this->usb_friendly_name_ = usb_port_name;
					this->usb_symbolic_name_ = usb_symblic_name;
					is_found = true;
					break;
			}
		}
	}
	return is_found;
}



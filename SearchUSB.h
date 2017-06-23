#ifndef SEARCH_USB_H
#define SEARCH_USB_H
#include <string>
#include <vector>

class SearchUSB
{
private:
	typedef std::pair<std::string, std::string> USBPidVidPair;
	
public:
	explicit SearchUSB(
		int* const stop_flag, 
		const bool is_with_timeout = true, 
		const unsigned int timeout = kDefaultTimeoutSecond);	
	~SearchUSB(void);
    //Getters
	std::string usb_symbolic_name(void) const {
		return usb_symbolic_name_;
	}
	std::string usb_friendly_name(void) const {
		return usb_friendly_name_;
	}
	void AddUSBPort(const std::string& pid, const std::string& vid);
	bool ExecuteToSearch(void);
	void Dump(void);
private:
	//Disable default constructor, dummy constrcutor
	SearchUSB(void) : kStopFlag_(0) {}
	bool SearchUSBPortPool(void);
private:
    static const unsigned int kDefaultTimeoutSecond;
private:
	int* const  kStopFlag_;
	bool is_with_timeout_;
	unsigned int timeout_count_;
	std::string usb_symbolic_name_;
	std::string usb_friendly_name_;
	std::vector<USBPidVidPair> usb_port_pool_;
};

#endif//SEARCH_USB_H
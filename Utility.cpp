/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/
#include <vcl.h>
#pragma hdrstop

#pragma warn -8004
#include <algorithm>
#include <utility>
#include <vector>
#include <initguid.h>
#include <cassert>
#include <exception>
#include <stdlib.h>
#include <stdio.h>

#include "Utility.h"
#include "com_enum.h"

#include "AndroidImageInfo.h"
#include "Logger.h"
#include "ImageMapRule.h"
#include "FlashToolUSB.h"
#include "SearchUSB.h"
#include "DownloadImageChecksum.h"

using std::string;
using std::wstring;

/**
 * Search for a newly created COM port.
 *
 * @param newCOMPortNum [out] a newly created COM port's number
 *
 * @return true for success or false for failure
 */
bool SearchNewlyCreatedCOMPort(unsigned short &newCOMPortNum)
{
    using std::mismatch;
    using std::pair;
    using std::vector;

    vector<unsigned short> oldCOMPortList(255);
    unsigned short oldNumCOMPorts = oldCOMPortList.size();

    // Retrieve the original COM port list
    if (ComPortEnumerate(&oldCOMPortList[0], &oldNumCOMPorts) != COM_ENUM_OK)
    {
        return false;
    }

    const DWORD startTick = ::GetTickCount();

    while (::GetTickCount() - startTick < 30000)
    {
        vector<unsigned short> newCOMPortList(255);
        unsigned short numCOMPorts = newCOMPortList.size();

        // Retrieve the new COM port list
        if (ComPortEnumerate(&newCOMPortList[0], &numCOMPorts) != COM_ENUM_OK)
        {
            return false;
        }

        // Compare the old list with the new list
        typedef vector<unsigned short>::iterator COMIter;

        pair<COMIter, COMIter> result = mismatch(newCOMPortList.begin(),
                                                 newCOMPortList.end(),
                                                 oldCOMPortList.begin());

        // Return the first new COM port's number, if any.
        if (result.first != newCOMPortList.end())
        {
            newCOMPortNum = *(result.first);
            return true;
        }
    }

    return false;
}


struct PROCESS_BASIC_INFORMATION
{
    PVOID Reserved1;
    void* PebBaseAddress;
    PVOID Reserved2[2];
    ULONG_PTR UniqueProcessId;
    ULONG_PTR ParentProcessId;
};

// GetParentProcessId will use the NtQueryInformationProcess function
// exported by NtDll to retrieve the parent process id for the current
// process and if for some reason it doesn't work, it returns 0
DWORD GetParentProcessId()
{
    // Much easier in ASM but C/C++ looks so much better
    typedef ULONG NTSTATUS;
    typedef NTSTATUS (WINAPI *pNtQueryInformationProcess)
                                (HANDLE ,UINT ,PVOID ,ULONG , PULONG);

    // Some locals
    PROCESS_BASIC_INFORMATION pbi;
    ZeroMemory(&pbi, sizeof(PROCESS_BASIC_INFORMATION));

    // Get NtQueryInformationProcess
    pNtQueryInformationProcess NtQIP = (pNtQueryInformationProcess)
                            GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")),
                                           "NtQueryInformationProcess");

    // Sanity check although there's no reason for it to have failed
    if (NtQIP == 0)
    {
        return 0;
    }

    // Now we can call NtQueryInformationProcess, the second
    // param 0 == ProcessBasicInformation
    NTSTATUS status = NtQIP(GetCurrentProcess(), 0, (void*) &pbi,
                            sizeof(PROCESS_BASIC_INFORMATION), 0);

    if (status != 0x00000000)
    {
        return 0;
    }
    else
    {
        return pbi.ParentProcessId;
    }
}

/**
 * Check whether scatter file contain invisable images info
 *
 * @param brom.dll Download handle
 *
 * @return true for scatter file contain invisable images info, need to tell Pre-Loader to do boundary check
 */
bool IsNewScatterFileWithBoundaryCheck(DL_HANDLE_T pDLHandle)
{
    const char* NEW_SCATTER_STR = "__NODL_";
    const unsigned char NEW_SCATTER_STR_COUNT = strlen(NEW_SCATTER_STR);
    if(NULL != pDLHandle)
    {
        DL_HANDLE_T &dl_handle = pDLHandle;
        unsigned short count = 0;
        if (!DL_GetCount(dl_handle, &count)) {
		    ROM_INFO rom[MAX_LOAD_SECTIONS];
		    if (!DL_Rom_GetInfoAll(dl_handle, rom, MAX_LOAD_SECTIONS)) {
			    for (int i = 0; i < count; i++) {
				    if( 0 == strncmp(rom[i].name, NEW_SCATTER_STR, NEW_SCATTER_STR_COUNT) ){
					    return true;
				    }
			    }
		    }
        }
    }
    return false;
}

void FillAndroidImageRegionInfo( DL_HANDLE_T pDLHandle, 
                                 REGION_INFO_E* region_info,
                                 unsigned int &region_num)
{
    assert(pDLHandle != NULL);
    unsigned short count = 0;
    if (!DL_GetCount(pDLHandle, &count)) {
	    ROM_INFO rom[MAX_LOAD_SECTIONS];
        ImageType imgType = UNKNOWN_TYPE;
	    ImageItem imgItem;
	    if (!DL_Rom_GetInfoAll(pDLHandle, rom, MAX_LOAD_SECTIONS)) {
		    for (int i = 0; i < count; i++) {
                strcpy(region_info[i].region_name, rom[i].name);
                region_info[i].start_addr = rom[i].begin_addr;
                imgType = GetImageMapRule().queryType(rom[i].name);
				imgItem = GetImageMapRule().getImageItem(imgType);
                region_info[i].region_type = DM_IMG_TYPE((imgItem.is_bootloader()) ? UNKNOWN_TYPE : imgType);
                region_info[i].is_visible = rom[i].item_is_visable;
                region_info[i].is_selected = rom[i].enable;
                
                //DUMP
                LOG("----------Image Region Info-----------");
                LOG("FillAndroidImageRegionInfo(): Image index: %d", i);
                LOG("FillAndroidImageRegionInfo(): Image name: %s", region_info[i].region_name);
                LOG("FillAndroidImageRegionInfo(): Image start address: 0x%x", DumpHex(region_info[i].start_addr));
                LOG("FillAndroidImageRegionInfo(): Image type: %d", region_info[i].region_type);
                LOG("FillAndroidImageRegionInfo(): Image is_visible: %d", region_info[i].is_visible);
                LOG("FillAndroidImageRegionInfo(): Image is_selected: %d", region_info[i].is_selected);
		    }
	    }
    }
    region_num = count;
}



/**
 * Scan USB VCOM which is newly enumerated with timeout
 *
 * @param time_out, com_num(output parameter), PID, VID of the USB VCOM
 *
 * @return true for scatter file contain invisable images info, need to tell Pre-Loader to do boundary check
 */
bool ScanNewCreateUSBVComPortWithTimeout( unsigned int time_out,
                           unsigned short& com_num,
                           const std::string& PID,
                           const std::string& VID)
{
    std::string s_com_str;
    std::string s_port_str;
    std::set<std::string> s_strSymbolicName;
    time_t   start, finish;

    //Get start time
    time(&start);

    do
    {
       if( GetNewCreatedUSBVComPort( s_com_str,
                                      s_port_str,
                                      s_strSymbolicName,
                                      PID.c_str(),
                                      VID.c_str())
                                          )
        {
            //find usb_com port via MS DDK
            com_num = GetUSBVCOMNumByPortName(s_port_str);
			LOG("ScanNewCreateUSBVComPortWithTimeout: Find usb port PID is %s, VID is %s, symblic name is %s, port num is %s.",
				PID.c_str(), VID.c_str(), s_com_str.c_str(), s_port_str.c_str());
            break;
        }
        //Get current time
        time( &finish );

        //wait if there still not found a new usb com port
        if(difftime( finish, start ) > time_out )
        {
            LOG("ScanUSBVOMWithTimeout: Find usb port PID is %s, VID is %s, time out %u s passed, search usb port error!",
                PID.c_str(), VID.c_str(), time_out);            
            return false;
        }
    }while(1);
    return true;
}

/**
 * Get USB VCOM which is newly enumerated
 *
 * @param USB COM symbolic name, port name, symbolic name key value, PID, VID
 *
 * @return true for scatter file contain invisable images info, need to tell Pre-Loader to do boundary check
 */
bool GetNewCreatedUSBVComPort( std::string &usb_com_port_str,
		                       std::string &usb_port_str,
                               std::set<std::string> &exist_com_port_str,
                               const std::string& PID,
                               const std::string& VID)
{
    std::set<std::string> current_exist_symbolic_str;
    std::set<std::string> current_exist_port_str;
    std::set<std::string> :: size_type current_com_port_size;
    std::set<std::string>::iterator it_current_com_port;
    std::vector<std::string>::iterator  it_last_result_str;
    string   result_port_str_test[10];

    //Get current exist com port
    ScanExistUSBVComPort(current_exist_symbolic_str, current_exist_port_str,
        PID, VID);
    it_current_com_port = current_exist_symbolic_str.begin();
    current_com_port_size = current_exist_symbolic_str.size();
    if ( 1 == current_com_port_size )
    {
        usb_com_port_str = *it_current_com_port;
        usb_port_str = *(current_exist_port_str.begin());
        LOGD("Double scan: Get only one USB VCom Port!");
        return true;
    }
    it_last_result_str = set_difference(current_exist_symbolic_str.begin(), current_exist_symbolic_str.end(),
                                   exist_com_port_str.begin(), exist_com_port_str.end(),
                                   result_port_str_test);

    if(result_port_str_test == it_last_result_str)
    {
        return false;
    }

    usb_com_port_str =  *result_port_str_test;
    LOGD("Double scan: Get a new USB VCom Port!");

    return true;
}

bool ScanUSBPortByCOMNum(int* stop_flag, unsigned char com_num, unsigned int time_out)
{
    time_t start, finish;
    HANDLE hCom(NULL);
    DWORD errCode(0);
    char com[50];
    bool ret = false;

     sprintf(com, "COM%d", com_num);
     LOGD("%s is used.", com);

    //Get start time
    time(&start);
    do
    {
        if (*(stop_flag) == BOOT_STOP)
	 {
		LOGD("User press stop button.");
		break;
	 } else {	
         //open usb port by com name.
         if(hCom != NULL) hCom = NULL;
		 
         hCom = CreateFile(com, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	  if(hCom == INVALID_HANDLE_VALUE)
	  {
               //get error code
               errCode = GetLastError();
               LOGD("Open %s fail, Err(%d)", com, errCode);
	  }
        else
	{
	     LOGD("Open usb port is ok, and check pid/vid");
	  
	     //TODO: check if the pid vid is ok.
	     /////////////////////////////
	     /////////////////////////////
      
	    //Close COM port
	    if(CloseHandle(hCom))
	    {
              LOGD("Get USB Port (%s) success.", com);
		 ret = true;
		 break;
	    }
	    else
	    {
              errCode = GetLastError();
              LOGE("Close Handle fail. Err(%d)", errCode);

		 hCom = NULL;
	    }
	  }
		
        time( &finish );

        //wait if there still not found a new usb com port
        if(difftime( finish, start ) > time_out )
        {            
	      if(hCom == INVALID_HANDLE_VALUE)
	      {
               //get error code
               errCode = GetLastError();
	         LOGE("Open %s fail, Err(%d)", com, errCode);

		  //reset hCom;
		  hCom == NULL;
		}
		
	      LOGD("Find usb port(COM %u), time out %u s passed, search usb port error!", com_num, time_out);
	      break;
        }
       }
    }while(1);

     return ret;
}

void ScanExistUSBVComPort( std::set<std::string>  &exist_symbollic_str,
                           std::set<std::string> &exist_port_str,
                           const std::string& PID,
                           const std::string& VID)
{
        const int SYMBOLIC_NAME_BUFSIZE = 512;
        const int PORT_NAME_BUFSIZE = 128;
        unsigned long	device_number;
        char			symbolic_name[SYMBOLIC_NAME_BUFSIZE];
        unsigned long	symbolic_name_length;
        char			port_name[PORT_NAME_BUFSIZE];
        unsigned long	port_name_real_length;
        GUID usb_guid;

		FlashToolUSBTable usb_table = GetFlashToolUSBTable();
		if (!usb_table.QueryUSBGUIDByPID(PID, (GUID*)&usb_guid)) {
			LOG("ERROR:ScanExistUSBVComPort(): PID(%s), VID(%s) failed!", PID.c_str(), VID.c_str());
			return;
		}
        
        device_number = GetDeviceNumber(usb_guid, PID.c_str(), VID.c_str());
        LOGD("device_number(%d).", device_number);

        if( device_number == 0) {
            return;
        }

	    for(unsigned int i=0; i<device_number; i++)
	    {
 		    if(GetPresentDevicePath(usb_guid, PID.c_str(), VID.c_str(), i, \
                    port_name, PORT_NAME_BUFSIZE, (unsigned long *) &port_name_real_length, \
			        symbolic_name, SYMBOLIC_NAME_BUFSIZE, (unsigned long *) &symbolic_name_length \
						))  
            {
                //tmpPair = make_pair( port_name, symbolic_name);
                exist_symbollic_str.insert(symbolic_name);
                exist_port_str.insert(port_name);
				LOG("Double scan: Find and insert a USB VCom Port PID:%s, VID:%s, sybolic name: %s, port name:%s.",
					PID.c_str(), VID.c_str(), symbolic_name, port_name);
            }
            else
            {
                LOGD("Double scan:Get_Device_Path fail");
            }
	    }
}

/**
 * Obtain USB VCOM Number by Port Name in Registry
 *
 * @param USB VCOM Port Name
 *
 * @return USB VCOM Number, if 0 is returned indicates failure
 */
 unsigned char GetUSBVCOMNumByPortName(const std::string& usb_port)
{
    if(usb_port.empty() || (std::string::npos == usb_port.find("COM")))
    {
        return 0;
    }

    unsigned int com_num_start_addr = 0;
    unsigned int COM_NUM_MAX_LEN = 3;
    unsigned char usb_com_num = 0;

    do
    {
        com_num_start_addr = usb_port.find("COM", com_num_start_addr, COM_NUM_MAX_LEN) + COM_NUM_MAX_LEN;
        if( IsDigitChar(usb_port.at(com_num_start_addr)) ){
            break;        
        } else {
            continue;
        }
             
    } while(std::string::npos != com_num_start_addr);
    

    std::string::size_type com_num_len = 0;

    for(std::string::const_iterator it = usb_port.begin() + com_num_start_addr;
        it != usb_port.begin() + COM_NUM_MAX_LEN; ++it)
    {
        if( IsDigitChar(*it)){
            com_num_len += 1;        
        } else {
            break;
        }
    }
    
    std::string s_com_num = usb_port.substr(com_num_start_addr, com_num_len);

    usb_com_num = StringToNumber<unsigned short>(s_com_num);
    
    return usb_com_num;
}

/**
 * Check the character is located among '0' ~ '9'
 *
 * @param character
 *
 * @return true if the character is located among '0' ~ '9'
 */
 bool IsDigitChar(const char character)
{
    if( '0' <= character && 
        '9' >= character){
        return true;        
    } else {
        return false;
    }
}

void CheckSingleInstanceOfFlashTool(bool isConsole){
	HANDLE singleMutex = CreateMutex(NULL,FALSE, "Smart_Phone_Flash_Tool_MediaTek");
	if(GetLastError() == ERROR_ALREADY_EXISTS){
		CloseHandle(singleMutex);
		singleMutex = NULL;
		if(isConsole){
		    std::cout<<"Flash tool is already running, can't start another one."<<std::endl;
		}
		else{
			MessageBox(NULL,"Flash tool is already running, can't start another one.",
			    				"Warning", MB_OK + MB_ICONWARNING);
		}
		exit(-1);
	}
}

/**
 * Check if all images to be downloaded with images paths
 *
 * @param DL_HANDLE_T pDLHandle, std::string &errHint
 *
 * @return true if all images to be downloaded with images paths
 */
bool IsImgsToBeDLWithPath(DL_HANDLE_T pDLHandle, std::string &errHint)
{
    assert(NULL != pDLHandle);
    unsigned short rom_count;
    ROM_INFO rom_info[MAX_LOAD_SECTIONS]; 
    bool isImgsWithPaths = true;

    if (!DL_GetCount(pDLHandle, &rom_count)) {
        if( !DL_Rom_GetInfoAll(pDLHandle, rom_info, MAX_LOAD_SECTIONS) ) {
            for( int i = 0; i < rom_count; i++ ) {
                if ( (_TRUE == rom_info[i].item_is_visable) && 
                     (_TRUE == rom_info[i].enable) &&
                     (strlen(rom_info[i].filepath) < 1)) {
                    isImgsWithPaths = false;
					errHint += std::string("[Hint] ") + 
						std::string(rom_info[i].name) + 
                        "is checked, but without path!\n";
                }
            }
        } else {
            return false;
        }
    } else {
        return false;
    }

    return isImgsWithPaths;
}

/**
 * Check if user clicks Download button but without any images is checked to be downloaded
 *
 * @param DL_HANDLE_T pDLHandle
 *
 * @return true if user clicks Download button but without any images is checked to be downloaded
 */
bool IsNullImgsToBeDL(DL_HANDLE_T pDLHandle)
{
    assert(NULL != pDLHandle);
    unsigned short rom_count;
    ROM_INFO rom_info[MAX_LOAD_SECTIONS]; 
    bool isNullImgsToBeDL = true;

    if (!DL_GetCount(pDLHandle, &rom_count)) {
        if( !DL_Rom_GetInfoAll(pDLHandle, rom_info, MAX_LOAD_SECTIONS) ) {
            for( int i = 0; i < rom_count; i++ ) {
                if ( _TRUE == rom_info[i].item_is_visable ) {
                    isNullImgsToBeDL = (isNullImgsToBeDL && 
						(!(_TRUE == rom_info[i].enable)));
                }
            }
        } else {
            return true;
        }
    } else {
        return true;
    }

    return isNullImgsToBeDL;
}
/**
 * Return string to uppercase
 *
 * @param std::string or char*
 *
 * @return std::string with all characters are uppercase
 */
//template <typename T>
std::string ToUppercaseString(const std::string& str)
{
	std::string tmpstr(str);
	std::transform(tmpstr.begin(), tmpstr.end(), tmpstr.begin(), toupper);
	return tmpstr;
}

std::string ToLowercaseString(const std::string& str)
{
	std::string tmpstr(str);
	std::transform(tmpstr.begin(), tmpstr.end(), tmpstr.begin(), tolower);
	return tmpstr;
}


void GetRomInfoByName(DL_HANDLE_T pDLHandle,		 
		                   const std::string &rom_name,
		                   PartitionExistStatus &parti_status)
{
      assert(NULL != pDLHandle);

	unsigned short rom_count;
	ROM_INFO rom_info[MAX_LOAD_SECTIONS];

	if (!DL_GetCount(pDLHandle, &rom_count)) {
		if( !DL_Rom_GetInfoAll(pDLHandle, rom_info, MAX_LOAD_SECTIONS) ) {
			for( int i = 0; i < rom_count; i++ ) {
				if(rom_name == rom_info[i].name){
                                if(!rom_info[i].item_is_visable){
                                      parti_status = PARTITION_INVISIBLE;
                                }else if(!rom_info[i].enable){
                                      parti_status = PARTITION_DISABLE;
					  }else{
                                      parti_status = PARTITION_ENABLE;
					    }                   
								  
					return;
				}
			}
			parti_status = PARTITION_NOT_EXIST;
		}
	}
}


void GetRomRegionByName(DL_HANDLE_T pDLHandle,
		const std::string &rom_name,
		U64 &begin_addr,
		U64 &length)
{
	assert(NULL != pDLHandle);

	unsigned short rom_count;
	ROM_INFO rom_info[MAX_LOAD_SECTIONS];

	if (!DL_GetCount(pDLHandle, &rom_count)) {
		if( !DL_Rom_GetInfoAll(pDLHandle, rom_info, MAX_LOAD_SECTIONS) ) {
			for( int i = 0; i < rom_count - 1; i++ ) {
				if(rom_name == rom_info[i].name){
					begin_addr = rom_info[i].begin_addr;
					length = rom_info[i+1].begin_addr - begin_addr;
					break;
				}
			}
		}
	}

	LOG("GetRomRegionByName(): %s (0x%X, 0x%X)", rom_name.c_str(), begin_addr, length);
}

/**
 * Check if user clicks Format->Download button but without partial images is not checked to be downloaded
 *
 * @param DL_HANDLE_T pDLHandle
 *
 * @return true if user clicks Format->Download button with all images are checked to be downloaded
 */
bool IsAllImgsToBeDL(DL_HANDLE_T pDLHandle)
{
    assert(NULL != pDLHandle);
    unsigned short rom_count;
    ROM_INFO rom_info[MAX_LOAD_SECTIONS]; 
    bool isAllImgsToBeDL = true;

    if (!DL_GetCount(pDLHandle, &rom_count)) {
        if( !DL_Rom_GetInfoAll(pDLHandle, rom_info, MAX_LOAD_SECTIONS) ) {
            for( int i = 0; i < rom_count; i++ ) {
                if ( _TRUE == rom_info[i].item_is_visable &&
					_FALSE == rom_info[i].enable) {
					LOGW("rom(%s) is lost to download!", rom_info[i].name);
                    isAllImgsToBeDL = false;
					break;
                }
            }
        } else {
            return false;
        }
    } else {
        return false;
    }

    return isAllImgsToBeDL;

}

/**
 * Check if user clicks  Firmware->Upgrade button but with partial images is not checked to be downloaded
 *
 * @param DL_HANDLE_T pDLHandle
 *
 * @return true if user clicks Firmware->Upgrade button with all non-uncheckable images are checked to be downloaded
 */
bool IsNecessaryImgsToBeDL(DL_HANDLE_T pDLHandle)
{
     assert(NULL != pDLHandle);
     unsigned short rom_count;
     ROM_INFO rom_info[MAX_LOAD_SECTIONS];
     bool IsNecessaryImgsToBeDl= true;
     bool IsUnCheckable = false;
     int imageType = 0;

     if(!DL_GetCount(pDLHandle, &rom_count))
     {
        if(!DL_Rom_GetInfoAll(pDLHandle, rom_info, MAX_LOAD_SECTIONS))
	 {
              for(int i=0; i<rom_count; i++)
              {
                   imageType = GetImageMapRule().queryType(rom_info[i].name);
                   IsUnCheckable = GetImageMapRule().getImageItem(imageType).is_uncheckable();
		      LOGD("image name(%s): is uncheckable(%d)", rom_info[i].name, IsUnCheckable);
		     if(_TRUE == rom_info[i].item_is_visable && _FALSE == rom_info[i].enable && false == IsUnCheckable)
		     {
                         LOGW("rom(%s) is lost to download!", rom_info[i].name);
			    IsNecessaryImgsToBeDl = false;

			    break;
		     }
	       }
	 }
	 else
	 {
              return false;
	 }
    }
    else
    {
              return false;
    }

    return IsNecessaryImgsToBeDl;
     
}

/**
 * Check if Pre-Loader or DSP_BL to be downloaded
 *
 * @param DL_HANDLE_T pDLHandle
 *
 * @return true one of boot loader to be downloaded
 */
bool IsBLToBeDL(DL_HANDLE_T pDLHandle)
{
    assert(NULL != pDLHandle);
    unsigned short rom_count;
    ROM_INFO rom_info[MAX_LOAD_SECTIONS]; 
    bool isBLToBeDL = false;
    ImageType imgType = UNKNOWN_TYPE;
	ImageItem imgItem;
    if (!DL_GetCount(pDLHandle, &rom_count)) {
        if( !DL_Rom_GetInfoAll(pDLHandle, rom_info, MAX_LOAD_SECTIONS) ) {
            for( int i = 0; i < rom_count; i++ ) {
                imgType = GetImageMapRule().queryType(rom_info[i].name);
				imgItem = GetImageMapRule().getImageItem(imgType);
		        if (imgItem.is_bootloader() && imgItem.is_format_effective() )
		        {
		            isBLToBeDL = rom_info[i].enable;
					if (isBLToBeDL) {
						break;
					}
				} else {
					break;
                }
            }
        } else {
            return false;
        }
    } else {
        return false;
    }

    return isBLToBeDL;

}

bool IsSecurityToBeDL(SCERT_HANDLE_T  scert_handle)
{
    LOG("IsSecurityToBeDL: scert_handle(%x).", scert_handle);
    SCERT_INFO scert_info;
    if( S_DONE == SCERT_IsReady(scert_handle, &scert_info, _TRUE) ) {
        return true;
    } else {
	return false;
    }
}

bool IsCertToBeDL(AUTH_HANDLE_T  auth_handle)
{
    LOG("IsCertToBeDL(): auth_handle(%x).", auth_handle);
    AUTH_INFO auth_info;
    if( S_DONE == AUTH_IsReady(auth_handle, &auth_info, _TRUE) ) {
        return true;
    } else {
	return false;
    }
}

bool IsFoundDLImageByScatterFile(DL_HANDLE_T p_dl_handle, 
				   ROM_INFO *p_rom_info,
				   const std::string &rom_name)
{
	assert((p_dl_handle != NULL) && "IsFindDLImage(): p_dl_handle is NULL!");
	assert((p_rom_info != NULL) && "IsFindDLImage(): p_rom_info is NULL!");
	assert((!rom_name.empty()) && "IsFindDLImage(): rom_name is empty!");

	LOG("IsFoundDLImageByScatterFile(): image to be found is (%s).", rom_name.c_str());
	int ret = 0;
	unsigned short count = 0;
	bool is_found = false;
	if (S_DONE == (ret = DL_GetCount(p_dl_handle, &count))) {
	    ROM_INFO rom[MAX_LOAD_SECTIONS];
		if (S_DONE == (ret = DL_Rom_GetInfoAll(p_dl_handle, rom, MAX_LOAD_SECTIONS))) {
			for (int i = 0; i < count; i++) {
				if( 0 == rom_name.compare(rom[i].name) ) {
					memcpy(p_rom_info, (rom + i), sizeof(ROM_INFO));
					LOG("IsFoundDLImageByScatterFile(): \
						Original rom info: rom name(%s), begin_addr(0x%x), \
						image info: image name(%s), begin_addr(0x%x).",
						rom[i].name, rom[i].begin_addr,
						p_rom_info->name, p_rom_info->begin_addr);
					is_found = true;
					break;   
				}
			}

			if(rom_name.compare("NVRAM") == std::string::npos)
		      	{
		      	     LOGD("Partition(%s) skip...", rom_name);
                        is_found = true;
			}
		} else {
			LOG("ERROR: IsFindDLImage(): DL_Rom_GetInfoAll() failed, brom error code(%d)!", ret);
			return is_found;
		}
	} else {
		LOG("ERROR: IsFindDLImage(): DL_GetCount() failed, brom error code(%d)!", ret); 
		return is_found;
	}

	return is_found;
}

std::string WStr2Str(const std::wstring& ws)
{
	std::string temp(ws.length(), '\0');
	std::copy(ws.begin(), ws.end(), temp.begin());
	return temp;
}

std::wstring Str2WStr(const std::string& s)
{
    const size_t newsize = (s.size())*(sizeof(wchar_t)/sizeof(char)) + 1;
    wchar_t* _dest = NULL;
	int ret = 0;
	std::wstring wcString;
	
	try {
		_dest = new wchar_t[newsize];
		wmemset(_dest, 0, newsize);
		ret = mbstowcs(_dest, s.c_str(), newsize);
		if ( -1 == ret) {
			 LOG("Str2WStr(): mbstowcs() failed!");
		}
		wcString = _dest;
	} catch (std::exception& ex)	{
		LOG("Str2WStr(): Standard exception: %s!", ex.what());
		if (NULL != _dest) {
			delete[] _dest;
		}		
	} 

	if (NULL != _dest) {
		delete[] _dest;
	}	

    return wcString;
}


bool VerifyDLImagesBuffer(DL_HANDLE_T dl_handle, std::string& error_msg, RomMemChecksumArg &chksum_arg, RomMemChecksumResult &chksum_res)
{
    assert(NULL != dl_handle);
    unsigned short rom_count = 0;
    ROM_INFO rom_info[MAX_LOAD_SECTIONS]; 
    bool is_checksum_pass = true;
	error_msg = "Images checksum unkown error!";
	std::ostringstream oss;
	 
    //Load golden checksum vaule	
	DownloadImageChecksum dl_imgs_checksum;
	dl_imgs_checksum.Dump();
	unsigned int chksum = 0;
       ImageType imgType = UNKNOWN_TYPE;
	ImageItem imgItem;
    if (!DL_GetCount(dl_handle, &rom_count)) {
        if( !DL_Rom_GetInfoAll(dl_handle, rom_info, MAX_LOAD_SECTIONS) ) {
            for( int i = 0; i < rom_count; i++ ) {
				imgType = GetImageMapRule().queryType(rom_info[i].name);
				imgItem = GetImageMapRule().getImageItem(imgType);
				if (imgItem.is_format_effective()) {
					chksum_arg.chksum= dl_imgs_checksum.QueryChecksumValueByImageName(rom_info[i].name);
					chksum_arg.index = i;
					LOG("%s(): Android index(%d), rom(%s), chksum(%u).", __FUNC__, i, rom_info[i].name, chksum_arg.chksum);
					if (S_DONE != DL_VerifyROMMemBuf(dl_handle, &chksum_arg, &chksum_res)) {
						oss << "Image " << rom_info[i].name << " checksum failed! "
							<<std::hex
							<< "Checksum reference value(0x" << chksum_arg.chksum << ") in the config ini file."<<std::endl
							<<std::dec
							<< "Please re-fill correct checksum values in Checksum.INI under tool folder and re-load scatter file again!"
							<<std::endl;
						error_msg = oss.str().c_str();
						LOG("ERROR: %s(): %s.", __FUNC__, oss.str().c_str());
						is_checksum_pass = false;
					}
				      /*	if (BOOT_STOP == *chksum_arg.p_stopflag) {
						is_checksum_pass = false;
						LOGE("User press stop button!");
						break;
					}    */
				}
			}
		}
	}

	return is_checksum_pass;
}

/**
 * Search USB port for downloading DA
 *
 * @param USB COM symbolic name, port name, symbolic name key value, PID, VID
 *
 * @return true for obtaining the usb port
 */
bool ScanUSBPort4DownloadDA(int* stop_flag,
							std::string& symbolic_name,
							std::string& friendly_name,
							const bool with_timeout, 
							const unsigned int timeout)
{
	bool is_found(false);

	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_bootrom;
	FlashToolUSB usb_preloader;
	FlashToolUSB usb_composite;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::BOOTROM_VCOM, usb_bootrom) ) {
		LOGE("QueryUSBItemByName(): (%s) failed!", 	FlashToolUSB::BOOTROM_VCOM.c_str());
		return is_found;
	}
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
		LOGE("QueryUSBItemByName(): (%s) failed!",	FlashToolUSB::PRELOADER_VCOM.c_str());
		return is_found;
	}
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::COMPOSITE_PRELOADER_VCOM, usb_composite)){

             LOGE("QueryUSBItemByName(): (%s) failed!", FlashToolUSB::COMPOSITE_PRELOADER_VCOM.c_str());
	      return is_found;
	}

	SearchUSB search_usb(stop_flag, with_timeout, timeout);
	search_usb.AddUSBPort(usb_bootrom.GetUSBPID(), usb_bootrom.GetUSBVID());
	search_usb.AddUSBPort(usb_preloader.GetUSBPID(), usb_preloader.GetUSBVID());
	search_usb.AddUSBPort(usb_composite.GetUSBPID(), usb_composite.GetUSBVID());
	search_usb.Dump();
	if(search_usb.ExecuteToSearch()) {
		friendly_name =  search_usb.usb_friendly_name();
		symbolic_name = search_usb.usb_symbolic_name();
		LOGD("USB is found, port name(%s), symbolic name(%s).", friendly_name.c_str(), symbolic_name.c_str());
		is_found = true;
	} else {
		LOGE("Search USB port for Download DA failed!");
	}

	return is_found;
}

/**
 * Switch Brom Full Speed to DA High Speed
 *
 * @param stop_flag, symbolic_name, friendly_name, FLASHTOOL_API_HANDLE_T, with_timeout, timeout
 *
 * @return true for switching to DA high speed
 */
bool Swith2DAHighSpeed(int* stop_flag,
					   std::string& symbolic_name,
					   std::string& friendly_name,
					   FLASHTOOL_API_HANDLE_T flashtool_handle, 
					   const bool with_timeout,
					   const unsigned int timeout)
{
    bool is_switch_hs(false);

	if (S_DONE != FlashTool_SetupUSBDL(&flashtool_handle, 1)) {
		LOGE("FlashTool_SetupUSBDL failed!");
		return is_switch_hs;
	}

	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_da_hs;
	FlashToolUSB usb_composite_da;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::DA_HIGHSPEED_VCOM, usb_da_hs) ) {
		LOGE("QueryUSBItemByName(): (%s) failed!", 	FlashToolUSB::DA_HIGHSPEED_VCOM.c_str());
		return is_switch_hs;
	}
       if ( !usb_table.QueryUSBItemByName(FlashToolUSB::COMPOSITE_DA_VCOM, usb_composite_da) ) {
		LOGE("QueryUSBItemByName(): (%s) failed!", 	FlashToolUSB::COMPOSITE_DA_VCOM.c_str());
		return is_switch_hs;
	}
 
	SearchUSB search_usb(stop_flag, with_timeout, timeout);
	search_usb.AddUSBPort(usb_da_hs.GetUSBPID(), usb_da_hs.GetUSBVID());
	search_usb.AddUSBPort(usb_composite_da.GetUSBPID(), usb_composite_da.GetUSBVID());
	search_usb.Dump();
	if(search_usb.ExecuteToSearch()) {
		friendly_name =  search_usb.usb_friendly_name();
		symbolic_name = search_usb.usb_symbolic_name();
		LOGD("USB is found, port name(%s), symbolic name(%s).", friendly_name.c_str(), symbolic_name.c_str());
		unsigned char com_port = GetUSBVCOMNumByPortName(friendly_name);
		//Update globle com port number
		COM_PORT = com_port;
		if (S_DONE != FlashTool_ChangeCOM(&flashtool_handle, com_port)) {
			LOGE("FlashTool_ChangeCOM() failed, port name(%s), symbolic name(%s).", friendly_name.c_str(), symbolic_name.c_str());
			return is_switch_hs;
		}
		is_switch_hs = true;
	} else {
		LOGE("Search USB port (%s) failed!", FlashToolUSB::DA_HIGHSPEED_VCOM.c_str());
		return is_switch_hs;
	}

	return is_switch_hs;
}

/**
 * Search port to download certification files.
 *
 * @param stop_flag, symbolic_name, friendly_name, FLASHTOOL_API_HANDLE_T, with_timeout, timeout
 *
 * @return true for obtain port.
 */
bool ScanUSBPort4DownloadCert(int* stop_flag,
							std::string& symbolic_name,
							std::string& friendly_name,
							const bool with_timeout, 
							const unsigned int timeout)
{
	bool is_found(false);

	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_bootrom;
	FlashToolUSB usb_preloader;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::BOOTROM_VCOM, usb_bootrom) ) {
		LOGE("QueryUSBItemByName(): (%s) failed!", 	FlashToolUSB::BOOTROM_VCOM.c_str());
		return is_found;
	}

	SearchUSB search_usb(stop_flag, with_timeout, timeout);
	search_usb.AddUSBPort(usb_bootrom.GetUSBPID(), usb_bootrom.GetUSBVID());
	search_usb.Dump();
	if(search_usb.ExecuteToSearch()) {
		friendly_name =  search_usb.usb_friendly_name();
		symbolic_name = search_usb.usb_symbolic_name();
		LOGD("USB is found, port name(%s), symbolic name(%s).", friendly_name.c_str(), symbolic_name.c_str());
		is_found = true;
	} else {
		LOGE("Search USB port (%s) failed!", FlashToolUSB::DA_HIGHSPEED_VCOM.c_str());
	}

	return is_found;
}

/**
*Check if it is a RSV ROM by the start address.*
**/
bool CheckIfRSVByAddr(U64 addr)
{
      int convert = (addr>>32) & 0xF;

      LOGD("Is RSV: %d.", convert);

      return (convert == 1) ? false:true;
}





#ifndef SPMETA_DLL_H
#define SPMETA_DLL_H


#include "brom.h"

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------//
//  META General                                                            //
//--------------------------------------------------------------------------//

//-----------------------------------------------------//
//  META General: data structure definition            //
//-----------------------------------------------------//
//namespace SPMETA_DLL
//{



#define STATUS_OK_DIRVER		1
#define STATUS_FAIL_DIRVER		0
#define STATUS_OK_DVB			1
#define STATUS_FAIL_DVB			0



#define STATUS_OK_FT			0
#define STATUS_FAIL_FT			1

typedef enum
{
	// META_DLL received a corrupted frame
	META_CNF_FRAME_ERROR = 0,

	// META_DLL received a confirm or indication from target,
	// but there is not corresponding call back function
	// installed for this confirm or indication.
	META_CNF_NO_CALLBACK = 1,

	// META_DLL received a corrupted primitive.
	META_CNF_PRIMITIVE_ERROR = 2,

	// META_DLL received a confirm or indication from
	// target, but there is no sufficient memory to process.
	META_CNF_NO_MEMORY = 3,

	// META_DLL retrieved a callback function, however,
	// the user input arguments are invalid.
	META_CNF_CALLBACK_PARAMETER_ERROR = 4,

	// META_DLL received a confirm with peer msg, however,
	// the peer msg is corrupted.
	META_CNF_PEER_MSG_ERROR = 5,

	// META_DLL received a confirm and successfully executed
	// the callback function.
	META_CNF_OK = 6,
	META_CNF_FT_STATUS_ERROR = 7
} META_CNF_ERR_CODE;

// The magic value to stop usb enumerate process 
#define ENUM_USB_STOP	9876

typedef enum
{
	META_SUCCESS = 0
	,META_FAILED
	,META_COMM_FAIL
	,META_NORESPONSE
	,META_BUFFER_LEN
	,META_FILE_BAD
	,META_LID_INVALID
	,META_INTERNAL_DB_ERR
	,META_NO_MEMORY
	,META_INVALID_ARGUMENTS
	,META_TIMEOUT
	,META_BUSY
	,META_INVALID_HANDLE
	,META_FAT_ERROR
	,META_FAT_DISK_FULL
	,META_FAT_ROOT_DIR_FULL
	,META_FAT_INVALID_FILENAME
	,META_FAT_INVALID_FILE_HANDLE
	,META_FAT_FILE_NOT_FOUND
	,META_FAT_DRIVE_NOT_FOUND
	,META_FAT_PATH_NOT_FOUND
	,META_FAT_ACCESS_DENIED
	,META_FAT_TOO_MANY_FILES
	,META_INCORRECT_TARGET_VER
	,META_COM_ERROR
	,META_BROM_CMD_ERROR
	,META_INCORRECT_BBCHIP_TYPE
	,META_BROM_ERROR
	,META_STOP_BOOTUP_PROCEDURE
	,META_CANCEL
	,META_CCT_NOT_IMPORT_PROFILE
	,META_CCT_INVALID_SENSOR_ID
	,META_CCT_TGT_NO_MEM_FOR_SINGLE_SHOT
	,META_CCT_TGT_NO_MEM_FOR_MULTI_SHOT
	,META_FUNC_NOT_IMPLEMENT_YET
	,META_CCT_NOT_IMPLEMENT_YET = META_FUNC_NOT_IMPLEMENT_YET
	,META_CCT_PREVIEW_ALREADY_STARTED
	,META_CCT_PREVIEW_ALREADY_STOPPED
	,META_CCT_READ_REG_NO_CNF
	,META_CCT_WRITE_REG_NO_CNF
	,META_CCT_TGT_ABORT_IMAGE_SENDING
	,META_CCT_READ_ONLY_REGISTER
	,META_CCT_LOAD_FROM_NVRAM_FAIL
	,META_CCT_SAVE_TO_NVRAM_FAIL
	,META_CCT_AE_INVALID_EC_LEVEL
	,META_CCT_AE_INVALID_EC_STEP
	,META_CCT_AE_ALREADY_ENABLED
	,META_CCT_AE_ALREADY_DISABLED
	,META_CCT_WB_INVALID_INDEX
	,META_CCT_NO_TGT_SENSOR_MATCH_IN_PROFILE
	,META_CCT_IMAGE_SENDING_FAME_NUM_ERROR
	,META_CCT_AE_IS_NOT_DISABLED
	,META_FAT_APP_QUOTA_FULL
	,META_IMEI_CD_ERROR
	,META_RFID_MISMATCH
	,META_NVRAM_DB_IS_NOT_LOADED_YET
	,META_CCT_ERR_CAPTURE_WIDTH_HEIGHT_TOO_SMALL
	,META_WAIT_FOR_TARGET_READY_TIMEOUT
	,META_CCT_ERR_SENSOR_ENG_SET_INVALID_VALUE
	,META_CCT_ERR_SENSOR_ENG_GROUP_NOT_EXIST
	,META_CCT_NO_TGT_ISP_MATCH_IN_PROFILE
	,META_CCT_TGT_ISP_SUPPORT_NOT_DEFINED
	,META_CCT_ERR_SENSOR_ENG_ITEM_NOT_EXIST
	,META_CCT_ERR_INVALID_COMPENSATION_MODE
	,META_CCT_ERR_USB_COM_NOT_READY
	,META_CCT_DEFECTPIXEL_CAL_UNDER_PROCESSING
	,META_CCT_ERR_DEFECTPIXEL_CAL_NO_MEM
	,META_CCT_ERR_TOO_MANY_DEFECT_PIXEL
	,META_CCT_ERR_CAPTURE_JPEG_FAIL
	,META_CCT_ERR_CAPTURE_JPEG_TIMEOUT
	,META_CCT_ERR_AF_FAIL
	,META_CCT_ERR_AF_TIMEOUT
	,META_CCT_ERR_AF_LENS_OFFSET_CAL_FAIL
	,META_CCT_ERR_PREVIEW_MUST_ENABLE
	,META_CCT_ERR_UNSUPPORT_CAPTURE_FORMAT
	,META_CCT_ERR_EXCEED_MAX_DEFECT_PIXEL
	,META_ERR_EXCEED_MAX_PEER_BUF_SIZE
	,META_CCT_ERR_INVALID_WIDTH_FACTOR
	,META_BROM_SECURITY_CHECK_FAIL
	,META_CCT_ERR_PREVIEW_MUST_DISABLE
	,META_MAUI_DB_INCONSISTENT
	,META_FAT_FILEPATH_TOO_LONG
	,META_FAT_RESTRICTED_FILEPATH
	,META_FAT_DIR_NOT_EXIST
	,META_FAT_DISK_SPACE_IS_NOT_ENOUGH
	,META_TDMB_ERR_BAND_NOT_EXIST
	,META_TDMB_ERR_FREQ_NOT_EXIST
	,META_TDMB_ERR_ENSM_NOT_EXIST
	,META_TDMB_ERR_SERV_NOT_EXIST
	,META_TDMB_ERR_SUB_CHAN_NOT_EXIST
	,META_TDMB_ERR_DEMOD_STATE
	,META_PERMISSION_DENIED
	,META_ENUMERATE_USB_FAIL
  ,META_STOP_ENUM_USB_PROCEDURE
   //----------------[TH] for CCT 6238--------------------------
  ,META_CCT_6238_AE_ALREADY_ENABLED
	,META_CCT_6238_AE_ALREADY_DISABLED
	,META_CCT_6238_AE_IS_NOT_DISABLED
  ,META_CCT_6238_ISP_FLASHLIGHT_LINEARITY_PRESTROBE_FAIL
  //-----------------------------------------------------------
	,META_LAST_RESULT
} META_RESULT;

typedef enum  {
	META_BAUD2400 = 0,
	META_BAUD4800,
	META_BAUD9600,
	META_BAUD14400,
	META_BAUD19200,
	META_BAUD57600,   // 5
	META_BAUD115200,
	META_BAUD230400,
	META_BAUD460800,
	META_BAUD921600,
	META_BAUD1500000,            //10
	META_BAUD_END = 0xFF
} META_COMM_BAUDRATE;

typedef enum {
	META_NO_FLOWCTRL = 0,	// no flow control
	META_SW_FLOWCTRL,		// enable S/W flow control
	META_FLOWCTRL_END
} META_FLOWCTRL;

typedef struct {
	char	BB_CHIP[64];	// BaseBand chip version
	char	ECO_VER[4];		// ECO version
	char	SW_TIME[64];
	char	DSP_FW[64];		// DSP firmware version
	char	DSP_PATCH[64];	// DSP patch version
	char	SW_VER[64];		// S/W version
	char	HW_VER[64];		// H/W board version
	char	MELODY_VER[64];	// Melody version
	unsigned char status;
} VerInfo_Cnf;

typedef struct {
	char	BB_CHIP[64];	// BaseBand chip version
	char	ECO_VER[4];		// ECO version
	char	SW_TIME[64];
	char	DSP_FW[64];		// DSP firmware version
	char	DSP_PATCH[64];	// DSP patch version
	char	SW_VER[64];		// S/W version
	char	HW_VER[64];		// H/W board version
	char	MELODY_VER[64];	// Melody version
	char	BUILD_DISP_ID[64];  //build version
	unsigned char status;
} VerInfo_V2_Cnf;

typedef struct
{
	unsigned short      com_port_list[255];   
	unsigned short      com_port_num;
	unsigned int		ms_connect_timeout; // [META] META enumerate port timeout value 

}META_Enumerate_USB_Req;

typedef struct {
	int 				com_port;
	META_COMM_BAUDRATE  baudrate[12];		// [META] META stage baudrate polling array, it must end with META_BAUD_END. 
	META_FLOWCTRL  		flowctrl;			// [META] META stage uart flow control type. 
	BOOT_META_ARG		boot_meta_arg;		// [BootROM] please refer to brom.h 
	unsigned int		ms_connect_timeout; // [META] META stage sync timeout value (after BootROM negotiation pass) 
} META_Connect_Req;

typedef struct {
	META_COMM_BAUDRATE  final_baudrate;					// [META] Detected META stage baudrate.     
	unsigned int		meta_ver_required_by_target;	// [META] Target required META_DLL version. 
	BOOT_RESULT			boot_result;					// [BootROM] boot-up result. 
	STATUS_E			boot_meta_ret;					// [BROM_DLL] The return code of Boot_META function. 
} META_Connect_Report;

typedef struct {
	int 				com_port;
	BOOT_META_ARG		boot_meta_arg;		// [BootROM] please refer to brom.h 
	unsigned int		ms_connect_timeout; // [META] META stage sync timeout value (after BootROM negotiation pass) 
} META_ConnectByUSB_Req;

typedef struct {
	unsigned int		meta_ver_required_by_target;	// [META] Target required META_DLL version. 
	BOOT_RESULT			boot_result;					// [BootROM] boot-up result. 
	STATUS_E			boot_meta_ret;					// [BROM_DLL] The return code of Boot_META function. 
} META_ConnectByUSB_Report;

typedef struct {
	int 				com_port;
	META_COMM_BAUDRATE  baudrate[11];		// [META] META stage baudrate polling array, it must end with META_BAUD_END. 
	META_FLOWCTRL  		flowctrl;			// [META] META stage uart flow control type. 
	unsigned int		ms_connect_timeout; // [META] META stage sync timeout value (after BootROM negotiation pass) 
}WM_META_ConnectInMETA_Req;


typedef struct {
	META_COMM_BAUDRATE  final_baudrate;					// [META] Detected META stage baudrate. 
	unsigned int		meta_ver_required_by_target;	// [META] Target required META_DLL version. 
}WM_META_ConnectInMETA_Report;



//-----------------------------------------------------//
//  META General: callback function definition         //
//-----------------------------------------------------//
typedef void (__stdcall *META_Error_CallBack)(const META_CNF_ERR_CODE  mr);
typedef void (__stdcall *META_SysTrace_CallBack)(const char *sys_trace);
typedef void (__stdcall *META_GET_VERSION_INFO_CNF)(const VerInfo_Cnf  *cnf, const short token, void *usrData);
typedef void (__stdcall *META_GET_VERSION_INFO_V2_CNF)(const VerInfo_V2_Cnf  *cnf_v2, const short token, void *usrData);

//-----------------------------------------------------//
//  META for CTI                                       //
//-----------------------------------------------------//
typedef enum {
	 CTI_OK = 0
	,CTI_MISSING_HEADER
	,CTI_CORRUPTED_FAME
	,CTI_EXCEED_LEN
} CTI_RET_ENUM;

typedef void (__stdcall *META_CTI_CallBack)(CTI_RET_ENUM  ret, const int size, const unsigned char *data, void *param);
META_RESULT  __stdcall SP_META_CTI_SendPacketCmd(const unsigned char *pPayLoadBuffer, int nPayloadLength);
META_RESULT  __stdcall SP_META_CTI_SendPacketCmd_r(const int meta_handle, const unsigned char *pPayLoadBuffer, int nPayloadLength);
META_RESULT  __stdcall SP_META_CTI_SetPacketCallback(META_CTI_CallBack  pCBFunc, void* param);
META_RESULT  __stdcall SP_META_CTI_SetPacketCallback_r(const int meta_handle, META_CTI_CallBack  pCBFunc, void* param);

//-----------------------------------------------------//
//  Switch TST message format                          //
//-----------------------------------------------------//
typedef enum {
	META_TST_MSG_2G = 0,
	META_TST_MSG_3G
} META_TST_MSG_FORMAT;

META_RESULT  __stdcall SP_META_SetTstMsgFormat(META_TST_MSG_FORMAT  msg_fmt);
META_RESULT  __stdcall SP_META_SetTstMsgFormat_r(const int meta_handle, META_TST_MSG_FORMAT  msg_fmt);

//-----------------------------------------------------//
//  META Debug: exported debug function definition     //
//-----------------------------------------------------//
META_RESULT  __stdcall SP_META_DebugOn();
META_RESULT  __stdcall SP_META_DebugOn_ex(const int meta_handle);
META_RESULT  __stdcall SP_META_DebugOff();
META_RESULT  __stdcall SP_META_DebugClear();
META_RESULT  __stdcall SP_META_DebugOnThePath(const char * path);

//-----------------------------------------------------//
//  META UnitTest                                      //
//-----------------------------------------------------//

/*
typedef struct {
	unsigned int	m_TestCaseID;
	const char *	m_pDescription;
} META_UT_TestCaseID_T;
*/

//void __stdcall META_QueryTestCase(META_UT_TestCaseID_T  **ppTestCase, unsigned int  *pTestCaseCount);
//void __stdcall META_UnitTest(const unsigned int  *p_TestCaseID_Array, unsigned int  TestCaseCount);

//-----------------------------------------------------//
//  META General: exported function definition         //
//-----------------------------------------------------//

#define     FT_MT_UNKNOWN  0
#define     FT_MT6305  1
#define     FT_MT6318  2 
#define     FT_MT6326  3
typedef struct {
	unsigned char	id;
} PMIC_ID;
typedef struct {
	unsigned int	pcl;
} RF_GetITC_PCL;
// General 

void  __stdcall SP_META_GetDLLVer(unsigned int *major_ver, unsigned int *minor_ver, unsigned int *build_num, unsigned int *patch_num);
void  __stdcall SP_META_GetDLLInfo(const char **pp_version, const char **pp_release_type, const char **pp_build_date, const char **pp_load_path);
void  __stdcall SP_META_Cancel(const short token);
void  __stdcall SP_META_Cancel_r(const int meta_handle, const short token);
void  __stdcall SP_META_CancelAllBlockingCall(void);
void  __stdcall SP_META_CancelAllBlockingCall_r(const int meta_handle);
META_RESULT  __stdcall SP_META_QueryIfFunctionSupportedByTarget(unsigned int ms_timeout, const char *query_func_name);
META_RESULT  __stdcall SP_META_QueryIfFunctionSupportedByTarget_r(const int meta_handle, unsigned int ms_timeout, const char *query_func_name);
META_RESULT  __stdcall SP_META_QueryIfTargetSupportISP(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfTargetSupportISP_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfTargetSupportAcoustic16level(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfTargetSupportAcoustic16level_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfTargetSupportAudioParam45Tap(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfTargetSupportAudioParam45Tap_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfTargetIsLowCostSingleBankFlash(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfTargetIsLowCostSingleBankFlash_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryPMICID(unsigned int  ms_timeout, PMIC_ID  *cnf);
META_RESULT  __stdcall SP_META_QueryPMICID_r(const int meta_handle, unsigned int  ms_timeout, PMIC_ID  *cnf);
META_RESULT  __stdcall SP_META_BTPowerOn(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_BTPowerOn_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfTargetSupportWifiALC(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfTargetSupportWifiALC_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryITC_PCL(unsigned int  ms_timeout, RF_GetITC_PCL  *cnf);
META_RESULT  __stdcall SP_META_QueryITC_PCL_r(const int meta_handle, unsigned int  ms_timeout, RF_GetITC_PCL  *cnf);
META_RESULT  __stdcall SP_META_QueryIfTargetSupportDRC(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfTargetSupportDRC_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfBTPowerOn(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_QueryIfBTPowerOn_r(const int meta_handle, unsigned int ms_timeout);

//-----------------------------------------------------//
//  UTILITY--ENABLE WATCHDOG				           //
//-----------------------------------------------------//
#define GPIO_DEV_LED_MAINLCD 0
//#define GPIO_DEV_LED_SUBLCD 1

typedef struct  {
	unsigned char			lcd_light_level;
}LCDLevel_REQ;

typedef struct  {
	int			status;
}LCDLevel_CNF;

typedef struct  {
	BOOL				onoff;
	char					DIV;
	char					DUTY;
}KeypadBK_REQ;

typedef struct  {
	int			status;
}KeypadBK_CNF;

typedef struct{
    UINT LedNum;
    INT  OFFON;
}NLED_REQ;

typedef struct{
    BOOL ret;
}NLED_CNF;

typedef struct{
   int 	Notused;
}SetCleanBootFlag_REQ;

typedef struct{
   int 	drv_status;
}SetCleanBootFlag_CNF;



typedef struct  {
	unsigned short		interval;
}WatchDog_REQ;

typedef struct  {
	unsigned short		rtc_sec;    
	unsigned short		rtc_min;    
	unsigned short		rtc_hour;   
	unsigned short		rtc_day;    
	unsigned short		rtc_mon;    
	unsigned short		rtc_wday;  
	unsigned short		rtc_year;  
	unsigned short		status;
}WatchDog_CNF;


//META_RESULT  __stdcall META_EnableWatchDogTimer(unsigned int ms_timeout, FtWatchDog *req);
//META_RESULT  __stdcall META_EnableWatchDogTimer_r(const int meta_handle, unsigned int ms_timeout, FtWatchDog *req);


META_RESULT  __stdcall SP_META_SetLEDLightLevel(unsigned int ms_timeout, KeypadBK_REQ *req);
META_RESULT  __stdcall SP_META_SetLEDLightLevel_r(const int meta_handle, unsigned int ms_timeout, KeypadBK_REQ *req);
META_RESULT  __stdcall SP_META_SetLEDLightLevelforMT6573(unsigned int ms_timeout, NLED_REQ *req);
META_RESULT  __stdcall SP_META_SetLEDLightLevelforMT6573_r(const int meta_handle, unsigned int ms_timeout, NLED_REQ *req);
META_RESULT  __stdcall SP_META_SetVibratorOnOff(unsigned int ms_timeout, NLED_REQ *req);
META_RESULT  __stdcall SP_META_SetVibratorOnOff_r(const int meta_handle, unsigned int ms_timeout, NLED_REQ *req);
META_RESULT  __stdcall SP_META_SetSignalIndicatorOnOff(unsigned int ms_timeout, NLED_REQ *req);
META_RESULT  __stdcall SP_META_SetSignalIndicatorOnOff_r(const int meta_handle, unsigned int ms_timeout, NLED_REQ *req);
META_RESULT  __stdcall SP_META_QueryLocalTime(unsigned int  ms_timeout, WatchDog_CNF  *cnf);
META_RESULT  __stdcall SP_META_QueryLocalTime_r(const int meta_handle, unsigned int  ms_timeout, WatchDog_CNF  *cnf);
META_RESULT  __stdcall SP_META_SetMainSubLCDLightLevel(unsigned int ms_timeout, LCDLevel_REQ *req);
META_RESULT  __stdcall SP_META_SetMainSubLCDLightLevel_r(const int meta_handle, unsigned int ms_timeout, LCDLevel_REQ *req);
// timer-related APIs
META_RESULT  __stdcall SP_META_StartTimer();
META_RESULT  __stdcall SP_META_StartTimer_r(const int meta_handle);
META_RESULT  __stdcall SP_META_StopTimer();
META_RESULT  __stdcall SP_META_StopTimer_r(const int meta_handle);
META_RESULT  __stdcall SP_META_GetProcessTime(unsigned int  *pProcessTime, unsigned short *pNumAPIs);
META_RESULT  __stdcall SP_META_GetProcessTime_r(const int meta_handle, unsigned int *pProcessTime, unsigned short *pNumAPIs);
const char * __stdcall SP_META_GetErrorString(META_RESULT  ErrCode);
const char * __stdcall SP_META_BaudrateEnumToName(META_COMM_BAUDRATE  baudrate);
// Initialization 
META_RESULT  __stdcall SP_META_GetAvailableHandle(int *p_meta_handle);
META_RESULT  __stdcall SP_META_Init(const META_Error_CallBack  cb);
META_RESULT  __stdcall SP_META_Init_r(const int meta_handle, const META_Error_CallBack  cb);
META_RESULT  __stdcall SP_META_SetSysTraceCallback(const META_SysTrace_CallBack  sys_cb);
META_RESULT  __stdcall SP_META_SetSysTraceCallback_r(const int meta_handle, const META_SysTrace_CallBack  sys_cb);
void  __stdcall SP_META_Deinit(void);
void  __stdcall SP_META_Deinit_r(int *p_meta_handle);


// connect with target 
META_RESULT  __stdcall SP_META_ConnectWithTarget(const META_Connect_Req  *req, int *p_bootstop, META_Connect_Report  *p_report);
META_RESULT  __stdcall SP_META_ConnectWithTarget_r(const int meta_handle, const META_Connect_Req  *req, int *p_bootstop, META_Connect_Report  *p_report);
// disconnect and shutdown target
META_RESULT  __stdcall SP_META_DisconnectWithTarget(void);
META_RESULT  __stdcall SP_META_DisconnectWithTarget_r(const int meta_handle);

// connect with target when target already in meta mode 
META_RESULT  __stdcall SP_META_ConnectInMetaMode(const WM_META_ConnectInMETA_Req  *req, int *p_bootstop, WM_META_ConnectInMETA_Report  *p_report);
META_RESULT  __stdcall SP_META_ConnectInMetaMode_r(const int meta_handle, const WM_META_ConnectInMETA_Req  *req, int *p_bootstop, WM_META_ConnectInMETA_Report  *p_report);

// disconnect without shutdown target
META_RESULT  __stdcall SP_META_DisconnectInMetaMode(void);
META_RESULT  __stdcall SP_META_DisconnectInMetaMode_r(const int meta_handle);

// USB-related connect
META_RESULT  __stdcall SP_META_ConnectInMetaModeByUSB(const META_ConnectByUSB_Req  *req, int *p_bootstop, META_ConnectByUSB_Report  *p_report);
META_RESULT  __stdcall SP_META_ConnectInMetaModeByUSB_r(const int meta_handle, const META_ConnectByUSB_Req  *req, int *p_bootstop, META_ConnectByUSB_Report  *p_report);

META_RESULT  __stdcall SP_META_ConnectWithTargetByUSB(const META_ConnectByUSB_Req  *req, int *p_bootstop, META_ConnectByUSB_Report  *p_report);
META_RESULT  __stdcall SP_META_ConnectWithTargetByUSB_r(const int meta_handle, const META_ConnectByUSB_Req  *req, int *p_bootstop, META_ConnectByUSB_Report  *p_report);
META_RESULT  __stdcall SP_META_GetDynamicUSBComPort(unsigned int ms_scan_timeout, unsigned short *com_port, int *p_scanstop);
META_RESULT  __stdcall SP_META_GetDynamicUSBComPort_r(const int meta_handle, unsigned int ms_scan_timeout, unsigned short *com_port, int *p_scanstop);

// Get target S/W, H/W and Melody version
META_RESULT  __stdcall SP_META_GetTargetVerInfo(const META_GET_VERSION_INFO_CNF  cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_GetTargetVerInfo_r(const int meta_handle, const META_GET_VERSION_INFO_CNF  cb, short *token, void *usrData);

// Get target S/W, H/W, melody and build version
META_RESULT  __stdcall SP_META_GetTargetVerInfoV2(VerInfo_V2_Cnf  *cnf_v2, short *token, void *usrData);
META_RESULT  __stdcall SP_META_GetTargetVerInfoV2_r(const int meta_handle, VerInfo_V2_Cnf  *cnf_v2, short *token, void *usrData);


// Shutdown target 
META_RESULT  __stdcall SP_META_ShutDownTarget(void);
META_RESULT  __stdcall SP_META_ShutDownTarget_r(const int meta_handle);

META_RESULT  __stdcall SP_META_RebootTarget(unsigned int delay);
META_RESULT  __stdcall SP_META_RebootTarget_r(const int meta_handle,unsigned int delay);

// ***** Expired Functions -- BEGIN ***** //
// these functions are expired, we encourage you to use META_ConnectWithTarget and META_DisconnectWithTarget 
META_RESULT  __stdcall SP_META_COMM_Set_Baudrate(const META_COMM_BAUDRATE  baudrate);
META_RESULT  __stdcall SP_META_COMM_Set_Baudrate_r(const int meta_handle, const META_COMM_BAUDRATE  baudrate);
META_RESULT  __stdcall SP_META_COMM_Start(const int comm_port, const META_FLOWCTRL  flowctrl);
META_RESULT  __stdcall SP_META_COMM_Start_r(const int meta_handle, const int comm_port, const META_FLOWCTRL  flowctrl);
META_RESULT  __stdcall SP_META_COMM_Stop(void);
META_RESULT  __stdcall SP_META_COMM_Stop_r(const int meta_handle);
META_RESULT  __stdcall SP_META_WaitForTargetReady(unsigned int ms_waiting_time, unsigned int request_count);
META_RESULT  __stdcall SP_META_WaitForTargetReady_r(const int meta_handle, unsigned int ms_waiting_time, unsigned int request_count);
META_RESULT  __stdcall SP_META_GetTargetRequiredMetaVer(unsigned int *p_meta_ver_required_by_target);
META_RESULT  __stdcall SP_META_GetTargetRequiredMetaVer_r(const int meta_handle, unsigned int *p_meta_ver_required_by_target);


META_RESULT  __stdcall SP_META_SetVersionInfo(VerInfo_Cnf *vinfo);

META_RESULT  __stdcall SP_META_BackupEFuseToFile( unsigned int ms_timeout, char * path);
META_RESULT  __stdcall SP_META_BackupEFuseToFile_r(const int meta_handle, unsigned int ms_timeout,char * path);


// ***** Expired Functions -- END ***** //

//--------------------------------------------------------------------------//
//  3G RF Testing                                                           //
//--------------------------------------------------------------------------//

//-----------------------------------------------------//
//  3G RF Testing: data structure definition           //
//-----------------------------------------------------//
typedef enum {
	URF_TEST_CMD_TXACCESS = 0
	,URF_TEST_CMD_STOP
	,URF_TEST_CMD_TX_DPCH
	,URF_TEST_CMD_RX_DPCH
	,URF_TEST_CMD_RSSI
	,URF_TEST_CMD_RSCP
	,URF_TEST_CMD_AFC
	,URF_TEST_CMD_TX_PAAPC  // for calling UL1D_RF_SetPaApcDac in FT task
	,URF_TEST_CMD_GET_RFID
	,URF_TEST_CMD_CONFIG_HWTPC
	,URF_TEST_CMD_GET_PWR_DT_STEP
	,URF_TEST_CMD_GET_PWR_DT_DAC
	,URF_TEST_CMD_GET_PWR_DT_DEFAULT_THR
	,URF_TEST_CMD_SET_IMMEDIATE_BSI
	,URF_TEST_CMD_GET_IMMEDIATE_BSI
	,URF_TEST_CMD_END
}URfTestCmdType;

typedef struct {
	unsigned short	uarfcn;			//kal_int16
	short			psc;			//kal_int16
	unsigned short	signature;	    //kal_uint16
	unsigned char	pa_mode;		//unsigned char
	char			init_power;		//kal_int8
	unsigned char   power_step;     //kal_uint8	
	unsigned char	max_retrans;	//kal_uint8
}URfTestCmdTxAccess;
typedef struct
{
	//unsigned short	dl_freq;
	unsigned short	ul_freq;
	short	psc;		/* 0~511. */
	unsigned int	sc_code;	/* Scrambling code #. 0 ~ 16777215 */
	unsigned char   power_ctrl_mode;
	unsigned char 	pa_mode;
	unsigned short 	idx;
	unsigned short	afc_dac;
	unsigned char	dpcch_pwr;
	unsigned char	dpdch_pwr;
	
	/* Below for UL1D_RF_Meta_SetTxInfo. */
	bool 	no_loop_ctrl;
	
	/* Below for setPaApcDac. */	
	unsigned char 	rf_band;
	unsigned char   vm1;
    unsigned char   vm2;
	unsigned short  dc2dc_dac;
    unsigned short  vbias_dac;
	bool            pwr_det;
	unsigned short 	apc_dac;		
} URfTestCmdTxDPCh;	//Anthony  target side is :UL1TSTCmdTxDPCh and  URfTestCmdTxDPCh

typedef struct
{
	unsigned short	dl_freq;
	short	psc;	/* 0~511. */
	unsigned char	ssc;	/* 0~15. */
	short	ovsf;	/* 0~sf-1. */
	unsigned short	afc_dac;
	
	/* Below for RF_SetBBRxParams. */
	bool 	hwAGC;
	unsigned char	mode;		/* 0: mode0, 1: mode1. */
	short	gain;		/* mode0. */
	unsigned char	LNAmode;	 /* mode1. 0: LNA high, 1: LNA mid, 2: LNA low. */
	unsigned short	pga;		/* mode1. */
} URfTestCmdRxDPCh;
#define MAX_FREQ_LIST 36
typedef struct
{
	unsigned char	num_freq;
	unsigned short	dl_freq[ MAX_FREQ_LIST ];
	unsigned char   temperature;
	
	/* Below for RF_SetBBRxParams. */
	bool 	hwAGC;
	unsigned char	mode;		/* 0: mode0, 1: mode1. */
	short	gain;		/* mode0. */
	unsigned char	LNAmode;	/* mode1. 0: LNA high, 1: LNA mid, 2: LNA low. */
	unsigned short	pga;		/* mode1. */
} URfTestCmdRSSI;

typedef struct
{
	bool	pscan_before_cell_search;	/* True if UL1TST needs power scan before cell search/RSCP. */
	unsigned short	dl_freq;	/* Specific dl_freq to do cell search. Valid if pscan_before_cell_search=F. */
	unsigned char	sample_num_per_cell;
	bool	read_sfn;	/* True if we need to do SFN measurement for the found cell. */
	
	/* Below for RF_SetBBRxParams. */
	bool 	hwAGC;
	unsigned char	mode;		/* 0: mode0, 1: mode1. */
	short	gain;		/* mode0. */
	unsigned char	LNAmode;	/* mode1. 0: LNA high, 1: LNA mid, 2: LNA low. */
	unsigned short	pga;		/* mode1. */
} URfTestCmdRSCP;

typedef struct
{
	//kal_bool	pscan_before_cell_search;	/* True if UL1TST needs power scan before cell search/RSCP. */
	short	        dl_freq;	/* Specific dl_freq to do cell search. Valid if pscan_before_cell_search=F. */
	//kal_uint8	sample_num_per_cell;
	//kal_bool	read_sfn;	/* True if we need to do SFN measurement for the found cell. */
	
	short           afc_dac;    //anthony 0514
	
	/* Below for RF_SetBBRxParams. */
	bool 	        hwAGC;
	unsigned char	mode;		/* 0: mode0, 1: mode1. */
	short	        gain;		/* mode0. */
	unsigned char	LNAmode;	/* mode1. 0: LNA high, 1: LNA mid, 2: LNA low. */
	unsigned short	pga;		/* mode1. */

} URfTestCmdAFC;

typedef struct
{
	char            m_cRfBand;    // only 0 ~ 5
    unsigned short  m_u2Idx;
	unsigned char   m_ucPaMode;
//	unsigned short m_u2PaDac;
	unsigned char    m_ucVm1;
	unsigned char    m_ucVm2;
	unsigned short   m_u2DC2DC_Dac;
	unsigned short   m_u2Vbias_Dac;
	unsigned short   m_u2ApcDac;

}UL1D_RF_TX_PA_APC_REQ_T;


typedef struct
{
   // structure of META_HWTPC_FRAME_INFO in target
   unsigned char tpc_step;
   unsigned char itp;
   unsigned char rpp;
   unsigned char fmt_idx;
   unsigned char dl_frame_type;
   unsigned short slot_mask;
   char   tpc_cmd[15];
   unsigned char  beta_c;
   unsigned char  beta_d;

}UL1D_RF_HWTPC_FRAME_INFO;

typedef struct
{
   unsigned char pc_algo;
   unsigned char tpc_used_frame;  // at most 8 so far
   short  p_ini;

   UL1D_RF_HWTPC_FRAME_INFO frame_info[8];
   
}UL1D_RF_HWTPC_CONFIG_REQ_T;


typedef struct
{
	unsigned char rf_band;

}UL1D_RF_GET_PWR_THR_REQ_T;

typedef struct
{
    unsigned int bsi_data;
}UL1D_RF_SET_BSI_DATA_REQ_T;

typedef struct
{
    unsigned int bsi_addr;
}UL1D_RF_GET_BSI_DATA_REQ_T;



typedef union {
	URfTestCmdTxAccess         txaccess;
	URfTestCmdTxDPCh	txdpch;	//Anthony
	URfTestCmdRxDPCh	rxdpch;
	URfTestCmdRSSI		rssi;
	URfTestCmdRSCP		rscp;
	URfTestCmdAFC       afc;
    UL1D_RF_TX_PA_APC_REQ_T    m_rTxPaApc;
	UL1D_RF_HWTPC_CONFIG_REQ_T  m_rHWTPC;
	UL1D_RF_GET_PWR_THR_REQ_T   m_rGetPwrThr;
}URfTestCmdParam;

typedef struct
{
	bool	ok;
	unsigned char	num_freq;
	short	dl_freq[ MAX_FREQ_LIST ];
	int	rssi[ MAX_FREQ_LIST ];	
} URfTestResultRSSI;



typedef struct
{	
	unsigned short	psc;		/* Primary scrambling code */
	int	tm;		/* Cell frame boundary offset to LST */
	short	off;		/* Cell frame number offset to LST */	
	bool	sttd; 		/* True for STTD used. */
	unsigned char	sample_num;
	unsigned char	rscp_sum;
	short freq_error;  // 20070514
} UL1TST_cpich_result_T;

#define MAX_NUM_MEAS_CELL 32
typedef struct
{
	bool		ok;
	unsigned char		num_cell;
	UL1TST_cpich_result_T	cpich_result[ MAX_NUM_MEAS_CELL ];	
} URfTestResultRSCP;

typedef struct
{
	bool	        ok;
	unsigned short	psc;		/* Primary scrambling code */
	int	            tm;		/* Cell frame boundary offset to LST */
	bool	        sttd; 		/* True for STTD used. */
	unsigned char	rscp_sum;
	short           freq_error;	//anthony 0514    

}URfTestResultAFC;

typedef struct
{
	bool	ok;
	unsigned int	ber;	/* Spec requirement=10^-3. We will count 10^5 frames(100 times spec requirement) for BER calculation. Only count for the only TRCh for DPDCh. */
} URfTestResultRxDPCh;

#define  UL1D_RF_ID_SONY_CXA3359    0x00000001
#define  UL1D_RF_ID_MT6159B         0x00000002
#define  UL1D_RF_ID_SMARTI3G        0x00000003
#define  UL1D_RF_ID_MT6159C         0x00000004


typedef struct
{
	unsigned int m_u4Rfid;
	
}URfTestResultRFID;

typedef struct
{
	unsigned char m_u1Result;

}URfTestResultPwrDtStep;

typedef struct
{
	unsigned short m_u2Result;

}URfTestResultPwrDtDac;

typedef struct
{

	unsigned char m_u1Result;

}URfTestResultPwrDtDefaultThr;


typedef union {
	bool	ok;   //kal_bool  // for only request
	URfTestResultRSSI	rssi;
	URfTestResultAFC    afc;
  URfTestResultRSCP	rscp;
  URfTestResultRxDPCh	rx_dpch;
	URfTestResultRFID   rfid;
	URfTestResultPwrDtStep        pwr_dt_step;
	URfTestResultPwrDtDac         pwr_dt_dac;
  URfTestResultPwrDtDefaultThr  pwr_dt_default_thr;
  unsigned int                  bsi_data;
}URfTestResultParam;


//-----------------------------------------------------//
//  3G RF Testing: function definition				   //
//-----------------------------------------------------//

META_RESULT  __stdcall SP_META_3Grf_ContinuousRX(unsigned int  ms_timeout, URfTestCmdRSSI *req);
META_RESULT  __stdcall SP_META_3Grf_ContinuousRX_r(const int meta_handle, unsigned int  ms_timeout, URfTestCmdRSSI *req);

META_RESULT  __stdcall SP_META_3Grf_TxAccess(unsigned int  ms_timeout, URfTestCmdTxAccess *req, URfTestResultParam *cnf);
META_RESULT  __stdcall SP_META_3Grf_TxAccess_r(const int meta_handle, unsigned int  ms_timeout, URfTestCmdTxAccess *req, URfTestResultParam *cnf);
META_RESULT  __stdcall SP_META_3Grf_TestStop(unsigned int  ms_timeout, URfTestResultParam *cnf);
META_RESULT  __stdcall SP_META_3Grf_TestStop_r(const int meta_handle, unsigned int  ms_timeout, URfTestResultParam *cnf);
META_RESULT  __stdcall SP_META_3Grf_TxDpch(unsigned int  ms_timeout, URfTestCmdTxDPCh *req, URfTestResultParam *cnf);
META_RESULT  __stdcall SP_META_3Grf_TxDpch_r(const int meta_handle, unsigned int  ms_timeout, URfTestCmdTxDPCh *req, URfTestResultParam *cnf);
META_RESULT  __stdcall SP_META_3Grf_RxDpch(unsigned int  ms_timeout, URfTestCmdRxDPCh *req, URfTestResultRxDPCh *cnf);
META_RESULT  __stdcall SP_META_3Grf_RxDpch_r(const int meta_handle, unsigned int  ms_timeout, URfTestCmdRxDPCh *req, URfTestResultRxDPCh *cnf);
META_RESULT  __stdcall SP_META_3Grf_Rssi(unsigned int  ms_timeout, URfTestCmdRSSI *req, URfTestResultRSSI *cnf);
META_RESULT  __stdcall SP_META_3Grf_Rssi_r(const int meta_handle, unsigned int  ms_timeout, URfTestCmdRSSI *req, URfTestResultRSSI *cnf);
META_RESULT  __stdcall SP_META_3Grf_Rscp(unsigned int  ms_timeout, URfTestCmdRSCP *req, URfTestResultRSCP *cnf);
META_RESULT  __stdcall SP_META_3Grf_Rscp_r(const int meta_handle, unsigned int  ms_timeout, URfTestCmdRSCP *req, URfTestResultRSCP *cnf);

META_RESULT  __stdcall SP_META_3Grf_Set_Tx_PaApc(unsigned int  ms_timeout, UL1D_RF_TX_PA_APC_REQ_T *req);
META_RESULT  __stdcall SP_META_3Grf_Set_Tx_PaApc_r(const int meta_handle, unsigned int  ms_timeout, UL1D_RF_TX_PA_APC_REQ_T *req);

META_RESULT  __stdcall SP_META_3Grf_AFC(unsigned int  ms_timeout, URfTestCmdAFC *req, URfTestResultAFC *cnf);
META_RESULT  __stdcall SP_META_3Grf_AFC_r(const int meta_handle, unsigned int  ms_timeout, URfTestCmdAFC *req, URfTestResultAFC *cnf);

META_RESULT  __stdcall SP_META_3Grf_GetRFID(unsigned int  ms_timeout, URfTestResultRFID *cnf);
META_RESULT  __stdcall SP_META_3Grf_GetRFID_r(const int meta_handle, unsigned int  ms_timeout, URfTestResultRFID *cnf);

META_RESULT  __stdcall SP_META_3Grf_ConfigHWTPC(unsigned int  ms_timeout, UL1D_RF_HWTPC_CONFIG_REQ_T *req);
META_RESULT  __stdcall SP_META_3Grf_ConfigHWTPC_r(const int meta_handle, unsigned int  ms_timeout, UL1D_RF_HWTPC_CONFIG_REQ_T *req);


META_RESULT  __stdcall SP_META_3Grf_GetPwrDtStep(unsigned int  ms_timeout, URfTestResultPwrDtStep *cnf);
META_RESULT  __stdcall SP_META_3Grf_GetPwrDtStep_r(const int meta_handle, unsigned int  ms_timeout, URfTestResultPwrDtStep *cnf);
META_RESULT  __stdcall SP_META_3Grf_GetPwrDtDac(unsigned int  ms_timeout, URfTestResultPwrDtDac *cnf);
META_RESULT  __stdcall SP_META_3Grf_GetPwrDtDac_r(const int meta_handle, unsigned int  ms_timeout, URfTestResultPwrDtDac *cnf);
META_RESULT  __stdcall SP_META_3Grf_GetPwrDtDefaultThr(unsigned int  ms_timeout, UL1D_RF_GET_PWR_THR_REQ_T *req, URfTestResultPwrDtDefaultThr *cnf);
META_RESULT  __stdcall SP_META_3Grf_GetPwrDtDefaultThr_r(const int meta_handle, unsigned int  ms_timeout, UL1D_RF_GET_PWR_THR_REQ_T *req, URfTestResultPwrDtDefaultThr *cnf);


META_RESULT  __stdcall SP_META_3Grf_SetImmediateBSI(unsigned int  ms_timeout, const UL1D_RF_SET_BSI_DATA_REQ_T *req);
META_RESULT  __stdcall SP_META_3Grf_SetImmediateBSI_r(const int meta_handle, unsigned int  ms_timeout, const UL1D_RF_SET_BSI_DATA_REQ_T *req);
META_RESULT  __stdcall SP_META_3Grf_GetImmediateBSI(unsigned int  ms_timeout, const UL1D_RF_GET_BSI_DATA_REQ_T *req, unsigned int *p_bsi_data);
META_RESULT  __stdcall SP_META_3Grf_GetImmediateBSI_r(const int meta_handle, unsigned int  ms_timeout, const UL1D_RF_GET_BSI_DATA_REQ_T *req, unsigned int *p_bsi_data);

//--------------------------------------------------------------------------//
//  RF Testing                                                              //
//--------------------------------------------------------------------------//

//-----------------------------------------------------//
//  RF Testing: data structure definition              //
//-----------------------------------------------------//
typedef short	ARFCN;
typedef short	Gain;
typedef char	BSIC;
typedef short	Power;
typedef unsigned char	TimingAdvance;

// RF ID 
#define  RF_ID_UNKNOWN     0x00000000
#define  RF_ID_BRIGHT2     0x00000001
#define  RF_ID_BRIGHT4     0x00000002
#define  RF_ID_AERO        0x00000004
#define  RF_ID_AERO1PLUS   0x00000008
#define  RF_ID_POLARIS1    0x00000010
#define  RF_ID_POLARIS2    0x00000020
#define  RF_ID_SKY74045    0x00000040
#define  RF_ID_BRIGHT5P    0x00000080
#define  RF_ID_MT6116      0x00000100
#define  RF_ID_MT6119      0x00000200
#define  RF_ID_MT6119C     0x00000400
#define  RF_ID_MT6129A     0x00000800
#define  RF_ID_MT6129B     0x00001000
#define  RF_ID_MT6129C     0x00002000
#define  RF_ID_MT6129D     0x00004000
#define  RF_ID_MT6139B     0x00008000
#define  RF_ID_MT6139C     0x00010000
#define  RF_ID_MT6140A     0x00020000
#define  RF_ID_SKY74117    0x00040000
#define  RF_ID_SKY74400    0x00080000
#define  RF_ID_AERO2       0x00100000
#define  RF_ID_MT6140B     0x00200000
#define  RF_ID_ALICEG2S    0x00400000
#define  RF_ID_MT6139E     0x00800000
#define  RF_ID_SKY74137    0x01000000
#define  RF_ID_MT6140C     0x02000000
#define  RF_ID_GRF6201     0x04000000
#define  RF_ID_IRFS3001    0x08000000
#define  RF_ID_MT6140D     0x10000000
#define  RF_ID_AG2550      0x10000001
#define  RF_ID_AERO2E      0x10000002
#define  RF_ID_AD6548      0x10000005     
#define  RF_ID_AD6546      0x10000006
#define  RF_ID_A60111A     0x10000007

typedef enum
{
   FrequencyBand400=0,				// GSM 450/480 band
   FrequencyBand850,				// GSM 850 band
   FrequencyBand900,				// GSM 900 band
   FrequencyBand1800,				// DCS 1800 band
   FrequencyBand1900,				// PCS 1900 band

   FrequencyBandCount				// count of supported bands
} FrequencyBand;

typedef struct 
{
	ARFCN			arfcn;				// Absolute radio frequency channel number
	char			sampleNoPerFrame;	// number of samples per frame
	Gain			gain;				// Gain that should be used in power management
	short			frames;				// number of frames
} RfPm_Req;

typedef struct {
	unsigned char	valid;				// if valid != zero, it means the extra info is meaningful. 
										// otherwise, the extra info should be ignore. 
   	int				iOffset;
	int				qOffset;
	int				validSamples;
} RfPmExtraInfo_T;

typedef struct
{
	int				power;				// average power
	int				deviation;			// deviation of power measurement
	Gain			usedGain;			// Gain that is used
	unsigned char	ok;					// status
	RfPmExtraInfo_T	extra_info;			// extra info 
} RfPm_Cnf;

typedef struct
{
	ARFCN			arfcn;				// absolute radio frequency channel number
	short			dacValue;			// AFC DAC value
	Gain			gain;				// gain used for AFC testing
	short			testNumber;			// test number
} RfAfc_Req;

typedef struct
{
	short			fcb_ok_number;		// successful number of FCB decoded
	int				freqOffset;			// average frequency error
	int				deviation;			// deviation of frequency error
	unsigned char	ok;					// status
} RfAfc_Cnf;

typedef enum {
	 AB_TX_RANDOM_WITH_SYNC_SEQ
	,NB_TX_ALL_ZEROS_WITHOUT_TSC
	,NB_TX_ALL_ONES_WITHOUT_TSC
	,NB_TX_ALTER_BITS_WITHOUT_TSC
	,NB_TX_RANDOM_WITH_TSC
	,NB_TX_PATTERN_WITHOUT_TSC
	,NB_TX_FIXED_RANDOM_WITH_TSC
	,NB_TX_FIXED_ALL_ZEROS_WITH_TSC
	,NB_TX_FIXED_ALTER_BITS_WITH_TSC
} APCTxPattern;

typedef struct
{
	ARFCN			arfcn;				// Absolute radio frequency channel number
	BSIC			bsic;				// bsic value used in transmission
	Power			power;				// Tx power in the unit of PCL
	short			frames;				// the number of frames NB should transmit
	short			dacValue;			// AFC DAC value
	APCTxPattern	burstTypeNB;
} RfNbtx_Req;

typedef struct
{
	ARFCN			arfcn;				// Absolute radio frequency channel number
	Gain			gain;				// Gain that should be used
	unsigned char	OnOff;				// On or off
} RfCnRx_Req;

typedef enum {
	CONT_TX_ALL_ZEROS
	,CONT_TX_ALL_ONES
	,CONT_TX_ALTERNATE_BITS
	,CONT_TX_PSEUDO_RANDOM
	,CONT_TX_PATTERN_WITHOUT_TSC
} ContTxPattern;

typedef struct
{
	ARFCN			arfcn;				// Absolute radio frequency channel number
	ContTxPattern	pattern;
	unsigned char	OnOff;				// On or off
} RfCnTx_Req;

typedef struct
{
	char	TxTrimI;
	char	TxTrimQ;
	char	TxOffsetI;
	char	TxOffsetQ;
} RfSetBBTXCfg_Req;

typedef struct {
	char	TxTrimI;
	char	TxTrimQ;
	char	TxOffsetI;
	char	TxOffsetQ;
	char	TxCalbias;
	char	TxIQSwap;
	char	TxCMV;
	char	TxGain;
	char	TxCalrcsel;
} RfBBTXCfg2;

typedef struct {
	char	TxTrimI;
	char	TxTrimQ;
	char	TxOffsetI;
	char	TxOffsetQ;
	char	TxCalbias;
	char	TxIQSwap;
	char	TxCMV;
	char	TxGain;
	char	TxCalrcsel;
	char	TxPhasesel;
} RfBBTXCfg3;

typedef struct {
	char    TxTrimI;
	char    TxTrimQ;
	char	TxOffsetI;
	char	TxOffsetQ;
	char	TxCalbias;
	char	TxIQSwap;
	char	TxCMV;
	char	TxGain;
	char	TxCalrcsel;
	char	TxPhasesel;
	char    TxCoarseI;
	char    TxCoarseQ;

}RfBBTXCfg4;  //RfTestCmdSetBBTXCfg4

typedef struct
{
    unsigned char bbtx_common_mode_voltage;
    unsigned char bbtx_gain;
    unsigned char bbtx_calrcsel;
//    unsigned char bbtx_coarseI; // need to set
//   unsigned char bbtx_coarseQ; // need to set
    unsigned char bbtx_trimI;   // need to set
    unsigned char bbtx_trimQ;   // need to set
	unsigned char bbtx_dccoarseI; // need to set
    unsigned char bbtx_dccoarseQ; // need to set
    unsigned char bbtx_offsetI; // need to set
    unsigned char bbtx_offsetQ; // need to set
    unsigned char bbtx_isCalibrated; // need to set
    int           apc_bat_low_voltage;
    int           apc_bat_high_voltage;
    int           apc_bat_low_temperature;
    int           apc_bat_high_temperature;
    unsigned char bbtx_common_mode_voltage_h;
    unsigned char bbtx_gain_h;
    unsigned char bbtx_calrcsel_h;
    unsigned char bbtx_trimI_h;
    unsigned char bbtx_trimQ_h;
//    unsigned char bbtx_coarseI_h;
//    unsigned char bbtx_coarseQ_h;
	unsigned char bbtx_dccoarseI_h;
    unsigned char bbtx_dccoarseQ_h;

    unsigned char bbtx_offsetI_h;
    unsigned char bbtx_offsetQ_h;
    unsigned char bbtx_phsel;
    unsigned char bbtx_phsel_h;
//    unsigned char bbrx_gsm850_gsm900_swap;
 //   unsigned char bbrx_dcs1800_pcs1900_swap;
}BBTXParameters_T;
typedef enum {
	CodingSchemeCS1 = 1,
	CodingSchemeCS2,
	CodingSchemeCS3,
	CodingSchemeCS4,
	CodingSchemePRACh8,
	CodingSchemePRACh11,
	CodingSchemeMCS1,
	CodingSchemeMCS2,
	CodingSchemeMCS3,
	CodingSchemeMCS4,
	CodingSchemeMCS5,
	CodingSchemeMCS6,
	CodingSchemeMCS7,
	CodingSchemeMCS8,
	CodingSchemeMCS9
} CodingScheme;

typedef struct {
	ARFCN			arfcn;			// absolute radio frequency channel number
	BSIC			bsic;			// training sequence
	char			timeSlotmask;	// time slot mask, slot_1: 0x01, slot_2: 0x02, slot_3: 0x04, slot_4: 0x08
	Power			powerLev[4];	// power level for each time slot
	CodingScheme	cs[4];			// coding scheme for each time slot
	TimingAdvance	ta;				// time advance
	int				frames;			// the number of frames should transmit
	short			dacValue;		// AFC DAC value
} RfMultiSlotTX_Req;

typedef struct {
	FrequencyBand	rf_band;
	int				power_level;
	int				apc_dac;
} RfSetRampApcLevel_Req;

typedef struct {
	short			dacValue;		// AFC DAC value
} RfSetAfcDacValue_Req;

typedef struct {
	int				cap_id;
} RfSetCrystalCfg_Req;

typedef struct {
	ARFCN			arfcn;			// absolute radio frequency channel number
	BSIC			bsic;			// training sequence
	char			timeSlotmask;	// time slot mask, slot_1: 0x01, slot_2: 0x02, slot_3: 0x04, slot_4: 0x08
	Power			powerLev[4];	// power level for each time slot
	CodingScheme	cs[4];			// coding scheme for each time slot, MCS1~9 is only valid for EPSK function 
	TimingAdvance	ta;				// time advance
	int				frames;			// the number of frames should transmit
	short			dacValue;		// AFC DAC value
	APCTxPattern	pattern;		// Tx pattern is only valid for EPSK function  
	unsigned short	pattern_data;	// if NB_TX_PATTERN_WITHOUT_TSC==pattern, user can input any 16bits value as pattern. 
} Rf_MultiSlotTXEx_Req;

typedef struct {
	unsigned int	id;				// please refer RF_ID_XXXX 
} RFMod_ID;

typedef enum {
	MS_GSM = 0
	,MS_GPRS
	,MS_EGPRS_RX_ONLY
	,MS_EGPRS_FULL_FUNCTION
} MS_CAPABILITY_E;

typedef struct {
	unsigned int	GSM400;			// Zero: not support, Non-zero: support 
	unsigned int	GSM850;
	unsigned int	GSM900;
	unsigned int	DCS1800;
	unsigned int	PCS1900;
} RFBandSupport_S;

typedef struct {
	MS_CAPABILITY_E		capability;
	RFBandSupport_S		band_support;
} RfMsCapability_S;

typedef struct {
	unsigned int	GSM:1;
	unsigned int	GPRS:1;
	unsigned int	EDGE_RX:1;
	unsigned int	EDGE_8PSK_TX:1;
	unsigned int	Calibration_8PM:1;
} RfMsCapabilityBits;

typedef struct {
	unsigned int	GSM:1;
	unsigned int	GPRS:1;
	unsigned int	EDGE_RX:1;
	unsigned int	EDGE_8PSK_TX:1;
	unsigned int	Calibration_8PM:1;
	unsigned int    Calibration_FDT:1;      // new
	unsigned int    Calibration_33Steps:1;  // new
} RfMsCapabilityBits_2;

typedef struct {
	unsigned int	GSM400:1;
	unsigned int	GSM850:1;
	unsigned int	GSM900:1;
	unsigned int	DCS1800:1;
	unsigned int	PCS1900:1;
} RfMsBandSupportBits;

typedef struct {
	RfMsCapabilityBits		capability;
	RfMsBandSupportBits		band_support;
} RfMsCapabilityEx_S;

typedef struct {
	RfMsCapabilityBits_2		capability;
	RfMsBandSupportBits		band_support;
} RfMsCapabilityEx2_S;



typedef enum {
	AFC_SINWAVE_OFF = 0
	,AFC_SINWAVE_ON
} AFC_SINWAVE_DETECTION_E;

typedef struct {
	ARFCN			arfcn;				// Absolute radio frequency channel number
	ContTxPattern	pattern;
	unsigned short	pattern_data;
	unsigned char	OnOff;				// On or off 
	unsigned short	modtype;			// modulation type: 0->GMSK, 1->EPSK 
} RfCnTxEx_Req;

typedef struct {
	ARFCN			arfcn;				// Absolute radio frequency channel number
	ContTxPattern	pattern;
	unsigned short	pattern_data;
	unsigned char	OnOff;				// On or off 
	unsigned short	modtype;			// modulation type: 0->GMSK, 1->EPSK 
	Power			powerLev;			// power level 
} RfCnTxEx2_Req;

typedef struct {
	short			dacValue;		// AFC DAC value
} RfGetAfcDacValueAtRTXOffsetCal;

//----------  FDT related structure -----------------------

#define MAX_STEP_CNT   50
typedef struct{
   FrequencyBand	  band;
   ARFCN			  arfcn;
   short		      dac_value[33];
   Gain			      gain;
   short		      repeat_cnt;	// repetitive test counts (frames) for each AFC DAC value
   bool			      capid_cal;	// capid calibration ctrl
   bool			      linear_cal;	// 33 stages calibration ctrl
   //char			      capid_min;	// min value for capid range when capid_cal is True; capid when capid_cal is False
   //char			      capid_max;	// max value for capid range
   int			      capid_min;	// min value for capid range when capid_cal is True; capid when capid_cal is False
   int			      capid_max;	// max value for capid range

}Rf_DSSAFC_T;

typedef struct
{
   FrequencyBand 	   band;
   ARFCN			   arfcn;
   Gain				   gain[6];		// gain for rx slot 0/1/2/3/4/5
   short			   repeat_cnt;	// repetitive test counts (frames) for each ARFCN value
//   short			   dac_value;	// Use InitDacValue from AFC calibration when dacValue = 0 (or -1)
} Rf_DSSPL_T;

typedef struct
{
   bool				   afc_cal;
   bool                pl_cal;       // Control whether Path loss calibration is needed or not
   char				   sync_sb_num;	// the SB frame numbers needed for sync process before path loss calibration
   short		       power;               // the power level expected to measure from test set
   Rf_DSSAFC_T 	       AfcDSS;
   char				   step_cnt;
   Rf_DSSPL_T	       PathLossDSS[MAX_STEP_CNT-2]; // because sync process will need 2 steps

}Rf_DTS_REQ_T;

typedef struct
{
   FrequencyBand	    band;
   ARFCN			    arfcn;
   char				    timeslot_per_frame;	
   char				    apc_dac_pcl_sel;				// 1: apc_dac, 0: apc_pcl
   short			    apc_dac_pcl_value[4];
   unsigned char		pa_vbias_val;	
   CodingScheme		    cs[4];
   int			        repeat_cnt;			
   short			    afc_dac_value;
   char				    tsc;
   APCTxPattern			pattern;		
   unsigned short		pattern_data;
} Rf_USSAPC_T;

typedef struct
{
//   bool                pa_vbias_cal;
   char				   step_cnt;
   Rf_USSAPC_T	       ApcUSS[MAX_STEP_CNT];
}Rf_UTS_REQ_T;

typedef struct
{
   int	    power[MAX_STEP_CNT-2];  // because sync process will need 2 steps
   short    valid_sample[MAX_STEP_CNT-2];
   bool		ok;
} Rf_DSSPL_RESULT_T;

typedef struct
{
   int	    freq_offset[33];	// only valid when 33 stage calibration is ON
   int	    deviation[33];		// only valid when 33 stage calibration is ON
   short	fcb_ok_number[33];  // only valid when 33 stage calibration is ON
   //char		capid;			    // only valid when capid calibration is ON
   int		capid;			    // only valid when capid calibration is ON
   short	init_dac_value; 	// only valid when 33 stage calibration is OFF
   int	    slope;              // only valid when 33 stage calibration is OFF
   bool		ok;
} Rf_DSSAFC_RESULT_T;

typedef struct
{
   Rf_DSSPL_RESULT_T	  PLResult;
   Rf_DSSAFC_RESULT_T	  AfcResult;
	
} Rf_DTS_CNF_T;

//-----------------------------------------------------//
//  TX Ramping Table                                   //
//-----------------------------------------------------//
#define PROFILE_NUM             16
#define ARFCN_SECTION_NUM       12
#define ARFCN_SECTION_NUM_Ex       64
typedef  struct
{
   unsigned char   point[2][16];	// ramp up/down profile

} sRAMPAREADATA;

typedef  struct
{
   short			max_arfcn;		// sub-band boundary of this PCL weighting area
   unsigned short   mid_level;		// PCLboundary level to apply high/low weighting
   unsigned short   hi_weight;		// scale factor of PCLs higher than mid_level
   unsigned short   low_weight;		// scale factor of PCLs lower than mid_level

} sARFCN_SECTION;

typedef  struct
{
   int				lowest_power;						// The lower apc power of the indicated band
   unsigned short	power[16];							// The mapping of power level to apc dac value
   sRAMPAREADATA	ramp[ PROFILE_NUM ];				// ramp profile
   sARFCN_SECTION	arfcn_weight[ ARFCN_SECTION_NUM ];	// profile of weighting power level by PCL and sub-band
   unsigned short	battery_compensate[3][3];			// [volt][temp] 
   short			tx_afc_offset;
} sRAMPDATA;

typedef struct
{
   int				lowest_power;						// The lower apc power of the indicated band
   unsigned short	power[16];							// The mapping of power level to apc dac value
   sRAMPAREADATA	ramp[ PROFILE_NUM ];				// ramp profile
   sARFCN_SECTION	arfcn_weight[ ARFCN_SECTION_NUM_Ex ];	// profile of weighting power level by PCL and sub-band
   unsigned short	battery_compensate[3][3];			// [volt][temp] 
   short			tx_afc_offset;
} sRAMPDATA_Ex;

typedef  struct
{
   int				lowest_power;						// The lower apc power of the indicated band
   unsigned short	power[16];							// The mapping of power level to apc dac value
   sRAMPAREADATA	ramp[ PROFILE_NUM ];				// ramp profile
   sARFCN_SECTION	arfcn_weight[ ARFCN_SECTION_NUM ];	// profile of weighting power level by PCL and sub-band
   unsigned short	battery_compensate[3][3];			// [volt][temp] 
   short			tx_afc_offset;
   unsigned char	vbias[16];
} sRAMPDATA_Ex2;

typedef struct
{
   sRAMPDATA          rampData;							// apc ramp profile of all bands
}l1cal_rampTable_T;

typedef struct
{
   sRAMPDATA_Ex          rampData;							// apc ramp profile of all bands
}l1cal_rampTable_T_Ex;

typedef struct
{
   sRAMPDATA_Ex2          rampData;							// apc ramp profile of all bands
}l1cal_rampTable_T_Ex2;

//-----------------------------------------------------//
//  TX Inter Ramping Table                             //
//-----------------------------------------------------//

// interRampData 
typedef struct {   
	unsigned char	interRampData[16];
} l1cal_interRampData_T;

// EPSK interRampData 
typedef struct {
	unsigned char	EPSK_interRampData[4][16];
} l1cal_EPSK_interRampData_T;

//-----------------------------------------------------//
//  3F RF compose/decompose table                      //
//-----------------------------------------------------//
#define  CAL_UARFCN_SECTION  15
#define  U_ARFCN_SECTION_NUM   15
#define  CAL_TEMP_SECTION     8
#define CAL_PWR_DETECTOR_SECTION 32  
typedef  struct
{
   unsigned short  max_uarfcn;
    char   path_loss_H;//loss;
    char   path_loss_M;//gain_diff_HM;
    char   path_loss_L;//gain_diff_HL;
}  U_sAGCGAINOFFSET;

typedef  struct
{
   //char   temp;   
   U_sAGCGAINOFFSET  gain_of_uarfcn[CAL_UARFCN_SECTION];   
}  U_sTEMPAGCOFFSET;

typedef  struct
{
   unsigned short dc2dc_dac;
   unsigned short vbias_dac;
   unsigned char vm1;
   unsigned char vm2;
}  U_sPADATA;

typedef  struct
{
   unsigned short  max_uarfcn;
   short           pwr_offset;
   short           pwr_slope;
} U_sARFCN_SECTION;

typedef struct
{
   unsigned short max_uarfcn;
   short          pwr_offset_dB; /* unit: 1/32 dB, range: -8 ~ +7 dB */ 
   short          pwr_offset_txdac;
}U_sARFCN_SECTION_B;  // for MT6268B later


typedef  struct
{
   //unsigned short  pa_dac;
   U_sPADATA          pa_data;
   unsigned short     vga_dac[90];//vga_dac[81];
   U_sARFCN_SECTION   vga_comp_by_subband[CAL_UARFCN_SECTION];
   short              vga_comp_by_temperature[8][2];  //[0]:slope, [1]:offset
   //short           vga_offset_by_temperature[8]; 
} U_sTXPOWERDATA;

typedef  struct
{
   U_sPADATA           pa_data; 
   unsigned short      vga_dac[90];
   U_sARFCN_SECTION_B  vga_comp_by_subband[ CAL_UARFCN_SECTION ];
   short               vga_comp_by_temperature[8][2];  //[0]:offset in dB (unit: 1/32 dB), [1]:offset in txdac
} U_sTXPOWERDATA_B;  // for MT6268B later

typedef  struct
{
   unsigned short start;
   unsigned short end;
} U_sHYSTERESISDATA;

typedef  struct
{
   unsigned char     pwr_dt_thr;
   unsigned char     pwr_dt_section;   // can not be larger than CAL_PWR_DETECTOR_SECTION
   unsigned short    pwr_dt_dac[CAL_PWR_DETECTOR_SECTION];
   
   short             pwr_dt_value[CAL_PWR_DETECTOR_SECTION]; //bit0~4 is used for fractions
   U_sARFCN_SECTION  pwr_dt_comp_by_subband[CAL_UARFCN_SECTION];   // for compensation, no need calibration, after test, will auto-store
   short             pwr_dt_comp_by_temperature[8][2];  //[0]:slope, [1]:offset
 
}  U_sPWTDTDATA;

typedef  struct
{
   unsigned char       pwr_dt_thr;
   unsigned char       pwr_dt_section;
   unsigned short      pwr_dt_dac[ CAL_PWR_DETECTOR_SECTION ];
   short               pwr_dt_value[ CAL_PWR_DETECTOR_SECTION ]; //bit0~4 is used for fractions
   U_sARFCN_SECTION_B  pwr_dt_comp_by_subband[ CAL_UARFCN_SECTION ];
   short               pwr_dt_comp_by_temperature[8][2];  //[0]:offset in dB (unit: 1/32 dB), [1]:offset in txdac
}  U_sPWTDTDATA_B;   // for MT6268B later



typedef  struct
{
   U_sTXPOWERDATA    power_dac[3];   //0:PA high mode, 1:PA mid mode, 2:PA low mode (use 0&1 if only 2 mode)
   U_sHYSTERESISDATA tx_hysteresis[2];
   U_sPWTDTDATA      pwr_dt_data;
 //  U_sRAMPAREADATA   u_ramp;
 //  U_sARFCN_SECTION  u_arfcn_weight[ U_ARFCN_SECTION_NUM ];
} U_sRAMPDATA;

typedef  struct
{
   U_sTXPOWERDATA_B      power_dac[3];   //0:PA high mode, 1:PA mid mode, 2:PA low mode (use 0&1 if only 2 mode)
   U_sHYSTERESISDATA     tx_hysteresis[2];
   U_sPWTDTDATA_B        pwr_dt_data;

} U_sRAMPDATA_B;   // for MT6268B later


//chliu provide
typedef struct
{
   unsigned char tempdacData[8];
}ul1cal_tempdacData_T; 

typedef struct
{
   U_sTEMPAGCOFFSET  pathlossData[CAL_TEMP_SECTION]; 
}ul1cal_pathlossData_T;

typedef struct
{
   U_sRAMPDATA txdacData; 
}ul1cal_txdacData_T;

typedef struct
{
   U_sRAMPDATA_B txdacData; 
}ul1cal_txdacData_T_B;   // for MT6268B later

/* end of chliu */

//-----------------------------------------------------//
//  RF Module Special Coef                             //
//-----------------------------------------------------//

//mt6140D
typedef struct{
   short		pcl_index;
   unsigned char pa_vbias1;   
}pa_vbias;

typedef struct {
   pa_vbias GSM850_pa_vbias[8];
   pa_vbias GSM900_pa_vbias[8];   
   pa_vbias DCS1800_pa_vbias[8];
   pa_vbias PCS1900_pa_vbias[8];
   //pa_vbias low_band_pa_vbias[8];
   //pa_vbias high_band_pa_vbias[8];
}mt6140tx_pa_vbias;

typedef struct{  
      mt6140tx_pa_vbias data;
}mt6140tx;  
// Skyworks 
typedef struct {
	unsigned int		icorrection;
	unsigned int		qcorrection;
} RF_SKY74045_IP2_Coef;

typedef struct {
	RF_SKY74045_IP2_Coef	coef[5/*band*/];
} RF_SKY74045_RX_Coef;

typedef struct {
	RF_SKY74045_RX_Coef		rx;
} RF_SKY74045_Coef_T;

typedef struct {
	unsigned int			ipol;
	unsigned int			qpol;
} RF_SKY74117_IP2_Pol;

typedef struct {
	RF_SKY74045_IP2_Coef	coef[5/*band*/];
	RF_SKY74117_IP2_Pol		pol[5/*band*/];
} RF_SKY74117_RX_Coef;

typedef struct {
	RF_SKY74117_RX_Coef		rx;
} RF_SKY74117_Coef_T;

// MT6139B 
typedef struct {
	unsigned int		acode;
	unsigned int		amcode;
} RF_MT6139B_IP2_Coef;

typedef struct {  
	RF_MT6139B_IP2_Coef		coef[5/*band*/];
	unsigned int			rxamcalmode;
} RF_MT6139B_RX_Coef;

typedef struct {
	RF_MT6139B_RX_Coef		rx;
} RF_MT6139B_Coef_T;

// Bright5P 
typedef struct {
	unsigned int		word6_4_0;
	unsigned int		word6_5_0;
	unsigned int		word6_6_0;
	unsigned int		word6_7_0;
	unsigned int		bvmode;
	unsigned int		c3mode;
	unsigned int		wordC3;
} RF_BRIGHT5P_TX_Coef;

typedef struct {
	RF_BRIGHT5P_TX_Coef		tx;
} RF_BRIGHT5P_Coef_T;

typedef struct
{
   unsigned char REFDET_SLOPE_SKEW ;
   unsigned char AM_FB_DAC; 
}ad6546txcoef;



typedef  struct
{ 
      ad6546txcoef   CalData[4];

} ad6546tx;   

//-----------------------------------------------------//
//  RF Testing: callback function definition           //
//-----------------------------------------------------//
typedef void (__stdcall *META_RF_PM_CNF)(const RfPm_Cnf *cnf, const short token, void *usrData);
typedef void (__stdcall *META_RF_AFC_CNF)(const RfAfc_Cnf *cnf, const short token, void *usrData);
typedef void (__stdcall *META_RF_NB_TX_CNF)(const unsigned char cnf, const short token, void *usrData);
typedef void (__stdcall *META_RF_CONT_RX_CNF)(const unsigned char cnf, const short token, void *usrData);
typedef void (__stdcall *META_RF_CONT_TX_CNF)(const unsigned char cnf, const short token, void *usrData);
typedef void (__stdcall *META_RF_SETBBTX_CFG_CNF)(const unsigned char cnf, const short token, void *usrData);
typedef void (__stdcall *META_RF_SELBAND_CNF)(const unsigned char cnf, const short token, void *usrData);
typedef void (__stdcall *META_RF_STOP_CNF)(const unsigned char cnf, const short token, void *usrData);
typedef void (__stdcall *META_RF_MULTISLOT_TX_CNF)(const unsigned char cnf, const short token, void *usrData);
typedef void (__stdcall *META_RF_SET_RAMPAPCLEVEL_CNF)(const unsigned char cnf, const short token, void *usrData);
typedef void (__stdcall *META_RF_SET_AFCDACVALUE_CNF)(const unsigned char cnf, const short token, void *usrData);

//-----------------------------------------------------//
//  RF Testing: exported function definition           //
//-----------------------------------------------------//
// for SP project, RF is exclusive

META_RESULT  __stdcall SP_META_Rf_PM(const RfPm_Req *req, const META_RF_PM_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_PM_r(const int meta_handle, const RfPm_Req *req, const META_RF_PM_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_AFC(const RfAfc_Req *req, const META_RF_AFC_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_AFC_r(const int meta_handle, const RfAfc_Req *req, const META_RF_AFC_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_NB_TX(const RfNbtx_Req *req, const META_RF_NB_TX_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_NB_TX_r(const int meta_handle, const RfNbtx_Req *req, const META_RF_NB_TX_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_CONTINUE_RX(const RfCnRx_Req *req, const META_RF_CONT_RX_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_CONTINUE_RX_r(const int meta_handle, const RfCnRx_Req *req, const META_RF_CONT_RX_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_CONTINUE_TX(const RfCnTx_Req *req, const META_RF_CONT_TX_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_CONTINUE_TX_r(const int meta_handle, const RfCnTx_Req *req, const META_RF_CONT_TX_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_SetBBTXCfg(const RfSetBBTXCfg_Req *req, const META_RF_SETBBTX_CFG_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_SetBBTXCfg_r(const int meta_handle, const RfSetBBTXCfg_Req *req, const META_RF_SETBBTX_CFG_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_SelectFrequencyBand1900(const unsigned char selectPCS1900, const META_RF_SELBAND_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_SelectFrequencyBand1900_r(const int meta_handle, const unsigned char selectPCS1900, const META_RF_SELBAND_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_Stop(const META_RF_STOP_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_Stop_r(const int meta_handle, const META_RF_STOP_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_MultiSlot_TX(const RfMultiSlotTX_Req *req, const META_RF_MULTISLOT_TX_CNF  cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_MultiSlot_TX_r(const int meta_handle, const RfMultiSlotTX_Req *req, const META_RF_MULTISLOT_TX_CNF  cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_SetAfcDacValue(const RfSetAfcDacValue_Req *req, const META_RF_SET_AFCDACVALUE_CNF  cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_SetAfcDacValue_r(const int meta_handle, const RfSetAfcDacValue_Req *req, const META_RF_SET_AFCDACVALUE_CNF  cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_SetBBTxCfg2(unsigned int ms_timeout, const RfBBTXCfg2  *tx_cfg_req, RfBBTXCfg2  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_SetBBTxCfg2_r(const int meta_handle, unsigned int ms_timeout, const RfBBTXCfg2  *tx_cfg_req, RfBBTXCfg2  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_GetBBTxCfg2(unsigned int ms_timeout, RfBBTXCfg2  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_GetBBTxCfg2_r(const int meta_handle, unsigned int ms_timeout, RfBBTXCfg2  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_SetCrystalCapId(unsigned int ms_timeout, const RfSetCrystalCfg_Req  *req);
META_RESULT  __stdcall SP_META_Rf_SetCrystalCapId_r(const int meta_handle, unsigned int ms_timeout, const RfSetCrystalCfg_Req  *req);
META_RESULT  __stdcall SP_META_Rf_BBTXAutoCal(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_Rf_BBTXAutoCal_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_Rf_QueryMSCapability(unsigned int ms_timeout, RfMsCapability_S  *p_type);
META_RESULT  __stdcall SP_META_Rf_QueryMSCapability_r(const int meta_handle, unsigned int ms_timeout, RfMsCapability_S  *p_type);
META_RESULT  __stdcall SP_META_Rf_QueryMSCapabilityEx(unsigned int ms_timeout, RfMsCapabilityEx_S  *p_ms_cap);
META_RESULT  __stdcall SP_META_Rf_QueryMSCapabilityEx_r(const int meta_handle, unsigned int ms_timeout, RfMsCapabilityEx_S  *p_ms_cap);
META_RESULT  __stdcall SP_META_Rf_SetAfcSinWaveDetection(unsigned int ms_timeout, AFC_SINWAVE_DETECTION_E  bIsAfcSinWaveOn);
META_RESULT  __stdcall SP_META_Rf_SetAfcSinWaveDetection_r(const int meta_handle, unsigned int ms_timeout, AFC_SINWAVE_DETECTION_E  bIsAfcSinWaveOn);
META_RESULT  __stdcall SP_META_Rf_QueryIfTwoApcDCOffsetSupport(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_Rf_QueryIfTwoApcDCOffsetSupport_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_Rf_MultiSlot_TX_Ex(unsigned int ms_timeout, const Rf_MultiSlotTXEx_Req *req);
META_RESULT  __stdcall SP_META_Rf_MultiSlot_TX_Ex_r(const int meta_handle, unsigned int ms_timeout, const Rf_MultiSlotTXEx_Req *req);
META_RESULT  __stdcall SP_META_Rf_GetRFID(unsigned int ms_timeout, RFMod_ID *cnf);
META_RESULT  __stdcall SP_META_Rf_GetRFID_r(const int meta_handle, unsigned int ms_timeout, RFMod_ID *cnf);
META_RESULT  __stdcall SP_META_Rf_CONTINUE_TX_Ex(unsigned int ms_timeout, const RfCnTxEx_Req *req);
META_RESULT  __stdcall SP_META_Rf_CONTINUE_TX_Ex_r(const int meta_handle, unsigned int ms_timeout, const RfCnTxEx_Req *req);
META_RESULT  __stdcall SP_META_Rf_SetBBTxCfg3(unsigned int ms_timeout, const RfBBTXCfg3  *tx_cfg_req, RfBBTXCfg3  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_SetBBTxCfg3_r(const int meta_handle, unsigned int ms_timeout, const RfBBTXCfg3  *tx_cfg_req, RfBBTXCfg3  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_GetBBTxCfg3(unsigned int ms_timeout, RfBBTXCfg3  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_GetBBTxCfg3_r(const int meta_handle, unsigned int ms_timeout, RfBBTXCfg3  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_CONTINUE_TX_Ex2(unsigned int ms_timeout, const RfCnTxEx2_Req *req);
META_RESULT  __stdcall SP_META_Rf_CONTINUE_TX_Ex2_r(const int meta_handle, unsigned int ms_timeout, const RfCnTxEx2_Req *req);
META_RESULT  __stdcall SP_META_Rf_GetAfcDacValueAtRTXOffsetCal(unsigned int ms_timeout, RfGetAfcDacValueAtRTXOffsetCal *cnf);
META_RESULT  __stdcall SP_META_Rf_GetAfcDacValueAtRTXOffsetCal_r(const int meta_handle, unsigned int ms_timeout, RfGetAfcDacValueAtRTXOffsetCal *cnf);

META_RESULT  __stdcall SP_META_Rf_SetBBTxCfg4(unsigned int ms_timeout, const RfBBTXCfg4  *tx_cfg_req, RfBBTXCfg4  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_SetBBTxCfg4_r(const int meta_handle, unsigned int ms_timeout, const RfBBTXCfg4  *tx_cfg_req, RfBBTXCfg4  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_GetBBTxCfg4(unsigned int ms_timeout, RfBBTXCfg4  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_GetBBTxCfg4_r(const int meta_handle, unsigned int ms_timeout, RfBBTXCfg4  *tx_cfg_cnf);

META_RESULT  __stdcall SP_META_Rf_SetBBTxCfg5(unsigned int ms_timeout, const RfBBTXCfg4  *tx_cfg_req, RfBBTXCfg4  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_SetBBTxCfg5_r(const int meta_handle, unsigned int ms_timeout, const RfBBTXCfg4  *tx_cfg_req, RfBBTXCfg4  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_GetBBTxCfg5(unsigned int ms_timeout, RfBBTXCfg4  *tx_cfg_cnf);
META_RESULT  __stdcall SP_META_Rf_GetBBTxCfg5_r(const int meta_handle, unsigned int ms_timeout, RfBBTXCfg4  *tx_cfg_cnf);

//-----------------------------------------------------//
//  RunTime Setting Functions Without Update NVRAM     //
//-----------------------------------------------------//
META_RESULT  __stdcall SP_META_Rf_SetRampTable(unsigned int ms_timeout, FrequencyBand  band, const l1cal_rampTable_T  *ramp);
META_RESULT  __stdcall SP_META_Rf_SetRampTable_r(const int meta_handle, unsigned int ms_timeout, FrequencyBand  band, const l1cal_rampTable_T  *ramp);
META_RESULT  __stdcall SP_META_Rf_SetRampApcLevel(const RfSetRampApcLevel_Req *req, const META_RF_SET_RAMPAPCLEVEL_CNF  cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_SetRampApcLevel_r(const int meta_handle, const RfSetRampApcLevel_Req *req, const META_RF_SET_RAMPAPCLEVEL_CNF  cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Rf_EPSK_SetRampTable(unsigned int ms_timeout, FrequencyBand  band, const l1cal_rampTable_T  *ramp);
META_RESULT  __stdcall SP_META_Rf_EPSK_SetRampTable_r(const int meta_handle, unsigned int ms_timeout, FrequencyBand  band, const l1cal_rampTable_T  *ramp);
META_RESULT  __stdcall SP_META_Rf_EPSK_SetRampApcLevel(unsigned int ms_timeout, const RfSetRampApcLevel_Req *req);
META_RESULT  __stdcall SP_META_Rf_EPSK_SetRampApcLevel_r(const int meta_handle, unsigned int ms_timeout, const RfSetRampApcLevel_Req *req);
META_RESULT  __stdcall SP_META_Rf_SetRFImmediateBSI(unsigned int ms_timeout, const unsigned int bsi_data);
META_RESULT  __stdcall SP_META_Rf_SetRFImmediateBSI_r(const int meta_handle, unsigned int ms_timeout, const unsigned int bsi_data);
META_RESULT  __stdcall SP_META_Rf_GetRFImmediateBSI(unsigned int ms_timeout, unsigned int bsi_addr, unsigned int *p_bsi_data);
META_RESULT  __stdcall SP_META_Rf_GetRFImmediateBSI_r(const int meta_handle, unsigned int ms_timeout, unsigned int bsi_addr, unsigned int *p_bsi_data);

META_RESULT  __stdcall SP_META_Rf_SetRampTable_Ex(unsigned int ms_timeout, FrequencyBand  band, const l1cal_rampTable_T_Ex  *ramp);
META_RESULT  __stdcall SP_META_Rf_SetRampTable_Ex_r(const int meta_handle, unsigned int ms_timeout, FrequencyBand  band, const l1cal_rampTable_T_Ex  *ramp);
META_RESULT  __stdcall SP_META_Rf_SetRampTable_Ex2(unsigned int ms_timeout, FrequencyBand  band, const l1cal_rampTable_T_Ex2  *ramp);
META_RESULT  __stdcall SP_META_Rf_SetRampTable_Ex2_r(const int meta_handle, unsigned int ms_timeout, FrequencyBand  band, const l1cal_rampTable_T_Ex2  *ramp);

// Skyworks
META_RESULT  __stdcall SP_META_Rf_SKY74045_SetSpecialCoef(unsigned int ms_timeout, const RF_SKY74045_Coef_T *rf_mod_coef);
META_RESULT  __stdcall SP_META_Rf_SKY74045_SetSpecialCoef_r(const int meta_handle, unsigned int ms_timeout, const RF_SKY74045_Coef_T *rf_mod_coef);
META_RESULT  __stdcall SP_META_Rf_SKY74117_SetSpecialCoef(unsigned int ms_timeout, const RF_SKY74117_Coef_T *rf_mod_coef);
META_RESULT  __stdcall SP_META_Rf_SKY74117_SetSpecialCoef_r(const int meta_handle, unsigned int ms_timeout, const RF_SKY74117_Coef_T *rf_mod_coef);
// MT6139B
META_RESULT  __stdcall SP_META_Rf_MT6139B_SetSpecialCoef(unsigned int ms_timeout, const RF_MT6139B_Coef_T *rf_mod_coef);
META_RESULT  __stdcall SP_META_Rf_MT6139B_SetSpecialCoef_r(const int meta_handle, unsigned int ms_timeout, const RF_MT6139B_Coef_T *rf_mod_coef);
// Renesas Bright5P 
META_RESULT  __stdcall SP_META_Rf_BRIGHT5P_SetSpecialCoef(unsigned int ms_timeout, const RF_BRIGHT5P_Coef_T *rf_mod_coef);
META_RESULT  __stdcall SP_META_Rf_BRIGHT5P_SetSpecialCoef_r(const int meta_handle, unsigned int ms_timeout, const RF_BRIGHT5P_Coef_T *rf_mod_coef);

META_RESULT  __stdcall SP_META_Rf_32kCalibration(unsigned int ms_timeout, int *p_result);
META_RESULT  __stdcall SP_META_Rf_32kCalibration_r(const int meta_handle, unsigned int ms_timeout, int *p_result);

META_RESULT  __stdcall SP_META_Rf_AD6546_SetSpecialCoef(unsigned int ms_timeout, const ad6546tx *rf_mod_coef, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_Rf_AD6546_SetSpecialCoef_r(const int meta_handle, unsigned int ms_timeout, const ad6546tx *rf_mod_coef, const char *buf, const int buf_len);



//--------------------------------------------------------------------------//
//  NVRAM                                                                   //
//--------------------------------------------------------------------------//

//-----------------------------------------------------//
//  NVRAM: data structure definition                   //
//-----------------------------------------------------//

// Reset NVRAM
typedef enum 
{
	NVRAM_RESET_ALL,		// Reset all data items in both of user and system category
	NVRAM_RESET_USER,		// Reset data items in user category
	NVRAM_RESET_SYSTEM,		// Reset data items in system category
	NVRAM_RESET_CERTAIN,	// Reset certain data item according to LID
	NVRAM_RESET_FACTORY		// Reset to factory default value, all the LIDs has FACTORY attribute will be reseted 
} ResetCategory;   

typedef struct
{
	ResetCategory	category;	// Reset category

	const char		*LID;		// The name of logical data item ID , it will be used
								// if and only if ResetCategory = NVRAM_RESET_CERTAIN,
								// in other case you can just assign NULL.
} FT_NVRAM_RESET_REQ;

typedef struct
{
	unsigned char   reset_status;
	unsigned char	status;		// The status of Reset
} FT_NVRAM_RESET_CNF;

// Read from NVRAM
typedef struct
{
	const char			*LID;		// The name of logical data item ID
	unsigned short 		RID;		// Record ID (the first record is 1)
} FT_NVRAM_READ_REQ;

typedef struct
{
	unsigned short		LID;		// Logical data item ID of a EF
	unsigned short		RID;		// Record ID (the first record is 1)
	unsigned char		status;		// 0: read ok; others: read failed.

	unsigned int		len;		// [IN] Length of Buffer, [OUT] Length of read data
									// The "len" field indicates the size of "buf" you 
									// allocated. When the data is read back, "len" will
									// be replaced with the actual size of the data.

	unsigned char 		*buf;		// Buffer that will contains the content of record
	unsigned char		read_status;
} FT_NVRAM_READ_CNF;

//Write to NVRAM
typedef struct
{
	const char			*LID;		// The name of logical data item ID
	unsigned short		RID;		// Record ID (the first record is 1)
	unsigned int		len;		// Length of write data
	unsigned char		*buf;		// Buffer that contains the content of record
} FT_NVRAM_WRITE_REQ;

typedef struct
{
	unsigned short		LID;		// Logical data item ID of a EF
	unsigned short		RID;		// Record ID (the first record is 1)
	unsigned char		write_status;
	unsigned char		status;		// 0: write ok; others: write failed.
} FT_NVRAM_WRITE_CNF;

// AGC path loss 
#define  PLTABLE_SIZE  13			// element count of path loss table

typedef  struct
{
   short        max_arfcn;			// The maximum ARFCN of the indicated sub-band
   char			gain_offset;		// The maximum available gain of transceiver of the indicated sub-band
} sAGCGAINOFFSET;

typedef struct
{
   sAGCGAINOFFSET     agcPathLoss[FrequencyBandCount][PLTABLE_SIZE];
}l1cal_agcPathLoss_T;

// Speech Coefficient
typedef struct {
	short		Speech_8k_Input_Coeff[30];		// FIR for input speech (microphone) with 8k sampling rate  
	short		Speech_8k_Output_Coeff[30];		// FIR for output speech (speaker) with 8k sampling rate    
	short		Speech_16k_Input_Coeff[62];		// FIR for input speech (microphone) with 16k sampling rate 
	short		Speech_16k_Output_Coeff[62];	// FIR for output speech (speaker) with 16k sampling rate   

	short		Additional_Speech_8k_Output_Coeff[5][30];	// The additional FIR for output speech (speaker) with 8k sampling rate 

	unsigned short	Speech_8k_Output_Coeff_Index;	// The active FIR index                      
													// 0 -> Speech_8k_Output_Coeff               
													// 1 -> Additional_Speech_8k_Output_Coeff[0] 
													// 2 -> Additional_Speech_8k_Output_Coeff[1] 
													// 3 -> Additional_Speech_8k_Output_Coeff[2] 
													// 4 -> Additional_Speech_8k_Output_Coeff[3] 
													// 5 -> Additional_Speech_8k_Output_Coeff[4] 
}L1_SpeechCoeff_T;

// Melody Coefficient
typedef struct {
	short		Melody_32k_Output_Coeff[45];	// FIR for melody playback with with 32k sampling rate 
}L1_MelodyCoeff_T;

// L1Audio Param
typedef struct{
	L1_SpeechCoeff_T	Speech_FIR[2];	// [0]: normal mode 
										// [1]: headset mode 
										// NOTE: In headset mode, Additional_Speech_8k_Output_Coeff and 
										//       Speech_8k_Output_Coeff_Index are ignored! you can just 
										//       leave them alone.                                      

	L1_MelodyCoeff_T	Melody_FIR[2];	// [0]: loud speaker mode 
										// [1]: stereo speaker mode 
	unsigned short		ES_TimeConst;
	unsigned short		ES_VolConst;
	unsigned short		ES_TimeConst2;
	unsigned short		ES_VolConst2;
	unsigned short		Media_Playback_Maximum_Swing;
}l1audio_param_T;

// L1Audio Param from W0547 

#define SPEECH_NORMAL_MODE			0
#define SPEECH_EARPHONE_MODE		1
#define SPEECH_LOUDSPEAKER_MODE		2
#define SPEECH_BT_ERAPHONE_MODE		3
#define SPEECH_BT_CORDLESS_MODE		4
#define SPEECH_AUX1_MODE			5
#define SPEECH_AUX2_MODE			6
#define SPEECH_AUX3_MODE			7

typedef struct{
	L1_SpeechCoeff_T	Speech_FIR[2];	// [0]: normal mode 
										// [1]: headset mode 
										// NOTE: In headset mode, Additional_Speech_8k_Output_Coeff and 
										//       Speech_8k_Output_Coeff_Index are ignored! you can just 
										//       leave them alone.                                      

	L1_MelodyCoeff_T	Melody_FIR[2];	// [0]: loud speaker mode 
										// [1]: stereo speaker mode 

	unsigned short		Speech_Common_Para[12];

	unsigned short		Speech_ModeDependent_Para[8][8];	// [0]: Normal Mode             
															// [1]: Earphone Mode           
															// [2]: Loud Speaker Mode       
															// [3]: BlueTooth Earphone Mode 
															// [4]: BlueTooth Cordless Mode 
															// [5]: AUX1 Mode               
															// [6]: AUX2 Mode               
															// [7]: AUX3 Mode               
	unsigned short		Media_Playback_Maximum_Swing;
} l1audio_param_W0547_T;


typedef struct{
	short speech_input_FIR_coeffs[6][45];
    short speech_output_FIR_coeffs[6][45];
    unsigned short selected_FIR_output_index;
    unsigned short speech_common_para[12];
    unsigned short speech_normal_mode_para[8];
    unsigned short speech_earphone_mode_para[8];
    unsigned short speech_loudspk_mode_para[8];
    unsigned short speech_bt_earphone_mode_para[8];
    unsigned short speech_bt_cordless_mode_para[8];
    unsigned short speech_aux1_mode_para[8];
    unsigned short speech_aux2_mode_para[8];
    unsigned short speech_aux3_mode_para[8];
    unsigned short Media_Playback_Maximum_Swing;
    short Melody_FIR_Output_Coeff_32k_Tbl1[45];
} l1audio_param_W0547_45_T;

typedef struct{
	short speech_input_FIR_coeffs[6][45];
    short speech_output_FIR_coeffs[6][45];
    unsigned short selected_FIR_output_index;
    unsigned short speech_common_para[12];
    unsigned short speech_normal_mode_para[8];
    unsigned short speech_earphone_mode_para[8];
    unsigned short speech_loudspk_mode_para[8];
    unsigned short speech_bt_earphone_mode_para[8];
    unsigned short speech_bt_cordless_mode_para[8];
    unsigned short speech_aux1_mode_para[8];
    unsigned short speech_aux2_mode_para[8];
    unsigned short speech_aux3_mode_para[8];
    unsigned short Media_Playback_Maximum_Swing;
    short Melody_FIR_Output_Coeff_32k_Tbl1[25];
} l1audio_param_W0712_T;


typedef struct
{
    short          speech_input_FIR_coeffs[6][45];
    short          speech_output_FIR_coeffs[6][45];
    unsigned short selected_FIR_output_index;
    unsigned short speech_common_para[12];
    unsigned short speech_mode_para[8][8];
    unsigned short Media_Playback_Maximum_Swing;
    short          Melody_FIR_Coeff_Tbl[25];
    short          audio_compensation_coeff[2][45];  // new added, so different with others structure

} l1audio_param_W0740_T;



typedef struct
{
	/* volume setting */
	char		   volume[3][7];
	/* speech enhancement */
	unsigned short speech_common_para[12];
	unsigned short speech_mode_para[8][16];
	unsigned short speech_volume_para[4];
	
	unsigned short debug_info[16];
	/* speech input FIR */
	short		   speech_input_FIR_coeffs[6][45];
	/* speech output FIR */
	short		   speech_output_FIR_coeffs[6][45];

	/* digital gain of DL speech */
	unsigned short Digi_DL_Speech;
	/* digital gain of uplink speech */
	unsigned short Digi_Microphone;
	/* FM record volume*/
	unsigned short FM_Record_Volume;	
	/* user mode : normal mode, earphone mode, loud speaker mode */
	unsigned short Bluetooth_Sync_Type;
	unsigned short Bluetooth_Sync_Length;
	unsigned short bt_pcm_in_vol;
	unsigned short bt_pcm_out_vol;
	unsigned short user_mode;
	/* auto VM record setting */
	unsigned short bSupportVM;
	unsigned short bAutoVM;
	unsigned short uMicbiasVolt;

} l1audio_param_W0809_T;

typedef struct 
{    
    unsigned int bes_loudness_hsf_coeff[9][4];
    unsigned int bes_loudness_bpf_coeff[4][6][3];
    // BesLoudness V3
    unsigned int besloudness_DRC_Forget_Table[9][2];
    unsigned int besloudness_WS_Gain_Max;
    unsigned int besloudness_WS_Gain_Min;
    unsigned int besloudness_Filter_First;
    char         besloudness_Gain_Map_In[5];
    char         besloudness_Gain_Map_Out[5];
    
}l4aud_acf_param;



// crystalAfcData
#define XO_SlopeArea_Num       33  // change from 8 to 33, 8 is obsolete

typedef struct {
	int		min_freq;
	short	min_dac;
	int		inv_slope;
}XO_SLOPE_AREA_DATA;

typedef struct {  
	XO_SLOPE_AREA_DATA		XO_SlopeAreaData[XO_SlopeArea_Num]; 
}l1cal_crystalAfcData_T;

// IMEISV
typedef struct {
	char			imei[16];
	unsigned char	svn;
	unsigned char	pad;
}IMEISV_struct_T;

// Custom Acoustic Volume
#define MAX_VOL_CATE		3
#define MAX_VOL_TYPE		7
#define MAX_VOL_LEVEL		7
typedef struct {
	unsigned char	volume_gain[MAX_VOL_CATE][MAX_VOL_TYPE][MAX_VOL_LEVEL];
	// Volume Gain:	[Mode (Normal, Headset, LoudSpeaker)]									
	//				[Tone type (CallTone, Keytone, MIC, GMI, Speech, SideTone, Melody) ]	
	//				[Level (1~7)]															

	unsigned char	volume[MAX_VOL_CATE][MAX_VOL_TYPE];
	// Current Volume Level:	[Mode (Normal, Headset, LoudSpeaker)]									
	//							[Tone type (CallTone, Keytone, MIC, GMI, Speech, SideTone, Melody) ]	
	//							value: 0~6 [ Level_1(0) ~ Level_7(6) ]
   	
} CustAcousticVol_T;
typedef struct {
	unsigned char	volume_gain[MAX_VOL_CATE][MAX_VOL_TYPE][MAX_VOL_LEVEL];
	// Volume Gain:	[Mode (Normal, Headset, LoudSpeaker)]									
	//				[Tone type (CallTone, Keytone, MIC, GMI, Speech, SideTone, Melody) ]	
	//				[Level (1~7)]															

	unsigned char	volume[MAX_VOL_CATE][MAX_VOL_TYPE];
	// Current Volume Level:	[Mode (Normal, Headset, LoudSpeaker)]									
	//							[Tone type (CallTone, Keytone, MIC, GMI, Speech, SideTone, Melody) ]	
	//							value: 0~6 [ Level_1(0) ~ Level_7(6) ]
   	unsigned char max_melody_volume_gain[MAX_VOL_CATE + 1];
    unsigned char melody_volume_gain_step[MAX_VOL_CATE + 1];
    unsigned char tv_out_volume_gain[MAX_VOL_LEVEL];
} CustAcousticVol16lvl_T;

// S/W Change 
typedef enum {
	LID_VER_SAME = 0,
	LID_VER_CHANGED
}LID_STATUS;

typedef struct {
	int		OldVer;
	int		NewVer;
	char	LID[64];
}LID_Info;

typedef struct {
   int		target_nvramsize;	// current NVRAM size on target FAT file system
   int		target_freespace;	// current freespace of target FAT file system
   int		target_overhead;	// S/W upgrade operation overhead
   int		newdb_nvramsize;	// new NVRAM size
   unsigned char	status;		// 0 -> [OK] safe to upgrade to new NVRAM
   								// 1 -> [ERROR] can't retrieve info from target
   								// 2 -> [ERROR] freespace is not enough to upgrade to new NVRAM
} NVRAM_GetDiskInfo_Cnf;

// WiFi 
typedef struct {
	unsigned char	mac_addr[6];
} WiFi_MacAddress_S;

typedef struct {
	unsigned char	CCKTxPWR[14]; 
	unsigned char	OFDMTxPWR[14]; 
} WiFi_TxPower_2400M_S;

typedef struct {
	unsigned char	TxPWR[34]; 
} WiFi_TxPower_5000M_S;

typedef struct {
	unsigned char	i_ch_offset;
	unsigned char	q_ch_offset;
} WiFi_DAC_DC_Offset_S;

typedef struct {
	unsigned char txAlcCCK[14];
    unsigned char txOutputPowerDBCCK[14];
    unsigned char txAlcOFDM [8][14];
    unsigned char txOutputPowerDBOFDM[8][14];
} WiFi_ALC_2400M_S;

typedef struct
{
    unsigned char alcSlop1Divider;
    unsigned char alcSlop1Dividend;
    unsigned char alcSlop2Divider;
    unsigned char alcSlop2Dividend;
} WiFi_TxALC_2400M_S;
typedef struct
{
   unsigned char BluetoothAddress[6];
   unsigned char MinEncryptionSize[1];
   unsigned char MaxEncryptionSize[1];
   unsigned char HCITransportLayerParameters[3];
   unsigned char FixedPIN[16];
   unsigned char FixedPINLength[1];
   unsigned char SleepEnableMask[1];
   unsigned char LowPowerClockParameter[8];
   unsigned char PowerControlConfiguration[13];
   unsigned char SleepControlParameters[12];
   unsigned char DebugControl[4];
   unsigned char LCandRMOverrideEnable[4];
   unsigned char RadioRegisterOverride[6];
   unsigned char CodecConfiguration[8];
   unsigned char CVSDGainVolumeSettings[6];
   unsigned char VoiceSettings[2];
   unsigned char UserBaudRate[3];

   unsigned char LowPowerDriftRate[1];
   unsigned char MaxTxPowerLevel[1];
   unsigned char AdaptiveFrequencyHoppingParameters[29];
   unsigned char BufferSize[4];
   unsigned char GpioMapping[16];
   unsigned char GpioPolarity[4];
}  nvram_ef_btradio_rfmd3500_struct;

typedef struct
{
    unsigned char BDAddr[6];
    unsigned char ClassOfDevice[3];
    unsigned char LinkKeyType[1];
    unsigned char UnitKey[16];
    unsigned char Encryption[3];
    unsigned char PinCodeType[1];
    unsigned char Voice[2];
    unsigned char Codec[1];
    unsigned char Radio[30];
    unsigned char Sleep[6];
    unsigned char MainOscillatorInfo[5];
    unsigned char LPOInfo[4];
    unsigned char AFH[9];
    unsigned char PTA[49];
    unsigned char WDT[2];
    unsigned char Debug[1];
    unsigned char UART[2];
}  nvram_ef_btradio_mt6601_struct;


typedef struct
{
	unsigned char addr[6];
	unsigned char CapId[1];
	unsigned char LinkKeyType[1];
	unsigned char UnitKey[16];
	unsigned char Encryption[3];
	unsigned char PinCodeType[1];
	unsigned char Voice[2];
	unsigned char Codec[2];
	unsigned char Radio[6];
	unsigned char Sleep[7];
	unsigned char Reserved[2];
}nvram_ef_btradio_mt6611_struct;

//-----------------------------------------------------//
//  NVRAM: callback function definition                //
//-----------------------------------------------------//
typedef void (__stdcall *META_NVRAM_Reset_CNF)(const FT_NVRAM_RESET_CNF *cnf, const short token, void *usrData);
typedef void (__stdcall *META_NVRAM_Read_CNF)(const FT_NVRAM_READ_CNF *cnf, const short token, void *usrData);
typedef void (__stdcall *META_NVRAM_Write_CNF)(const FT_NVRAM_WRITE_CNF *cnf, const short token, void *usrData);
typedef void (__stdcall *CB_META_NVRAM_GET_DISK_INFO_CNF)(const NVRAM_GetDiskInfo_Cnf *cnf, const short token, void *usrData);

//-----------------------------------------------------//
//  NVRAM: exported function definition                //
//-----------------------------------------------------//
META_RESULT  __stdcall SP_META_NVRAM_Init(const char *PathName, unsigned long *p_nvram_CatcherTranAddr);
META_RESULT  __stdcall SP_META_NVRAM_Init_r(const int meta_handle,const char *PathName, unsigned long *p_nvram_CatcherTranAddr);
META_RESULT  __stdcall SP_META_NVRAM_Reset(const FT_NVRAM_RESET_REQ *req, const META_NVRAM_Reset_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_NVRAM_Reset_r(const int meta_handle, const FT_NVRAM_RESET_REQ *req, const META_NVRAM_Reset_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_NVRAM_Read(const FT_NVRAM_READ_REQ *req, FT_NVRAM_READ_CNF *cnf, const META_NVRAM_Read_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_NVRAM_Read_r(const int meta_handle, const FT_NVRAM_READ_REQ *req, FT_NVRAM_READ_CNF *cnf, const META_NVRAM_Read_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_NVRAM_Write(const FT_NVRAM_WRITE_REQ *req, const META_NVRAM_Write_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_NVRAM_Write_r(const int meta_handle, const FT_NVRAM_WRITE_REQ *req, const META_NVRAM_Write_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_NVRAM_GetAllLIDNameLength(int *len);
META_RESULT  __stdcall SP_META_NVRAM_GetAllLIDName(char *buf, const int buf_len, int *NofLID);
META_RESULT  __stdcall SP_META_NVRAM_GetLIDVersion(const char *LID,unsigned short *ver);
META_RESULT  __stdcall SP_META_NVRAM_GetRecStructNameLength(const char *LID, int *len);
META_RESULT  __stdcall SP_META_NVRAM_GetRecStructName(const char *LID, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_GetAllRecFieldNameLength(const char *LID, int *len);
META_RESULT  __stdcall SP_META_NVRAM_GetAllRecFieldName(const char *LID, char *buf, const int buf_len, int *NofField);
META_RESULT  __stdcall SP_META_NVRAM_CheckFieldNameExist(const char *LID, const char *Field, bool *result);
META_RESULT  __stdcall SP_META_NVRAM_GetRecNum(const char *LID, int *num);
META_RESULT  __stdcall SP_META_NVRAM_GetRecLen(const char *LID, int *len);
META_RESULT  __stdcall SP_META_NVRAM_SetRecFieldValue(const char *LID, const char *field, char *buf, const int buf_len, void *value, const int value_len);
META_RESULT  __stdcall SP_META_NVRAM_GetRecFieldValue(const char *LID, const char *field, const char *buf, const int buf_len, void *value, const int value_len);
META_RESULT  __stdcall SP_META_NVRAM_SetRecFieldBitValue(const char *LID, const char *field, const char *bitname, char *buf, const int buf_len, const int bitvalue);
META_RESULT  __stdcall SP_META_NVRAM_GetRecFieldBitValue(const char *LID, const char *field, const char *bitname, const char *buf, const int buf_len, int *bitvalue);
META_RESULT  __stdcall SP_META_NVRAM_QueryIsLIDExist(const char *LID);
META_RESULT  __stdcall SP_META_NVRAM_ResetToFactoryDefault(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_NVRAM_ResetToFactoryDefault_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_NVRAM_LockDown(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_NVRAM_LockDown_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_NVRAM_OTP_LockDown(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_NVRAM_OTP_LockDown_r(const int meta_handle, unsigned int ms_timeout);

// S/W Change
META_RESULT  __stdcall SP_META_NVRAM_SWC_RetrieveChangeList(void);
META_RESULT  __stdcall SP_META_NVRAM_SWC_RetrieveChangeList_r(const int meta_handle);
META_RESULT  __stdcall SP_META_NVRAM_SWC_UpdateChangeList(void);
META_RESULT  __stdcall SP_META_NVRAM_SWC_UpdateChangeList_r(const int meta_handle);
META_RESULT  __stdcall SP_META_NVRAM_SWC_GetAllChangedLIDCount(int *NofLID);
META_RESULT  __stdcall SP_META_NVRAM_SWC_GetAllChangedLIDCount_r(const int meta_handle, int *NofLID);
META_RESULT  __stdcall SP_META_NVRAM_SWC_GetAllChangedLIDName(LID_Info *p_ArrayOfLID, const int NofLID);
META_RESULT  __stdcall SP_META_NVRAM_SWC_GetAllChangedLIDName_r(const int meta_handle, LID_Info *p_ArrayOfLID, const int NofLID);
META_RESULT  __stdcall SP_META_NVRAM_SWC_QueryIfLIDChanged(const char *LID, LID_STATUS  *result);
META_RESULT  __stdcall SP_META_NVRAM_SWC_QueryIfLIDChanged_r(const int meta_handle, const char *LID, LID_STATUS  *result);
META_RESULT  __stdcall SP_META_NVRAM_SWC_ImportData(LID_Info *p_import_multiple_lid, int num_of_import_multiple_lid, int import_1st_sys_record_size );
META_RESULT  __stdcall SP_META_NVRAM_SWC_ImportData_r(const int meta_handle, LID_Info *p_import_multiple_lid, int num_of_import_multiple_lid, int import_1st_sys_record_size );
META_RESULT  __stdcall SP_META_NVRAM_SWC_Database_Compare(const char *PathName, int *p_NumOfNewAddLID, int *p_NumOfModifiedLID, int *p_NumOfDeletedLID);
META_RESULT  __stdcall SP_META_NVRAM_SWC_Database_Compare_r(const int meta_handle, const char *PathName, int *p_NumOfNewAddLID, int *p_NumOfModifiedLID, int *p_NumOfDeletedLID);
META_RESULT  __stdcall SP_META_NVRAM_SWC_Get_Database_Compare_Result(LID_Info *p_ArrayOfNewAddLID, const int NumOfNewAddLID, LID_Info *p_ArrayOfModifiedLID, const int NumOfModifiedLID, LID_Info *p_ArrayOfDeletedLID, const int NumOfDeletedLID);
META_RESULT  __stdcall SP_META_NVRAM_SWC_Get_Database_Compare_Result_r(const int meta_handle, LID_Info *p_ArrayOfNewAddLID, const int NumOfNewAddLID, LID_Info *p_ArrayOfModifiedLID, const int NumOfModifiedLID, LID_Info *p_ArrayOfDeletedLID, const int NumOfDeletedLID);
META_RESULT  __stdcall SP_META_NVRAM_SWC_Check_FAT_FreeSpace(const CB_META_NVRAM_GET_DISK_INFO_CNF  cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_NVRAM_SWC_Check_FAT_FreeSpace_r(const int meta_handle, const CB_META_NVRAM_GET_DISK_INFO_CNF  cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_NVRAM_SWC_Enable_ForceUpgrade(void);
META_RESULT  __stdcall SP_META_NVRAM_SWC_Enable_ForceUpgrade_r(const int meta_handle);
META_RESULT  __stdcall SP_META_NVRAM_SWC_Disable_ForceUpgrade(void);
META_RESULT  __stdcall SP_META_NVRAM_SWC_Disable_ForceUpgrade_r(const int meta_handle);

META_RESULT  __stdcall SP_META_NVRAM_Compose_AudioBesLoudNess(const l4aud_acf_param *param, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_AudioBesLoudNess(l4aud_acf_param *param, const char *buf, const int buf_len);

// AGC path loss 
META_RESULT  __stdcall SP_META_NVRAM_agcPathLoss_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_agcPathLoss(const l1cal_agcPathLoss_T *loss, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_agcPathLoss(l1cal_agcPathLoss_T *loss, const char *buf, const int buf_len);

META_RESULT  __stdcall SP_META_NVRAM_rampTable_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_rampTable(const l1cal_rampTable_T *tbl, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_rampTable(l1cal_rampTable_T *tbl, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_rampTable_Len_Ex(int *len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_rampTable_Ex(const l1cal_rampTable_T_Ex *tbl, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_rampTable_Ex(l1cal_rampTable_T_Ex *tbl, const char *buf, const int buf_len);

// rampTable
META_RESULT  __stdcall SP_META_NVRAM_rampTable_Len_Ex2(int *len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_rampTable_Ex2(const l1cal_rampTable_T_Ex2 *tbl, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_rampTable_Ex2(l1cal_rampTable_T_Ex2 *tbl, const char *buf, const int buf_len);

// L1Audio Param
META_RESULT  __stdcall SP_META_NVRAM_AudioParam_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_AudioParam(const l1audio_param_T *param, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_AudioParam(l1audio_param_T *param, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_If_AudioParam_W0547_Support(void);
META_RESULT  __stdcall SP_META_NVRAM_Compose_AudioParam_W0547(const l1audio_param_W0547_T *param, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_AudioParam_W0547(l1audio_param_W0547_T *param, const char *buf, const int buf_len);

META_RESULT  __stdcall SP_META_NVRAM_Compose_AudioParam_W0547_45(const l1audio_param_W0547_45_T *param, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_AudioParam_W0547_45(l1audio_param_W0547_45_T *param, const char *buf, const int buf_len);

META_RESULT  __stdcall SP_META_NVRAM_Compose_AudioParam_W0712(const l1audio_param_W0712_T *param, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_AudioParam_W0712(l1audio_param_W0712_T *param, const char *buf, const int buf_len);
// interRampData
META_RESULT  __stdcall SP_META_NVRAM_interRampData_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_interRampData(const l1cal_interRampData_T *tbl, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_interRampData(l1cal_interRampData_T *tbl, const char *buf, const int buf_len);
// crystalAfcData
META_RESULT  __stdcall SP_META_NVRAM_crystalAfcData_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_crystalAfcData(const l1cal_crystalAfcData_T *xo_afc, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_crystalAfcData(l1cal_crystalAfcData_T *xo_afc, const char *buf, const int buf_len);
// IMEISV
META_RESULT  __stdcall SP_META_NVRAM_Calculate_IMEI_CD(const char *imei, unsigned short *p_cd);
META_RESULT  __stdcall SP_META_NVRAM_IMEISV_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_IMEISV(const IMEISV_struct_T  *p_imeisv, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_IMEISV_NoCheck(const IMEISV_struct_T  *p_imeisv, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_IMEISV_ex(const IMEISV_struct_T  *p_imeisv, char *buf, const int buf_len,bool DoCheckSum);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_IMEISV(IMEISV_struct_T  *p_imeisv, const char *buf, const int buf_len);

// Custom Acoustic Volume
META_RESULT  __stdcall SP_META_NVRAM_CustAcousticVol_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_CustAcousticVol(const CustAcousticVol_T *cust_acoustic_vol, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_CustAcousticVol(CustAcousticVol_T *cust_acoustic_vol, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_16lvlCustAcousticVol(const CustAcousticVol16lvl_T *cust_acoustic_vol, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_16lvlCustAcousticVol(CustAcousticVol16lvl_T *cust_acoustic_vol, const char *buf, const int buf_len);
// RF Module Configuration 
META_RESULT  __stdcall SP_META_NVRAM_RFSpecialCoef_Len(int *len);
// Skyworks 
META_RESULT  __stdcall SP_META_NVRAM_Compose_SKY74045_RFSpecialCoef(const RF_SKY74045_Coef_T *rf_mod_coef, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_SKY74045_RFSpecialCoef(RF_SKY74045_Coef_T *rf_mod_coef, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_SKY74117_RFSpecialCoef(const RF_SKY74117_Coef_T *rf_mod_coef, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_SKY74117_RFSpecialCoef(RF_SKY74117_Coef_T *rf_mod_coef, const char *buf, const int buf_len);
// MT6139B 
META_RESULT  __stdcall SP_META_NVRAM_Compose_MT6139B_RFSpecialCoef(const RF_MT6139B_Coef_T *rf_mod_coef, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_MT6139B_RFSpecialCoef(RF_MT6139B_Coef_T *rf_mod_coef, const char *buf, const int buf_len);
// MT6140
META_RESULT  __stdcall SP_META_NVRAM_Compose_MT6140tx_RFSpecialCoef(const mt6140tx *rf_mod_coef, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_MT6140tx_RFSpecialCoef(mt6140tx *rf_mod_coef, const char *buf, const int buf_len);

META_RESULT  __stdcall SP_META_NVRAM_Compose_MT6140tx_PaVbias(const mt6140tx *pavbias, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_MT6140tx_PaVbias(mt6140tx *pavbias, const char *buf, const int buf_len);

// Renesas Bright5P 
META_RESULT  __stdcall SP_META_NVRAM_Compose_BRIGHT5P_RFSpecialCoef(const RF_BRIGHT5P_Coef_T *rf_mod_coef, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_BRIGHT5P_RFSpecialCoef(RF_BRIGHT5P_Coef_T *rf_mod_coef, const char *buf, const int buf_len);
// EPSK interRampData 
META_RESULT  __stdcall SP_META_NVRAM_EPSK_interRampData_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_EPSK_interRampData(const l1cal_EPSK_interRampData_T *tbl, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_EPSK_interRampData(l1cal_EPSK_interRampData_T *tbl, const char *buf, const int buf_len);

META_RESULT  __stdcall SP_META_NVRAM_WiFi_MacAddress_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Compose_MacAddress(const WiFi_MacAddress_S  *mac, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Decompose_MacAddress(WiFi_MacAddress_S  *mac, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_TxPower2400M_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Compose_TxPower2400M(const WiFi_TxPower_2400M_S  *txpwr, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Decompose_TxPower2400M(WiFi_TxPower_2400M_S  *txpwr, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_TxPower5000M_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Compose_TxPower5000M(const WiFi_TxPower_5000M_S  *txpwr, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Decompose_TxPower5000M(WiFi_TxPower_5000M_S  *txpwr, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_DacDcOffset_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Compose_DacDcOffset(const WiFi_DAC_DC_Offset_S  *dac, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Decompose_DacDcOffset(WiFi_DAC_DC_Offset_S  *dac, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Compose_ALC_2400M(const WiFi_ALC_2400M_S  *alc, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Decompose_ALC_2400M(WiFi_ALC_2400M_S  *alc, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_ALC_2400M_Len(int *len);

META_RESULT  __stdcall SP_META_NVRAM_WiFi_TxALC2400M_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Compose_TxALC2400M(const WiFi_TxALC_2400M_S  *txalc, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_WiFi_Decompose_TxALC2400M(WiFi_TxALC_2400M_S  *txalc, const char *buf, const int buf_len);

META_RESULT  __stdcall SP_META_NVRAM_3G_Compose_tempdacData(const ul1cal_tempdacData_T  *dac, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_3G_Decompose_tempdacData(ul1cal_tempdacData_T  *dac, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_3G_Compose_pathlossData(const ul1cal_pathlossData_T  *pathloss, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_3G_Decompose_pathlossData(ul1cal_pathlossData_T  *pathloss, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_3G_Compose_txdacData(const ul1cal_txdacData_T  *txdac, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_3G_Decompose_txdacData(ul1cal_txdacData_T  *txdac, const char *buf, const int buf_len);

//BT
META_RESULT  __stdcall SP_META_NVRAM_BT_Compose_RFMD3500Radio(const nvram_ef_btradio_rfmd3500_struct  *radio, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_BT_Decompose_RFMD3500Radio(nvram_ef_btradio_rfmd3500_struct  *radio, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_BT_Compose_MT6601Radio(const nvram_ef_btradio_mt6601_struct  *radio, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_BT_Decompose_MT6601Radio(nvram_ef_btradio_mt6601_struct  *radio, const char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_BT_Compose_MT6611Radio(const nvram_ef_btradio_mt6611_struct  *radio, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_BT_Decompose_MT6611Radio(nvram_ef_btradio_mt6611_struct  *radio, const char *buf, const int buf_len);

// sBBTxParameters
META_RESULT  __stdcall SP_META_NVRAM_BBTXParameters_Len(int *len);
META_RESULT  __stdcall SP_META_NVRAM_Compose_BBTXParameters(const BBTXParameters_T *bbtx, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_BBTXParameters(BBTXParameters_T *bbtx, const char *buf, const int buf_len);
//l1audio_param_W0740_T
META_RESULT  __stdcall SP_META_NVRAM_Compose_AudioParam_W0740(const l1audio_param_W0740_T *param, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_AudioParam_W0740(l1audio_param_W0740_T *param, const char *buf, const int buf_len);
// l1audio_param_W0809_T
META_RESULT  __stdcall SP_META_NVRAM_Compose_AudioParam_W0809(const l1audio_param_W0809_T *param, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_AudioParam_W0809(l1audio_param_W0809_T *param, const char *buf, const int buf_len);
// ad6546tx
META_RESULT  __stdcall SP_META_NVRAM_Compose_ad6546tx(const ad6546tx *adtx, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_ad6546tx(ad6546tx *adtx, const char *buf, const int buf_len);


//--------------------------------------------------------------------------//
//  Audio Testing                                                           //
//--------------------------------------------------------------------------//

//-----------------------------------------------------//
//  Audio Testing: data structure definition           //
//-----------------------------------------------------//

// audio testing result
typedef enum  {
	AUD_RES_OK = 0,						// OK 
	AUD_RES_FAIL,						// General Fail 
	AUD_RES_BUSY,						// system busy 
	AUD_RES_DISC_FULL,					// Memory full 
	AUD_RES_OPEN_FILE_FAIL,				// open file fail 
	AUD_RES_END_OF_FILE,				// play finish 
	AUD_ERR_OP_NOT_SUPPORT = 0xFB,       // added by ShuMin, for error handler enhancements// filepath too long
	AUD_ERR_STILL_PLAYING = 0xFC,       // added by ShuMin, because I found target had this error value
	AUD_ERR_PEER_BUF_ERROR = 0xFD,		// peer buf error 
	AUD_ERR_FILEPATH_ERROR = 0xFE,		// filepath error 
	AUD_ERR_FILEPATH_TOO_LONG = 0xFF	// filepath too long 
}AUDIO_RESULT;

// play style enum 
typedef enum {
	FT_L4AUD_AUDIO_PLAY_CRESCENDO = 0,	// Play sound for crescendo. 
	FT_L4AUD_AUDIO_PLAY_INFINITE,		// Play sound for infinite. 
	FT_L4AUD_AUDIO_PLAY_ONCE,			// Play sound for once. 
	FT_L4AUD_AUDIO_PLAY_DESCENDO		// Play sound for descendo. 
}AUDIO_PLAY_STYLE;

// default system embeded audio id query 
typedef struct {
	unsigned short		MinRingTone_ID;
	unsigned short		MaxRingTone_ID;
	unsigned short		MinMIDI_ID;
	unsigned short		MaxMIDI_ID;
	unsigned short		MinSound_ID;
	unsigned short		MaxSound_ID;
	AUDIO_RESULT		status;
}Audio_Query_ID_Cnf;

// play default system embeded audio by the given audio id 
typedef struct {
	unsigned short		audio_id;		// default system embeded audio id 
	AUDIO_PLAY_STYLE	play_style;		// play style 
}Audio_Play_Req;

// play audio from FAT by the given filepath 
typedef struct {
	const char			*fat_filepath;	// filepath on target FAT file system 
	AUDIO_PLAY_STYLE	play_style;		// play style 
}Audio_Play_ByName_Req;

// play imelody by the buffer from PC side 
typedef struct {
	const char			*imy_buf;		// buffer that stores iMelody content 
	unsigned int		imy_buf_len;	// length of buffer 
	unsigned char		imy_instrument;	// instrument id, 1 ~ 128 
	AUDIO_PLAY_STYLE	play_style;		// play style 
}Audio_Play_IMY_ByBuf_Req;

// play mp3 from FAT by the given filepath 
typedef struct {
	const char			*fat_filepath;	// filepath on target FAT file system 
	AUDIO_PLAY_STYLE	play_style;		// play style 
}Audio_MEDIA_Play_Req;

// set volume 
typedef struct {
	unsigned char		volume;			// play volume, 0 ~ 255 
}Audio_Set_Volume_Req;

typedef struct {
	unsigned char		echoflag;			// echofalg true
}Audio_Set_Echo_Req;

typedef struct {
	unsigned char		modeflag;			// modeflag
}Audio_Set_Mode_Req;

typedef struct {
	unsigned char		type;
	unsigned char		gain;
}Audio_Set_Gain_Req;

typedef struct {
	short		in_fir_coeffs[45];
	short		out_fir_coeffs[45];
}Audio_Set_LoudSpk_FIR_Coeffs_Req;

/*
typedef struct
{
	unsigned int     bes_loudness_hsf_coeff[9][4];
	unsigned int     bes_loudness_bpf_coeff[4][6][3];
	// BesLoudness V3
	unsigned int besloudness_DRC_Forget_Table[9][2];
	unsigned int besloudness_WS_Gain_Max;
	unsigned int besloudness_WS_Gain_Min;
	unsigned int besloudness_Filter_First;
	char         besloudness_Gain_Map_In[5];
	char         besloudness_Gain_Map_Out[5];
	
}Audio_Ex_SetACFToTarget_REQ_T;
*/





typedef struct {
	unsigned short speech_common_para[12];  // 8 or 12, so at most 12
}Audio_Set_Speech_Common_Req;

typedef struct {
	unsigned short speech_loudspk_mode_para[16];  // change from 8 to 16, because at most: 16
}Audio_Set_LoudSpk_Mode_Req;

typedef struct {
	unsigned short Media_Playback_Maximum_Swing;
}Audio_Set_Playback_Maximum_Swing_Req;

typedef struct {
	short Melody_FIR_Output_Coeff_32k_Tbl1[25];
}Audio_Set_Melody_FIR_Output_Coeffs_Req;

typedef struct {
	unsigned short speech_common_para[12];
	unsigned short speech_loudspk_mode_para[16];  // change from 8 to 16, because at most: 16
}Audio_Set_Speech_Common_And_Mode_Req;

typedef struct {
	unsigned short		fre;
	unsigned char		spkgain;
	unsigned char		micgain;
	unsigned short      ulgain; 
	unsigned short      dlgain;
	unsigned short      amp;
    
}Audio_Tone_LoopBackRec_Req;

typedef struct {
	unsigned int		buffer[2000];
}Audio_Tone_LoopBackRec_Cnf;

typedef struct {
	unsigned int		buffer[500];
}Audio_Tone_LoopBackRec_Cnf_2K;

typedef struct
{
	unsigned char  m_ucVolume;
	unsigned short m_u2Freq;
}Audio_Set_Freq_Vol_Tone_Req_T;

typedef struct
{
	unsigned char  m_ucMode;
}Audio_Get_Profile_Settings_By_Mode_Req_T;

typedef struct
{
	unsigned char mode;
    unsigned char melody[7];         
    unsigned char sound[7];          
    unsigned char keytone[7];         
    unsigned char speech[7];         
    unsigned char mic[7];           
    unsigned char sidetone;         
    unsigned char max_melody_volume_gain;
    unsigned char melody_volume_gain_step;
    unsigned char tv_out_volume_gain[MAX_VOL_LEVEL];  // 7 here

}Audio_Get_Profile_Settings_By_Mode_Cnf_T;

typedef struct
{
	unsigned char mode;
    unsigned char melody[7];         
    unsigned char sound[7];          
    unsigned char keytone[7];         
    unsigned char speech[7];         
    unsigned char mic[7];           
    unsigned char sidetone;         
    unsigned char max_melody_volume_gain;
    unsigned char melody_volume_gain_step;
    unsigned char tv_out_volume_gain[MAX_VOL_LEVEL];  // 7 here

}Audio_Set_Profile_Settings_By_Mode_Req_T;

typedef struct
{
    
    unsigned short m_u2FailReason;  // possible fail resons

}Audio_Set_Profile_Settings_By_Mode_Cnf_T;


typedef struct
{
    unsigned short m_u2FailReason;  // possible fail resons, (2 means the format is not matched with Target side)
}Audio_Set_Param_Cnf_T;

typedef	struct
{
	char	receiver_test;		// receiver_test true mean enable
}ft_l4aud_receiver_test;

typedef	struct
{
	char	left_channel;		// true mean enable
	char	right_channel;		// true mean enable
}ft_l4aud_loudspk;




//For Dual Mic

typedef enum 
{
    RECORD_ERROR = 0,
    RECORD_START,
    RECORD_END,
    NUM_RECORD_STATES
    
}AUDIO_RECORD_STATES_E;


typedef struct
{
    char fileName[256];
    
}AUDIO_DL_PLAYBACK_FILE_REQ_S;

typedef struct
{
    char fileName[256];
    int duration;	  /* record duration */
    
}AUDIO_DUALMIC_RECORD_REQ_S;

typedef struct
{
    char playbackFileName[256];	
    char recordingFileName[256];
    int recordDuration;
    
}AUDIO_PLAYBACK_DUALMICRECORD_REQ_S;

typedef struct
{
    char pcFileName[256];
    char tgFileName[256];
    
}AUDIO_LOAD_FILE_REQ_S;

typedef struct
{
    int value;
    
}AUDIO_PARAM_VALUE_S;

//-----------------------------------------------------//
//  API function definition for Dual Mic       //
//-----------------------------------------------------//

META_RESULT  __stdcall SP_META_Audio_SetPlaybackFile(unsigned int  ms_timeout, const AUDIO_DL_PLAYBACK_FILE_REQ_S  *req);
META_RESULT  __stdcall SP_META_Audio_SetPlaybackFile_r(const int meta_handle, unsigned int  ms_timeout, const AUDIO_DL_PLAYBACK_FILE_REQ_S  *req);
META_RESULT  __stdcall SP_META_Audio_DualMicRecord(unsigned int  ms_timeout, const AUDIO_DUALMIC_RECORD_REQ_S *req, AUDIO_RECORD_STATES_E * cnf);
META_RESULT  __stdcall SP_META_Audio_DualMicRecord_r(const int meta_handle, unsigned int  ms_timeout, const AUDIO_DUALMIC_RECORD_REQ_S *req, AUDIO_RECORD_STATES_E * cnf);
META_RESULT  __stdcall SP_META_Audio_PlaybackDualMicRecord(unsigned int  ms_timeout, const AUDIO_PLAYBACK_DUALMICRECORD_REQ_S *req, AUDIO_RECORD_STATES_E * cnf);
META_RESULT  __stdcall SP_META_Audio_PlaybackDualMicRecord_r(const int meta_handle, unsigned int  ms_timeout, const AUDIO_PLAYBACK_DUALMICRECORD_REQ_S *req, AUDIO_RECORD_STATES_E * cnf);
META_RESULT  __stdcall SP_META_Audio_StopDualMicRecord(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_Audio_StopDualMicRecord_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_Audio_DownloadFile(unsigned int  ms_timeout, const AUDIO_LOAD_FILE_REQ_S  *req);
META_RESULT  __stdcall SP_META_Audio_DownloadFile_r(const int meta_handle, unsigned int  ms_timeout, const AUDIO_LOAD_FILE_REQ_S  *req);
META_RESULT  __stdcall SP_META_Audio_UploadFile(unsigned int  ms_timeout, const AUDIO_LOAD_FILE_REQ_S  *req);
META_RESULT  __stdcall SP_META_Audio_UploadFile_r(const int meta_handle, unsigned int  ms_timeout, const AUDIO_LOAD_FILE_REQ_S  *req);
META_RESULT  __stdcall SP_META_Audio_GetRecordingGain(unsigned int  ms_timeout, AUDIO_PARAM_VALUE_S * cnf);
META_RESULT  __stdcall SP_META_Audio_GetRecordingGain_r(const int meta_handle, unsigned int  ms_timeout, AUDIO_PARAM_VALUE_S * cnf);
META_RESULT  __stdcall SP_META_Audio_SetRecordingGain(unsigned int  ms_timeout, AUDIO_PARAM_VALUE_S * req);
META_RESULT  __stdcall SP_META_Audio_SetRecordingGain_r(const int meta_handle, unsigned int  ms_timeout, AUDIO_PARAM_VALUE_S * req);
META_RESULT  __stdcall SP_META_Audio_GetPlaybackGain(unsigned int  ms_timeout, AUDIO_PARAM_VALUE_S * cnf);
META_RESULT  __stdcall SP_META_Audio_GetPlaybackGain_r(const int meta_handle, unsigned int  ms_timeout, AUDIO_PARAM_VALUE_S * cnf);
META_RESULT  __stdcall SP_META_Audio_SetPlaybackGain(unsigned int  ms_timeout, AUDIO_PARAM_VALUE_S * req);
META_RESULT  __stdcall SP_META_Audio_SetPlaybackGain_r(const int meta_handle, unsigned int  ms_timeout, AUDIO_PARAM_VALUE_S * req);



META_RESULT  __stdcall SP_META_Audio_QueryRecordStatus(AUDIO_RECORD_STATES_E * pStates);
META_RESULT  __stdcall SP_META_Audio_QueryRecordStatus_r(const int meta_handle, AUDIO_RECORD_STATES_E * pStates);



//-----------------------------------------------------//
//  Audio Testing: callback function definition        //
//-----------------------------------------------------//
typedef void (__stdcall *META_AUDIO_QUERY_ID_CNF)(const Audio_Query_ID_Cnf *cnf, const short token, void *usrData);
typedef void (__stdcall *META_AUDIO_PLAY_CNF)(const AUDIO_RESULT status, const short token, void *usrData);
typedef void (__stdcall *META_AUDIO_PLAY_BYNAME_CNF)(const AUDIO_RESULT status, const short token, void *usrData);
typedef void (__stdcall *META_AUDIO_PLAY_IMY_BYBUF_CNF)(const AUDIO_RESULT status, const short token, void *usrData);
typedef void (__stdcall *META_AUDIO_PLAY_OVER_IND)(const AUDIO_RESULT status, const short token, void *usrData);
typedef void (__stdcall *META_AUDIO_STOP_CNF)(const AUDIO_RESULT status, const short token, void *usrData);
typedef void (__stdcall *META_AUDIO_MEDIA_PLAY_CNF)(const AUDIO_RESULT status, const short token, void *usrData);
typedef void (__stdcall *META_AUDIO_MEDIA_PLAY_OVER_IND)(const AUDIO_RESULT status, const short token, void *usrData);
typedef void (__stdcall *META_AUDIO_MEDIA_STOP_CNF)(const AUDIO_RESULT status, const short token, void *usrData);
typedef void (__stdcall *META_AUDIO_SET_VOLUME_CNF)(const AUDIO_RESULT status, const short token, void *usrData);

//-----------------------------------------------------//
//  Audio Testing: exported function definition        //
//-----------------------------------------------------//

META_RESULT  __stdcall SP_META_Audio_Query_ID(const META_AUDIO_QUERY_ID_CNF  cnf_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Query_ID_r(const int meta_handle, const META_AUDIO_QUERY_ID_CNF  cnf_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Play(const Audio_Play_Req  *req, const META_AUDIO_PLAY_CNF cnf_cb, const META_AUDIO_PLAY_OVER_IND  ind_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Play_r(const int meta_handle, const Audio_Play_Req  *req, const META_AUDIO_PLAY_CNF cnf_cb, const META_AUDIO_PLAY_OVER_IND  ind_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Play_ByName(const Audio_Play_ByName_Req  *req, const META_AUDIO_PLAY_BYNAME_CNF  cnf_cb, const META_AUDIO_PLAY_OVER_IND  ind_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Play_ByName_r(const int meta_handle, const Audio_Play_ByName_Req  *req, const META_AUDIO_PLAY_BYNAME_CNF  cnf_cb, const META_AUDIO_PLAY_OVER_IND  ind_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Play_IMY_ByBuf(const Audio_Play_IMY_ByBuf_Req  *req, const META_AUDIO_PLAY_IMY_BYBUF_CNF  cnf_cb, const META_AUDIO_PLAY_OVER_IND  ind_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Play_IMY_ByBuf_r(const int meta_handle, const Audio_Play_IMY_ByBuf_Req  *req, const META_AUDIO_PLAY_IMY_BYBUF_CNF  cnf_cb, const META_AUDIO_PLAY_OVER_IND  ind_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Stop(const META_AUDIO_STOP_CNF  cnf_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Stop_r(const int meta_handle, const META_AUDIO_STOP_CNF  cnf_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_MEDIA_Play(const Audio_MEDIA_Play_Req  *req, const META_AUDIO_MEDIA_PLAY_CNF  cnf_cb, const META_AUDIO_MEDIA_PLAY_OVER_IND  ind_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_MEDIA_Play_r(const int meta_handle, const Audio_MEDIA_Play_Req  *req, const META_AUDIO_MEDIA_PLAY_CNF  cnf_cb, const META_AUDIO_MEDIA_PLAY_OVER_IND  ind_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_MEDIA_Stop(const META_AUDIO_MEDIA_STOP_CNF  cnf_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_MEDIA_Stop_r(const int meta_handle, const META_AUDIO_MEDIA_STOP_CNF  cnf_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Set_Volume(const Audio_Set_Volume_Req  *req, const META_AUDIO_SET_VOLUME_CNF  cnf_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Set_Volume_r(const int meta_handle, const Audio_Set_Volume_Req  *req, const META_AUDIO_SET_VOLUME_CNF  cnf_cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_Audio_Set_Echo_Loop(unsigned int  ms_timeout,const Audio_Set_Echo_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Echo_Loop_r(const int meta_handle,unsigned int  ms_timeout ,const Audio_Set_Echo_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Mode(unsigned int  ms_timeout,const Audio_Set_Mode_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Mode_r(const int meta_handle,unsigned int  ms_timeout ,const Audio_Set_Mode_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Gain(unsigned int  ms_timeout,const Audio_Set_Gain_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Gain_r(const int meta_handle,unsigned int  ms_timeout ,const Audio_Set_Gain_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Tone_Loop_Back_Rec(unsigned int  ms_timeout, Audio_Tone_LoopBackRec_Req  *req, Audio_Tone_LoopBackRec_Cnf *cnf);
META_RESULT  __stdcall SP_META_Audio_Tone_Loop_Back_Rec_r(const int meta_handle,unsigned int  ms_timeout , Audio_Tone_LoopBackRec_Req  *req, Audio_Tone_LoopBackRec_Cnf *cnf);
//  for loud-speaker mode
META_RESULT  __stdcall SP_META_Audio_Tone_Loop_Back_Rec_2K(unsigned int  ms_timeout, Audio_Tone_LoopBackRec_Req  *req, Audio_Tone_LoopBackRec_Cnf_2K *cnf);
META_RESULT  __stdcall SP_META_Audio_Tone_Loop_Back_Rec_2K_r(const int meta_handle,unsigned int  ms_timeout , Audio_Tone_LoopBackRec_Req  *req, Audio_Tone_LoopBackRec_Cnf_2K *cnf);
// for normal mode
META_RESULT  __stdcall SP_META_Audio_Tone_Loop_Back_Rec_2K_Normal(unsigned int  ms_timeout, Audio_Tone_LoopBackRec_Req  *req, Audio_Tone_LoopBackRec_Cnf_2K *cnf);
META_RESULT  __stdcall SP_META_Audio_Tone_Loop_Back_Rec_2K_Normal_r(const int meta_handle,unsigned int  ms_timeout , Audio_Tone_LoopBackRec_Req  *req, Audio_Tone_LoopBackRec_Cnf_2K *cnf);
META_RESULT  __stdcall SP_META_Audio_Set_LoudSpk_FIR_Coeffs(unsigned int  ms_timeout,const Audio_Set_LoudSpk_FIR_Coeffs_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_LoudSpk_FIR_Coeffs_r(const int meta_handle, unsigned int  ms_timeout,const Audio_Set_LoudSpk_FIR_Coeffs_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Speech_Common(unsigned int  ms_timeout,const Audio_Set_Speech_Common_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Speech_Common_r(const int meta_handle, unsigned int  ms_timeout,const Audio_Set_Speech_Common_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_LoudSpk_Mode(unsigned int  ms_timeout,const Audio_Set_LoudSpk_Mode_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_LoudSpk_Mode_r(const int meta_handle, unsigned int  ms_timeout,const Audio_Set_LoudSpk_Mode_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Playback_Maximum_Swing(unsigned int  ms_timeout,const Audio_Set_Playback_Maximum_Swing_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Playback_Maximum_Swing_r(const int meta_handle, unsigned int  ms_timeout,const Audio_Set_Playback_Maximum_Swing_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Melody_FIR_Output_Coeffs(unsigned int  ms_timeout,const Audio_Set_Melody_FIR_Output_Coeffs_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Melody_FIR_Output_Coeffs_r(const int meta_handle, unsigned int  ms_timeout,const Audio_Set_Melody_FIR_Output_Coeffs_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Speech_Common_And_Mode(unsigned int  ms_timeout,const Audio_Set_Speech_Common_And_Mode_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Speech_Common_And_Mode_r(const int meta_handle, unsigned int  ms_timeout,const Audio_Set_Speech_Common_And_Mode_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Play_Freq_Vol_Tone(unsigned int  ms_timeout,const Audio_Set_Freq_Vol_Tone_Req_T  *req);
META_RESULT  __stdcall SP_META_Audio_Play_Freq_Vol_Tone_r(const int meta_handle, unsigned int  ms_timeout,const Audio_Set_Freq_Vol_Tone_Req_T  *req);
META_RESULT  __stdcall SP_META_Audio_Stop_Freq_Vol_Tone(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_Audio_Stop_Freq_Vol_Tone_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_Audio_Get_Audio_Profile_Settings(unsigned int ms_timeout,Audio_Get_Profile_Settings_By_Mode_Req_T *req, Audio_Get_Profile_Settings_By_Mode_Cnf_T *cnf);
META_RESULT  __stdcall SP_META_Audio_Get_Audio_Profile_Settings_r(const int meta_handle, unsigned int  ms_timeout, Audio_Get_Profile_Settings_By_Mode_Req_T *req, Audio_Get_Profile_Settings_By_Mode_Cnf_T *cnf);
META_RESULT  __stdcall SP_META_Audio_Set_Audio_Profile_Settings(unsigned int ms_timeout,Audio_Set_Profile_Settings_By_Mode_Req_T *req, Audio_Set_Profile_Settings_By_Mode_Cnf_T *cnf);
META_RESULT  __stdcall SP_META_Audio_Set_Audio_Profile_Settings_r(const int meta_handle, unsigned int  ms_timeout, Audio_Set_Profile_Settings_By_Mode_Req_T *req, Audio_Set_Profile_Settings_By_Mode_Cnf_T *cnf);
META_RESULT  __stdcall SP_META_Audio_Get_Audio_Param_Settings_0809(unsigned int ms_timeout,l1audio_param_W0809_T *cnf);
META_RESULT  __stdcall SP_META_Audio_Get_Audio_Param_Settings_0809_r(const int meta_handle, unsigned int  ms_timeout,  l1audio_param_W0809_T *cnf);
META_RESULT  __stdcall SP_META_Audio_Set_Audio_Param_Settings_0809(unsigned int ms_timeout,l1audio_param_W0809_T *req,Audio_Set_Param_Cnf_T *cnf);
META_RESULT  __stdcall SP_META_Audio_Set_Audio_Param_Settings_0809_r(const int meta_handle, unsigned int  ms_timeout,  l1audio_param_W0809_T *req,Audio_Set_Param_Cnf_T *cnf);
META_RESULT  __stdcall SP_META_Audio_Receiver_Test(unsigned int ms_timeout, ft_l4aud_receiver_test *req);
META_RESULT  __stdcall SP_META_Audio_Receiver_Test_r(const int meta_handle, unsigned int ms_timeout, ft_l4aud_receiver_test *req);
META_RESULT  __stdcall SP_META_Audio_LoudSpk_Test(unsigned int ms_timeout, ft_l4aud_loudspk *req);
META_RESULT  __stdcall SP_META_Audio_LoudSpk_Test_r(const int meta_handle, unsigned int ms_timeout, ft_l4aud_loudspk *req);
META_RESULT  __stdcall SP_META_Audio_EX_SetACFIIRToTarget(const unsigned int ms_timeout, l4aud_acf_param *req);
META_RESULT  __stdcall SP_META_Audio_EX_SetACFIIRToTarget_r(const int meta_handle, const unsigned int ms_timeout, l4aud_acf_param *req);


//--------------------------------------------------------------------------//
//  BaseBand Testing                                                        //
//--------------------------------------------------------------------------//

//-----------------------------------------------------//
//  BaseBand Testing: data structure definition        //
//-----------------------------------------------------//

typedef struct{
	unsigned int		addr;
	unsigned char		bytenum;
}CPU_REG_READ_REQ;

typedef struct{
	unsigned int		value;
	unsigned char		status;
}CPU_REG_READ_CNF;

typedef struct{
	unsigned int		addr;
	unsigned int		value;
	unsigned char		bytenum;
}CPU_REG_WRITE_REQ;

typedef struct{
	unsigned char		status;
}CPU_REG_WRITE_CNF;


typedef struct{
	BYTE 	registernumber;	/// the valid value: 0--96
}WM_CMD_ReadPMICRegister_REQ_T;

typedef struct{
	BYTE 		value;
	BOOL		status;
}WM_CMD_ReadRegister_CNF_T;

typedef struct{
	BYTE registernumber;   //the valid value: 20~~ 96
	BYTE registervalue;
}WM_CMD_WritePMICRegister_REQ_T;

typedef struct{
	int value;   //not used
	BOOL		status;
}WM_CMD_WriteRegister_CNF_T;


//add by dian.wang for MT6573 PMIC
typedef struct{
	DWORD 	registernumber;	/// the valid value: 0--96
}WM_CMD_ReadPMICRegister_DWORD_REQ_T;

typedef struct{
	unsigned int  value;
	unsigned char status;
}WM_CMD_ReadRegister_DWORD_CNF_T;

typedef struct{
	DWORD registernumber;   //the valid value: 20~~ 96
	WORD registervalue;
}WM_CMD_WritePMICRegister_DWORD_REQ_T;

typedef struct{
	unsigned int    value;   //not used
	unsigned char	status;
}WM_CMD_WriteRegister_DWORD_CNF_T;

////////////////////////////////////////


typedef struct {
    int num;
    int delay;
    int tolerance;
} GS_CMD_CALI;

typedef struct {
    int x;
    int y;
    int z; 
} GS_ACK_CALI;

typedef struct {
    int dummy;
} GS_CMD_READ_RAW;

typedef struct {
    int x;
    int y;
    int z;
} GS_ACK_READ_RAW;

typedef struct {
    int x;
    int y;
    int z;    
} GS_CMD_WRITE_NVRAM;

typedef struct {
    int   dummy;
} GS_ACK_WRITE_NVRAM;

typedef struct {
    int   dummy;
} GS_CMD_READ_NVRAM;

typedef struct {
    int x;
    int y;
    int z;    
} GS_ACK_READ_NVRAM;


META_RESULT  __stdcall SP_META_GS_Perform_Calibration(unsigned int ms_timeout, const  GS_CMD_CALI*req, GS_ACK_CALI *cnf);
META_RESULT  __stdcall SP_META_GS_Perform_Calibration_r(const int meta_handle, unsigned int ms_timeout, const  GS_CMD_CALI*req, GS_ACK_CALI *cnf);

META_RESULT  __stdcall SP_META_GS_Write_NVRAM(unsigned int ms_timeout, const  GS_CMD_WRITE_NVRAM*req, GS_ACK_WRITE_NVRAM *cnf);
META_RESULT  __stdcall SP_META_GS_Write_NVRAM_r(const int meta_handle, unsigned int ms_timeout, const  GS_CMD_WRITE_NVRAM*req, GS_ACK_WRITE_NVRAM *cnf);

typedef struct {
    int num;
    int delay;
    int tolerance;
} GYRO_CMD_CALI;

typedef struct {
    int x;
    int y;
    int z; 
} GYRO_ACK_CALI;

typedef struct {
    int dummy;
} GYRO_CMD_READ_RAW;

typedef struct {
    int x;
    int y;
    int z;
} GYRO_ACK_READ_RAW;

typedef struct {
    int x;
    int y;
    int z;    
} GYRO_CMD_WRITE_NVRAM;

typedef struct {
    int   dummy;
} GYRO_ACK_WRITE_NVRAM;

typedef struct {
    int   dummy;
} GYRO_CMD_READ_NVRAM;

typedef struct {
    int x;
    int y;
    int z;    
} GYRO_ACK_READ_NVRAM;


META_RESULT  __stdcall SP_META_GYRO_Perform_Calibration(unsigned int ms_timeout, const  GYRO_CMD_CALI*req, GYRO_ACK_CALI *cnf);
META_RESULT  __stdcall SP_META_GYRO_Perform_Calibration_r(const int meta_handle, unsigned int ms_timeout, const  GYRO_CMD_CALI*req, GYRO_ACK_CALI *cnf);



META_RESULT  __stdcall SP_META_GYRO_Write_NVRAM(unsigned int ms_timeout, const  GYRO_CMD_WRITE_NVRAM*req, GYRO_ACK_WRITE_NVRAM *cnf);
META_RESULT  __stdcall SP_META_GYRO_Write_NVRAM_r(const int meta_handle, unsigned int ms_timeout, const  GYRO_CMD_WRITE_NVRAM*req, GYRO_ACK_WRITE_NVRAM *cnf);

typedef struct
{
	unsigned char	channel;	// ADC channel number.
	unsigned short	Meacount;	// Number of measure times.
} ADCMeaData_Req;

typedef struct
{
	unsigned int	value;		// ADC value, it a sum value of each measurement data.
	int				drv_status;
	unsigned char	status;		// 0: success, others: get ADC measurement fail.
} ADCMeaData_Cnf;

//-----------------------------------------------------//
//  BaseBand Testing: callback function definition     //
//-----------------------------------------------------//
typedef void (__stdcall *META_BB_READREG_CNF)(const CPU_REG_READ_CNF *result, const short token, void *usrData);
typedef void (__stdcall *META_BB_WRITEREG_CNF)(const CPU_REG_WRITE_CNF *result, const short token, void *usrData);
typedef void (__stdcall *META_BB_ADCGETMEADATA_CNF)(const ADCMeaData_Cnf *result, const short token, void *usrData);

//-----------------------------------------------------//
//  BaseBand Testing: exported function definition     //
//-----------------------------------------------------//

META_RESULT  __stdcall SP_META_BB_RegRead(const CPU_REG_READ_REQ *req, const META_BB_READREG_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_BB_RegRead_r(const int meta_handle, const CPU_REG_READ_REQ *req, const META_BB_READREG_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_BB_RegWrite(const CPU_REG_WRITE_REQ *req, const META_BB_WRITEREG_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_BB_RegWrite_r(const int meta_handle, const CPU_REG_WRITE_REQ *req, const META_BB_WRITEREG_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_PMIC_RegRead(unsigned int ms_timeout, const WM_CMD_ReadPMICRegister_REQ_T *req, WM_CMD_ReadRegister_CNF_T *cnf) ;
META_RESULT  __stdcall SP_META_PMIC_RegRead_r(const int meta_handle,unsigned int ms_timeout, const WM_CMD_ReadPMICRegister_REQ_T *req, WM_CMD_ReadRegister_CNF_T *cnf);
META_RESULT  __stdcall SP_META_PMIC_RegWrite(unsigned int ms_timeout, const WM_CMD_WritePMICRegister_REQ_T *req, WM_CMD_WriteRegister_CNF_T *cnf) ;
META_RESULT  __stdcall SP_META_PMIC_RegWrite_r(const int meta_handle,unsigned int ms_timeout, const WM_CMD_WritePMICRegister_REQ_T *req, WM_CMD_WriteRegister_CNF_T *cnf);
META_RESULT  __stdcall SP_META_BB_ADCGetMeaSumData(const ADCMeaData_Req *req, const META_BB_ADCGETMEADATA_CNF cb, short *token, void *usrData);
META_RESULT  __stdcall SP_META_BB_ADCGetMeaSumData_r(const int meta_handle, const ADCMeaData_Req *req, const META_BB_ADCGETMEADATA_CNF cb, short *token, void *usrData);

META_RESULT  __stdcall SP_META_PMIC_RegRead_DWORD(unsigned int ms_timeout, const WM_CMD_ReadPMICRegister_DWORD_REQ_T *req, WM_CMD_ReadRegister_DWORD_CNF_T *cnf) ;
META_RESULT  __stdcall SP_META_PMIC_RegRead_DWORD_r(const int meta_handle,unsigned int ms_timeout, const WM_CMD_ReadPMICRegister_DWORD_REQ_T *req, WM_CMD_ReadRegister_DWORD_CNF_T *cnf);
META_RESULT  __stdcall SP_META_PMIC_RegWrite_DWORD(unsigned int ms_timeout, const WM_CMD_WritePMICRegister_DWORD_REQ_T *req, WM_CMD_WriteRegister_DWORD_CNF_T *cnf) ;
META_RESULT  __stdcall SP_META_PMIC_RegWrite_DWORD_r(const int meta_handle,unsigned int ms_timeout, const WM_CMD_WritePMICRegister_DWORD_REQ_T *req, WM_CMD_WriteRegister_DWORD_CNF_T *cnf);

//--------------------------------------------------------------------------//
//  FAT Access                                                              //
//--------------------------------------------------------------------------//

//-----------------------------------------------------//
//  FAT Access: data structure definition              //
//-----------------------------------------------------//
typedef enum {
	FAT_OPEN_READ = 0,
	FAT_OPEN_WRITE
}FAT_OPEN_MODE;

typedef enum {
	FAT_FIND_FILE = 0,
	FAT_FIND_FILE_RECURSIVE,
	FAT_FIND_DIR_RECURSIVE
}FAT_FIND_MODE;

typedef enum {
	FAT12 = 0,
	FAT16,
	FAT32
}FAT_TYPE;

typedef struct {
	FAT_TYPE		Type;
	unsigned int 	SectorsPerCluster;
	unsigned int	TotalSize;
	unsigned int	FreeSpace;
}FAT_DiskInfo_T;

typedef struct 
{
	char m_cDriveLetter;   // Target FAT disk drive letter such as: 'C'
	char *m_pcfilepath;    // File path of the file we intend to write into target FAT

}FAT_FILE_INFO_REQ_T;

//-----------------------------------------------------//
//  FAT Access: callback function definition           //
//-----------------------------------------------------//
typedef int (__stdcall *CALLBACK_META_FAT_PROGRESS)(unsigned char percent, int sent_bytes, int total_bytes, const short token, void *usr_arg);

//-----------------------------------------------------//
//  FAT Access: exported function definition           //
//-----------------------------------------------------//

META_RESULT  __stdcall SP_META_FAT_Open(const char *fat_filepath, FAT_OPEN_MODE  mode, int *fs_handle, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Open_r(const int meta_handle, const char *fat_filepath, FAT_OPEN_MODE  mode, int *fs_handle, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Close(int *fs_handle, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Close_r(const int meta_handle, int *fs_handle, short *p_token);
META_RESULT  __stdcall SP_META_FAT_GetFileSize(const int fs_handle, int *filesize, short *p_token);
META_RESULT  __stdcall SP_META_FAT_GetFileSize_r(const int meta_handle, const int fs_handle, int *filesize, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Read(const int fs_handle, char *buf, const int buf_len, CALLBACK_META_FAT_PROGRESS  cb_progress, void  *cb_progress_arg, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Read_r(const int meta_handle, const int fs_handle, char *buf, const int buf_len, CALLBACK_META_FAT_PROGRESS  cb_progress, void  *cb_progress_arg, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Write(const int fs_handle, const char *buf, const int buf_len, CALLBACK_META_FAT_PROGRESS  cb_progress, void  *cb_progress_arg, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Write_r(const int meta_handle, const int fs_handle, const char *buf, const int buf_len, CALLBACK_META_FAT_PROGRESS  cb_progress, void  *cb_progress_arg, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Read_To_File(const int fs_handle, const char *local_filepath, CALLBACK_META_FAT_PROGRESS  cb_progress, void  *cb_progress_arg, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Read_To_File_r(const int meta_handle, const int fs_handle, const char *local_filepath, CALLBACK_META_FAT_PROGRESS  cb_progress, void  *cb_progress_arg, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Write_By_File(const int fs_handle, const char *local_filepath, CALLBACK_META_FAT_PROGRESS  cb_progress, void  *cb_progress_arg, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Write_By_File_r(const int meta_handle, const int fs_handle, const char *local_filepath, CALLBACK_META_FAT_PROGRESS  cb_progress, void  *cb_progress_arg, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Delete(const char *fat_filepath, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Delete_r(const int meta_handle, const char *fat_filepath, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Move(const char *fat_filepath, const char *new_fat_filepath, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Move_r(const int meta_handle, const char *fat_filepath, const char *new_fat_filepath, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Find_Start(const char *fat_base_dir, const char *fat_find_pattern, FAT_FIND_MODE	 find_mode, int *p_find_handle, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Find_Start_r(const int meta_handle, const char *fat_base_dir, const char *fat_find_pattern, FAT_FIND_MODE	 find_mode, int *p_find_handle, short *p_token);
META_RESULT  __stdcall SP_META_FAT_Find_Head(int find_handle);
META_RESULT  __stdcall SP_META_FAT_Find_Prev(int find_handle);
META_RESULT  __stdcall SP_META_FAT_Find_Next(int find_handle);
META_RESULT  __stdcall SP_META_FAT_Find_GetFileInfo(int find_handle, char *p_filepath, const int filepath_len, int *p_filesize);
META_RESULT  __stdcall SP_META_FAT_Find_Close(int *p_find_handle);
META_RESULT  __stdcall SP_META_FAT_GetDiskInfo(const char DriveLetter, FAT_DiskInfo_T  *p_DiskInfo, short *p_token);
META_RESULT  __stdcall SP_META_FAT_GetDiskInfo_r(const int meta_handle, const char DriveLetter, FAT_DiskInfo_T  *p_DiskInfo, short *p_token);
META_RESULT  __stdcall SP_META_FAT_RemoveDir(const char *fat_dirpath);
META_RESULT  __stdcall SP_META_FAT_RemoveDir_r(const int meta_handle, const char *fat_dirpath);

META_RESULT  __stdcall SP_META_FAT_CheckEnoughSpace(FAT_FILE_INFO_REQ_T *req);
META_RESULT  __stdcall SP_META_FAT_CheckEnoughSpace_r(const int meta_handle, FAT_FILE_INFO_REQ_T *req);


/*  NOR_DRIVE = 1,
	NAND_DRIVE=2,
	CARD_DRIVE = 3,
	EXTERNAL_DRIVE = 4
*/
META_RESULT  __stdcall SP_META_FAT_GetDriveType(unsigned int ms_timeout, const char DriveLetter, int *p_DriveType);
META_RESULT  __stdcall SP_META_FAT_GetDriveType_r(const int meta_handle, unsigned int ms_timeout, const char DriveLetter, int *p_DriveType);
//--------------------------------------------------------------------------//
//  WiFi Calibration                                                        //
//--------------------------------------------------------------------------//

//-----------------------------------------------------//
//  WiFi Calibration: data structure definition        //
//-----------------------------------------------------//

// WiFi Baseband Chip ID 
#define WIFI_BB_MT5911		0x00000001

// WiFi RF Chip ID 
#define WIFI_RF_AL2236		0x00000001
#define WIFI_RF_MAX2827		0x00000002

typedef enum {
	WIFI_TEST_RATE_1M = 0,     /* 1M          */
	WIFI_TEST_RATE_2M,         /* 2M          */
	WIFI_TEST_RATE_5_5M,       /* 5.5M        */
	WIFI_TEST_RATE_11M,        /* 11M         */
	WIFI_TEST_RATE_6M,         /* 6M          */
	WIFI_TEST_RATE_9M,         /* 9M          */
	WIFI_TEST_RATE_12M,        /* 12M         */
	WIFI_TEST_RATE_18M,        /* 18M         */
	WIFI_TEST_RATE_24M,        /* 24M         */
	WIFI_TEST_RATE_36M,        /* 36M         */
	WIFI_TEST_RATE_48M,        /* 48M         */
	WIFI_TEST_RATE_54M,        /* 54M         */
	WIFI_TEST_RATE_COUNT       /* Total count */
} WiFi_TestRate_E;

typedef enum {
	 WNDRV_HOST_INTERFACE_SDIO = 0
	,WNDRV_HOST_INTERFACE_HPI
	,WNDRV_HOST_INTERFACE_SPI
	,WNDRV_HOST_INTERFACE_CF_MEM
	,WNDRV_HOST_INTERFACE_CF_IO  
} WiFi_HostInterface_E;

typedef enum {
	WIFI_TX_ALL_ZEROS,
	WIFI_TX_ALL_ONES,
	WIFI_TX_ALTERNATE_BITS,
	WIFI_TX_PSEUDO_RANDOM
} WiFi_TestPktTxPattern_E;

typedef enum {
	WIFI_POWER_MODE_NORMAL,
	WIFI_POWER_MODE_IDLE,
	WIFI_POWER_MODE_SLEEP
} WiFi_PowerManagementMode_E;

typedef enum {    
	WIFI_RF_RX_TEST_MODE = 1  /* For RF Test use */
} WiFi_TestPktRxMode_E;

typedef enum {
	WIFI_RX_ANT_DIVERSITY_AGC,  /* AGC based selection */
	WIFI_RX_ANT_DIVERSITY_MPDU, /* MPDU based selection */
	WIFI_RX_ANT_FIXED_0,        /* Always 0 */ 
	WIFI_RX_ANT_FIXED_1         /* Always 1 */
} WiFi_RxAntSel_E;

typedef struct {
	unsigned int	bb_chip_id;
	char			bb_chip_ver[32];
	unsigned int	rf_chip_id;
	char			rf_chip_ver[32];
	unsigned char	support_802_11b;
	unsigned char	support_802_11a;
	unsigned char	support_802_11g;
	bool			eeprom_exist;
	unsigned int	eeprom_size;
	WiFi_HostInterface_E	host_interface;
} WiFi_ChipCapability_S;

typedef struct {
	unsigned int		ch_freq; /* Frq, units are kHz */
	WiFi_TestRate_E		tx_rate;
	int					dbm;
} WiFi_DBM2DAC_Set_S;

typedef struct {
	unsigned short		tx_gain_dac;
} WiFi_DBM2DAC_Query_S;

typedef struct {
	unsigned int		ch_freq;/* Frq, units are kHz */
	WiFi_TestRate_E		tx_rate;
	unsigned char		txAnt; /* 0 for Antenna 0; 1 for Antenna 1 */
	unsigned short		tx_gain_dac;
} WiFi_TestTx_S;

typedef struct {
	unsigned int			ch_freq;			/* Frq, units are kHz */
	WiFi_TestRate_E			tx_rate;
	unsigned short			tx_gain_dac;
	unsigned int			pktCount;
	unsigned int			pktInterval;		/* interval between each Tx Packet */
	unsigned int			pktLength;			/* 24~1500 */
	WiFi_TestPktTxPattern_E	pattern;			/* content of the Tx Packet */
	unsigned char			txAnt;				/* 0 for Antenna 0; 1 for Antenna 1 */
	unsigned char			is_short_preamble;	/* 0 for long preamble and 1 for short preamble */
	unsigned char			mac_header[ 24 ];	/* Frame Ctrl, Duration = 2bytes + 2bytes */
												/* Address 1 = 6 bytes */ 
												/* Address 2 = 6 bytes */ 
												/* Address 3 = 6 bytes */ 
												/* Sequence Ctrl = 2 bytes */
} WiFi_TestPktTx_S;

typedef struct {
	unsigned int			ch_freq;			/* Frq, units are kHz */
	WiFi_TestRate_E			tx_rate;
	unsigned short			tx_gain_dac;
	unsigned int			pktCount;
	unsigned int			pktInterval;		/* interval between each Tx Packet */
	unsigned int			pktLength;			/* 24~1500 */
	WiFi_TestPktTxPattern_E	pattern;			/* content of the Tx Packet */
	unsigned char			txAnt;				/* 0 for Antenna 0; 1 for Antenna 1 */
	unsigned int			txFlags;
	unsigned int			targetAlc;
	unsigned char			is_short_preamble;	/* 0 for long preamble and 1 for short preamble */
	unsigned char			mac_header[ 24 ];	/* Frame Ctrl, Duration = 2bytes + 2bytes */
												/* Address 1 = 6 bytes */ 
												/* Address 2 = 6 bytes */ 
												/* Address 3 = 6 bytes */ 
												/* Sequence Ctrl = 2 bytes */
} WiFi_TestPktTx_Ex_S;

typedef struct {    
	unsigned int		pkt_sent_count;  /* total num sent */
	unsigned int		pkt_sent_acked;  /* acked num */    
} WiFi_TxStatus_S;


typedef struct {    
	unsigned int		pkt_sent_count;  /* total num sent */
	unsigned int		pkt_sent_acked;  /* acked num */    
	unsigned short		avgAlc;
	unsigned char		cckGainControl;
    unsigned char		ofdmGainControl;
} WiFi_TxStatus_Ex_S;

typedef struct {
	unsigned int				ch_freq;  /* Frq, units are kHz */
	WiFi_TestPktRxMode_E		mode;
	WiFi_RxAntSel_E				rxAnt;
} WiFi_TestPktRx_S;

typedef struct {    
	unsigned int		int_rx_ok_num;     /* number of packets that Rx ok from interrupt */
	unsigned int		int_crc_err_num;   /* number of packets that CRC error from interrupt */
	unsigned int		pau_rx_pkt_count;  /* number of packets that Rx ok from PAU */
	unsigned int		pau_crc_err_count; /* number of packets that CRC error from PAU */
	unsigned int		pau_cca_count;     /* CCA rising edge count */
	unsigned int		pau_rx_fifo_full_count; /* number of lost packets due to FiFo full */
	unsigned int		int_long_preamble_num;
	unsigned int		int_short_preamble_num;
	unsigned int		int_rate_ok_num[ WIFI_TEST_RATE_COUNT ];
	unsigned int		int_rate_crc_err_num[ WIFI_TEST_RATE_COUNT ];
	int					int_rssi_max;
	int					int_rssi_min;
	int					int_rssi_mean;
	int					int_rssi_variance;
} WiFi_RxStatus_S;

typedef struct {    
	int  ED;
	int  OSD;
	int  SQ1;
	int  SFD;
	int  CRC16;
} WiFi_RxCounter_S;

typedef struct {    
	unsigned int	channel_num;
	unsigned char	channel_list[64];
} WiFi_ChannelList_S;

typedef struct {    
	unsigned char	country_code[2];
} WiFi_RegDomain_S;

typedef struct {
	unsigned int	index;		// 32bits alignment index, +4 
	unsigned int	mcr_data32;
} WiFi_MACReg32_S;

typedef struct {
	unsigned int	index;		// 16bits alignment index, +2 
	unsigned short	mcr_data16;
} WiFi_MACReg16_S;

typedef struct {
	unsigned int	index;		// 8bits alignment index, +1 
	unsigned char	bbcr_data8;
} WiFi_BBReg8_S;

typedef struct {
	unsigned int	index;		// 16bits alignment index, +2 
	unsigned short	eeprom_data16;
} WiFi_EEPROM_S;

//-----------------------------------------------------//
//  WiFi Calibration: WNDRV SET Functions              //
//-----------------------------------------------------//
META_RESULT  __stdcall SP_META_WiFi_Stop(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_WiFi_Stop_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_WiFi_ContTx(unsigned int  ms_timeout, const WiFi_TestTx_S *req);
META_RESULT  __stdcall SP_META_WiFi_ContTx_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_TestTx_S *req);
META_RESULT  __stdcall SP_META_WiFi_LocalFrequencyMeasure(unsigned int  ms_timeout, const WiFi_TestTx_S *req);
META_RESULT  __stdcall SP_META_WiFi_LocalFrequencyMeasure_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_TestTx_S *req);
META_RESULT  __stdcall SP_META_WiFi_CarrierSuppressionMeasure(unsigned int  ms_timeout, const WiFi_TestTx_S *req);
META_RESULT  __stdcall SP_META_WiFi_CarrierSuppressionMeasure_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_TestTx_S *req);
META_RESULT  __stdcall SP_META_WiFi_ContPktTx(unsigned int  ms_timeout, const WiFi_TestPktTx_S *req);
META_RESULT  __stdcall SP_META_WiFi_ContPktTx_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_TestPktTx_S *req);
META_RESULT  __stdcall SP_META_WiFi_ContPktTx_Ex(unsigned int  ms_timeout, const WiFi_TestPktTx_Ex_S *req);
META_RESULT  __stdcall SP_META_WiFi_ContPktTx_Ex_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_TestPktTx_Ex_S *req);

META_RESULT  __stdcall SP_META_WiFi_SetPowerManagementMode(unsigned int  ms_timeout, const WiFi_PowerManagementMode_E  mode);
META_RESULT  __stdcall SP_META_WiFi_SetPowerManagementMode_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_PowerManagementMode_E  mode);
META_RESULT  __stdcall SP_META_WiFi_ContPktRx(unsigned int  ms_timeout, const WiFi_TestPktRx_S *req);
META_RESULT  __stdcall SP_META_WiFi_ContPktRx_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_TestPktRx_S *req);
META_RESULT  __stdcall SP_META_WiFi_SetRegDomain(unsigned int  ms_timeout, const WiFi_RegDomain_S  *req);
META_RESULT  __stdcall SP_META_WiFi_SetRegDomain_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_RegDomain_S  *req);
META_RESULT  __stdcall SP_META_WiFi_SetDbmToDac(unsigned int  ms_timeout, const WiFi_DBM2DAC_Set_S *req);
META_RESULT  __stdcall SP_META_WiFi_SetDbmToDac_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_DBM2DAC_Set_S *req);
META_RESULT  __stdcall SP_META_WiFi_MACReg32Write(unsigned int  ms_timeout, const WiFi_MACReg32_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_MACReg32Write_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_MACReg32_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_MACReg16Write(unsigned int  ms_timeout, const WiFi_MACReg16_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_MACReg16Write_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_MACReg16_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_BBRegWrite(unsigned int  ms_timeout, const WiFi_BBReg8_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_BBRegWrite_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_BBReg8_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_EEPROM_Write(unsigned int  ms_timeout, const WiFi_EEPROM_S *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_EEPROM_Write_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_EEPROM_S *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_QueryTxStatus(unsigned int  ms_timeout, WiFi_TxStatus_S *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryTxStatus_r(const int meta_handle, unsigned int  ms_timeout, WiFi_TxStatus_S *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryTxStatus_Ex(unsigned int  ms_timeout, WiFi_TxStatus_Ex_S *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryTxStatus_Ex_r(const int meta_handle, unsigned int  ms_timeout, WiFi_TxStatus_Ex_S *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryRxStatus(unsigned int  ms_timeout, WiFi_RxStatus_S *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryRxStatus_r(const int meta_handle, unsigned int  ms_timeout, WiFi_RxStatus_S *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryChannelList(unsigned int  ms_timeout, WiFi_ChannelList_S *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryChannelList_r(const int meta_handle, unsigned int  ms_timeout, WiFi_ChannelList_S *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryRxCounter(unsigned int  ms_timeout, WiFi_RxCounter_S *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryRxCounter_r(const int meta_handle, unsigned int  ms_timeout, WiFi_RxCounter_S *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryDbmToDac(unsigned int  ms_timeout, WiFi_DBM2DAC_Query_S  *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryDbmToDac_r(const int meta_handle, unsigned int  ms_timeout, WiFi_DBM2DAC_Query_S  *cnf);


//-----------------------------------------------------//
//  WiFi Calibration: WNDRV QUERY Functions            //
//-----------------------------------------------------//
META_RESULT  __stdcall SP_META_WiFi_MACReg32Read(unsigned int  ms_timeout, WiFi_MACReg32_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_MACReg32Read_r(const int meta_handle, unsigned int  ms_timeout, WiFi_MACReg32_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_MACReg16Read(unsigned int  ms_timeout, WiFi_MACReg16_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_MACReg16Read_r(const int meta_handle, unsigned int  ms_timeout, WiFi_MACReg16_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_BBRegRead(unsigned int  ms_timeout, WiFi_BBReg8_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_BBRegRead_r(const int meta_handle, unsigned int  ms_timeout, WiFi_BBReg8_S  *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_EEPROM_Read(unsigned int  ms_timeout, WiFi_EEPROM_S *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_EEPROM_Read_r(const int meta_handle, unsigned int  ms_timeout, WiFi_EEPROM_S *array, unsigned int array_cnt);
META_RESULT  __stdcall SP_META_WiFi_DacDcOffsetAutoCalibration(unsigned int  ms_timeout, WiFi_DAC_DC_Offset_S  *cnf);
META_RESULT  __stdcall SP_META_WiFi_DacDcOffsetAutoCalibration_r(const int meta_handle, unsigned int  ms_timeout, WiFi_DAC_DC_Offset_S  *cnf);

//-----------------------------------------------------//
//  WiFi Calibration: Exported Functions               //
//-----------------------------------------------------//
META_RESULT  __stdcall SP_META_WiFi_QueryChipCapability(unsigned int  ms_timeout, WiFi_ChipCapability_S  *cnf);
META_RESULT  __stdcall SP_META_WiFi_QueryChipCapability_r(const int meta_handle, unsigned int  ms_timeout, WiFi_ChipCapability_S  *cnf);
META_RESULT  __stdcall SP_META_WiFi_SetMacAddress(unsigned int  ms_timeout, const WiFi_MacAddress_S  *mac);
META_RESULT  __stdcall SP_META_WiFi_SetMacAddress_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_MacAddress_S  *mac);
META_RESULT  __stdcall SP_META_WiFi_SetTxPower2400M(unsigned int  ms_timeout, const WiFi_TxPower_2400M_S  *txpwr);
META_RESULT  __stdcall SP_META_WiFi_SetTxPower2400M_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_TxPower_2400M_S  *txpwr);
META_RESULT  __stdcall SP_META_WiFi_SetTxPower5000M(unsigned int  ms_timeout, const WiFi_TxPower_5000M_S  *txpwr);
META_RESULT  __stdcall SP_META_WiFi_SetTxPower5000M_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_TxPower_5000M_S  *txpwr);
META_RESULT  __stdcall SP_META_WiFi_SetDacDcOffset(unsigned int  ms_timeout, const WiFi_DAC_DC_Offset_S  *dac_dc_offset);
META_RESULT  __stdcall SP_META_WiFi_SetDacDcOffset_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_DAC_DC_Offset_S  *dac_dc_offset);

META_RESULT  __stdcall SP_META_WiFi_SetTxALC2400M(unsigned int  ms_timeout, const WiFi_TxALC_2400M_S  *txalc);
META_RESULT  __stdcall SP_META_WiFi_SetTxALC2400M_r(const int meta_handle, unsigned int  ms_timeout, const WiFi_TxALC_2400M_S  *txalc);


//--------------------------------------------------------------------------//
//  BT Calibration                                                          //
//--------------------------------------------------------------------------//

//-----------------------------------------------------//
//  BT Calibration: data structure definition          //
//-----------------------------------------------------//

// BT Module ID 
#define BT_NOT_SUPPORT		0x00000000
#define BTMODULE_MT6601		0x00000011
#define BTMODULE_MT6611	    0x00000012
#define BTMODULE_RFMD3500   0x00000021 
#define BTMODULE_RFMD4020	0x00000022

//#define BT_PACKET_LEN       339
#define BT_PACKET_LEN       1021  // because BT2.0 support at most 1021 bytes per packet
#define BT_BUFFER_LEN       1024
#define BT_DATA_LEN           1026
typedef struct {
	unsigned char	id;
} BT_ModuleID_S;

typedef struct {
	unsigned char   m_event;
	char         	m_status;
	unsigned short  m_handle;
	unsigned char	m_len;
	unsigned char	m_parms[256];
} BT_HCI_EVENT;

typedef struct {
	unsigned short	m_opcode;
	unsigned char	m_len;
	unsigned char	m_cmd[256];
} BT_HCI_COMMAND;
typedef struct {
    unsigned short           m_con_hdl;
    unsigned short           m_len;      	
    unsigned char            m_buffer[BT_BUFFER_LEN]; 
} BT_HCI_BUFFER;
typedef struct {
    unsigned short           m_len;
    unsigned char            m_data[BT_DATA_LEN];
} BT_HCI_PACKET;
typedef struct {
    unsigned short           m_con_hdl;
    unsigned short           m_len;      	
    unsigned short           m_total_pks; 
} BT_HCI_TX_PURE_TEST;

typedef struct {
    unsigned int             m_used_time;
    unsigned short           m_len;     
} BT_HCI_TX_PURE_TEST_STAT;

typedef struct {
    unsigned int             m_used_time;
    unsigned short           m_len;     
} BT_HCI_RX_PURE_TEST_STAT;

typedef struct {
    unsigned int             m_u4UsedTime;
    unsigned short           m_u2PktSentNum; 
    
} BT_HCI_TX_PURE_TEST_STAT_V2;

//-----------------------------------------------------//
//  BT Calibration Functions                           //
//-----------------------------------------------------//
META_RESULT  __stdcall META_BT_QueryModuleID(unsigned int  ms_timeout, BT_ModuleID_S  *cnf);
META_RESULT  __stdcall META_BT_QueryModuleID_r(const int meta_handle, unsigned int  ms_timeout, BT_ModuleID_S  *cnf);

typedef void (__stdcall *META_BT_HCI_CNF)(const BT_HCI_EVENT *cnf, const short token, void *usrData);
typedef void (__stdcall *META_BT_HCI_TXDATA_CNF)(const BT_HCI_PACKET *cnf, const short token, void *usrData);
typedef void (__stdcall *META_BT_AUTO_HCI_CNF)(const BT_HCI_EVENT *cnf, const short token, void *usrData);
typedef void (__stdcall *META_BT_HCI_RXDATA_CNF)(const BT_HCI_BUFFER *cnf, const short token, void *usrData);

typedef void (__stdcall *META_BT_HCI_TXTEST_CNF)(const BT_HCI_TX_PURE_TEST_STAT *cnf, const short token, void *usrData);
typedef void (__stdcall *META_BT_HCI_RXTEST_CNF)(const BT_HCI_RX_PURE_TEST_STAT *cnf, const short token, void *usrData);

typedef void (__stdcall *META_BT_HCI_TXTEST_V2_CNF)(const BT_HCI_TX_PURE_TEST_STAT_V2 *cnf, const short token, void *usrData);

typedef struct{
	META_BT_HCI_TXDATA_CNF      m_SendDataCallback;
	META_BT_HCI_RXDATA_CNF		m_RecvDataCallback;
	META_BT_AUTO_HCI_CNF		m_AutoCallback;
	META_BT_HCI_TXTEST_CNF		m_TxTestCallback;
	META_BT_HCI_RXTEST_CNF		m_RxTestCallback;
	META_BT_HCI_TXTEST_V2_CNF   m_TxTestCallback_V2;
} BT_OtherCallBack;

META_RESULT  __stdcall SP_META_BT_SendHCICommand(unsigned int  ms_timeout,BT_HCI_COMMAND *req, META_BT_HCI_CNF  cb, void  *cb_arg, unsigned char Cmpltcode);
META_RESULT  __stdcall SP_META_BT_SendHCICommand_r(const int meta_handle, unsigned int  ms_timeout,BT_HCI_COMMAND *req, META_BT_HCI_CNF  cb, void  *cb_arg, unsigned char Cmpltcode);
META_RESULT  __stdcall SP_META_BT_CancelHCICommand(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_BT_CancelHCICommand_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_BT_SendHCIData(unsigned int  ms_timeout,BT_HCI_BUFFER *snd, META_BT_HCI_TXDATA_CNF  cb_tx, void  *cb_arg);
META_RESULT  __stdcall SP_META_BT_SendHCIData_r(const int meta_handle, unsigned int  ms_timeout,BT_HCI_BUFFER *snd, META_BT_HCI_TXDATA_CNF  cb_tx, void  *cb_arg);
META_RESULT  __stdcall SP_META_BT_RegisterAutoCallback(META_BT_AUTO_HCI_CNF cb_auto);
META_RESULT  __stdcall SP_META_BT_RegisterAutoCallback_r(const int meta_handle,META_BT_AUTO_HCI_CNF cb_auto);
META_RESULT  __stdcall SP_META_BT_ReceiveHCIData(META_BT_HCI_RXDATA_CNF cb_rx);
META_RESULT  __stdcall SP_META_BT_ReceiveHCIData_r(const int meta_handle,META_BT_HCI_RXDATA_CNF cb_rx);
META_RESULT  __stdcall SP_META_BT_TxPureTest(unsigned int  ms_timeout, BT_HCI_TX_PURE_TEST *snd, META_BT_HCI_TXTEST_CNF cb_tx, void  *cb_arg);
META_RESULT  __stdcall SP_META_BT_TxPureTest_r(const int meta_handle, unsigned int  ms_timeout, BT_HCI_TX_PURE_TEST *snd, META_BT_HCI_TXTEST_CNF cb_tx, void  *cb_arg);
META_RESULT  __stdcall SP_META_BT_RxTestStart(unsigned int  ms_timeout, META_BT_HCI_RXTEST_CNF cb_rx);
META_RESULT  __stdcall SP_META_BT_RxTestStart_r(const int meta_handle, unsigned int  ms_timeout, META_BT_HCI_RXTEST_CNF cb_rx);
META_RESULT  __stdcall SP_META_BT_RxTestEnd(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_BT_RxTestEnd_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_BT_TxPureTest_V2(unsigned int  ms_timeout, BT_HCI_TX_PURE_TEST *snd, META_BT_HCI_TXTEST_V2_CNF cb_txtest, void  *cb_arg);
META_RESULT  __stdcall SP_META_BT_TxPureTest_V2_r(const int meta_handle, unsigned int  ms_timeout, BT_HCI_TX_PURE_TEST	*snd, META_BT_HCI_TXTEST_V2_CNF cb_txtest, void  *cb_arg);
META_RESULT  __stdcall SP_META_BT_RxTestStart_V2(unsigned int  ms_timeout, META_BT_HCI_RXTEST_CNF cb_rx);
META_RESULT  __stdcall SP_META_BT_RxTestStart_V2_r(const int meta_handle, unsigned int ms_timeout, META_BT_HCI_RXTEST_CNF cb_rx);
META_RESULT  __stdcall SP_META_BT_EnableNvramOnlineUpdate(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_BT_EnableNvramOnlineUpdate_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_BT_DisableNvramOnlineUpdate(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_BT_DisableNvramOnlineUpdate_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_BT_EnablePcmClockSyncSignal(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_BT_EnablePcmClockSyncSignal_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_BT_DisablePcmClockSyncSignal(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_BT_DisablePcmClockSyncSignal_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_BT_RemoveAutoCallback();
META_RESULT  __stdcall SP_META_BT_RemoveAutoCallback_r(const int meta_handle);
META_RESULT  __stdcall SP_META_BT_RemoveReceiveHCIDataCallback();
META_RESULT  __stdcall SP_META_BT_RemoveReceiveHCIDataCallback_r(const int meta_handle);

//----------------------------------------------------------------//
//                              MATV                              //
//----------------------------------------------------------------//

typedef struct
{
	unsigned int	freq;
	unsigned char	sndsys;
	unsigned char	colsys;
	unsigned char	flag;
}matv_ch_entry;

typedef struct
{
    unsigned char   m_ucChannel;
    matv_ch_entry   m_rmatv_ch_entry;
}FT_MATV_SET_CHANNEL_PROPERTY_REQ_T;

typedef struct
{
    unsigned char   m_ucProgress;
    unsigned char   m_ucChannels;
    matv_ch_entry   m_rmatv_ch_entry[70];
}FT_MATV_GET_CHANNEL_LIST_CNF_T;

typedef struct
{
    int             m_i4QualityIndex[128];
}FT_MATV_GET_CHANNEL_QUALITY_ALL_CNF_T;


META_RESULT  __stdcall SP_META_MATV_PowerOn(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_MATV_PowerOn_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_MATV_PowerOff(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_MATV_PowerOff_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_MATV_SetRegion(unsigned int ms_timeout, unsigned char region);
META_RESULT  __stdcall SP_META_MATV_SetRegion_r(const int meta_handle, unsigned int ms_timeout, unsigned char region);
META_RESULT  __stdcall SP_META_MATV_StartScan(unsigned int ms_timeout, unsigned int scanmode);
META_RESULT  __stdcall SP_META_MATV_StartScan_r(const int meta_handle, unsigned int ms_timeout, unsigned char scanmode);
META_RESULT  __stdcall SP_META_MATV_StartFullScan(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_MATV_StartFullScan_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_MATV_StopScan(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_MATV_StopScan_r(const int meta_handle, unsigned int ms_timeout);


META_RESULT  __stdcall SP_META_MATV_GetChannelList(unsigned int ms_timeout, FT_MATV_GET_CHANNEL_LIST_CNF_T* cnf);
META_RESULT  __stdcall SP_META_MATV_GetChannelList_r(const int meta_handle, unsigned int ms_timeout, FT_MATV_GET_CHANNEL_LIST_CNF_T* cnf);
META_RESULT  __stdcall SP_META_MATV_ChangeChannel(unsigned int ms_timeout, unsigned char channel);
META_RESULT  __stdcall SP_META_MATV_ChangeChannel_r(const int meta_handle, unsigned int ms_timeout, unsigned char channel);
META_RESULT  __stdcall SP_META_MATV_SetChannelProperty(unsigned int ms_timeout, FT_MATV_SET_CHANNEL_PROPERTY_REQ_T* req);
META_RESULT  __stdcall SP_META_MATV_SetChannelProperty_r(const int meta_handle, unsigned int ms_timeout, FT_MATV_SET_CHANNEL_PROPERTY_REQ_T* req);
META_RESULT  __stdcall SP_META_MATV_GetChannelQuality(unsigned int ms_timeout, unsigned short item, int *qualityindex);
META_RESULT  __stdcall SP_META_MATV_GetChannelQuality_r(const int meta_handle, unsigned int ms_timeout, unsigned short index, int *qualityindex);
META_RESULT  __stdcall SP_META_MATV_GetChannelQualityAll(unsigned int ms_timeout, FT_MATV_GET_CHANNEL_QUALITY_ALL_CNF_T* channel_quality);
META_RESULT  __stdcall SP_META_MATV_GetChannelQualityAll_r(const int meta_handle, unsigned int ms_timeout, FT_MATV_GET_CHANNEL_QUALITY_ALL_CNF_T* channel_quality);


//----------------------------------------------------------------//
//                              FM                                //
//----------------------------------------------------------------//

//--------------------------//
//    FM data structures    //
//--------------------------//
typedef enum
{
    FM_CHIP_ID_MT6189AN = 0,
    FM_CHIP_ID_MT6189BN_CN = 1,
    FM_CHIP_ID_MT6188A = 3,
    FM_CHIP_ID_MT6188C = 4,
    FM_CHIP_ID_MT6188D = 5,
    FM_CHIP_ID_MT6616 = 6,
	FM_CHIP_ID_AR1000 = 7,
	FM_CHIP_ID_MT6620 = 8

}FM_CHIP_ID_E;

typedef struct{
    unsigned char pty;         // 0~31 integer
    unsigned char rds_rbds;    // 0:RDS, 1:RBDS
    unsigned char dyn_pty;     // 0:static, 1:dynamic
    unsigned short pi_code;    // 2-byte hex
    unsigned char ps_buf[8];     // hex buf of PS
    unsigned char ps_len;      // length of PS, must be 0 / 8"
    unsigned char af;          // 0~204, 0:not used, 1~204:(87.5+0.1*af)MHz
    unsigned char ah;          // Artificial head, 0:no, 1:yes
    unsigned char stereo;      // 0:mono, 1:stereo
    unsigned char compress;    // Audio compress, 0:no, 1:yes
    unsigned char tp;          // traffic program, 0:no, 1:yes
    unsigned char ta;          // traffic announcement, 0:no, 1:yes
    unsigned char speech;      // 0:music, 1:speech
}FM_RDS_TX_REQ_T;

typedef struct
{
    unsigned char  m_ucChipId;
}FM_CHIP_ID_CNF_T;

typedef struct
{
	short m_i2CurFreq;  // freq range is [875, 1080]
}FM_FREQ_REQ_T;



typedef struct
{
    unsigned char m_ucSignalLevel;
}FM_RSSI_CNF_T;

typedef struct
{
	//unsigned char m_ucIfCnt;
	unsigned short m_u2IfCnt;
	
}FM_IF_CNT_CNF_T;

typedef struct
{
	unsigned short m_u2MonoOrStereo;  // 0: mono, 1: stereo
	unsigned short m_u2SblendOnOrOff; // 0: sblend off, 1: sblend on
	unsigned int   m_u4ItemValue;  // 0: disable, 1: enable

}FM_MONO_STEREO_BLEND_REQ_T;

typedef struct  // freq range is [875, 1080]
{
   short m_i2StartFreq;    // note: when we try to search next: start freq should <= stop freq 
   short m_i2StopFreq;     // note: when we try to search prev: start freq should >= stop freq

}FM_FREQ_RANGE_REQ_T;

typedef struct
{
	unsigned char m_ucExit;      // 0: don't exist, 1: exist
	short         m_i2ValidFreq; // -1: settings error, 0: invalid freq, others: 875-1080 valid

}FM_VAILD_FREQ_CNF_T;

typedef struct
{
   unsigned int m_u4RssiThreshold;

}FM_RSSI_THRESHOLD_REQ_T;

typedef struct
{
   unsigned int m_u4IfCntDelta;

}FM_IF_CNT_DELTA_REQ_T;


typedef struct
{
	unsigned char m_ucAddr;
	
}FM_READ_BYTE_ADDR_REQ_T;


typedef struct
{
   unsigned short m_u2ReadByte;

}FM_READ_BYTE_CNF_T;


typedef struct
{
	unsigned char m_ucAddr;
	unsigned short m_u2WriteByte;
}FM_WRITE_BYTE_REQ_T;

typedef struct
{
    unsigned char m_bOnOff;  // 0: off, 1: on

}FM_SOFT_MUTE_ONOFF_REQ_T;

typedef struct
{
	unsigned char m_ucStage;  // 1~3
}FM_STAGE_REQ_T;

typedef struct
{
	unsigned char  m_ucHighOrLow;
}FM_HL_Side_CNF_T;

typedef struct
{
	unsigned char m_ucStereoOrMono;

}FM_Stereo_Mono_CNF_T;

// for MT6616 new API
typedef struct
{
    unsigned char m_ucVolume;
    char m_cDigitalGainIndex;
}FM_Volume_Setting_REQ_T;

typedef struct
{
    unsigned short m_u2Bitmap[16];
}FM_AutoScan_CNF_T;

typedef struct
{
    unsigned char m_ucRDSOn;
}FM_SetRDS_REQ_T;

typedef struct
{
    unsigned char m_ucRXFilterBW;
}FM_RX_FilterBW_CNF_T;

typedef struct
{
    unsigned char m_ucPAMDLevel;
}FM_PAMD_Level_CNF_T;

typedef struct
{
    unsigned char m_ucMR;
}FM_MR_CNF_T;

typedef struct
{
    unsigned int m_u4DecodeMode;
}FM_Decode_Mode_REQ_T;

typedef struct
{
    unsigned int m_u4HCC;
}FM_HCC_REQ_T;

typedef struct
{
    unsigned int m_u4PAMDThreshold;
}FM_PAMD_Threshold_REQ_T;

typedef struct
{
    unsigned int m_u4SoftmuteEnable;
}FM_Softmute_Enable_REQ_T;

typedef struct
{
    unsigned int m_u4DeemphasisLevel;
}FM_Deemphasis_Level_REQ_T;

typedef struct
{
	unsigned int m_u4HLSide;
}FM_HL_Side_REQ_T;

typedef struct
{
    unsigned int m_u4DemodBandwidth;
}FM_Demod_Bandwidth_REQ_T;

typedef struct
{
    unsigned int m_u4DynamicLimiter;
}FM_DynamicLimiter_REQ_T;

typedef struct
{
    unsigned int m_u4SoftmuteRate;
}FM_Softmute_Rate_REQ_T;

typedef enum
{
    RDS_CMD_NONE = 0,   // No command. This is usually an error.
    RDS_CMD_PI_CODE,
    RDS_CMD_PTY_CODE,
    RDS_CMD_PROGRAMNAME,
    RDS_CMD_LOCDATETIME,
    RDS_CMD_UTCDATETIME,
    RDS_CMD_LAST_RADIOTEXT,
    RDS_CMD_AF,
    RDS_CMD_AF_LIST,  
    RDS_CMD_AFON,
    RDS_CMD_TAON,
    RDS_CMD_TAON_OFF
}RdsCmd;

typedef enum
{
    RDS_FLAG_IS_TP              	              = 0x0001, // Program is a traffic program
    RDS_FLAG_IS_TA                            = 0x0002, // Program currently broadcasts a traffic ann.
    RDS_FLAG_IS_MUSIC                     = 0x0004, // Program currently broadcasts music
    RDS_FLAG_IS_STEREO                  = 0x0008, // Program is transmitted in stereo
    RDS_FLAG_IS_ARTIFICIAL_HEAD = 0x0010, // Program is an artificial head recording
    RDS_FLAG_IS_COMPRESSED       = 0x0020, // Program content is compressed
    RDS_FLAG_IS_DYNAMIC_PTY       = 0x0040, // Program type can change 
    RDS_FLAG_TEXT_AB                      = 0x0080  // If this flag changes state, a new radio text 					 string begins
}RdsFlag;

typedef enum {
   RDS_EVENT_FLAGS          = 0x0001, // One of the RDS flags has changed state
   RDS_EVENT_PI_CODE        = 0x0002, // The program identification code has changed
   RDS_EVENT_PTY_CODE       = 0x0004, // The program type code has changed
   RDS_EVENT_PROGRAMNAME    = 0x0008, // The program name has changed
   RDS_EVENT_UTCDATETIME    = 0x0010, // A new UTC date/time is available
   RDS_EVENT_LOCDATETIME    = 0x0020, // A new local date/time is available
   RDS_EVENT_LAST_RADIOTEXT = 0x0040, // A radio text string was completed
   RDS_EVENT_AF                   = 0x0080, // Current Channel RF signal strength too weak, need do AF switch  
   RDS_EVENT_AF_LIST        = 0x0100, // An alternative frequency list is ready
   RDS_EVENT_AFON_LIST        = 0x0200, // An alternative frequency list is ready
   RDS_EVENT_TAON        = 0x0400,  // Other Network traffic announcement start
   RDS_EVENT_TAON_OFF        = 0x0800 // Other Network traffic announcement finished.
} RdsEvent;

typedef struct
{
    RdsCmd m_eCmd;
}FM_RDS_Info_REQ_T;

typedef struct
{
    unsigned char m_buffer[64];
}FM_RDS_Info_CNF_T;

typedef struct
{
    RdsFlag m_eFlag;
    unsigned char m_buffer[64];
}FM_RDS_Status_CNF_T;

typedef struct  
{
	char TP;
	char TA;
	char Music;
	char Stereo;
	char Artificial_Head;
	char Compressed;
	char Danamic_PTY;
	char Text_AB;
	int falg_status;
}RDSFlag_Struct;

typedef struct
{
        unsigned short Month;
        unsigned short Day;
        unsigned short Year;
        unsigned short Hour;
        unsigned short Minute;
        unsigned char Local_Time_offset_signebit;
        unsigned char Local_Time_offset_half_hour;
}CT_Struct;

typedef struct
{
    unsigned short m_u2GoodBlock;
}FM_RDS_Good_Block_Counter_CNF_T;

typedef struct
{
    unsigned short m_u2BadBlock;
}FM_RDS_Bad_Block_Counter_CNF_T;

typedef struct
{
    unsigned short m_u2GroupCounter[32];
}FM_RDS_Group_Counter_CNF_T;

typedef struct
{
    short m_i2StartFreq;
    unsigned char m_ucDirection;
}FM_HWSeek_REQ_T;

typedef struct
{
    short m_i2EndFreq;
}FM_HWSeek_CNF_T;


typedef struct
{
    unsigned short m_u2StereoBlendControl;
}FM_SetStereoBlend_REQ_T;

typedef struct
{
    unsigned short m_u2Blocks[5];
}FM_RDS_Block_CNF_T;


typedef enum
{
	FMTX_1K_TONE = 1, 
	FMTX_2K_TONE = 2,
	FMTX_3K_TONE = 3,
	FMTX_4K_TONE = 4,
	FMTX_5K_TONE = 5,
	FMTX_6K_TONE = 6,
	FMTX_7K_TONE = 7,
	FMTX_8K_TONE = 8,
	FMTX_9K_TONE = 9,
	FMTX_10K_TONE = 10,
	FMTX_11K_TONE = 11,
	FMTX_12K_TONE = 12,
	FMTX_13K_TONE = 13,
	FMTX_14K_TONE = 14,
	FMTX_15K_TONE = 15,
	FMTX_MAX_TONE
	
}FM_TX_TONE_T;

typedef enum
{
	FM_TX_AUDIO_ANALOG = 0,
	FM_TX_AUDIO_I2S = 1,
	FM_RX_AUDIO_ANALOG = 2,
	FM_RX_AUDIO_I2S = 3,
	FM_AUDIO_MAX
	
}FM_TX_AUDIO_PATH_T;

typedef struct
{
	FM_TX_AUDIO_PATH_T m_audioPath;
	
}FM_SetTxAudioPath_REQ_T;

typedef struct
{
	FM_TX_TONE_T m_audioFreq;
	
}FM_SetTxAudioFreq_REQ_T;



typedef struct  
{
	unsigned short DECODE_MODE;
	unsigned short STEREO_BLEND;
	unsigned short HCC;
	unsigned short PAMD_THRESHOLD;
	unsigned short RSSI_THRESHOLD;
	unsigned short SOFTMUTE;
	unsigned short COSTAS;
	unsigned short DE_EMPHASIS_LEV;
	unsigned short HL_SIDE;
	unsigned short DEMOD_BANDWIDTH;
	unsigned short DYNAMIC_LIMITER;
	unsigned short SOFTMUTE_RATE;
	unsigned short AFC;
	unsigned short SET_BW;
	unsigned short CAP_ARRAY;
	unsigned short DEMOD_TYPE;
}FM_SETStatus_REQ_T;

typedef struct  
{
	unsigned short RSSI;               //RSSI
	unsigned short RSSI_HEX;           //RSSI(Hex)
	unsigned short RSSI_DBM;            //
	unsigned short STA_BW;              //BW
	unsigned short PAMD;
	unsigned short PAMD_HEX;
	unsigned short PAMD_DBM;
	unsigned short MR;
	unsigned short STEREO_MONO;			//Stereo/Mono
	unsigned short BLEND_GAIN;			//Blend gain
	unsigned short BLEND_FILTER_NUMBER; //Blend filter number
	unsigned short SOFTMUTE_GMS;
	unsigned short SOFTMUTE_GFS;
	unsigned short DYNAMIC_GAIN;
	unsigned short PILOT_LOCKED_FLAG;
	unsigned short SOFTMUTE_SELECTION_FLAG;
	unsigned short RSSI_HCC;
	unsigned short PAMD_HCC;
	unsigned short RSSI_OFF_B;
	unsigned short RSSI_OFF_H;
	unsigned short PAMD_OFF_B;
	unsigned short PAMD_OFF_H;
	unsigned short HCC_FILTER;
	unsigned short SOFTMUTE_STEP;
	unsigned short GAIN_COUNTER;
	unsigned short PGA_GAIN;
	unsigned short LNA_GAIN;
	unsigned short PGA_GAIN_INDEX;
	unsigned short LNA_GAIN_INDEX;
	unsigned short TOTAL_GAIN;
	unsigned short PULSE_RATIO;
	unsigned short FAST_PAMD;
	unsigned short POWER_DETECTOR;
	unsigned short CHIP_ID;
}FM_Status_CNF_T;

//--------------------------//
//      FM Functions        //
//--------------------------//

META_RESULT  __stdcall SP_META_FM_SetRDSTX(unsigned int ms_timeout,FM_RDS_TX_REQ_T req );
META_RESULT  __stdcall SP_META_FM_SetRDSTX_r(const int meta_handle, unsigned int ms_timeout,FM_RDS_TX_REQ_T req);
META_RESULT  __stdcall SP_META_FM_SetStatus(unsigned int ms_timeout, char * fileName,FM_SETStatus_REQ_T req);
META_RESULT  __stdcall SP_META_FM_SetStatus_r(const int meta_handle, unsigned int ms_timeout, char * fileName,FM_SETStatus_REQ_T req);
META_RESULT  __stdcall SP_META_FM_GetStatus( unsigned int ms_timeout, char * fileName,FM_Status_CNF_T* cnf);
META_RESULT  __stdcall SP_META_FM_GetStatus_r(const int meta_handle, unsigned int ms_timeout, char * fileName,FM_Status_CNF_T* cnf);
META_RESULT  __stdcall SP_META_FM_GetChipId(unsigned int ms_timeout, FM_CHIP_ID_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetChipId_r(const int meta_handle, unsigned int ms_timeout, FM_CHIP_ID_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_PowerOn(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_PowerOn_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_TXPowerOn(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_TXPowerOn_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_PowerOff(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_PowerOff_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_TxSetFreq(unsigned int ms_timeout, FM_FREQ_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_TxSetFreq_r(const int meta_handle,unsigned int ms_timeout, FM_FREQ_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetFreq(unsigned int ms_timeout, FM_FREQ_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetFreq_r(const int meta_handle, unsigned int ms_timeout, FM_FREQ_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_GetRSSI(unsigned int ms_timeout, FM_FREQ_REQ_T *req, FM_RSSI_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetRSSI_r(const int meta_handle, unsigned int ms_timeout, FM_FREQ_REQ_T *req, FM_RSSI_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetIfCnt(unsigned int ms_timeout, FM_FREQ_REQ_T *req, FM_IF_CNT_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetIfCnt_r(const int meta_handle, unsigned int ms_timeout, FM_FREQ_REQ_T *req, FM_IF_CNT_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_SearchNextFreq(unsigned int ms_timeout, FM_FREQ_RANGE_REQ_T *req, FM_VAILD_FREQ_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_SearchNextFreq_r(const int meta_handle, unsigned int ms_timeout, FM_FREQ_RANGE_REQ_T *req, FM_VAILD_FREQ_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_SearchPrevFreq(unsigned int ms_timeout, FM_FREQ_RANGE_REQ_T *req, FM_VAILD_FREQ_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_SearchPrevFreq_r(const int meta_handle, unsigned int ms_timeout, FM_FREQ_RANGE_REQ_T *req, FM_VAILD_FREQ_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_SetMonoOrStereo_Blend(unsigned int ms_timeout, FM_MONO_STEREO_BLEND_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetMonoOrStereo_Blend_r(const int meta_handle, unsigned int ms_timeout, FM_MONO_STEREO_BLEND_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetRssiThreold(unsigned int ms_timeout, FM_RSSI_THRESHOLD_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetRssiThreold_r(const int meta_handle, unsigned int ms_timeout, FM_RSSI_THRESHOLD_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetIfCntDelta(unsigned int ms_timeout, FM_IF_CNT_DELTA_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetIfCntDelta_r(const int meta_handle, unsigned int ms_timeout, FM_IF_CNT_DELTA_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_ReadByte(unsigned int ms_timeout, FM_READ_BYTE_ADDR_REQ_T *req, FM_READ_BYTE_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_ReadByte_r(const int meta_handle, unsigned int ms_timeout, FM_READ_BYTE_ADDR_REQ_T *req, FM_READ_BYTE_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_WriteByte(unsigned int ms_timeout, FM_WRITE_BYTE_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_WriteByte_r(const int meta_handle, unsigned int ms_timeout, FM_WRITE_BYTE_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetSoftMute(unsigned int ms_timeout, FM_SOFT_MUTE_ONOFF_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetSoftMute_r(const int meta_handle, unsigned int ms_timeout, FM_SOFT_MUTE_ONOFF_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SelectSoftMuteStage(unsigned int ms_timeout, FM_STAGE_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SelectSoftMuteStage_r(const int meta_handle, unsigned int ms_timeout, FM_STAGE_REQ_T *req);
META_RESULT  __stdcall WM_META_FM_SelectSBlendStage(unsigned int ms_timeout, FM_STAGE_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SelectSBlendStage_r(const int meta_handle, unsigned int ms_timeout, FM_STAGE_REQ_T *req);
META_RESULT  __stdcall WM_META_FM_GetHighOrLowSide(unsigned int ms_timeout, FM_FREQ_REQ_T *req, FM_HL_Side_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetHighOrLowSide_r(const int meta_handle, unsigned int ms_timeout, FM_FREQ_REQ_T *req, FM_HL_Side_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetStereoOrMono(unsigned int ms_timeout, FM_Stereo_Mono_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetStereoOrMono_r(const int meta_handle, unsigned int ms_timeout, FM_Stereo_Mono_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_SetVolume(unsigned int ms_timeout, FM_Volume_Setting_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetVolume_r(const int meta_handle, unsigned int ms_timeout, FM_Volume_Setting_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_AutoScan(unsigned int ms_timeout, FM_AutoScan_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_AutoScan_r(const int meta_handle, unsigned int ms_timeout, FM_AutoScan_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_SetRDS(unsigned int ms_timeout, FM_SetRDS_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetRDS_r(const int meta_handle, unsigned int ms_timeout, FM_SetRDS_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_GetRXFilterBW(unsigned int ms_timeout, FM_RX_FilterBW_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetRXFilterBW_r(const int meta_handle, unsigned int ms_timeout, FM_RX_FilterBW_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetPAMDLevel(unsigned int ms_timeout, FM_FREQ_REQ_T *req, FM_PAMD_Level_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetPAMDLevel_r(const int meta_handle, unsigned int ms_timeout, FM_FREQ_REQ_T* req, FM_PAMD_Level_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetMR(unsigned int ms_timeout, FM_MR_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetMR_r(const int meta_handle, unsigned int ms_timeout, FM_MR_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_SetDecodeMode(unsigned int ms_timeout, FM_Decode_Mode_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetDecodeMode_r(const int meta_handle, unsigned int ms_timeout, FM_Decode_Mode_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetHCC(unsigned int ms_timeout, FM_HCC_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetHCC_r(const int meta_handle, unsigned int ms_timeout, FM_HCC_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetPAMDThreshold(unsigned int ms_timeout, FM_PAMD_Threshold_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetPAMDThreshold_r(const int meta_handle, unsigned int ms_timeout, FM_PAMD_Threshold_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_YUSU_SetSoftmute(unsigned int ms_timeout, FM_Softmute_Enable_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_YUSU_SetSoftmute_r(const int meta_handle, unsigned int ms_timeout, FM_Softmute_Enable_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetDeemphasisLevel(unsigned int ms_timeout, FM_Deemphasis_Level_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetDeemphasisLevel_r(const int meta_handle, unsigned int ms_timeout, FM_Deemphasis_Level_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetHLSide(unsigned int ms_timeout, FM_HL_Side_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetHLSide_r(const int meta_handle, unsigned int ms_timeout, FM_HL_Side_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetDemodBW(unsigned int ms_timeout, FM_Demod_Bandwidth_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetDemodBW_r(const int meta_handle, unsigned int ms_timeout, FM_Demod_Bandwidth_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetDynamicLimiter(unsigned int ms_timeout, FM_DynamicLimiter_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetDynamicLimiter_r(const int meta_handle, unsigned int ms_timeout, FM_DynamicLimiter_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetSoftmuteRate(unsigned int ms_timeout, FM_Softmute_Rate_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_SetSoftmuteRate_r(const int meta_handle, unsigned int ms_timeout, FM_Softmute_Rate_REQ_T *req);
META_RESULT  __stdcall SP_META_FM_GetPI(unsigned int ms_timeout, FM_RDS_Info_REQ_T *req, FM_RDS_Info_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetPI_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Info_REQ_T *req, FM_RDS_Info_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetPTY(unsigned int ms_timeout, FM_RDS_Info_REQ_T *req, FM_RDS_Info_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetPTY_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Info_REQ_T *req, FM_RDS_Info_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetPS(unsigned int ms_timeout, FM_RDS_Info_REQ_T *req, FM_RDS_Info_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetPS_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Info_REQ_T *req, FM_RDS_Info_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetAF(unsigned int ms_timeout, FM_RDS_Info_REQ_T *req, FM_RDS_Info_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetAF_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Info_REQ_T *req, FM_RDS_Info_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetRT(unsigned int ms_timeout, FM_RDS_Info_REQ_T *req, FM_RDS_Info_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetRT_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Info_REQ_T *req, FM_RDS_Info_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetTP(unsigned int ms_timeout, FM_RDS_Status_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetTP_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Status_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetTA(unsigned int ms_timeout, FM_RDS_Status_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetTA_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Status_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetMS(unsigned int ms_timeout, FM_RDS_Status_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetMS_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Status_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetGoodBlockCounter(unsigned int ms_timeout, FM_RDS_Good_Block_Counter_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetGoodBlockCounter_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Good_Block_Counter_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetBadBlockCounter(unsigned int ms_timeout, FM_RDS_Bad_Block_Counter_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetBadBlockCounter_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Bad_Block_Counter_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_ResetBlockCounter(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_ResetBlockCounter_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_GetGroupCounter(unsigned int ms_timeout, FM_RDS_Group_Counter_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_GetGroupCounter_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Group_Counter_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_ResetGroupCounter(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_ResetGroupCounter_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_HWSeek(unsigned int ms_timeout, FM_HWSeek_REQ_T *req, FM_HWSeek_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_HWSeek_r(const int meta_handle, unsigned int ms_timeout, FM_HWSeek_REQ_T *req, FM_HWSeek_CNF_T *cnf);
META_RESULT  __stdcall SP_META_FM_HWSearch_Stop(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_HWSearch_Stop_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_FM_SetStereoBlend(unsigned int ms_timeout, FM_SetStereoBlend_REQ_T* req);
META_RESULT  __stdcall SP_META_FM_SetStereoBlend_r(const int meta_handle, unsigned int ms_timeout, FM_SetStereoBlend_REQ_T* req);
META_RESULT  __stdcall SP_META_FM_GetRDSLogData(unsigned int ms_timeout, FM_RDS_Block_CNF_T* cnf);
META_RESULT  __stdcall SP_META_FM_GetRDSLogData_r(const int meta_handle, unsigned int ms_timeout, FM_RDS_Block_CNF_T* cnf);
META_RESULT  __stdcall SP_META_FM_GetRDSBLERRatio(unsigned int ms_timeout, unsigned short* bler);
META_RESULT  __stdcall SP_META_FM_GetRDSBLERRatio_r(const int meta_handle, unsigned int ms_timeout, unsigned short* bler);

META_RESULT  __stdcall SP_META_FM_SetTxAudioPath(unsigned int ms_timeout, FM_SetTxAudioPath_REQ_T path);
META_RESULT  __stdcall SP_META_FM_SetTxAudioPath_r(const int meta_handle, unsigned int ms_timeout, FM_SetTxAudioPath_REQ_T path);
META_RESULT  __stdcall SP_META_FM_SetTxAudioFreq(unsigned int ms_timeout, FM_SetTxAudioFreq_REQ_T freq);
META_RESULT  __stdcall SP_META_FM_SetTxAudioFreq_r(const int meta_handle, unsigned int ms_timeout, FM_SetTxAudioFreq_REQ_T freq);


typedef void (__stdcall *WM_META_FM_RDS_INFO_UPDATE_CNF)(const FM_RDS_Info_CNF_T *cnf, const short token, void *usrData);
typedef void (__stdcall *WM_META_FM_RDS_STATUS_UPDATE_CNF)(const FM_RDS_Status_CNF_T *cnf, const short token, void *usrData);
typedef struct
{
	WM_META_FM_RDS_INFO_UPDATE_CNF m_RDSInfoUpdateCallback;
	WM_META_FM_RDS_STATUS_UPDATE_CNF m_RDSStatusUpdateCallback;
} FM_RDSCallBack;

META_RESULT  __stdcall SP_META_FM_RegisterRDSInfoUpdateCallback(WM_META_FM_RDS_INFO_UPDATE_CNF cb);
META_RESULT  __stdcall SP_META_FM_RegisterRDSInfoUpdateCallback_r(const int meta_handle, WM_META_FM_RDS_INFO_UPDATE_CNF cb);
META_RESULT  __stdcall SP_META_FM_RegisterRDSStatusUpdateCallback(WM_META_FM_RDS_STATUS_UPDATE_CNF cb);
META_RESULT  __stdcall SP_META_FM_RegisterRDSStatusUpdateCallback_r(const int meta_handle, WM_META_FM_RDS_STATUS_UPDATE_CNF cb);
META_RESULT  __stdcall SP_META_FM_RemoveRDSInfoUpdateCallback(void);
META_RESULT  __stdcall SP_META_FM_RemoveRDSInfoUpdateCallback_r(const int meta_handle);
META_RESULT  __stdcall SP_META_FM_RemoveRDSStatusUpdateCallback(void);
META_RESULT  __stdcall SP_META_FM_RemoveRDSStatusUpdateCallback_r(const int meta_handle);

//----------------------------------------------------------------//
//                            TDMB                                //
//----------------------------------------------------------------//

//--------------------------//
//    TDMB data structures  //
//--------------------------//

typedef enum {   // ref from TDMB
   META_TDMB_KOREA_BAND=1,
   META_TDMB_BAND_III,
   META_TDMB_L_BAND,
   META_TDMB_CANADA_BAND,
   META_TDMB_CHINESE_BAND,
   META_TDMB_BAND_II,
   META_TDMB_BAND_IF,
   META_TDMB_UNDEF_BAND
} META_TDMB_BAND_enum;

typedef struct
{
    META_TDMB_BAND_enum  m_rBand;
	
}TDMB_SET_BAND_REQ_T;

typedef struct
{
   unsigned int  m_u4Freq;
}TDMB_SET_FREQ_REQ_T;



typedef struct
{
	unsigned char m_ucFreqNum;
	unsigned int m_u4Freq[10];
   
}TDMB_AUTO_SCAN_CNF_T;

// ========  for Ensemble ========


typedef struct
{
	//TDMB_DBSTATE	   DB;
	unsigned char        m_ucStateNum;
	unsigned int		 m_u4State[10];


	unsigned int		Type;   //DMB,DAB,DATA
	unsigned int		Id;
	unsigned int		BitRate;
	unsigned char		PL; //Protection Level
	unsigned char		Reg[8];
	unsigned short		UserApplType;		// added by KST 2006.07.20

	unsigned int		TMId;
	unsigned int		ASCTy_DSCTy;
	unsigned int		SCId;
	unsigned int		PackAdd;
	unsigned int		DG_MFflag;
	unsigned int		Primary;
	unsigned int		CAflag;
	unsigned int		Language;
	char				SCLabel[16];
 
	//TDMB_SvcComponentInfo	 *pSvcComp;
	unsigned char		SvcComp_Order;			// 4bits
	unsigned char		SvcComp_TMId;			// 2bits	Transport Mechanism Id
	unsigned char		SvcComp_ASCTy_DSCTy;	// 6bits	Audio Service Component Type	
	unsigned char		SvcComp_SubCh_FIDCId;	// 6bits	SubChId or FIDCId in FIG 0/4
	unsigned int		SvcComp_SId;			// 16bit
	unsigned char		SvcComp_CAflag;			// 1bit		CA Flag
	unsigned char		SvcComp_DG_MFflag;		// 1bit		DG Flag or MF flag
	unsigned char		SvcComp_Language;		// 8bit
	unsigned char		SvcComp_SCIdS;			// 4bit		Service component Identifier within ther Service
	unsigned char       SvcComp_SvcCompLabel[16];// 16bytes Service component Label	

	unsigned short		SvcComp_SCId;			// 12bits	Service Component Id
	unsigned short		SvcComp_PackAdd;		// 10bits	Packet Address
	unsigned short		SvcComp_SCCA;			// 16bits	Service Component Conditional Access

	unsigned short      SvcComp_m_encoded_id;   // Only for Frontier
    unsigned char       SvcComp_m_sif;          // Only for Frontier	


	//TDMB_SubChInfo			 *pSubCh;
	unsigned char	    SubChId;		// 6bits	Sub channel Id
	unsigned char	    TblIndex;		// 6bits	TableIndex
	unsigned char	    Form_Opt_Prot;  //[3] : FormFlag   //[2] : Option//[1~0] : protection
	unsigned short	    StrtAdd;		// 10bits	Start Address
	unsigned short	    SubChSize;		// 10bits	Sub channel size

	unsigned int		Tag;

}TDMB_CHANNELDB_T;


typedef struct
{
	// TDMB_DBSTATE
	unsigned char       m_ucStateNum;
	unsigned int		m_u4State[10];

	unsigned int		Id;
	char				Label[20];

	//TDMB_ServiceInfo  *pService;
	unsigned int		SId;			// 32bits	
	unsigned char		SvcLabel[16];	// 16bytes	Service Label(Program service and Data service)
	unsigned short		CharacterFlag;
	unsigned char		CAId;			// 3bit
	unsigned char		NumSvcComp;		// 4bits	Number of Service Component	


	//TDMB_CHANNELDB		*Channel;
    unsigned char     m_ucChannelDBNum;
	TDMB_CHANNELDB_T  m_rChannelDB[10];


	//struct _TDMB_SERVICEDB	*Next;
	unsigned int				Tag;
	unsigned int			ChannelCount;


}TDMB_SERVICEDB_T; 

typedef struct
{
	// TDMB_DBSTATE
	unsigned char        m_ucStateNum;
	unsigned int		 m_u4State[10];

	unsigned int		 Band;
    unsigned int		 Frequency;
    unsigned short		 Id;
    unsigned int		 SvcNum;
    unsigned int		 SvcCompNum;
    unsigned int		 SubChNum;
	char				 Label[20];

	// TDMB_EnsembleInfo
	unsigned char	AlFlag;				// 1bit		Al flag
	unsigned char   NumSubCh;
	unsigned char   NumSvc;
	unsigned char	NumProgram;
	unsigned char   NumSvcComp;
	unsigned char	NumUserApp;
	unsigned char	NumAnn;
	unsigned char	NumProgType;
	unsigned char	EnsemLabel[16];		// 16bytes	Ensemble Label
	unsigned short  CharacterFlag;
	unsigned short	EId;				// 16bits	country Id Ensemble reference

	// TDMB_SERVICEDB[]
	unsigned char   m_ucServiceDBNum;
	TDMB_SERVICEDB_T  m_rServiceDB[10];

	unsigned int     Tag;

}TDMB_ENSEMBLEDB_T;


typedef struct   // for META APP
{
   unsigned char      m_ucEnsembleNum;
   TDMB_ENSEMBLEDB_T  m_rEnsembleDB[10];

}TDMB_GET_ENSM_INFO_BY_AUTO_SCAN_CNF_T;

typedef struct   // for META APP
{
	char m_cResult; // 0: success, 
	                // 1: the band not exist  ==> META_TDMB_ERR_BAND_NOT_EXIST
	                // 2: frequency not exist ==> META_TDMB_ERR_FREQ_NOT_EXIST

	unsigned char      m_ucEnsembleNum;
    TDMB_ENSEMBLEDB_T  m_rEnsembleDB[10];
	TDMB_ENSEMBLEDB_T  m_rCurEnsembleDB;

}TDMB_SET_FREQ_CNF_T;


typedef struct
{
	unsigned short m_u2Snr;
	unsigned char  m_ucBer_a;  // a.b*10^-c
	unsigned char  m_ucBer_b;
	unsigned char  m_ucBer_c;
	short          m_i2RSSI; 

}TDMB_GET_SIGNAL_CNF_T;

typedef struct
{
	unsigned int m_u4ServiceId;
	unsigned int m_u4SubChnId;
	char         *m_pcfilepath; // store the TS stream data to this file 

}TDMB_SEL_SERVICE_REQ_T;

typedef struct  
{
	unsigned int m_u4ServiceId;
	unsigned int m_u4SubChnId;

}TDMB_SEL_SERVICE_ONLY_REQ_T;



typedef struct  //  for Meta APP only
{
	unsigned char      m_ucEnsembleNum;
    TDMB_ENSEMBLEDB_T  m_rEnsembleDB[10];
	TDMB_ENSEMBLEDB_T  m_rCurEnsembleDB;

}TDMB_GET_ENSM_CNF_T;
// --------------------------//
//      TDMB callback        //
// --------------------------//
typedef enum
{
    TDMB_FAT_DISK_FULL = 0
   ,TDMB_FAT_UNKNOWN_WRITE_ERROR
   ,TDMB_MED_MEMORY_FULL
   ,TDMB_MED_MEMORY_NOT_EXIST

}TDMB_SEL_SERV_ERROR_RESULT;

typedef void (__stdcall *META_TDMB_SEL_SERV_CNF)(const TDMB_SEL_SERV_ERROR_RESULT status);

//--------------------------//
//      TDMB Functions      //
//--------------------------//

META_RESULT  __stdcall SP_META_TDMB_TurnOn(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_TDMB_TurnOn_r(const int meta_handle, unsigned int ms_timeout);

// send band may return: META_TDMB_ERR_BAND_NOT_EXIST, META_SUCCESS, META_FAILED
META_RESULT __stdcall SP_META_TDMB_SetBand(unsigned int ms_timeout, TDMB_SET_BAND_REQ_T *req);
META_RESULT __stdcall SP_META_TDMB_SetBand_r(const int meta_handle, unsigned int ms_timeout, TDMB_SET_BAND_REQ_T *req);

META_RESULT __stdcall SP_META_TDMB_AutoScan_GetFreq(unsigned int ms_timeout, TDMB_AUTO_SCAN_CNF_T *cnf);
META_RESULT __stdcall SP_META_TDMB_AutoScan_GetFreq_r(const int meta_handle, unsigned int ms_timeout, TDMB_AUTO_SCAN_CNF_T *cnf);

META_RESULT __stdcall SP_META_TDMB_SetFreq(unsigned int ms_timeout, TDMB_SET_FREQ_REQ_T *req, TDMB_SET_FREQ_CNF_T *cnf);
META_RESULT __stdcall SP_META_TDMB_SetFreq_r(const int meta_handle, unsigned int ms_timeout, TDMB_SET_FREQ_REQ_T *req, TDMB_SET_FREQ_CNF_T *cnf);

META_RESULT __stdcall SP_META_TDMB_AutoScan_GetEnsemble(unsigned int ms_timeout, TDMB_GET_ENSM_INFO_BY_AUTO_SCAN_CNF_T *cnf);
META_RESULT __stdcall SP_META_TDMB_AutoScan_GetEnsemble_r(const int meta_handle, unsigned int ms_timeout, TDMB_GET_ENSM_INFO_BY_AUTO_SCAN_CNF_T *cnf);

META_RESULT __stdcall SP_META_TDMB_GetSignal(unsigned int ms_timeout, TDMB_GET_SIGNAL_CNF_T *cnf);
META_RESULT __stdcall SP_META_TDMB_GetSignal_r(const int meta_handle, unsigned int ms_timeout, TDMB_GET_SIGNAL_CNF_T *cnf);

//META_RESULT __stdcall META_TDMB_SelService(unsigned int ms_timeout, TDMB_SEL_SERVICE_REQ_T *req);
//META_RESULT __stdcall META_TDMB_SelService_r(const int meta_handle, unsigned int ms_timeout, TDMB_SEL_SERVICE_REQ_T *req);

META_RESULT __stdcall SP_META_TDMB_SelService(unsigned int ms_timeout, TDMB_SEL_SERVICE_REQ_T *req, const META_TDMB_SEL_SERV_CNF  cnf_cb);
META_RESULT __stdcall SP_META_TDMB_SelService_r(const int meta_handle, unsigned int ms_timeout, TDMB_SEL_SERVICE_REQ_T *req, const META_TDMB_SEL_SERV_CNF  cnf_cb);

//META_RESULT __stdcall META_TDMB_SetIdle(unsigned int ms_timeout);
//META_RESULT __stdcall META_TDMB_SetIdle_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT __stdcall SP_META_TDMB_SetIdle(unsigned int ms_timeout, CALLBACK_META_FAT_PROGRESS  cb_progress, void  *cb_progress_arg);
META_RESULT __stdcall SP_META_TDMB_SetIdle_r(const int meta_handle, unsigned int ms_timeout, CALLBACK_META_FAT_PROGRESS  cb_progress, void  *cb_progress_arg);


META_RESULT __stdcall SP_META_TDMB_TurnOff(unsigned int ms_timeout);
META_RESULT __stdcall SP_META_TDMB_TurnOff_r(const int meta_handle, unsigned int ms_timeout);

META_RESULT __stdcall SP_META_TDMB_GetEnsm(unsigned int ms_timeout, TDMB_GET_ENSM_CNF_T *cnf);
META_RESULT __stdcall SP_META_TDMB_GetEnsm_r(const int meta_handle, unsigned int ms_timeout, TDMB_GET_ENSM_CNF_T *cnf);

META_RESULT __stdcall SP_META_TDMB_SelServiceOnly( unsigned int ms_timeout, TDMB_SEL_SERVICE_ONLY_REQ_T *req);
META_RESULT __stdcall SP_META_TDMB_SelServiceOnly_r(const int meta_handle, unsigned int ms_timeout, TDMB_SEL_SERVICE_ONLY_REQ_T *);


META_RESULT __stdcall SP_META_TDMB_StopAutoScan(unsigned int ms_timeout);
META_RESULT __stdcall SP_META_TDMB_StopAutoScan_r(const int meta_handle, unsigned int ms_timeout);

/*
//----------------------------------------------------------------------------------//
//  WM_MetaTest: data structure definition
//-----------------------------------------------------------------------------------//
//  WM_CMD_SUM
#define SIZE_ARRAY_NTEST_WM_CMD_SUM_REQ_T	10
typedef struct 
{
	short	nTest[SIZE_ARRAY_NTEST_WM_CMD_SUM_REQ_T];
}WM_CMD_SUM_REQ_T;

typedef struct 
{
	short	nTestSum;
}WM_CMD_SUM_CNF_T;

//	WM_CMD_Query_If_Target_Support_DVBH
typedef struct 
{
	 short	notUsed;
}WM_CMD_Query_If_Target_Support_DVBH_REQ_T;

typedef struct 
{
	  bool		bSupportDVBH;
}WM_CMD_Query_If_Target_Support_DVBH_CNF_T;

  //WM_CMD_Active_Timer
typedef struct
{
	   unsigned int		nMsTimer;
}WM_CMD_Active_Timer_REQ_T;

typedef struct 
{
	   unsigned int		nRecNum;
	   unsigned int		nMs;
}WM_CMD_Active_Timer_CNF_T;

typedef enum{
	FILE_START = 0,
	FILE_ONGOING,
	FILE_CLOSE,
	FILE_ONCE
}WM_METATEST_FILE_OP_TYPE;

typedef struct{
	unsigned int	nReqWriteFileStatus;
}WM_CMD_WriteFile_REQ_T;

typedef struct{
	unsigned int	nCnfWriteFileStatus;
}WM_CMD_WriteFile_CNF_T;

typedef struct{
	unsigned int	nReqReadFileStatus;
}WM_CMD_ReadFile_REQ_T;

typedef struct{
	unsigned int	nCnfReadFileStatus;
}WM_CMD_ReadFile_CNF_T;


// ---------------------------------------------
//      WM_MetaTest: callback        
// ----------------------------------------------

typedef enum
{
    WM_CMD_SUM_SUCESS = 0
   ,WM_CMD_SUM_FAIL 
}WM_MetaTest_RESULT;
//------------------------------------------
//WM_MetaTest: export function definition
//-----------------------------------------
META_RESULT  __stdcall META_WmMetaTest_Sum(unsigned int  ms_timeout, WM_CMD_SUM_REQ_T *req, WM_CMD_SUM_CNF_T *cnf);
META_RESULT  __stdcall META_WmMetaTest_Sum_r(const int meta_handle,unsigned int  ms_timeout, WM_CMD_SUM_REQ_T *req, WM_CMD_SUM_CNF_T *cnf);
META_RESULT  __stdcall META_WmMetaTest_QueryIfTargetSupportDVBH(unsigned int  ms_timeout, WM_CMD_Query_If_Target_Support_DVBH_REQ_T *req, WM_CMD_Query_If_Target_Support_DVBH_CNF_T *cnf);
META_RESULT  __stdcall META_WmMetaTest_QueryIfTargetSupportDVBH_r(const int meta_handle,unsigned int  ms_timeout, WM_CMD_Query_If_Target_Support_DVBH_REQ_T *req, WM_CMD_Query_If_Target_Support_DVBH_CNF_T *cnf);
META_RESULT  __stdcall META_WmMetaTest_ActiveTimer(unsigned int  ms_timeout, WM_CMD_Active_Timer_REQ_T *req, WM_CMD_Active_Timer_CNF_T *cnf);
META_RESULT  __stdcall META_WmMetaTest_ActiveTimer_r(const int meta_handle,unsigned int  ms_timeout, WM_CMD_Active_Timer_REQ_T *req, WM_CMD_Active_Timer_CNF_T *cnf);
META_RESULT  __stdcall META_WmMetaTest_WriteFile(unsigned int  ms_timeout, WM_CMD_WriteFile_REQ_T *req, WM_CMD_WriteFile_CNF_T *cnf);
META_RESULT  __stdcall META_WmMetaTest_WriteFile_r(const int meta_handle,unsigned int  ms_timeout, WM_CMD_WriteFile_REQ_T *req, WM_CMD_WriteFile_CNF_T *cnf);
META_RESULT  __stdcall META_WmMetaTest_ReadFile(unsigned int  ms_timeout, WM_CMD_ReadFile_REQ_T *req, WM_CMD_ReadFile_CNF_T *cnf);
META_RESULT  __stdcall META_WmMetaTest_ReadFile_r(const int meta_handle,unsigned int  ms_timeout, WM_CMD_ReadFile_REQ_T *req, WM_CMD_ReadFile_CNF_T *cnf);
*/

//-----------------------------------------------------//
//  WM META UnitTest
//-----------------------------------------------------//

typedef struct {
	unsigned int	m_TestCaseID;
	const char *	m_pDescription;
} WM_META_UT_TestCaseID_T;

void __stdcall SP_META_QueryTestCase(WM_META_UT_TestCaseID_T  **ppTestCase, unsigned int  *pTestCaseCount);
void __stdcall SP_META_UnitTest(const unsigned int  *p_TestCaseID_Array, unsigned int  TestCaseCount);


// --------------------------------------------------------------------------------
//      WM_Battery:    data structure definition     addey by yuying 2008-12-18     
// --------------------------------------------------------------------------------
typedef enum{
	FILE_START,
	FILE_ONGOING,
	FILE_CLOSE,
	FILE_ONCE
}WM_Bat_Image_OP_TYPE;

typedef enum{
	FILE_Success,
	FILE_Fail
}WM_Bat_File_Err_TYPE;

 typedef enum{
  WM_BAT_WRITE_DATA=0,
  WM_BAT_COMPARA_DATA,
  WM_BAT_DELAY
}WM_BAT_Upload_OP_TYPE;

typedef struct{
	int				nReqDLImageStatus;
	unsigned int		image_size;  //the size of whole image
	unsigned int		block_size;  //the size of current transfer.
}WM_Bat_DLImage_REQ_T;

typedef struct{
	int	nCnfDLImageStatus;
	int    DL_Status;		//0-success 1-failed
}WM_Bat_DLImage_CNF_T;

typedef struct{
	//int	nReqUPImageStatus;
	WM_Bat_Image_OP_TYPE	nReqStartStatus;
 	WM_BAT_Upload_OP_TYPE 	nReqUpdateOpStatus;
  	char  					StartAddress;		
  	unsigned short 			delaytime;
	unsigned short			nLen;
	char					Buf[96];
}WM_Bat_UPImage_REQ_T;

typedef struct{
	WM_Bat_Image_OP_TYPE	nCnfStartStatus;	//0-first 1-
	int	nCnfUpdateStatus;  //0-success 1-fail
}WM_Bat_UPImage_CNF_T;


//export function
META_RESULT  __stdcall SP_META_Battery_DownloadImage(unsigned int ms_timeout, const WM_Bat_DLImage_REQ_T *req, WM_Bat_DLImage_CNF_T *cnf, char* fileAddress);
META_RESULT  __stdcall SP_META_Battery_DownloadImage_r(const int meta_handle,unsigned int ms_timeout, const WM_Bat_DLImage_REQ_T *req, WM_Bat_DLImage_CNF_T *cnf, char* fileAddress);

//META_RESULT  __stdcall META_Battery_UploadImage(unsigned int ms_timeout, const WM_Bat_UPImage_REQ_T *req, WM_Bat_UPImage_CNF_T *cnf,char* fileAddress);
//META_RESULT  __stdcall META_Battery_UploadImage_r(const int meta_handle,unsigned int ms_timeout, const WM_Bat_UPImage_REQ_T *req, WM_Bat_UPImage_CNF_T *cnf, char* fileAddress);



// --------------------------------------------------------------------------------
//      WM_Battery:    data structure definition
// --------------------------------------------------------------------------------

// 0  WM_CMD_DVB_Connect

typedef struct
{
	unsigned int Frequency;
	unsigned int BandWidth;
}DVB_CONNECT_REQ;

typedef struct
{
	int           drv_status;
}DVB_CONNECT_CNF;	

// 1  WM_CMD_DVB_Disconnect

typedef struct
{
	unsigned int NotUsed;
}DVB_DISCONNECT_REQ;

typedef struct{
	int           drv_status;
}DVB_DISCONNECT_CNF;

// 2 WM_CMD_DVB_Middleware_Update

typedef struct
{
	int 			FileStatus;
	unsigned int 	ImageSize;
	unsigned int 	BrockSize;
}DVB_MIDDLEWARE_UPDATE_REQ;

typedef struct
{
	int 	FileStatus;
	int		drv_status;
}DVB_MIDDLEWARE_UPDATE_CNF;


// 3 WM_CMD_DVB_Parameter_Calibration
typedef struct
{
	unsigned int NotUsed;
}DVB_PARAMETER_CALIBRATION_REQ;

typedef struct
{
	int           drv_status;
}DVB_PARAMETER_CALIBRATION_CNF;

// 4  WM_CMD_DVB_Get_Signal_Quality

typedef struct
{
	unsigned int NotUsed;
}DVB_GET_SIGNALQUALITY_REQ;

typedef struct
{
	unsigned char	SNRValue;
	char			Strength;
	unsigned int	TSPER;
	unsigned int	PostVBER;
	int				drv_status;
}DVB_GET_SIGNALQUALITY_CNF;

// 5  WM_CMD_DVB_Demodulator_IsAlive

typedef struct
{
	unsigned int NotUsed;
}DVB_DEMODULATOR_ISALIVE_REQ;

typedef struct
{
	int           drv_status;
}DVB_DEMODULATOR_ISALIVE_CNF;

// 6  WM_CMD_DVB_Set_TS_PacketBatch

typedef struct
{
	unsigned int BatchNum;
}DVB_SET_TS_PACKETBATCH_REQ;

typedef struct
{
	int           drv_status;
}DVB_SET_TS_PACKETBATCH_CNF;

// 7  WM_CMD_DVB_Set_TX_PacketTimeout

typedef struct
{
	unsigned int TimeOut;
}DVB_SET_TX_PACKETTIMEOUT_REQ;

typedef struct
{
	int           drv_status;
}DVB_SET_TX_PACKETTIMEOUT_CNF;

// 9  WM_CMD_DVB_Add_TS_PID

typedef struct
{
	unsigned int PIDValue;
}DVB_ADD_TS_PID_REQ;

typedef struct
{
	int           drv_status;
}DVB_ADD_TS_PID_CNF;

// 10  WM_CMD_DVB_Remove_TS_PID

typedef struct
{
	unsigned int PIDValue;
}DVB_REMOVE_TS_PID_REQ;

typedef struct
{
	int           drv_status;
}DVB_REMOVE_TS_PID_CNF;

// 11 WM_CMD_DVB_Disable_AllTS_PIDsFiltering

typedef struct
{
	unsigned int NotUsed;
}DVB_DISABLE_ALLTS_PIDFILTERING_REQ;

typedef struct
{
	int		drv_status;
}DVB_DISABLE_ALLTS_PIDFILTERING_CNF;

// 12 WM_CMD_DVB_Dump_TS_PacketstoSDCard

typedef struct
{
	unsigned int NotUsed;
}DVB_DUMP_TS_PACKETSTOSDCARD_REQ;

typedef struct
{
	int           drv_status;
}DVB_DUMP_TS_PACKETSTOSDCARD_CNF;

// 13 WM_CMD_DVB_Get_ReceptionMode

typedef struct
{
	unsigned int NotUsed;
}DVB_GET_RECEPTIONMODE_REQ;

typedef struct
{
	unsigned char	FFT;
	unsigned char	GI;
	unsigned char	CodeRate;
	unsigned char	Constellation;
	unsigned char	Hierarchy;
	unsigned char	HP_LP;
	unsigned char	HP_CodeRate;
	unsigned char	LP_CodeRate;
	unsigned char	Indepth;
	unsigned short	CellID;
	int				drv_status;
}DVB_GET_RECEPTIONMODE_CNF;


// 14 WM_CMD_DVB_Get_LockIndicator

typedef struct
{
	unsigned int NotUsed;
}DVB_GET_LOCKINDICATOR_REQ;

typedef struct
{
	unsigned char	AGCLock;
	unsigned char	MDLock;
	unsigned char	TPSLock;
	unsigned char	TSLock;
	unsigned char	CtrlStatus;
	unsigned char	SigStrength;
	unsigned char	SigQuality;
	short			InbandPow;
	short			WidebandPow;
	int				drv_status;
}DVB_GET_LOCKINDICATOR_CNF;

// 15 WM_CMD_DVB_Get_PerformanceInfo

typedef struct
{
	unsigned int NotUsed;
}DVB_GET_PERFORMANCEINFO_REQ;

typedef struct
{
    unsigned char	SNR;
    unsigned char	CCCICount;
    unsigned char	AR;
    unsigned char	FDBW;
    char			RFAGC;
    char			IFAGC;
    unsigned char	RFAGCState;
    unsigned char	ReceiveMode;
    unsigned char	ResetCount;
    unsigned char	AcqCount;
    unsigned char	Wbpd;
    unsigned char	AdcPow;
    unsigned short	INRCount;
    short			WinDrift;
    unsigned short	IQGain;
    unsigned short	TPSTime;
    unsigned short	TSTime;
    unsigned short	FER;
    unsigned short	MFER;
    unsigned int	PostBER;
    unsigned int	TSPER;
    unsigned int	TSBER;
    unsigned int	IQPhase;
    unsigned int	PhaseComp;
    int				CFOInit;
    int				CFOTra;
    int				TimeOffset;
    int				Tope;
	int				drv_status;
}DVB_GET_PERFORMANCEINFO_CNF;

// 16 WM_CMD_DVB_Get_Version

typedef struct
{
	unsigned int	NotUsed;
} DVB_GET_VERSION_REQ;

typedef struct
{
	char	Version[256];
	int		drv_status;
} DVB_GET_VERSION_CNF;

// 17 WM_CMD_DVB_Get_Debug_Counter

typedef struct
{
    unsigned int	NotUsed;
} DVB_GET_DEBUG_COUNTER_REQ;

typedef struct
{
	unsigned int	TSPacketNumber;
	unsigned int	OverflowCounter;
	unsigned int	InterruptCounter;
	int				drv_status;
} DVB_GET_DEBUG_COUNTER_CNF;


//export function
META_RESULT  __stdcall SP_META_DVB_Connect(unsigned int ms_timeout, const DVB_CONNECT_REQ *req, DVB_CONNECT_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Disconnect(unsigned int ms_timeout, const DVB_DISCONNECT_REQ *req, DVB_DISCONNECT_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Middleware_Update(unsigned int ms_timeout, const DVB_MIDDLEWARE_UPDATE_REQ *req, DVB_MIDDLEWARE_UPDATE_CNF *cnf,  char * fileAddress);
//META_RESULT  __stdcall META_DVB_Parameter_Calibration(unsigned int ms_timeout, const DVB_PARAMETER_CALIBRATION_REQ *req, DVB_PARAMETER_CALIBRATION_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Get_Signal_Quality(unsigned int ms_timeout, const DVB_GET_SIGNALQUALITY_REQ *req, DVB_GET_SIGNALQUALITY_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Demodulator_IsAlive(unsigned int ms_timeout, const DVB_DEMODULATOR_ISALIVE_REQ *req, DVB_DEMODULATOR_ISALIVE_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Set_TS_PacketBatch(unsigned int ms_timeout, const DVB_SET_TS_PACKETBATCH_REQ *req, DVB_SET_TS_PACKETBATCH_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Set_TX_PacketTimeout(unsigned int ms_timeout, const DVB_SET_TX_PACKETTIMEOUT_REQ *req, DVB_SET_TX_PACKETTIMEOUT_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Add_TS_PID(unsigned int ms_timeout, const DVB_ADD_TS_PID_REQ *req, DVB_ADD_TS_PID_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Remove_TS_PID(unsigned int ms_timeout, const DVB_REMOVE_TS_PID_REQ *req, DVB_REMOVE_TS_PID_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Disable_AllTS_PIDsFiltering(unsigned int ms_timeout, const DVB_DISABLE_ALLTS_PIDFILTERING_REQ *req, DVB_DISABLE_ALLTS_PIDFILTERING_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Dump_TS_PacketstoSDCard(unsigned int ms_timeout, const DVB_DUMP_TS_PACKETSTOSDCARD_REQ *req, DVB_DUMP_TS_PACKETSTOSDCARD_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Get_ReceptionMode(unsigned int ms_timeout, const DVB_GET_RECEPTIONMODE_REQ *req, DVB_GET_RECEPTIONMODE_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Get_LockIndicator(unsigned int ms_timeout, const DVB_GET_LOCKINDICATOR_REQ *req, DVB_GET_LOCKINDICATOR_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Get_PerformanceInfo(unsigned int ms_timeout, const DVB_GET_PERFORMANCEINFO_REQ *req, DVB_GET_PERFORMANCEINFO_CNF *cnf);

META_RESULT  __stdcall SP_META_DVB_Get_Version(unsigned int ms_timeout, const DVB_GET_VERSION_REQ *req, DVB_GET_VERSION_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Get_DebugCounter(unsigned int ms_timeout, const DVB_GET_DEBUG_COUNTER_REQ *req, DVB_GET_DEBUG_COUNTER_CNF *cnf);


META_RESULT  __stdcall SP_META_DVB_Connect_r(const int meta_handle, unsigned int ms_timeout, const DVB_CONNECT_REQ *req, DVB_CONNECT_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Disconnect_r(const int meta_handle, unsigned int ms_timeout, const DVB_DISCONNECT_REQ *req, DVB_DISCONNECT_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Middleware_Update_r(const int meta_handle, unsigned int ms_timeout, const DVB_MIDDLEWARE_UPDATE_REQ *req, DVB_MIDDLEWARE_UPDATE_CNF *cnf,  char * fileAddress);
//META_RESULT  __stdcall META_DVB_Parameter_Calibration_r(const int meta_handle, unsigned int ms_timeout, const DVB_PARAMETER_CALIBRATION_REQ *req, DVB_PARAMETER_CALIBRATION_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Get_Signal_Quality_r(const int meta_handle, unsigned int ms_timeout, const DVB_GET_SIGNALQUALITY_REQ *req, DVB_GET_SIGNALQUALITY_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Demodulator_IsAlive_r(const int meta_handle, unsigned int ms_timeout, const DVB_DEMODULATOR_ISALIVE_REQ *req, DVB_DEMODULATOR_ISALIVE_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Set_TS_PacketBatch_r(const int meta_handle, unsigned int ms_timeout, const DVB_SET_TS_PACKETBATCH_REQ *req, DVB_SET_TS_PACKETBATCH_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Set_TX_PacketTimeout_r(const int meta_handle, unsigned int ms_timeout, const DVB_SET_TX_PACKETTIMEOUT_REQ *req, DVB_SET_TX_PACKETTIMEOUT_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Add_TS_PID_r(const int meta_handle, unsigned int ms_timeout, const DVB_ADD_TS_PID_REQ *req, DVB_ADD_TS_PID_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Remove_TS_PID_r(const int meta_handle, unsigned int ms_timeout, const DVB_REMOVE_TS_PID_REQ *req, DVB_REMOVE_TS_PID_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Disable_AllTS_PIDsFiltering_r(const int meta_handle, unsigned int ms_timeout, const DVB_DISABLE_ALLTS_PIDFILTERING_REQ *req, DVB_DISABLE_ALLTS_PIDFILTERING_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Dump_TS_PacketstoSDCard_r(const int meta_handle, unsigned int ms_timeout, const DVB_DUMP_TS_PACKETSTOSDCARD_REQ *req, DVB_DUMP_TS_PACKETSTOSDCARD_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Get_ReceptionMode_r(const int meta_handle, unsigned int ms_timeout, const DVB_GET_RECEPTIONMODE_REQ *req, DVB_GET_RECEPTIONMODE_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Get_LockIndicator_r(const int meta_handle, unsigned int ms_timeout, const DVB_GET_LOCKINDICATOR_REQ *req, DVB_GET_LOCKINDICATOR_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Get_PerformanceInfo_r(const int meta_handle, unsigned int ms_timeout, const DVB_GET_PERFORMANCEINFO_REQ *req, DVB_GET_PERFORMANCEINFO_CNF *cnf);

META_RESULT  __stdcall SP_META_DVB_Get_Version_r(const int meta_handle, unsigned int ms_timeout, const DVB_GET_VERSION_REQ *req, DVB_GET_VERSION_CNF *cnf);
META_RESULT  __stdcall SP_META_DVB_Get_DebugCounter_r(const int meta_handle, unsigned int ms_timeout, const DVB_GET_DEBUG_COUNTER_REQ *req, DVB_GET_DEBUG_COUNTER_CNF *cnf);


//wifi
typedef struct
{    
	unsigned int		int_rx_ok_num;
	unsigned int		int_crc_err_num;
	unsigned int		int_rssi_max;
	unsigned int		int_rssi_min;
	unsigned int		int_rssi_mean;
	unsigned int		int_rssi_variance;
} WIFI_RXSTATUS_T;

typedef enum _ENUM_CFG_SRC_TYPE_T
{
	CFG_SRC_TYPE_EEPROM,	//cfg data is queried/set from/to EEPROM
	CFG_SRC_TYPE_NVRAM,		//cfg data is queried/set from/to NVRAM
	CFG_SRC_TYPE_BOTH,		//cfg data is queried/set from/to NVRAM, and E2PROM presents too
	CFG_SRC_TYPE_AUTO
} ENUM_CFG_SRC_TYPE_T;

META_RESULT  __stdcall SP_META_WiFi_QueryConfig(unsigned int ms_timeout, ENUM_CFG_SRC_TYPE_T *bufType);
META_RESULT  __stdcall SP_META_WiFi_setPacketRx_r(const int meta_handle, unsigned int ms_timeout, int condition, int nAntenna);
META_RESULT  __stdcall SP_META_WiFi_setPacketRx(unsigned int ms_timeout, int condition, int nAntenna);



META_RESULT  __stdcall SP_META_WiFi_readMCR32(unsigned int ms_timeout, unsigned int offset, unsigned long *value);
META_RESULT  __stdcall SP_META_WiFi_writeMCR32(unsigned int ms_timeout, unsigned int offset, unsigned int value);

#define SP_META_WiFi_readEEPRom16(ms_timeout, offset, value)	\
	META_WiFi_ReadConfigData(ms_timeout, offset, value, CFG_SRC_TYPE_AUTO)
#define SP_META_WiFi_writeEEPRom16(ms_timeout, offset, value)	\
	META_WiFi_WriteConfigData(ms_timeout, offset, value, CFG_SRC_TYPE_AUTO)

META_RESULT  __stdcall SP_META_WiFi_ReadConfigData(unsigned int ms_timeout, unsigned int offset, unsigned long *value, ENUM_CFG_SRC_TYPE_T type);
META_RESULT  __stdcall SP_META_WiFi_WriteConfigData(unsigned int ms_timeout, unsigned int offset, unsigned int value, ENUM_CFG_SRC_TYPE_T type);

META_RESULT  __stdcall SP_META_WiFi_eepromReadByteStr(unsigned int ms_timeout, unsigned int u4Addr, unsigned int u4Length, char *pszStr);
META_RESULT  __stdcall SP_META_WiFi_eepromWriteByteStr(unsigned int ms_timeout, unsigned int u4Addr, unsigned int u4Length, char *pszStr);
META_RESULT  __stdcall SP_META_WiFi_getChannel(unsigned int ms_timeout, long *channelConfig_p);
META_RESULT  __stdcall SP_META_WiFi_setPacketTxEx(unsigned int ms_timeout, int bufSize,	int bLongPreamble, int txRate, int pktCount, int pktInterval, int bGainControl, int gainControl, int bTrackAlc, int bTargetAlc, int targetAlcValue, int txAntenna);
META_RESULT  __stdcall SP_META_WiFi_GetATParam(unsigned int ms_timeout, unsigned int offset, unsigned long *value);
META_RESULT  __stdcall SP_META_WiFi_SetATParam(unsigned int ms_timeout, unsigned int offset, unsigned int value);
META_RESULT  __stdcall SP_META_WiFi_setOutputPower(unsigned int ms_timeout, int nTxRate, int txPower, int txAntenna);
META_RESULT  __stdcall SP_META_WiFi_setStandBy(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_WiFi_setCarrierSuppression(unsigned int ms_timeout, int nModulationType, int txPower, int txAntenna);
META_RESULT  __stdcall SP_META_WiFi_setLocalFrequecy(unsigned int ms_timeout, int txPower, int txAntenna);
META_RESULT  __stdcall SP_META_WiFi_setNormalMode(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_WiFi_setOutputPin(unsigned int ms_timeout, int pinIndex, int outputLevel);
META_RESULT  __stdcall SP_META_WiFi_setPnpPower(unsigned int ms_timeout, int i4PowerMode);
META_RESULT  __stdcall SP_META_WiFi_setTestMode(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_WiFi_setChannel(unsigned int ms_timeout, int channelConfig);
META_RESULT  __stdcall SP_META_WiFi_readTxPowerFromEEPromEx(unsigned int ms_timeout, int channelFreq, int rate, long *nTxPwr, long *outputPower, long *targetAlc);
META_RESULT  __stdcall SP_META_WiFi_getPacketRxStatus(unsigned int ms_timeout, WIFI_RXSTATUS_T *pRxStatus);

META_RESULT  __stdcall SP_META_WiFi_setXtalTrimToCr(unsigned int ms_timeout, unsigned int u4Value);
META_RESULT  __stdcall SP_META_WiFi_queryThermoInfo(unsigned int ms_timeout, long * pi4Enable, unsigned long * pu4RawVal);
META_RESULT  __stdcall SP_META_WiFi_setThermoEn(unsigned int ms_timeout, long i4Enable);


META_RESULT  __stdcall SP_META_WiFi_QueryConfig_r(int meta_handle, unsigned int ms_timeout, ENUM_CFG_SRC_TYPE_T *bufType);

META_RESULT  __stdcall SP_META_WiFi_readMCR32_r(const int meta_handle, unsigned int ms_timeout, unsigned int offset, unsigned long *value);
META_RESULT  __stdcall SP_META_WiFi_writeMCR32_r(const int meta_handle, unsigned int ms_timeout, unsigned int offset, unsigned int value);

#define SP_META_WiFi_readEEPRom16_r(meta_handle, ms_timeout, offset, value)	\
SP_META_WiFi_ReadConfigData_r(meta_handle, ms_timeout, offset, value, CFG_SRC_TYPE_AUTO)
#define SP_META_WiFi_writeEEPRom16_r(meta_handle, ms_timeout, offset, value)	\
SP_META_WiFi_WriteConfigData_r(meta_handle, ms_timeout, offset, value, CFG_SRC_TYPE_AUTO)

META_RESULT  __stdcall SP_META_WiFi_ReadConfigData_r(int meta_handle, unsigned int ms_timeout, unsigned int offset, unsigned long *value, ENUM_CFG_SRC_TYPE_T type);
META_RESULT  __stdcall SP_META_WiFi_WriteConfigData_r(int meta_handle, unsigned int ms_timeout, unsigned int offset, unsigned int value, ENUM_CFG_SRC_TYPE_T type);

META_RESULT  __stdcall SP_META_WiFi_eepromReadByteStr_r(const int meta_handle, unsigned int ms_timeout, unsigned int u4Addr, unsigned int u4Length, char *pszStr);
META_RESULT  __stdcall SP_META_WiFi_eepromWriteByteStr_r(const int meta_handle, unsigned int ms_timeout, unsigned int u4Addr, unsigned int u4Length, char *pszStr);
META_RESULT  __stdcall SP_META_WiFi_getChannel_r(const int meta_handle, unsigned int ms_timeout, long *channelConfig_p);
META_RESULT  __stdcall SP_META_WiFi_setPacketTxEx_r(const int meta_handle, unsigned int ms_timeout, int bufSize,	int bLongPreamble, int txRate, int pktCount, int pktInterval, int bGainControl, int gainControl, int bTrackAlc, int bTargetAlc, int targetAlcValue, int txAntenna);
META_RESULT  __stdcall SP_META_WiFi_GetATParam_r(const int meta_handle, unsigned int ms_timeout, unsigned int offset, unsigned long *value);
META_RESULT  __stdcall SP_META_WiFi_SetATParam_r(const int meta_handle, unsigned int ms_timeout, unsigned int offset, unsigned int value);
META_RESULT  __stdcall SP_META_WiFi_setOutputPower_r(const int meta_handle, unsigned int ms_timeout, int nTxRate, int txPower, int txAntenna);
META_RESULT  __stdcall SP_META_WiFi_setStandBy_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_WiFi_setCarrierSuppression_r(const int meta_handle, unsigned int ms_timeout, int nModulationType, int txPower, int txAntenna);
META_RESULT  __stdcall SP_META_WiFi_setLocalFrequecy_r(const int meta_handle, unsigned int ms_timeout, int txPower, int txAntenna);
META_RESULT  __stdcall SP_META_WiFi_setNormalMode_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_WiFi_setOutputPin_r(const int meta_handle, unsigned int ms_timeout, int pinIndex, int outputLevel);
META_RESULT  __stdcall SP_META_WiFi_setPnpPower_r(const int meta_handle, unsigned int ms_timeout, int i4PowerMode);
META_RESULT  __stdcall SP_META_WiFi_setTestMode_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_WiFi_setChannel_r(const int meta_handle, unsigned int ms_timeout, int channelConfig);
META_RESULT  __stdcall SP_META_WiFi_readTxPowerFromEEPromEx_r(const int meta_handle, unsigned int ms_timeout, int channelFreq, int rate, long *nTxPwr, long *outputPower, long *targetAlc);
META_RESULT  __stdcall SP_META_WiFi_getPacketRxStatus_r(const int meta_handle, unsigned int ms_timeout, WIFI_RXSTATUS_T *pRxStatus);
META_RESULT  __stdcall SP_META_WiFi_setXtalTrimToCr_r(const int meta_handle, unsigned int ms_timeout, unsigned int u4Value);
META_RESULT  __stdcall SP_META_WiFi_queryThermoInfo_r(const int meta_handle, unsigned int ms_timeout, long * pi4Enable, unsigned long * pu4RawVal);
META_RESULT  __stdcall SP_META_WiFi_setThermoEn_r(const int meta_handle, unsigned int ms_timeout, long i4Enable);

//add by dian.wang for MT6620
META_RESULT __stdcall SP_META_WiFi_readTxPower_r(const int meta_handle, unsigned int ms_timeout, unsigned long *value);
META_RESULT __stdcall SP_META_WiFi_setRxTest_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT __stdcall SP_META_WiFi_setBandwidth_r(const int meta_handle, unsigned int ms_timeout,unsigned int value);
META_RESULT __stdcall SP_META_WiFi_setGuardinterval_r(const int meta_handle, unsigned int ms_timeout,unsigned int value);
META_RESULT __stdcall SP_META_WiFi_setModeSelect_r(const int meta_handle, unsigned int ms_timeout,unsigned int value);
META_RESULT __stdcall SP_META_WiFi_setTxRxIQCalibration_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT __stdcall SP_META_WiFi_setDPDCalibration_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT __stdcall SP_META_WiFi_getResultInformation_r(const int meta_handle, unsigned int ms_timeout,unsigned int index,unsigned long * length);
META_RESULT __stdcall SP_META_WiFi_getCalResult_r(const int meta_handle, unsigned int ms_timeout,unsigned int index,unsigned int offset,unsigned long * data);
META_RESULT __stdcall SP_META_WiFi_getTemperatureSensorResult_r(const int meta_handle, unsigned int ms_timeout,unsigned long *value);
META_RESULT __stdcall SP_META_WiFi_getVoltageSensorResult_r(const int meta_handle, unsigned int ms_timeout,unsigned long *value);
META_RESULT __stdcall SP_META_WiFi_readEFuseAddr_r(const int meta_handle, unsigned int ms_timeout,unsigned int addr,unsigned long *value);
META_RESULT __stdcall SP_META_WiFi_writeEFuseAddr_r(const int meta_handle, unsigned int ms_timeout,unsigned int addr,unsigned int value);
META_RESULT __stdcall SP_META_WiFi_setTSSIEnableorDisable_r(const int meta_handle, unsigned int ms_timeout,unsigned int flag);
META_RESULT __stdcall SP_META_WiFi_getTSSICalibrationResult_r(const int meta_handle, unsigned int ms_timeout,unsigned long * value);
META_RESULT __stdcall SP_META_WiFi_setRate_r(const int meta_handle, unsigned int ms_timeout,unsigned long value);
META_RESULT __stdcall SP_META_WiFi_ReceivedErrorCount_r(const int meta_handle, unsigned int ms_timeout, unsigned long * value);
META_RESULT __stdcall SP_META_WiFi_ReceivedOKCount_r(const int meta_handle, unsigned int ms_timeout, unsigned long * value);
META_RESULT __stdcall SP_META_WiFi_GetChipVersion_r(const int meta_handle, unsigned int ms_timeout,unsigned long * chipVersion);

META_RESULT __stdcall SP_META_WiFi_readTxPower(unsigned int ms_timeout, unsigned long *value);
META_RESULT __stdcall SP_META_WiFi_setRxTest(unsigned int ms_timeout);
META_RESULT __stdcall SP_META_WiFi_setBandwidth(unsigned int ms_timeout,unsigned int value);
META_RESULT __stdcall SP_META_WiFi_setGuardinterval( unsigned int ms_timeout,unsigned int value);
META_RESULT __stdcall SP_META_WiFi_setModeSelect(unsigned int ms_timeout,unsigned int value);
META_RESULT __stdcall SP_META_WiFi_setTxRxIQCalibration( unsigned int ms_timeout);
META_RESULT __stdcall SP_META_WiFi_setDPDCalibration( unsigned int ms_timeout);
META_RESULT __stdcall SP_META_WiFi_getResultInformation( unsigned int ms_timeout,unsigned int index,unsigned long * length);
META_RESULT __stdcall SP_META_WiFi_getCalResult(unsigned int ms_timeout,unsigned int index,unsigned int offset,unsigned long * data);
META_RESULT __stdcall SP_META_WiFi_getTemperatureSensorResult( unsigned int ms_timeout,unsigned long *value);
META_RESULT __stdcall SP_META_WiFi_getVoltageSensorResult(unsigned int ms_timeout,unsigned long *value);
META_RESULT __stdcall SP_META_WiFi_readEFuseAddr( unsigned int ms_timeout,unsigned int addr,unsigned long *value);
META_RESULT __stdcall SP_META_WiFi_writeEFuseAddr(unsigned int ms_timeout,unsigned int addr,unsigned int value);
META_RESULT __stdcall SP_META_WiFi_setTSSIEnableorDisable(unsigned int ms_timeout,unsigned int flag);
META_RESULT __stdcall SP_META_WiFi_getTSSICalibrationResult( unsigned int ms_timeout,unsigned long * value);
META_RESULT __stdcall SP_META_WiFi_setRate(unsigned int ms_timeout,unsigned long value);
META_RESULT __stdcall SP_META_WiFi_ReceivedErrorCount(unsigned int ms_timeout, unsigned long * value);
META_RESULT __stdcall SP_META_WiFi_ReceivedOKCount(unsigned int ms_timeout, unsigned long * value);
META_RESULT __stdcall SP_META_WiFi_GetChipVersion( unsigned int ms_timeout,unsigned long * chipVersion);


//ui does not use, no test
#if 0
META_RESULT  __stdcall SP_META_WiFi_getPacketTxStatusEx(unsigned int ms_timeout, long *sentCount, long *ackCount, long *alc, 
												long *cckGainControl, long *ofdmGainControl);
META_RESULT  __stdcall SP_META_WiFi_setEEPRomFromFile(unsigned int ms_timeout, TCHAR* fileName);
META_RESULT  __stdcall SP_META_WiFi_setEEPromCKSUpdated(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_WiFi_setEEPRomSize(unsigned int ms_timeout, long eepromSz);
META_RESULT  __stdcall SP_META_WiFi_getChannelBand(unsigned int ms_timeout, long freq, long *channel, long *band);
META_RESULT  __stdcall SP_META_WiFi_getEEPRomSize(unsigned int ms_timeout, long *eepromSz);
META_RESULT  __stdcall SP_META_WiFi_setChipType(unsigned int ms_timeout, unsigned long u4ChipType);

META_RESULT  __stdcall SP_META_WiFi_getPacketTxStatusEx_r(const int meta_handle, unsigned int ms_timeout, long *sentCount, long *ackCount, long *alc, 
												long *cckGainControl, long *ofdmGainControl);
META_RESULT  __stdcall SP_META_WiFi_setEEPRomFromFile_r(const int meta_handle, unsigned int ms_timeout, TCHAR* fileName);
META_RESULT  __stdcall SP_META_WiFi_setEEPromCKSUpdated_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_WiFi_setEEPRomSize_r(const int meta_handle, unsigned int ms_timeout, long eepromSz);
META_RESULT  __stdcall SP_META_WiFi_getChannelBand_r(const int meta_handle, unsigned int ms_timeout, long freq, long *channel, long *band);
META_RESULT  __stdcall SP_META_WiFi_getEEPRomSize_r(const int meta_handle, unsigned int ms_timeout, long *eepromSz);
META_RESULT  __stdcall SP_META_WiFi_setChipType_r(const int meta_handle, unsigned int ms_timeout, unsigned long u4ChipType);
#endif

//Clean Boot Flag
META_RESULT __stdcall SP_META_SetCleanBootFlag(unsigned int ms_timeout,SetCleanBootFlag_REQ *req, SetCleanBootFlag_CNF *cnf);
META_RESULT __stdcall SP_META_SetCleanBootFlag_r(const int meta_handle,unsigned int ms_timeout,SetCleanBootFlag_REQ *req,SetCleanBootFlag_CNF *cnf);

//Battey FW/SOC info
typedef enum{
 BAT_READ_INFO_FAILED=0, 
 BAT_READ_INFO_SUCCESS,
 BAT_READ_FW_SUCCESS,
 BAT_READ_VBAT_SUCCESS 
}WM_Bat_READ_FW_TYPE;

 typedef enum{
	WM_BAT_SOC1_SETTINGS=0,
   	WM_BAT_SOC1_CLEAR
 }WM_BAT_SOC_TYPE;

typedef struct
{
  	int 		ibatteryinfo; //N/A
}WM_Bat_READ_FW_INFO_REQ_T;
 
typedef struct{
  	//int 		ibatteryinfo; //N/A
  	int		nReqReadSocType;	//0-setting, 1-clear
}WM_Bat_READ_SOC_REQ_T; 
 
typedef struct
{
  	//unsigned short 	SocValue; //N/A
  	unsigned char		SocValue;
  	unsigned char		SocClearValue;
  	int		nReqWriteSocType;	//0-setting, 1-clear
}WM_Bat_WRITE_SOC_REQ_T; 
 
typedef struct
{
	unsigned short	BQ27500_FW_Version;		//0xFFFF
	unsigned short	BQ27500_Battery_Voltage;	 //0xFFFF  
	unsigned short	BQ27500_DFI_Version;
//	WM_Bat_READ_FW_TYPE    Drv_Status; 	
  	int				Drv_Status;
 }WM_Bat_READ_FW_INFO_CNF_T;
 
typedef struct{	
	unsigned char   	BQ27500_SOC_Threshold;        //0xFFFF  
	unsigned char		BQ27500_SOC_ClearThreshold;
 	
	//WM_Bat_READ_FW_TYPE    	Drv_Status; 
	int				Drv_Status;
}WM_Bat_READ_SOC_CNF_T;
 
typedef struct{	    
 	//WM_Bat_READ_FW_TYPE    	Drv_Status; 
	int				Drv_Status;
}WM_Bat_WRITE_SOC_CNF_T;

META_RESULT  __stdcall SP_META_Battery_Read_FW_INFO(unsigned int ms_timeout, const WM_Bat_READ_FW_INFO_REQ_T *req,WM_Bat_READ_FW_INFO_CNF_T *cnf);
META_RESULT  __stdcall SP_META_Battery_Read_FW_INFO_r(const int meta_handle,unsigned int ms_timeout, const WM_Bat_READ_FW_INFO_REQ_T *req,WM_Bat_READ_FW_INFO_CNF_T *cnf);
META_RESULT  __stdcall SP_META_Battery_Read_SOC(unsigned int ms_timeout, const WM_Bat_READ_SOC_REQ_T *req, WM_Bat_READ_SOC_CNF_T *cnf);
META_RESULT  __stdcall SP_META_Battery_Read_SOC_r(const int meta_handle,unsigned int ms_timeout, const WM_Bat_READ_SOC_REQ_T *req, WM_Bat_READ_SOC_CNF_T *cnf);
META_RESULT  __stdcall SP_META_Battery_Write_SOC(unsigned int ms_timeout,const WM_Bat_WRITE_SOC_REQ_T *req, WM_Bat_WRITE_SOC_CNF_T *cnf); 
META_RESULT  __stdcall SP_META_Battery_Write_SOC_r(const int meta_handle,unsigned int ms_timeout, const WM_Bat_WRITE_SOC_REQ_T *req, WM_Bat_WRITE_SOC_CNF_T *cnf);
META_RESULT  __stdcall SP_META_Battery_Update_FW(unsigned int ms_timeout,const WM_Bat_UPImage_REQ_T*req, WM_Bat_UPImage_CNF_T *cnf); 
META_RESULT  __stdcall SP_META_Battery_Update_FW_r(const int meta_handle,unsigned int ms_timeout, const WM_Bat_UPImage_REQ_T *req, WM_Bat_UPImage_CNF_T *cnf);
META_RESULT  __stdcall SP_META_Battery_Enable_IT(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_Battery_Enable_IT_r(int meta_handle, unsigned int ms_timeout);

//GPS module
typedef struct{
	unsigned int	len;
	unsigned char	buff[1024];
}GPS_CMD; 

typedef struct {
	unsigned int	len;
	unsigned char	buff[1024];
}GPS_ACK_BUF;

//GPS callback
typedef void (__stdcall *META_GPS_SEND_COMMAND_CNF)(const GPS_ACK_BUF*cnf, const short token, void *usrData);

META_RESULT  __stdcall SP_META_GPS_Open(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_GPS_Open_r(const int meta_handle,unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_GPS_Close(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_GPS_Close_r(const int meta_handle,unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_GPS_SendCommand(unsigned int ms_timeout,const GPS_CMD *req, GPS_ACK_BUF *cnf,META_GPS_SEND_COMMAND_CNF cb);
META_RESULT  __stdcall SP_META_GPS_SendCommand_r(const int meta_handle,unsigned int ms_timeout,const GPS_CMD *req, GPS_ACK_BUF *cnf,META_GPS_SEND_COMMAND_CNF cb);


typedef struct
{
	unsigned int	dwSDHCIndex; // MSDC1/2/3. if dwSDHCIndex no equal 1/2/3 auto test.
}FT_SDCARD_REQ;

typedef struct
{
	BYTE			DatBusWidth;
	BOOL			IsSecuredMode;
	unsigned short	CardTpye;
	unsigned int	SizeOfProtectErea;
	BYTE			SpeedClass;
	BYTE			Performance_move;
	BYTE			AUSize;
	unsigned char	status;
}FT_SDCARD_CNF;

META_RESULT  __stdcall SP_META_SDCARD_Query(unsigned int ms_timeout,const FT_SDCARD_REQ *req, FT_SDCARD_CNF *cnf);
META_RESULT  __stdcall SP_META_SDCARD_Query_r(const int meta_handle,unsigned int ms_timeout,const FT_SDCARD_REQ *req, FT_SDCARD_CNF *cnf);

typedef struct
{
	unsigned long	time_duration;
}LCDFt_REQ;

typedef struct
{
	int status;
}LCDFt_CNF;

META_RESULT __stdcall SP_META_LcdColorTest(unsigned int ms_timeout, LCDFt_REQ *req, LCDFt_CNF *cnf);
META_RESULT __stdcall SP_META_LcdColorTest_r(const int meta_handle, unsigned int ms_timeout, LCDFt_REQ *req, LCDFt_CNF *cnf);

//Low Power
typedef enum
{
	WM_CMD_POWER_DOWN =0, 
	WM_CMD_POWER_UP,
}WM_LOW_POWER_TYPE;

META_RESULT __stdcall SP_META_LowPowerTest(unsigned int ms_timeout, WM_LOW_POWER_TYPE *ptype /*in & out*/);
META_RESULT __stdcall SP_META_LowPowerTest_r(int meta_handle, unsigned int ms_timeout, WM_LOW_POWER_TYPE *ptype /*in & out*/);


META_RESULT __stdcall SP_META_ReadUuid(unsigned int ms_timeout, UINT *high, UINT *low);
META_RESULT __stdcall SP_META_ReadUuid_r(int meta_handle, unsigned int ms_timeout, UINT *high, UINT *low);

META_RESULT __stdcall SP_META_WriteUuid(unsigned int ms_timeout, UINT high, UINT low);
META_RESULT __stdcall SP_META_WriteUuid_r(int meta_handle, unsigned int ms_timeout, UINT high, UINT low);




/*
typedef enum
{
    HW_GPIO0 = 0,
	HW_GPIO1,
	HW_GPIO2,
	...
	HW_GPIO146,
	HW_GPIO_MAX,
}HW_GPIO;          //pin number
*/
typedef enum
{
	GET_MODE_STA = 0,
	SET_MODE_0,  // 00
	SET_MODE_1,  // 01
	SET_MODE_2,  // 10
	SET_MODE_3,  // 11

	GET_DIR_STA, 
	SET_DIR_IN,  // 0
	SET_DIR_OUT, // 1
	
	GET_PULLEN_STA,  
	SET_PULLEN_DISABLE,  // 0
	SET_PULLEN_ENABLE,   // 1
	
	GET_PULL_STA,
	SET_PULL_DOWN,  // 0
	SET_PULL_UP,    // 1
	
	GET_INV_STA,
	SET_INV_ENABLE,  // 1
	SET_INV_DISABLE, // 0
	
	GET_DATA_IN,
	GET_DATA_OUT,
	SET_DATA_LOW,  // 0
	SET_DATA_HIGH, // 1

	SET_MODE_4,
	SET_MODE_5,
	SET_MODE_6,
	SET_MODE_7,


}GPIO_OP;

typedef struct
{
	UINT	pin;	// pin number
	GPIO_OP	op;		// operation to GPIO	
}GPIO_REQ;

typedef struct
{
	UINT	status;
	DWORD	data;
}GPIO_CNF;

META_RESULT __stdcall SP_META_GpioCtrl(unsigned int ms_timeout, const GPIO_REQ *req, GPIO_CNF *cnf);
META_RESULT __stdcall SP_META_GpioCtrl_r(int meta_handle, unsigned int ms_timeout, const GPIO_REQ *req, GPIO_CNF *cnf);


META_RESULT __stdcall SP_META_Nvram_Backup(unsigned int ms_timeout, const char *file1, const char *file2);
META_RESULT __stdcall SP_META_Nvram_Backup_r(int meta_handle, unsigned int ms_timeout, const char *file1, const char *file2);
META_RESULT __stdcall SP_META_Nvram_Backup_YUSU(unsigned int ms_timeout, const char *file);
META_RESULT __stdcall SP_META_Nvram_Backup_YUSU_r(int meta_handle, unsigned int ms_timeout, const char *file);

META_RESULT __stdcall SP_META_Nvram_Restore(unsigned int ms_timeout, const char *file1, const char *file2);
META_RESULT __stdcall SP_META_Nvram_Restore_r(int meta_handle, unsigned int ms_timeout, const char *file1, const char *file2);
META_RESULT __stdcall SP_META_Nvram_Restore_YUSU(unsigned int ms_timeout, const char *file);
META_RESULT __stdcall SP_META_Nvram_Restore_YUSU_r(int meta_handle, unsigned int ms_timeout, const char *file);

META_RESULT __stdcall SP_META_Clean_Boot(unsigned int ms_timeout);
META_RESULT __stdcall SP_META_Clean_Boot_r(int meta_handle,unsigned int ms_timeout);

META_RESULT __stdcall SP_META_Mode_Lock(unsigned int ms_timeout);
META_RESULT __stdcall SP_META_Mode_Lock_r(int meta_handle,unsigned int ms_timeout);

typedef struct
{
	char mldrVersion[50];
	char ebootVersion[50];
	char flashVersion[50];
	WORD mldrCheckSum;
	WORD ebootCheckSum;
	WORD flashCheckSum;
	BYTE status;
}FT_BTLDR_FLASH_VER_CNF;

META_RESULT __stdcall SP_META_Btldr_Flash_Ver(unsigned int ms_timeout, FT_BTLDR_FLASH_VER_CNF *cnf);
META_RESULT __stdcall SP_META_Btldr_Flash_Ver_r(int meta_handle, unsigned int ms_timeout, FT_BTLDR_FLASH_VER_CNF *cnf);


META_RESULT __stdcall SP_META_EciPortTest(unsigned int ms_timeout, DWORD portIdx);
META_RESULT __stdcall SP_META_EciPortTest_r(int meta_handle, unsigned int ms_timeout, DWORD portIdx);


META_RESULT __stdcall SP_META_Nvram2Bin(unsigned int ms_timeout);
META_RESULT __stdcall SP_META_Nvram2Bin_r(int meta_handle, unsigned int ms_timeout);




#define MD_FRAME_MAX_LEN 256

typedef struct
{
    short	frame_length;
    char	frame_data[MD_FRAME_MAX_LEN]; 
}MD_FRAME;

typedef struct _AUDIO_VOLUME_CUSTOM_STRUCT
{
	unsigned char audiovolume_ring[3][7];
	unsigned char audiovolume_key[3][7];
	unsigned char audiovolume_mic[3][7];
	unsigned char audiovolume_fmr[3][7];
	unsigned char audiovolume_sph[3][7];
	unsigned char audiovolume_sid[3][7];
	unsigned char audiovolume_media[3][7];
	unsigned char audiovolume_matv[3][7];
} AUDIO_VOLUME_CUSTOM_STRUCT;

typedef struct 
{
	short speech_input_FIR_coeffs[8][45];
	short speech_output_FIR_coeffs[8][6][45];
	short select_FIR_output_index[8];
	short select_FIR_intput_index[8];
	short speech_mode_para[8][16];
	
}AUDIO_PARAM_MED_STRUCT;

typedef struct
{
	unsigned short speech_mode_wb_para[8][16];
	short sph_wb_in_fir[6][90];
	short sph_wb_out_fir[6][90];
	
}AUDIO_CUSTOM_WB_PARAM_STRUCT;

META_RESULT __stdcall SP_META_SendMDCmd(unsigned int ms_timeout, MD_FRAME *frame/*in & out*/);
META_RESULT __stdcall SP_META_SendMDCmd_r(int meta_handle, unsigned int ms_timeout, MD_FRAME *frame/*in & out*/);
META_RESULT __stdcall SP_META_SwitchUsbChnl(BOOL enter, const WM_META_ConnectInMETA_Req *req, int *p_bootstop, WM_META_ConnectInMETA_Report *p_report);
META_RESULT __stdcall SP_META_SwitchUsbChnl_r(int meta_handle, BOOL enter, const WM_META_ConnectInMETA_Req *req, int *p_bootstop, WM_META_ConnectInMETA_Report *p_report);

META_RESULT  __stdcall SP_META_NVRAM_Compose_AudioVlomeCustomStruct(AUDIO_VOLUME_CUSTOM_STRUCT *param, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_AudioVlomeCustomStruct(AUDIO_VOLUME_CUSTOM_STRUCT *param, const char *buf, const int buf_len);

META_RESULT  __stdcall SP_META_NVRAM_Compose_AudioMedStruct(AUDIO_PARAM_MED_STRUCT *param, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_AudioMedStruct(AUDIO_PARAM_MED_STRUCT *param, const char *buf, const int buf_len);

META_RESULT  __stdcall SP_META_NVRAM_Compose_AudioCustomWBStruct(AUDIO_CUSTOM_WB_PARAM_STRUCT *param, char *buf, const int buf_len);
META_RESULT  __stdcall SP_META_NVRAM_Decompose_AudioCustomWBStruct(AUDIO_CUSTOM_WB_PARAM_STRUCT *param, const char *buf, const int buf_len);


META_RESULT __stdcall SP_META_Nvram_Backup_Custom(unsigned int ms_timeout, 
													const char *file1, const char *file2,const char * buffer,  int count, int mode );

META_RESULT __stdcall SP_META_Nvram_Backup_Custom_r(int meta_handle, unsigned int ms_timeout, 
										const char *file1, const char *file2,const char * buffer,  int count, int mode );

META_RESULT  __stdcall SP_META_Audio_Set_Echo_Loop2(unsigned int  ms_timeout,const Audio_Set_Echo_Req  *req);
META_RESULT  __stdcall SP_META_Audio_Set_Echo_Loop2_r(const int meta_handle,unsigned int  ms_timeout ,const Audio_Set_Echo_Req  *req);


META_RESULT __stdcall SP_META_Customer_Func(int ms_timeout, const unsigned char *data_in, const int data_in_len, unsigned char *data_out, int *data_out_len);
META_RESULT __stdcall SP_META_Customer_Func_r(int meta_handle, int ms_timeout, const unsigned char *data_in, const int data_in_len, unsigned char *data_out, int *data_out_len);

META_RESULT  __stdcall SP_META_GetChipID(unsigned int  ms_timeout, unsigned char* ChipID);
META_RESULT  __stdcall SP_META_GetChipID_r(const int meta_handle, unsigned int  ms_timeout, unsigned char* ChipID);

META_RESULT  __stdcall SP_META_MSensorTest(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_MSensorTest_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CTPTest(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CTPTest_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_ALSPSTest(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_ALSPSTest_r(const int meta_handle, unsigned int  ms_timeout);




//CMMB

#define MAX_CHANNEL_INFO_NUM    36
#define MAX_SERVICE_NUM   40

typedef struct
{
	int channel;
	int freq;
	
} CMMB_CHANNEL_INFO_S;

typedef struct
{
    int flag;              /*  flag = 0 means continuous confirm  */
                               /*  flag = 1 means all confirms have been received  */
    unsigned int    num;
    CMMB_CHANNEL_INFO_S    chInfo[MAX_CHANNEL_INFO_NUM];
    
} CMMB_CHANNEL_LIST_S;

typedef struct
{
    int flag;              /*  flag = 0 means continuous confirm  */
                               /*  flag = 1 means all confirms have been received  */
    unsigned int    num;
    int    servID[MAX_SERVICE_NUM];
    
} CMMB_SERVICE_LIST_S;

typedef struct
{
    int servID;
    char szMfsFile[260];
    
} CMMB_START_SERV_PARAM_S;

typedef struct
{
    int SNR;
    int PRE_BER;
    int RSSI;
    
} CMMB_PROPS_S;

META_RESULT  __stdcall SP_META_CMMB_Init(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_Init_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_Term(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_Term_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_AutoScan(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_AutoScan_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_CancelScan(unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_CancelScan_r(const int meta_handle, unsigned int ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_SetChannel(unsigned int  ms_timeout, int channel);
META_RESULT  __stdcall SP_META_CMMB_SetChannel_r(const int meta_handle, unsigned int  ms_timeout, int channel);
META_RESULT  __stdcall SP_META_CMMB_ListServices(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_ListServices_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_StartService(unsigned int  ms_timeout, CMMB_START_SERV_PARAM_S * servParam);
META_RESULT  __stdcall SP_META_CMMB_StartService_r(const int meta_handle, unsigned int  ms_timeout, CMMB_START_SERV_PARAM_S * servParam);
META_RESULT  __stdcall SP_META_CMMB_StopService(unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_StopService_r(const int meta_handle, unsigned int  ms_timeout);
META_RESULT  __stdcall SP_META_CMMB_GetProp(unsigned int  ms_timeout, CMMB_PROPS_S * prop);
META_RESULT  __stdcall SP_META_CMMB_GetProp_r(const int meta_handle, unsigned int  ms_timeout, CMMB_PROPS_S * prop);

META_RESULT  __stdcall SP_META_CMMB_QueryChannelList(CMMB_CHANNEL_LIST_S * chList);
META_RESULT  __stdcall SP_META_CMMB_QueryChannelList_r(const int meta_handle, CMMB_CHANNEL_LIST_S * chList);
META_RESULT  __stdcall SP_META_CMMB_QueryServiceList(CMMB_SERVICE_LIST_S * servList);
META_RESULT  __stdcall SP_META_CMMB_QueryServiceList_r(const int meta_handle, CMMB_SERVICE_LIST_S * servList);



// CCT
typedef struct
{
	char sensor_prefix_name[64];
}CCT_Dual_Dev_ISP_camera_sensor_prefix_name_struct;

typedef struct
{
	char lens_prefix_name[64];
}CCT_Dual_Dev_ISP_camera_lens_prefix_name_struct; 

//-------------END---------------

//};

#ifdef __cplusplus
}
#endif

#endif







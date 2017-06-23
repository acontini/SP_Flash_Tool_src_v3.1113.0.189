/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2002
*
*****************************************************************************/

/*******************************************************************************
* Filename:
* ---------
*  tboot_1.h
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  header file of Boot ROM communicate thread
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.9  $
* $Modtime:   Oct 19 2005 11:15:18  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/TBOOT_1.H-arc  $
 *
 * Sep 1 2008 MTK01952
 * [STP100001792] [FlashTool] v3.0836
 * New feature:
 * 1. Add the upload files funcitonality 
 *
 * Aug 7 2008 MTK01952
 * [STP100001779] [FlashTool] v3.0828.00
 * New features:
 *  1. Add the backup and restore functinality 
 *
 * May 19 2008 MTK01952
 * [STP100001712] [FlashTool] GPS download Phase 2
 * 
 *
 * Mar 5 2008 MTK01952
 * [STP100001655] [FlashTool] v3.0808.0 DRAM Testing of Memory Test
 * 
 *
 * Dec 3 2007 mtk01413
 * [STP100001568] [FlashTool] v3.0748.0 release
 * New features:
 *  1. USB Download on MT6225/MT6226/MT6227 Series BB
 *  2. GPS Download
 *  3. NOR+SDR in MT6238
 *
 * Aug 30 2007 mtk01413
 * [STP100001497] [FlashTool] v3.2.0 release
 * 
 *
 * May 18 2007 mtk01413
 * [STP100001402] FlashTool v3.1.05 release
 * 
 *
 * Mar 12 2007 mtk01413
 * [STP100001329] FlashTool v3.1.04 release
 * Enhancements:
 *  1. [FlashTool] Show Parameter List View automatically when loading secure-on MAUI
 *  2. [FlashTool] Move "Paremeter"/ "File Management"/ "ROM Writer" under "Window" menu item
 *  3. [FlashTool] Show DA version and Build Date in help dialog
 * 
 *
 * Aug 14 2006 mtk00539
 * [STP100001057] FlashTool v3.1.00 release
 * 
 *
 * Mar 22 2006 mtk00539
 * [STP100000703] FlashTool v2.7.1017
 * [FlashTool] Use known BBCHIP_TYPE and EXT_CLOCK to increase start command hit rate in "Reset to Factory Default" procedure.
 * 
 *    Rev 1.9   Oct 19 2005 14:47:26   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1008. 
 * Resolution for 141: [FlashTool v2.7.1008][New] Support NFB download and many new features.
 * 
 *    Rev 1.8   May 24 2005 20:03:42   mtk00539
 *  1. [FlashTool][New] Reset FAT to factory default setting. 
 *  2. [FlashTool][New] Option to enable/disable resource project id comparison. 
 * Resolution for 116: [FlashTool v2.6.1012][New] Reset FAT to factory default setting.
 * 
 *    Rev 1.7   Feb 16 2005 17:27:44   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1009 to support SPANSION S71AL016D and SHARP LRS18C8A flash. 
 *  2. [FlashTool][Enhance] Allow to setup EMI setting in TestMode.
 *  3. [FlashTool][Enhance] Keep TestMode unless you disable it. In order to allow users to do test continuously.
 *  4. [FlashTool][Enhance] Add CTRL+S hot-key to save TestMode log into file.
 * Resolution for 106: [FlashTool v2.6.1009][New] Adapt new BROM_DLL&DA v2.4.1009 to support SPANSION S71AL016D and SHARP LRS18C8A flash.
 * 
 *    Rev 1.6   May 21 2004 15:54:54   mtk00539
 *  1. [FlashTool][BUF FIX] fix incorrect error message of resource detection.
 * Resolution for 71: [FlashTool v2.5.1010][BUF FIX] fix incorrect error message of resource detection.
 * 
 *    Rev 1.5   May 14 2004 17:04:22   mtk00539
 *  1. [FlashTool][New] add CTRL+ALT+O hot-key to toggle Advanced Option Mode.
 *  2. [FlashTool][New] add FAT auto format mechanism.
 *  3. [FlashTool][New] add DA auto selection mechanism.
 *  4. [FlashTool][New] add STOP button.
 *  5. [FlashTool][Enhance] start timer when BootROM start cmd pass.
 *  6. [FlashTool][New] display flash info in status bar hint.
 *  7. [FlashTool][New] display format range info in format progress bar hint.
 *  8. [FlashTool][New] record the DA, Scatter and DL path separately.
 * Resolution for 68: [FlashTool v2.5.1009][New] add FAT auto format, DA auto selection mechanism and lots of enhancements.
 * 
 *    Rev 1.4   Sep 25 2003 14:03:28   mtk00539
 * adapt brom.dll v2.1.1001, please see SCR(29) for more details.
 * Resolution for 29: [FlashTool v2.4.1001][New] See the reasons below.
 * 
 *    Rev 1.3   Jun 30 2003 19:19:36   mtk00539
 *  1. [FlashTool][Add Features] Split flashtool function into brom.dll
 *  2. [FlashTool][Add Features] Format function: users can format any range you want without downloading procedure.
 *  3. [FlashTool][Add Features] Report format percentage.
 *  4. [FlashTool][Add Features] Check format range.
 *  5. [FlashTool][Add Features] Merge FlashTool for Pluto version.
 *  6. [FlashTool][Add Features] Runtime debug log: you can press (CTRL+ALT+T) to enable/disable debug log whenever you want.
 *  7. [FlashTool][Add Features] Forcedly Stop hot-key: you can forcedly stop FlashTool by pressing CTRL+Z.
 *  8. [FlashTool][BUG FIXED] Fix FlashTool MEM_CMD end_addr bug, FlashTool should use (begin_addr+length-1) as end_addr.
 * Resolution for 11: [FlashTool v2.3.1001][New Version] Split flashtool function into brom.dll
 * 
 *    Rev 1.2   Jun 03 2003 22:24:56   mtk00539
 * 1. extend timeout to 10 sec for large image download in boot_2.cpp
 * 2. disable unnecesssary debug hot-key.
 * 3. add shift+ctrl+A for Jensen's DA debug tool kit.
 * 4. enable build number, and start from 1003.
 * 5. save baseband chip type, mcu frequency and auto-memory wait state setup flag to ini file.
 * 6. add DA_SET_REG_CMD command and remove FINISH_CMD, so that release power key could be issued from FlashTool, not hardcoded in DA.
 * 7. add DA_MCU_FREQ_CMD command, so that we don't have to select different DA while switching frequency.
 * 8. add new flash MB84VD23280FA-70 for Chicago project.
 * 9. remove DEVICE_CMD, DA will check flash automatically and report the flash type to PC.
 * 10. add DA_FORMAT_CMD command to support range format.
 * 11. display flash type on FlashTool.
 * 12. merge the DOWNLOAD.H header file, both FlashTool and DA will use the same header file.
 * 13. modify SPEED_CMD handshake by adding a sync mechanism to detect whether if the speed change is done by both sides.
 * Resolution for 7: [FlashTool v2.2.1003][AddFeature] Enhanced for KLM and Chicago project.
 * 
 *    Rev 1.1   Jul 26 2002 11:52:20   admin
 * ver 0726
 * 
 *    Rev 1.0   Jul 20 2002 19:26:16   admin
 * Initial revision.
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/
//---------------------------------------------------------------------------

#ifndef tboot_1H
#define tboot_1H
//---------------------------------------------------------------------------
#include <Classes.hpp>

//#include "GCIO_XP.H"
#include "meta.h"
#include "general.h"
#include "metaapp_common.h"
#include "IMEI_common.h"
#include "eboot\interface.h"
#include "com_enum.h"
#include "com_util.h"
#include "oxdevicequery.h"
#include "frm_IMEIDownload.h"
//#include "frm_RestoreNVRAM.h"
#include "frm_FourInOne.h"
#include "BromDLLWrapper.h"
#include "Logger.h"
#include "FileUtils.h"
#include "RegionFormatSetting.h"
#include "BackupConfig.h"

#include <vector>
#include <set>
#include <map>

// Count of images are locked
typedef enum
{
    NONE_IMG_LOCKED  = 0,
    PARTIAL_IMG_LOCKED  = 1,
    ALL_IMG_LOCKED = 2
} COUNT_IMG_LOCKED;

using namespace std;
class BackupInfo;
//---------------------------------------------------------------------------
class tboot_1 : public TThread
{
protected:
        void _fastcall Execute();
        void FlashTool();
        void DebugDA();

public:
        __fastcall tboot_1( bool CreateSuspended );
		__fastcall ~tboot_1();
//        void cb_sp_dl_progress(int progress);
		// update progress
        void SyncInitProgress();
        void _fastcall InitProgress();
        void _fastcall UpdateProgress();

        void SyncUpdateProgress();
        void _fastcall ClearStatusBar();

        void SyncDisplayFlashType();
        void _fastcall DisplayFlashType(); 

        void SyncShowMsg();
        void _fastcall ShowMsg();

		void _fastcall ShowOK_Form();

        void _fastcall StartTimer();
		void __fastcall StartChksumTimer();
		void __fastcall StopChksumTimer();
		void _fastcall StopTimer();
        void __fastcall StartUSBHintTimer();
        void __fastcall StopUSBHintTimer();

        void __fastcall UpdateUSBVCOMInfo();

		void _fastcall UpdateDebugDAWindow();


public:
/******************************************************************************/
/* Download/Format/Readback Modules                                           */
/******************************************************************************/
        int  Download( void );
#if 0
        int  Format( void );
#endif
        int  Auto_Format_Without_WatchDog( void );
        int  Auto_Format_With_WatchDog( void );
        int  Auto_Format_Without_Disconnect( void );

        int  BackupFormatDownloadYuSuRestore(void);
        int  FormatDownloadRestoreYuSu();  /* added for format->download->restore NVram*/
        int  RestoreOnlyYuSu();            /* added for restore NVram only*/

        int  BackupFormatDownloadYuSuRestoreDLMode(void);
#if 0
        int  FormatDownloadRestoreYuSuUnderDLMode(void);
        int  RestoreOnlyYuSuUnderDLMode(void);
#endif
        int  DownloadYuSuRestore(void);
        int  DownloadFourInOne(void);
        int  DownloadYuSuFourInOne(void);
        int  FormatDownloadFourInOne(void);
        int  FormatDownloadYuSuFourInOne(void);

#if 0
        int  DLFlashBin(void);
        int  FlashToolAPITest( void );
        int  RomWriter( void );
#endif

        void  ShowFlashToolFinalResult( int ret );
        void __fastcall ResetProgressBar();

/******************************************************************************/
/* Android Modules                                                     */
/******************************************************************************/
        int DownloadDAViaUSB(void); 
		//FIXME Remove FormatDownloadYuSu
        int FormatDownloadYuSu( void );
        int FormatDownloadYuSuByAdv( const Android_Image_File& img_file, const bool isDynaicLayout );
        int  DownloadYuSu( void );
        //added for DA download all
        int  DownloadYuSu_ByDA( void );
#if 0
        int FormatDownloadYuSu_ByDA( void );
#endif
        static void Restore_Rom_File(void);
        static void Remove_Other_Rom_File( bool &is_need_dl_uboot, bool &is_need_dl_image   );

        int  Download_Android_Images( void );
        int  Download_Android_ImagesByAdv ( void );

        void ArgAndroidAdvDL(Android_Boot_ARG &boot_arg, Android_ADV_Download_ARG &dl_adv_arg);
/******************************************************************************/
/* Firmware Upgrade Modules                                                   */
/******************************************************************************/ 
//        int Conn2ObtianPartitionRegion(const string& img_name, RB_INFO &rb_info);
        int ReadbackPartitioWithoutDisconnect(const std::string &dest_folder, const std::string &file_name,
        		const bool isDynamicLayout, RB_INFO &rb_info);
        int FormatWithoutConnection(NandLayoutParameter &para, BackupConfig &config);
        bool IsPartitionShouldFmt(BackupConfig &config, const std::string &name, bool layoutChange);
        int BackupWithoutConnection(BackupItem &backupItem, const std::string &backupFolder, bool isDynamic);
        int WritePartition( const Android_Image_File& img_file );
        int ReadPartitionRegionByScatterFile(DL_HANDLE_T pDLHandle, 
        		                             const string& image_folder,
                                             Android_Image_File &img_file,
                                             const string& img_name);
        bool ReArrangeAndroidArray(const Android_Image_File &img_file);
		//DA DL ALL Firmware Upgrade
		int DABackupFormatDownloadRestore(void);
		int SetBinRegionByScatterFile(DL_HANDLE_T p_dl_dandle,
			WriteFlashMemoryParameter *p_write_flash_memory_para,
			BackupItem& backup_item,
			const string& binregion_file);
/******************************************************************************/
/* Parameter Page Modules                                                     */
/******************************************************************************/
        int Parameter ();
        int FlashToolOTP( void );
        int ParameterSecRomLock( void );
        int GetLockImageInfo(const SecurityBitCtrl_YuSu_T &secBitCtrl,
                              const char *romName, const unsigned char index, char *sec_log);    
        void FillColumnInfo(char* pSecLOg, const char* pColFir, 
                              const char* pColSec, const char* pColTir);        

/******************************************************************************/
/* GPS Modules                                                                */
/******************************************************************************/
        WRAPPER_RETURN GPSDownload ( void );
        WRAPPER_RETURN GPSReadback ( void );

/******************************************************************************/
/* Memory Test Modules                                                        */
/******************************************************************************/
        int MemoryTest ( void );
        int EnableDRAM ( FlashTool_Connect_Result    *cn_result);
        // Memory Test : RAM test functions
        int RAMTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result);
        int RAMDataBusTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result);
        int RAMAddrBusTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result);
        int RAMPatternTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result, int pattern_set[], int pattern_size);
        int RAMOnePatternTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result, int pattern);
        int RAMIncDecTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result);
        int RAMIncDecTestIO ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result, HW_MemoryIO_E io);
#if 0
        // Memory Test : NOR test functions
        int NORTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result);
        int NORAddrBusTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result);
        int NORPatternTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result);
#endif
        // Memory Test : NAND test functions
        int NANDTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result);
        int NANDPatternTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result);
        // Memory Test : SDMMC test functions
        int EMMCTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result);
        int EMMCPatternTest ( FlashTool_MemoryTest_Arg *mt_arg,FlashTool_MemoryTest_Result *mt_result);

        void UpdateMemoryTestDetection();
        void _fastcall UpdateMemoryTestRichEditor(AnsiString s, TColor color);

/******************************************************************************/
/* Write Memory Modules                                                        */
/******************************************************************************/
        int WriteMemory ( void );
/******************************************************************************/
/* DL Certification Modules
/******************************************************************************/
        int DLCertification( void );
/******************************************************************************/
/* Read Software Version Modules                                              */
/******************************************************************************/
		int ArgFlashToolRBToBufSetting(RB_HANDLE_T rb_handle, const RB_INFO &rb_info, char* buf, unsigned int buf_len);
        int ReadbackPartitionToBuffer(const RB_INFO &rb_info, const bool isDynamicLayout, const RB_HANDLE_T rb_handle, char* buf, unsigned int buf_len);
		int FlashToolReadSWVersion(void);

/******************************************************************************/
/* Read Software Version Modules                                              */
/******************************************************************************/
		int FlashToolReadProductInfo(void);
/******************************************************************************/
/* Meta Modules                                                               */
/******************************************************************************/
        // Meta Module
        int  EnterMETAResetFactoryDefault( void );
        int  EnterMETABackup( void );
        int  EnterMETARestore( void );

        int  EnterMETAUpdateNVRAM(void);
        META_RESULT  EnterMETADownloadIMEI(int com_port);
        META_RESULT  EnterMETADownloadWIFI_r( const int meta_handle );
        META_RESULT  EnterMETADownloadBT_r( const int meta_handle );
        META_RESULT  EnterMETABackupNvram2BinRegion(void);
        META_RESULT  EnterMETASetCleanBootFlag_r(int meta_handle);
        META_RESULT  EnterMETASetCleanBootFlag(void);
        EBOOT_RESULT SP_BootAsMetaWrapper(int p_comport,COMM_BAUDRATE p_baud, int* p_BootStop);
        META_RESULT  SPMETAInit( int& meta_handle, int com_port );
        META_RESULT  NVRAMInit(void);
        META_RESULT  ModemNVRAMInit( const char* database);
        META_RESULT  ApNVRAMInit(const int meta_handle, const char* database);
        void GetSupportInfoFromNVRAMDB(void);
       
        int  DownloadIMEI(S_IMEI_T &sIMEIdownload, int RID);
        META_RESULT  WriteSIMX2Nvram(const int RID);
        static int  WriteIMEItoNVRAM(S_IMEI_T &sIMEIdownload, int RID ,bool bCheckChecksum );
        int  UploadIMEI(S_IMEI_T &sIMEIupload, int RID);
                

        void __fastcall InitIMEIPara( void );
        void __fastcall Sync2ndImeiSupport ( void );
        void __fastcall InitIMIE_BT_WIFI_Para ( void );
        void __fastcall SyncFourInOne2ndImeiSupport ( void );

        void __fastcall ResetMETABackup ( void );
        void __fastcall ResetMETARestore ( void );
        void __fastcall ResetDL_IMEI_Info( void );
        void __fastcall ResetDL_FourInOne_Info( void );
        void __fastcall ResetFakeProgress( void );
        void __fastcall StopFakeProgress( void );

        void __fastcall SyncStartFakeProgress( void );
        void __fastcall StartFakeProgress( void );

        void __fastcall FinishFakeProgress( void );
        void __fastcall ErrorMessage (void);

        void __fastcall ClearMeta( void );
        void __fastcall ClearSPMeta( void );
        void __fastcall ClearSPMeta( int meta_handle );
        
/******************************************************************************/
/* fill the FlashTool Args                                                    */
/******************************************************************************/


        int ArgComPortSetting( COM_PORT_SETTING &comPortSetting );
#if 0
        int ArgComPortSetting_ByhCOM( COM_PORT_SETTING  &comPortSetting );
#endif
        int ArgFlashTool( FLASHTOOL_ARG &arg, FLASHTOOL_RESULT &result );
        int ArgCloneChksum(S_CHKSUM_Arg &chksum_arg);

        int ArgBootFlashTool( BOOT_FLASHTOOL_ARG &bootFlashTool, void * m_cb_in_brom_stage_arg );
        int ArgFlashToolConnect( FlashTool_Connect_Arg &ftConnect, FlashTool_Connect_Result &ftConnectResult );
        int ArgFlashToolAdvancedFormat(FlashTool_Format_Arg &fmt_arg, FlashTool_Format_Result &fmt_res, 
                                       const FlashTool_Connect_Result& cn_result, bool will_report, bool isDynamicLayout);
#if 0
        //Fill Auto Format parameters for fixed and dynamic layout
        int ArgAutoFormatRegion(FlashTool_Format_Arg &fmt_arg,
                                const unsigned int nvram_start_addr, 
                                const unsigned int nvram_length,
                                const unsigned int nand_flash_size);
#endif
        int ArgFlashToolAdvancedDownload(FlashTool_Download_Arg &fdl_arg, FlashTool_Download_Result &fdl_res);
        int ArgFlashToolAdvancedReadback(FlashTool_Readback_Arg &rb_arg,
        		FlashTool_Readback_Result &rb_result, 
        		bool isDynamicLayout,
        		RB_HANDLE_T rb_handle);
        int ArgFlashToolRBSetting(RB_HANDLE_T rb_handle, const RB_INFO &rb_info, const NUTL_AddrTypeFlag_E  flag);
#if 0
        int ArgFlashDownload( void );
		int ArgFlashFormat( void );
#endif
		int ArgFlashReadback( void );
       
#if 0
        int ArgFlashToolDownload( FLASHTOOL_DOWNLOAD_ARG &dl_arg, FLASHTOOL_DOWNLOAD_RESULT &dl_result );
#endif

        int ArgFlashToolReadback( FLASHTOOL_READBACK_ARG &rb_arg, FLASHTOOL_READBACK_RESULT &rb_result );
#if 0        
		int ArgFlashToolFormat( FLASHTOOL_FORMAT_ARG &fmt_arg, FLASHTOOL_FORMAT_RESULT &fmt_result );
        int ArgFlashToolParameter( FLASHTOOL_PARAMETER_ARG &pm_arg, FLASHTOOL_PARAMETER_RESULT &pm_result );
        int ArgFlashToolProgress( FlashTool_Progress_Arg  &pgs_arg );
        int ArgFlashToolChangeBaudrate( FlashTool_ChangeBaudrate_Arg &cb_arg );
#endif
        int ArgFlashToolMemoryTest( FlashTool_MemoryTest_Arg &mt_arg, FlashTool_MemoryTest_Result &mt_result );
        int ArgFlashToolDLDA( Android_Boot_ARG &boot_arg,
                              DA_Download_ARG &da_dl_arg,
                              const string& s_com_str,
                              DA_PARSE_INFO& da_parse_info);
        int ArgFlashToolDAINFO(DA_PARSE_INFO_E& da_dl_arg, DA_PARSE_INFO& da_parse_info);
        int ArgFlashToolOTP(FLASHTOOL_PARAMETER_ARG &pm_arg, FLASHTOOL_PARAMETER_RESULT &pm_result);
        int ArgFlashToolWriteMemory(WriteFlashMemoryParameter  &wm_arg);
		int ArgFlashToolWatchDog(FlashTool_EnableWDT_Arg *p_wdt_arg);
	 //add for certification file download
	 int ArgFlashToolDLCert(SCERT_ARG_S &cdl_arg, void *m_cb_in_brom_stage_arg);

     RegionFormatSetting* CreateRegionFormatSetting(const std::string &image_name);
/******************************************************************************/
/* fill the MEAT Args                                                         */
/******************************************************************************/

        int ArgMETAConnectWithTarget( META_Connect_Req &meta_con_req, META_Connect_Report &meta_con_report );
        int ArgMETABackupCalibrationData( MISC_BACKUP_REQ_T &meta_backup_req );
        int ArgMETAEnableWatchDogTimer( FtWatchDog &meta_watchdog_req );
        int ArgMETARestoreCalibrationData( MISC_RESTORE_REQ_T   &meta_restore_req );
        int ArgMETAGetBackupResultInfo( BACKUP_RESULT_T &cnf );
        int ArgMETAGetRestoreResultInfo( RESTORE_RESULT_T &cnf );
        int ArgMETAUploadFilesToTarget( MISC_UPLOAD_REQ_EX_T &meta_upload_req, AnsiString *imei_status);
        int ArgMETAConnectWithTargetInMETA( META_ConnectInMETA_Req  &META_ConnectInMETA_Req, 
                                            META_ConnectInMETA_Report  &META_ConnectInMETA_Report,
                                            int com_port);

//        int ArgWMMETAConnectWithTargetInMETA( WM_META_ConnectInMETA_Req  &WM_META_ConnectInMETA_Req ,
//                                           WM_META_ConnectInMETA_Report  &WM_META_ConnectInMETA_Report);

public:
/******************************************************************************/
/* fill the FlashTool Args                                                    */
/******************************************************************************/
		bool	 		bUpdateFinishBytes;
		unsigned char	progress_percentage;
		unsigned long	long progress_finished_bytes;
		unsigned long	long progress_total_bytes;
		AnsiString		progress_hint;
		AnsiString            speed_status;
		AnsiString		progress_flashtype;
		TColor			progress_forecolor;

        unsigned char   m_com_port;
        unsigned char   m_RecvChar;

        COM_PORT_SETTING            com;
		FLASHTOOL_ARG				arg;
		FLASHTOOL_RESULT			result;
//		FLASHTOOL_DOWNLOAD_ARG		dl_arg;
//		FLASHTOOL_DOWNLOAD_RESULT	dl_result;
		FLASHTOOL_READBACK_ARG		rb_arg;
		FLASHTOOL_READBACK_RESULT	rb_result;
//		FLASHTOOL_FORMAT_ARG		fmt_arg;
//		FLASHTOOL_FORMAT_RESULT		fmt_result;


        FlashTool_Connect_Arg        cn_arg;
        FlashTool_Connect_Result     cn_result;
       
     
        bool    m_bGetDAReportWithConnArg;

		char	m_strHWDetectionReport[2048];
		char m_strDeviceHint[512];
#if 0
		char	m_strNorFlashHint[512];
		char	m_strNandFlashHint[512];
#endif
        AnsiString      asMsg;
        AnsiString      m_RecvString;
        bool m_bDLFlashBin;   
   
private:
    bool CharMove(char dst[], const char src[], const unsigned char offset, const unsigned int num);
    void DisplaySecResult(const SecurityBitCtrl_YuSu_T& sec_arg_result);
    bool ScanUSBVOMWithoutTimeout(const std::string& pid, const std::string& vid);
    bool ScanUSBVOMWithTimeout(unsigned int timeout, const std::string& pid, const std::string& vid);
    EBOOT_RESULT ScanMETAUSBPorts(unsigned char&  com_port);
    //Nvram backup & restore
    bool IsNvramFilesExist(const std::string& nvram_folder);
    //all-in-one APIs implementations internally
    int FlashFormat_internal();
    int FlashDownload_internal();
    int FlashReadback_internal();
    int FlashParameter_internal();
    //SCI Clone
    int SCIReadback();
    int SCIWriteMemory();
    //SCI Download
    int SCIDownload();

    int Conn2ObtianPartitionRegion(const string& img_name, RB_INFO &rb_info, bool &isDynamic);
    int ObtainPartitionRegion(const string &img_name, RB_INFO &rb_info);

    //battery auto detect issue
    int GetBatteryStatus(void);
    std::string GetStorageByDAReport(const FlashTool_Connect_Result &result);
    bool CheckStorageByDAReport();
    StorageLayoutType_E GetStorageLayoutType(bool isDynamic, HW_StorageType_E &storage);
    int GetUSBSpeedStatus(FLASHTOOL_API_HANDLE_T &ft_handle, FlashTool_USB_Status_Result &usb_status_result);
    bool ChecksumBefDL();
    bool CheckIfBackupFileExist(const  std::string backup_folder, BackupItem &backup_item);
    unsigned long long CaculateFlashSize(DA_REPORT_T &da_report);
   
    //layout comparasion before download, if changed, and target PMT is ready, firmware upgrade is recommanded.
    bool  VerifyLayoutBeforeDownload(const DL_HANDLE_T &dl_handle, 
		                                                        const FLASHTOOL_API_HANDLE_T &flashtool_handle);
    bool CheckBefPartiDL(const DL_HANDLE_T &dl_handle, const FLASHTOOL_API_HANDLE_T &ft_handle);

private:
    //MS DDK double scan
    std::set<string> m_strSymbolicName;
    std::set<string> m_strPortName;
    std::string m_strPort;
    std::string m_strSymbolic;
    static const int USB_SCAN_TIMEOUT;
    
    // Check or Write IMEI
    S_IMEI_T m_sIMEIdownload;
    bool m_bIMEI1Check;
    bool m_bIMEI2Check;
    bool m_bIMEI1Update;
    bool m_bIMEI2Update;
    bool m_b2ndImeiSupport;
    bool m_bWriteIMEI1;
    bool m_bWriteIMEI2;
    bool m_bWriteBTAddr;
    bool m_bWriteWIFIAddr;
    bool m_bCheckChecksum;
    // Write Wifi/BlueTooth address
    char *m_pModemDatabase;
    char *m_pApDatabase;
    char *m_pBTAddr;
    char *m_pWIFIAddr;
    // NVRAM map & dat file
    char m_szNvramPath[_MAX_PATH];

    static const string MapFileName;
    static const string DatFileName;
    static const string NvramName;
    static const string ProInfoName;
    static const string BinRegionName;
	static const string BootImgName;
	//Demo test for prodcut info
	static const string kProductInfoName;

    //use chip ID for backup folder name, otherwise use COM port
    bool m_bUseChipID;  

    //error message
    AnsiString m_as_err_msg;
    //meta progress value
    int m_meta__progress_value;
};

//---------------------------------------------------------------------------
#endif

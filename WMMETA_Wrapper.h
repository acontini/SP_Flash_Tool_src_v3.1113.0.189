/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/

#ifndef _WMMETA_Wrapper_H
#define _WMMETA_Wrapper_H

// Get SP META Version & Build Info
void  WM_META_GetDLLVer_Wrapper(unsigned int *major_ver, unsigned int *minor_ver, unsigned int *build_num, unsigned int *patch_num);
void  WM_META_GetDLLInfo_Wrapper(const char **pp_version, const char **pp_release_type, const char **pp_build_date, const char **pp_load_path);



int  WM_META_GetAvailableHandle_Wrapper(int *p_meta_handle);

// Initialization 

int  WM_META_Init_Wrapper();
int  WM_META_Init_r_Wrapper(const int meta_handle);


void  WM_META_Deinit_Wrapper(void);
void  WM_META_Deinit_r_Wrapper(int *p_meta_handle);
      
// initialize AP nvram database
int WM_META_NVRAM_Init_Wrapper(const char *PathName, unsigned long *p_nvram_CatcherTranAddr);
int WM_META_NVRAM_Init_r_Wrapper(const int meta_handle, const char *PathName, unsigned long *p_nvram_CatcherTranAddr);

int WM_META_NVRAM_GetRecLen_Wrapper(const char *LID, int *len);
//int WM_META_NVRAM_BT_Decompose_MT6611Radio_Wrapper(nvram_ef_btradio_mt6611_struct  *radio, const char *buf, const int buf_len);
//int WM_META_NVRAM_BT_Compose_MT6611Radio_Wrapper(const nvram_ef_btradio_mt6611_struct  *radio, char *buf, const int buf_len);
//int WM_META_NVRAM_Read_Wrapper(const FT_NVRAM_READ_REQ *req, FT_NVRAM_READ_CNF *cnf, const META_NVRAM_Read_CNF cb, short *token, void *usrData);
//int WM_META_NVRAM_Write_Wrapper(const FT_NVRAM_WRITE_REQ *req, const META_NVRAM_Write_CNF cb, short *token, void *usrData);
// disconnect and shutdown target
int  WM_META_DisconnectWithTarget_Wrapper(void);
int  WM_META_DisconnectWithTarget_r_Wrapper(const int meta_handle);

// disconnect and close port
int WM_META_COMM_Stop_Wrapper(void);
int WM_META_COMM_Stop_r_Wrapper(const int meta_handle);

// connect with target when target already in meta mode 
int  WM_META_ConnectInMetaMode_Wrapper( int *p_bootstop);
int  WM_META_ConnectInMetaMode_r_Wrapper(const int meta_handle, int *p_bootstop, int com_port);

// Shutdown target
int  WM_META_ShutDownTarget_Wrapper(void);
int  WM_META_ShutDownTarget_r_Wrapper(const int meta_handle);

// Reboot target
int  WM_META_RebootTarget_Wrapper(unsigned int delay);
int  WM_META_RebootTarget_r_Wrapper( const int meta_handle, unsigned int delay );

// write IMEI from NVRAM to BinRegion
int  WM_META_Nvram2Bin_Wrapper(unsigned int ms_timeout);

// NVRAM backup and restore
int  WM_META_Nvram_Backup_Wrapper(unsigned int ms_timeout, const char *file1, const char *file2);
int  WM_META_Nvram_Backup_r_Wrapper(int meta_handle, unsigned int ms_timeout, const char *file1, const char *file2);
int  WM_META_Nvram_Restore_Wrapper(unsigned int ms_timeout, const char *file1, const char *file2);
int  WM_META_Nvram_Restore_r_Wrapper(int meta_handle, unsigned int ms_timeout, const char *file1, const char *file2);
//-----------------------------------------------------//
//  META Debug: exported debug function definition     //
//-----------------------------------------------------//
int  WM_META_DebugOn_Wrapper();
int  WM_META_DebugOff_Wrapper();
int  SP_META_DebugOnThePath_Wrapper(const char * path);

int WriteBTtoNVRAM(const char * pBTaddress, const int meta_handle );
int WriteWIFItoNVRAM(const char * pWIFIaddress, const int meta_handle );

//Clean Boot Flag
int WM_META_SetCleanBootFlag_Wrapper(unsigned int ms_timeout);
int WM_META_SetCleanBootFlag_r_Wrapper(const int meta_handle,unsigned int ms_timeout);

int WM_META_Nvram_Backup_Custom_r_Wrapper(int meta_handle, unsigned int ms_timeout, const char *file1, const char *file2, const char * buffer, int count, int mode);

int WM_META_GetChipID_Wrapper(const int meta_handle, unsigned int ms_timeout, unsigned char *chip_id);



#endif // _WMMETA_Wrapper_H



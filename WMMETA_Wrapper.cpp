/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/

#include "spmeta.h"
#include "WMMETA_Wrapper.h"
#include "eboot\interface.h"
#include "general.h"
#include "Logger.h"
#include "Utility.h"
#include <stdio.h>

#pragma warn -8004

#define BD_ADDR_LEN  6
#define IMEI_MAX_LENGTH  15
#define IMEI_ARRAY_LEN IMEI_MAX_LENGTH + 1
#define BARCODE_MAX_LENGTH  64
#define BT_ADDRESS_MAX_LENGTH  ( BD_ADDR_LEN * 2 )
#define MAC_ADDR_LEN  6
#define WIFI_MAC_MAX_LENGTH  ( MAC_ADDR_LEN * 2 )
#define EEPROM_SIZE 512

//For EEPROM Checksum
#define  EEPROM_NIC_CHKSUM_ADD_BYTE                0x13F
#define  EEPROM_NIC_CHKSUM_START_ADD_BYTE          0x1A/* EEPROM offset for HIF section checksum */
#define  EEPROM_NIC_CHKSUM_ADD_DW                0x9F
#define  EEPROM_NIC_CHKSUM_START_ADD_DW          0x0D

//Chip Version
#define MT5921 0x5921
#define MT6620 0x6620

HANDLE gWriteToNVRAMEvent;
HANDLE gReadFromNVRAMEvent;

typedef struct
{
	unsigned char bd_addr[BD_ADDR_LEN];
}S_HANDSET_BT_ADRRESS;

extern unsigned int COM_PORT;

// Get SP META Version & Build Info
void  WM_META_GetDLLVer_Wrapper(unsigned int *major_ver, unsigned int *minor_ver, unsigned int *build_num, unsigned int *patch_num)
{
    return SP_META_GetDLLVer(major_ver, minor_ver, build_num, patch_num);
}

void  WM_META_GetDLLInfo_Wrapper(const char **pp_version, const char **pp_release_type, const char **pp_build_date, const char **pp_load_path)
{
    return SP_META_GetDLLInfo(pp_version, pp_release_type, pp_build_date, pp_load_path);
}

//

int  WM_META_GetAvailableHandle_Wrapper(int *p_meta_handle)
{
    return SP_META_GetAvailableHandle(p_meta_handle);
}


// Initialization 

int  WM_META_Init_Wrapper()
{
    return SP_META_Init(NULL);
}

int WM_META_Init_r_Wrapper(const int meta_handle)
{
    return SP_META_Init_r(meta_handle, NULL);
}
//

void  WM_META_Deinit_Wrapper(void)
{
    SP_META_Deinit();
}

void  WM_META_Deinit_r_Wrapper(int *p_meta_handle)
{
   SP_META_Deinit_r( p_meta_handle);
}
      
// initialize AP nvram database
int WM_META_NVRAM_Init_Wrapper(const char *PathName, unsigned long *p_nvram_CatcherTranAddr)
{
   return SP_META_NVRAM_Init(PathName, p_nvram_CatcherTranAddr);
}

int WM_META_NVRAM_Init_r_Wrapper(const int meta_handle, const char *PathName, unsigned long *p_nvram_CatcherTranAddr)
{
   return SP_META_NVRAM_Init_r(meta_handle, PathName, p_nvram_CatcherTranAddr);
}

int WM_META_NVRAM_BT_Decompose_MT6611Radio_Wrapper(nvram_ef_btradio_mt6611_struct  *radio, const char *buf, const int buf_len)
{
  return SP_META_NVRAM_BT_Decompose_MT6611Radio(radio, buf,  buf_len);
}

int WM_META_NVRAM_BT_Compose_MT6611Radio_Wrapper(const nvram_ef_btradio_mt6611_struct  *radio, char *buf, const int buf_len)
{
  return SP_META_NVRAM_BT_Compose_MT6611Radio(radio, buf,  buf_len);
}

int WM_META_NVRAM_Read_Wrapper(const FT_NVRAM_READ_REQ *req, FT_NVRAM_READ_CNF *cnf, const META_NVRAM_Read_CNF cb, short *token, void *usrData)
{
   return SP_META_NVRAM_Read(req, cnf,  cb, token, usrData);
}

int WM_META_NVRAM_Read_r_Wrapper(const int meta_handle, const FT_NVRAM_READ_REQ *req, FT_NVRAM_READ_CNF *cnf, const META_NVRAM_Read_CNF cb, short *token, void *usrData)
{
   return SP_META_NVRAM_Read_r(meta_handle, req, cnf,  cb, token, usrData);
}

int WM_META_NVRAM_Write_Wrapper(const FT_NVRAM_WRITE_REQ *req, const META_NVRAM_Write_CNF cb, short *token, void *usrData)
{
   return SP_META_NVRAM_Write(req,  cb, token, usrData);
}

int WM_META_NVRAM_Write_r_Wrapper(const int meta_handle, const FT_NVRAM_WRITE_REQ *req, const META_NVRAM_Write_CNF cb, short *token, void *usrData)
{
   return SP_META_NVRAM_Write_r(meta_handle, req,  cb, token, usrData);
}

int WM_META_NVRAM_GetRecLen_Wrapper(const char *LID, int *len)
{
   return SP_META_NVRAM_GetRecLen(LID, len);
}

// disconnect and shutdown target 
int  WM_META_DisconnectWithTarget_Wrapper(void)
{
     return SP_META_DisconnectWithTarget();
}

int  WM_META_DisconnectWithTarget_r_Wrapper(const int meta_handle)
{
     return SP_META_DisconnectWithTarget_r(meta_handle);
}

// Disconnect and close port
int WM_META_COMM_Stop_Wrapper(void)
{
    return SP_META_COMM_Stop();
}

int WM_META_COMM_Stop_r_Wrapper(const int meta_handle)
{
    return SP_META_COMM_Stop_r(meta_handle);
}

// connect with target when target already in meta mode 
int  WM_META_ConnectInMetaMode_Wrapper( int *p_bootstop)
{
    WM_META_ConnectInMETA_Req     WM_META_ConnectInMETA_Req;
    WM_META_ConnectInMETA_Report  WM_META_ConnectInMETA_Report;

    // fill AP META Connet with Target paprameter
    memset(&WM_META_ConnectInMETA_Req,    0, sizeof(WM_META_ConnectInMETA_Req));
    memset(&WM_META_ConnectInMETA_Report, 0, sizeof(WM_META_ConnectInMETA_Report));
    WM_META_ConnectInMETA_Req.com_port = COM_PORT;

    // set baud rate = AUTO
    WM_META_ConnectInMETA_Req.baudrate[0] = META_BAUD57600;
    WM_META_ConnectInMETA_Req.baudrate[1] = META_BAUD115200;
    WM_META_ConnectInMETA_Req.baudrate[2] = META_BAUD230400;
    WM_META_ConnectInMETA_Req.baudrate[3] = META_BAUD460800;
    WM_META_ConnectInMETA_Req.baudrate[4] = META_BAUD921600;
    WM_META_ConnectInMETA_Req.baudrate[5] = META_BAUD1500000;
    WM_META_ConnectInMETA_Req.baudrate[6] = META_BAUD_END;
    WM_META_ConnectInMETA_Req.flowctrl = META_NO_FLOWCTRL;

    WM_META_ConnectInMETA_Req.ms_connect_timeout = 40000;
    return SP_META_ConnectInMetaMode(&WM_META_ConnectInMETA_Req, p_bootstop, &WM_META_ConnectInMETA_Report);
}

int  WM_META_ConnectInMetaMode_r_Wrapper(const int meta_handle, int *p_bootstop, int com_port)
{
    WM_META_ConnectInMETA_Req     WM_META_ConnectInMETA_Req;
    WM_META_ConnectInMETA_Report  WM_META_ConnectInMETA_Report;

    // fill META Connet with Target paprameter
    memset(&WM_META_ConnectInMETA_Req,    0, sizeof(WM_META_ConnectInMETA_Req));
    memset(&WM_META_ConnectInMETA_Report, 0, sizeof(WM_META_ConnectInMETA_Report));
    WM_META_ConnectInMETA_Req.com_port = com_port;

    // set baud rate = AUTO
    WM_META_ConnectInMETA_Req.baudrate[0] = META_BAUD57600;
    WM_META_ConnectInMETA_Req.baudrate[1] = META_BAUD115200;
    WM_META_ConnectInMETA_Req.baudrate[2] = META_BAUD230400;
    WM_META_ConnectInMETA_Req.baudrate[3] = META_BAUD460800;
    WM_META_ConnectInMETA_Req.baudrate[4] = META_BAUD921600;
    WM_META_ConnectInMETA_Req.baudrate[5] = META_BAUD1500000;
    WM_META_ConnectInMETA_Req.baudrate[6] = META_BAUD_END;
    WM_META_ConnectInMETA_Req.flowctrl = META_NO_FLOWCTRL;

    WM_META_ConnectInMETA_Req.ms_connect_timeout = 40000;
    return SP_META_ConnectInMetaMode_r(meta_handle,&WM_META_ConnectInMETA_Req, p_bootstop, &WM_META_ConnectInMETA_Report);
}

// Reboot target
int WM_META_RebootTarget_Wrapper(unsigned int delay)
{
	return SP_META_RebootTarget(delay);
}

int WM_META_RebootTarget_r_Wrapper(const int meta_handle, unsigned int delay)
{
    return SP_META_RebootTarget_r(meta_handle, delay);
}

// Shutdown target
int  WM_META_ShutDownTarget_Wrapper(void)
{
    return SP_META_ShutDownTarget();
}

int  WM_META_ShutDownTarget_r_Wrapper(const int meta_handle)
{
    return SP_META_ShutDownTarget_r(meta_handle);
}

// write IMEI from NVRAM to BinRegion
int  WM_META_Nvram2Bin_Wrapper(unsigned int ms_timeout)
{
    return SP_META_Nvram2Bin(ms_timeout);
}
//Clean Boot Flag
int WM_META_SetCleanBootFlag_Wrapper(unsigned int ms_timeout)
{
    SetCleanBootFlag_REQ req;
    SetCleanBootFlag_CNF cnf;
    return SP_META_SetCleanBootFlag(ms_timeout, &req, &cnf);
}
//
int WM_META_SetCleanBootFlag_r_Wrapper(const int meta_handle,unsigned int ms_timeout)
{
    SetCleanBootFlag_REQ req;
    SetCleanBootFlag_CNF cnf;
    return SP_META_SetCleanBootFlag_r(meta_handle,ms_timeout, &req, &cnf);
}

// NVRAM backup and restore
int  WM_META_Nvram_Backup_Wrapper(unsigned int ms_timeout, const char *file1, const char *file2)
{
    return SP_META_Nvram_Backup(ms_timeout,file1,file2);
}

int WM_META_Nvram_Backup_r_Wrapper(int meta_handle, unsigned int ms_timeout, const char *file1, const char *file2)
{
    return SP_META_Nvram_Backup_r(meta_handle,ms_timeout,file1,file2);
}

int WM_META_Nvram_Backup_Custom_Wrapper(unsigned int ms_timeout, const char *file1, const char *file2, const char * buffer, int count, int mode)
{
    return SP_META_Nvram_Backup_Custom(ms_timeout, file1, file2, buffer, count, mode);
}

int WM_META_Nvram_Backup_Custom_r_Wrapper(int meta_handle, unsigned int ms_timeout, const char *file1, const char *file2, const char * buffer, int count, int mode)
{
    return SP_META_Nvram_Backup_Custom_r(meta_handle, ms_timeout, file1, file2, buffer, count, mode);
}

int  WM_META_Nvram_Restore_Wrapper(unsigned int ms_timeout, const char *file1, const char *file2)
{
	return SP_META_Nvram_Restore(ms_timeout,file1,file2);
}

int  WM_META_Nvram_Restore_r_Wrapper(int meta_handle, unsigned int ms_timeout, const char *file1, const char *file2)
{
       return SP_META_Nvram_Restore_r(meta_handle,ms_timeout,file1,file2);
}

//-----------------------------------------------------//
//  META Debug: exported debug function definition     //
//-----------------------------------------------------//
int  WM_META_DebugOn_Wrapper()
{
	return SP_META_DebugOn();
}

int  WM_META_DebugOff_Wrapper()
{
	return SP_META_DebugOff();
}

int  SP_META_DebugOnThePath_Wrapper(const char * path)
{
	return SP_META_DebugOnThePath(path);
}

kal_int8 Ascii2BCD ( kal_uint8 iAscii )
{
	kal_uint8 iBCD;
	if ( iAscii>= '0' && iAscii<= '9')
	{
        iBCD = iAscii - '0';

	} else if ( iAscii>= 'a' && iAscii<= 'f' )
	{
        iBCD = iAscii - 'a' + 0x0a;

	} else if ( iAscii>= 'A' && iAscii<= 'F' )
	{
        iBCD = iAscii - 'A' + 0x0a;
	} else
	{
		return -1;
	}

	return iBCD;
}

void __stdcall CNF_WMReadFromNVRAM(const FT_NVRAM_READ_CNF *cnf, const short token, void *usrData)
{
    if (cnf->status != META_SUCCESS)
    {  
	return;
    }
    SetEvent (gReadFromNVRAMEvent);
}
//-----------------------------------------------
void __stdcall CNF_WMWriteNVRAM ( const FT_NVRAM_WRITE_CNF *cnf, const short token, void *usrData)
{
    if (cnf->status != META_SUCCESS)
    {
        return;
    }
    SetEvent (gWriteToNVRAMEvent);   
}

//-----------------------------------------------
META_RESULT REQ_Write2NVRAM(const int meta_handle, const FT_NVRAM_WRITE_REQ *req, const META_NVRAM_Write_CNF cb, short *token, void *usrData)
{
    kal_int16 m_sNVRAM_OPID;
    DWORD wait_result;
    META_RESULT ret;
   
    gWriteToNVRAMEvent = CreateEvent( NULL, TRUE, FALSE, NULL );

    ResetEvent ( gWriteToNVRAMEvent );

    ret = (META_RESULT)WM_META_NVRAM_Write_r_Wrapper (meta_handle, req,  cb, token, usrData);

    wait_result = WaitForSingleObject ( gWriteToNVRAMEvent, 15000 );
    
    CloseHandle ( gWriteToNVRAMEvent );
    
    if (WAIT_TIMEOUT == wait_result)
    {
        LOGD( "Error: REQ_Write2NVRAM() fails, WaitForSingleObject ( gWriteToNVRAMEvent, 15000 ): WAIT_TIMEOUT!");
        return META_TIMEOUT;
    }

    if (ret != META_SUCCESS)
    {
        LOGD( "Error: WM_META_NVRAM_Write_Wrapper() fails!");
        return ret;
    }
    return META_SUCCESS;
}


//-----------------------------------------------
META_RESULT REQ_ReadFromNVRAM (const int meta_handle, const FT_NVRAM_READ_REQ *req, FT_NVRAM_READ_CNF *cnf, const META_NVRAM_Read_CNF cb, short *token, void *usrData)
{
    DWORD wait_result;
    META_RESULT ret;
    kal_int16 m_sNVRAM_OPID;

    gReadFromNVRAMEvent = CreateEvent( NULL, TRUE, FALSE, NULL );

    ResetEvent ( gReadFromNVRAMEvent );

    ret = (META_RESULT)WM_META_NVRAM_Read_r_Wrapper (meta_handle, req, cnf,  cb, token, usrData);

    wait_result = WaitForSingleObject ( gReadFromNVRAMEvent, 60000 );
    CloseHandle ( gReadFromNVRAMEvent );

    if ( WAIT_TIMEOUT == wait_result )
    {
        LOGD( "Error: WM_META_NVRAM_Read_Wrapper() fails, WaitForSingleObject ( gReadFromNVRAMEvent, 60000 ): WAIT_TIMEOUT!");
        return META_TIMEOUT;
    }

    if ( ret != META_SUCCESS )
    {
        LOGD( "Error: WM_META_NVRAM_Read_Wrapper() fails!");
        return ret;
    }

    return META_SUCCESS;
}
        
META_RESULT REQ_WriteBTAddr2NVRAM_Start (const int meta_handle, kal_uint32 iBTId, kal_uint8* pBTAddress)
{
    kal_int32 m_usRID = 1;
    kal_int32 m_iBTBufSize;
    kal_uint8 *pLID;
    nvram_ef_btradio_mt6611_struct  tBT;
    META_RESULT ret;
    
	switch ( iBTId )
	{
		case BTMODULE_MT6601:  //6601
		case BTMODULE_MT6611:
		//case BTMODULE_MT6612:
			if (!WM_META_NVRAM_GetRecLen_Wrapper ( "AP_CFG_RDCL_FILE_BT_ADDR_LID", &m_iBTBufSize )) // to Test LID exist
			{
				pLID = "AP_CFG_RDCL_FILE_BT_ADDR_LID";  //after DUMA 1004
			} else if (!WM_META_NVRAM_GetRecLen_Wrapper ( "AP_CFG_RDEB_FILE_BT_ADDR_LID", &m_iBTBufSize ))
			{
				pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID";  //before DUMA 1004
			} else
			{
				return META_LID_INVALID;
			}
			break;
			
		case BTMODULE_RFMD3500:  //RFMD
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		case BTMODULE_RFMD4020:
			
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		default:
			break;
	}

	ret = (META_RESULT)WM_META_NVRAM_GetRecLen_Wrapper ( pLID, &m_iBTBufSize );
    if ( ret != META_SUCCESS )
    {
        //TODO: LOG
        return ret;
    }

    FT_NVRAM_WRITE_REQ tNVRAM_WriteReq;
	FT_NVRAM_READ_REQ tNVRAM_ReadReq;
	FT_NVRAM_READ_CNF tNVRAM_ReadCnf;

    /*if ( NULL != tNVRAM_ReadCnf.buf )
    {
		free ( tNVRAM_ReadCnf.buf );
		tNVRAM_ReadCnf.buf = NULL;
	}*/

    tNVRAM_ReadReq.LID = pLID;
    tNVRAM_ReadReq.RID = m_usRID;
    tNVRAM_ReadCnf.len = m_iBTBufSize;
    //tNVRAM_ReadCnf.buf = (kal_uint8*) malloc (m_iBTBufSize*sizeof(kal_uint8));
    tNVRAM_ReadCnf.buf = new kal_uint8[m_iBTBufSize*sizeof(kal_uint8)]; 


	kal_int16 m_sNVRAM_OPID;
    ret =  REQ_ReadFromNVRAM (   meta_handle,
                                 &tNVRAM_ReadReq,
                                 &tNVRAM_ReadCnf,
                                  CNF_WMReadFromNVRAM,
                                 &m_sNVRAM_OPID,
                                  NULL );

	if ( ret!=META_SUCCESS )
    {
    	return ret;
    }

	ret = (META_RESULT)WM_META_NVRAM_BT_Decompose_MT6611Radio_Wrapper ( &tBT, tNVRAM_ReadCnf.buf, m_iBTBufSize);

	if ( ret != META_SUCCESS )
    {
    	return ret;
    }
	
	memcpy ( tBT.addr, pBTAddress, BD_ADDR_LEN ); 
	
	switch ( iBTId )	
	{
		case BTMODULE_MT6601:  //6601
		case BTMODULE_MT6611:
		//case BTMODULE_MT6612:
			if (!WM_META_NVRAM_GetRecLen_Wrapper ( "AP_CFG_RDCL_FILE_BT_ADDR_LID", &m_iBTBufSize )) // to Test LID exist
			{
				pLID = "AP_CFG_RDCL_FILE_BT_ADDR_LID";  //after DUMA 1004
			} else if (!WM_META_NVRAM_GetRecLen_Wrapper ( "AP_CFG_RDEB_FILE_BT_ADDR_LID", &m_iBTBufSize ))
			{
				pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID";  //before DUMA 1004
			} else
			{
				return META_LID_INVALID;
			}
			break;
			
		case BTMODULE_RFMD3500:  //RFMD
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		case BTMODULE_RFMD4020:
			
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		default:
			break;
	}

	ret = (META_RESULT)WM_META_NVRAM_GetRecLen_Wrapper ( pLID, &m_iBTBufSize );
    if ( ret != META_SUCCESS )
    {
         //TODO: LOG
        return ret;
    }
		
    m_usRID = 1;
	tNVRAM_WriteReq.LID = pLID;
    tNVRAM_WriteReq.RID = m_usRID;
    tNVRAM_WriteReq.len = m_iBTBufSize;
    //tNVRAM_WriteReq.buf = (kal_uint8*) malloc ( m_iBTBufSize*sizeof(kal_uint8) );
    tNVRAM_WriteReq.buf = new kal_uint8[m_iBTBufSize*sizeof(kal_uint8)];
    
	ret = (META_RESULT)WM_META_NVRAM_BT_Compose_MT6611Radio_Wrapper ( &tBT,
	                                       tNVRAM_WriteReq.buf,
		                                   m_iBTBufSize );
    if ( ret != META_SUCCESS )
    {
         //TODO: LOG
        return ret;
    }
    
    ret = REQ_Write2NVRAM (  meta_handle,
    		                 &tNVRAM_WriteReq,
                             CNF_WMWriteNVRAM,
                             &m_sNVRAM_OPID,
                             NULL);

	if ( ret != META_SUCCESS )
    {
        return ret;
    }

    if ( NULL != tNVRAM_ReadCnf.buf )
	{
		//free ( tNVRAM_ReadCnf.buf );
		delete []tNVRAM_ReadCnf.buf;
		tNVRAM_ReadCnf.buf = NULL;
	}

	if (NULL != tNVRAM_WriteReq.buf)
	{
		//free (tNVRAM_WriteReq.buf);
		delete []tNVRAM_WriteReq.buf;
		tNVRAM_WriteReq.buf = NULL;
	}
	
    return META_SUCCESS;
}
        
META_RESULT REQ_ReadBTAddrFromNVRAM_Start ( const int meta_handle,  kal_uint32 iBTId, kal_uint8* pBTAddress )
{
    kal_int32 m_usRID = 1, m_iBTBufSize;
	kal_uint8 *pLID;
	nvram_ef_btradio_mt6611_struct tBT;
	FT_NVRAM_READ_REQ tNVRAM_ReadReq;
	FT_NVRAM_READ_CNF tNVRAM_ReadCnf;
	META_RESULT ret;

	switch ( iBTId )	
	{
		case BTMODULE_MT6601:  //6601
		case BTMODULE_MT6611:
			if (!WM_META_NVRAM_GetRecLen_Wrapper ( "AP_CFG_RDCL_FILE_BT_ADDR_LID", &m_iBTBufSize )) // to Test LID exist
			{
				pLID = "AP_CFG_RDCL_FILE_BT_ADDR_LID";  //after DUMA 1004
			} else if (!WM_META_NVRAM_GetRecLen_Wrapper ( "AP_CFG_RDEB_FILE_BT_ADDR_LID", &m_iBTBufSize ))
			{
				pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID";  //before DUMA 1004
			} else
			{
				return META_LID_INVALID;
			}
			break;
			
		case BTMODULE_RFMD3500:  //RFMD
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		case BTMODULE_RFMD4020:
			
			pLID = "AP_CFG_RDEB_FILE_BT_ADDR_LID"; 
			break;
		default:
			break;
	}

    ret = (META_RESULT)WM_META_NVRAM_GetRecLen_Wrapper( pLID, &m_iBTBufSize);
    if ( ret!=META_SUCCESS )
    {
    	return ret;
    }
    /*
	if ( NULL != tNVRAM_ReadCnf.buf )
	{
		free ( tNVRAM_ReadCnf.buf );
		tNVRAM_ReadCnf.buf = NULL;
		
	}
    */
	tNVRAM_ReadReq.LID = pLID;
    tNVRAM_ReadReq.RID = m_usRID;
    tNVRAM_ReadCnf.len = m_iBTBufSize;
    tNVRAM_ReadCnf.buf = (kal_uint8*) malloc ( m_iBTBufSize*sizeof(kal_uint8) );


    kal_int16 m_sNVRAM_OPID;

    ret =  REQ_ReadFromNVRAM (   meta_handle,
    		                     &tNVRAM_ReadReq,
                                 &tNVRAM_ReadCnf,
                                 CNF_WMReadFromNVRAM,
                                 &m_sNVRAM_OPID,
                                 NULL );

	if ( ret!=META_SUCCESS )
    {
    	return ret;
    }

	ret = (META_RESULT)WM_META_NVRAM_BT_Decompose_MT6611Radio_Wrapper ( &tBT, tNVRAM_ReadCnf.buf, m_iBTBufSize );
	if ( ret!=META_SUCCESS )
    {
    	return ret;
    }
	memcpy ( pBTAddress, tBT.addr, BD_ADDR_LEN ); 

	if ( NULL != tNVRAM_ReadCnf.buf )
	{
		free ( tNVRAM_ReadCnf.buf );
		tNVRAM_ReadCnf.buf = NULL;
		
	}
	
	return ret;
}

void Checksum_Generation(unsigned char StorageBuf[])
{
	int u2Len = (EEPROM_NIC_CHKSUM_ADD_DW - EEPROM_NIC_CHKSUM_START_ADD_DW + 1) * 2;

	/* 5921 Start NIC EEPROM Checksum from 0x0D ~ 0x9F */
	int StartIndex = EEPROM_NIC_CHKSUM_START_ADD_DW * 2;	//from word to byte
	//int EndIndex = EEPROM_NIC_CHKSUM_ADD_DW * 2;
	int LoopIndex;
	unsigned char Chksum = 0;
	//unsigned char New_Chksum = 0;
	//unsigned char Old_Chksum = 0;
	
       //for (LoopIndex = StartIndex; LoopIndex <= EndIndex; LoopIndex++)
       for (LoopIndex = 0; LoopIndex < u2Len - 1; LoopIndex++)//not count 0x13F
       {
              Chksum = (Chksum + StorageBuf[LoopIndex + StartIndex]) & 0x00FF;
       }
       //Old_Chksum = StorageBuf[0x13F];
       //	New_Chksum = (0x01FF - Chksum) & 0x00FF;
    
       StorageBuf[0x13F] = (0x01FF - Chksum) & 0x00FF;
}


//===========================================================================
META_RESULT REQ_WriteWifiMAC2NVRAM_Start (WiFi_MacAddress_S *MACAddress, const int meta_handle )
{
    kal_int32 usRID = 1;
    kal_int32 iWifiBufSize;
    const kal_char* const WIFI_LID = "AP_CFG_RDEB_FILE_WIFI_LID";
    META_RESULT ret;
    
    unsigned long uChipVersion = -1;

    FT_NVRAM_WRITE_REQ tNVRAM_WriteReq;
    FT_NVRAM_READ_REQ tNVRAM_ReadReq;
    FT_NVRAM_READ_CNF tNVRAM_ReadCnf;
    kal_int16 sNVRAM_OPID;
    tNVRAM_ReadCnf.buf = NULL;
    tNVRAM_WriteReq.buf = NULL;

    kal_char *pWifiBuf = NULL;
    kal_uint8 uWifiValue = 0x11;
    char szWifiFiledName[255] = "";

    ret = (META_RESULT)WM_META_NVRAM_GetRecLen_Wrapper ( WIFI_LID, &iWifiBufSize );
    if ( ret != META_SUCCESS )
    {
        LOGD( "Error: WM_META_NVRAM_GetRecLen_Wrapper() fails!");
        return ret;
    }

    pWifiBuf = new kal_char[iWifiBufSize*(sizeof(kal_char))];
    if ( NULL == pWifiBuf )
    {
        LOGD( "REQ_WriteWifiMAC2NVRAM_Start(): Malloc memory for SetRecFieldValue buffer fails!");
        return META_FAILED;
    }

    tNVRAM_ReadReq.LID = WIFI_LID;
    tNVRAM_ReadReq.RID = usRID;
    tNVRAM_ReadCnf.len = iWifiBufSize;
    tNVRAM_ReadCnf.buf = new kal_uint8[iWifiBufSize*(sizeof(kal_uint8))];

    if ( NULL == tNVRAM_ReadCnf.buf )
    {
        if( NULL != pWifiBuf )
        {
            delete[] pWifiBuf;
            pWifiBuf = NULL;
        }
        LOGD( "REQ_WriteWifiMAC2NVRAM_Start(): Malloc memory for ReadCnf buffer fails!" );
        return META_FAILED;
    }
    ret =  REQ_ReadFromNVRAM (   meta_handle,
    		                     &tNVRAM_ReadReq,
                                 &tNVRAM_ReadCnf,
                                 CNF_WMReadFromNVRAM,
                                 &sNVRAM_OPID,
                                 NULL );
    if ( ret != META_SUCCESS )
    {
        LOGD( "REQ_WriteWifiMAC2NVRAM_Start(): REQ_ReadFromNVRAM() fails!");
        return ret;
    }

    //TODO: remove retry mechanism when target wifi driver is ready.
    unsigned int uRetry = 0;
    do
    {
        ret = SP_META_WiFi_GetChipVersion_r(meta_handle, 30000, &uChipVersion);

        if(META_SUCCESS != ret) {
            LOGD( "REQ_WriteWifiMAC2NVRAM_Start(): META_WiFi_GetChipVersion_r fails!");
            return ret;
        }
    }while( uRetry < 5 && (0 ==uChipVersion) );


    if ( MT6620 == uChipVersion )
    {
    	LOGD( "REQ_WriteWifiMAC2NVRAM_Start():MT6620");
    	for(int i = 0; i < MAC_ADDR_LEN; i++)
		{
			uWifiValue = MACAddress->mac_addr[i];
            sprintf(szWifiFiledName, "aucMacAddress[%d]", i);
            ret = SP_META_NVRAM_SetRecFieldValue(WIFI_LID,
                                             szWifiFiledName,
                                             pWifiBuf,
                                             iWifiBufSize,
                                             &uWifiValue,
                                             sizeof(uWifiValue));
            Logger::GetLogger().Log(Logger::Info,
            "REQ_WriteWifiMAC2NVRAM_Start(): WiFi Field name is %s, write current value is %x.",
            szWifiFiledName, uWifiValue);
            
            if(META_SUCCESS != ret) {
                LOGD( "REQ_WriteWifiMAC2NVRAM_Start(): SP_META_NVRAM_SetRecFieldValue fails!");
                return ret;
            }
        }
		memcpy(tNVRAM_ReadCnf.buf, pWifiBuf, iWifiBufSize*(sizeof(kal_uint8)));
    }
    else //MT5921
    {
    	LOGD( "REQ_WriteWifiMAC2NVRAM_Start():MT5921");
        //MT5921 driver read Array data by BYTE
        //For instance: 000ce7090b65, Nvram(0c0009e7650b),Driver: 0c0009e7650b
    	for(int i = 0; i < MAC_ADDR_LEN; i=i+2)
		{
	    	tNVRAM_ReadCnf.buf[0x26+i+1] = MACAddress->mac_addr[i+1];
	        tNVRAM_ReadCnf.buf[0x26+i] = MACAddress->mac_addr[i];
        }
		Checksum_Generation (tNVRAM_ReadCnf.buf);
    }

    usRID = 1;
    tNVRAM_WriteReq.LID = WIFI_LID;
    tNVRAM_WriteReq.RID = usRID;
    tNVRAM_WriteReq.len = iWifiBufSize;
    tNVRAM_WriteReq.buf = tNVRAM_ReadCnf.buf;
    ret = REQ_Write2NVRAM ( meta_handle,
    		                &tNVRAM_WriteReq,
                            CNF_WMWriteNVRAM,
                            &sNVRAM_OPID,
                            NULL);

    if ( ret != META_SUCCESS )
    {
        LOGD( "REQ_WriteWifiMAC2NVRAM_Start(): REQ_Write2NVRAM() fails!");
        return ret;
    }

    if( NULL != pWifiBuf)
    {
         delete[] pWifiBuf;
         pWifiBuf = NULL;
    }

    if( NULL != tNVRAM_ReadCnf.buf)
    {
         delete[] (tNVRAM_ReadCnf.buf);
         tNVRAM_ReadCnf.buf = NULL;
    }

    return META_SUCCESS;
}

//===========================================================================
META_RESULT REQ_ReadWifiMACFromNVRAM_Start ( WiFi_MacAddress_S *MACAddress, const int meta_handle )
{
    kal_int32 iWifiBufSize;
    const kal_char* const WIFI_LID = "AP_CFG_RDEB_FILE_WIFI_LID";
    META_RESULT ret;
    char szLog[256] = "";
    unsigned long uChipVersion = -1;

    kal_int32 m_usRID = 1;
    FT_NVRAM_READ_REQ tNVRAM_ReadReq;
    FT_NVRAM_READ_CNF tNVRAM_ReadCnf;
    tNVRAM_ReadCnf.buf = NULL;
    kal_int16 sNVRAM_OPID;

    char szWifiFiledName[255] = "";

    ret = (META_RESULT)WM_META_NVRAM_GetRecLen_Wrapper ( WIFI_LID, &iWifiBufSize );
    if ( ret != META_SUCCESS )
    {
        LOGD( "REQ_ReadWifiMACFromNVRAM_Start(): WM_META_NVRAM_GetRecLen_Wrapper() fails!");
        return ret;
    }

    tNVRAM_ReadReq.LID = WIFI_LID;
    tNVRAM_ReadReq.RID = m_usRID;
    tNVRAM_ReadCnf.len = iWifiBufSize;
    tNVRAM_ReadCnf.buf = new kal_uint8[iWifiBufSize*sizeof(kal_uint8)];
    if ( NULL == tNVRAM_ReadCnf.buf )
    {
        LOGD( "REQ_ReadWifiMACFromNVRAM_Start(): Malloc memory for ReadCnf buffer fails!");
        return META_FAILED;
    }
    ret =  REQ_ReadFromNVRAM (   meta_handle,
    		                     &tNVRAM_ReadReq,
                                 &tNVRAM_ReadCnf,
                                 CNF_WMReadFromNVRAM,
                                 &sNVRAM_OPID,
                                 NULL );
    if ( ret != META_SUCCESS )
    {
        LOGD( "REQ_ReadWifiMACFromNVRAM_Start(): REQ_ReadFromNVRAM() fails!");
        return ret;
    }

    //TODO: remove retry mechanism when target wifi driver is ready.
    unsigned int uRetry = 0;
    do
    {
        ret = SP_META_WiFi_GetChipVersion_r(meta_handle, 30000, &uChipVersion);

        if(META_SUCCESS != ret) {
            LOGD( "REQ_ReadWifiMACFromNVRAM_Start(): META_WiFi_GetChipVersion_r fails!");
            return ret;
        }
    }while( uRetry < 5 && (0 ==uChipVersion) );

    if ( MT6620 == uChipVersion )
    {
    	LOGD( "REQ_ReadWifiMACFromNVRAM_Start():MT6620");
    	for(int i = 0; i < MAC_ADDR_LEN; i++)
		{
            sprintf(szWifiFiledName, "aucMacAddress[%d]", i);
            ret = SP_META_NVRAM_GetRecFieldValue(WIFI_LID,
                                             szWifiFiledName,
                                             tNVRAM_ReadCnf.buf,//pWifiBuf,
                                             iWifiBufSize,
                                             &MACAddress->mac_addr[i],
                                             sizeof(kal_uint8));
            Logger::GetLogger().Log(Logger::Info,
            "REQ_WriteWifiMAC2NVRAM_Start(): WiFi Field name is %s, read current MAC value is %x.",
            szWifiFiledName, MACAddress->mac_addr[i]);
            if(META_SUCCESS != ret) {
                LOGD( "REQ_ReadWifiMACFromNVRAM_Start(): SP_META_NVRAM_GetRecFieldValue fails!");
                return ret;
            }
        }
    }
    else //MT5921
    {
    	LOGD( "REQ_ReadWifiMACFromNVRAM_Start():MT5921");
    	for(int i = 0; i < MAC_ADDR_LEN; i=i+2)
		{
            MACAddress->mac_addr[i] = tNVRAM_ReadCnf.buf[0x26+i];
            MACAddress->mac_addr[i+1] = tNVRAM_ReadCnf.buf[0x26+i+1];
        }
    }

    if( NULL != tNVRAM_ReadCnf.buf)
    {
         delete[] (tNVRAM_ReadCnf.buf);
         tNVRAM_ReadCnf.buf = NULL;
    }

    return META_SUCCESS;
}

int WriteBTtoNVRAM( const char * pBTaddress, const int meta_handle )
{
    kal_uint8 strTip [256] , i, iBCD_L, iBCD_H;
    META_RESULT ret;
    BT_ModuleID_S BT_ID;

	S_HANDSET_BT_ADRRESS tBtAddress_W, tBtAddress_R;

	kal_uint8 strBtAddress_W [ BT_ADDRESS_MAX_LENGTH + 1 ];
	kal_uint8 strBtAddress_R [ BT_ADDRESS_MAX_LENGTH + 1 ];

	
	BT_ID.id = BTMODULE_MT6611;
    
	LOGD("Step: Enter AP meta to write BT Address to smartphone AP nvram!");
	LOGD("Step: Start to Init AP Nvram Database.");

    //get BT address
    strcpy(strBtAddress_W, pBTaddress);

    //write BT address
    for ( i = 0; i < BT_ADDRESS_MAX_LENGTH; i += 2 )
    {

        iBCD_H = Ascii2BCD( strBtAddress_W [i] );
        iBCD_L = Ascii2BCD( strBtAddress_W [i + 1] );
        tBtAddress_W.bd_addr [i/2] = iBCD_H<<4 | iBCD_L;
				
    }

    switch ( BT_ID.id )
    {
        case BTMODULE_MT6601:  //6601
        case BTMODULE_MT6611:
            //case BTMODULE_MT6612:
            if ( META_SUCCESS != (ret = REQ_WriteBTAddr2NVRAM_Start ( meta_handle, BT_ID.id, tBtAddress_W.bd_addr)) )
            {
                LOGD(string("Error: Write BT Address  fail. Meta Result = ")
                		.append(NumberToString((int)ret)).c_str());

                return ret;
            }
            break;
        case BTMODULE_RFMD3500:  //RFMD
        case BTMODULE_RFMD4020:
            if ( META_SUCCESS != (ret = REQ_WriteBTAddr2NVRAM_Start ( meta_handle, BT_ID.id, tBtAddress_W.bd_addr )) )
            {
                LOGD(string("Error: Write BT Address  fail. Meta Result = ")
                		.append(NumberToString((int)ret)).c_str());
                return ret;
            }
					
            break;
        default:
            break;
     }

    LOGD("Step: Write BT Address successfully.");

    if ( META_SUCCESS != (ret = REQ_ReadBTAddrFromNVRAM_Start ( meta_handle, BT_ID.id, tBtAddress_R.bd_addr)) )
    {
        LOGD(string("Error: Read BT Address  fail. Meta Result = ")
                        		.append(NumberToString((int)ret)).c_str());
        return ret;

    }

    LOGD("Step: Check BT Address.");
			
    if ( memcmp ( tBtAddress_W.bd_addr, tBtAddress_R.bd_addr, BD_ADDR_LEN )) 
    {
        Logger::GetLogger().Log(Logger::Debug,
				"Error: Check BT Address fail. BT Address = \"%x %x %x %x %x %x\".",
				tBtAddress_R.bd_addr[0],
				tBtAddress_R.bd_addr[1],
				tBtAddress_R.bd_addr[2],
				tBtAddress_R.bd_addr[3],
				tBtAddress_R.bd_addr[4],
				tBtAddress_R.bd_addr[5]);

        ret = META_FAILED;
				
    }
    else
    {
        Logger::GetLogger().Log(Logger::Debug,
        		"OK: Check BT Address. BT Address  = \"%x %x %x %x %x %x\".",
        		tBtAddress_R.bd_addr[0],
        		tBtAddress_R.bd_addr[1],
        		tBtAddress_R.bd_addr[2],
        		tBtAddress_R.bd_addr[3],
        		tBtAddress_R.bd_addr[4],
        		tBtAddress_R.bd_addr[5]);

        ret = META_SUCCESS;
    }
            return ret;
}

int WriteWIFItoNVRAM(const char * pWIFIaddress, const int meta_handle )
{
    kal_uint8 strLog [1024];
    kal_uint8 strTip [256] , i, j, iBCD_L, iBCD_H, iBCD_M;
    WiFi_MacAddress_S tWifiMac_W, tWifiMac_R;
    kal_uint8 strWifiMac_W [ WIFI_MAC_MAX_LENGTH + 1 ];
    kal_uint8 srtWifiMac_R [ WIFI_MAC_MAX_LENGTH + 1 ];
	//kal_uint32 iMacHeaderLen = 0;
    META_RESULT ret;

    LOGD("Step: Start to write WiFi address.");
    //get WiFi address
    strcpy(strWifiMac_W, pWIFIaddress);

    Logger::GetLogger().Log(Logger::Debug,
    		"Wifi MAC to be written is: %s",
    		strWifiMac_W);
    if( 12 != strlen (strWifiMac_W) )
    {
        LOGD ("Error: Wifi MAC code < 12 bytes!");
        return ret = META_FAILED;
    }


    for ( i = 0, j = 0; i < WIFI_MAC_MAX_LENGTH; i+=2, j++ )
    {

        iBCD_H = Ascii2BCD( strWifiMac_W [i] );
        iBCD_L = Ascii2BCD( strWifiMac_W [i+1] );
        iBCD_M = iBCD_H<<4;
        tWifiMac_W.mac_addr[j] = iBCD_M | iBCD_L;
        /*
        if ( (i/2)%2 == 0 )
        {
            tWifiMac_W.mac_addr [i/2+1] = iBCD_H<<4 | iBCD_L;
        }
        else
        {
            tWifiMac_W.mac_addr [i/2-1] = iBCD_H<<4 | iBCD_L;
        }*/
    }

    if ( META_SUCCESS != (ret = REQ_WriteWifiMAC2NVRAM_Start (&tWifiMac_W, meta_handle)) )
    {
        LOGD(string("Error: Write WiFi MAC  fail. Meta Result = ")
        		.append(NumberToString((int)ret)).c_str());
        return ret;
    }   
			
    LOGD("Step: Write Wifi MAC successfully.");

    LOGD("Step: Start to check Wifi MAC.");

    if ( META_SUCCESS != (ret = REQ_ReadWifiMACFromNVRAM_Start (&tWifiMac_R, meta_handle)) )
    {
        LOGD(string("Error: Read WiFi MAC  fail. Meta Result = ")
                		.append(NumberToString((int)ret)).c_str());
        return ret;
    }

    if ( memcmp  ( tWifiMac_W.mac_addr, tWifiMac_R.mac_addr, MAC_ADDR_LEN))
    {
        Logger::GetLogger().Log(Logger::Debug,
        		"Error: Check Wifi MAC fail.Wifi MAC = \"%x %x %x %x %x %x\".",
				tWifiMac_R.mac_addr[0],
				tWifiMac_R.mac_addr[1],
				tWifiMac_R.mac_addr[2],
				tWifiMac_R.mac_addr[3],
				tWifiMac_R.mac_addr[4],
				tWifiMac_R.mac_addr[5]);
        ret = META_FAILED;
    }
    else
    {
        Logger::GetLogger().Log(Logger::Debug,
        		"OK: Check Wifi MAC Pass. Wifi MAC = \"%x %x %x %x %x %x\".",
				tWifiMac_R.mac_addr[0],
				tWifiMac_R.mac_addr[1],
				tWifiMac_R.mac_addr[2],
				tWifiMac_R.mac_addr[3],
				tWifiMac_R.mac_addr[4],
				tWifiMac_R.mac_addr[5]);
        ret = META_SUCCESS;
    }

    return ret;
}

int WM_META_GetChipID_Wrapper(const int meta_handle, unsigned int ms_timeout, unsigned char *chip_id){
    return SP_META_GetChipID_r(meta_handle, ms_timeout, chip_id);
}


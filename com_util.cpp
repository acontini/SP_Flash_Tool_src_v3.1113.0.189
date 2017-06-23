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
*  com_util.cpp
*
* Project:
* --------
*   Flash tool
*
* Description:
* ------------
*   Flash tool utility
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.1  $
* $Modtime:   Nov 20 2002 16:38:02  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/com_util.cpp-arc  $
 *
 * Aug 7 2008 MTK01952
 * [STP100001779] [FlashTool] v3.0828.00
 * New features:
 *  1. Add the backup and restore functinality 
 * 
 *    Rev 1.1   Nov 20 2002 19:52:58   mtk00303
 * update for reference phone
 * 
 *    Rev 1.0   Jul 26 2002 11:53:18   admin
 * Initial revision.
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/
//---------------------------------------------------------------------------



#include <windows.h>
#include <stdio.h>

DCB dcb;
//------------------------------------------------------------------------------
bool open_com_port( HANDLE &hCOM_HANDLE, int i_com_port, int i_baud_rate)
{
    if ( hCOM_HANDLE != NULL && hCOM_HANDLE != INVALID_HANDLE_VALUE )
    {
        PurgeComm( hCOM_HANDLE, PURGE_TXABORT);
        PurgeComm( hCOM_HANDLE, PURGE_RXABORT);
        PurgeComm( hCOM_HANDLE, PURGE_TXCLEAR);
        PurgeComm( hCOM_HANDLE, PURGE_RXCLEAR);
        CloseHandle( hCOM_HANDLE);
        hCOM_HANDLE = NULL;
    }

	char c_com[50];

    ::sprintf(c_com, "\\\\.\\COM%d", i_com_port);

	hCOM_HANDLE = ::CreateFile( c_com,
			                    GENERIC_READ|GENERIC_WRITE,
			                    0,
			                    NULL,
			                    OPEN_EXISTING,
			                    FILE_ATTRIBUTE_NORMAL,
			                    NULL);

	if( hCOM_HANDLE == INVALID_HANDLE_VALUE )
    {
        //ShowMessage(" COM" + IntToStr( i_com_port) + " is used by other program.");
        hCOM_HANDLE = NULL;
	    return false;
	}

	if( ::SetupComm(hCOM_HANDLE, 8192, 8192)==FALSE )
        return false;

	if( ::PurgeComm(hCOM_HANDLE, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR)==FALSE )
        return false;


    COMMTIMEOUTS TimeOut;
    TimeOut.ReadIntervalTimeout         = 0;
    TimeOut.ReadTotalTimeoutMultiplier  = 1;
    TimeOut.ReadTotalTimeoutConstant    = 700;
    TimeOut.WriteTotalTimeoutMultiplier = 1;
    TimeOut.WriteTotalTimeoutConstant   = 700;

    SetCommTimeouts(hCOM_HANDLE, &TimeOut);

	char c_dcb[50];
    ::sprintf( c_dcb, "%d,n,8,1", i_baud_rate);

    BuildCommDCB( c_dcb, &dcb );

    SetCommState( hCOM_HANDLE, &dcb );
    return true;
}
//------------------------------------------------------------------------------
bool set_com_port( HANDLE &hCOM_HANDLE, int i_baud_rate)
{
	if( hCOM_HANDLE==INVALID_HANDLE_VALUE )
    {
        hCOM_HANDLE = NULL;
	    return false;
	}

	if( hCOM_HANDLE==NULL )
    {
	    return false;
	}

    if ( PurgeComm( hCOM_HANDLE, PURGE_TXABORT)==0 || PurgeComm( hCOM_HANDLE, PURGE_RXABORT)==0 ||
         PurgeComm( hCOM_HANDLE, PURGE_TXCLEAR)==0 || PurgeComm( hCOM_HANDLE, PURGE_RXCLEAR)==0 )
    {
	    return false;
    }

	if( ::SetupComm(hCOM_HANDLE, 8192, 8192)==FALSE )
		return false;

	if( ::PurgeComm(hCOM_HANDLE, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR)==FALSE )
		return false;

    COMMTIMEOUTS TimeOut;
    TimeOut.ReadIntervalTimeout         = 0;
    TimeOut.ReadTotalTimeoutMultiplier  = 1;
    TimeOut.ReadTotalTimeoutConstant    = 700;
    TimeOut.WriteTotalTimeoutMultiplier = 1;
    TimeOut.WriteTotalTimeoutConstant   = 700;

    SetCommTimeouts( hCOM_HANDLE, &TimeOut);

	char c_dcb[50];
    ::sprintf( c_dcb, "%d,n,8,1", i_baud_rate);

    BuildCommDCB( c_dcb, &dcb );

    SetCommState( hCOM_HANDLE, &dcb );
    return true;
}
//------------------------------------------------------------------------------
bool close_com_port( HANDLE &hCOM_HANDLE  )
{
    if ( hCOM_HANDLE != NULL && hCOM_HANDLE != INVALID_HANDLE_VALUE )
    {
        PurgeComm( hCOM_HANDLE, PURGE_TXABORT);
        PurgeComm( hCOM_HANDLE, PURGE_RXABORT);
        if ( !CloseHandle( hCOM_HANDLE ) ) return false;
        hCOM_HANDLE = NULL;
    }

    if ( hCOM_HANDLE == INVALID_HANDLE_VALUE )
    {
        hCOM_HANDLE = NULL;
    }

    return true;
}

//------------------------------------------------------------------------------





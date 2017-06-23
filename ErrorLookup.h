/*
 * ErrorLookup.h
 *
 *  Created on: Jan 6, 2011
 *      Author: MTK81019
 */

#ifndef ERRORLOOKUP_H_
#define ERRORLOOKUP_H_

#include <iostream>

#include "brom.h"
#include "eboot\interface.h"
#include "BromDLLWrapper.h"
#include "FlashToolTypedefs.h"
#include "FlashToolErrorCodeDef.h"

class ErrorLookup{
public:
	static std::string GetErrorMessage(int ret, unsigned int msp_error_code = 0,
			UART_BAUDRATE baudrate = UART_BAUD_921600);

	static void SetErrorCodeMode(ERROR_CODE_MODE_E mode){
		error_code_mode = mode;
	}
	static ERROR_CODE_MODE_E GetErrorCodeMode() {
		return error_code_mode;
	}

	static std::string BromErrorMessage(STATUS_E status,
				unsigned int error_code, UART_BAUDRATE baudrate);
private:
	ErrorLookup();

	static std::string EbootErrorMessage(EBOOT_RESULT ret);
	static std::string MetaErrorMessage(META_RESULT ret);
	static std::string GPSErrorMessage(WRAPPER_RETURN ret);
	static std::string FlashToolErrorMessage(FLASH_TOOL_RESULT ret);

	static ERROR_CODE_MODE_E  error_code_mode;
};

#endif /* ERRORLOOKUP_H_ */

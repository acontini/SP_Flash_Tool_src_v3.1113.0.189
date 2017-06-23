/*
 * ErrorLookup.cpp
 *
 *  Created on: Jan 6, 2011
 *      Author: MTK81019
 */
#pragma hdrstop

#include "ErrorLookup.h"
#include <cassert>
#include <stdio.h>


#include "Utility.h"
#include "GlobalData.h"
#include "main.h"

using std::string;

ERROR_CODE_MODE_E ErrorLookup::error_code_mode  = FLASHTOOL;

string ErrorLookup::GetErrorMessage(int ret, unsigned int msp_error_code, UART_BAUDRATE baudrate){
	const std::string common_hint("Common Hint: For SP Flash Tool issues:\n\n"
		"Please supply your tool version, GUI screen shot, and tool logs when you encounter trouble with the latest tool.\n"
		"How to obtain the tool logs?\n"
		"1. Run the tool;\n"
		"2. Press Ctrl+Alt+t(Tool Title Hint: Runtime Trace Mode);\n"
		"3. [Menu]Help-[SubMenu]Open logs folder.\n\n");
	std::string err_msg;
	std::string module_err_msg;

	switch(error_code_mode){
	case EBOOT:
		module_err_msg = EbootErrorMessage(static_cast<EBOOT_RESULT>(ret));
		break;
	case GPS:
		module_err_msg = GPSErrorMessage(static_cast<WRAPPER_RETURN>(ret));
		break;
	case META:
		module_err_msg = MetaErrorMessage(static_cast<META_RESULT>(ret));
		break;
	case BROM:
		module_err_msg = BromErrorMessage(static_cast<STATUS_E>(ret), msp_error_code, baudrate);
		break;
	case FLASHTOOL:
		module_err_msg = FlashToolErrorMessage(static_cast<FLASH_TOOL_RESULT>(ret));
		break;
	default:
		LOGE("Unknown module issue.");
		module_err_msg = "Unknown module issue.";
	}
	err_msg = common_hint + module_err_msg;
	return err_msg;
}

string ErrorLookup::MetaErrorMessage(META_RESULT ret){
	string msg("META Hint: \r\n");
	msg.append(META_GetErrorString( (META_RESULT)ret )).append("\r\n");
	return msg;
}

string ErrorLookup::BromErrorMessage(STATUS_E status,
		unsigned int error_code, UART_BAUDRATE baudrate) {
	string prefix, errMsg, tipMsg;

	if (S_SECURITY_ERROR_BEGIN <= status) {
		char buf[256];
		sprintf(buf,
				"BROM ERROR : %s (%d) , MSP ERROE CODE : 0x%02X. ",
				StatusToString(status), status, error_code);
		prefix.append(buf);
	} else if (status == -1) {
		prefix.append("BROM ERROR : FROM UI ");
	} else {
		prefix.append("BROM ERROR : ").append(StatusToString(status)) .append(" (").append(
				NumberToString(status)).append(")");
	}

	switch (status) {
	//	    case S_STOP: break;
	//	    case S_UNDEFINED_ERROR: break;
	//	    case S_INVALID_ARGUMENTS: break;
	//	    case S_INVALID_BBCHIP_TYPE: break;
	//	    case S_INVALID_EXT_CLOCK: break;
	//	    case S_GET_DLL_VER_FAIL: break;
	//	    case S_INVALID_BUF: break;
	//	    case S_BUF_IS_NULL: break;
	//	    case S_BUF_LEN_IS_ZERO: break;
	//	    case S_BUF_SIZE_TOO_SMALL: break;
	//	    case S_NOT_ENOUGH_MEMORY: break;

	case S_COM_PORT_OPEN_FAIL:
		errMsg.append("[COM] Failed to open COM ").append(NumberToString(
				COM_PORT));
		tipMsg = "Possible reason:" 
			"1. If you use UART1 to download DA, please make sure that you have selected  the correct UART1 COM port first!"
			"2. USB driver is abnormal, please restore them, and then try again.";
		break;

	case S_COM_PORT_SET_TIMEOUT_FAIL:
		errMsg.append("[COM] Failed to set COM").append(
				NumberToString(COM_PORT)).append(" timeout!");
		break;

		//	    case S_COM_PORT_SET_STATE_FAIL: break;
		//	    case S_COM_PORT_PURGE_FAIL: break;
		//	    case S_FILEPATH_NOT_SPECIFIED_YET: break;

	case S_UNKNOWN_TARGET_BBCHIP:
		errMsg = "[User] Unsupported target baseband chip type!";
		tipMsg = "Please upgrade to the latest FlashTool then try again.";
		break;

		//	    case S_SKIP_BBCHIP_HW_VER_CHECK: break;

	case S_UNSUPPORTED_VER_OF_BOOT_ROM:
		errMsg = "[User] Unsupported Boot ROM !";
		tipMsg = "Please upgrade to the latest FlashTool then try again.";
		break;

	case S_UNSUPPORTED_VER_OF_BOOTLOADER:
		errMsg
				= "[MAUI] Boot Loader Image file contains an unsupported version in its header! Please ask for help.";
		break;

	case S_UNSUPPORTED_VER_OF_DA:
		errMsg
				= "[DA] DA binary file contains an unsupported version in its header! Please ask for help.";
		break;

	case S_UNSUPPORTED_VER_OF_SEC_INFO:
		errMsg
				= "[MAUI] MAUI binary file contains an unsupported security version! Please ask for help.";
		break;

	case S_UNSUPPORTED_VER_OF_ROM_INFO:
		errMsg
				= "[MAUI] MAUI binary file contains an unsupported MAUI version! Please ask for help.";
		break;

	case S_SEC_INFO_NOT_FOUND:
		errMsg
				= "[User] Your ROM files doesn't enable secure! Secure-on BB must boot up with secure-on ROM files!";
		tipMsg = "Please use a secure-on ROM file then try again.";
		break;

	case S_ROM_INFO_NOT_FOUND:
		errMsg
				= "[MAUI] There doesn't exist a header in MAUI file! Please ask for help.";
		break;

	case S_CUST_PARA_NOT_SUPPORTED:
		errMsg
				= "[User] The phone doesn't contain Customer Parameter Area! Please check it again.";
		break;

	case S_CUST_PARA_WRITE_LEN_INCONSISTENT:
		errMsg
				= "[User] The size of Customer Parameter file is inconsistent with that on the phone!\r\n\
	            Please check it again.";
		break;

		//	    case S_SEC_RO_NOT_SUPPORTED: break;
		//	    case S_SEC_RO_WRITE_LEN_INCONSISTENT: break;
		//	    case S_ADDR_N_LEN_NOT_32BITS_ALIGNMENT: break;

	case S_UART_CHKSUM_ERROR:
		errMsg
				= "[H/W] Read-back SEC_RO or CUST_PARA and its checksum is mismatched \r\n\
	            with the checksum BROM DLL calculates after receiving through UART! ";
		tipMsg = "Please check your UART cable is stable or not.";
		break;

		//	    case S_NOR_FLASH_BOOT: break;
		//	    case S_NAND_FLASH_BOOT: break;

	case S_UNSUPPORTED_VER_OF_EMI_INFO:
		errMsg
				= "[MAUI] MAUI binary file contains an unsupported version of EMI setting! Please ask for help.";
		break;

		//=> BOOT ROM error code (2000~2999)
		//	    case S_BROM_SET_META_REG_FAIL: break;
		//	    case S_BROM_SET_FLASHTOOL_REG_FAIL: break;
		//	    case S_BROM_SET_REMAP_REG_FAIL: break;
		//	    case S_BROM_SET_EMI_FAIL: break;

	case S_BROM_DOWNLOAD_DA_FAIL:
		errMsg = "[H/W] Fail to download DA to baseband chip's internal SRAM! ";
		tipMsg =  
			    "1. There's an cable communication problem between FlashTool and BootROM.\r\n"
	            "2. Target might be shutdown unexpectedly or target lost power supply.\r\n"
	            "[ACTION]\r\n"
	            "1. Try again.\r\n"
	            "2. Proceed H/W checking in download cable and target side com port.\r\n"
	            "3. Monitor if power-drop occured in target side.";
		break;

	case S_BROM_CMD_STARTCMD_FAIL:
		errMsg = "[BROM] Can not pass bootrom start command via USB cable! ";
		tipMsg = "1. Possibly target power up too early, please try again.\n"
			"2. Load in the phone does not support bootloader download DA, please try to use BootRom download DA instead.\n"
			"How to use BootRom download DA?\n"
			"Step1. Unplug battery and USB cable in the target.\n"
			"Step2. Plug in battery.\n"
			"Step3. Press USB download key and do not loose it.\n"
			"Step4. Plug in USB cable.\n"
			"Step5. After DA is downloading, USB download key could be loosed.\n"
			"Step6. If it dose not work, please retry from Step1 to Step6.";
		break;

	case S_BROM_CMD_STARTCMD_TIMEOUT:
		errMsg = "[BROM] BootROM start command timeout!";
		break;

		//	    case S_BROM_CMD_JUMP_FAIL:break;
		//	    case S_BROM_CMD_WRITE16_MEM_FAIL:break;
		//	    case S_BROM_CMD_READ16_MEM_FAIL:break;
		//	    case S_BROM_CMD_WRITE16_REG_FAIL:break;
		//	    case S_BROM_CMD_READ16_REG_FAIL:break;
		//	    case S_BROM_CMD_CHKSUM16_MEM_FAIL:break;
		//	    case S_BROM_CMD_WRITE32_MEM_FAIL:break;
		//	    case S_BROM_CMD_READ32_MEM_FAIL:break;
		//	    case S_BROM_CMD_WRITE32_REG_FAIL:break;
		//	    case S_BROM_CMD_READ32_REG_FAIL:break;
		//	    case S_BROM_CMD_CHKSUM32_MEM_FAIL:break;
		//	    case S_BROM_JUMP_TO_META_MODE_FAIL:break;
		//	    case S_BROM_WR16_RD16_MEM_RESULT_DIFF:break;

	case S_BROM_CHKSUM16_MEM_RESULT_DIFF:
		errMsg
				= "[H/W] Fail to download DA to baseband chip's internal SRAM!\n\
	                     The internal SRAM has the problem that leads to 16 bits checksum error!";
		break;

	case S_BROM_BBCHIP_HW_VER_INCORRECT:
		errMsg = "[H/W] Target baseband chip is inconsistent with bin files!";
		tipMsg
				= "Please select the suitable bin files for the target's baseband chip.";
		break;

	case S_BROM_FAIL_TO_GET_BBCHIP_HW_VER:
		errMsg = "[H/W] Fail to get target baseband chip H/W version!";
		tipMsg
				= "\r\n\
	            1. There's an cable communication problem between FlashTool and BootROM.\r\n\
	            2. Target might be shutdown unexpectedly.\r\n\
	            \r\n\
	            [ACTION]\r\n\
	            1. Try again.\r\n\
	            2. Proceed H/W checking in download cable and target side UART path.\r\n\
	            3. Monitor if power-drop occured in target side.";
		break;

	case S_BROM_AUTOBAUD_FAIL:
		errMsg
				= "[H/W] BootROM start command passed but fail to multiple BootROM baudrate!";
		tipMsg
				= "\r\n\
	            1. There's an cable communication problem between FlashTool and BootROM.\r\n\
	            2. Target might be shutdown unexpectedly.\r\n\
	            \r\n\
	            [ACTION]\r\n\
	            1. Try again.\r\n\
	            2. If the problem still exists. Disable \"Options\"->\"Transmission option\"->\"Speed-Up BootROM baudrate\r\n\
	            in advance mode (CTRL+ALT+V) then try again.\r\n\
	            3. Proceed H/W checking in download cable and target side UART path.\r\n\
	            4. Monitor if power-drop occured in target side.";
		break;

	case S_BROM_SPEEDUP_BAUDRATE_FAIL:
		errMsg
				= "[H/W] BootROM start command passed but fail to multiple BootROM baudrate!";
		tipMsg
				= "1. There's an cable communication problem between FlashTool and BootROM.\r\n\
	            2. Target might be shutdown unexpectedly.\r\n\
	            \r\n\
	            [ACTION]\r\n\
	            1. Try again.\r\n\
	            2. If the problem still exists. Disable \"Options\"->\"Transmission option\"->\"Speed-Up BootROM baudrate\"\r\n\
	            in advance mode (CTRL+ALT+V) then try again.\r\n\
	            3. Proceed H/W checking in download cable and target side UART path.\r\n\
	            4. Monitor if power-drop occured in target side.";
		break;

		//	    case S_BROM_LOCK_POWERKEY_FAIL:break;
		//	    case S_BROM_WM_APP_MSG_OUT_OF_RANGE:break;
		//	    case S_BROM_NOT_SUPPORT_MT6205B:break;

	case S_BROM_EXCEED_MAX_DATA_BLOCKS:
		errMsg = "[MAUI] The number of Multi-Bin files is more than 10!";
		tipMsg = "Please don't build more than 10 binary files.";
		break;

		//	    case S_BROM_EXTERNAL_SRAM_DETECTION_FAIL:break;
		//	    case S_BROM_EXTERNAL_DRAM_DETECTION_FAIL:break;


		//=> DA error code (3000~3999)

	case S_DA_INT_RAM_ERROR:
		errMsg = "[H/W] DA didn't detect internal RAM!";
		tipMsg = "It maybe a SMT issue. Please ask for help.";
		break;

	case S_DA_EXT_RAM_ERROR:
		errMsg = "[H/W] DA didn't detect external RAM!";
		tipMsg
				= "1. It maybe a SMT issue.\r\n\
	            2. It maybe a EMI issue.\r\n\
	            Please ask for help.";
		break;

		//	    case S_DA_SETUP_DRAM_FAIL:break;
		//	    case S_DA_SETUP_PLL_ERR:break;

	case S_DA_DRAM_NOT_SUPPORT:
		errMsg = "[H/W] The handset doesn't support DRAM. Please ask for help.";
		break;

	case S_DA_RAM_FLOARTING:
		errMsg = "[H/W] DA detects that DRAM is floating!";
		tipMsg
				= "1. It maybe a SMT issue.\r\n\
	            2. It maybe a EMI issue.\r\n\
	            Please ask for help.";
		break;

	case S_DA_RAM_UNACCESSABLE:
		errMsg
				= "[H/W] DA detects that RAM is un-accessable. It maybe a SMT issue. Please ask for help.";
		break;

	case S_DA_RAM_ERROR:
		errMsg
				= "[H/W] DA detects other access error of RAM! Please ask for help.";
		break;

	case S_DA_DEVICE_NOT_FOUND:
		errMsg = "[H/W] DA didn't detect external SRAM or DRAM on the phone.";
		tipMsg
				= "1. It maybe a SMT issue.\r\n\
	            2. It maybe a EMI issue.\r\n\
	            3. NOR or NAND hasn't been validated.\r\n\
	            Please check \"Memory_Validation_List_External.xls\" or ask for help.";
		break;

	case S_DA_NOR_UNSUPPORTED_DEV_ID:
		errMsg = "[User] Unsupported NOR Flash type!";
		tipMsg = "Please upgrade to the latest FlashTool then try again.";
		break;

	case S_DA_NAND_UNSUPPORTED_DEV_ID:
		errMsg = "[User] Unsupported NAND Flash type!";
		tipMsg = "Please upgrade to the latest FlashTool then try again.";
		break;

	case S_DA_NOR_FLASH_NOT_FOUND:
		errMsg = "[H/W] DA didn't detect NOR Flash on the phone.";
		tipMsg
				= "1. It maybe a SMT issue.\r\n\
	            2. It maybe a EMI issue.\r\n\
	            3. NOR or NAND hasn't been validated.\r\n\
	            Please check \"Memory_Validation_List_External.xls\" or ask for help.";
		break;

	case S_DA_NAND_FLASH_NOT_FOUND:
		errMsg = "[H/W] DA didn't detect NAND Flash on the phone.";
		tipMsg
				= "1. It maybe a SMT issue.\r\n\
	            2. It maybe a NFI issue.\r\n\
	            3. NOR or NAND hasn't been validated.\r\n\
	            Please check \"Memory_Validation_List_External.xl\" or ask for help.";
		break;

	case S_DA_SOC_CHECK_FAIL:
		errMsg = "[User] SOC verification fail!";
		break;

	case S_DA_NOR_PROGRAM_FAILED:
		errMsg = "[H/W] DA fails to program NOR Flash!";
		tipMsg = "1. It maybe a SMT issue. Please ask for help.";
		break;

	case S_DA_NOR_ERASE_FAILED:
		errMsg = "[H/W] DA fails to erase NOR Flash!";
		tipMsg = "1. It maybe a SMT issue. Please ask for help.";
		break;

	case S_DA_NAND_PAGE_PROGRAM_FAILED:
		errMsg = "[H/W] DA fails to page-program NAND Flash!";
		tipMsg = "1. It maybe a SMT issue. Please ask for help.";
		break;

	case S_DA_NAND_SPARE_PROGRAM_FAILED:
		errMsg = "[H/W] DA fails to spare-program NAND Flash!";
		tipMsg = "1. It maybe a SMT issue. Please ask for help.";
		break;

		//	    case S_DA_NAND_HW_COPYBACK_FAILED:break;
		//	    case S_DA_NAND_ERASE_FAILED:break;
		//	    case S_DA_TIMEOUT:break;
		//	    case S_DA_IN_PROGRESS:break;
		//	    case S_DA_SUPERAND_ONLY_SUPPORT_PAGE_READ:break;
		//	    case S_DA_SUPERAND_PAGE_PRGRAM_NOT_SUPPORT:break;
		//	    case S_DA_SUPERAND_SPARE_PRGRAM_NOT_SUPPORT:break;
		//	    case S_DA_SUPERAND_COPYBACK_NOT_SUPPORT:break;
		//	    case S_DA_NOR_CMD_SEQUENCE_ERR:break;
		//	    case S_DA_NOR_BLOCK_IS_LOCKED:break;
		//	    case S_DA_NAND_BLOCK_IS_LOCKED:break;

	case S_DA_NAND_BLOCK_DATA_UNSTABLE:
		errMsg
				= "[H/W] Data of the block is unstable after erasing NAND Flash.!";
		tipMsg = "1. It maybe a SMT issue. Please ask for help.";
		break;

	case S_DA_NOR_BLOCK_DATA_UNSTABLE:
		errMsg
				= "[H/W] Data of the block is unstable after erasing NOR Flash.!";
		tipMsg = "It maybe a SMT issue. Please ask for help.";
		break;

	case S_DA_NOR_VPP_RANGE_ERR:
		errMsg
				= "[H/W] Vpp is out of working range for NOR Flash! Please ask for help.";
		break;

	case S_DA_INVALID_BEGIN_ADDR:
              errMsg 
			  	= "An invlid beginning address is given for erase operation.";
              tipMsg     = "Possibly begin address is not align to 512(0x200) for EMMC.";

		break;	      

	case S_DA_NOR_INVALID_ERASE_BEGIN_ADDR:
		errMsg
				= "[User] An invalid begging address is given for erase operation on NOR Flash.";
		tipMsg = "Please check your erase address again.";
		break;

	case S_DA_NOR_INVALID_READ_BEGIN_ADDR:
		errMsg
				= "[User] An invalid begging address is given for read operation on NOR Flash.";
		tipMsg = "Please check your read address again.";
		break;

	case S_DA_NOR_INVALID_PROGRAM_BEGIN_ADDR:
		errMsg
				= "[User] An invalid begging address is given for program operation on NOR Flash.";
		tipMsg = "Please check your program address again.";
		break;

	case S_DA_INVALID_RANGE:
		errMsg = "[User] DA_MEM_CMD command fail!";
		tipMsg = "1. One of the download blocks has invalid range.\r\n"
			"2. Possibly invalid begin address or end address exceeds target flash size.\n"
			"3. Possibly logcial begin address or length exceeds check boundary.";
        if(-1 != g_ulNandFormatLengthByDAReport) {
            std::ostringstream ss;
            ss << "\r\n3. The target flash size is 0x"
               << std::hex
               << g_ulNandFormatLengthByDAReport
               << std::dec
               << " by DA report.";
            string daMsg = ss.str();
            tipMsg += daMsg;
        }
		break;

	case S_DA_NOR_PROGRAM_AT_ODD_ADDR:
		errMsg = "[User] DA_MEM_CMD command fail!";
		tipMsg = "1. One of the download blocks has the ODD begin address!";
		break;

	case S_DA_NOR_PROGRAM_WITH_ODD_LENGTH:
		errMsg = "[User] DA_MEM_CMD command fail!";
		tipMsg
				= "1. One of the download blocks has the EVEN end address! That is download block is in ODD length.";
		break;

		//	    case S_DA_NOR_BUFPGM_NO_SUPPORT:break;
		//	    case S_DA_NAND_UNKNOWN_ERR:break;
		//	    case S_DA_NAND_BAD_BLOCK:break;
		//	    case S_DA_NAND_ECC_1BIT_CORRECT:break;
		//	    case S_DA_NAND_ECC_2BITS_ERR:break;
		//	    case S_DA_NAND_SPARE_CHKSUM_ERR:break;
		//	    case S_DA_NAND_HW_COPYBACK_DATA_INCONSISTENT:break;
		//	    case S_DA_NAND_INVALID_PAGE_INDEX:break;
		//	    case S_DA_NFI_NOT_SUPPORT:break;
		//	    case S_DA_NFI_CS1_NOT_SUPPORT:break;
		//	    case S_DA_NFI_16BITS_IO_NOT_SUPPORT:break;

	case S_DA_NFB_BOOTLOADER_NOT_EXIST:
		errMsg
				= "[User] BootLoader doesn't exist on NAND flash! Please download BootLoader first!";
		break;

	case S_DA_NAND_NO_GOOD_BLOCK:
		errMsg = "[H/W] There doesn't exist any good block on NAND Flash!";
		break;

	case S_DA_BOOTLOADER_IS_TOO_LARGE:
		errMsg
				= "[MAUI] Boot Loader Image is more than 7 blocks on NAND Flash!\n\nPlease ask for help.";
		break;

		//	    case S_DA_SIBLEY_REWRITE_OBJ_MODE_REGION:break;
		//	    case S_DA_SIBLEY_WRITE_B_HALF_IN_CTRL_MODE_REGION:break;
		//	    case S_DA_SIBLEY_ILLEGAL_CMD:break;
		//	    case S_DA_SIBLEY_PROGRAM_AT_THE_SAME_REGIONS:break;
		//	    case S_DA_UART_GET_DATA_TIMEOUT:break;
		//	    case S_DA_UART_GET_CHKSUM_LSB_TIMEOUT:break;
		//	    case S_DA_UART_GET_CHKSUM_MSB_TIMEOUT:break;
		//	    case S_DA_UART_DATA_CKSUM_ERROR:break;
		//	    case S_DA_UART_RX_BUF_FULL:break;
		//	    case S_DA_FLASH_RECOVERY_BUF_NOT_ENOUGH:break;
		//	    case S_DA_HANDSET_SEC_INFO_NOT_FOUND:break;
		//	    case S_DA_HANDSET_SEC_INFO_MAC_VERIFY_FAIL:break;
		//	    case S_DA_HANDSET_ROM_INFO_NOT_FOUND:break;
		//	    case S_DA_HANDSET_FAT_INFO_NOT_FOUND:break;
		//	    case S_DA_OPERATION_UNSUPPORT_FOR_NFB:break;
		//	    case S_DA_BYPASS_POST_PROCESS:break;
		//	    case S_DA_NOR_OTP_NOT_SUPPORT:break;
		//	    case S_DA_NOR_OTP_EXIST:break;
		//	    case S_DA_NOR_OTP_LOCKED:break;
		//	    case S_DA_NOR_OTP_GETSIZE_FAIL:break;
		//	    case S_DA_NOR_OTP_READ_FAIL:break;
		//	    case S_DA_NOR_OTP_PROGRAM_FAIL:break;
		//	    case S_DA_NOR_OTP_LOCK_FAIL:break;
		//	    case S_DA_NOR_OTP_LOCK_CHECK_STATUS_FAIL:break;

	case S_DA_BLANK_FLASH:
		errMsg
				= "[User] There doesn't exist MAUI code and SEC_RO (option) on the flash.";
		tipMsg
				= "Please choose MAUI file and SEC_RO file (option) for downloading.";
		break;

	case S_DA_CODE_AREA_IS_BLANK:
		errMsg = "[User] There doesn't exist MAUI code on the flash.";
		tipMsg = "Please choose MAUI file for downloading.";
		break;

	case S_DA_SEC_RO_AREA_IS_BLANK:
		errMsg = "[User] There doesn't exist SEC_RO (option) on the flash.";
		tipMsg = "Please choose SEC_RO file (option) for downloading.";
		break;

		//	    case S_DA_NOR_OTP_UNLOCKED:break;

	case S_DA_UNSUPPORTED_BBCHIP:
		errMsg
				= "[User] BROM DLL is too old to support this baseband chip on the phone!";
		tipMsg = "Please upgrade to the latest FlashTool then try again.";
		break;

	case S_DA_FAT_NOT_EXIST:
		errMsg = "[User] FAT doesn't exist on the phone!";
		break;

	case S_DA_EXT_SRAM_NOT_FOUND:
		errMsg
				= "[H/W] DA didn't detect external SRAM on the phone! Please ask for help.";
		break;

	case S_DA_EXT_DRAM_NOT_FOUND:
		errMsg
				= "[H/W] DA didn't detect external DRAM on the phone! Please ask for help.";
		break;

	case S_DA_MT_PIN_LOW:
		errMsg
				= "[H/W] DA detects that a pin is always low on the phone while memory test! Please ask for help.";
		break;

	case S_DA_MT_PIN_HIGH:
		errMsg
				= "[H/W] DA detects that a pin is always high on the phone while memory test! Please ask for help.";
		break;

	case S_DA_MT_PIN_SHORT:
		errMsg
				= "[H/W] DA detects that two pin is short on the phone while memory test! Please ask for help.";
		break;

	case S_DA_MT_BUS_ERROR:
		errMsg
				= "[H/W] DA detects bus error on the phone while memory test! Please ask for help.";
		break;

	case S_DA_MT_ADDR_NOT_2BYTE_ALIGNMENT:
		errMsg
				= "[User] Input address is not 2-Byte aligned while memory test!";
		tipMsg = "Please ask for help.";
		break;

	case S_DA_MT_ADDR_NOT_4BYTE_ALIGNMENT:
		errMsg
				= "[User] Input address is not 4-Byte aligned while memory test!";
		tipMsg = "Please ask for help.";
		break;

	case S_DA_MT_SIZE_NOT_2BYTE_ALIGNMENT:
		errMsg = "[User] Input size is not 2-Byte aligned while memory test!";
		tipMsg = "Please ask for help.";
		break;

	case S_DA_MT_SIZE_NOT_4BYTE_ALIGNMENT:
		errMsg = "[User] Input size is not 4-Byte aligned while memory test!";
		tipMsg = "Please ask for help.";
		break;

	case S_DA_MT_DEDICATED_PATTERN_ERROR:
		errMsg
				= "[H/W] DA detects error on the phone while memory test with dedicated pattern! Please ask for help.";
		break;

	case S_DA_MT_INC_PATTERN_ERROR:
		errMsg
				= "[H/W] DA detects error on the phone while memory test with incremental pattern! Please ask for help.";
		break;

	case S_DA_MT_DEC_PATTERN_ERROR:
		errMsg
				= "[H/W] DA detects error on the phone while memory test with decremental pattern! Please ask for help.";
		break;

	case S_DA_NFB_BLOCK_0_IS_BAD:
		errMsg
				= "[H/W] DA detects Block 0 of NAND Flash is bad! Please ask for help.";
		break;

		//=> FlashTool error code (4000~4999)
		//	    case S_FT_CALLBACK_DA_REPORT_FAIL:break;
	case S_DA_EMMC_OTP_LOCKED:
             errMsg
                         = "[User]OTP has been locked!";
             break;

       case S_DA_OTP_LOCKED:
             errMsg
                         = "[User]OTP has been locked!";
             break;

	case S_FT_DA_NO_RESPONSE:
		errMsg = "DA didn't send response data to FlashTool!";
		break;

	case S_FT_DA_SYNC_INCORRECT:
		errMsg = "[User] DA sync fail! Possibly download an illegal DA.";
		break;

	case S_FT_DA_VERSION_INCORRECT:
		errMsg = "[User] DA version is incorrect!";
		break;

	case S_FT_DA_INIT_SYNC_ERROR:
		errMsg = "Fail to send sync data to DA in initialization stage!";
		break;

		//	    case S_FT_GET_DSP_VER_FAIL:break;

	case S_FT_CHANGE_BAUDRATE_FAIL: {
		unsigned int baudrate_tbl[] = { 0, 921600, 460800, 230400, 115200,
				57600, 38400, 19200, 9600, 4800, 2400, 1200, 300, 110 };
		errMsg = "Fail to change baudrate to " + NumberToString(
				baudrate_tbl[baudrate]) + ".";
	}
		break;

	case S_FT_SET_DOWNLOAD_BLOCK_FAIL:
		errMsg = "DA_MEM_CMD command fail! Possibly the following reason.";
		tipMsg
				= "1. Download block exceeds target flash size.\r\n\
	            2. Download block start address is not WORD alignment.\r\n\
	            3. Download block length is not multiple of WORD.";
		break;

	case S_FT_DOWNLOAD_FAIL:
		errMsg
				= "Download to flash fail! Please press CTRL+ALT+T to turn on debug log then reproduce again!";
		tipMsg
				= "BROM_DLL_V5.log and BROM_DLL.log would be created and record more detail information.";
		break;

	case S_FT_READBACK_FAIL:
		errMsg
				= "Readback from flash fail! Please press CTRL+ALT+T to turn on debug log then reproduce again!";
		tipMsg
				= "BROM_DLL_V5.log and BROM_DLL.log would be created and record more detail information.";
		break;

	case S_FT_FORMAT_FAIL:
		errMsg
				= "Format flash error! Possibly given a wrong format range, please check your format setting.";
		break;

	case S_FT_FINISH_CMD_FAIL:
		errMsg = "DA_FINISH_CMD command fail!";
		break;

		//	    case S_FT_ENABLE_WATCHDOG_FAIL:break;

	case S_FT_NFB_DOWNLOAD_BOOTLOADER_FAIL:
		errMsg = "Fail to download BootLoader to NAND flash!";
		break;

	case S_FT_NFB_DOWNLOAD_CODE_FAIL:
		errMsg = "Fail to download Image(s) to NAND flash!";
		break;

		//	    case S_FT_NFB_INVALID_BOOTLOADER_DRAM_SETTING:break;

	case S_FT_NAND_READADDR_NOT_PAGE_ALIGNMENT:
		errMsg
				= "[User] The begging address of read-back operation is not page-aligned on NAND Flash!";
		tipMsg = "Please check your read address again.";
		break;

	case S_FT_NAND_READLEN_NOT_PAGE_ALIGNMENT:
		errMsg
				= "[User] The length of read-back operation is not page-aligned on NAND Flash!";
		tipMsg = "Pease check your read address again.";
		break;

		//	    case S_FT_READ_REG16_FAIL:break;
		//	    case S_FT_WRITE_REG16_FAIL:break;
		//	    case S_FT_CUST_PARA_GET_INFO_FAIL:break;
		//	    case S_FT_CUST_PARA_READ_FAIL:break;
		//	    case S_FT_CUST_PARA_WRITE_FAIL:break;
		//	    case S_FT_INVALID_FTCFG_OPERATION:break;
		//	    case S_FT_INVALID_CUST_PARA_OPERATION:break;
		//	    case S_FT_INVALID_SEC_RO_OPERATION:break;
		//	    case S_FT_INVALID_OTP_OPERATION:break;
		//	    case S_FT_POST_PROCESS_FAIL:break;
		//	    case S_FT_FTCFG_UPDATE_FAIL:break;
		//	    case S_FT_SEC_RO_GET_INFO_FAIL:break;
		//	    case S_FT_SEC_RO_READ_FAIL:break;
		//	    case S_FT_SEC_RO_WRITE_FAIL:break;
		//	    case S_FT_FS_FINDFIRSTEX_FAIL:break;
		//	    case S_FT_FS_FINDNEXTEX_FAIL:break;
		//	    case S_FT_FS_FOPEN_FAIL:break;
		//	    case S_FT_FS_GETFILESIZE_FAIL:break;
		//	    case S_FT_FS_READ_FAIL:break;

	case S_FT_ENABLE_DRAM_FAIL:
		errMsg = "[EMI] Enable DRAM Failed!";
		tipMsg = "Please check your load matches to your target which is to be downloaded.";
		break;

	case S_DL_GET_DRAM_SETTING_FAIL:
		errMsg = "[EMI] Obtain DRAM Failed!";
		tipMsg = "Please check your load matches to your target which is to be downloaded.";
		break;

	case S_FT_FS_FILENAME_INVALID:
		errMsg
				= "[User] The used filename is valid! Please check if your file exists.";
		break;

	case S_FT_FS_FILENAME_TOO_LONG:
		errMsg
				= "[User] The length of used filename is too long! Please check \r\n\
	            your filename is valid.";
		break;

		//	    case S_FT_FS_ASSERT:break;

	case S_FT_OTP_ADDR_NOT_WORD_ALIGNMENT:
		errMsg
				= "[User] The address given of OTP operation is not word-aligned!";
		tipMsg = "Please check your OTP address again.";
		break;

	case S_FT_OTP_LENGTH_NOT_WORD_ALIGNMENT:
		errMsg
				= "[User] The length given of OTP operation is not word-aligned! \r\n\Please check your OTP length again.";
		break;

	case S_FT_OTP_INVALID_ADDRESS_RANGE:
		errMsg
				= "[User] The address given of OTP operation is out of range! \r\n\Please check your OTP address and length again.";
		break;

		//	    case S_FT_NAND_READ_TO_BUFFER_NOT_SUPPORT:break;
		//	    case S_FT_GET_PROJECT_ID_FAIL:break;

	case S_FT_ENFB_ROM_FILE_SMALL_THAN_HEADER_DESCRIBE:
		errMsg
				= "[MAUI] The size of E-NFB Rom file is smaller than that described \r\n\
	            in header of E-NFB Rom file! Please ask for help.";
		break;

	case S_FT_NEED_DOWNLOAD_ALL_FAIL:
		errMsg = "Need download all images!";
		tipMsg = "DA paritial images download is ONLY allowed under following prerequisite:"
			"1. All images have been downloaded to target before, and target could boot up;"
			"2. The images layout map on the target is same as the load that is to be downloaded.";
		break;

	case S_FT_UPDATE_PARTITION_TBL_FAIL:
		errMsg = "Update NAND Flash partition table failed!";
		break;

		//	    case S_FT_RW_EXTRACT_NFB_FAIL:break;
		//	    case S_FT_MEMORY_TEST_FAIL:break;

		//=> FlashTool Handle error code (5000~5999)
	case S_AUTH_HANDLE_IS_NOT_READY:
		errMsg
				= "[User] This is a secure Base-band Chip! Please select the authentication file first.";
		break;

	case S_INVALID_AUTH_FILE:
		errMsg
				= "[User] This is an invalid authentication file with wrong format! Please ask for help.";
		break;

	case S_INVALID_DA_FILE:
		errMsg
				= "[User] This is an invalid DA file with wrong format! Please ask for help.";
		break;

		//	    case S_DA_HANDLE_IS_NOT_READY:break;
		//	    case S_FTHND_ILLEGAL_INDEX:break;
		//	    case S_FTHND_HANDLE_BUSY_NOW:break;
		//	    case S_FTHND_FILE_IS_UPDATED:break;

	case S_FTHND_FILE_IS_NOT_LOADED_YET:
		errMsg = "There is file not loaded yet!!";
		tipMsg
				= "\r\n\
	            1. Please check if the DA path is correct.\r\n\
	            2. Please check if all the ROM files exist.\r\n\
	            3. Please check if the scatter file description is sync with the exist ROM files.";
		break;

		//	    case S_FTHND_FILE_LOAD_FAIL:break;
		//	    case S_FTHND_FILE_UNLOAD_FAIL:break;

	case S_FTHND_LIST_IS_EMPTY:
		errMsg = "Download or Readback list is empty or all disabled!";
		tipMsg = "Please select at least one entry.\r\n"
	                 "[For Android]Please load scatter file first from load folder.";
		break;

	case S_DL_SCAT_INCORRECT_FORMAT:
		errMsg
				= "[MAUI] The scatter file has incorrect format! Please ask for help.";
		break;

	case S_DL_SCAT_ADDR_IS_NOT_WORD_ALIGN:
		errMsg
				= "[MAUI] The address of some Load Region in the scatter file is\r\n\
	            not word-aligned! Please ask for help.";
		break;

	case S_DL_SCAT_OFFSET_IS_NOT_WORD_ALIGN:
		errMsg
				= "[MAUI] The offset of some Load Region in the scatter file is\r\n\
	            not word-aligned! Please ask for help.";
		break;

	case S_DL_SCAT_ADDR_IS_NOT_ASCENDING_ORDER:
		errMsg
				= "[MAUI] The addresses of all Load Region in the scatter file\r\n\
	            are not ascending in order! Please ask for help.";
		break;

	case S_DL_SCAT_JUMPTABLE_IS_NOT_ABSOLUTE_ADDR:
		errMsg
				= "[MAUI] The address of jump table binary file in the scatter file\r\n\
	            is not absolute address! Please ask for help.";
		break;

	case S_DL_LOAD_REGION_IS_OVERLAP:
		errMsg = "Load Rom image failed!";
		tipMsg  = "Possible reason is that the file, which is to be loaded, is too large and cause region overlap!";
		break;

		//	    case S_DL_LOAD_REGION_NOT_FOUND:break;
		//	    case S_DL_NOT_RESOURCE_BIN:break;
		//	    case S_DL_MULTIBIN_MECHANISM_DISABLED:break;

	case S_DL_RESOURCE_NOT_MATCH_IN_JUMPTABLE:
		errMsg
				= "[DL_HANDLE] a bin file doesn't match any entry in jump table!";
		break;

	case S_DL_RESOURCE_MUST_DOWNLOAD_WITH_JUMPTABLE:
		errMsg
				= "[User] Resources and jump table are not selected to download \r\n\
	                     together! Please select all resource you wanna download";
		break;

		//	    case S_DL_OVERLAP_WITH_EXISTING_RESOURCE:break;
		//	    case S_DL_INVALID_RESOURCE_BIN:break;

	case S_DL_JUMPTABLE_INCONSISTENT_WITH_SCAT:
		errMsg = "[DL_HANDLE] jump table is different from scatter!";
		break;

	case S_DL_INVALID_JUMPTABLE:
		errMsg
				= "[MAUI] Jump table is not loaded yet!\r\n\
	            Because its content is not a correct jump table format.";
		break;

		//	    case S_DL_REGION_ADDR_INCONSISTENT_WITH_SCAT:break;

	case S_DL_REGION_ADDR_INCONSISTENT_WITH_RESOURCE_ADDR:
		errMsg
				= "[MAUI] The address of resource binary file in scatter file is \r\n\
	            inconsistent with the address in the header of resource binary \r\n\
	            file! Please ask for help.";
		break;

	case S_DL_INVALID_BOOTLOADER:
		errMsg
				= "[MAUI] The Boot Loader Image file has invalid information in its header! Please ask for help.";
		break;

		//	    case S_DL_BOOTLOADER_IS_NOT_LOADED_YET:break;
		//	    case S_DL_BOOTLOADER_NOT_FOUND:break;

	case S_DL_REMOTE_FILE_UNSUPPORTED_BY_BL_AUTOLOAD:
		errMsg = "[User] Boot Loader Image file is in remote server!";
		tipMsg = "Please use a local Boot Loader Image file in your computer.";
		break;

		//	    case S_DLIST_SAME_BBCHIP_SW_VER:break;

	case S_DLIST_BBCHIP_HW_VER_NOT_MATCHED:
		errMsg = "[H/W] Target baseband chip is inconsistent with bin files!";
		tipMsg
				= "Please select the suitable bin files for the target's baseband chip.";
		break;

		//	    case S_DLIST_NO_MATCHED_DL_HANDLE_FOUND:break;
		//	    case S_DLIST_DL_HANDLE_NOT_IN_LIST:break;
		//	    case S_DLIST_DL_HANDLE_ALREADY_IN_LIST:break;
		//	    case S_FTHND_CALLBACK_REMOTE_GET_FILE_LEN_FAIL:break;
		//	    case S_FTHND_CALLBACK_REMOTE_READ_FILE_FAIL:break;
		//	    case S_FTHND_CALLBACK_FILE_INTEGRITY_CHECK_FAIL:break;

	case S_UNSUPPORTED_VER_OF_AUTH_FILE:
		errMsg
				= "[User] The authentication file contains an unsupported version!";
		tipMsg
				= "Please check the FlashTool is the latest version, or ask for help.";
		break;

	case S_DL_PROJECT_ID_DIFF_BETWEEN_MAIN_CODE_AND_JUMP_TBL:
		errMsg
				= "[MAUI] The project IDs between MAUI code and jump table binary file are different!";
		tipMsg
				= "Please check the MAUI and jump table are in the same project.";
		break;

	case S_DL_SCAT_OPEN_FAIL:
		errMsg = "[User] The scatter file cannot be opened!";
		tipMsg
				= "Please check if your scatter file exists and is not used by other software.";
		break;

		//	    case S_FTHND_CALLBACK_COM_INIT_STAGE_FAIL:break;

	case S_DL_UNSECURE_MAUI_TO_SECURE_BB:
		errMsg = "[User] Un-secure MAUI cannot be downloaded into Secure BB!";
		tipMsg = "Please use security-enabled MAUI.";
		break;

		//=> security error code (6000~6999)
		//	    case S_SECURITY_CALLBACK_SLA_CHALLENGE_FAIL:break;

	case S_SECURITY_SLA_WRONG_AUTH_FILE:
		errMsg
				= "[User] The authentication file with a custom name is different \r\n\
	            from the custom name in the handset! Please ask the owner of this \r\n\
	            handset for an authentication file with a correct custom name.";
		break;

	case S_SECURITY_SLA_INVALID_AUTH_FILE:
		errMsg = "[User] An invalid authentication file is used!";
		tipMsg
				= "This error message will occurs with MSP (MTK Secure Platform) code.\r\n\
	            Please keep up the MSP code and ask for help.";
		break;

		//	    case S_SECURITY_SLA_CHALLENGE_FAIL:break;
		//	    case S_SECURITY_SLA_FAIL:break;
		//	    case S_SECURITY_DAA_FAIL:break;
		//	    case S_SECURITY_SBC_FAIL:break;

	case S_SECURITY_SF_SECURE_VER_CHECK_FAIL:
		errMsg
				= "[User] The secure version of the secure-MAUI is older than that in the handset!";
		tipMsg
				= "Please choose a secure-MAUI with an equal or newer secure version.";
		break;

	case S_SECURITY_SF_HANDSET_SECURE_CUSTOM_NAME_NOT_MATCH:
		errMsg
				= "[User] The custom name of the secure-MAUI is different from that in the handset!";
		tipMsg = "Please choose a secure-MAUI with the same custom name.";
		break;

	case S_SECURITY_SF_FTCFG_LOCKDOWN:
		errMsg = "[User] The Tool configuration is locked down!";
		break;

	case S_SECURITY_SF_CODE_DOWNLOAD_FORBIDDEN:
		errMsg = "[User] To download code area is forbidden in this phone!";
		break;

	case S_SECURITY_SF_CODE_READBACK_FORBIDDEN:
		errMsg = "[User] To read-back code area is forbidden in this phone!";
		break;

	case S_SECURITY_SF_CODE_FORMAT_FORBIDDEN:
		errMsg = "[User] To format code area is forbidden in this phone!";
		break;

	case S_SECURITY_SF_SEC_RO_DOWNLOAD_FORBIDDEN:
		errMsg = "[User] To download SEC_RO is forbidden in this phone!";
		break;

	case S_SECURITY_SF_SEC_RO_READBACK_FORBIDDEN:
		errMsg = "[User] To read-back SEC_RO is forbidden in this phone!";
		break;

	case S_SECURITY_SF_SEC_RO_FORMAT_FORBIDDEN:
		errMsg = "[User] To format SEC_RO is forbidden in this phone!";
		break;

	case S_SECURITY_SF_FAT_DOWNLOAD_FORBIDDEN:
		errMsg = "[User] To download FAT area is forbidden in this phone!";
		break;

	case S_SECURITY_SF_FAT_READBACK_FORBIDDEN:
		errMsg = "[User] To read-back FAT area is forbidden in this phone!";
		break;

	case S_SECURITY_SF_FAT_FORMAT_FORBIDDEN:
		errMsg = "[User] To format FAT area is forbidden in this phone!";
		break;

	case S_SECURITY_SF_RESTRICTED_AREA_ACCESS_FORBIDDEN:
		errMsg
				= "[User] To access restricted area (SEC_RO area and Flash Tool \r\n\
	            configuration area in the handset) is forbidden in this phone!";
		break;

	case S_SECURITY_SECURE_CUSTOM_NAME_NOT_MATCH_BETWEEN_AUTH_AND_DL_HANDLE:
		errMsg
				= "[User] The custom name in the authentication file is different from that in secure-MAUI!";
		tipMsg
				= "Please choose the same custom name between authentication file and secure-MAUI!";
		break;

	case S_SECURITY_DOWNLOAD_FILE_IS_CORRUPTED:
		errMsg
				= "[MAUI] Some information about security in secure-MAUI file is corrupted or broken! Please ask for help.";
		break;

	case S_PART_NO_VALID_TABLE:
		errMsg = "No valid Partition Management Table(PMT) for storage device!";
		tipMsg = "Please make sure there is a correct load in the target.\n"
			"\"Firmware Upgrade\" could not be executed without PMT!\n"
			"Please \"Download\" ONLY first to create PMT on the target!";
		break;

	case S_PART_NO_SPACE_FOUND:
		errMsg = "No space found for partition table!";
		tipMsg = "Please make sure there is a correct load in the target.";
		break;

	case S_DA_UPDATE_BOOTLOADER_FILE_SIZE_EXCEEDS_BOUNDARY_ADDR:
		errMsg = "DA download bootloader exceeds partition boundary in this device!";
		tipMsg = "Possible reason is that there are too many bad blocks in bootloader reserved area.";
		break;
	case S_SECURITY_DAA_FAIL:
		errMsg = "DA Security download error!";
		tipMsg = "Possible reason is that security DA is not signed by a correct key.";
		break;

    //2011.08.11 add for DSP_BL check
	case S_DA_DSPBL_CHECK_PLATFORM_FAILED:
		errMsg = "DA DSP_BL check platform error.";
		tipMsg = "Target platform is not consistent with DSP_BL, Please check the DSP_BL is correct or not.";
		break;

	case S_DA_UPDATE_BOOTLOADER_EXIST_MAGIC_NOT_MATCHED:
		errMsg = "DA DSP_BL check exist error.";
		tipMsg = "There is no DSP_BL in previous load on target, please use full set erase and download again.";
		break;
		
	case S_FTHND_FILE_LOAD_FAIL: 
		errMsg = "Load Rom image failed!";
		tipMsg = "Possible reason is that there is not enough space in PC memory to place the image.";
		break;

	case S_FT_FS_READ_FAIL:
		errMsg = "Read file to buffer failed!";
		tipMsg = "1.[File Not Exist] Please help check the file to be operated exist.\n"
			"2.[File Cursor Is Damaged] Please reload the same scatter file or image, and try again.\n"
			"3.[Bad Network] If the file to be operated is under SAMBA server, please copy the file to your local PC, and try again.";
	
       case S_DA_EMMC_FW_VER_CHECK_FAIL:
		errMsg = "[H/W] DA didn't detect EMMC Flash on the phone.";
		tipMsg
				= "1. It maybe a SMT issue.\r\n\
	            2. It maybe a EMI issue.\r\n\
	            3. EMMC hasn't been validated.\r\n\
	            Please check \"Memory_Validation_List_External.xls\" or ask for help.";
		break;      

	default:
		break;
	}

	std::ostringstream ostr;
	ostr << prefix << std::endl << std::endl
		<< errMsg << std::endl << std::endl
		<<"[HINT]: "<< std::endl
		<< tipMsg <<std::endl;

	return (ostr.str().c_str());
}

string ErrorLookup::EbootErrorMessage(EBOOT_RESULT ret) {
	string prefix, errMsg, tipMsg;

	if (ret == -1) {
		prefix.append(" EBOOT MESSAGE : ( UI )\n\n");
	} else {
		prefix.append(" EBOOT ERROR : ( ") .append(NumberToString(ret)).append(
				" )");
	}
	switch (ret) {

	case SET_COM_STATE_ERROR:
		errMsg = "[COM Setting] COM setting error!";
		tipMsg = "Set COM port state fail!";
		break;

	case OPEN_COM_PORT_ERROR:
		errMsg = "[COM] Open COM port failed!";
		tipMsg
				= "1.Please check if the COM port is correct and can work normally.";
		break;

	case READ_READY_PATTERN_ERROR:
		errMsg
				= "[BOOT] Read sync packet 'READY' from target's bootloader failed!";
		tipMsg
				= "\n1.Please check if the COM cable connection is good.\n"
					"2.Please check if the bootloader(xldr&eboot / uboot)is correct.\n"
					"3.Maybe bootloader's problem. \n"
					"Please catch target bootloader's log to get more information and to find help.";
		break;

	case WRITE_META_PATTERN_ERROR:
		errMsg
				= "[BOOT] Write sync packet 'META' to target's bootloader failed!";
		tipMsg = "1.Please check if the COM cable connection is good.";
		break;

	case READ_META_ACK_PATTERN_ERROR:
		errMsg
				= "[BOOT] Read sync packet 'META' from target's bootloader failed!";
		tipMsg
				= "\n1.Please check if the COM cable connection is good.\n"
					"2.Please check if the bootloader(xldr&eboot / uboot)is correct.\n"
					"3.Maybe bootloader's problem. \n"
					"Please catch target bootloader's log to get more information and to find help.";
		break;

	case WRITE_DOWNLOAD_PATTERN_ERROR:
		errMsg
				= "[BOOT] Write sync packet 'DOWNLOAD' to target's bootloader failed!";
		tipMsg = "1.Please check if the COM cable connection is good.";
		break;

	case READ_DOWNLOAD_ACK_PATTERN_ERROR:
		errMsg
				= "[BOOT] Read sync packet 'DOWNLOAD' from target's bootloader failed!";
		tipMsg
				= "\n1.Please check if the COM cable connection is good.\n"
					"2.Please check if the bootloader(xldr&eboot / uboot)is correct.\n"
					"3.Maybe bootloader's problem. \n"
					"Please catch target bootloader's log to get more information and to find help.";
		break;

	case WAIT_FOR_PLATFORM_ERROR:
		errMsg
				= "[BOOT] Read/Write sync packet 'DOWNLOAD' from/to target's bootloader failed!";
		tipMsg
				= "\n1.Please check if the COM cable connection is good.\n"
					"2.Please check if the bootloader(xldr&eboot / uboot)is correct.\n"
					"3.Maybe bootloader's problem. \n"
					"Please catch target bootloader's log to get more information and to find help.";
		break;

	case OPEN_USB_PORT_ERROR:
		errMsg = "[USB] Open USB port failed!";
		tipMsg = "\n1.Please check if the USB cable connection is good.\n"
			"2.Please check if the bootloader(xldr&eboot / uboot)is correct.";
		break;

	case USB_PORT_READ_FILE_ERROR:
		errMsg = "[USB] Read data from USB port failed!";
		break;

	case USB_PORT_READ_FILE_TIMEOUT_ERROR:
		errMsg = "[USB] Read size request from target via USB port timeout!";
		tipMsg
				= "\n1. Maybe bootloader's problem. \n"
					"Please catch target bootloader's log to get more information and to find help.";
		break;

	case USB_PORT_WRITE_FILE_ERROR:
		errMsg = "[USB] Write data to USB port failed!";
		break;

	case OPEN_FLASH_BIN_FILE_ERROR:
		errMsg = "[Flash.bin] Open flash.bin file failed! ";
		break;

	case READ_FLASH_BIN_FILE_ERROR:
		errMsg = "[Flash.bin] Read flash.bin file failed! ";
		break;

	case NOT_FLASH_INFO_PKT_ERROR:
		errMsg = "[Android] Read DM_FLASH_INFO_PACKET failed! ";
		break;

	case OPEN_IMAGE_FILE_ERROR:
		errMsg = "[Android] Open image file failed! ";
		break;

	case GET_IMAGE_FILE_SIZE_ERROR:
		errMsg = "[Android] Get size of image file on PC failed! ";
		break;

	case IMAGE_FILE_PATH_IS_NULL_ERROR:
		errMsg = "[Android] Path of image file is NULL! ";
		break;

	case READ_IMAGE_FILE_ERROR:
		errMsg = "[Android] Read image file on PC failed! ";
		break;

	case WRITE_IMAGE_FILE_ERROR:
		errMsg = "[Android] Send image file via usb failed! ";
		tipMsg = 
			"1. USB cable is not connected well.\n"
			"2. Lack of battery power for your target.\n"
			"3. There is a leakage of usb hub if you are using a usb hub.";
		break;

	case SEND_IMAGE_FILE_ERROR:
		errMsg = "[Android] Received check sum packet is DM_ERROR_PKT_PATN ! ";
		break;

	case UNKNOWN_SEND_IMAGE_CHECK_PACKET_ERROR:
		errMsg = "[Android] Received check sum packet is unkonwn ! ";
		break;

	case ANDROID_VERIFY_FAIL_ERROR:
		errMsg = "[Android] Verify auth file failed !";
		tipMsg = "1. Please check your auth file.";
		break;

	case INFORM_IMAGE_PACKET_ERROR:
		errMsg = "[Android] Image info packet error!";
		break;
	case TARGET_INVALID_TABLE:
        errMsg = "[Android] Partition size changed!";
        tipMsg = "Partial images download error.\n"
                 "The following partitions must be down FULL downloaded all together.";
        break;
        
	case TARGET_SPACE_NOT_FOUND:
        errMsg = "[Android] Partition size changed!";
        tipMsg = "No place to write down partiton table. Please format and try again.";
        break;

	case USB_PORT_READ_FILE_LEN_ERROR:
	    errMsg = "[Android] USB Port read response length error!";
	    tipMsg = "The response length read from USB port is not as expected.\n"
	             "Please eboot_dll.log and UART4 log for help.";
        break;
    
	case SET_LOCK_RESPONSE_ERROR:
		errMsg = "[Android Image Lock] Image Lock error!";
		tipMsg = "The Android images have been locked before, and could be locked only ONCE!";
		break;
	
	default:
		break;
	}

	return (prefix + "\n\n" + errMsg + "\n\n[HINT]:\n" + tipMsg);
}

string ErrorLookup::GPSErrorMessage(WRAPPER_RETURN ret) {
	string prefix, errMsg, tipMsg;

	if (ret == -1) {
		prefix.append(" GPS MESSAGE : ( UI )\n\n");
	} else {
		prefix.append(" GPS ERROR : ( "). append(NumberToString(ret)).append(
				") )\n\n");
	}
	switch (ret) {

	//	case ERROR_WRONG_PARAM: break;
	//	case ERROR_DLL_NOT_LOAD: break;
	//	case ERROR_FUNC_INTERNAL_LOGIC: break;
	//	case ERROR_SOMEWHERE_COMPLICATE_LOGIC: break;
	//	case ERROR_SOMEWHERE_NONEXPECTED:  break;

	case ERROR_FAIL_TO_LOAD_DLL:
		errMsg = "[GPS FW] Dynamic-Load GPS DLL fails!";
		break;

	case ERROR_FAIL_TO_GETPROCADDRESS:
		errMsg = "[GPS FW] Dynamic-Link GPS DLL fails!";
		break;

	case ERROR_FAIL_TO_CREATE_IMAGEOBJ:
		errMsg = "[GPS FW] Create DL Handle fails!";
		break;

	case ERROR_FAIL_TO_CREATE_DAOBJ:
		errMsg = "[GPS FW] Create DA Handle fails!";
		break;

	case ERROR_FAIL_TO_CREATE_RBOBJ:
		errMsg = "[GPS FW] Create RB Handle fails!";
		break;

	case ERROR_FAIL_TO_DESTROY_IMAGEOBJ:
		errMsg = "[GPS FW] Destroy DL Object fails!";
		break;

	case ERROR_FAIL_TO_DESTROY_DAOBJ:
		errMsg = "[GPS FW] Destroy DA Object fails!";
		break;

	case ERROR_FAIL_TO_DESTROY_RBOBJ:
		errMsg = "[GPS FW] Destroy RB Object fails!";
		break;

		//	case ERROR_FAIL_TO_SET_DA_STARTADDR:break;
		//	case ERROR_SCAT_INCORRECT_FORMAT:break;
		//	case ERROR_SCAT_OFFSET_IS_NOT_WORD_ALIG:break;
		//	case ERROR_SCAT_ADDR_IS_NOT_WORD_ALIGN:break;
		//	case ERROR_SCAT_ADDR_IS_NOT_ASCENDING_ORDER: break;
		//	case ERROR_SCAT_FAIL_GET_COUNT:break;
		//	case ERROR_SCAT_FAIL_GET_INFO:break;
		//	case ERROR_SCAT_FAIL_SETATTR:break;

	case ERROR_DL_FW_INVALID_FORMAT:
		errMsg = "[GPS FW] You select an invalid format GPS FW!\r\n"
			"Please select a correct GPS FW!";
		break;

		//	case ERROR_FAIL_TO_SET_RB:break;
		//	case ERROR_RB_GET_COUNT:break;
		//	case ERROR_RB_FAIL_SETATTR:break;
		//	case ERROR_FAIL_TO_SETPACKETLENGTH:break;
		//	case ERROR_BOOT_STOP:break;
		//	case ERROR_CALLBACK:break;

	case ERROR_FAIL_TO_OPEN_COMPORT:
		errMsg = "[GPS FW] Cannot open COM PORT!";
		break;

		//	case ERROR_FAIL_TO_SET_DLBLOCK:break;

	case ERROR_FAIL_TO_DOWNLOAD_DA:
		errMsg = "[GPS FW] Download GPS Loader fails!\n\n"
			"Possible reasons:\n"
			"1. There doesn't exit GPS Module.\n"
			"2. GPIO_GPS_POWER_ON_PIN may be incorrectly defined!\n"
			"3. DL Cable is unstable, please try again.";
		break;

	case ERROR_FAIL_TO_FLASHDOWNLOAD:
		errMsg = "[GPS FW] Download GPS FW fails!\n\n"
			"Possible reasons:\n"
			"1. There doesn't exit GPS Module.\n"
			"2. GPIO_GPS_POWER_ON_PIN may be incorrectly defined!\n"
			"3. DL Cable is unstable, please try again.";
		break;

	case ERROR_FAIL_TO_FLASHREADBACK:
		errMsg = "[GPS FW] Readback GPS FW fails!\n\n"
			"Possible reasons:\n"
			"1. There doesn't exit GPS Module.\n"
			"2. GPIO_GPS_POWER_ON_PIN may be incorrectly defined!\n"
			"3. DL Cable is unstable, please try again.";
		break;

	case ERROR_FAIL_TO_OPEN_DEBUG_LOG:
		errMsg = "[GPS FW] Open Debug Log fails!";
		break;

	case ERROR_FAIL_TO_CLOSE_DEBUG_LOG:
		errMsg = "[GPS FW] Close Debug Log fails!";
		break;

	default:
		break;
	}

	return (prefix + "\n\n" + errMsg + "\n[HINT]:\n" + tipMsg);
}

string ErrorLookup::FlashToolErrorMessage(FLASH_TOOL_RESULT ret) {
	string prefix, errMsg, tipMsg;

	if (ret == -1) {
		prefix.append("SP FLASH TOOL ERROR MESSAGE : ( UI )\n\n");
	} else {
		prefix.append(" SP FLASH TOOL ERROR : ( ") .append(NumberToString(ret)).append(
				" )");
	}
	switch (ret) {
		case FT_EXCEPTION:
			errMsg = "[SP Flash Tool] Common Error!";
			tipMsg = "SP Flash Tool common error.";
			break;
        //USB CATEGORY
		case FT_FIND_USB_ERROR:
			errMsg = "[Android USB] Can not find USB port !";
			tipMsg = "\n1. Lack of battery power for your target.\n"
				"2. Hardware problem of your cable.\n"
				"3. There is a leakage of usb hub if you are using a usb hub.\n"
				"4. You do not install usb driver for Android download yet.\n"
				"Please check above items or catch SP Flash Tool logs and UART4 log to find help.";
			break;

 		case FT_FIND_GADGET_USB_ERROR:
			errMsg = "[Android USB] Can not find Gadget Serial USB port !";
			tipMsg = "\n1. Lack of battery power for your target.\n"
				"2. Hardware problem of your cable.\n"
				"3. There is a leakage of usb hub if you are using a usb hub.\n"
				"4. You do not install Gadget Serial USB driver for USB META yet.\n"
				"Please check above items or catch UART4 log to find help.";

         //PLATFORM CATEGORY
		case FT_DL_PLATFORM_ERROR:
			errMsg = "[Platform Error] The load and target are inconsistent!\n";
			tipMsg = "The load to be downloadeded is for " + g_platform_info.getLoadPlatformName()  +";\n"
					 "The target platform is " + g_platform_info.getTargetPlatformName() + ".\n"
			         "Please select a correct load according to the target to download.";
			break;

	    //FIRMWARE UPGRADE
		case FT_UPGRADE_FOLDER_OVERLAPPED:
			errMsg = "[Android Firmware Upgrade] Backup folder will be overlapped!";
			tipMsg = "The Backup destination folder exists already!"
				"Please move existing data of this folder to another place,"
				"then delete this folder before executing backup!";
			break;

		case FT_UPGRADE_FOLDER_NOT_EXSIT:
            errMsg = "[Android Firmware Upgrade] The restore folder does not exist!";
			tipMsg = "The restore folder is not found under \" Tool folder\\BackupNvram \" "
			    "Please move the nvram data folder under the location above, and try again.";
			break;

		case FT_UPGRADE_DIR_CREATE_FAIL:
            errMsg = "[Android Firmware Upgrade] Create backup directory fails!";
			tipMsg = "The backcup folder could not be created under \" Tool folder\\BackupNvram \" ";
			break;

		case FT_UPGRADE_FILE_CORRUPTED:
			errMsg = "[Android Firmware Upgrade] Backup file will be overlapped!";
			tipMsg = "The Backup nvram file exists already!"
				"Please move existing data of this folder to another place,"
				"then delete this folder before executing backup!";
			break;

		case FT_UPGRADE_FILE_NOT_EXSIT:
			errMsg = "[Android Firmware Upgrade] The restore file does not exist!";
			tipMsg = "The nvram calibration file to be restored is not found under \" Tool folder\\BackupNvram \\chip id \" \n"
				"Please move the nvram calibration data under the location above, and try again.";
			break;

		case FT_UPGRADE_BACKUP_ROM_NOT_EXSIT:
			errMsg = "[Android Firmware Upgrade] The restore rom image does not exist!";
			tipMsg = "The restore rom image is not found in scatter file!\n"
				"Please make sure the content of scatter file is not modified!";
			break;

		case FT_OTP_FILE_NOT_WORD_ALIGN:
			errMsg = "[Flash Tool OTP] Load OTP file fail!";
			tipMsg = "The length of OTP file is not WORD align!\n"
				"Please modify it to be WORD aligned!";
			break;

		case FT_UPGRADE_LAYOUT_CHANGED:
			 errMsg = "[Android Firmware Upgrade ] Layout has been changed!" ;
			 tipMsg = "If you want to keep FAT data, please make sure the layout is not changed!";
			 break;

	       case FT_DOWNLOAD_LAYOUT_CHANGED:
		   	 errMsg = "[Android Download ] PMT is ready and Layout has been changed!";
			 tipMsg = "Please use FIRMWARE UPGRADE instead of download to avoid important data lost";
			 break;

              case FT_FILE_FOLDER_IS_NOT_EXIST:
			 errMsg = "The file folder is not exist!";
			 tipMsg ="Please check if the path is correct." ;
			 break;

	       case FT_FILE_IS_NOT_EXIT:
		   	errMsg = "The file is not exist!";
			tipMsg = "Please check if the path is correct.";
			break;

		case FT_CHECKSUM_NOT_MATCH:
		   	errMsg = "Checksum for the image file is not equal to the value in config file.";
			tipMsg = "Please check if the image file is completed.";
			break;	

		case FT_CREATE_FILE_FAIL:
			errMsg = "Create file fail!";
			break;
		case FT_STORAGE_ERROR:
			errMsg = "[Storage Error] The load and target are inconsistent!\n";
			tipMsg = "The load to be downloadeded is for " + g_platform_info.getFlashToolStorageConfig().GetStorageName() + ".\n"
					 "The target storage is " + g_platform_info.getTargetStorageName()+ ".\n"
			         "Please select a correct load according to the target.";
			break;
		case FT_SCI_DOWNLOAD_LAYOUT_CHANGE:
			errMsg = "[SCI Download]Paritial download when layout changed!";
		      tipMsg = "Please download completed load first if the layout changed!" ;
                   break;
		case FT_UPGRADE_GET_PMT_FAIL:
			errMsg = "No valid Partition Management Table(PMT) for storage device!";
		      tipMsg = "Please make sure there is a correct load in the target.\n"
			"\"Firmware Upgrade\" could not be executed without PMT!\n"
			"Please \"Download\" ONLY first to create PMT on the target!";
		break;
        	case FT_UPGRADE_BACKUP_SIZE_CHANGE:
			errMsg = "Backup partitions size has been changed!";
		      tipMsg = "Please \"Format Whole Flash\" and \"Download\".\n"
			"\"Firmware Upgrade\" could not be executed if size of backup partitions changed!\n";
		break;
             case FT_UPGRADE_NOT_SUPPORT_ROM_TYPE:
                   errMsg = "ROM type for the backup region is not supported by firmware upgrade.\n";
                   tipMsg = "Please check rom type in the scatter file. \n"
                    "Only \"YAFFS_IMG\" and \"NORMAL_ROM\" are supported. \n";
             break;
         default:
			break;
	}

	return (prefix + "\n\n" + errMsg + "\n[HINT]:\n" + tipMsg);
}

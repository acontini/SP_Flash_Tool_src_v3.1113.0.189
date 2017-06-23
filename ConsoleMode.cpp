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

#include <atlbase.h>
#include <exception>
#include <iostream>
#include <string> 

#include "Config.h"
#include "Command.h"
#include "CommandLineArguments.h"
#include "Logger.h"
#include "Utility.h"
#include "eboot\interface.h"
#include "meta.h"
#include "WMMETA_Wrapper.h"
#include "updater.h"
#include "FileUtils.h"

namespace ConsoleMode
{
    int Run(const std::string &commandLine)
    {
        const DWORD parentProcessID = GetParentProcessId();
        Logger::DebugOn();

        if (parentProcessID == 0)
        {
            Logger::GetLogger()<<Logger::Error<<endl
                <<"[console mode fail] return 1"<<endl;
            return 1;
        }

		if (!AttachConsole(parentProcessID))
		{
		       Logger::GetLogger()<<Logger::Error<<endl
                          <<"[console mode fail] return 2, process ID: "<<parentProcessID
                          <<endl;
			return 2;
		}
         
        //check single instance for Console Mode
        CheckSingleInstanceOfFlashTool(true);
        Logger::DebugOff();

        try
        {
            USES_CONVERSION;
            const CommandLineArguments commandLineArguments(
                                            A2CW(commandLine.c_str()));
            META_Init(NULL);
			//Enable console logs info
            Logger::DebugOn();
            Logger::GetLogger().SetBaseLevel(commandLineArguments.GetLoggingLevel());

            const Config config(commandLineArguments);
            config.Dump();

			if( config.GetGeneralSetting()->IsLogsEnabled() ){
				//Set Logs On
				FileUtils::DebugLogsOn();
			}

            if (!config.CreateCommand()->Execute())
            {
				if( config.GetGeneralSetting()->IsLogsEnabled() ){
					//Set Logs Off
					Logger::GetLogger()<<Logger::Info<<endl
						<<"[Logs Info]"<<endl
						<<"Please find SP Flash Tool logs under:"<<endl
						<<Logger::GetSPFlashToolLogFolder().c_str()<<endl;
					FileUtils::DebugLogsOff();
				}
                
                META_Deinit();
                return 3;
            }

            META_Deinit();
        }
        catch (std::exception &ex)
        {
        	LOGE(ex.what());
             LOGE("return 4");
			FileUtils::DebugLogsOff();
            return 4;
        }
        catch (Exception &ex)
        {
        	LOGE(ex.Message.c_str());
             LOGE("return 5");
			FileUtils::DebugLogsOff();
        	return 5;
        }

		//Set Logs Off
		FileUtils::DebugLogsOff();
        return 0;
    }
}

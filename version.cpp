#include "version.h"

#include <windows.h>
#include <stdio.h>
#include "Utility.h"

using std::string;


//************** PLEASE DO NOT MODIFY THE NAMES *******************

static const bool          CUSTOMER_VER    = true;
static const bool DEFAULT_ENABLE_LOGS = true;

static const unsigned int  MAJOR_VER        = 3;
static const unsigned int  MINOR_VER        = 1113;
static const unsigned int  BUILD_NUM        = 0;

static const unsigned int  BUILD_SN        = 0;

static const unsigned int  REVISION_NUM     = 189;
static const char* const   BUILD_DATE       = "2011/02/18 16:10";
static const char* const   COMMENTS         = "N/A";

static const char* const   APP_NAME         = "SP Flash Tool";
static const char* const   PROC_NAME        = "flash_tool.exe";

//*****************************************************************

bool ToolInfo::IsCustomerVer(){
    return CUSTOMER_VER;
}

bool ToolInfo::IsDefaultEnableLogs() {
	return DEFAULT_ENABLE_LOGS;
}

std::string ToolInfo::ToolName() {
    char toolName[256] = { 0 };
    sprintf(toolName, "%s V%d.%d.%d.sn%d", APP_NAME, MAJOR_VER, MINOR_VER,
		    BUILD_NUM, BUILD_SN);
    return std::string(toolName);
}

std::string ToolInfo::BuildInfo() {
    return std::string(BUILD_DATE).append(" (r")
        .append(NumberToString(REVISION_NUM)).append(")");
}

std::string ToolInfo::Comments() {
    return std::string(COMMENTS);
}

std::string ToolInfo::LoadPath() {
    char cLoadPath[_MAX_PATH] = { 0 };
    GetModuleFileName(NULL, cLoadPath, sizeof(cLoadPath));
    return std::string(cLoadPath);
}

std::string ToolInfo::ToString() {
    return std::string(
	    "==================================================================================================================================\n")
	    .append(ToolName()).append(" runtime trace is ON.\n") .append(
        "Build: ").append(BuildInfo()).append("\n").append(
        "Comment: ").append(COMMENTS).append("\n").append(
	    "Load Path:  ").append(LoadPath()) .append(
	    "\n==================================================================================================================================\n");
}

std::string ToolInfo::VersionNum(){
    char ver[20] = { 0 };
    sprintf(ver, "%d.%d.%d.sn%d", MAJOR_VER, MINOR_VER, BUILD_NUM, BUILD_SN);
    return std::string(ver);
}

/*
 * FileUtils.cpp
 *
 *  Created on: Dec 30, 2010
 *      Author: MTK81019
 */
#include "FileUtils.h"

#include <windows.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <iomanip>
#include <io.h>
#include "Utility.h"
//Log files
#include "Logger.h"
#include "brom.h"
#include "eboot\interface.h"
#include "meta.h"
#include "WMMETA_Wrapper.h"

#ifdef __BORLANDC__
#pragma warn -8004
#endif

namespace FileUtils{
    using std::string;
	const std::string kBackupFolder("BackupData");
}

bool FileUtils::CreateFiles(std::string fileName)
{
   FILE *fpOut=fopen(fileName.c_str(), "wb+");

   if(fpOut == NULL) return false;

   fclose(fpOut);

   return true;
}

std::string FileUtils::GetTimestamp(){
	char infoTimestamp[_MAX_FNAME] = { 0 };
	SYSTEMTIME timestamp;
	GetLocalTime(&timestamp);
	sprintf(infoTimestamp,
			"%02d-%02d-%02d-%02d-%02d-%02d",
			timestamp.wMonth, timestamp.wDay, timestamp.wYear, timestamp.wHour,
			timestamp.wMinute, timestamp.wSecond);
	return string(infoTimestamp);
}

E_CHECK_DIR_STATUS FileUtils::CheckDirectory(const std::string &dir, bool createIfNotExist) {
    if(FileUtils::IsDirectoryExist(dir)){
		LOG("%s(): the dir(%s) already exists.", __FUNC__, dir);
            return DIR_EXIST;
    }

    if(!createIfNotExist){
		LOG("%s(): the dir(%s) does not exist.", __FUNC__, dir);
        return DIR_NOT_EXIST;
    }

		WCHAR wszAndroidPath[256];
		MultiByteToWideChar(CP_ACP, 0, dir.c_str(), -1, wszAndroidPath,
				sizeof(wszAndroidPath) / sizeof(wszAndroidPath[0]));
		if (::CreateDirectoryW(wszAndroidPath, NULL) == 0) {
		LOG("%s(): create the dir(%s) failed.", __FUNC__, dir);
			return CREATE_DIR_FAIL; //create directory fail
		} else {
		LOG("%s(): create the dir(%s) succeed.", __FUNC__, dir);
		    return CREATE_DIR_SUCCESS; //create directory successfully
		}
	}

/**
 * Check whether the directory exists
 *
 * @param directory to be checked
 *
 * @return whether the directory exists
 */
bool FileUtils::IsDirectoryExist(const  string & dir) {
    struct stat fileInfo;
    int ret = stat(dir.c_str(), &fileInfo);
    return ( ret == 0 && S_ISDIR(fileInfo.st_mode));
}

/**
 * Check whether the file exists
 *
 * @param file to be checked
 *
 * @return whether the file exists
 */
bool FileUtils::IsFileExist(const  string & file) {
    struct stat fileInfo;
    int ret = stat(file.c_str(), &fileInfo);
    return ( ret == 0 && S_ISREG(fileInfo.st_mode));
}

/**
 * Delete a directory
 *
 * @param directory to be deleted
 *
 * @return whether the directory is deleted
 */
bool FileUtils::DeleteDirectory(const std::string &dir) {
	std::vector<std::string> files;
	bool isFindFiles = FileUtils::SearchFile(dir.c_str(), files, "");
    string tmpFile;
	if(isFindFiles) {
	    for(std::vector<std::string>::const_iterator it = files.begin();
		        it != files.end(); ++it) {
                tmpFile = dir + "\\" + *it;
		        DeleteFile(tmpFile.c_str());
	    }
    }
	    return RemoveDirectory(dir.c_str());
	}

bool FileUtils::DeleteDummyFile(const std::string &file_name)
{
      return DeleteFile(file_name.c_str());
}

std::string FileUtils::GetAppDirectory() {
	char buf[MAX_PATH];
	GetModuleFileName(NULL, buf, MAX_PATH);
	std::string currentPath(buf);
	return currentPath.substr(0, currentPath.rfind('\\'));
}

#if 0    //deprecated function
E_CHECK_DIR_STATUS FileUtils::CheckDirByCOMPort(int port, std::string &dir, 
                                                bool createIfNotExist){
    string parentDir = FileUtils::GetAppDirectory()+"\\BackupNvram";
    E_CHECK_DIR_STATUS status = FileUtils::CheckDirectory(parentDir,createIfNotExist);
    if(status == DIR_NOT_EXIST || status == CREATE_DIR_FAIL){
        return status;
    }
    dir = parentDir + "\\" + NumberToString(port);
    return FileUtils::CheckDirectory(dir,createIfNotExist);
}

E_CHECK_DIR_STATUS FileUtils::CheckDirByChipID(unsigned char* chipId, unsigned int length, 
                                               std::string &dir, bool createIfNotExist){
    std::ostringstream oss;
    oss<<std::hex;
    for(unsigned int i=0;i<length;++i){
        oss<<std::setfill('0')<<std::setw(2)<<static_cast<unsigned int>(chipId[i]);
    }
    string chipName = oss.str();

    string parentDir = FileUtils::GetAppDirectory()+"\\BackupNvram";
    E_CHECK_DIR_STATUS status = FileUtils::CheckDirectory(parentDir, createIfNotExist);
    if(status == DIR_NOT_EXIST || status == CREATE_DIR_FAIL){
        return status;
    }
    dir = parentDir + "\\" + chipName;
    return FileUtils::CheckDirectory(dir, createIfNotExist);
}
#endif

bool FileUtils::MakeParentBackupDir(const string& folder)
{
	E_CHECK_DIR_STATUS backup_dir_status = 
		FileUtils::CheckDirectory(FileUtils::GetAppDirectory()+"\\" + folder, true);
	return ( DIR_EXIST ==  backup_dir_status ||
		CREATE_DIR_SUCCESS == backup_dir_status ) 
		? true : false;
}

std::string FileUtils::ComposeDirNameByTimeStamp(const string &parentDir, const string &prefix)
{
     std::string dirName = parentDir + "\\" +prefix + GetTimestamp();

     return dirName;	 
} 

std::string FileUtils::ComposeDirNameByChipID(const unsigned char* chipId, const unsigned int length, const string& folder)
{
    std::ostringstream oss;
    oss<<std::hex;
    for(unsigned int i=0;i<length;++i){
        oss<<std::setfill('0')<<std::setw(2)<<static_cast<unsigned int>(chipId[i]);
    }
    string chipName = oss.str();

    string dirName = FileUtils::GetAppDirectory()+ "\\" + folder + "\\" +chipName;
    LOG("%s(): folder name: %s.", __FUNC__, dirName.c_str());

    return dirName;
}


std::string FileUtils::ComposeDirNameByCOMPort(const int port, const string& folder)
{
	string dirName = FileUtils::GetAppDirectory()+ "\\" + folder + "\\" +NumberToString(port);
	LOG("%s(): folder name: %s.", __FUNC__, dirName.c_str());
	return dirName;
}




bool FileUtils::SearchFile(std::string folder, std::vector<std::string> &files,
		std::string pattern, COMPARE_METHOD compare_m, bool recursive) {
	WIN32_FIND_DATA find_data;
	HANDLE hFind;
	bool bIsDirectory;
	string file_name, file_path, search_path;
	search_path = folder + "\\*.*";

	hFind = FindFirstFile(search_path.c_str(), &find_data);

	if (hFind == INVALID_HANDLE_VALUE) {
		return false;
	}

	do {
		bIsDirectory = ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				!= 0);
		file_name = find_data.cFileName;

		if (!bIsDirectory) {
			if (compare_m == NULL) {
				if (pattern == "") {
					//add all files if no pattern defined
					files.push_back(file_name);
				} else if (pattern == file_name) {
					files.push_back(file_name);
				}
			} else {
				if (compare_m(file_name, pattern)) {
					files.push_back(file_name);
				}
			}
		} else if (recursive) {
			if ((".." != file_name) && ("." != file_name)) {
				file_path = folder + "\\";
				file_path += find_data.cFileName;
				SearchFile(file_path, files, pattern, compare_m, recursive);
			}
		}
	} while (FindNextFile(hFind, &find_data));

    FindClose(hFind);
	return true;
}

bool FileUtils::ListFiles(std::string folder, std::vector<std::string> &files){
		return FileUtils::SearchFile(folder, files, "");
}

bool FileUtils::FindFileByPrefix(std::vector<std::string> &files, const std::string prefix,  std::vector<std::string> &satisified_files)
{
      for(std::vector<std::string>::const_iterator it = files.begin();
	       it != files.end(); ++it)
     {
             if((*it).find(prefix) == 0)
             {
                  LOGD("Find object file(%s), prefix(%s)", (*it).c_str(), prefix.c_str());
		     satisified_files.push_back((*it));
		}
     }

     return (satisified_files.size() > 0);
}

/**
 * Get the size of the given file.
 *
 * @param filename a filename
 *
 * @return size of the given file
 */
unsigned int FileUtils::GetFileSize(const std::string &filename)
{
    //
    // FIXME: Should use some filesystem API instead
    //
    unsigned int size;
    std::ifstream is(filename.c_str(), std::ios::in | std::ios::binary);

    is.seekg(0, std::ios::end);
    size = is.tellg();
    is.close();

    return size;
}

/**
 * Get the content of the given file. The caller is responsible for memory
 * deallocation.
 *
 * @param filename a filename
 *
 * @return content of the given file
 */
unsigned char* FileUtils::GetFileContent(const std::string &filename)
{
    std::ifstream is(filename.c_str(), std::ios::in | std::ios::binary);
    is.seekg(0, std::ios::end);

    const unsigned int size = is.tellg();
    unsigned char *content = new unsigned char[size];

    is.seekg(0, std::ios::beg);
    is.read(content, size);
    is.close();

    return content;
}

/**
 * Set debug log file on
 *
 * @param NULL
 *
 * @return NULL
 */
void FileUtils::DebugLogsOn( void ) {
	std::string dll_log;
	Logger::SetSPFlashToolDumpFileFolder();
	Logger::DebugOff();
	Logger::DebugOn();
	dll_log = Logger::GetSPFlashToolDumpFileFolder() + "\\EBOOT_DLL.log";
	Eboot_DebugChangePath(dll_log.c_str());
	dll_log = Logger::GetSPFlashToolDumpFileFolder() + "\\BROM_DLL_V5.log";
	Brom_Debug_SetLogFilename(dll_log.c_str());
	Brom_DebugOn();
	dll_log = Logger::GetSPFlashToolDumpFileFolder() + "\\META_DLL.log";
	META_DebugOn_With_FilePath(dll_log.c_str());
	dll_log = Logger::GetSPFlashToolDumpFileFolder() + "\\SP_META_DLL.log";
	SP_META_DebugOnThePath_Wrapper(dll_log.c_str());
}

/**
 * Set debug log file on
 *
 * @param NULL
 *
 * @return NULL
 */
void FileUtils::DebugLogsOff( void ) {
	Logger::DebugOff();
	Eboot_DebugOff();
	Brom_DebugOff();
	META_DebugOff();
	WM_META_DebugOff_Wrapper();
}

bool FileUtils::ComputeCloneCheckSum(const std::string &src_file, S_CHKSUM_Arg &chksum_arg)
{
    unsigned char buffer[1024];

    FILE *file = fopen ( src_file.c_str() , "rb" );
    if (file==NULL) {
		LOG("%s(): file open failed: %s.", __FUNC__, src_file.c_str());
        return false;
    }
    chksum_arg.m_cb_rom_mem_checksum_init(chksum_arg.m_cb_rom_mem_checksum_init_arg,
		                                                     src_file.c_str());

    chksum_arg.chksum_value= 0;
    unsigned int read_size = 0;    
    static unsigned char lastPercentage = 0;	
    unsigned char percentage = 0;
    unsigned int file_len = 0;  
    unsigned int position = 0;

    file_len = filelength(fileno(file));	
	
    while(!feof(file)){
        read_size = fread(buffer, 1, 1024, file);
	
	 position = ftell(file);

	 percentage = static_cast<unsigned char>((static_cast<float> (position)/file_len)*100);
		
	 if (lastPercentage != percentage) 	
	 {
            lastPercentage = percentage;
	     chksum_arg.m_cb_rom_mem_checksum(percentage,
		                             position, read_size, chksum_arg.m_cb_rom_mem_checksum_arg);
	}	

        for(unsigned int i=0;i<read_size;i++){

             if(BOOT_STOP == *(chksum_arg.stopflag))
             {
                  LOG("%s: user press stop button.", __FUNC__);
                  return false;
		}
			
              chksum_arg.chksum_value += buffer[i];
        }
    }

    chksum_arg.m_cb_rom_mem_checksum(100, file_len, file_len, chksum_arg.m_cb_rom_mem_checksum_arg);

    LOG("%s(): check sum result(%u).", __FUNC__, chksum_arg.chksum_value);
    fclose (file);
    return true;
}       

bool FileUtils::ComputeCheckSum(const std::string &src_file, unsigned char &chksum)
{
    unsigned char buffer[1024];

    FILE *file = fopen ( src_file.c_str() , "rb" );
    if (file==NULL) {
		LOG("%s(): file open failed: %s.", __FUNC__, src_file.c_str());
        return false;
    }

    chksum = 0;
    unsigned int read_size = 0;
    while(!feof(file)){
        read_size = fread(buffer, 1, 1024, file);

        for(unsigned int i=0;i<read_size;i++){
            chksum += buffer[i];
        }
    }

	LOG("%s(): check sum result(%u).", __FUNC__, chksum);
    fclose (file);
    return true;
}


bool FileUtils::LoadCheckSum(const std::string &chksum_file, unsigned char &chksum)
{
    unsigned char buffer[2];

    FILE *file = fopen ( chksum_file.c_str() , "rb" );
    if (file==NULL) {
		LOG("%s(): file open failed: %s.", __FUNC__, chksum_file.c_str());
        return false;
    }

    unsigned int read_size = 0;
    read_size = fread(buffer, 1, 1024, file);
    if(read_size <= 0){
		LOG("%s(): read file error: %s", __FUNC__, chksum_file.c_str());
        return false;
    }

    chksum = buffer[0];

	LOG("%s(): check sum result(%u).", __FUNC__, chksum);
    fclose (file);
    return true;
}

bool FileUtils::SaveCheckSum(const std::string &chksum_file, const unsigned char chksum)
{
    unsigned char buffer[2] = {0};
    buffer[0] = chksum;

    FILE *file = fopen ( chksum_file.c_str() , "wb" );
    if (file==NULL) {
		LOG("%s(): file create/open failed: %s.", __FUNC__, chksum_file.c_str());
        return false;
    }

    fwrite (buffer , 1 , sizeof(buffer) , file );

	LOG("%s(): check sum result(%u).", __FUNC__, chksum);
    fclose (file);
    return true;
}

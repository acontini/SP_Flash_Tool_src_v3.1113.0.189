/*
 * FileUtils.h
 *
 *  Created on: Dec 30, 2010
 *      Author: MTK81019
 */

#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

#include "flashtool_api.h"

enum E_CHECK_DIR_STATUS{
    DIR_EXIST,
    DIR_NOT_EXIST,
    CREATE_DIR_SUCCESS,
    CREATE_DIR_FAIL
};


typedef struct
{
   unsigned char chksum_value; //output
   
   CALLBACK_ROM_MEM_CHECKSUM_PROGRESS_INIT m_cb_rom_mem_checksum_init;
   void * m_cb_rom_mem_checksum_init_arg;
   CALLBACK_ROM_MEM_CHECKSUM_PROGRESS m_cb_rom_mem_checksum;
   void * m_cb_rom_mem_checksum_arg; 
   int *stopflag;
}S_CHKSUM_Arg;     

namespace FileUtils {

	//Common Directory OPs
	E_CHECK_DIR_STATUS CheckDirectory(const std::string &dir, bool createIfNotExist = true);
	bool CreateFiles(std::string fileName);

    bool IsDirectoryExist(const std::string &dir);

    bool IsFileExist(const std::string &file);

    bool DeleteDirectory(const std::string &dir);
    bool DeleteDummyFile(const std::string &file_name);

    //Application related OPs
	std::string GetAppDirectory();

#if 0   //deprecated function
    //prepare backup NVRAM folder.
    E_CHECK_DIR_STATUS CheckDirByCOMPort(int port, std::string &dir, 
        bool createIfNotExist = true);

    E_CHECK_DIR_STATUS CheckDirByChipID(unsigned char* chipId, unsigned int length, std::string &dir, 
        bool createIfNotExist = true);
#endif

	//Declaration for nvram backup folder
	extern const std::string kBackupFolder;
	//Check the backup directory, if it does not exsit, create it
	bool MakeParentBackupDir(const std::string& folder = kBackupFolder);
	std::string GetTimestamp();
	std::string ComposeDirNameByTimeStamp(const std::string &parentDir, const std::string &prefix);
	std::string ComposeDirNameByChipID(const unsigned char* chipId, const unsigned int length, const std::string& folder = kBackupFolder);
    std::string ComposeDirNameByCOMPort(const int port, const std::string& folder = kBackupFolder);

	//File Search OPs
	typedef bool (*COMPARE_METHOD)(const std::string &file_name, const std::string &pattern);
	bool SearchFile(std::string folder, std::vector<std::string> &files,
			std::string pattern, COMPARE_METHOD compare_m = NULL, bool recursive =
					false);
	bool ListFiles(std::string folder, std::vector<std::string> &files);
	bool FindFileByPrefix(std::vector<std::string> &files, const std::string prefix, std::vector<std::string> &satisified_files);

	unsigned int GetFileSize(const std::string &filename);
	unsigned char* GetFileContent(const std::string &filename);

	void DebugLogsOn(void);
	void DebugLogsOff(void);

	//file checksum
	bool ComputeCheckSum(const std::string &src_file, unsigned char &chksum);
	bool ComputeCloneCheckSum(const std::string &src_file, S_CHKSUM_Arg &chksum_arg);
	bool LoadCheckSum(const std::string &chksum_file, unsigned char &chksum);
	bool SaveCheckSum(const std::string &chksum_file, const unsigned char chksum);

	class FileOpenSentry {
	public:
		FileOpenSentry(const std::string &filepath, const std::string &mode, FILE *&fp)
		        : m_fp(fp) {
			m_fp = NULL;
			if (filepath.length() == 0 || mode.length() == 0)
				return;
			m_fp = fopen(filepath.c_str(), mode.c_str());
		}
		~FileOpenSentry() {
			if (NULL != m_fp) {
				fclose(m_fp);
				m_fp = NULL;
			}
		}
	private:
		FILE *&m_fp;
	};

};

#endif /* FILEUTILS_H_ */

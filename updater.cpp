#include "updater.h"
#include "version.h"
#include "Logger.h"
#include "Utility.h"
#include "FileUtils.h"

#include <windows.h>
#include <algorithm>
#include <fstream>

const std::string AutoUpdater::ReleaseFolder(
    "\\\\glbfs14\\sw_releases\\Wireless_Global_Tools\\Tool_Release\\SP Flash Tool\\Release\\General");

const std::string AutoUpdater::UpdaterExe("Updater.exe");


AutoUpdater* AutoUpdater::instance = NULL;

static bool isUpdatePackage(const std::string &file_name, const std::string &pattern){
    return file_name.find("SP_Flash_Tool")!=std::string::npos 
        && file_name.find(".zip")!=std::string::npos;
}

__fastcall AutoUpdater::AutoUpdater() 
    : TThread(true), hasNewVersion(false), newVersion(), newVersionFolder(), observers(){
        isRunningLock = new TCriticalSection();
        SetIsRunning(false);
}


void AutoUpdater::AddObserver(const IVersionOb * ob){
    if(ob != NULL){
        observers.push_back(ob);
    }
}
void AutoUpdater::RemoveObserver(const IVersionOb * ob){
    if(ob != NULL){
        observers.remove(ob);
    }
}

void __fastcall AutoUpdater::notifyObservers(){
    for(std::list<const IVersionOb*>::const_iterator it = observers.begin(); 
        it!= observers.end(); ++it){
            (*it)->newVersionDetected(newVersion, newVersionFolder);
    }
}



void _fastcall AutoUpdater::Execute(){
    SetIsRunning(true);
    CheckUpdate();
    SetIsRunning(false);
}

void AutoUpdater::CheckUpdate(){
    std::vector<std::string> allVersions;

    getAllVersions(allVersions);
    if(allVersions.size() == 0){
        return;
    }

    std::sort(allVersions.begin(), allVersions.end());

    std::string latestVer = allVersions.back();
    
    if(latestVer.compare(ToolInfo::VersionNum())>0){
        std::vector<std::string> files;
        FileUtils::SearchFile(ReleaseFolder+"\\"+latestVer,files,"",isUpdatePackage);

        if(files.size()>0){
            hasNewVersion = true;
            newVersion = latestVer;
            newVersionFolder = ReleaseFolder+"\\"+latestVer;
            newVersionPackage = newVersionFolder+"\\"+files.front();

            Synchronize(notifyObservers);
        }
        //notifyObservers();
    }
}

void AutoUpdater::getAllVersions(std::vector<std::string> &versions){
    WIN32_FIND_DATA find_data;
	HANDLE hFind;
	bool bIsDirectory;
	std::string file_name;
    std::string search_path(ReleaseFolder+"\\*");

	hFind = FindFirstFile(search_path.c_str(), &find_data);

	if (hFind == INVALID_HANDLE_VALUE) {
        LOGE(std::string("Find File error: ").append(NumberToString(GetLastError())).c_str());
		return;
	}

	do {
		bIsDirectory = ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				!= 0);
		file_name = find_data.cFileName;

		if (bIsDirectory) {
			versions.push_back(file_name);
		}
	} while (FindNextFile(hFind, &find_data));

    FindClose(hFind);
}

bool AutoUpdater::GetIsRunning(){
    CS_Sentry cs(isRunningLock);
    return isRunning;
}

void AutoUpdater::SetIsRunning(bool running){
    CS_Sentry cs(isRunningLock);
    isRunning = running;
}

bool AutoUpdater::Start(){
    if(!GetIsRunning()){
        this->Resume();
        return true;
    }else{
        return false;
    }
}

void AutoUpdater::ExecuteUpdate(){
    if(hasNewVersion){
        Fork(UpdaterExe, newVersionPackage);
        exit(0);
    }
}


void AutoUpdater::Fork(const std::string& binary, const std::string &arg){
    //get user's temp folder
    char temp_dir[MAX_PATH] = {0};
    if(GetTempPath(MAX_PATH, temp_dir) == 0){
        LOGE("GetTempPath failed");
        return;
    }
    const std::string userTempDir(temp_dir);
    const std::string updaterFile = userTempDir+binary;

    //copy "Updater.exe" to user temp dir
    std::ifstream inputStream(binary.c_str(), std::ios::in|std::ios::binary);	
	std::ofstream outputStream(updaterFile.c_str(), std::ios::out|std::ios::binary);

    if(inputStream.is_open() && outputStream.is_open()){
        outputStream << inputStream.rdbuf();
        outputStream.close();
        inputStream.close();
    }else{
        LOGE("%s copy failed or not exist.", binary.c_str());
        return;
    }

    //converting arg's all blank spaces to '*'
    char cmd[MAX_PATH] = {0};
    for(unsigned int i=0; i<arg.size(); i++){
        char ch = arg.at(i);
        if(ch == ' '){
            cmd[i] = '*';
        }else{
            cmd[i] = ch;
        }
    }

	//starting new process
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// Start the child process.
	if (!CreateProcess(updaterFile.c_str(), // No module name (use command line)
			cmd, // Command line
			NULL, // Process handle not inheritable
			NULL, // Thread handle not inheritable
			FALSE, // Set handle inheritance to FALSE
			CREATE_NEW_CONSOLE, // Create process in a new console
			NULL, // Use parent's environment block
			NULL, // Use parent's starting directory
			&si, // Pointer to STARTUPINFO structure
			&pi) // Pointer to PROCESS_INFORMATION structure
	) {
        Logger::GetLogger().Log(Logger::Error, "CreateProcess failed (%d).\n", GetLastError());
	}
}


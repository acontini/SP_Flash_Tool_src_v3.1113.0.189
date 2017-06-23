#ifndef _UPDATER_H_
#define _UPDATER_H_

#include <Classes.hpp>
#include <SyncObjs.hpp>

#include <iostream>
#include <vector>
#include <list>

class IVersionOb{
public:
    virtual void newVersionDetected(const std::string &version, const std::string &path) = 0;
};

class AutoUpdater : public TThread{
    const static std::string ReleaseFolder; 
    const static std::string UpdaterExe;

public:
    __fastcall AutoUpdater();
    
    void AddObserver(const IVersionOb * ob);
    void RemoveObserver(const IVersionOb * ob);

    bool GetIsRunning(); //synchronized
    bool Start();

    void ExecuteUpdate(); //this will fork another update process and exit self.

protected:
    void _fastcall Execute();

private:
    void SetIsRunning(bool running); //synchronized

    void CheckUpdate();
    void getAllVersions(std::vector<std::string> &versions);
    void __fastcall notifyObservers();

    void Fork(const std::string &binary, const std::string &arg);
    
    bool hasNewVersion;
    std::string newVersion;
    std::string newVersionFolder;
    std::string newVersionPackage;

    std::list<const IVersionOb*> observers;
    
    TCriticalSection *isRunningLock;
    bool isRunning;


public:
    static AutoUpdater *Instance(){
        if(instance == NULL){
            instance = new AutoUpdater();
        }
        return instance;
    }

private:
    static AutoUpdater *instance;
};


#endif
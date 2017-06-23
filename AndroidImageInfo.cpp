/*
 * AndroidImageInfo.cpp
 *
 *  Created on: Jan 13, 2011
 *      Author: MTK81019
 */
#pragma hdrstop

#include "AndroidImageInfo.h"
#include "Flashtool_handle.h"
#include <sstream>
#include <cassert>
#include "Logger.h"


AndroidImageInfoTable& GetAndroidImageInfoTable(){
	static AndroidImageInfoTable table;
	return table;
}

AndroidImageInfoTable::AndroidImageInfoTable(){
	currentCount = 0;
};

void AndroidImageInfoTable::UpdateInfo(const string &romname, AndroidImageInfo &info) {
	/*int ImgSeq = GetImageMapRule().getImageSeq(
			static_cast<ImageType>(info.type));*/
	//TODO: refine this to avoid creating it per image loaded.
	CreateSeqMap();		
	int ImgSeq = GetImageSeq(static_cast<ImageType>(info.type));

	bool willInsert;
	int androidIndex = 0;
	list<DM_IMG_TYPE>::iterator it;
	for(it = AndroidImgTypeList.begin(); it!=AndroidImgTypeList.end(); ++it,++androidIndex){
		//int seq = GetImageMapRule().getImageSeq(static_cast<ImageType>(*it));
		int seq = GetImageSeq(static_cast<ImageType>(*it));
		if(seq == ImgSeq){
			willInsert = false;
			break;
		}else if(ImgSeq < seq){
			willInsert = true;
			break;
		}
	}


	if(AndroidImgTypeList.empty() || it == AndroidImgTypeList.end()){
		//for empty or last, just push at the list end
		AndroidImgTypeList.push_back(info.type);
		info.androidFileIndex = androidIndex;
	info.isValid = true;

	infoTable.insert(pair<string, AndroidImageInfo> (romname, info));
	romIndexNameMap.insert(pair<int, string> (info.romIndex, romname));
	AndroidImgIndexNameMap.insert(pair<int, string> (info.androidFileIndex,
			romname));
		currentCount++;

	}else if(willInsert){
		//for middle element, insert and update others' android index
		AndroidImgTypeList.insert(it,info.type);

		//update latter images' android index
		for(int i = currentCount-1; i>=androidIndex; --i){
			string imgName = AndroidImgIndexNameMap[i];
			AndroidImageInfo& infoRef = infoTable[imgName];
			infoRef.androidFileIndex ++;
			AndroidImgIndexNameMap.erase(i);
			AndroidImgIndexNameMap.insert(pair<int,string>(i+1,imgName));
}
		info.androidFileIndex = androidIndex;
		info.isValid = true;

		infoTable.insert(pair<string, AndroidImageInfo> (romname, info));
		romIndexNameMap.insert(pair<int, string> (info.romIndex, romname));
		AndroidImgIndexNameMap.insert(pair<int, string> (info.androidFileIndex,
				romname));
		currentCount++;

	}else{
		// for already exists element, just update it
		AndroidImageInfo& existedInfo = infoTable[AndroidImgIndexNameMap[androidIndex]];
		existedInfo.filePath = info.filePath;
		existedInfo.isPatch = info.isPatch;
		existedInfo.romIndex = info.romIndex;
		existedInfo.romName = info.romName;
		existedInfo.type = info.type;
		existedInfo.format = info.format;
		existedInfo.isValid = true;
	}
}

AndroidImageInfo& AndroidImageInfoTable::GetImageByRomIndex(int romIndex){
	map<int, string>::const_iterator it = romIndexNameMap.find(romIndex);
	if(it != romIndexNameMap.end()){
		return infoTable[it->second];
	}else{
		return infoTable[""]; //return an invalid info
	}
}

AndroidImageInfo& AndroidImageInfoTable::GetImageByAndroidFileIndex(int androidFileIndex){
	map<int, string>::const_iterator it = AndroidImgIndexNameMap.find(androidFileIndex);
	if(it != AndroidImgIndexNameMap.end()){
		return infoTable[it->second];
	}else{
		return infoTable[""]; //return an invalid info
	}
}

void AndroidImageInfoTable::Reset() {
	infoTable.clear();
	romIndexNameMap.clear();
	AndroidImgIndexNameMap.clear();
	AndroidImgTypeList.clear();
	currentCount = 0;
}

string AndroidImageInfoTable::Dump() const{
	std::ostringstream oss;
	oss<<"\nCurrent Android Image Count = "<<currentCount<<std::endl;
	oss<<"\nAI\t\tRI\t\tRomName\t\t\tType\tPatch\tValid\tIsDownload\tFilePath"<<std::endl;
	for(int index = 0; index < currentCount; ++index){
		map<int, string>::const_iterator it =
				AndroidImgIndexNameMap.find(index);
		if(it != AndroidImgIndexNameMap.end()){
			map<string, AndroidImageInfo>::const_iterator imageIt =
					infoTable.find(it->second);
			if(imageIt != infoTable.end()){
				oss<<imageIt->second.androidFileIndex<<"\t\t"
					<<imageIt->second.romIndex<<"\t\t"
					<<imageIt->second.romName<<"\t\t\t"
					<<imageIt->second.type<<"\t\t"
					<<imageIt->second.isPatch<<"\t\t"
					<<imageIt->second.isValid<<"\t\t"
					<<imageIt->second.filePath<<std::endl;
	}
		}
	}
	return oss.str();
}
//Workaround for image sequence change request
bool AndroidImageInfoTable::CreateSeqMap(void)
{
    assert(NULL != g_pCurNode->m_dl_handle);
    DL_HANDLE_T &dl_handle = g_pCurNode->m_dl_handle;
    int seqCount = 0;
    unsigned short  romCount = 0;
    ROM_INFO romInfo;

    if (!DL_GetCount(dl_handle, &romCount)) {
        sequenceMap.clear();
        for (int i = 0; i < romCount; i++) {
            if(!DL_Rom_GetInfo(dl_handle, i, &romInfo)) {
                if(romInfo.item_is_visable) {
                    seqCount++;
                    ImageType imgType = GetImageMapRule().queryType(romInfo.name);
                    sequenceMap.insert(pair<ImageType,int>(imgType, seqCount));
                    //Logger::GetLogger().Log(Logger::Debug, "CreateSeqMap: ROM = %s, Sequence = %d",romInfo.name, seqCount);
                }
            }
        }
    } else {
        return false;
    }

    return true;
}

/*
 * AndroidImageInfo.h
 *
 *  Created on: Dec 9, 2010
 *      Author: MTK81019
 */

#ifndef ANDROIDIMAGEINFO_H_
#define ANDROIDIMAGEINFO_H_

#include<string>
#include<map>
#include<list>

using std::string;
using std::map;
using std::pair;
using std::list;

#include "GlobalData.h"
#include "ImageMapRule.h"

class AndroidImageInfo{
public:
	int androidFileIndex;
	int romIndex;
	DM_IMG_TYPE type;
	DM_IMG_FORMAT format;
    string romName;
	string filePath;
	bool isPatch;
	bool isValid; //**TIPS: the operator[] on map will always return a Object,
	//even if the key-mapped one doesn't exist, it will be auto created & inserted, and returned.
	//So the field "isValid" are used to distinguish such situation**//

	AndroidImageInfo(){
		androidFileIndex = -1;
		romIndex = -1;
		type = DM_IMG_TYPE_UNKNOWN;
		format = DM_IMG_FORMAT_UNKNOWN;
		isPatch = false;
		isValid = false;
	}
};

class AndroidImageInfoTable{
public:
	const AndroidImageInfo& operator[](const string &romname){
		return infoTable[romname];
	}

	int ImageNum() const{
		return currentCount;
	}

	AndroidImageInfo& GetImageByRomIndex(int romIndex);
    AndroidImageInfo& GetImageByAndroidFileIndex(int androidFileIndex);
	void UpdateInfo(const string &romname, AndroidImageInfo &info);
	void Reset();
	string Dump() const;
private:
	AndroidImageInfoTable();
    bool CreateSeqMap(void);
    int GetImageSeq(ImageType type) { return sequenceMap[type]; }

	map<string, AndroidImageInfo> infoTable; //may have invalid info, with isValid=false
	map<int, string> romIndexNameMap;        //all valid
    map<int, string> AndroidImgIndexNameMap; //all valid

    list<DM_IMG_TYPE> AndroidImgTypeList;    //sequenced type list,
                                             //used for sorting android image index
                                             //when inserting new ones
    map<ImageType,int> sequenceMap;
    int sequence;
	int currentCount;

	friend AndroidImageInfoTable& GetAndroidImageInfoTable();
};

AndroidImageInfoTable& GetAndroidImageInfoTable();

#endif /* ANDROIDIMAGEINFO_H_ */

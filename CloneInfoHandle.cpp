#include "CloneInfoHandle.h"

#include "XMLDocument.h"
#include "XMLNode.h"
#include "Logger.h"
#include "FileUtils.h"

#include <atlbase.h>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>

using XML::Document;
using XML::Node;
using std::hex;
using std::setfill;
using std::setw;

CloneInfoItem::CloneInfoItem()
: chksum_value_(0)
{}

CloneInfoItem::~CloneInfoItem()
{}

void CloneInfoItem::LoadXML(const XML::Node &node)
{
       USES_CONVERSION;
	Node childNode = node;
	const unsigned int nodeNum = node.GetNumChildNodes();

	std::wstring addr_str;
	std::wstring len_str;

	partition_name_ = W2CA(node.GetAttribute(L"name").c_str());
        addr_str = node.GetAttribute(L"start_addr").c_str();
	len_str = node.GetAttribute(L"length").c_str();

        //convert wstring to unsigned long long
        ::swscanf(addr_str.c_str(), L"%I64x", &partition_info_.start_addr);
        ::swscanf(len_str.c_str(), L"%I64x", &partition_info_.length);

	for(unsigned int childIndex = 0; childIndex < nodeNum; ++childIndex)
	{
              childNode = node.GetChildNode(childIndex);
		if(childNode.GetName() == L"file_path")	 
		{
                     image_path_ = W2CA(childNode.GetText().c_str());
		}
		else if(childNode.GetName() == L"chksum")
		{
                     std::string chksumVStr;
                     chksum_value_= wcstoul(childNode.GetText().c_str(), 0, 16);
		}
		else
		{
                      LOGE("%s: Invalid clone info item type(%s)!", __FUNC__, W2CA(childNode.GetText().c_str()));
		}
	}
}

void CloneInfoItem::SaveXML(XML::Node &node) const
{
       USES_CONVERSION;
       Node rootNode(node.AppendChildNode(L"partition"));
       //add attribute
       rootNode.SetAttribute(L"name", A2CW(partition_name_.c_str()));
	   
	std::wostringstream start_addr;
	start_addr<<hex<<"0x"
		<<setfill('0')<<setw(16)
		<<partition_info_.start_addr;
	rootNode.SetAttribute(L"start_addr", start_addr.str());

	std::wostringstream length;
	length<<hex<<"0x"
	     <<setfill('0')<<setw(16)
	     <<partition_info_.length;
	rootNode.SetAttribute(L"length", length.str());

	//add child node
	rootNode.AppendChildNode(L"file_path", A2CW(image_path_.c_str()));
	
	std::wostringstream chksum;
        chksum << hex << "0x"
                << setfill('0') << setw(8)
                << (unsigned int)chksum_value_;
	 LOGD("chksum(%s)", chksum.str().c_str());
        rootNode.AppendChildNode(L"chksum", chksum.str());
}

CloneInfoHandle::CloneInfoHandle()
{
       
}
CloneInfoHandle::CloneInfoHandle(const std::string & fileName)
{
       USES_CONVERSION;
       LoadFile(A2CW(fileName.c_str()));
}

CloneInfoHandle::~CloneInfoHandle()
{}

void CloneInfoHandle::LoadFile(const std::wstring & filename)
{
          USES_CONVERSION;
	  Document document(filename);
	  const Node rootNode = document.GetRootNode();
	  assert(rootNode.GetName() == (L"clone_info"));

	  CloneInfoItem cloneItem;
	  Node childNode = rootNode.GetChildNode(0);
	  const unsigned int nodeNum = rootNode.GetNumChildNodes();
	  std::string partiName;

	  for(unsigned int childIndex = 0; childIndex < nodeNum; ++childIndex)
	  {
               childNode = rootNode.GetChildNode(childIndex);
		 cloneItem.LoadXML(childNode);
		 
		 CloneInfo_table.insert(std::make_pair(cloneItem.partition_name(), cloneItem));
		 PartitionName_set.insert(cloneItem.partition_name());
		 LOG("%s: partition_name(%s)", __FUNC__, cloneItem.partition_name());
	  }
}

void CloneInfoHandle::SaveFile(const std::string &filename) const
{
         USES_CONVERSION;

         Document document(L"1.0", L"UTF-8", L"clone_info");

	  Node rootNode = document.GetRootNode();

	  for(std::map<std::string, CloneInfoItem>::const_iterator it = CloneInfo_table.begin();
	                   it!=CloneInfo_table.end(); ++it)
	  {
                 it->second.SaveXML(rootNode);
         }

	  document.Beautify();
        document.Save(A2CW(filename.c_str()));
}

void CloneInfoHandle::AddCloneInfoItem(const CloneInfoItem &item)
{
      LOGD("Add Clone Item.");
       CloneInfo_table.insert(std::make_pair(item.partition_name(), item));
	PartitionName_set.insert(item.partition_name());
	LOG("%s: Clone Info Item: partion_name(%s), partition_start_addr(%I64u), partition_len(%I64u), image_path(%s)",
		 __FUNC__, item.partition_name().c_str(),item.start_addr(), item.partition_len(), item.image_path().c_str());
}

void CloneInfoHandle::RemoveCloneInfoItem(CloneInfoItem &item)
{
       std::map<std::string, CloneInfoItem>::const_iterator it;

	for(it = CloneInfo_table.begin(); it!=CloneInfo_table.end(); ++it)
	{
             if(it->second.partition_name() == item.partition_name())
             {
                 // CloneInfo_table.erase(it);
	      }
	}
}

void CloneInfoHandle::UpdateCloneInfoTable(CloneInfoItem & cloneinfo)
{
         for(std::map<std::string, CloneInfoItem>::iterator it = CloneInfo_table.begin();
		           it!=CloneInfo_table.end(); ++it)
        {
                if(it->first == cloneinfo.partition_name_)
                {
                         it->second.set_partition_name(cloneinfo.partition_name());
                         it->second.set_image_path(cloneinfo.image_path());
                         it->second.set_start_addr(cloneinfo.start_addr());
                         it->second.set_partition_len(cloneinfo.partition_len());
                         it->second.set_chksum_value(cloneinfo.chksum_value());                      
                }
	 }
}

bool CloneInfoHandle::QueryCloneInfoByPartitionName(const  std::string & partition_name, CloneInfoItem *p_clone_info)
{
       bool ret = false;

       for(std::map<std::string, CloneInfoItem>::const_iterator it = CloneInfo_table.begin();
	                it!=CloneInfo_table.end(); ++it)
	{
                if(partition_name == it->first)
                {
                      p_clone_info->set_partition_name(it->second.partition_name());
		         p_clone_info->set_image_path(it->second.image_path());
			 p_clone_info->set_chksum_value(it->second.chksum_value());
			 p_clone_info->set_start_addr(it->second.start_addr());
			 p_clone_info->set_partition_len(it->second.partition_len());

			 ret = true;

			 break;
		  }
       }
	   
       return ret;
}

std::set<std::string> CloneInfoHandle::partition_name_set(void) {
	std::set<std::string> partition_name_set_tmp;
	std::set<std::string>::iterator it;
	for (it = this->PartitionName_set.begin(); it != this->PartitionName_set.end(); ++it) {
		LOG("%s(): Partition_Name(%s).", __FUNC__, *it);
		partition_name_set_tmp.insert(*it);
	}
	return partition_name_set_tmp;
}

CloneInfoHandle& GetCloneInfoHandle(std::string filename){
	USES_CONVERSION;
	assert(FileUtils::IsFileExist(filename)&&"clone_info.xml does not exist under tool folder!");
        static CloneInfoHandle clHandle(filename.c_str());
	return clHandle;
}        




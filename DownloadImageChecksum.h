#ifndef DOWNLOAD_IMAGE_CHECKSUM_H
#define DOWNLOAD_IMAGE_CHECKSUM_H
#include <map>
#include <string>
#include <inifiles.hpp>

class DownloadImageChecksum
{
public:
	DownloadImageChecksum(void);
	~DownloadImageChecksum(void);
	unsigned int QueryChecksumValueByImageName(const std::string& img_name);
	bool is_do_checksum(void) {
		return this->is_do_checksum_;
	}
	bool is_checksum_file_ready(void) {
		return this->is_checksum_file_ready_;
	}

	void Dump(void);
private:
	void set_checksum_file_path_by_load(void);
	bool LoadIniFile(void);
	void InitChecksumMap(void);
	void UnLoadIniFile(void);
private:
	static const std::string kChecksumFileName;

	TIniFile* check_sum_ini_;
	std::map<std::string, unsigned int> image_checksum_map_;
	bool is_do_checksum_;
	bool is_checksum_file_ready_;
	std::string checksum_file_path_;
};
#endif

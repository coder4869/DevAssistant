// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "CUFile.h"

#include <algorithm>
#include <iostream>
#include <fstream>
//#include <sstream>
#include <fstream>

#if _HAS_CXX17
#include <filesystem> // C++17 and above is required for this header
#endif

#include <CUtils/logger.h>

#define LOG_TAG "TAG_CUFile"

NS_CU_BEGIN

int File::IsFileExist(const std::string& file_path)
{
    std::fstream fs;
    fs.open(file_path.c_str(), std::ios_base::in);
    if (!fs.is_open()) {
        LOGE("%s : Open File %s Failed", __FUNCTION__, file_path.c_str());
        return -1;
    }
    fs.close();
    return 0;
}

int File::CopyFiles(const std::vector<std::string>& src_list, const std::string& dst_path, CopyMode cmode)
{
    if (src_list.size() == 0) {
        LOGE("%s : src_list is Empty !", __FUNCTION__);
        return -1;
    }

    //File2File,	// Copy File From Path To File-Path
    //File2Dir,	// Copy Files From Path To Dir-Path
    //Dir2Dir		// Copy All Files In Dir To Dir-Path
#if _HAS_CXX17
    try {
        for (size_t idx = 0; idx < src_list.size(); idx++)
        {
            if (std::filesystem::exists(src_list[idx])) {
                std::string fname = std::filesystem::path(src_list[idx]).filename().string();
                std::filesystem::copy_file(src_list[idx], dst_path + fname, std::filesystem::copy_options::overwrite_existing);

                LOGI("%s : Source File %s Copy Succeed !", __FUNCTION__, src_list[idx].c_str());
            } else {
                LOGE("%s : Source File %s Not Exist !", __FUNCTION__, src_list[idx].c_str());
            }
        }
    }
    catch (const std::exception& e) {
        LOGE("%s : Error %s", __FUNCTION__, e.what());
    }

    return 0;
#else
    LOGE("%s : Error C++17 Not Support !", __FUNCTION__);
    return -2;
#endif
}

int File::LoadFileString(const std::string& file_path, std::string& out_str)
{
    std::fstream fs;
    fs.open(file_path.c_str(), std::ios_base::in);
    if (!fs.is_open()) {
        LOGE("%s : Open File %s Failed", __FUNCTION__, file_path.c_str());
        return -1;
    }

    if (fs) {
        fs.seekg(0, std::ios::end);
        out_str.resize(fs.tellg());
        fs.seekg(0, std::ios::beg);
        fs.read(&out_str[0], out_str.size());
        fs.close();

        return 0;
    }

    LOGE("%s : Read File %s Failed", __FUNCTION__, file_path.c_str());
    fs.close();
    return -1;
}

int File::SaveFileString(const std::string& file_path, const std::string& save_str, bool is_append)
{
    std::ofstream fs;
    std::locale::global(std::locale(""));  // Set global as system default
    if (is_append) {
        fs.open(file_path, std::ios::out | std::ios::app);
    }
    else {
        fs.open(file_path, std::ios::out | std::ios::trunc);
    }
    std::locale::global(std::locale("C"));  // Recover system default setting
    if (!fs.is_open()) {
        LOGE("%s : Open File %s Failed", __FUNCTION__, file_path.c_str());
        return -1;
    }

    //std::ostringstream oss;
    std::string str_copy = save_str;
    std::replace(str_copy.begin(), str_copy.end(), '\0', ' ');
    fs << str_copy;

    //fs.write(oss.str().c_str(), oss.str().length());
    //fs.close();
    return 0;
}

int File::DeleteFiles(const std::string& dir_path, const std::string& extends) {
#if _HAS_CXX17
    if (!std::filesystem::exists(dir_path) || !std::filesystem::is_directory(dir_path)) {
        LOGE("%s : dir %s not exist or not directory !", __FUNCTION__, dir_path.c_str());
        return -1;
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
        if (entry.is_regular_file() && entry.path().extension() == extends) {
            std::error_code ec;
            std::filesystem::remove(entry.path(), ec);
            if (ec) {
                LOGE("%s : delete file %s error %s !", __FUNCTION__, entry.path().c_str(), ec.message().c_str());
            } else {
                LOGI("%s : delete file %s succeed !", __FUNCTION__, entry.path().c_str());
            }
        }
    }
    return 0;
#else
    LOGE("%s : Error C++17 Not Support !", __FUNCTION__);
    return -2;
#endif
}


NS_CU_END

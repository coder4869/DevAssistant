// MIT License
//
// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "CUFile.h"

#include <algorithm>
#include <iostream>
#include <fstream>
//#include <sstream>
#include <fstream>

#if _HAS_CXX17
#include <filesystem> // C++17 and above is required for this header
#endif

NS_CU_BEGIN

int File::IsFileExist(const std::string& file_path)
{
    std::fstream fs;
    fs.open(file_path.c_str(), std::ios_base::in);
    if (!fs.is_open()) {
        std::cout << __FUNCTION__ << ": Open File " + file_path + " Failed" << std::endl;
        return -1;
    }
    fs.close();
    return 0;
}

int File::CopyFiles(const std::vector<std::string>& src_list, const std::string& dst_path, CopyMode cmode)
{
    if (src_list.size() == 0) {
        std::cout << __FUNCTION__ << ": src_list is Empty !" << std::endl;
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

                std::cout << __FUNCTION__ << " Info: Source File " << src_list[idx] << " Copy Succeed !" << std::endl;
            } else {
                std::cout << __FUNCTION__ << " Error: Source File " << src_list[idx] << " Not Exist !" << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << __FUNCTION__ << " Error: " << e.what() << std::endl;
    }

    return 0;
#else
    std::cout << __FUNCTION__ << " Error: C++17 Not Support !" << std::endl;
    return -2;
#endif
}

int File::LoadFileString(const std::string& file_path, std::string& out_str)
{
    std::fstream fs;
    fs.open(file_path.c_str(), std::ios_base::in);
    if (!fs.is_open()) {
        std::cout << __FUNCTION__ << ": Open File " + file_path + " Failed" << std::endl;
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

    std::cout << __FUNCTION__ << ": Read File " + file_path + " Failed" << std::endl;
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
        std::cout << __FUNCTION__ << ": Open File " + file_path + " Failed" << std::endl;
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

NS_CU_END
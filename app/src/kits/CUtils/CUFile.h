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

// https://blog.csdn.net/weixin_45525272/article/details/109687419

#ifndef CU_FILE_H
#define CU_FILE_H

#include <string>

#include "CUtilsDef.h"

NS_CU_BEGIN
namespace File {
	/// @return 0 succeed, other failed
	//CUtils_API 
	int IsFileExist(const std::string& file_path);

	/// @return 0 succeed, other failed
	//CUtils_API 
	int LoadFileString(const std::string& file_path, std::string& out_str);

	/// @return 0 succeed, other failed
	//CUtils_API 
	int SaveFileString(const std::string& file_path, const std::string& save_str, bool is_append = false);

} // namespace File
NS_CU_END


#endif // CU_FILE_H

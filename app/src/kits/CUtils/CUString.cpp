// MIT License
//
// Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)
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

#include "CUString.h"

NS_CU_BEGIN

/// @brief Split str by split_tag
/// @param values output set list 
int String::SplitStringToSet(const std::string& str, const std::string& split_tag, std::set<std::string>& values)
{
	values.clear();
	if (!str.empty() && !split_tag.empty()) {
		std::string sub_str;
		int len = split_tag.size();

		for (size_t idx = 0; idx < str.size(); idx++) {
			if (split_tag == str.substr(idx, len)) // Finish once
			{
				idx = idx + len - 1;
				if (!sub_str.empty()) {
					values.insert(sub_str);
					sub_str.clear();
				}
			}
			else // Finding next tag continue
			{
				sub_str.push_back(str[idx]);
			}
		}

		if (!sub_str.empty()) {
			values.insert(sub_str);
			sub_str.clear();
		}
		return 1;
	}

	//for (auto item = values.begin(); item != values.end(); item++) {
	//	std::cout << __FUNCTION__ << item->c_str() << std::endl;
	//}

	return 0;
}

/// @brief Split str by split_tag
/// @param values output vector list 
int String::SplitStringToVector(const std::string& str, const std::string& split_tag, std::vector<std::string>& values)
{
	values.clear();
	if (!str.empty() && !split_tag.empty()) {
		std::string sub_str;
		int len = split_tag.size();

		for (size_t idx = 0; idx < str.size(); idx++) {
			if (split_tag == str.substr(idx, len)) // Finish once
			{
				idx = idx + len - 1;
				if (!sub_str.empty()) {
					values.push_back(sub_str);
					sub_str.clear();
				}
			}
			else // Finding next tag continue
			{
				sub_str.push_back(str[idx]);
			}
		}

		if (!sub_str.empty()) {
			values.push_back(sub_str);
			sub_str.clear();
		}

		return 1;
	}

	//for (auto item = values.begin(); item != values.end(); item++) {
	//	std::cout << __FUNCTION__ << item->c_str() << std::endl;
	//}

	return 0;
}

NS_CU_END

// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "CUString.h"

#include <sstream>

#include "logger.h"

NS_CU_BEGIN

/// @brief Split str by split_tag
/// @param values output set list 
int String::SplitStringToSet(const std::string& str, const std::string& split, std::set<std::string>& values)
{
	values.clear();
    std::string split_tag = split.empty() ? " " : split;
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
    //  LOGE("%s : %s", __FUNCTION__, item->c_str());
	//}

	return 0;
}

/// @brief Split str by split_tag
/// @param values output vector list 
int String::SplitStringToVector(const std::string& str, const std::string& split, std::vector<std::string>& values)
{
	values.clear();
    std::string split_tag = split.empty() ? " " : split;
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
    //  LOGE("%s : %s", __FUNCTION__, item->c_str());
	//}
	return 0;
}

int String::Replace(std::string& str, const std::string& from, const std::string& to)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += to.length()) 
	{
		pos = str.find(from, pos);
		if (pos != std::string::npos) {
			str.replace(pos, from.length(), to);
		} else {
			break;
		}
	}
	return 0;
}

int String::LastNCharSubStr(const std::string& str, char ch, size_t n, std::string &output) {
    size_t pos = str.rfind(ch);
    size_t count = 1;
    
    while ((pos != std::string::npos) && (count < n)) {
        pos = str.rfind(ch, pos-1);
        ++count;
    }
    
    if (count == n) {
        output = str.substr(0, pos);
        return true;
    }
    output = "";
    return false;
}

NS_CU_END

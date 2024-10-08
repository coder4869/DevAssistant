// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef CU_STRING_H
#define CU_STRING_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <string>
#include <vector>
#include <set>

#include "CUtilsDef.h"
#define LOG_TAG "TAG_CUTILS"

NS_CU_BEGIN
namespace String {
    /// @brief Split str by split_tag
    /// @param values output set list 
    //CUtils_API 
    int SplitStringToSet(const std::string& str, const std::string& split_tag, std::set<std::string> & values);

    /// @brief Split str by split_tag
    /// @param values output vector list 
    //CUtils_API 
    int SplitStringToVector(const std::string& str, const std::string& split_tag, std::vector<std::string> & values);
    
    int Replace(std::string& str, const std::string& from, const std::string& to);
    
    /// @brief Get str's sub-string from [0, pos of last n'th ch]
    int LastNCharSubStr(const std::string& str, char ch, size_t n, std::string &output);
}
NS_CU_END

#endif // CU_STRING_H

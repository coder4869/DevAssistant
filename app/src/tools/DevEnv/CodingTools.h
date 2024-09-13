// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef DE_CODINGTOOLS_H
#define DE_CODINGTOOLS_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <string>
#include <map>

#include "DevEnvDef.h"

//NS_DE_BEGIN
namespace CodingTool {

    struct SoftInfo {
        std::string search_key = "";
        std::string install_path = "";
    };

    /// @return <soft, <search-key, install—path>>
    std::map<std::string, SoftInfo> GetSoftInfos();

	/// @brief Get APP Query Key. RegVar(Windows) or EnvPath
	std::string GetQueryKey();

	/// @brief Get APP Installed Path 
	std::string GetRootDir(const std::string &soft, const std::string &search_key);

	/// @brief Check APP Env. e.g. Install Path Exist or not in PATH EnvVar, Pkg-config Exist or Not.
	std::string CheckEnv();

} //namespace CodingTool
//NS_DE_BEGIN

#endif // DE_CODINGTOOLS_H

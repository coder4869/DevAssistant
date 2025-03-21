// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

// https://blog.csdn.net/weixin_45525272/article/details/109687419

#ifndef CU_FILE_H
#define CU_FILE_H

#include <string>
#include <vector>

#include "CUtilsDef.h"

NS_CU_BEGIN
namespace File {
	enum class CopyMode
	{
		File2File,	// Copy File From Path To File-Path
		File2Dir,	// Copy Files From Path To Dir-Path
		Dir2Dir		// Copy All Files In Dir To Dir-Path
	};

	/// @return 0 succeed, other failed
	//CUtils_API 
	int IsFileExist(const std::string& file_path);

	/// @brief Copy Files By Mode
	/// @return 0 succeed, other failed
	//CUtils_API 
	int CopyFiles(const std::vector<std::string>& src_list, const std::string& dst_path, CopyMode cmode= CopyMode::File2Dir);

	/// @return 0 succeed, other failed
	//CUtils_API 
	int LoadFileString(const std::string& file_path, std::string& out_str);

	/// @return 0 succeed, other failed
	//CUtils_API 
	int SaveFileString(const std::string& file_path, const std::string& save_str, bool is_append = false);

    /// @param  extends
    /// @return 0 succeed, other failed
    //CUtils_API
    int DeleteFiles(const std::string& dir_path, const std::string& extends);

} // namespace File
NS_CU_END


#endif // CU_FILE_H

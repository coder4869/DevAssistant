// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef MODULE_NAME_DEF_H
#define MODULE_NAME_DEF_H

#define NS_MODULE_NAME_BEGIN namespace MODULE_NAME {
#define NS_MODULE_NAME_END	} //namespace MODULE_NAME

#ifdef MODULE_NAME_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define MODULE_NAME_CLASS __declspec(dllexport)
#		define MODULE_NAME_API extern "C" __declspec(dllexport)
#	else
#		define MODULE_NAME_CLASS __attribute__((externally_visible))
#		define MODULE_NAME_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define MODULE_NAME_CLASS __declspec(dllimport)
#		define MODULE_NAME_API extern "C" __declspec(dllimport)
#	else
#		define MODULE_NAME_CLASS __attribute__((externally_visible))
#		define MODULE_NAME_API extern "C" __attribute__((externally_visible))
#	endif

#endif // MODULE_NAME_EXPORT

#endif /* MODULE_NAME_DEF_H */

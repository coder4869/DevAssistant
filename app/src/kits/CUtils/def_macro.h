// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#if WIN
#	define API_EXPORT _declspec(dllexport)
#	define API_IMPORT _declspec(dllimport)
#else // Linux
#	define API_EXPORT __attribute__((visibility("default")))
#	define API_IMPORT 
#endif // Linux


#ifndef __DEF_MACRO_H__
#define __DEF_MACRO_H__

#define RET_OK      0
#define RET_ERROR   1

//#if WIN
//const char* PATH_SPLIT_TAG = "\\";
//#else // Linux
//const char* PATH_SPLIT_TAG = "/";
//#endif // Linux

#endif // __DEF_MACRO_H__

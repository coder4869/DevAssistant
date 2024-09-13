// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef CUTILS_DEF_H
#define CUTILS_DEF_H

#define NS_CU_BEGIN namespace CU {
#define NS_CU_END	} //namespace CU

#ifdef CUTILS_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define CUTILS_CLASS __declspec(dllexport)
#		define CUTILS_API extern "C" __declspec(dllexport)
#	else
#		define CUTILS_CLASS __attribute__((externally_visible))
#		define CUTILS_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define CUTILS_CLASS __declspec(dllimport)
#		define CUTILS_API extern "C" __declspec(dllimport)
#	else
#		define CUTILS_CLASS __attribute__((externally_visible))
#		define CUTILS_API extern "C" __attribute__((externally_visible))
#	endif

#endif // CUTILS_EXPORT

#endif /* CUTILS_DEF_H */

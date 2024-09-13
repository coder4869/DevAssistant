// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef CAPP_DEF_H
#define CAPP_DEF_H

#define NS_CAPP_BEGIN namespace CAPP {
#define NS_CAPP_END	} //namespace CAPP

#ifdef CAPP_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define CAPP_CLASS __declspec(dllexport)
#		define CAPP_API extern "C" __declspec(dllexport)
#	else
#		define CAPP_CLASS __attribute__((externally_visible))
#		define CAPP_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define CAPP_CLASS __declspec(dllimport)
#		define CAPP_API extern "C" __declspec(dllimport)
#	else
#		define CAPP_CLASS __attribute__((externally_visible))
#		define CAPP_API extern "C" __attribute__((externally_visible))
#	endif

#endif // CAPP_EXPORT

#endif /* CAPP_DEF_H */

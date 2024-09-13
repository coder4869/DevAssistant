// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef GITTOOL_DEF_H
#define GITTOOL_DEF_H

#define NS_GIT_BEGIN namespace GIT {
#define NS_GIT_END	} //namespace GIT

#ifdef GITTOOL_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define GITTOOL_CLASS __declspec(dllexport)
#		define GITTOOL_API extern "C" __declspec(dllexport)
#	else
#		define GITTOOL_CLASS __attribute__((externally_visible))
#		define GITTOOL_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define GITTOOL_CLASS __declspec(dllimport)
#		define GITTOOL_API extern "C" __declspec(dllimport)
#	else
#		define GITTOOL_CLASS __attribute__((externally_visible))
#		define GITTOOL_API extern "C" __attribute__((externally_visible))
#	endif

#endif // GITTOOL_EXPORT

#endif /* GITTOOL_DEF_H */

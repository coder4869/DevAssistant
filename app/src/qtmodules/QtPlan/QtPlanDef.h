// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QTPLAN_DEF_H
#define QTPLAN_DEF_H

#define NS_QPL_BEGIN namespace QPL {
#define NS_QPL_END	} //namespace QPL

#ifdef QTPLAN_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTPLAN_CLASS __declspec(dllexport)
#		define QTPLAN_API extern "C" __declspec(dllexport)
#	else
#		define QTPLAN_CLASS __attribute__((externally_visible))
#		define QTPLAN_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTPLAN_CLASS __declspec(dllimport)
#		define QTPLAN_API extern "C" __declspec(dllimport)
#	else
#		define QTPLAN_CLASS __attribute__((externally_visible))
#		define QTPLAN_API extern "C" __attribute__((externally_visible))
#	endif

#endif // QTPLAN_EXPORT

#endif /* QTPLAN_DEF_H */

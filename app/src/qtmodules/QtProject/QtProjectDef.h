// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QTPROJECT_DEF_H
#define QTPROJECT_DEF_H

#define NS_QPROJ_BEGIN namespace QPROJ {
#define NS_QPROJ_END	} //namespace QPROJ

#ifdef QTPROJECT_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTPROJECT_CLASS __declspec(dllexport)
#		define QTPROJECT_API extern "C" __declspec(dllexport)
#	else
#		define QTPROJECT_CLASS __attribute__((externally_visible))
#		define QTPROJECT_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTPROJECT_CLASS __declspec(dllimport)
#		define QTPROJECT_API extern "C" __declspec(dllimport)
#	else
#		define QTPROJECT_CLASS __attribute__((externally_visible))
#		define QTPROJECT_API extern "C" __attribute__((externally_visible))
#	endif

#endif // QTPROJECT_EXPORT

#endif /* QTPROJECT_DEF_H */

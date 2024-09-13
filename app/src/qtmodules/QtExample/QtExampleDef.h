// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QTEXAMPLE_DEF_H
#define QTEXAMPLE_DEF_H

#define NS_QEXAM_BEGIN namespace QEXAM {
#define NS_QEXAM_END	} //namespace QEXAM

#ifdef QTEXAMPLE_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTEXAMPLE_CLASS __declspec(dllexport)
#		define QTEXAMPLE_API extern "C" __declspec(dllexport)
#	else
#		define QTEXAMPLE_CLASS __attribute__((externally_visible))
#		define QTEXAMPLE_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTEXAMPLE_CLASS __declspec(dllimport)
#		define QTEXAMPLE_API extern "C" __declspec(dllimport)
#	else
#		define QTEXAMPLE_CLASS __attribute__((externally_visible))
#		define QTEXAMPLE_API extern "C" __attribute__((externally_visible))
#	endif

#endif // QTEXAMPLE_EXPORT

#endif /* QTEXAMPLE_DEF_H */

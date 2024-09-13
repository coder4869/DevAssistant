// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QTCOREKIT_DEF_H
#define QTCOREKIT_DEF_H

#define NS_QCK_BEGIN namespace QCK {
#define NS_QCK_END	} //namespace QCK

#ifdef QTCOREKIT_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTCOREKIT_CLASS __declspec(dllexport)
#		define QTCOREKIT_API extern "C" __declspec(dllexport)
#	else
#		define QTCOREKIT_CLASS __attribute__((externally_visible))
#		define QTCOREKIT_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTCOREKIT_CLASS __declspec(dllimport)
#		define QTCOREKIT_API extern "C" __declspec(dllimport)
#	else
#		define QTCOREKIT_CLASS __attribute__((externally_visible))
#		define QTCOREKIT_API extern "C" __attribute__((externally_visible))
#	endif

#endif // QTCOREKIT_EXPORT

#endif /* QTCOREKIT_DEF_H */

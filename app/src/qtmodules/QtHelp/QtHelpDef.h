// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QTHELP_DEF_H
#define QTHELP_DEF_H

#define NS_QHP_BEGIN namespace QHP {
#define NS_QHP_END	} //namespace QHP

#ifdef QTHELP_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTHELP_CLASS __declspec(dllexport)
#		define QTHELP_API extern "C" __declspec(dllexport)
#	else
#		define QTHELP_CLASS __attribute__((externally_visible))
#		define QTHELP_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTHELP_CLASS __declspec(dllimport)
#		define QTHELP_API extern "C" __declspec(dllimport)
#	else
#		define QTHELP_CLASS __attribute__((externally_visible))
#		define QTHELP_API extern "C" __attribute__((externally_visible))
#	endif

#endif // QTHELP_EXPORT

#endif /* QTHELP_DEF_H */

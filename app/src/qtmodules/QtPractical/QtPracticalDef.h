// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QTPRACTICAL_DEF_H
#define QTPRACTICAL_DEF_H

#define NS_QPRAC_BEGIN namespace QPRAC {
#define NS_QPRAC_END	} //namespace QPRAC

#ifdef QTPRACTICAL_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTPRACTICAL_CLASS __declspec(dllexport)
#		define QTPRACTICAL_API extern "C" __declspec(dllexport)
#	else
#		define QTPRACTICAL_CLASS __attribute__((externally_visible))
#		define QTPRACTICAL_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTPRACTICAL_CLASS __declspec(dllimport)
#		define QTPRACTICAL_API extern "C" __declspec(dllimport)
#	else
#		define QTPRACTICAL_CLASS __attribute__((externally_visible))
#		define QTPRACTICAL_API extern "C" __attribute__((externally_visible))
#	endif

#endif // QTPRACTICAL_EXPORT

#endif /* QTPRACTICAL_DEF_H */

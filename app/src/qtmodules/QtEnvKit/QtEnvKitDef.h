// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QTENVKIT_DEF_H
#define QTENVKIT_DEF_H

#define NS_QEK_BEGIN	namespace QEK {
#define NS_QEK_END		} //namespace QEK

#ifdef QTENVKIT_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTENVKIT_CLASS __declspec(dllexport)
#		define QTENVKIT_API extern "C" __declspec(dllexport)
#	else
#		define QTENVKIT_CLASS __attribute__((externally_visible))
#		define QTENVKIT_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTENVKIT_CLASS __declspec(dllimport)
#		define QTENVKIT_API extern "C" __declspec(dllimport)
#	else
#		define QTENVKIT_CLASS __attribute__((externally_visible))
#		define QTENVKIT_API extern "C" __attribute__((externally_visible))
#	endif

#endif // QTENVKIT_EXPORT

#endif /* QTENVKIT_DEF_H */

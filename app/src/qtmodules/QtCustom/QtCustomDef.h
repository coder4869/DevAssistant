// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QTCUSTOM_DEF_H
#define QTCUSTOM_DEF_H

#define NS_QCST_BEGIN namespace QCST {
#define NS_QCST_END	} //namespace QCST

#ifdef QTCUSTOM_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTCUSTOM_CLASS __declspec(dllexport)
#		define QTCUSTOM_API extern "C" __declspec(dllexport)
#	else
#		define QTCUSTOM_CLASS __attribute__((externally_visible))
#		define QTCUSTOM_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTCUSTOM_CLASS __declspec(dllimport)
#		define QTCUSTOM_API extern "C" __declspec(dllimport)
#	else
#		define QTCUSTOM_CLASS __attribute__((externally_visible))
#		define QTCUSTOM_API extern "C" __attribute__((externally_visible))
#	endif

#endif // QTCUSTOM_EXPORT

#endif /* QTCUSTOM_DEF_H */

// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef CSCRIPT_DEF_H
#define CSCRIPT_DEF_H

#define NS_CS_BEGIN namespace CS {
#define NS_CS_END	} //namespace CS

#ifdef CSCRIPT_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define CSCRIPT_CLASS __declspec(dllexport)
#		define CSCRIPT_API extern "C" __declspec(dllexport)
#	else
#		define CSCRIPT_CLASS __attribute__((externally_visible))
#		define CSCRIPT_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define CSCRIPT_CLASS __declspec(dllimport)
#		define CSCRIPT_API extern "C" __declspec(dllimport)
#	else
#		define CSCRIPT_CLASS __attribute__((externally_visible))
#		define CSCRIPT_API extern "C" __attribute__((externally_visible))
#	endif

#endif // CSCRIPT_EXPORT

#endif /* CSCRIPT_DEF_H */

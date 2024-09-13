// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef COSENV_DEF_H
#define COSENV_DEF_H

#define NS_CE_BEGIN namespace CE {
#define NS_CE_END	} //namespace CE

#ifdef COSENV_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define COSENV_CLASS __declspec(dllexport)
#		define COSENV_API extern "C" __declspec(dllexport)
#	else
#		define COSENV_CLASS __attribute__((externally_visible))
#		define COSENV_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define COSENV_CLASS __declspec(dllimport)
#		define COSENV_API extern "C" __declspec(dllimport)
#	else
#		define COSENV_CLASS __attribute__((externally_visible))
#		define COSENV_API extern "C" __attribute__((externally_visible))
#	endif

#endif // COSENV_EXPORT

#endif /* COSENV_DEF_H */

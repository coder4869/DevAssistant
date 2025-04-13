// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef DEVENV_DEF_H
#define DEVENV_DEF_H

#define NS_DE_BEGIN namespace DE {
#define NS_DE_END	} //namespace DE

#ifdef DEVENV_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define DEVENV_CLASS __declspec(dllexport)
#		define DEVENV_API extern "C" __declspec(dllexport)
#	else
#		define DEVENV_CLASS __attribute__((externally_visible))
#		define DEVENV_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define DEVENV_CLASS __declspec(dllimport)
#		define DEVENV_API extern "C" __declspec(dllimport)
#	else
#		define DEVENV_CLASS __attribute__((externally_visible))
#		define DEVENV_API extern "C" __attribute__((externally_visible))
#	endif

#endif // DEVENV_EXPORT

#endif /* DEVENV_DEF_H */

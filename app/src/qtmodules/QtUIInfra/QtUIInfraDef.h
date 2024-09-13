// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QTUIINFRA_DEF_H
#define QTUIINFRA_DEF_H

#define NS_QUI_BEGIN namespace QUI {
#define NS_QUI_END	} //namespace QUI

#ifdef QTUIINFRA_EXPORT

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTUIINFRA_CLASS __declspec(dllexport)
#		define QTUIINFRA_API extern "C" __declspec(dllexport)
#	else
#		define QTUIINFRA_CLASS __attribute__((externally_visible))
#		define QTUIINFRA_API extern "C" __attribute__((externally_visible))
#	endif

#else

#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
#		define QTUIINFRA_CLASS __declspec(dllimport)
#		define QTUIINFRA_API extern "C" __declspec(dllimport)
#	else
#		define QTUIINFRA_CLASS __attribute__((externally_visible))
#		define QTUIINFRA_API extern "C" __attribute__((externally_visible))
#	endif

#endif // QTUIINFRA_EXPORT


#endif /* QTUIINFRA_DEF_H */

// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "GithubEnv.h"

#include <iostream>

NS_GIT_BEGIN

bool Github::GithubConnectFix()
{
#if WIN
	int ret = system("ipconfig /flushdns");
	return ret == 0;
#else
	return false;
#endif // WIN
}

NS_GIT_END

// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef GITHUB_ENV_H
#define GITHUB_ENV_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <string>

#include "GitToolDef.h"

NS_GIT_BEGIN
namespace Github {

	/// @brief Try Fix Github Connnect Issue
	bool GithubConnectFix();

} //namespace Github
NS_GIT_END

#endif // GITHUB_ENV_H

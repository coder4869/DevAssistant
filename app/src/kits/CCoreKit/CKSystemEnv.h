// https://www.delftstack.com/zh/howto/cpp/cpp-get-environment-variables/

#pragma once

#include <iostream>
#include <string>
#include <cstdlib> // GetEnv

class CKSystemEnv
{
public:
	// name is upper-case
	static std::string GetEnv(const char*name);
	static std::string GetPathEnv();
};


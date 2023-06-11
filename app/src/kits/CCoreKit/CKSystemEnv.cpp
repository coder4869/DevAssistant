#include "CKSystemEnv.h"

// name is upper-case
std::string CKSystemEnv::GetEnv(const char* name)
{
	const char* val = std::getenv(name);
	std::string env_var(val ? "" : std::string(val));
	return env_var;
}

std::string CKSystemEnv::GetPathEnv()
{
	return GetEnv("PATH");
}
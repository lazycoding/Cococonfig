#pragma once
#include <string>
class ResourceValue;
namespace stringutils
{
	std::string format(const char *fmt, ...);

	std::string tostring(const ResourceValue& value);
}
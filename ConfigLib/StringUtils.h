#pragma once
#include <string>
#include <vector>
#include <cctype>
class ResourceValue;
namespace stringutils
{
	typedef int(*TrimPred)(int);

	std::string format(const char *fmt, ...);

	std::string tostring(const ResourceValue& value);

	std::string &ltrim(std::string &s, TrimPred pred = std::isspace);

	std::string &rtrim(std::string &s, TrimPred pred = std::isspace);

	std::string &trim(std::string &s, TrimPred pred = std::isspace);

	int SplitString(const std::string& orign, std::vector<std::string>& splited_strings, const std::string& spliter);

	std::string ReadFromFile(const std::string& path );
}
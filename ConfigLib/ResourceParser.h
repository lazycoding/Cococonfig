#ifndef _RESOURCE_PARSER_H_
#define _RESOURCE_PARSER_H_
#include <string>

class ResourceValue;
class ResourceParser
{
public:
	virtual ~ResourceParser() = default;
	virtual bool Parse(const std::string&  raw_string, ResourceValue* rv) = 0;
};
#endif
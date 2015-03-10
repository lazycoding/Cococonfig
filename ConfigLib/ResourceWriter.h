#ifndef _RESOURCE_WRITER_H_
#define _RESOURCE_WRITER_H_

#include <string>

class ResourceValue;
class ResourceWriter
{
public:
	virtual ~ResourceWriter() = default;

	virtual bool WriteTo(const ResourceValue* rv, std::string& output_string) = 0;
};
#endif
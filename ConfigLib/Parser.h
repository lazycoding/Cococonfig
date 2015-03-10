#pragma once
#include <string>
#include <memory>
#include "ResourceNode.h"
class Parser
{
public:
	virtual ~Parser() = default;
	virtual bool Parse(const std::string& raw_value, ResourceNode& node) = 0;
};
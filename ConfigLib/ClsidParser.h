#pragma once
#include "Parser.h"
class ClsidParser:public Parser
{
public:
	ClsidParser();
	~ClsidParser();

	virtual bool Parse(const std::string& raw_value, ResourceNode& node);

};


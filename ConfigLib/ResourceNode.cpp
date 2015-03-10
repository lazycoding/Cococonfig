#include "stdafx.h"
#include "ResourceNode.h"

ResourceNode::ResourceNode() :line_(-1), parent_(nullptr)
{

}

ResourceNode::ResourceNode(const std::string& name, const ResourceValue& rv, LineNo line)
	: name_(name), parent_(nullptr), line_(line), value_(rv)
{

}

ResourceNode::ResourceNode(const std::string& name)
	: name_(name), line_(-1), parent_(nullptr)
{

}

ResourceNode::ResourceNode(const ResourceNode& rvalue)	
{
	Assign(rvalue);
}

ResourceNode::~ResourceNode()
{
	parent_ = nullptr;
	line_ = -1;
}

bool ResourceNode::IsValueNode() const
{
	return value_.GetType() != ResourceValue::Empty;
}

ResourceNode& ResourceNode::operator=(const ResourceNode& rvalue)
{
	if (this != &rvalue)
	{		
		Assign(rvalue);
	}
	return *this;
}

void ResourceNode::Assign(const ResourceNode& rvalue)
{
	name_ = rvalue.name_;
	line_ = rvalue.line_;
	parent_ = rvalue.parent_;
	children_.assign(rvalue.children_.begin(), rvalue.children_.end());
	value_ = rvalue.value_;
}

void ResourceNode::Name(const std::string& name)
{
	name_ = name;
}

std::string ResourceNode::Name() const
{
	return name_;
}

void ResourceNode::Value(const ResourceValue& v)
{
	value_ = v;
}

ResourceValue ResourceNode::Value() const
{
	return value_;
}

void ResourceNode::LineNumber(LineNo line_no)
{
	line_ = line_no;
}

LineNo ResourceNode::LineNumber() const
{
	return line_;
}

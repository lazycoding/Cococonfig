#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ResourceValue.h"

typedef int LineNo;

class ResourceNode
{
	friend class ResourceTree;
	friend class TraversalTree;
public:
	ResourceNode();

	ResourceNode(const ResourceNode& rvalue);

	ResourceNode& operator=(const ResourceNode& rvalue);

	explicit ResourceNode(const std::string& name);

	ResourceNode(const std::string& name, const ResourceValue& rv, LineNo line = -1);

	void Assign(const ResourceNode& r);

	~ResourceNode();

	bool IsValueNode() const;

	void Name(const std::string& name);

	std::string Name() const;

	void Value(const ResourceValue& v);

	ResourceValue Value() const;

	void LineNumber(LineNo line_no);

	LineNo LineNumber() const;
private:
	std::string name_;
	LineNo line_;
	ResourceValue value_;
	ResourceNode*  parent_;
	std::vector<ResourceNode*> children_;
};

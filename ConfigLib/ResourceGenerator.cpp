#include "stdafx.h"
#include <sstream>
#include "ResourceGenerator.h"
#include "ResourceTree.h"
#include "ResourceNode.h"
#include "Parser.h"
using std::shared_ptr;
using std::string;
using std::make_shared;
using std::istringstream;

ResourceGenerator::ResourceGenerator(const shared_ptr<Parser>& parser)
	:parser_(parser), tree_(make_shared<ResourceTree>())
{
	InitializeTree();
}


ResourceGenerator::~ResourceGenerator()
{
}

shared_ptr<ResourceTree> ResourceGenerator::GenerateResourceTree(const string& bytes, ResourceType res_type)
{		
	istringstream stream(bytes);
	string line;
	int lineno = -1;

	auto child = GetChildTree(res_type);
	ResourceNode* child_root = nullptr;
	while (getline(stream, line))
	{
		++lineno;
		try
		{
			ResourceNode node;
			auto successed = parser_->Parse(line, node);
			if (!successed)
			{
				continue;
			}
			node.LineNumber(lineno);
			if (!node.IsValueNode())
			{
				child_root = tree_->Insert(child, node);
			}
			else if (child_root)
			{
				tree_->Insert(child_root, node);
			}			
		}
		catch (...)
		{			
			
		}
		line.clear();
	}
		
	return tree_;
}

void ResourceGenerator::InitializeTree()
{
}

ResourceNode* ResourceGenerator::GetChildTree(ResourceType res_type)
{
#ifdef _DEBUG
	ResourceNode node;
	node.Name("etc");
	auto root = tree_->Insert(nullptr, node);

	node.Name("iip");
	return tree_->Insert(root, node);

// 	node.Name("gui");
// 	tree_->Insert(root, node);
// 
// 	node.Name("dev");
// 	tree_->Insert(root, node);

#endif // DEBUG

}

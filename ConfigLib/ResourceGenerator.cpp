#include "stdafx.h"
#include <sstream>
#include <vector>
#include <string>
#include "ResourceGenerator.h"
#include "ResourceTree.h"
#include "ResourceNode.h"
#include "Parser.h"
#include "StringUtils.h"
using namespace std;

ResourceGenerator::ResourceGenerator(const shared_ptr<Parser>& parser)
	:parser_(parser), tree_(make_shared<ResourceTree>())
{
	
}


ResourceGenerator::~ResourceGenerator()
{
}

std::shared_ptr<ResourceTree> ResourceGenerator::GenerateResourceTree()
{			
	InitializeTree();

	string bytes = stringutils::ReadFromFile(resource_path_);

	auto child = GetChildTree(ResourceType::Main);

	ConstructTree(bytes, child);


	string path = resource_path_;
	int splash = resource_path_.rfind('\\');
	path = resource_path_.substr(0, splash + 1);

// 	//dev
// 	auto devconfigpath = tree_->Find("/etc/iip/System/Config.device");
// 	auto v = devconfigpath->Value();	 
//  	bytes = stringutils::ReadFromFile(path + v.GetProperty()["file"]);
//  	child = GetChildTree(ResourceType::Device); 
//  	ConstructTree(bytes, child);
//  
// 	//gui
// 	auto guiconfigpath = tree_->Find("/etc/iip/System/Config.gui");
// 	v = guiconfigpath->Value();
// 	bytes = stringutils::ReadFromFile(path + v.GetProperty()["file"]);
// 	child = GetChildTree(ResourceType::Gui);
// 	ConstructTree(bytes, child);
		
	return tree_;
}

void ResourceGenerator::InitializeTree()
{
	ResourceNode node;
	node.Name("etc");
	auto root = tree_->Insert(nullptr, node);
	
	node.Name("iip");
	tree_->Insert(root, node);

	node.Name("gui");
	tree_->Insert(root, node);
	 
	node.Name("dev");
	tree_->Insert(root, node);
}

ResourceNode* ResourceGenerator::GetChildTree(ResourceType res_type)
{
	ResourceNode* node = nullptr;
	switch (res_type)
	{
	case ResourceType::Main:
		node = tree_->Find("/etc/iip");
		break;
	case ResourceType::Gui:
		node = tree_->Find("/etc/gui");
		break;
	case ResourceType::Device:
		node = tree_->Find("/etc/dev");
		break;
	default:
		break;
	}
	return node;
}

void ResourceGenerator::ConstructTree(const std::string& bytes, ResourceNode * child)
{
	if (child == nullptr)
	{
		return;
	}
	istringstream stream(bytes);
	string line;
	int lineno = -1;
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
}

void ResourceGenerator::Path(const char* path)
{
	resource_path_ = path;
}

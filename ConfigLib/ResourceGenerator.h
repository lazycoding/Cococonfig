#pragma once
#include <string>
#include <memory>
class Parser;
class ResourceNode;
class ResourceTree;

enum class ResourceType
{
	Main, Gui, Device
};

class ResourceGenerator
{
public:
	explicit ResourceGenerator(const std::shared_ptr<Parser>& parser);

	~ResourceGenerator();

	std::shared_ptr<ResourceTree> GenerateResourceTree();

	void Path(const char* path);

#ifdef _DEBUG
	ResourceNode* GetChildTree(ResourceType res_type);

	void InitializeTree();
#endif

private:
#ifndef _DEBUG
	ResourceNode* GetChildTree(ResourceType res_type);

	void InitializeTree();
#endif
	void ConstructTree(const std::string& bytes, ResourceNode * child);
		
	std::shared_ptr<Parser> parser_;

	std::shared_ptr<ResourceTree> tree_;

	std::string resource_path_;
};


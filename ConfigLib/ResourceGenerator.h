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

	std::shared_ptr<ResourceTree> GenerateResourceTree(const std::string& bytes, ResourceType res_type);

private:
	void InitializeTree();
	ResourceNode* GetChildTree(ResourceType res_type);
	std::shared_ptr<Parser> parser_;
	std::shared_ptr<ResourceTree> tree_;
};


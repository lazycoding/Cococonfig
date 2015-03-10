#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <xtree>

class ResourceNode;
class ResourceTree
{
public:
	ResourceTree();

	~ResourceTree();
	
	//insert
	ResourceNode* Insert(ResourceNode* _where, const ResourceNode& node);

	//delete

	//modify

	//create

private:
	ResourceNode* root_;
	void DestroyTree(ResourceNode* treenode);

};


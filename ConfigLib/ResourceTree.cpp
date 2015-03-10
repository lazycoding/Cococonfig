#include "stdafx.h"
#include "ResourceTree.h"
#include "ResourceNode.h"
using std::shared_ptr;
using std::make_shared;
using std::make_unique;

ResourceTree::ResourceTree()
{
}


ResourceTree::~ResourceTree()
{	
	DestroyTree(root_);
}

ResourceNode* ResourceTree::Insert(ResourceNode* _where, const ResourceNode& node)
{
	if (!_where)
	{
		root_ = new ResourceNode(node);
		return root_;
	}
	else
	{
		auto n = new ResourceNode(node);		
		n->parent_ = _where;
		_where->children_.push_back(n);
		return n;
	}
	return nullptr;
}

void ResourceTree::DestroyTree(ResourceNode* treenode)
{
	if (!treenode)
	{
		return;
	}

	for (auto child : treenode->children_)
	{
		DestroyTree(child);
	}

	delete treenode;
	treenode = nullptr;
}

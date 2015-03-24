#include "stdafx.h"
#include "ResourceTree.h"
#include <string>
#include <vector>
#include "ResourceNode.h"
#include "TraversalTree.h"
#include "StringUtils.h"

using namespace std;

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
	TraversalTree::Postorder(treenode, [](ResourceNode* node){
		delete node;
		node = nullptr;
	});	
}


ResourceNode* ResourceTree::Root() const
{
	return root_;
}

ResourceNode* ResourceTree::Find(const char* path)
{
	vector<string> levels;
	int deepth = stringutils::SplitString(path, levels, "/");

	ResourceNode* node = root_;
	
	for (int i = 0; i < deepth; i++)
	{
		if (levels[i].empty())
		{
			continue;
		}

		size_t sibling = 1;
		while(node)		
		{				
			if (node->name_.compare(levels[i]) == 0)
			{				
				if (i == (deepth -1))
				{
					return node;
				}
				node = node->children_[0];
				break;
			}
			else
			{								
				if (node->parent_ && sibling < node->parent_->children_.size())
				{
					node = node->parent_->children_[sibling];
					++sibling;
				}
				else
				{
					node = nullptr;
				}
			}
		}
	}

	return node;
}

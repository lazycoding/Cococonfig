#include "stdafx.h"
#include "TraversalTree.h"
#include "ResourceNode.h"
void TraversalTree::Preorder(ResourceNode* treenode, Pred pred)
{
	if (treenode == nullptr)
	{
		return;
	}

	pred(treenode);

	for (auto it = treenode->children_.begin(); it != treenode->children_.end(); it++)
	{
		Preorder(*it, pred);
	}

	return;
}

void TraversalTree::Postorder(ResourceNode* treenode, Pred pred)
{
	if (treenode == nullptr)
	{
		return;
	}

	for (auto it = treenode->children_.begin(); it != treenode->children_.end(); it++)
	{
		Postorder(*it, pred);
	}

	pred(treenode);
}

#pragma once
#include <functional>
class ResourceNode;
class TraversalTree
{
public:
	typedef std::function<void(ResourceNode*)> Pred;

	static void Preorder(ResourceNode* treenode, Pred pred);

	static void Inorder(ResourceNode* treenode, Pred pred);

	static void Postorder(ResourceNode* treenode, Pred pred);

};


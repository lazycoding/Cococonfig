#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\ConfigLib\ResourceTree.h"
#include "..\ConfigLib\ResourceNode.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittest
{
	TEST_CLASS(TreeTest)
	{
	public:
		
		TEST_METHOD(TestTreeCtor)
		{
			ResourceTree tree;
			{
				ResourceNode node("etc");
				auto root = tree.Insert(nullptr, node);
				//Assert::IsNotNull(root.get());

				ResourceNode node1("iip");
				auto iip = tree.Insert(root, node1);
				//Assert::IsNotNull(iip.get());

				ResourceNode node2("dev");
				auto dev = tree.Insert(root, node2);
				//Assert::IsNotNull(dev.get());


				ResourceNode node3("gui");
				auto gui = tree.Insert(root, node3);
				//Assert::IsNotNull(gui.get());


				ResourceNode node5("Environment", ResourceValue(), 1);
				Assert::AreEqual(false, node5.IsValueNode());
				auto env = tree.Insert(iip, node5);
				//Assert::IsNotNull(env.get());
				ResourceValue rv;
				rv.SetString("Admin");
				ResourceNode node4("User", rv, 2);
				Assert::AreEqual(true, node4.IsValueNode());
				tree.Insert(env, node4);
			}
		}

	};
}
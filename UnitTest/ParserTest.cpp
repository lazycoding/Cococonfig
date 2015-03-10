#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\ConfigLib\ClsidParser.h"
#include "..\ConfigLib\ResourceGenerator.h"
#include <functional>
#include <windows.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace unittest
{
	TEST_CLASS(ParserTest)
	{
	public:	
	
		TEST_METHOD(Parse)
		{			
			ClsidParser pa;			

			ResourceNode node;
			Assert::IsFalse(pa.Parse("", node));
			Assert::IsFalse(pa.Parse("\0\0\0\0", node));

			pa.Parse("[Environment]", node);
			Assert::AreEqual("Environment", node.Name().c_str());

			pa.Parse("A = \"我是中文\"", node);

			pa.Parse("ABC   =  123", node);
			Assert::AreEqual("ABC", node.Name().c_str());
			Assert::AreEqual(123, node.Value().GetInt());

			pa.Parse("DEF   =  0.5", node);
			Assert::AreEqual("DEF", node.Name().c_str());
			Assert::AreEqual(0.5, node.Value().GetFloat());// 

			pa.Parse("G  = TRUE", node);
			Assert::AreEqual("G", node.Name().c_str());			
			Assert::IsTrue(node.Value().GetBoolean());

			pa.Parse("G  = \"FALSE\"", node);
			Assert::IsFalse(node.Value().GetBoolean());

			pa.Parse("J = {100,   100,   100}", node);
			Assert::AreEqual("J", node.Name().c_str());
			Assert::AreEqual(RGB(100,100,100), (COLORREF)node.Value().GetColor());

			pa.Parse("J = {\"100\",   \"100\",   \"100\"}", node);
			Assert::AreEqual("J", node.Name().c_str());
			Assert::AreEqual(RGB(100, 100, 100), (COLORREF)node.Value().GetColor());

			pa.Parse("K  = {\"ABC\", \"DEV\"}", node);
			Assert::AreEqual("K", node.Name().c_str());
			Assert::AreEqual((int)ResourceValue::Array, (int)node.Value().GetType());
		}

	};
}
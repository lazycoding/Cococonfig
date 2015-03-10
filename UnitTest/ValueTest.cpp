#include "stdafx.h"
#include "CppUnitTest.h"
#include <functional>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
#include "..\ConfigLib\ResourceValue.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittest
{		
	TEST_CLASS(ResourceValueTest)
	{
	public:
		
		TEST_METHOD(TestInt)
		{
			ResourceValue v1;
			v1.SetInt(123);					
			Assert::AreEqual(123, v1.GetInt());			
		}

		TEST_METHOD(TestBool)
		{
			ResourceValue v1;
			v1.SetBoolean(true);
			Assert::AreEqual(true, v1.GetBoolean());
			v1.SetBoolean(false);
			Assert::AreEqual(false, v1.GetBoolean());
		}

		TEST_METHOD(TestFloat)
		{
			ResourceValue v;
			v.SetFloat(10.01);
			double d = v.GetFloat();
			Assert::AreEqual(10.01, d);
		}

		TEST_METHOD(TestString)
		{
			ResourceValue v;
			v.SetString("1235@!%%");
			auto str = v.GetString();
			Assert::AreEqual("1235@!%%", str.c_str());
		}

		TEST_METHOD(TestStringArray)
		{
			ResourceValue v;
			vector<string> array, ret;			
			array.push_back("ABC");
			array.push_back("DEF");
			v.SetStringArray(array);
			v.GetStringArray(ret);
			Assert::AreEqual(array.size(), ret.size());
			for (vector<string>::size_type i = 0; i < array.size(); i++)
			{
				Assert::AreEqual(array[i].c_str(), ret[i].c_str());
			}
		}

		TEST_METHOD(TestColor)
		{
			ResourceValue v;
			unsigned long clr = 0x00fff00;
			v.SetColor(clr);
			auto clr2 = v.GetColor();
			Assert::AreEqual(clr, clr2);
		}
		
	};
}
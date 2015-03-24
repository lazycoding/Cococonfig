#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ConfigLib/ResourceGenerator.h"
#include "../ConfigLib/ClsidParser.h"
#include <fstream>
#include <string>
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittest
{
	TEST_CLASS(GeneratorTest)
	{
	public:
		
		TEST_METHOD(GenTest)
		{
// 			ifstream f("..\\File\\chbroadcast.clsid");
// 			f.seekg(0, ios::end);
// 			size_t size = (size_t)f.tellg();
// 			string bytes;
// 			bytes.resize(size + 1);
// 			f.seekg(0, ios::beg);
// 			f.read(&bytes.front(), size);
// 			bytes[bytes.size()] = 0;
			ResourceGenerator g(make_shared<ClsidParser>());
			g.Path("..\\File\\chbroadcast.clsid");
			auto tree = g.GenerateResourceTree();
		}

	};
}
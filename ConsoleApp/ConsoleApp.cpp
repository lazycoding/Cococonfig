// ConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>
#include <fstream>
#include <iostream>
using namespace std;
#include "..\ConfigLib\ClsidParser.h"
#include "..\ConfigLib\ResourceGenerator.h"
#include "..\ConfigLib\ResourceTree.h"
#include "..\ConfigLib\TraversalTree.h"
#include "..\ConfigLib\StringUtils.h"
int _tmain(int argc, _TCHAR* argv[])
{
	{		
		ifstream f("..\\File\\chbroadcast.clsid");
		f.seekg(0, ios::end);
		size_t size = (size_t)f.tellg();
		string bytes;
		bytes.resize(size + 1);
		f.seekg(0, ios::beg);
		f.read(&bytes.front(), size);
		f.close();
		bytes[bytes.size()] = 0;
		ResourceGenerator g(make_shared<ClsidParser>());
		auto tree = g.GenerateResourceTree(bytes, ResourceType::Main);

		int level = 0;
		TraversalTree::Preorder(tree->Root(), [&](ResourceNode* node){
			if (node->IsValueNode())
			{
				cout << node->Name() << "=" << stringutils::tostring(node->Value()) << endl;
			}
			else if (node->LineNumber() != -1)
			{
				cout << "[" << node->Name() << "]" << endl;
			}					
		});
	}
	_CrtDumpMemoryLeaks();
	return 0;
}


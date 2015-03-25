#include "stdafx.h"
#include "XmlProperty.h"
#include <sstream>
using namespace std;

XmlProperty::XmlProperty()
{
}


XmlProperty::~XmlProperty()
{
}


std::string& XmlProperty::operator[](const std::string& key)
{
	return prop_[key];
}

std::string XmlProperty::ToString()
{
	string s = "<";
	for each(auto p in prop_)
	{
		s += p.first;
		s += "=";
		s += p.second;
		s += ",";
	}
	s[s.size() - 1] = '>';
	return s;
}

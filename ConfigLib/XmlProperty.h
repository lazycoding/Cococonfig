#pragma once
#include <string>
#include <unordered_map>
class XmlProperty
{
public:
	XmlProperty();
	~XmlProperty();

	std::string& operator[](const std::string& key);
	std::string ToString();
private:
	std::unordered_map<std::string, std::string> prop_;
};


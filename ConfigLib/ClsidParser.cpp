#include "stdafx.h"
#include "ClsidParser.h"
#include <string>
#include <vector>
#include <windows.h>
#include "StringUtils.h"
using namespace std;


ClsidParser::ClsidParser()
{
}


ClsidParser::~ClsidParser()
{
}

bool ClsidParser::Parse(const std::string& raw_value, ResourceNode& node)
{
	if (raw_value.empty() || raw_value[0] == '\0')
	{
		return false;
	}

	if (raw_value[0] == '/' && raw_value[1] == '/')
	{
		return false;
	}

	if (raw_value[0] == '-' && raw_value[1] == '-')
	{
		return false;
	}

	string name;
	if (raw_value[0] == '[' && raw_value[raw_value.length()-1] == ']')
	{
		name.assign(raw_value.begin() + 1, raw_value.end() - 1);
		node.Name(name);
		return true;
	}

	const char* c = raw_value.data();
	const char* data = c;
	int begin = -1;
	int end = 0;	
	string key;
	string value;
	while(c)
	{
		if (isalpha(*c))
		{
			if (begin == -1)
			{
				begin = c - data;
			}			
		}
		else if (isspace(*c))
		{			
			if (end == 0)
			{
				end = c - data;
			}	
		}
		else if (*c == '=')
		{
			key.assign(data + begin, data + end);
			begin = -1;
			end = -1;
			c++;
			while (c)
			{
				if (isspace(*c))
				{
					c++;
					continue;
				}

				if (*c == '"')
				{
					c++;
				}

#pragma region ArrayOrColor
				if (*c == '{')
				{
					ResourceValue v;
					begin = c - data + 1;
					while (*c != '}')
					{
						c++;
					}
					end = c - data;
					value.clear();
					value.assign(data + begin, data + end);
					vector<string> array;
					int splited = stringutils::SplitString(value, array, ",");
					vector<int> color;
					vector<string> strarray;
					if (splited > 0)
					{
						for (auto str : array)
						{
							string va = str;

							if (str[0] == '"')
							{
								auto pos = str.rfind('"');
								if (pos != string::npos && pos != 0)
								{
									va.assign(str.begin() + 1, str.begin() + pos);
								}
							}

							if ('0' <= va[0] && va[0] <= '9')
							{
								color.push_back(atoi(va.c_str()));
							}
							else
							{
								strarray.push_back(va);
							}
						}

						if (color.size() == 3)
						{
							v.SetColor(RGB(color[0], color[1], color[2]));							
							node.Name(key);
							node.Value(v);
							return true;
						}
						else if (strarray.size() > 0)
						{
							v.SetStringArray(strarray);							
							node.Name(key);
							node.Value(v);
							return true;
						}
					}
				}// end of array or color
#pragma endregion

#pragma region Number
				else if ( '0' <= *c && *c <= '9')
				{
					value.clear();
					end = raw_value.size() - (c - data);
					value.assign(c, c + end);
					ResourceValue v;
					if (value.find('.') != string::npos)
					{
						v.SetFloat(atof(value.c_str()));
					}
					else
					{
						v.SetInt(atoi(value.c_str()));
					}					
					node.Name(key);
					node.Value(v);
					return true;
				}
#pragma endregion	
				else
				{
					value.clear();
					end = raw_value.size() - (c - data);
					value.assign(c, c + end);
					ResourceValue v;
					stringutils::trim(value, [](int c_)->int{ return c_ == '"'; });
					int find = value.rfind('>');
					if (find != string::npos && value[0] == '<')
					{
						string str;
						str.assign(value.begin() + 1, value.begin() + find);
						vector<string> vs;
						stringutils::SplitString(str, vs, ",");
						XmlProperty prop;
						for each(auto i in vs)
						{
							string key;
							int sep = i.find('=');
							key = i.substr(0, sep);
							string val;
							val = i.substr(sep + 1);
							stringutils::trim(key);							
							stringutils::trim(val, [](int c_)->int{ return c_ == '"'; });
							prop[key] = val;
						}
						v.SetProperty(prop);						
					}
					else
					{			
						find = value.rfind('"');
						if (find != string::npos)
						{
							value = value.substr(0, find);
						}
						if (_stricmp(value.c_str(), "true") == 0)
						{
							v.SetBoolean(true);
						}
						else if (_stricmp(value.c_str(), "false") == 0)
						{
							v.SetBoolean(false);
						}
						else
						{
							v.SetString(value);
						}
					}
					
					node.Name(key);
					node.Value(v);
					return true;
				}														
				c++;
			}
		}
		c++;
	}

	return false;
}

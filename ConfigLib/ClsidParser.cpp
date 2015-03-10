#include "stdafx.h"
#include "ClsidParser.h"
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <cctype>
#include <windows.h>
using std::string;
using std::transform;
using std::vector;


// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

int SplitString(const std::string& orign, std::vector<std::string>& splited_strings, const std::string& spliter)
{
	string::size_type off = 0;
	string::size_type find_position = orign.find(spliter, off);
	string stemp;
	while (find_position != string::npos)
	{
		stemp = orign.substr(off, find_position - off);
		trim(stemp);
		splited_strings.push_back(stemp);
		off = find_position;
		off += spliter.length();
		find_position = orign.find(spliter, off);
	}
	if (off < orign.length())
	{
		stemp = orign.substr(off, orign.length() - off);
		trim(stemp);
		splited_strings.push_back(stemp);
	}
	return splited_strings.size();
}

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
					int splited = SplitString(value, array, ",");
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
					auto find = value.rfind('"');
					if (find != string::npos)
					{
						value.erase(find, value.size() - find);
					}
					ResourceValue v;
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

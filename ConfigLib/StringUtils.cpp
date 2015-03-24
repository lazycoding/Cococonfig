#include "stdafx.h"
#include "StringUtils.h"
#include <windows.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <functional>
#include "ResourceValue.h"
using namespace std;
namespace stringutils
{
	std::string format(const char *fmt, ...)
	{
		std::string strResult = "";
		if (NULL != fmt)
		{
			va_list marker = NULL;
			va_start(marker, fmt);                            //初始化变量参数 
			size_t nLength = _vscprintf(fmt, marker) + 1;    //获取格式化字符串长度
			std::vector<char> vBuffer(nLength, '\0');        //创建用于存储格式化字符串的字符数组
			int nWritten = _vsnprintf_s(&vBuffer[0], vBuffer.size(), nLength, fmt, marker);
			if (nWritten > 0)
			{
				strResult = &vBuffer[0];
			}
			va_end(marker);                                    //重置变量参数
		}
		return strResult;
	}
	std::string tostring(const ResourceValue& value)
	{
		auto type_ = value.GetType();
		if (type_ == ResourceValue::String)
		{
			return value.GetString();
		}

		if (type_ == ResourceValue::Array)
		{
			string ret = "{";
			vector<string> array;
			value.GetStringArray(array);
			for (auto it = array.begin(); it != array.end(); it++)
			{
				ret += "\"";
				ret += *it;				
				ret += "\",";
			}			
			ret = ret.substr(0, ret.size() - 1);
			ret += "}";
			return ret;
		}

		if (type_ == ResourceValue::Boolean)
		{
			return value.GetBoolean() ? "TRUE" : "FALSE";
		}

		if (type_ == ResourceValue::Integer)
		{
			std::stringstream s;
			s << value.GetInt();
			return s.str();
		}

		if (type_ == ResourceValue::Float)
		{
			std::stringstream s;
			s << value.GetFloat();
			return s.str();
		}

		if (type_ == ResourceValue::Color)
		{

			auto c = value.GetColor();
			int r = GetRValue(c);
			int g = GetGValue(c);
			int b = GetBValue(c);

			string ret = format("{%d,%d,%d}", r, g, b);

			return ret;
		}

		if (type_ == ResourceValue::Prop)
		{
			auto prop = value.GetProperty();
			return prop.ToString();
		}

		return "unknown";
	}

	std::string ReadFromFile(const std::string& path)
	{
		ifstream fs(path);
		fs.seekg(0, ios::end);
		size_t size = (size_t)fs.tellg();
		string bytes;
		bytes.resize(size + 1);
		fs.seekg(0, ios::beg);
		fs.read(&bytes.front(), size);
		fs.close();
		bytes[bytes.size()] = 0;
		rtrim(bytes, [](int c_)->int{ return c_ == '\0'; });
		return bytes;
	}


	// trim from start	
	std::string &ltrim(std::string &s, TrimPred pred) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(pred))));
		return s;
	}

	// trim from end
	std::string &rtrim(std::string &s, TrimPred pred) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(pred))).base(), s.end());
		return s;
	}

	// trim from both ends
	std::string &trim(std::string &s, TrimPred pred) {
		return ltrim(rtrim(s, pred), pred);
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

}

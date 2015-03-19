#include "stdafx.h"
#include "StringUtils.h"
#include <windows.h>
#include <vector>
#include <sstream>
#include "ResourceValue.h"
using std::string;
using std::vector;
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

			ret.replace(ret.rbegin().base(), ret.end(), "}");
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

		return "unknown";
	}

}

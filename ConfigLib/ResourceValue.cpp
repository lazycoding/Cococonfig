#include "stdafx.h"
#include "ResourceValue.h"
#include <sstream>
#include <Windows.h>
using namespace std;

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
		if (nWritten>0)
		{
			strResult = &vBuffer[0];
		}
		va_end(marker);                                    //重置变量参数
	}
	return strResult;
}

ResourceValue::~ResourceValue()
{
	FreeMemory();
}

ResourceValue::ResourceValue()
	:type_(Empty)
{
}

ResourceValue::ResourceValue(const ResourceValue& rvalue)
{
	type_ = rvalue.type_;

	if (rvalue.type_ == String)
	{
		value_.stringVal = new std::string(*rvalue.value_.stringVal);
	}
	else if (rvalue.type_ == Array)
	{
		value_.arrayVal = new std::vector<std::string>();
		value_.arrayVal->resize(rvalue.value_.arrayVal->size());
		value_.arrayVal->assign(rvalue.value_.arrayVal->begin(), rvalue.value_.arrayVal->end());
	}
	else if (rvalue.type_ == Integer)
	{
		value_.intVal = rvalue.value_.intVal;
	}
	else if (rvalue.type_ == Boolean)
	{
		value_.boolVal = rvalue.value_.boolVal;
	}
	else if (rvalue.type_ == Color)
	{
		value_.colorVal = rvalue.value_.colorVal;
	}
	else if (rvalue.type_ == Float)
	{
		value_.floatVal = rvalue.value_.floatVal;
	}
}

int ResourceValue::GetInt() const
{
	if (type_ == Integer)
	{
		return value_.intVal;
	}
	throw std::runtime_error("Type isn't integer!");
}

void ResourceValue::SetInt(int value)
{
	FreeMemory();
	type_ = Integer;
	value_.intVal = value;
}

bool ResourceValue::GetBoolean() const
{
	if (type_ == Boolean)
	{		
		return value_.boolVal;
	}
	throw std::runtime_error("Type isn't boolean");
}

void ResourceValue::SetBoolean(bool value)
{
	FreeMemory();
	type_ = Boolean;
	value_.boolVal = value;
}

double ResourceValue::GetFloat() const
{
	if (type_ == Float)
	{
		return value_.floatVal;
	}
	throw std::runtime_error("Type isn't float or double");
}

void ResourceValue::SetFloat(double value)
{
	FreeMemory();
	type_ = Float;
	value_.floatVal = value;
}

std::string ResourceValue::GetString() const
{
	if (type_ == String)
	{
		if (value_.stringVal == nullptr)
		{
			throw runtime_error("Unexpected error!");
		}
		return *value_.stringVal;
	}
	throw std::runtime_error("Type isn't string");
}

void ResourceValue::SetString(const string& value)
{	
	FreeMemory();
	value_.stringVal = new	string(value);
	type_ = String;
}

int ResourceValue::GetStringArray(vector<string>& strings) const
{
	if (type_ == Array && value_.arrayVal)
	{		
		strings.clear();
		strings.resize(value_.arrayVal->size());
		strings.assign(value_.arrayVal->begin(), value_.arrayVal->end());

 		return strings.size();
	}
	throw std::runtime_error("Type isn't array");
}

void ResourceValue::SetStringArray(const vector<string>& array)
{
	FreeMemory();

	if (type_ == Array)
	{
		delete value_.arrayVal;
	}
	type_ = Array;
	value_.arrayVal = new vector<string>(array);
}

void ResourceValue::SetColor(unsigned long value)
{
	FreeMemory();
	type_ = Color;	
	value_.colorVal = value;
}

unsigned long ResourceValue::GetColor() const
{
	if (type_ == Color)
	{
		return value_.colorVal;

		throw std::runtime_error("Can't convert string to color");
	}
	throw std::runtime_error("Type isn't color");
}


ResourceValue::Type ResourceValue::GetType() const
{
	return type_;
}

void ResourceValue::FreeMemory()
{
	if (type_ == String)
	{
		delete value_.stringVal;
		value_.stringVal = nullptr;
	}
	if (type_ == Array)
	{
		delete value_.arrayVal;
		value_.arrayVal = nullptr;
	}
	type_ = Empty;
}

ResourceValue& ResourceValue::operator=(const ResourceValue& rvalue)
{
	if (this == &rvalue)
	{
		return *this;
	}

	if (type_ == String)
	{
		delete value_.stringVal;
		value_.stringVal = nullptr;
	}

	if (type_ == Array)
	{
		delete value_.arrayVal;
		value_.arrayVal = nullptr;
	}

	type_ = rvalue.type_;

	if (rvalue.type_ == String)
	{
		value_.stringVal = new std::string(*rvalue.value_.stringVal);
	}
	else if (rvalue.type_ == Array)
	{
		value_.arrayVal = new std::vector<std::string>();
		value_.arrayVal->resize(rvalue.value_.arrayVal->size());
		value_.arrayVal->assign(rvalue.value_.arrayVal->begin(), rvalue.value_.arrayVal->end());
	}
	else if (rvalue.type_ == Integer)
	{
		value_.intVal = rvalue.value_.intVal;
	}
	else if (rvalue.type_ == Boolean)
	{
		value_.boolVal = rvalue.value_.boolVal;
	}
	else if (rvalue.type_ == Color)
	{
		value_.colorVal = rvalue.value_.colorVal;
	}
	else if (rvalue.type_ == Float)
	{
		value_.floatVal = rvalue.value_.floatVal;
	}

	return *this;
}

string ResourceValue::ToString() const
{
	if (type_ == String)
	{
		return *value_.stringVal;
	}

	if (type_ == Array)
	{
		string ret = "{";
		for (auto it = begin(*value_.arrayVal); it != end(*value_.arrayVal); it++)
		{
			ret += "\"";
			ret += *it;
			ret += "\",";			
		}
		
		ret.replace(ret.rbegin().base(), ret.end(), "}");
		return ret;
	}

	if (type_ == Boolean)
	{		
		return value_.boolVal ? "TRUE" : "FALSE";
	}

	if (type_ == Integer)
	{
		stringstream s;
		s << value_.intVal;
		return s.str();
	}

	if (type_ == Float)
	{
		stringstream s;
		s << value_.floatVal;
		return s.str();
	}

	if (type_ == Color)
	{

		int r = GetRValue(value_.colorVal);
		int g = GetGValue(value_.colorVal);
		int b = GetBValue(value_.colorVal);

		string ret = format("{%d,%d,%d}", r, g, b);

		return ret;
	}

	return "unknown";
}
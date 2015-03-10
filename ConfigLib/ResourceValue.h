#pragma once
#include <string>
#include <vector>


class ResourceValue
{
public:
	enum Type{ Empty, Boolean, Integer, Float, String, Array, Color, Url, Custom };

	ResourceValue();

	ResourceValue(const ResourceValue& rvalue);

	ResourceValue& operator=(const ResourceValue& rvalue);

	~ResourceValue();

	int GetInt() const;

	void SetInt(int value);

	bool GetBoolean() const;

	void SetBoolean(bool value);

	double GetFloat() const;

	void SetFloat(double value);

	std::string GetString() const;

	void SetString(const std::string& value); //

	int GetStringArray(std::vector<std::string>& strings) const;

	unsigned long GetColor() const;  //COLORREF <=> unsigned long

	void SetColor(unsigned long value);
	
	void SetStringArray(const std::vector<std::string>& array);

	Type GetType() const;
	
private:
	void FreeMemory();

	union ValueUnion
	{
		bool boolVal;
		int  intVal;
		unsigned long colorVal;
		double floatVal;		
		std::string* stringVal;
		std::vector<std::string>* arrayVal;
	}value_;

	Type type_;
};

#include "parser.h"

#include <string>

Parser::Parser(std::vector<char>& file)
{
	cur = file.begin();
	end = file.end();
}

bool Parser::readDouble(double& val, std::string& del)
{
	std::string str;

	readString(str, del);

	try
	{
		val = stod(str);
	}
	catch (std::invalid_argument ex)
	{
		return 0;
	}

	return 1;
}

bool Parser::readFloat(float& val, std::string& del)
{
	std::string str;

	readString(str, del);

	try
	{
		val = stof(str);
	}
	catch (std::invalid_argument ex)
	{
		return 0;
	}

	return 1;
}

bool Parser::readInt(int& val, std::string& del)
{
	std::string str;

	readString(str, del);

	try
	{
		val = stoi(str);
	}
	catch (std::invalid_argument ex)
	{
		return 0;
	}

	return 1;
}

void Parser::readString(std::string& str, std::string& del)
{
	str = "";

	if (cur >= end)
		return;
	
	for (; cur < end && del.find(*cur) != std::string::npos; ++cur) { }

	std::vector<char>::iterator strBeg = cur;

	for (; cur < end && del.find(*cur) == std::string::npos; ++cur) { }

	str.reserve(cur - strBeg);

	for (; strBeg < cur; ++strBeg)
		str += *strBeg;
}

bool Parser::skip(std::string& chars)
{
	if (cur >= end || chars.find(*cur) == std::string::npos)
		return 0;

	for (; cur < end && chars.find(*cur) == std::string::npos; ++cur) { }

	return 1;
}

void Parser::skipLine(std::string& chars)
{
	if (cur >= end)
		return;

	for (++cur; cur < end && chars.find(*cur) == std::string::npos; ++cur) { }
	for (++cur; cur < end && chars.find(*cur) != std::string::npos; ++cur) { }
}

bool Parser::eof()
{
	return cur == end;
}

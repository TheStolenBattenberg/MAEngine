#pragma once

#include <vector>

class Parser
{
public:
	Parser(std::vector<char>& file);

	bool readDouble(double& val, std::string& del = std::string("\r\n \t"));
	bool readFloat(float& val, std::string& del = std::string("\r\n \t"));
	bool readInt(int& val, std::string& del = std::string("\r\n \t"));
	void readString(std::string& str, std::string& del = std::string("\r\n \t"));
	bool skip(std::string& chars = std::string(" \t"));
	void skipLine(std::string& chars = std::string("\r\n"));
	bool eof();

private:
	std::vector<char>::iterator cur;
	std::vector<char>::iterator end;
};

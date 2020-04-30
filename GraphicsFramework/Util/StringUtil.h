#pragma once
#include "../Global.h"
#include <fstream>
#include <string.h>

namespace GF
{
	inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v") { s.erase(s.find_last_not_of(t) + 1); return s; }
	inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v") { s.erase(0, s.find_first_not_of(t)); return s; }
	inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v") { return ltrim(rtrim(s, t), t);	}

	void tokenize_string(std::string& str, int letters_per_line, std::string token);
	void eraseSubStr(std::string& mainStr, const std::string& toErase);
	void RemoveFromString(std::string& str, std::string chars_to_remove);
	void ReplaceStringInPlace(std::string& subject, const std::string& search,
	                          const std::string& replace);

	std::string splitStringAt(std::string& str, int index);
	std::string splitStringAt(std::string& str, char token);

	std::string toUpper(std::string str);
	std::string toLower(std::string str);
}
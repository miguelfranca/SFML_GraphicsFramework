#pragma once
#include "../Global.h"
#include <fstream>
#include <string.h>

namespace GF {
	class String {
	public:
		static void tokenize_string(std::string& str, int letters_per_line, std::string token);
		static void eraseSubStr(std::string& mainStr, const std::string& toErase);
		static void RemoveFromString(std::string& str, std::string chars_to_remove);
		static void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
		static std::string splitStringAt(std::string& str, int index);
		static std::string toupper(std::string str);
		static std::string tolower(std::string str);
	};
}
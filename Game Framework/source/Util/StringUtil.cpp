#include "../../headers/Util/StringUtil.h"

namespace GF {

	void String::tokenize_string(std::string& str, int letters_per_line, std::string token) {

		std::string final_str;
		bool flag = false;
		for (int i = 0; i < str.size(); i++) {
			if (i % letters_per_line == 0 && i != 0) flag = true;
			if (str[i] == ' ' && flag) { final_str += token; flag = false; }
			final_str += str[i];
		}

		str = final_str;
	}


	void String::RemoveFromString(std::string& str, std::string chars_to_remove) {

		for (char c : chars_to_remove) {
			str.erase(remove(str.begin(), str.end(), c), str.end());
		}
	}


	void String::eraseSubStr(std::string& mainStr, const std::string& toErase) {
		// Search for the substring in string
		size_t pos = mainStr.find(toErase);

		if (pos != std::string::npos)
		{
			// If found then erase it from string
			mainStr.erase(pos, toErase.length());
		}
	}


	void String::ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
	}


	std::string String::splitStringAt(std::string& str, int index) {

		std::string temp = "";
		std::string split = "";

		for (int i = 0; i < str.size(); i++) {
			if (i < index) temp += str[i];
			else split += str[i];
		}

		str = temp;

		return split;
	}


	std::string String::toupper(std::string str) {

		char c;
		std::string temp = "";

		for (int i = 0; i < str.size(); i++)
		{
			c = str[i];
			temp += toupper(std::to_string(c));
		}

		return temp;
	}


	std::string String::tolower(std::string str) {

		char c;
		std::string temp = "";

		for (int i = 0; i < str.size(); i++)
		{
			c = str[i];
			temp += tolower(std::to_string(c));
		}

		return temp;
	}
}

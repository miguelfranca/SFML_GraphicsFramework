#pragma once

#include <string>
#include "../Global.h"
#include <filesystem>
#include <fstream>

namespace GF {
	class File {
	public:
		static void replaceAllInFile(std::string file, std::string toReplace, std::string newStr);
		static void replaceInFile(std::string file, std::string toReplace, std::string newStr, int position);
		static void replaceLineInFile(std::string file, std::string toReplace, int position);
		static void copyTo_From(std::string to, std::string from);
		static void deleteFromFile(std::string file, std::string todelete);
		static void put_in_file(std::string file, std::string str);
		static void directory_iterator(std::string directory);
		static void createFile(std::string file);
	};
}

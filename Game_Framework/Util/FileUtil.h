#pragma once

#include <string>
#include "../Global.h"
#include <experimental/filesystem>
#include <fstream>

namespace GF
{
	void replaceAllInFile(std::string file, std::string toReplace, std::string newStr);
	void replaceInFile(std::string file, std::string toReplace, std::string newStr, int position);
	void replaceLineInFile(std::string file, std::string toReplace, int position);
	void copyTo_From(std::string to, std::string from);
	void deleteFromFile(std::string file, std::string todelete);
	void put_in_file(std::string file, std::string str);
	std::vector<std::string> directory_iterator(const std::string& directory);
	void createFile(std::string file);
	void moveFile(std::string old_path, std::string new_path);
	inline bool existsFile(const std::string& name)
	{
		std::ifstream f(name.c_str());
		return f.good();
	}
}

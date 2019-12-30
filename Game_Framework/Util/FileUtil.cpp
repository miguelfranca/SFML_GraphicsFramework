#include "FileUtil.h"
#include "StringUtil.h"
#include <iostream>

namespace GF
{

	void moveFile(std::string old_path, std::string new_path)
	{
#ifdef __linux__
		std::string command = "mv \"" + old_path + "\" \"" + new_path + "\"";
		int status = system(command.c_str());
#elif _WIN32
		std::string command = "move \"" + old_path + "\" \"" + new_path + "\"";
		int status = system(command.c_str());
#endif
	}

	void replaceAllInFile(std::string file, std::string toReplace, std::string newStr)
	{

		std::ifstream replace(file);
		std::ofstream temp("temp.txt");

		if (replace.fail() || temp.fail()) {
			std::cout << "Error opening file temp.txt or " + file << std::endl;
		}

		std::string strTemp;

		while (getline(replace, strTemp)) {
			if (strTemp == toReplace) {
				strTemp = newStr;
			}

			strTemp += "\n";
			temp << strTemp;
		}

		replace.close();
		temp.close();

		copyTo_From(file, "temp.txt");

		std::remove("temp.txt");
	}


	void replaceInFile(std::string file, std::string toReplace, std::string newStr, int position)
	{

		std::ifstream replace(file);
		std::ofstream temp("temp.txt");

		if (replace.fail() || temp.fail()) {
			std::cout << "Error opening file temp.txt or " + file << std::endl;
		}

		std::string strTemp;

		bool flagged = false;
		int found = 0;

		while (getline(replace, strTemp)) {
			if (strTemp == toReplace && !flagged) {
				if (++found == position) {
					strTemp = newStr;
					flagged = true;
				}
			}

			strTemp += "\n";
			temp << strTemp;
		}

		replace.close();
		temp.close();

		copyTo_From(file, "temp.txt");

		std::remove("temp.txt");
	}


	void replaceLineInFile(std::string file, std::string toReplace, int position)
	{

		std::ifstream replace(file);
		std::ofstream temp("temp.txt");

		if (replace.fail() || temp.fail()) {
			std::cout << "Error opening file temp.txt or " + file << std::endl;
		}

		std::string strTemp;

		bool flagged = false;
		int counter = 1;

		while (getline(replace, strTemp)) {
			if (counter++ == position && !flagged) {
				strTemp = toReplace;
				flagged = true;
			}

			strTemp += "\n";
			temp << strTemp;
		}

		replace.close();
		temp.close();

		copyTo_From(file, "temp.txt");

		std::remove("temp.txt");
	}


	void deleteFromFile(std::string file, std::string todelete)
	{

		std::ifstream replace(file);
		std::ofstream temp("temp.txt");

		if (replace.fail() || temp.fail()) {
			std::cout << "Error opening file temp.txt or " + file << std::endl;
		}

		std::string strTemp;

		while (getline(replace, strTemp)) {
			if (strTemp != todelete) {
				strTemp += "\n";
				temp << strTemp;
			}
		}

		replace.close();
		temp.close();

		copyTo_From(file, "temp.txt");

		std::remove("temp.txt");
	}


	void copyTo_From(std::string to, std::string from)
	{

		std::ofstream aa(to);
		std::ifstream bb(from);

		std::string temp;

		while (getline(bb, temp)) {
			aa << temp + "\n";
		}

		aa.close();
		bb.close();
	}


	void put_in_file(std::string file, std::string str)
	{
		std::ofstream to_file;
		to_file.open(file, std::ios::in | std::ios::app);

		if (to_file.fail()) {
			std::cout << "failed to open " << file << std::endl;
			std::cin.get();
			exit(1);
		}

		to_file << str;
		to_file << "\n";
		to_file.close();
	}


	std::vector<std::string> directory_iterator(const std::string& directory)
	{
		std::vector<std::string> files;

		for (auto& p : std::experimental::filesystem::directory_iterator(directory))
			files.push_back(p.path().string());

		return files;
	}


	void createFile(std::string file)
	{
		std::ifstream b(file);

		if (!b.fail())
			std::cout << file << "already exists" << std::endl;
		else {
			std::ofstream a(file);
			a.close();
		}

		b.close();
	}
}


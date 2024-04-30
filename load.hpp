#pragma once
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

class Loader {
public:
	std::string title;
	std::string author;
	std::string desc;

	//loads act file title, author, and description and stores them in corresponding strings
	std::string LoadFile(bool abs_path, const char input[]);
	//loads act file to vector at corresponding indices
	void LoadActToMap(std::string cleaned_act, std::map<std::string, std::stringstream>& outVec);
private:
	void LoadTad(std::string& cleaned_act);
};
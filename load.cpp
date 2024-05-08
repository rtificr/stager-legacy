#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "main.hpp"
#include "load.hpp"
#include <regex>

//TAD descriptors storage
std::string title, author, desc;
//loads file with or without an absolute path, and the directory
std::string Loader::LoadFile(bool abs_path, const char input[]) {
	//act file stream
	std::ifstream infile;
	//used as buffer for loading chunks
	std::string instring;
	//stores the act file with newlines removed
	std::string cleaned_act;
	//stores the directory as a string for easy use
	std::string dir;
	//stores the directory as a string for easy use (no input/). used if stager was loaded by opening an act file
	std::string ez_dir;

	//if using relative path, path is input/PATH HERE.act
	if (!abs_path) {
		dir = "input/";
		dir += input;
		dir += ".act";
		
		ez_dir = input;
		ez_dir += ".act";
	}
	//if using absolute path, set directory to input and replace backslashes with forward slashes 
	else {
		dir = input;
		std::replace(dir.begin(), dir.end(), '\\', '/');
	}
	//open the file
	infile.open(dir);
	
	std::cout << "\nReading from " << dir << "...";

	if (!infile.is_open()) {
		infile.open(ez_dir);
	}
	if (!infile.is_open()) {
		std::cout << "Reading failed.\nCheck if file exists in the \"input\" folder. Try again.\n";
		start();
	}
	else {
		//cleans up the act file by removing newlines
		while (std::getline(infile, instring)) {
			if (!instring.empty())
				cleaned_act.append(instring);
		}

		std::cout << "Reading done!\n";
		std::cout << "Loading descriptors...\n\n";

		LoadTad(cleaned_act);

		return cleaned_act;
	}
}
//takes act as string and converts it to map of stringstreams
void Loader::LoadActToMap(std::string cleaned_act, std::map<std::string, std::stringstream>& outVec) {
	//temporarily stores act chunks for processing
	std::string buffer;
	//used to getline from act
	std::stringstream cleaned_act_stream(cleaned_act);
	//gets line up to the closing bracket
	while (std::getline(cleaned_act_stream, buffer, '}')) {
		//used for finding the index
		std::regex index_pattern(".*?\s*?(?=:)");
		//finds the index (includes the trailing colon)
		std::smatch index_match;
		//get question index, remove it from string, and add string to act at said index
		if (std::regex_search(buffer, index_match, index_pattern)) {
			std::string index = index_match[0];

			//used for cleaning up the beginning
			std::regex cleanup_pattern(R"(^\s*.*?\s*:\s*)");

			buffer = std::regex_replace(buffer, cleanup_pattern, "");

			outVec[index].str(buffer);

			//std::cout << ":" << index << "=> " << buffer << '\n';
		}
	}
}
//parse and load TAD descriptors from the act file
void Loader::LoadTad(std::string& cleaned_act) { 
	//regex patterns for matching tad descriptors
	std::regex  p_title(R"((^|\\)T\s*:\s*(.*?)(\\))", std::regex_constants::icase);
	std::regex p_author(R"((^|\\)A\s*:\s*(.*?)(\\))", std::regex_constants::icase);
	std::regex   p_desc(R"((^|\\)D\s*:\s*(.*?)(\\))", std::regex_constants::icase);
	//stores the tad descriptors as regex matches
	std::smatch r_title;
	std::smatch r_author;
	std::smatch r_desc;
	//stores full descriptors (with T/A/D: and \)
	std::string f_title;
	std::string f_author;
	std::string f_desc;

	//locates and assigns descriptors to strings, as well as disposes of them in the act
	if (std::regex_search(cleaned_act, r_title, p_title)) {
		title = r_title[2];
		cleaned_act = std::regex_replace(cleaned_act, p_title, "");
	}
	else std::cout << "Noncritical error: Title not found!\n";

	if (std::regex_search(cleaned_act, r_author, p_author)) {
		author = r_author[2];
		cleaned_act = std::regex_replace(cleaned_act, p_author, "");
	}
	else std::cout << "Noncritical error: Author not found!\n";

	if (std::regex_search(cleaned_act, r_desc, p_desc)) {
		desc = r_desc[2];
		cleaned_act = std::regex_replace(cleaned_act, p_desc, "");
	}
	else std::cout << "Noncritical error: Description not found!\n";
}
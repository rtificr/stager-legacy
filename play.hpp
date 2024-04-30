#pragma once
#include <map>
#include <string>

class Player {
public:
	void Run(std::map<std::string, std::stringstream>& act);
	int TakeChoice();
private:
	bool IsNumber(const std::string& s);
	void Poll(std::string index, std::map<std::string, std::stringstream>& act);
};

class Choice {
public:
	std::string choice;
	std::string destination;
};
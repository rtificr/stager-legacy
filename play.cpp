#include "play.hpp"
#include "main.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

#include <Windows.h>

//runs the act file
void Player::Run(std::map<std::string, std::stringstream>& act) {
	std::cout << "Beginning...\n\n";
	//polls act file at index 1.
	Poll("start", act);
}

//does act parsing logic
void Player::Poll(std::string index, std::map<std::string, std::stringstream>& act) {
	//gets string from act at passed index
	std::string current_chunk_string = act[index].str();
	//stores the question
	std::string question;
	//used for getline-ing. i would set it directly from the act map, but cpp doesn't like that
	std::stringstream current_chunk(current_chunk_string);
	//used as a buffer for loading things from the current chunk
	std::string buffer;
	//stores the current choice. contains the text and the destination
	Choice choice;
	//stores all choices
	std::vector<Choice> choices;
	//parse out the question
	std::getline(current_chunk, question, '{');
	std::cout << '\n' << question << '\n';
	Sleep(60);
	std::cout << "\n";
	Sleep(60);
	//constantly read until a backslash until the end of file.
	while (std::getline(current_chunk, buffer, '\\')) {
		std::regex whitespace_pattern(R"(^\s*)");
		buffer = std::regex_replace(buffer, whitespace_pattern, "");
		choice.choice = buffer;
		std::getline(current_chunk, buffer, '\\');
		choice.destination = buffer;
		try {
			act.at(buffer);
		}
		catch (std::out_of_range& e) {
			choice.valid = false;
			choices.push_back(choice);
			continue;
		}
		choice.valid = true;
		choices.push_back(choice);
	}

	//print all choices. printing everything will always 150ms.
	int read_iterations = 0;
	for (Choice i_choice : choices) {
		read_iterations++;
		Sleep(150 / choices.size());
		if (i_choice.valid)
			std::cout << read_iterations << ": " << i_choice.choice << '\n';
		else
			std::cout << "Noncritical error: Choice #" << read_iterations << " has an invalid destination!\n";
	}

	Sleep(60);

	//takes choice only if there are choices
	if (choices.size() != 0) {
		std::cout << "\n\n";
		std::cout << "Take your choice:\n";
		int choice = TakeChoice() - 1;
		//checks if valid choice. if not, try again.
		if (choice < 0 || choice > choices.size() - 1) {
			std::cout << "Invalid choice. Try again.\n";
			Poll(index, act);
		}
		//polls at the choice's destination
		else Poll(choices[choice].destination, act);
	}
	//if there are no choices, treat as the end.
	else std::cout << "END\n\n";

	std::cout << "Restarting...";
	start();
}

//takes choice (duh)
int Player::TakeChoice() {
	std::string input;
	//loads user input into string
	std::cout << "> ";
	std::cin >> input;
	int choice;

	choice = round(std::stod(input));
	return choice;
}
//is a string a number?
bool Player::IsNumber(const std::string& s) {
	std::istringstream iss(s);
	double dummy;
	return iss >> dummy && iss.eof();
}

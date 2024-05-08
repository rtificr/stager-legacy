#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "main.hpp"
#include "load.hpp"
#include "play.hpp"
#include <map>

int main(int argc, char* argv[])
{   
    std::cout << "   _____ _______       _____      _____  \n";
    std::cout << "  / ____|__   __|/\\   / ____|    |  __ \\ \n";
    std::cout << " | (___    | |  /  \\ | |  __  ___| |__) |\n";
    std::cout << "  \\___ \\   | | / /\\ \\| | |_ |/ _ \\  _  / \n";
    std::cout << "  ____) |  | |/ ____ \\ |__| |  __/ | \\ \\ \n";
    std::cout << " |_____/   |_/_/    \\_\\_____|\\___|_|  \\_\\\n";

    std::cout << "v1.2.4\n\n";
    std::cout << "Static Text-based Adventure Game Runtime\n\n";

    /*
    std::filesystem::path executable_path = std::filesystem::absolute(argv[0]).parent_path();
    std::cout << "CURRENT WORKING DIRECTORY: " << executable_path << '\n';
    std::filesystem::current_path(executable_path);
    std::cout << "NEW WORKING DIRECTORY: " << std::filesystem::current_path() << '\n';
    */

    //if loaded from double-clicking on ACT file, run with that file
    if (argc == 2) {
        return start(argv[1]);
    }
    //if not, start and ask user for file input
    else {
        return start();
    }
}

int start() {
    std::cout << "\nLoad act by name (No file extension):\n> ";
    //the map representation of the act file
    std::map<std::string, std::stringstream> act;
    //stores user's selected directory
    std::string selected_directory;
    //the loader and player objects
    Loader loader;
    Player player;
    //set selected directory to the user input
    std::cin >> selected_directory;
    //load file with a relative path that is the user's selected directory
    std::string act_stream(loader.LoadFile(false, selected_directory.c_str()));
    //if act file is empty, return 2
    if (act_stream == "") return 2;
    //display TAD descriptors
    std::cout << "===========================================================\n";
    std::cout << "\"" << loader.title << "\"" << " by " << loader.author << '\n';
    std::cout << "Description:\n" << loader.desc << "\n";
    std::cout << "===========================================================\n";
    std::cout << "___________________________________________________________\n\n";
    //load the act stream to the act map
    loader.LoadActToMap(act_stream, act);
    //run the act map
    player.Run(act);
    //return 0 (everything OK)
    return 0;
}

int start(std::string directory) {
    //the map representation of the act file
    std::map<std::string, std::stringstream> act;
    //the loader and player objects
    Loader loader;
    Player player;
    //load file with an absolute path, using the path given by argv[1]
    std::string act_stream(loader.LoadFile(true, directory.c_str()));
    //if act file is empty, return 2
    if (act_stream == "") return 2;
    //display TAD descriptors
    std::cout << "===========================================================\n";
    std::cout << "\"" << loader.title << "\"" << " by " << loader.author << '\n';
    std::cout << "Description:\n" << loader.desc << "\n";
    std::cout << "===========================================================\n";
    std::cout << "___________________________________________________________\n\n";
    //load the act stream to the act map
    loader.LoadActToMap(act_stream, act);
    //run the act map
    player.Run(act);
    //return 0 (everything OK)
    return 0;
}
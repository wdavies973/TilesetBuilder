// TilesetBuilder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <experimental\filesystem>
#include <map>
#include <regex>
namespace fs = std::experimental::filesystem;

void build(std::map<std::string, std::string> map, std::string output);
bool isNumber(const std::string & s);

int main()
{
	std::cout << "Welcome to the Mars! TileSet Builder.\nadd [tileset-name] [C:\\Users\\Will Davies\\Desktop\\Mars Asset\\...]\nreset\nbuild\n";

	std::map <std::string, std::string> map;

	while (true) {
		std::string input;

		std::getline(std::cin, input);

		// Split into tokens,
		std::istringstream buf(input);
		std::istream_iterator<std::string> beg(buf), end;
		std::vector<std::string> tokens(beg, end);

		if (tokens[0] == "add") {
			map.insert(std::make_pair(tokens[1], "C:\\Users\\Will Davies\\Desktop\\Mars Assets\\"+tokens[2]));
		}
		else if (input == "reset") {
			map.clear();
		}
		else if (input == "build") {
			build(map, "C:\\Users\\Will Davies\\Desktop\\Mars Assets\\Textures");

		}
		else if (input == "end") {
			return 0;
		}
	}
}

// this function takes the folders (as specified by paths), loads all the images they contain,
// renames them, and moves them to the output directory
void build(std::map<std::string, std::string> map, std::string output) {
	std::map<std::string, std::string>::iterator it = map.begin();
	while (it != map.end())
	{
		std::cout << "Processing: " << it->second << std::endl;

		for (auto & p : fs::directory_iterator(it->second)) {
			fs::path file(p);

			if (!isNumber(file.stem().string())) continue;

			std::cout << p << std::endl;

			// delete file if it's there already
			fs::remove(output + "\\" + it->first + "_" + file.stem().string() + ".png");
			// copy file to output location
			fs::copy_file(p, output + "\\"+ it->first +"_"+ file.stem().string()+ ".png");
		}

		it++;
	}
}

bool isNumber(const std::string & src)
{
	std::regex e("^-?\\d+");
	if (std::regex_match(src, e)) return true;
	else return false;
}



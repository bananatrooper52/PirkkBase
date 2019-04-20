#pragma once

#include <fstream>
#include <string>

namespace Pirkk::Util {
	inline std::string loadFile(std::string location) {
		std::ifstream file;
		std::string output;

		file.open(location);
		if (file.is_open()) {
			while (!file.eof()) {
				std::string line;
				std::getline(file, line);
				output += line + "\n";
			}
		} else {
			printf("Could not open file: ");
			printf(location.c_str());
			printf("\n");
		}
		file.close();
		return output;
	}
}
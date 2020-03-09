#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

int main() {
	std::ifstream is("CONFIG");

	if (!is.is_open()) 
	{ std::cerr << "Failed to open file\n"; return EXIT_FAILURE; }
	
	std::string line;
	std::vector<std::string> strvec;
	while (std::getline(is, line)) {
		std::cout << "Processing line: '" << line << "'\n";

		strvec.clear();
		std::istringstream iss(line);
		std::copy(
				std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				std::back_inserter(strvec));
		std::cout << "number of strvec: " << strvec.size() << std::endl;

		if (strvec.size() == 0) { continue; } // skip empty line
		else if (strvec[0].find("#") == 0) { continue; }
		else if (strvec[0].find("//") == 0) { continue; }
		else if (strvec.size() != 3) { 
			std::cerr << "A line with a number of words not equal to 3\n"; 
			return EXIT_FAILURE;
		}

		for (size_t i=0; i<strvec.size(); ++i) {
			std::cout << strvec[i] << std::endl;
		}
	}

	is.close();
	return EXIT_SUCCESS;
}


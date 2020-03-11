#include <iostream>

#include "../include/param.h"

int main() {
	ParamFile paramFile;
	try {
		paramFile = ParamFile("CONFIG");
	} catch (const char *msg) {
		std::cerr << "[ERROR] Failed to construct ParamFile object\n";
		std::cerr << "[ERROR] Error message: '" << msg << "'\n";
		return EXIT_FAILURE;
	} catch (std::exception& e) {
		std::cerr << "[ERROR] Unexpected exception during ParamFile init\n";
		throw e;
		return EXIT_FAILURE;
	}	catch (...) {
		std::cerr << "[ERROR] Unexpected Error during ParamFile init\n";
		return EXIT_FAILURE;
	}
	std::cout << "query of 'Nx': " << paramFile.get_int("Nx") << std::endl;
	std::cout << "query of 'dx': " << paramFile.get_double("dx") << std::endl;
	std::cout << "query of 'Np': " << paramFile.get_long("Np") << std::endl;
	std::cout << "query of 'wf-file': " 
		<< paramFile.get_string("wf-file") << std::endl;

	return EXIT_SUCCESS;
}


#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iostream>

#include "../include/param.h"

ParamFile::ParamFile(const char *filename) {

	// Open and check if the file has been opened properly
	std::ifstream is(filename);
	if (!is.is_open()) 
	{ throw "Failed to open file: " + std::string(filename); }
	
	std::string line;
	std::vector<std::string> strvec;
	while (std::getline(is, line)) {
		
#ifdef DEBUG
		std::cout << "Processing line: '" << line << "'\n";
#endif
		strvec.clear();
		std::istringstream iss(line);
		std::copy(
				std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				std::back_inserter(strvec));
#ifdef DEBUG
		std::cout << "number of strvec: " << strvec.size() << std::endl;
#endif

		if (strvec.size() == 0) { continue; } // skip empty line
		else if (strvec[0].find("#") == 0) { continue; } // skip comment line
		else if (strvec[0].find("//") == 0) { continue; } // skip comment line
		else if (strvec.size() != 3) { 
			std::cerr << "[ERROR] A line should have three words but it doesn't.\n";
			std::exception e;
			throw e;
		}

		std::string namestr(strvec[0]), typestr(strvec[1]), valstr(strvec[2]);
#ifdef DEBUG
		std::cout 
			<< "name: " << namestr 
			<< ", type: " << typestr 
			<< ", value: " << valstr << std::endl;
#endif
		Param _param = { namestr, typestr, valstr };
		paramvec.push_back(_param);
//		paramvec.push_back(Param(namestr, typestr, valstr));
	}
	is.close();


	// Check uniqueness of parameters names
	std::vector<std::string> names;
	for (std::vector<Param>::iterator it=paramvec.begin(); 
			it != paramvec.end(); ++it) 
	{ names.push_back(it->name); }
	std::vector<std::string>::iterator last 
		= std::unique(names.begin(), names.end());
	if (last != names.end()) { 
		std::cerr << "There exists a duplicate in parameter names\n";
		std::exception e;
		throw e;
	}

	// Check whether the values are convertable to the prescribed type name
	std::vector<Param>::iterator it;
	for (it=paramvec.begin(); it != paramvec.end(); ++it) {
		if (it->type == "int") {
			int val;
			try { val = std::stoi(it->value, NULL); }
			catch (std::exception& e) { 
				std::cerr << "[ERROR] Failed to convert to an int: " 
					<< it->name << std::endl; 
				throw e;
			}
#ifdef DEBUG
			std::cout << "[ LOG ] int val == " << val << "\n";
#endif // DEBUG 
			params_int[it->name] = val;
		} else if (it->type == "double") {
			double val;
			try { val = std::stod(it->value, NULL); }
			catch (std::exception& e) { 
				std::cerr << "[ERROR] Failed to convert to a double: " 
					<< it->name << std::endl;
				throw e;
			}
#ifdef DEBUG
			std::cout << "[ LOG ] double val == " << val << "\n";
#endif // DEBUG 
			params_double[it->name] = val;
		} else if (it->type == "long") {
			long val;
			try { val = std::stol(it->value, NULL); }
			catch (std::exception& e) { 
				std::cerr << "[ERROR] Failed to convert to a long: " 
					<< it->name << std::endl;
				throw e;
			}
#ifdef DEBUG
			std::cout << "[ LOG ] long val == " << val << "\n";
#endif // DEBUG 
			params_long[it->name] = val;
		}
		else if ((it->type == "string") || (it->type == "str")) {
			params_str[it->name] = it->value;
		}
	}
}

int ParamFile::get_int(const char *name) {
	int _val;
	try { _val = params_int.at(name); }
	catch (std::out_of_range& e) {
		std::cerr << "[ERROR] No such parameter with name: " << name << std::endl; 
		throw e; 
	}
	catch (...) { 
		std::cerr << "[ERROR] Unexpected error during getting value of parameter: "
			<< name << std::endl; 
		std::exception e; throw e;
	}
	return _val;
}

double ParamFile::get_double(const char *name) {
	double _val;
	try { _val = params_double.at(name); }
	catch (std::out_of_range& e) {
		std::cerr << "[ERROR] No such parameter with name: " << name << std::endl; 
		throw e; 
	}
	catch (...) { 
		std::cerr << "[ERROR] Unexpected error during getting value of parameter: "
			<< name << std::endl; 
		std::exception e; throw e;
	}
	return _val;
}

long ParamFile::get_long(const char *name) {
	long _val;
	try { _val = params_long.at(name); }
	catch (std::out_of_range& e) {
		std::cerr << "[ERROR] No such parameter with name: " << name << std::endl; 
		throw e; 
	}
	catch (...) { 
		std::cerr << "[ERROR] Unexpected error during getting value of parameter: "
			<< name << std::endl; 
		std::exception e; throw e;
	}
	return _val;
}

std::string ParamFile::get_string(const char *name) {
	std::string _val;
	try { _val = params_str.at(name); }
	catch (std::out_of_range& e) {
		std::cerr << "[ERROR] No such parameter with name: " << name << std::endl; 
		throw e; 
	}
	catch (...) { 
		std::cerr << "[ERROR] Unexpected error during getting value of parameter: "
			<< name << std::endl; 
		std::exception e; throw e;
	}
	return _val;
}

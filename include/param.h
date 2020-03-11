#ifndef _PARAM_H_
#define _PARAM_H_

#include <string>
#include <vector>
#include <map>

struct Param { std::string name, type, value; };

class ParamFile {

	std::vector<Param> paramvec;
	std::string *names;

	// A set of parameter dictionaries for each data type
	std::map<std::string,int> params_int;
	std::map<std::string,long> params_long;
	std::map<std::string,double> params_double;
	std::map<std::string,std::string> params_str;

public:
	ParamFile() {};
	ParamFile(const char *filename);
	size_t size() { return paramvec.size(); };

	int get_int(const char *name);
	double get_double(const char *name);
	std::string get_string(const char *name);
	long get_long(const char *name);
};

#endif // _PARAM_H_

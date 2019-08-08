#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>
#include <type_traits>

#include "DCDefinition.h"
//#include "thirdparty/rapidjson/document.h"
//#include "thirdparty/rapidjson/prettywriter.h"

using namespace std;

class DocumentData;

class DCComponent
{
private:
	std::string componentType;
    DocumentData *ddata;
//    rapidjson::Document data;

public:
	DCComponent(const std::string &CompType);
	DCComponent(const std::string &CompType, const std::string &Json);
	std::string get_type();
	void set_value(const std::string &Field, const std::string &Value);  // string type default
	// other accepted types are string, int, double
    void set_value(const std::string &Field, const std::string &Value, const std::string &ValueType);
	void set_value_int(const std::string &Field, const int &Value);
	void set_value_dbl(const std::string &Field, const double &Value);
	void set_value_bol(const std::string &Field, const bool &Value);
	std::string to_string();	
};

#endif // COMPONENT_H

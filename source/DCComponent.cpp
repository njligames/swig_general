
#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

#include "DCComponent.h"
#include "thirdparty/rapidjson/document.h"
#include "thirdparty/rapidjson/prettywriter.h"

class DocumentData
{
public:
    rapidjson::Document data;
};

DCComponent::DCComponent(const std::string &CompType) :
ddata(new DocumentData())
{
	// check for valid type
    struct DCDefinition _DCDefinition;
    if (_DCDefinition.components.find(CompType) == _DCDefinition.components.end())
    {
        componentType = "unknown";
        return;
    }

    componentType = CompType;
    ddata->data.Parse("{}");
};

DCComponent::DCComponent(const std::string &CompType, const std::string &Json) :
ddata(new DocumentData())
{
    componentType = CompType;

    // parse json
    if (Json.length() == 0)  // empty string
    {
        ddata->data.Parse("{}");
    }
    else
    {
        rapidjson::ParseResult ok = ddata->data.Parse(Json.c_str());
        if (!ok)
        {   // TODO: add appropiate log error
            std::cout << "Error parsing: " << CompType << " Code: " << ok.Code() << "\n";
            ddata->data.Parse("{}");  // create empty object on error
            return;
        }
    }
};

std::string DCComponent::get_type()
{
	return componentType;
};

void DCComponent::set_value(const std::string &Field, const std::string &Value)
{
    rapidjson::Value::ConstMemberIterator itr = ddata->data.FindMember(Field.c_str());
    if (itr != ddata->data.MemberEnd())  // updated
    {
        ddata->data[Field.c_str()].SetString(Value.c_str(), ddata->data.GetAllocator());
    }
};

void DCComponent::set_value(const std::string &Field, const std::string &Value, const std::string &ValueType)
{
	
    std::map<std::string, int> type_lookup{ {"string", 1}, {"int", 2}, {"double", 3}, {"boolean", 4} };
    std::map<std::string, bool> bool_lookup{ {"false", false}, {"true", true} };

    int typeId = type_lookup[ValueType];
    std::string v_str = Value;  // needed for lower case convert
    bool bool_val = false;      // needed for string/bool conversion
    switch (typeId)
    {
        case 1:
            this->set_value(Field, Value);
            break;
        case 2:
            this->set_value_int(Field, std::stoi(Value));
            break;
        case 3:
            this->set_value_dbl(Field, std::stod(Value));
            break;
        case 4:
            v_str[0] = tolower(v_str[0]);  // force lower case
            if (bool_lookup.find(v_str) == bool_lookup.end())
                return;  // doesnt match bool
            bool_val = bool_lookup[v_str];
            this->set_value_bol(Field, bool_val);
            break;
        default:
            break;
    }
};

void DCComponent::set_value_int(const std::string &Field, const int &Value)
{
    rapidjson::Value::ConstMemberIterator itr = ddata->data.FindMember(Field.c_str());
    if (itr != ddata->data.MemberEnd())
    {
        ddata->data[Field.c_str()].SetInt(Value);
    }
};

void DCComponent::set_value_dbl(const std::string &Field, const double &Value)
{
    rapidjson::Value::ConstMemberIterator itr = ddata->data.FindMember(Field.c_str());
    if (itr != ddata->data.MemberEnd())
    {
        ddata->data[Field.c_str()].SetDouble(Value);
    }
};

void DCComponent::set_value_bol(const std::string &Field, const bool &Value)
{
    rapidjson::Value::ConstMemberIterator itr = ddata->data.FindMember(Field.c_str());
    if (itr != ddata->data.MemberEnd())
    {
        ddata->data[Field.c_str()].SetBool(Value);
    }
};

std::string DCComponent::to_string()
{
	// begin json string
	std::string json{ "{" };

    for (rapidjson::Value::ConstMemberIterator itr = ddata->data.MemberBegin();
        itr != ddata->data.MemberEnd(); ++itr)
    {
        std::string name = itr->name.GetString();

        // using string buffer to stringify
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        writer.SetFormatOptions(rapidjson::PrettyFormatOptions(1)); // no linefeeds on Arrays
        itr->value.Accept(writer);
        std::string valueStr = buffer.GetString();

        // remove potential spaces after commas if array ddata->data
        if (itr->value.IsArray())
        {
            static const std::regex rgx_pattern(",\\s+");
            valueStr = std::regex_replace(valueStr, rgx_pattern, ",");
        }

        json.append("\"" + name + "\":" + valueStr + ",");
    }

    // remove last comma and close json string
    if (json.back() == ',') json.pop_back();
    json.append("}");

	return json;
};

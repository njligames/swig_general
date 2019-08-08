#ifndef DEFINITION_H
#define DEFINITION_H

#include <map>
#include <string>
#include <vector>


struct DCDefinition
{
	// list of typeNames  TODO to be moved to another file
	const char* kTypeNames[7] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

	// list of fields associated with each type of component
	std::map<std::string, std::vector<std::string>> components = 
	{
		{ "Text",      { "Body", "Style" } },
		{ "Image",     { "Type", "Idx", "Title", "Uuid", "Updating" } },
		{ "Button",    { "Type", "Idx", "Title", "Action" } },
		{ "Checkbox",  { "Type", "Idx", "Title","Value" } },
		{ "Gantt",     { "Type", "Idx" } },
		{ "SequenceDia", { "Type", "Idx" } },
		{ "flowchart", { "Type", "title", "orientation", "nodes", "links" } }, // not upper
		{ "lingraph",  { "Type", "Title", "Idx", "avg", "min", "max", "samples" } } // not upper
	};
};

#endif 

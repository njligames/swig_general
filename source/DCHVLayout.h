#ifndef HVLAYOUT_H
#define HVLAYOUT_H

#include <string>
#include <vector>

#include "DCDefinition.h"
#include "DCComponent.h"

struct ElementRef
{
	int Idx;
	std::string Type;
};


class DCHVLayout
{
private:
	int Idx{ 0 };
	std::string Style{ "" };
	std::string LayoutType{"HLayout"};
	std::vector<ElementRef> Elements;

public:
	DCHVLayout(const std::string &NewLayoutType);
	std::string get_type();
	std::string get_style();
	void set_style(const std::string &NewStyle);
	void set_idx(int NewIdx);
	void add_component(const std::string &ComponentType, const int &Idx);
	std::string to_string();
};

#endif // HVLAYOUT_H

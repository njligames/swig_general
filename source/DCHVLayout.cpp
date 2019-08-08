
#include <iostream>

#include "DCHVLayout.h"
#include "DCComponent.h"


DCHVLayout::DCHVLayout(const std::string &NewLayoutType)
{
	LayoutType = NewLayoutType;
}

std::string DCHVLayout::get_type()
{
	return LayoutType;
};

std::string DCHVLayout::get_style()
{
	return Style;
};

void DCHVLayout::set_style(const std::string &NewStyle)
{
	Style = NewStyle;
};

void DCHVLayout::set_idx(int NewIdx)
{
	Idx = NewIdx;
};

void DCHVLayout::add_component(const std::string &ComponentType, const int &Idx)
{
	// Making a new struct ref
	ElementRef NewRef = ElementRef();
	NewRef.Idx = Idx;
	NewRef.Type = ComponentType;
	Elements.push_back(NewRef);
}

std::string DCHVLayout::to_string()
{
	std::string json{ "{" };

	json.append(R"("Idx":)" + std::to_string(Idx) + ",");

	json.append(R"("Elements":[)");
	for (auto& element : Elements)
	{
		std::string elemStr = R"({"Type":")" + element.Type + R"(","Idx":)" + std::to_string(element.Idx) + R"(},)";
		json.append(elemStr);
	}
	// remove last comma and close json string
	if (json.back() == ',') json.pop_back();
	json.append("],");

	if (Style != "")
	{
		json.append(R"("Style":)" + Style);
	}

	if (json.back() == ',') json.pop_back();
	json.append("}");

	return json;
};


#include <iostream>

#include "DCLayout.h"
#include "DCHVLayout.h"


std::string DCLayout::get_type()
{
	return RootLayoutType;
};

void DCLayout::set_type(const std::string &NewType)
{
	RootLayoutType = NewType;
};

void DCLayout::set_style(const std::string &NewStyle)
{
	RootLayoutType = NewStyle;
};

void DCLayout::add_rootlayout(const std::string &LayoutType)
{
	RootLayout = new DCHVLayout(LayoutType);
	RootLayout->set_idx(0);

	if (LayoutType == "HLayout")
	{
		HLayouts.push_back(RootLayout);
	}
	if (LayoutType == "VLayout")
	{
		VLayouts.push_back(RootLayout);
	}
};

DCHVLayout* DCLayout::add_layout(const std::string &LayoutType)
{
	CurrentLayout = new DCHVLayout(LayoutType);
	int curIdx = 0;
	
	if (LayoutType == "HLayout")
	{
		curIdx = HLayouts.size();
		CurrentLayout->set_idx(curIdx);
		HLayouts.push_back(CurrentLayout);
	}
	if (LayoutType == "VLayout")
	{
		curIdx = VLayouts.size();
		CurrentLayout->set_idx(curIdx);
		VLayouts.push_back(CurrentLayout);
	}

	// adding new layout to root element vector
	RootLayout->add_component(LayoutType, curIdx);

	return CurrentLayout;
}

DCHVLayout* DCLayout::get_cur_layout()
{
	return CurrentLayout;
}

void DCLayout::set_layout(DCHVLayout* Layout)
{
	CurrentLayout = Layout;
}

std::string DCLayout::to_string()
{
	// add RootIdx and RootLayoutType
	std::string json{ "" };

	json.append(R"("RootIdx":)" + std::to_string(RootIdx) + ",");
	json.append(R"("RootLayoutType":")" + RootLayoutType + "\",");

	json.append(R"("HLayout":[)");
	for (auto& layout : HLayouts)
	{
		json.append(layout->to_string() + ",");
	}
	// remove last comma and close json array
	if (json.back() == ',') json.pop_back();
	json.append("],");

	json.append(R"("VLayout":[)");
	for (auto& layout : VLayouts)
	{
		json.append(layout->to_string() + ",");
	}
	// remove last comma and close json array
	if (json.back() == ',') json.pop_back();
	json.append("]");

	return json;
};

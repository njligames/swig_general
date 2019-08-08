#ifndef LAYOUT_H
#define LAYOUT_H

#include <string>
#include <vector>

#include "DCDefinition.h"
#include "DCHVLayout.h"


class DCLayout
{
private:
	int RootIdx = 0;
	std::string RootLayoutType{ "VLayout" };  // check
	DCHVLayout* RootLayout;
	std::vector<DCHVLayout*> HLayouts;
	std::vector<DCHVLayout*> VLayouts;

	DCHVLayout* CurrentLayout = nullptr;

public:
	std::string get_type();
	void set_type(const std::string &NewType);
	void set_style(const std::string &NewStyle);
	void add_rootlayout(const std::string &LayoutType);
	DCHVLayout* add_layout(const std::string &LayoutType);
	DCHVLayout* get_cur_layout();
	void set_layout(DCHVLayout* Layout);
	std::string to_string();
};

#endif // LAYOUT_H

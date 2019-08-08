#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <vector>
#include <string>
using namespace std;

#include "DCComponent.h"
#include "DCLayout.h"


class DCCollector
{

private:
    DCLayout* Layout;// = new DCLayout();

	std::vector<std::string> NoLayout{ "Gantt", "Flowchart", "Linegraph", "Sequencedia" };

public:
	std::vector<DCComponent*> Text;
	std::vector<DCComponent*> Image;
	std::vector<DCComponent*> Button;
	std::vector<DCComponent*> Checkbox;
	std::vector<DCComponent*> Gantt;
	std::vector<DCComponent*> Sequencedia;  // not currently used
	std::vector<DCComponent*> Flowchart;
	std::vector<DCComponent*> Linegraph;

	DCCollector(const std::string &LayoutType);  // root layout
    virtual ~DCCollector();
	DCHVLayout* add_layout(std::string LayoutType);
	DCComponent* add_component(std::string ComponentType, std::string ComponentJson);

	std::string to_string();
	std::string gen_string(std::string Name, std::vector<DCComponent*> Element);
};

#endif // COLLECTOR_H

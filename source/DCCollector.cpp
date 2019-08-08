#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

#include "DCDefinition.h"
#include "DCComponent.h"
#include "DCCollector.h"

//#include "thirdparty/rapidjson/document.h"


DCCollector::DCCollector(const std::string &LayoutType):
Layout(new DCLayout())
{
    Layout->add_rootlayout(LayoutType);
	Layout->set_type(LayoutType);
}

DCCollector::~DCCollector()
{
    delete Layout;
}

DCHVLayout* DCCollector::add_layout(std::string LayoutType)
{
	return Layout->add_layout(LayoutType);
}

DCComponent* DCCollector::add_component(std::string ComponentType, std::string ComponentJson)
{
	DCComponent* newComponent = new DCComponent(ComponentType, ComponentJson);

	int newIdx{ 0 };
	// store in correct vector type and inc newIdx
	if (ComponentType == "Text")
	{
		Text.push_back(newComponent);
		newIdx = Text.size() - 1;
	}
	if (ComponentType == "Image")
	{
		Image.push_back(newComponent);
		newIdx = Image.size() - 1;
	}
	if (ComponentType == "Button")
	{
		Button.push_back(newComponent);
		newIdx = Button.size() - 1;
	}
	if (ComponentType == "Checkbox")
	{
		Checkbox.push_back(newComponent);
		newIdx = Checkbox.size() - 1;
	}
	if (ComponentType == "Gannt")
	{
		Gantt.push_back(newComponent);
		newIdx = Gantt.size() - 1;
	}
	if (ComponentType == "Sequencedia")
	{  // not currently used
		Sequencedia.push_back(newComponent);
		newIdx = Sequencedia.size() - 1;
	}
	if (ComponentType == "Flowchart")
	{
		Flowchart.push_back(newComponent);
		newIdx = Flowchart.size() - 1;
	}
	if (ComponentType == "Linegraph")
	{
		Linegraph.push_back(newComponent);
		newIdx = Linegraph.size() - 1;
	}

	// store component refernce with current layout
	// currently do if componentType not in NOLayout vector - To be removed when all can be included in a layout
	if (std::find(NoLayout.begin(), NoLayout.end(), ComponentType) == NoLayout.end())
	{
		DCHVLayout* curLayout = Layout->get_cur_layout(); // only add if layout set
		if (curLayout != nullptr)
		{
			curLayout->add_component(ComponentType, newIdx);
		}
	}

	return newComponent;
}

std::string DCCollector::to_string()
{
	std::string json{ "{" };

	// add layout
	json.append(R"("Layout":{)" + Layout->to_string() + "},");

	// adding element vectors 
	// Gantt, Flowchart, SequenceDia, and LineGraph tobe added later
	if (!Image.empty())
	{ 
		json.append(this->gen_string("Images", Image) + ",");	// Only Plural Form
	}
	// adding Text vector
	if (!Text.empty())
	{
		json.append(this->gen_string("Text", Text) + ",");
	}
	// adding Button vector
	if (!Button.empty())
	{
		json.append(this->gen_string("Button", Button) + ",");
	}
	// adding Checkbox vector
	if (!Checkbox.empty())
	{
		json.append(this->gen_string("Checkbox", Checkbox) + ",");
	}
	// adding Gantt vector - currently lower
	if (!Gantt.empty())
	{
		json.append(this->gen_string("gannt", Gantt) + ",");
	}
	// adding Flowchart vector   - currently lowercase
	if (!Flowchart.empty())
	{
		json.append(this->gen_string("flowChart", Flowchart) + ",");
	}
	// adding LineGraph vector - currently lowercase camel
	if (!Linegraph.empty())
	{
		json.append(this->gen_string("lineGraph", Linegraph) + ",");
	}

	// remove last comma and close json string
	if (json.back() == ',') json.pop_back();
	json.append("}");  // one for outer and one for layout

	return json;
}

std::string DCCollector::gen_string(std::string Name, std::vector<DCComponent*> Components)
{
	std::string json{ "\"" + Name + "\":[" };

	for (auto& component : Components)
	{
		json.append(component->to_string() + ",");
	}

	// remove last comma and close json string
	if (json.back() == ',') json.pop_back();
	json.append("]");

	return json; 
}

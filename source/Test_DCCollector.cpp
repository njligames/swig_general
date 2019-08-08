// Unit Test(s) for DCCollector 
//
#include <assert.h>
#include "Test_DCCollector.h"


void Test_Collector_Generate1()
{
	// Build validation string
	std::string CheckStr1{ "" };
	CheckStr1.append(R"({"Layout":{"RootIdx":0,"RootLayoutType":"VLayout","HLayout":)");
	CheckStr1.append(R"([{"Idx":0,"Elements":[)");
	CheckStr1.append(R"({"Type":"Text","Idx":0},{"Type":"Image","Idx":0},{"Type":"Button","Idx":0}]},)");
	CheckStr1.append(R"({"Idx":1,"Elements":[)");
	CheckStr1.append(R"({"Type":"Text","Idx":1},{"Type":"Image","Idx":1},{"Type":"Checkbox","Idx":0}]}],)");
	CheckStr1.append(R"("VLayout":[{"Idx":0,"Elements":[{"Type":"HLayout","Idx":0},{"Type":"HLayout","Idx":1}]}]},)");
	CheckStr1.append(R"("Images":[{"Title":"texture","Uuid":"730ad959-4bf9-4252-be59-612ad944050f","Updating":true},)");
	CheckStr1.append(R"({"Title":"thumbnail","Uuid":"874cea83-d897-4280-b066-b7eeba010fc1","Updating":false}],)");
	CheckStr1.append(R"("Text":[{"Title":"s Hdr0","Body":"Rusty Texture"},{"Title":"s Hdr1","Body":"UFO Screenshot"}],)");
	CheckStr1.append(R"("Button":[{"Title":"The Button","Action":"Perform task"}],)");
	CheckStr1.append(R"("Checkbox":[{"Title":"Validate Test","value":true}]})");

	// Build Collector
	DCCollector* NewCollector = new DCCollector("VLayout");
	NewCollector->add_layout("HLayout");
    NewCollector->add_component("Text", R"({"Title":"s Hdr0","Body":"Rusty Texture"})");
	NewCollector->add_component("Image", R"({"Title":"texture",
                                             "Uuid" : "730ad959-4bf9-4252-be59-612ad944050f",
                                             "Updating": true})");
	NewCollector->add_component("Button", R"({"Title":"The Button",
                                              "Action":"Perform task"})");
	NewCollector->add_layout("HLayout");
	NewCollector->add_component("Text", R"({"Title":"s Hdr1","Body":"UFO Screenshot"})");
	NewCollector->add_component("Image", R"({"Title":"thumbnail",
                                             "Uuid" : "874cea83-d897-4280-b066-b7eeba010fc1",
                                             "Updating" : false})");
	NewCollector->add_component("Checkbox", R"({"Title":"Validate Test",
                                                "value":true})");

	assert(NewCollector->to_string() == CheckStr1);
	//To be used to iterate throught character comparion
	//if (NewCollector->to_string() != CheckStr1)
	//{
	//	std::string TestStr1 = NewCollector->to_string();
	//	std::cout << TestStr1 << "\n";
	//	for (size_t i = 0; i != TestStr1.size(); ++i) 
	//	{
	//		if (TestStr1[i] != CheckStr1[i])
	//			std::cout << i  - 1 << " " << TestStr1[i] << " " << CheckStr1[i] << "\n";
	//	}
	//}

}


void Test_Collector_Generate2()  // same as one with lingraph as a central widget
{
	// Build validation string
	std::string CheckStr2{ "" };
	CheckStr2.append(R"({"Layout":{"RootIdx":0,"RootLayoutType":"VLayout","HLayout":)");
	CheckStr2.append(R"([{"Idx":0,"Elements":[)");
	CheckStr2.append(R"({"Type":"Text","Idx":0},{"Type":"Image","Idx":0},{"Type":"Button","Idx":0}]},)");
	CheckStr2.append(R"({"Idx":1,"Elements":[)");
	CheckStr2.append(R"({"Type":"Text","Idx":1},{"Type":"Image","Idx":1},{"Type":"Checkbox","Idx":0}]}],)");
	CheckStr2.append(R"("VLayout":[{"Idx":0,"Elements":[{"Type":"HLayout","Idx":0},{"Type":"HLayout","Idx":1}]}]},)");
	CheckStr2.append(R"("Images":[{"Title":"texture","Uuid":"730ad959-4bf9-4252-be59-612ad944050f","Updating":true},)");
	CheckStr2.append(R"({"Title":"thumbnail","Uuid":"874cea83-d897-4280-b066-b7eeba010fc1","Updating":false}],)");
	CheckStr2.append(R"("Text":[{"Title":"s Hdr0","Body":"Rusty Texture"},{"Title":"s Hdr1","Body":"UFO Screenshot"}],)");
	CheckStr2.append(R"("Button":[{"Title":"The Button","Action":"Perform task"}],)");
	CheckStr2.append(R"("Checkbox":[{"Title":"Validate Test","value":true}],)");
	CheckStr2.append(R"("lineGraph":[{"title":"Line Graphs are Cool","avg":2,"max":5,"min":0,"samples":[0,1,3,2,3,2,1,4,4,4]}]})");

	// Build Collector
	DCCollector* NewCollector = new DCCollector("VLayout");
	NewCollector->add_component("Linegraph", R"({"title":"Line Graphs are Cool",
                                                 "avg":2,"max":5,"min":0,
                                                 "samples":[0,1,3,2,3,2,1,4,4,4]})");
	NewCollector->add_layout("HLayout");
	NewCollector->add_component("Text", R"({"Title":"s Hdr0","Body":"Rusty Texture"})");
	NewCollector->add_component("Image", R"({"Title":"texture",
                                             "Uuid" : "730ad959-4bf9-4252-be59-612ad944050f",
                                             "Updating": true})");
	NewCollector->add_component("Button", R"({"Title":"The Button",
                                              "Action":"Perform task"})");
	NewCollector->add_layout("HLayout");
	NewCollector->add_component("Text", R"({"Title":"s Hdr1","Body":"UFO Screenshot"})");
	NewCollector->add_component("Image", R"({"Title":"thumbnail",
                                             "Uuid" : "874cea83-d897-4280-b066-b7eeba010fc1",
                                             "Updating" : false})");
    NewCollector->add_component("Checkbox", R"({"Title":"Validate Test",
                                                "value":true})");

	assert(NewCollector->to_string() == CheckStr2);
	//if (NewCollector->to_string() != CheckStr2)
	//{
	//   std::cout << NewCollector->to_string() << "\n";
	//}
}

void Test_Collector_Generate3()  // same as one with lingraph as a central widget
{
	// Build validation string
	std::string CheckStr3{ "" };
	CheckStr3.append(R"({"Layout":{"RootIdx":0,"RootLayoutType":"VLayout","HLayout":)");
	CheckStr3.append(R"([{"Idx":0,"Elements":[)");
	CheckStr3.append(R"({"Type":"Text","Idx":0},{"Type":"Checkbox","Idx":0}]},)");
	CheckStr3.append(R"({"Idx":1,"Elements":[)");
	CheckStr3.append(R"({"Type":"Text","Idx":1},{"Type":"Checkbox","Idx":1}]}],)");
	CheckStr3.append(R"("VLayout":[{"Idx":0,"Elements":[{"Type":"HLayout","Idx":0},{"Type":"HLayout","Idx":1}]}]},)");
	CheckStr3.append(R"("Text":[{"Title":"Line1","Body":"Line 1 goes right here"},)");
	CheckStr3.append(R"({"Title":"s Line2","Body":"and Line 2 goes here"}],)");
	CheckStr3.append(R"("Checkbox":[{"Title":"Like","value":false},{"Title":"Like","value":true}]})");

	// Build Collector
	DCCollector* NewCollector = new DCCollector("VLayout");
	NewCollector->add_layout("HLayout");
	NewCollector->add_component("Text", R"({"Title":"Line1","Body":"Line 1 goes right here"})");
	NewCollector->add_component("Checkbox", R"({"Title":"Like",
                                                "value":false})");
	NewCollector->add_layout("HLayout");
	NewCollector->add_component("Text", R"({"Title":"s Line2","Body":"and Line 2 goes here"})");
	NewCollector->add_component("Checkbox", R"({"Title":"Like",
                                                "value":true})");

	assert(NewCollector->to_string() == CheckStr3);
	//if (NewCollector->to_string() != CheckStr3)
	//{
	//	std::cout << NewCollector->to_string() << "\n";
	//}
}

// Collector.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Test_DCCollector.h"


int main()
{	
	std::cout << "Running tests\n";
	Test_Collector_Generate1();
	Test_Collector_Generate2();
	Test_Collector_Generate3();

	std::cout << "\nAll Done!\n";
    return 0;
}


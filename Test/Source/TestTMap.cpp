/**
 * Created by rayfalling on 2020/10/21.
 * */

#include "TestTMap.h"
#include "Container/TMap.h"

#include <iostream>

using namespace Engine::Core;

void TestTMap() {
	/* test area */
	std::cout << "initialize TMap" << std::endl;
	int a= 9;
    TMap<int,double> map(static_cast<SIZE_T>(a));
}

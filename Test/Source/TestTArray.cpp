/**
 * Created by rayfalling on 2020/10/21.
 * */

#include "TestTArray.h"
#include "Container/TArray.h"

#include <iostream>

using namespace Engine::Core;

void TestTArray() {
	/* test area */
	std::cout << "initialize array: {1, 2, 3, 4, 5, 6, 7, 8}" << std::endl;
	TArray<int> array = {1, 2, 3, 4, 5, 6, 7, 8};

	std::cout << "Test TArray operator[](): array[3] " << array[3] << std::endl;
	
	std::cout << "Test TArray Add(): array.Add(9) " << std::endl;
	array.Add(9);
	
	std::cout << "Test TArray IndexOf(): array.IndexOf(9) " << array.IndexOf(9) << std::endl;

	std::cout << "Test TArray RemoveRange(): RemoveRange(0, 7) " << std::endl;
	array.RemoveRange(0, 7);
	
	std::cout << "Test TArray operator[](): array[0] " << array[0] << std::endl;
}

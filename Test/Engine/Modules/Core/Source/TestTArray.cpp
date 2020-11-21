/**
 * Created by rayfalling on 2020/10/21.
 * */

#include "TestTArray.h"
#include "CoreTypes.h"
#include "Container/TArray.h"
#include "Container/TSafeArray.h"

using namespace Engine::Core;
using namespace std::chrono;

void TestTArray() {
	auto& logger = CoreLog::GetInstance();
	logger.SetLogLevel(LogLevel::Debug);

	logger.LogDebug(FString("Test TArray function......"));
	logger.LogDebug(FString("initialize array: {1, 2, 3, 4, 5, 6, 7, 8}"));
	auto start = system_clock::now();
	TArray<int> array = {1, 2, 3, 4, 5, 6, 7, 8};

	logger.LogDebug(FString::Format("Test TArray operator[]() array[3]: {0}", array[3]));
	array.Add(9);

	auto next = 10;
	array.Add(next);
	array.Reserve();
	array.RemoveAt(1);
	array.RemoveAtSwap(1);
	logger.LogDebug(FString::Format("Test TArray IndexOf(): {0}", array.IndexOf(5)));

	auto vec = std::vector({11, 12, 13, 14});
	array.AddRange(vec);

	logger.LogDebug(FString::Format("Test TArray IndexOf() array.IndexOf(9): {0}", array.IndexOf(7)));
	array.RemoveRange(0, 7);

	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	logger.LogDebug(FString::Format("TArray test finished in: {0} microseconds", duration.count()));

	vec.clear();
	logger.LogDebug(FString("std::vector single thread writing count 10000000"));
	start = system_clock::now();

	for (auto i = 0; i < 10000000; i++) {
		vec.emplace_back(i);
	}

	end = system_clock::now();
	duration = duration_cast<microseconds>(end - start);
	logger.LogDebug(FString::Format("std::vector single thread writing test finished in: {0} microseconds", duration.count()));

	array.Clear();
	logger.LogDebug(FString("TArray single thread writing count 10000000"));
	start = system_clock::now();

	for (auto i = 0; i < 10000000; i++) {
		array.Add(i);
	}

	end = system_clock::now();
	duration = duration_cast<microseconds>(end - start);
	logger.LogDebug(FString::Format("TArray single thread writing test finished in: {0} microseconds", duration.count()));

	TSafeArray<int> safeArray;

	logger.LogDebug(FString("TSafeArray multi thread (num 4) writing by using OpenMP count 10000000"));
	start = system_clock::now();

	#pragma omp parallel for num_threads(4)
	for (auto i = 0; i < 10000000; i++) {
		safeArray.Add(i);
	}

	end = system_clock::now();
	duration = duration_cast<microseconds>(end - start);
	logger.LogDebug(FString::Format("TSafeArray multi thread writing test finished in: {0} microseconds", duration.count()));
}

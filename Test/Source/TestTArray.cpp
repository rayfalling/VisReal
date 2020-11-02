/**
 * Created by rayfalling on 2020/10/21.
 * */

#include "TestTArray.h"

#include "Entry.h"
#include "Container/TArray.h"

using namespace Engine::Core;

void TestTArray() {
	/* test TArray methods */
	auto& logger = CoreLog::GetInstance();
	logger.SetLogLevel(LogLevel::Debug);

	auto start = std::chrono::system_clock::now();
	logger.LogDebug(FString("initialize array: {1, 2, 3, 4, 5, 6, 7, 8}"));
	TArray<int> array = {1, 2, 3, 4, 5, 6, 7, 8};

	logger.LogDebug(FString("Test TArray operator[](): array[3] " + array[3]));
	logger.LogDebug(FString("Test TArray Add(): array.Add(9)"));
	array.Add(9);

	auto next = 10;
	logger.LogDebug(FString("Test TArray Add(): array.Add(next)"));
	array.Add(next);

	logger.LogDebug(FString("Test TArray AddRange(): vex: { 11,12,13,14 }"));
	auto vec = std::vector({11, 12, 13, 14});
	logger.LogDebug(FString("Test TArray AddRange(): array.AddRange(vec)"));
	array.AddRange(vec);

	logger.LogDebug(FString("Test TArray IndexOf(): array.IndexOf(9) " + array.IndexOf(9)));
	logger.LogDebug(FString("Test TArray RemoveRange(): RemoveRange(0, 7)"));
	array.RemoveRange(0, 7);

	logger.LogDebug(FString("initialize array: {1, 2, 3, 4, 5, 6, 7, 8}"));

	auto end      = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	logger.LogDebug(FString("TArray test finished in: " + std::to_string(duration.count()) + " microseconds"));

	logger.LogDebug(FString("TArray multi thread by using OpenMP count 100000000"));
	start = std::chrono::system_clock::now();

	#pragma omp parallel for num_threads(4)
	for (auto i = 0; i < 100000000; i++) {
		array.Add(i);
	}

	end      = std::chrono::system_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	logger.LogDebug(
			FString("TArray multi thread test finished in: " + std::to_string(duration.count()) + " microseconds"));
}

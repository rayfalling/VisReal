/**
 * Created by rayfalling on 2020/11/1.
 * */

#include "TestHash.h"


#include "Container/TArray.h"
#include "Logger/CoreLog.h"
#include "Platform/Windows/WindowsPlatformMath.h"

using namespace Engine::Core;

void TestHash() {
	auto& logger = CoreLog::GetInstance();
	logger.SetLogLevel(LogLevel::Debug);

	const auto start = std::chrono::system_clock::now();
	logger.LogDebug(FString("Test Hash function"));
	TArray<hash_t> array(10000);
	
	for (auto i = 0; i < 1000000; ++i) {
		array.Add(FHash::Hash(Math::FPlatformMath::Rand()));
	}

	const auto end = std::chrono::system_clock::now();
	const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	logger.LogDebug(FString("Hash test finished in: " + std::to_string(duration.count()) + " microseconds"));
}

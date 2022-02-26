/**
 * Created by rayfalling on 2020/11/1.
 * */

#include "TestHash.h"

#include "Core.h"
#include "Container/TArray.h"
#include "Hash/Hash.h"
#include "Logger/CoreLog.h"
#include "Platform/Windows/WindowsPlatformMath.h"

using namespace Engine::Core;

void TestHash() {
	auto& logger = CoreLog::GetInstance();
	logger.SetLogLevel(LogLevel::Debug);

	logger.LogDebug(FString("Test Hash function......"));
	const auto     start = std::chrono::system_clock::now();
	TArray<hash_t> array(10000000);

	for (auto i = 0; i < 10000000; ++i) {
		array.Add(FHash::Hash(Math::FPlatformMath::Rand()));
	}

	const auto end = std::chrono::system_clock::now();
	const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	logger.LogDebug(FString::Format("Hash test finished in: {0} microseconds", duration.count()));
}

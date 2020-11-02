/**
 * Created by rayfalling on 2020/10/21.
 * */

#include "TestTMap.h"
#include "Container/TMap.h"

#include <iostream>

#include "Container/FString.h"
#include "Logger/CoreLog.h"

using namespace Engine::Core;

void TestTMap() {
	auto& logger = CoreLog::GetInstance();
	logger.SetLogLevel(LogLevel::Debug);

	logger.LogDebug(FString("Test TMap function......"));
	logger.LogDebug(FString("initialize TMap"));
	int a = 9;
	//    TMap<int,double> map(static_cast<SIZE_T>(a));
}

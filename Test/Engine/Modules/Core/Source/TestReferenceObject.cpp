/**
 * Created by Rayfalling on 2022/2/26.
 * */

#include "TestReferenceObject.h"

#include "Core.h"
#include "Logger/CoreLog.h"
#include "Object/ReferenceObject.h"

using namespace Engine::Core;

class TestObject {
	public:
		int Value = 0;
};

void TestReferenceObject() {
	auto& logger = CoreLog::GetInstance();
	logger.SetLogLevel(LogLevel::Debug);
	logger.LogDebug(FString("Test ReferenceObject......"));

	logger.LogDebug(FString("Create ReferenceObject......"));
	{
		const ReferenceObject<TestObject> referenceObject;
		referenceObject->Value = 1;
		logger.LogDebug(FString::Format("ReferenceObject Reference now is {0}......", referenceObject.GetRefCount()));
		logger.LogDebug(FString::Format("ReferenceObject Value now is {0}......", referenceObject->Value));
		{
			logger.LogDebug(FString("Copy ReferenceObject......"));
			const ReferenceObject<TestObject> another = referenceObject;  // NOLINT(performance-unnecessary-copy-initialization)
			another->Value = 2;
			logger.LogDebug(FString::Format("ReferenceObject Reference now is {0}......", another.GetRefCount()));
			logger.LogDebug(FString::Format("ReferenceObject Value now is {0}......", referenceObject->Value));
		}
		logger.LogDebug(FString("Destroy ReferenceObject copy......"));
		logger.LogDebug(FString::Format("ReferenceObject Reference now is {0}......", referenceObject.GetRefCount()));
		logger.LogDebug(FString::Format("ReferenceObject Value now is {0}......", referenceObject->Value));
	}
	logger.LogDebug(FString("Destroy ReferenceObject......"));
}

/**
 * Created by Rayfalling on 2020/11/26.
 * */


#include "Platform/Generic/GenericPlatformTime.h"

#include "Logger/CoreLog.h"
#include "Math/VisRealMathUtility.h"

using namespace Engine::Core;
using namespace Types;
using namespace Math;

double FGenericPlatformTime::SecondsPerCycle = 0.0;
double FGenericPlatformTime::SecondsPerCycle64 = 0.0;

double FGenericPlatformTime::GetSecondsPerCycle64() {
	if (SecondsPerCycle64 != 0.0) {
		CoreLog::GetInstancePtr()->LogError(FString("SecondsPerCycle64 is zero."));
		PLATFORM_BREAK();
	}
	return SecondsPerCycle64;
}

TCHAR* FGenericPlatformTime::GetDate(TCHAR* dest, const SIZE_T destSize) {
	int32 year;
	int32 month;
	int32 dayOfWeek;
	int32 day;
	int32 hour;
	int32 min;
	int32 sec;
	int32 mSec;

	// FPlatformTime::SystemTime(year, month, dayOfWeek, day, hour, min, sec, mSec);
	// FString::Format(dest, static_cast<int32>(destSize), TEXT("{:02d}/{:02d}/{:02d}"), month, day, year % 100);
	return dest;
}

TCHAR* FGenericPlatformTime::GetTime(TCHAR* Dest, SIZE_T DestSize) {
	int32 year;
	int32 month;
	int32 dayOfWeek;
	int32 day;
	int32 hour;
	int32 min;
	int32 sec;
	int32 mSec;

	// FPlatformTime::SystemTime(year, month, dayOfWeek, day, hour, min, sec, mSec);
	// FString::Format(Dest, static_cast<int32>(DestSize), TEXT("{:02d}:{:02d}:{:02d}"), hour, min, sec);
	return Dest;
}

const TCHAR* FGenericPlatformTime::GetTimestamp() {
	static TCHAR result[1024];
	*result = 0;
	// GetDate(result, UE_ARRAY_COUNT(result));
	// FString::Strcat(result, TEXT(" "));
	// GetTime(result + FCString::Strlen(result), UE_ARRAY_COUNT(result) - FCString::Strlen(result));
	return result;
}

/**
 * Returns a pretty-string for a time given in seconds. (I.e. "4:31 min", "2:16:30 hours", etc)
 * @param Seconds	Time in seconds
 * @return			Time in a pretty formatted string
 */
FString FGenericPlatformTime::PrettyTime(double Seconds) {
	if (Seconds < 1.0) {
		return FString::Format(TEXT("{} ms"), FMath::TruncToInt(static_cast<float>(Seconds * 1000)));
	} else if (Seconds < 10.0) {
		int32 sec = FMath::TruncToInt(static_cast<float>(Seconds));
		const int32 Ms = FMath::TruncToInt(static_cast<float>(Seconds * 1000)) - sec * 1000;
		return FString::Format(TEXT("{}.{:2d} sec"), sec, Ms / 10);
	} else if (Seconds < 60.0) {
		int32 Sec = FMath::TruncToInt(static_cast<float>(Seconds));
		int32 Ms = FMath::TruncToInt(static_cast<float>(Seconds * 1000)) - Sec * 1000;
		return FString::Format(TEXT("{}.{} sec"), Sec, Ms / 100);
	} else if (Seconds < 60.0 * 60.0) {
		int32 Min = FMath::TruncToInt(static_cast<float>(Seconds / 60.0));
		int32 Sec = FMath::TruncToInt(static_cast<float>(Seconds)) - Min * 60;
		return FString::Format(TEXT("{}:{:02d} min"), Min, Sec);
	} else {
		int32 Hr = FMath::TruncToInt(static_cast<float>(Seconds / 3600.0));
		int32 Min = FMath::TruncToInt(static_cast<float>((Seconds - Hr * 3600) / 60.0));
		int32 Sec = FMath::TruncToInt(static_cast<float>(Seconds - Hr * 3600 - Min * 60));
		return FString::Format(TEXT("{}:{:02d}:{:02d} hours"), Hr, Min, Sec);
	}
}

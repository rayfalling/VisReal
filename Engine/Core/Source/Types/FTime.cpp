/**
 * Created by rayfalling on 2020/10/15.
 * */

#include <ctime>
#include "Types/FTime.h"

FString FTime::getCurrentTime() {
    std::time_t t = std::time(nullptr);
    char tmp[32] = {NULL};
    #ifndef _CRT_SECURE_NO_WARNING
    #define _CRT_SECURE_NO_WARNING
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
    #undef _CRT_SECURE_NO_WARNING
    #else
    strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H-%M-%S", localtime(&t));
    #endif
    return FString(tmp, 32);
}

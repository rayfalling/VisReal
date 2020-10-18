/**
 * Created by rayfalling on 2020/10/18.
 * */

#include "Entry.h"

bool Engine::InitEngine() {
    /* Init Engine Logger */
    CoreLog = &Engine::Core::CoreLog::GetInstance();
    CoreLog->LogInfo(FString(ENGINE_START_TIPS));

    return true;
}

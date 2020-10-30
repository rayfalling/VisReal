/**
 * Created by rayfalling on 2020/10/18.
 * */

#include "Marco/Constant.h"
#include "Entry.h"

bool Engine::InitEngine() {
	/* Init Engine Logger */
	CoreLog = &Core::CoreLog::GetInstance();
	CoreLog->LogInfo(Core::ENGINE_START);

	/* Start Render Thread */
	return true;
}

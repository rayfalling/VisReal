/**
 * Created by rayfalling on 2020/10/18.
 * */

#include "Marco/Constant.h"
#include "Entry.h"

#include "RenderThread.h"

bool Engine::InitEngine() {
	/* Init Engine Logger */
	Logger = Core::CoreLog::GetInstancePtr();
	Logger->LogInfo(Core::ENGINE_START);

	/* Start Render Thread */
	InitRenderThread();
	
	return true;
}

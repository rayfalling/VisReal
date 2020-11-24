/**
 * Created by rayfalling on 2020/10/18.
 * */

#include "Marco/Constant.h"
#include "Entry.h"

#include "RenderThread.h"
#include "EventLoop.h"

bool Engine::InitEngine() {
	atexit(Terminate);

	/* Init Engine Logger */
	Logger = Core::CoreLog::GetInstancePtr();
	Logger->LogInfo(Core::ENGINE_START);

	/* Start Render Thread */
	InitRenderThread();

	/* Main Event Loop */
	MessageLoop = Event::EventLoop::GetInstancePtr();
	MessageLoop->Run();

	return true;
}

void Engine::Terminate() {
	TerminateRenderThread();
	Logger->FlushAll();
}

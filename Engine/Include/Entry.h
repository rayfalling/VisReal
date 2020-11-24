/**
 * Created by rayfalling on 2020/10/18.
 * */

#ifndef VISREAL_ENTRY_H
#define VISREAL_ENTRY_H

#include "Logger/CoreLog.h"
#include "EventLoop.h"

namespace Engine {
	/* Global static logger variable */
	static Core::CoreLog* Logger;
	static Event::EventLoop* MessageLoop;

	/* Init engine thread, logger, and other needed */
	bool InitEngine();

	/* Terminate Application */
	void Terminate();
}

#endif //VISREAL_ENTRY_H

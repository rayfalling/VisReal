/**
 * Created by rayfalling on 2020/10/18.
 * */

#ifndef VISREAL_ENTRY_H
#define VISREAL_ENTRY_H

#include "Container/FString.h"
#include "Marco/Marcos.h"
#include "Logger/CoreLog.h"
#include "ThreadPool/ThreadPool.h"

namespace Engine {
	/* Global static logger variable */
	static Core::CoreLog* CoreLog;

	/* Init engine thread, logger, and other needed */
	bool InitEngine();
}

#endif //VISREAL_ENTRY_H

/**
 * Created by rayfalling on 2020/10/18.
 * */

#ifndef VISREAL_ENTRY_H
#define VISREAL_ENTRY_H

#include "Logger/CoreLog.h"

namespace Engine {
	/* Global static logger variable */
	inline Core::CoreLog* Logger;

	/* Init engine thread, logger, and other needed */
	bool InitEngine();
}

#endif //VISREAL_ENTRY_H

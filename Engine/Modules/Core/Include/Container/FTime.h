/**
 * Created by rayfalling on 2020/10/15.
 * */

#pragma once

#ifndef VISREAL_TIME_H
#define VISREAL_TIME_H

#include "FString.h"

namespace Engine::Core::Types {
	class FTime {
		public:
			static FString CurrentTime();
	};
}

#endif //VISREAL_TIME_H

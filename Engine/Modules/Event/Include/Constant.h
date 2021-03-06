/**
 * Created by rayfalling on 2020/11/24.
 * */

#pragma once

#ifndef VISREAL_EVENT_CONSTANT_H
#define VISREAL_EVENT_CONSTANT_H

#include "Container/FString.h"

namespace Engine::Event {
	const static Core::Types::FString FUNCTION_NOT_REGISTER = Core::Types::FString("Function not registered, can not remove.");
	const static Core::Types::FString EVENT_LOOP_START = Core::Types::FString("VisReal Engine Event Loop Started.");
	const static Core::Types::FString EVENT_LOOP_STOP = Core::Types::FString("VisReal Engine Event Loop Stopped.");
}

#endif

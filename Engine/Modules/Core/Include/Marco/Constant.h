/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma once

#ifndef VISREAL_CONSTANT_H
#define VISREAL_CONSTANT_H

#include "Container/FString.h"

namespace Engine::Core {
	const static FString OUT_OF_ARRAY_INDEX          = FString("Index out of Array size");
	const static FString CORE_LOG_NAME               = FString("VisReal Core");
	const static FString ENGINE_START                = FString("VisReal Engine Start.");
	const static FString TARRY_ADD_CONTAINER_ELEMENT = FString(
			"Attempting to use a container element which already comes from the container being modified");
	const static int32 INDEX_NONE = -1;
}

#endif //VISREAL_CONSTANT_H

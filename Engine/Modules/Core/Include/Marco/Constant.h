/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma once

#ifndef VISREAL_CONSTANT_H
#define VISREAL_CONSTANT_H

#include "Container/FString.h"

namespace Engine::Core {
	const static FString CORE_LOG_NAME = FString("VisReal Core");
	const static FString ENGINE_START = FString("VisReal Engine Start.");

	/* TArray Tips */
	const static FString TARRAY_MAX_SIZE = FString("Growth size attach to max size, set to SIZE_T max value");
	const static FString TARRAY_OUT_OF_INDEX_ERROR = FString("Index out of Array size");
	const static FString TARRY_ADD_CONTAINER_ELEMENT = FString("Attempting to use an element which already comes from the container");
	const static FString TARRAY_REMOVE_AT_SWAP_WARNING = FString("!!!This operation don't preserve the order.!!!");

	/* FString Tips */
	const static FString FSTRING_OUT_OF_INDEX_ERROR = FString("Index out of FString length");

	const static int32 INDEX_NONE = -1;
}

#endif //VISREAL_CONSTANT_H

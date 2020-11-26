/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma once

#ifndef VISREAL_CONSTANT_H
#define VISREAL_CONSTANT_H

#include "Container/FString.h"

namespace Engine::Core {
	const static Types::FString C_APPLICATION_NAME = Types::FString("VisReal");

	/* Core Log */
	const static Types::FString C_CORE_LOG_NAME = Types::FString("VisReal Core");
	const static Types::FString C_ENGINE_START = Types::FString("VisReal Engine Started.");
	const static Types::FString C_ENGINE_STOP = Types::FString("VisReal Engine Stopped.");

	/* TArray Tips */
	const static Types::FString C_TARRAY_MAX_SIZE = Types::FString("Growth size attach to max size, set to SIZE_T max value");
	const static Types::FString C_TARRAY_OUT_OF_INDEX_ERROR = Types::FString("Index out of Array size");
	const static Types::FString C_TARRY_ADD_CONTAINER_ELEMENT = Types::FString(
			"Attempting to use an element which already comes from the container");
	const static Types::FString C_TARRAY_REMOVE_AT_SWAP_WARNING = Types::FString("!!!This operation don't preserve the order.!!!");

	/* Types::FString Tips */
	const static Types::FString C_FSTRING_OUT_OF_INDEX_ERROR = Types::FString("Index out of Types::FString length");

	const static int32 C_INDEX_NONE = -1;
}

#endif //VISREAL_CONSTANT_H

/**
 * Created by rayfalling on 2020/10/30.
 * */

#pragma once

#ifndef VISREAL_CONTAINER_FORWARD_DEFINITION_H
#define VISREAL_CONTAINER_FORWARD_DEFINITION_H

namespace Engine::Core::Types {
	class FString;

	template <typename T>
	class TArray;

	template <typename KeyType, typename ValueType, typename HashFunction>
	class TMap;

	template <typename>
	struct TTypeTraits;

	template <typename InElementType, typename HashFunction>
	class TSet;
}

#endif //VISREAL_CONTAINER_FORWARD_DEFINITION_H

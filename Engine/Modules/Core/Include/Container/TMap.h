/**
 * Created by rayfalling on 2020/10/18.
 * */

#pragma once

#ifndef VISREAL_T_MAP_H
#define VISREAL_T_MAP_H

#include "Platform/PlatformTypes.h"
#include <mutex>

namespace Engine::Core::Types {
	/* forward declaration for TArray */
	template <typename T>
	class TArray;

	template <typename Key, typename Value>
	class MapItem {
		public:
			MapItem() noexcept = default;

			MapItem(Key key, Value value) noexcept: _key(key), _value(value) {
			};

		private:
			Key   _key;
			Value _value;

		public:
			Key& GetKey() {
				return _key;
			}

			Value& GetValue() {
				return _value;
			}
	};

	/* TODO think about how to store KeyValuePair */
	template <typename Key, typename Value, typename KeyFunc>
	class TMap {
		typedef MapItem<Key, Value> ElementType;

		public:
			explicit TMap(SIZE_T size) {
				_size = size;
				_hashtable = std::make_shared<TArray<ElementType>>(size);
			}

			~TMap() = default;

		private:
			SIZE_T                               _size;
			std::mutex                           _mutex;
			std::shared_ptr<TArray<ElementType>> _hashtable{};
	};
}

#endif //VISREAL_T_MAP_H

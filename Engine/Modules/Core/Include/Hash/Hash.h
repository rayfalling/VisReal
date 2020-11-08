/**
 * Created by rayfalling on 2020/10/31.
 * */

#pragma once

#ifndef VISREAL_HASH_H
#define VISREAL_HASH_H

#include <xxhash.h>
#include "Platform/PlatformTypes.h"

namespace Engine::Core {
	#ifdef PLATFORM_64BITS
	typedef uint64 hash_t;

	inline hash_t DoHash(void* input, const size_t length, const hash_t seed = 0) {
		return XXH64(input, length, seed);
	}
	#else
	typedef uint64 hash_t;
	
	inline hash_t DoHash(void* input, const size_t length, const hash_t seed = 0) {
		return XXH32(input, length, seed);
	}
	#endif

	struct FHash {
		inline static hash_t Seed = 236541925u;

		template <typename T>
		static uint64 Hash(T value) {
			return DoHash(&value, sizeof(T), Seed);
		}

		/* Hash built-in types */
		static uint64 Hash(int8 value);
		static uint64 Hash(int16 value);
		static uint64 Hash(int32 value);
		static uint64 Hash(int64 value);

		static uint64 Hash(uint8 value);
		static uint64 Hash(uint16 value);
		static uint64 Hash(uint32 value);
		static uint64 Hash(uint64 value);

		static uint64 Hash(float value);
		static uint64 Hash(double value);

		static uint64 Hash(CHAR value);
		static uint64 Hash(WCHAR value);
	};
}

#endif // VISREAL_HASH_H

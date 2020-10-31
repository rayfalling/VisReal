/**
 * Created by rayfalling on 2020/10/31.
 * */

#pragma once

#ifndef VISREAL_HASH_H
#define VISREAL_HASH_H

#include "xxhash.h"
#include "Platform/PlatformTypes.h"

#ifdef PLATFORM_64BITS
#define XXHASH(a, b, c)     XXH64(a, b, c)
#define uint64				XXH64_hash_t
#else
#define XXHASH(a, b, c)     XXH32(a, b, c)
#define uint32				XXH32_hash_t
#endif

namespace Engine::Core {
	struct FHash {
		static uint64 Hash(int32 value);
	};
}

#endif // VISREAL_HASH_H

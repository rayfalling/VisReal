/**
 * Created by rayfalling on 2020/10/31.
 * */

#include "Hash/Hash.h"

#include "Platform/Windows/WindowsPlatformMath.h"

using namespace Engine::Core;

uint64 FHash::Hash(int8 value) {
	return DoHash(&value, sizeof(int8), Seed);
}

uint64 FHash::Hash(int16 value) {
	return DoHash(&value, sizeof(int16), Seed);
}

hash_t FHash::Hash(int32 value) {
	return DoHash(&value, sizeof(int32), Seed);
}

uint64 FHash::Hash(int64 value) {
	return DoHash(&value, sizeof(int64), Seed);
}

uint64 FHash::Hash(uint8 value) {
	return DoHash(&value, sizeof(uint8), Seed);
}

uint64 FHash::Hash(uint16 value) {
	return DoHash(&value, sizeof(uint16), Seed);
}

hash_t FHash::Hash(uint32 value) {
	return DoHash(&value, sizeof(uint32), Seed);
}

uint64 FHash::Hash(uint64 value) {
	return DoHash(&value, sizeof(uint64), Seed);
}

uint64 FHash::Hash(float value) {
	return DoHash(&value, sizeof(float), Seed);
}

uint64 FHash::Hash(double value) {
	return DoHash(&value, sizeof(double), Seed);
}

hash_t FHash::Hash(CHAR value) {
	return DoHash(&value, sizeof(CHAR), Seed);
}

uint64 FHash::Hash(WCHAR value) {
	return DoHash(&value, sizeof(WCHAR), Seed);
}

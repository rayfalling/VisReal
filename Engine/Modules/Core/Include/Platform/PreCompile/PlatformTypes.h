/**
 * Created by Rayfalling on 2020/11/26.
 * */

#ifndef VISREAL_PRE_PLATFORM_TYPES_H
#define VISREAL_PRE_PLATFORM_TYPES_H

#include "Marco/PreprocessorHelpers.h"
#include "Platform/PreCompile/Platform.h"

#include COMPILED_PLATFORM_HEADER(PlatformTypes.h)

//~ Unsigned base types.
// An 8-bit unsigned integer.
typedef Engine::Core::Types::FPlatformTypes::uint8 uint8;
// A 16-bit unsigned integer.
typedef Engine::Core::Types::FPlatformTypes::uint16 uint16;
// A 32-bit unsigned integer.
typedef Engine::Core::Types::FPlatformTypes::uint32 uint32;
// A 64-bit unsigned integer.
typedef Engine::Core::Types::FPlatformTypes::uint64 uint64;

//~ Signed base types.
// An 8-bit signed integer.
typedef Engine::Core::Types::FPlatformTypes::int8 int8;
// A 16-bit signed integer.
typedef Engine::Core::Types::FPlatformTypes::int16 int16;
// A 32-bit signed integer.
typedef Engine::Core::Types::FPlatformTypes::int32 int32;
// A 64-bit signed integer.
typedef Engine::Core::Types::FPlatformTypes::int64 int64;

//~ Character types.
// An ANSI character. Normally a signed type.
typedef Engine::Core::Types::FPlatformTypes::CHAR CHAR;
// A wide character. Normally a signed type.
typedef Engine::Core::Types::FPlatformTypes::WCHAR WCHAR;
// Either CHAR or WCHAR, depending on whether the platform supports wide characters or the requirements of the licensee.
typedef Engine::Core::Types::FPlatformTypes::TCHAR TCHAR;
// An 8-bit character containing a UTF8 (Unicode, 8-bit, variable-width) code unit.
typedef Engine::Core::Types::FPlatformTypes::CHAR8 UTF8CHAR;
// A 16-bit character containing a UCS2 (Unicode, 16-bit, fixed-width) code unit, used for compatibility with 'Windows TCHAR' across multiple platforms.
typedef Engine::Core::Types::FPlatformTypes::CHAR16 UCS2CHAR;
// A 16-bit character containing a UTF16 (Unicode, 16-bit, variable-width) code unit.
typedef Engine::Core::Types::FPlatformTypes::CHAR16 UTF16CHAR;
// A 32-bit character containing a UTF32 (Unicode, 32-bit, fixed-width) code unit.
typedef Engine::Core::Types::FPlatformTypes::CHAR32 UTF32CHAR;

// An unsigned integer the same size as a pointer
typedef Engine::Core::Types::FPlatformTypes::PTR_SIZE PTR_SIZE;
// A signed integer the same size as a pointer
typedef Engine::Core::Types::FPlatformTypes::SPTR_SIZE SPTR_SIZE;
// An unsigned integer the same size as a pointer, the same as VISREAL_UNSIGNED_SIZE_T
typedef Engine::Core::Types::FPlatformTypes::SIZE_T SIZE_T;
// An integer the same size as a pointer, the same as PTR_SIZE
typedef Engine::Core::Types::FPlatformTypes::SSIZE_T SSIZE_T;

namespace Engine::Core {
	template <typename, typename>
	struct TAreTypesEqual;

	//------------------------------------------------------------------
	// Test the global types
	//------------------------------------------------------------------
	namespace TypeTests {
		template <typename A, typename B>
		struct TAreTypesEqual {
			static const bool Value = false;
		};

		template <typename T>
		struct TAreTypesEqual<T, T> {
			static const bool Value = true;
		};

		static_assert(!PLATFORM_TCHAR_IS_4_BYTES || sizeof(TCHAR) == 4, "TCHAR size must be 4 bytes.");
		static_assert(PLATFORM_TCHAR_IS_4_BYTES || sizeof(TCHAR) == 2, "TCHAR size must be 2 bytes.");

		static_assert(!PLATFORM_WCHAR_IS_4_BYTES || sizeof(wchar_t) == 4, "wchar_t size must be 4 bytes.");
		static_assert(PLATFORM_WCHAR_IS_4_BYTES || sizeof(wchar_t) == 2, "wchar_t size must be 2 bytes.");

		static_assert(PLATFORM_32BITS || PLATFORM_64BITS, "Type tests pointer size failed.");
		static_assert(PLATFORM_32BITS != PLATFORM_64BITS, "Type tests pointer exclusive failed.");
		static_assert(!PLATFORM_64BITS || sizeof(void*) == 8, "Pointer size is 64bit, but pointers are short.");
		static_assert(PLATFORM_64BITS || sizeof(void*) == 4, "Pointer size is 32bit, but pointers are long.");

		static_assert(static_cast<char>(-1) < static_cast<char>(0), "Unsigned char type test failed.");

		static_assert((!TAreTypesEqual<CHAR, WCHAR>::Value), "CHAR and WCHAR should be different types.");
		static_assert((!TAreTypesEqual<CHAR, UCS2CHAR>::Value), "CHAR and CHAR16 should be different types.");
		static_assert((!TAreTypesEqual<WCHAR, UCS2CHAR>::Value), "WCHAR and CHAR16 should be different types.");
		static_assert((TAreTypesEqual<TCHAR, CHAR>::Value == true || TAreTypesEqual<TCHAR, WCHAR>::Value == true),
			"TCHAR should either be CHAR or WCHAR.");

		static_assert(sizeof(uint8) == 1, "uint8 type size test failed.");
		static_assert(static_cast<int32>(static_cast<uint8>(-1)) == 0xFF, "uint8 type sign test failed.");

		static_assert(sizeof(uint16) == 2, "uint16 type size test failed.");
		static_assert(static_cast<int32>(static_cast<uint16>(-1)) == 0xFFFF, "uint16 type sign test failed.");

		static_assert(sizeof(uint32) == 4, "uint32 type size test failed.");
		static_assert(static_cast<int64>(static_cast<uint32>(-1)) == static_cast<int64>(0xFFFFFFFF), "uint32 type sign test failed.");

		static_assert(sizeof(uint64) == 8, "uint64 type size test failed.");
		static_assert(static_cast<uint64>(-1) > static_cast<uint64>(0), "uint64 type sign test failed.");


		static_assert(sizeof(int8) == 1, "int8 type size test failed.");
		static_assert(static_cast<int32>(static_cast<int8>(-1)) == -1, "int8 type sign test failed.");

		static_assert(sizeof(int16) == 2, "int16 type size test failed.");
		static_assert(static_cast<int32>(static_cast<int16>(-1)) == -1, "int16 type sign test failed.");

		static_assert(sizeof(int32) == 4, "int32 type size test failed.");
		static_assert(static_cast<int64>(static_cast<int32>(-1)) == static_cast<int64>(-1), "int32 type sign test failed.");

		static_assert(sizeof(int64) == 8, "int64 type size test failed.");
		static_assert(static_cast<int64>(-1) < static_cast<int64>(0), "int64 type sign test failed.");

		static_assert(sizeof(CHAR) == 1, "CHAR type size test failed.");
		static_assert(static_cast<int32>(static_cast<CHAR>(-1)) == -1, "CHAR type sign test failed.");

		static_assert(sizeof(WCHAR) == 2 || sizeof(WCHAR) == 4, "WCHAR type size test failed.");

		static_assert(sizeof(UCS2CHAR) == 2, "UCS2CHAR type size test failed.");

		static_assert(sizeof(SPTR_SIZE) == sizeof(void*), "SPTR_SIZE type size test failed.");
		static_assert(static_cast<SPTR_SIZE>(-1) < static_cast<SPTR_SIZE>(0), "SPTR_SIZE type sign test failed.");

		static_assert(sizeof(PTR_SIZE) == sizeof(void*), "PTR_SIZE type size test failed.");
		static_assert(static_cast<PTR_SIZE>(-1) > static_cast<PTR_SIZE>(0), "PTR_SIZE type sign test failed.");

		static_assert(sizeof(SIZE_T) == sizeof(void*), "SIZE_T type size test failed.");
		static_assert(static_cast<SIZE_T>(-1) > static_cast<SIZE_T>(0), "SIZE_T type sign test failed.");
	}
}

#endif // VISREAL_PRE_PLATFORM_TYPES_H

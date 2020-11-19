/**
 * Created by rayfalling on 2020/8/30.
 * */

#pragma once

#ifndef VISREAL_PLATFORM_TYPES_H
#define VISREAL_PLATFORM_TYPES_H

#ifdef MSVC
// include windows platform types
#include "Platform/Windows/WindowsPlatform.h"
#endif

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

#endif //VISREAL_PLATFORM_TYPES_H

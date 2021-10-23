/**
 * Created by Rayfalling on 2020/11/26.
 * */

#pragma once

#ifndef VISREAL_PLATFORM_H
#define VISREAL_PLATFORM_H

#include "Marco/PreprocessorHelpers.h"

//---------------------------------------------------------
// Include main platform setup header (XXX/XXXPlatform.h)
//---------------------------------------------------------

#include COMPILED_PLATFORM_HEADER(Platform.h)

namespace Engine::Core {
	//------------------------------------------------------------------
	// Finalize define setup
	//------------------------------------------------------------------

	// Base defines, must define these for the platform, there are no defaults
	#ifndef PLATFORM_DESKTOP
	#error "PLATFORM_DESKTOP must be defined"
	#endif
	#ifndef PLATFORM_64BITS
	#error "PLATFORM_64BITS must be defined"
	#endif
}

#include "Platform/Generic/GenericPlatform.h"

namespace Engine::Core {
	// Console CHAR/TCHAR command line handling
	#if PLATFORM_COMPILER_HAS_TCHAR_WMAIN
	#define INT32_MAIN_INT32_ARGC_TCHAR_ARGV() int32 wmain(int32 ArgC, TCHAR* ArgV[])
	#else
	INT32_MAIN_INT32_ARGC_TCHAR_ARGV() \
	int32 tchar_main(int32 ArgC, TCHAR* ArgV[]); \
	int32 main(int32 ArgC, CHAR* Utf8ArgV[]) \
	{ \
		TCHAR** ArgV = new TCHAR*[ArgC]; \
		for (int32 a = 0; a < ArgC; a++) \
		{ \
			FUTF8ToTCHAR ConvertFromUtf8(Utf8ArgV[a]); \
			ArgV[a] = new TCHAR[ConvertFromUtf8.Length() + 1]; \
			FCString::Strcpy(ArgV[a], ConvertFromUtf8.Length() + 1, ConvertFromUtf8.Get()); \
		} \
		int32 Result = tchar_main(ArgC, ArgV); \
		for (int32 a = 0; a < ArgC; a++) \
		{ \
			delete[] ArgV[a]; \
		} \
		delete[] ArgV; \
		return Result; \
	} \
	int32 tchar_main(int32 ArgC, TCHAR* ArgV[])
	#endif

	// If we don't have a platform-specific define for the TEXT macro, define it now.
	#if !defined(TEXT)
	#if PLATFORM_TCHAR_IS_CHAR16
	#define TEXT_PASTE(x) u ## x
	#else
	#define TEXT_PASTE(x) L ## x
	#endif
	#define TEXT(x) TEXT_PASTE(x)
	#endif
}
#endif // VISREAL_PLATFORM_H

/**
 * Created by rayfalling on 2020/11/26.
 *
 * Use Epic version to make <Windows.h> include correctly
 * */


// Disable the warning that the pack size is changed in this header.
#ifdef __clang__
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wpragma-pack"
#else	// __clang__
	#pragma warning(disable:4103)
#endif	// __clang__

// Save these macros for later; Windows redefines them
#pragma push_macro("MAX_uint8")
#pragma push_macro("MAX_uint16")
#pragma push_macro("MAX_uint32")
#pragma push_macro("MAX_int32")
#pragma push_macro("TEXT")
#pragma push_macro("TRUE")
#pragma push_macro("FALSE")

// Undefine the TEXT macro for winnt.h to redefine it, unless it's already been included
#ifndef _WINNT_
#undef TEXT
#endif

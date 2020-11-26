/**
 * Created by rayfalling on 2020/8/30.
 * 
 * Typedef file for project.
 * Use for cross platform data type.
 * Windows platform definition to override generic definition.
 * */

#pragma once

#ifndef VISREAL_WINDOWS_PLATFORM_TYPES_H
#define VISREAL_WINDOWS_PLATFORM_TYPES_H

#include "Platform/Generic/GenericPlatformTypes.h"

namespace Engine::Core::Types {
	/**
	* Windows specific types
	**/
	struct FWindowsPlatformTypes : public GenericPlatformTypes {
		#ifdef PLATFORM_64BITS
		typedef unsigned long long SIZE_T;
		typedef long long SSIZE_T;
		#else
		typedef unsigned long SIZE_T;
		typedef long SSIZE_T;
		#endif
	};

	typedef FWindowsPlatformTypes FPlatformTypes;
}
#endif //VISREAL_WINDOWS_PLATFORM_TYPES_H

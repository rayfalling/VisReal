/**
 * Created by Rayfalling on 2020/11/26.
 * */

#ifndef VISREAL_PLATFORM_H
#define VISREAL_PLATFORM_H

#include "Marco/PreprocessorHelpers.h"

//---------------------------------------------------------
// Include main platform setup header (XXX/XXXPlatform.h)
//---------------------------------------------------------

#include COMPILED_PLATFORM_HEADER(Platform.h)

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

#include "Platform/Generic/GenericPlatform.h"

#endif // VISREAL_PLATFORM_H

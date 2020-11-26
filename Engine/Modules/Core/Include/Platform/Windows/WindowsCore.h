/**
 * Created by rayfalling on 2020/11/26.
 *
 * Use Epic version to make <Windows.h> include correctly
 * */

#pragma once

#include "Platform/Windows/PreWindowsApi.h"
#ifndef STRICT
#define STRICT
#endif
#include "Platform/Windows/MinWindows.h"
#include "Platform/Windows/PostWindowsApi.h"

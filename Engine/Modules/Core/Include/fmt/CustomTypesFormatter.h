/**
 * Created by rayfalling on 2020/11/12.
 * */

// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppInconsistentNaming
#pragma once

#ifndef VISREAL_CUSTOM_TYPES_FORMATTER_H
#define VISREAL_CUSTOM_TYPES_FORMATTER_H

#include <fmt/format.h>

#include "Container/FString.h"
#include "Math/FVector.h"

namespace Engine::Core {
	namespace Types {
		class FString;
	}

	namespace Math {
		class FVector3;
		class FPlane;
	}
}

template <>
struct fmt::formatter<FString> {
	template <typename ParseContext>
	constexpr auto parse(ParseContext& ctx) {
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const FString& string, FormatContext& ctx) {
		return fmt::format_to(ctx.out(), "{}", string.ToString());
	}
};

template <>
struct fmt::formatter<Engine::Core::Math::FVector3> {
	template <typename ParseContext>
	constexpr auto parse(ParseContext& ctx) {
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const Engine::Core::Math::FVector3& vector3, FormatContext& ctx) {
		return fmt::format_to(ctx.out(), "{}", vector3.GetName());
	}
};

#endif // VISREAL_CUSTOM_TYPES_FORMATTER_H

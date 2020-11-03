/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma once
#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"

#ifndef VISREAL_T_IS_TRIVIALLY_DESTRUCTIBLE_H
#define VISREAL_T_IS_TRIVIALLY_DESTRUCTIBLE_H

namespace Engine::Core {
	namespace IsTriviallyDestructiblePrivate {
		// We have this specialization for enums to avoid the need to have a full definition of
		// the type.
		template <typename T, bool IsTriviallyTriviallyDestructible = __is_enum(T)>
		struct TImpl {
			enum { Value = true };
		};

		template <typename T>
		struct TImpl<T, false> {
			enum { Value = __has_trivial_destructor(T) };
		};
	}

	/**
	 * Traits class which tests if a type has a trivial destructor.
	 */
	template <typename T>
	struct TIsTriviallyDestructible {
		enum { Value = IsTriviallyDestructiblePrivate::TImpl<T>::Value };
	};
}

#endif //VISREAL_T_IS_TRIVIALLY_DESTRUCTIBLE_H

#pragma clang diagnostic pop

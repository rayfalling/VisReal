/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"
#pragma once

#ifndef VISREAL_T_IS_TRIVIALLY_COPY_ASSIGNABLE_H
#define VISREAL_T_IS_TRIVIALLY_COPY_ASSIGNABLE_H

namespace Engine::Core {
	/**
	 * Traits class which tests if a type has a trivial copy assignment operator.
	 */
	template <typename T>
	struct TIsTriviallyCopyAssignable {
		enum { Value = __has_trivial_assign(T) };
	};
}

#endif //VISREAL_T_IS_TRIVIALLY_COPY_ASSIGNABLE_H

#pragma clang diagnostic pop

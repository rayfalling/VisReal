/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma once

#ifndef VISREAL_T_ARE_TYPES_EQUAL_H
#define VISREAL_T_ARE_TYPES_EQUAL_H

namespace Engine::Core {
	/** Tests whether two typenames refer to the same type. */
	template <typename A, typename B>
	struct TAreTypesEqual;

	template <typename, typename>
	struct TAreTypesEqual {
		enum {
			Value = false
		};
	};

	template <typename A>
	struct TAreTypesEqual<A, A> {
		enum {
			Value = true
		};
	};
}
#endif //VISREAL_T_ARE_TYPES_EQUAL_H

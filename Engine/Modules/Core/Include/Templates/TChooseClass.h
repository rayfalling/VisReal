/**
 * Created by rayfalling on 2020/8/30.
 *
 * From Unreal Engine
 * */

#pragma once

#ifndef VISREAL_T_CHOOSE_CLASS_H
#define VISREAL_T_CHOOSE_CLASS_H

namespace Engine::Core {
	/** 
	 * Chooses between two different classes based on a boolean. 
	 * */
	template <bool Predicate, typename TrueClass, typename FalseClass>
	class TChooseClass;

	template <typename TrueClass, typename FalseClass>
	class TChooseClass<true, TrueClass, FalseClass> {
		public:
			typedef TrueClass Result;
	};

	template <typename TrueClass, typename FalseClass>
	class TChooseClass<false, TrueClass, FalseClass> {
		public:
			typedef FalseClass Result;
	};
}

#endif //VISREAL_T_CHOOSE_CLASS_H

/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma once

#ifndef VISREAL_T_IS_ENUM_H
#define VISREAL_T_IS_ENUM_H

namespace Engine::Core {
	template <typename T>
	struct TIsEnum {
		enum {
			Value = __is_enum(T)
		};
	};
}

#endif //VISREAL_T_IS_ENUM_H

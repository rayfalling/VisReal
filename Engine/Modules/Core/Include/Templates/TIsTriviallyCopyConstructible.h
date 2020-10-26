/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"
#pragma once

#ifndef VISREAL_T_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_H
#define VISREAL_T_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_H

namespace Engine::Core {
    /**
     * Traits class which tests if a type has a trivial copy constructor.
     */
    template<typename T>
    struct TIsTriviallyCopyConstructible {
        enum {
            Value = __has_trivial_copy(T)
        };
    };
}

#endif //VISREAL_T_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_H

#pragma clang diagnostic pop
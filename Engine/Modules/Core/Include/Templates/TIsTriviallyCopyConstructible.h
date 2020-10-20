/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma once

#ifndef VISREAL_TISTRIVIALLYCOPYCONSTRUCTIBLE_H
#define VISREAL_TISTRIVIALLYCOPYCONSTRUCTIBLE_H

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

#endif //VISREAL_TISTRIVIALLYCOPYCONSTRUCTIBLE_H

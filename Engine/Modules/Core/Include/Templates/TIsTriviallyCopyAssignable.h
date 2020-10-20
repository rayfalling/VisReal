/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma once

#ifndef VISREAL_TISTRIVIALLYCOPYASSIGNABLE_H
#define VISREAL_TISTRIVIALLYCOPYASSIGNABLE_H

namespace Engine::Core {
    /**
     * Traits class which tests if a type has a trivial copy assignment operator.
     */
    template <typename T>
    struct TIsTriviallyCopyAssignable
    {
        enum { Value = __has_trivial_assign(T) };
    };
}

#endif //VISREAL_TISTRIVIALLYCOPYASSIGNABLE_H

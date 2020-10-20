/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma once

#ifndef VISREAL_TISPOINTER_H
#define VISREAL_TISPOINTER_H

namespace Engine::Core {
    /**
     * Traits class which tests if a type is a pointer.
     */
    template <typename T>
    struct TIsPointer
    {
        enum { Value = false };
    };

    template <typename T> struct TIsPointer<T*> { enum { Value = true }; };

    template <typename T> struct TIsPointer<const          T> { enum { Value = TIsPointer<T>::Value }; };
    template <typename T> struct TIsPointer<      volatile T> { enum { Value = TIsPointer<T>::Value }; };
    template <typename T> struct TIsPointer<const volatile T> { enum { Value = TIsPointer<T>::Value }; };
}

#endif //VISREAL_TISPOINTER_H

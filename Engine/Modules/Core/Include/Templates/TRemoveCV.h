/**
 * Created by rayfalling on 2020/10/20.
 * */

#pragma once

#ifndef VISREAL_TREMOVECV_H
#define VISREAL_TREMOVECV_H

namespace Engine::Core{
    /**
     * TRemoveCV<type> will remove any const/volatile qualifiers from a type.
     * (based on std::remove_cv<>
     * note: won't remove the const from "const int*", as the pointer is not const
     */
    template <typename T> struct TRemoveCV                   { typedef T Type; };
    template <typename T> struct TRemoveCV<const T>          { typedef T Type; };
    template <typename T> struct TRemoveCV<volatile T>       { typedef T Type; };
    template <typename T> struct TRemoveCV<const volatile T> { typedef T Type; };
}

#endif //VISREAL_TREMOVECV_H

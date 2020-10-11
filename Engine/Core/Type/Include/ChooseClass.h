//
// Created by rayfalling on 2020/8/30.
//
#pragma once

#ifndef VISREAL_CHOOSE_CLASS_H
#define VISREAL_CHOOSE_CLASS_H

namespace Engine::Core::Types {
    /** 
     * Chooses between two different classes based on a boolean. 
     * */
    template<bool Predicate, typename TrueClass, typename FalseClass>
    class TChooseClass;

    template<typename TrueClass, typename FalseClass>
    class TChooseClass<true, TrueClass, FalseClass> {
    public:
        typedef TrueClass Result;
    };

    template<typename TrueClass, typename FalseClass>
    class TChooseClass<false, TrueClass, FalseClass> {
    public:
        typedef FalseClass Result;
    };
}

#endif //VISREAL_CHOOSE_CLASS_H

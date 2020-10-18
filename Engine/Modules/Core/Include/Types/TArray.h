/**
 * Created by rayfalling on 2020/10/18.
 *
 * Custom Array class, like std::vector
 * */

#ifndef VISREAL_TARRAY_H
#define VISREAL_TARRAY_H

#include <initializer_list>
#include "PlatformTypes.h"

namespace Engine::Core::Types {
    template<typename T>
    class TArray {

    public:
        TArray();
        explicit TArray(int32 capacity);
        explicit TArray(uint32 capacity);
        explicit TArray(std::initializer_list<T> initList);

    private:
        /* use count */
        uint32 _size;
        /* max item size */
        uint32 _capacity = 0;
        /* item array */
        T _data[];
        /* default capacity */
        const static uint32 _defaultArraySize;
    };


}

#endif //VISREAL_TARRAY_H

/**
 * Created by rayfalling on 2020/10/18.
 * */

#include "Types/TArray.h"

using namespace Engine::Core::Types;

template<typename T>
TArray<T>::TArray() {
    _size = 0;
    _capacity = _defaultArraySize;
}

template<typename T>
TArray<T>::TArray(int32 capacity) {
    _size = 0;
    _capacity = capacity;
}

template<typename T>
TArray<T>::TArray(uint32 capacity) {
    _size = 0;
    _capacity = capacity;
}

template<typename T>
TArray<T>::TArray(std::initializer_list<T> initList) {
    _size = initList;

}

template<typename T>
const uint32 TArray<T>::_defaultArraySize = 8;
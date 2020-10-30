/**
 * Created by rayfalling on 2020/10/30.
 * */

#pragma once

#ifndef VISREAL_CONTAINER_FORWARD_DEFINITION_H
#define VISREAL_CONTAINER_FORWARD_DEFINITION_H

namespace Engine::Core::Types {
    class FString;

    template<typename T>
    class TArray;

    template<typename KeyType, typename ValueType, typename KeyFuncs>
    class TMap;

    template<typename>
    struct TTypeTraits;

    template<typename InElementType, typename KeyFuncs>
    class TSet;
}

#endif //VISREAL_CONTAINER_FORWARD_DEFINITION_H

//
// Created by rayfalling on 2020/8/29.
//
#pragma once

#ifndef VISREAL_OBJECT_H
#define VISREAL_OBJECT_H

#include "Container/FString.h"
#include "EngineCoreExport.generate.h"

namespace Engine::Core {
    using namespace Types;

    class ENGINE_CORE_EXPORTS Object {
    private:
        FString Name;
    protected:
        Object() = default;

        virtual ~Object() = default;
    };
}

#endif //VISREAL_OBJECT_H

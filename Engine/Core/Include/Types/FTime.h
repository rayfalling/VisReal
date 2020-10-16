/**
 * Created by rayfalling on 2020/10/15.
 * */

#ifndef VISREAL_TIME_H
#define VISREAL_TIME_H

#include "FString.h"

using namespace Engine::Core::Types;

namespace Engine::Core::Types {
    class FTime {
    public:
        static FString getCurrentTime();
    };
}

#endif //VISREAL_TIME_H

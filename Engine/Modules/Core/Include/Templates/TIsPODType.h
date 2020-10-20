/**
 * Created by rayfalling on 2020/10/20.
 *
 * From Unreal Engine Source
 * */

#pragma once

#ifndef VISREAL_TISPODTYPE_H
#define VISREAL_TISPODTYPE_H

namespace Engine::Core {

    /**
     * Traits class which tests if a type is POD.
     */
    template<typename T>
    struct TIsPODType {
        enum {
            Value = __is_pod(T)
        };
    };

}
#endif //VISREAL_TISPODTYPE_H

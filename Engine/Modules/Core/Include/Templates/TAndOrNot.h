/**
 * Created by rayfalling on 2020/8/30.
 *
 * From Unreal Engine
 * */

#pragma once

#ifndef VISREAL_TAND_OR_NOT_H
#define VISREAL_TAND_OR_NOT_H

namespace Engine::Core {
    /**
     * Does a boolean AND of the ::Value static members of each type, but short-circuits if any Type::Value == false.
     */
    template<typename... Types>
    struct TAnd;

    template<bool LHSValue, typename... RHS>
    struct TAndValue {
        enum {
            Value = TAnd<RHS...>::Value
        };
    };

    template<typename... RHS>
    struct TAndValue<false, RHS...> {
        enum {
            Value = false
        };
    };

    template<typename LHS, typename... RHS>
    struct TAnd<LHS, RHS...> : TAndValue<LHS::Value, RHS...> {
    };

    template<>
    struct TAnd<> {
        enum {
            Value = true
        };
    };

    /**
     * Does a boolean OR of the ::Value static members of each type, but short-circuits if any Type::Value == true.
     */
    template<typename... Types>
    struct TOr;

    template<bool LHSValue, typename... RHS>
    struct TOrValue {
        enum {
            Value = TOr<RHS...>::Value
        };
    };

    template<typename... RHS>
    struct TOrValue<true, RHS...> {
        enum {
            Value = true
        };
    };

    template<typename LHS, typename... RHS>
    struct TOr<LHS, RHS...> : TOrValue<LHS::Value, RHS...> {
    };

    template<>
    struct TOr<> {
        enum {
            Value = false
        };
    };

    /**
     * Does a boolean NOT of the ::Value static members of the type.
     */
    template<typename Type>
    struct TNot {
        enum {
            Value = !Type::Value
        };
    };

}

#endif
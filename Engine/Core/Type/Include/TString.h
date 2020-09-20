//
// Created by rayfalling on 2020/8/29.
//
#pragma once

#ifndef VISREAL_TSTRING_H
#define VISREAL_TSTRING_H

#include <codecvt>
#include "PlatformTypes.h"

namespace Engine::Core::Types {
    /**
     * A String Class for both wstring or string
     * Using TString to avoid include string.h in std
     * */
    class TString {
    private:
        TCHAR *string;
    public:
        TString();

        explicit TString(std::string &str);

        ~TString();

        /**
         * Static method for TString
         * 
         * */
    public:
        // convert for string & wstring
        using converter = std::codecvt_utf8<WCHAR>;

        static std::wstring string2wstring(std::string& src) {
            std::wstring_convert<converter, WCHAR> WStringConverter;
            return WStringConverter.from_bytes(src);
        }
    };
}

#endif //VISREAL_TSTRING_H

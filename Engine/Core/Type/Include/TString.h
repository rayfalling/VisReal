/**
 * Created by rayfalling on 2020/8/29.
 * 
 * This file is an alternative string header for project.
 * Not use std::string in project because it not support utf-8.
 * Base type is WCHAR.
 * */
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
        /** 
         * Data ptr
         * */
        TCHAR *string = nullptr;
        
        /**
         * String Length
         * */
        uint32 length = 0;
    public:
        TString();

        explicit TString(std::string &str);

        ~TString();

        [[nodiscard]] uint32 Length() const;

        /**
         * override operator method 
         * make it can use like origin string
         * */
    public:
        TString& operator=(const TString &Another)
        {
            string = Another.string;
            length = Another.length;
            return *this;
        }

        TString& operator=(const std::string &Another)
        {
            
        }
        
        /**
         * Static method region for TString
         * */
    public:
        /**
         * static typedef for std::convert of WCHAR
         * */
        using converter = std::codecvt_utf8<WCHAR>;

        static std::wstring string2wstring(std::string &src) {
            std::wstring_convert<converter, WCHAR> WStringConverter;
            return WStringConverter.from_bytes(src);
        }
    };
}

#endif //VISREAL_TSTRING_H

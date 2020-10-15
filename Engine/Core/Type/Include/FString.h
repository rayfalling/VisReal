/**
 * Created by rayfalling on 2020/8/29.
 * 
 * This file is an alternative string header for project.
 * Not use std::string in project because it not support utf-8.
 * Base type is WCHAR.
 * */
#pragma once

#ifndef VISREAL_FSTRING_H
#define VISREAL_FSTRING_H

#include <codecvt>
#include "PlatformTypes.h"

namespace Engine::Core::Types {
    /**
     * A String Class for both wstring or string
     * Using FString to avoid include string.h in std
     * */
    class FString {
    private:
        /** 
         * Data ptr
         * */
        TCHAR *_string = nullptr;

        /**
         * String Length
         * */
        uint32 _length = 0;

        /**
         * is constructed from const value
         * */
        bool _const = false;
    public:
        FString();

        explicit FString(const FString &string);

        explicit FString(std::string &str);

        explicit FString(const std::string &str);

        explicit FString(std::wstring &str);

        explicit FString(const std::wstring &str);

        explicit FString(char *string);

        explicit FString(const char *string);

        explicit FString(char string[], int length);

        ~FString();

        [[nodiscard]] uint32 Length() const;

        /**
         * override operator method 
         * make it can use like origin string
         * */
    public:
        FString &operator=(const FString &Another);

        FString &operator=(const std::string &Another);

        std::string toString();

        /**
         * Static method region for FString
         * */
    public:
        /**
         * static typedef for std::convert of WCHAR
         * */
        using converter = std::codecvt_utf8<WCHAR>;

        /**
         * convert from string to wstring
         * */
        static std::wstring string2wstring(const std::string &src) {
            std::wstring_convert<converter, WCHAR> WStringConverter;
            return WStringConverter.from_bytes(src);
        }

        /**
         * convert from char* to wstring
         * */
        static std::wstring string2wstring(const char *src) {
            std::wstring_convert<converter, WCHAR> WStringConverter;
            return WStringConverter.from_bytes(src);
        }

        /**
         * convert from wstring to string
         * */
        static std::string wstring2string(const std::wstring &src) {
            std::wstring_convert<converter, WCHAR> WStringConverter;
            return WStringConverter.to_bytes(src);
        }

        /**
         * convert from WCHAR* to string
         * */
        static std::string wstring2string(const WCHAR *src) {
            std::wstring_convert<converter, WCHAR> WStringConverter;
            return WStringConverter.to_bytes(src);
        }
    };
}

#endif //VISREAL_FSTRING_H

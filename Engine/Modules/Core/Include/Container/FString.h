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

#include "Platform/PlatformTypes.h"
#include <codecvt>

namespace Engine::Core::Types {
/**
 * A String Class for both wstring or string
 * Using FString to avoid include string.h in std
 *
 * FString length means char length exclude '\0',
 * while in Construction methods, '\0' is also copy to FString last char
 * so it actually length is length() + 1;
 *
 * _const bool means this FString is copy from another const string/wstring.
 * Not recommend to modify inner value in FString. it's initial size is set
 * from copied value length. Thus every write operation lead to memory real-
 * -locate.
 * */
    class FString {
    private:
        /* Data ptr */
        std::shared_ptr<TCHAR[]> _string = nullptr;
        /* String Length */
        SIZE_T _length = 0;
        /* String max Length */
        SIZE_T _capacity = 0;
        /* is constructed from const value */
        bool _const = false;

    public:
        FString() noexcept;
        FString(const FString &string) noexcept;
        FString(FString &&string) noexcept;

        /* construct from std::string */
        explicit FString(std::string &str) noexcept;
        explicit FString(const std::string &str) noexcept;

        /* construct from std::wstring */
        explicit FString(std::wstring &str) noexcept;
        explicit FString(const std::wstring &str) noexcept;

        /* construct from char* */
        explicit FString(char *string) noexcept;
        explicit FString(const char *string) noexcept;

        /* construct from char[] */
        FString(char string[], int length) noexcept;

        ~FString();

        [[nodiscard]] SIZE_T Length() const;

        /**
         * override operator method
         * make it can use like origin string
         * */
    public:
        FString &operator=(const FString &Another);
        FString &operator=(const std::string &Another);

        /* overload operator==() */
        bool operator==(const FString &string);

        [[nodiscard]] std::string toString();
        [[nodiscard]] std::string toString() const;

    protected:
        std::shared_ptr<TCHAR[]> &GetSharedPtr() {
            return _string;
        }

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
        static std::wstring string2wstring(const std::string &src);

        /**
         * convert from char* to wstring
         * */
        static std::wstring string2wstring(const char *src, int length);

        /**
         * convert from wstring to string
         * */
        static std::string wstring2string(const std::wstring &src);

        /**
         * convert from WCHAR* to string
         * */
        static std::string wstring2string(const WCHAR *src, int length);
    };
} // namespace Engine::Core::Types

#endif // VISREAL_FSTRING_H

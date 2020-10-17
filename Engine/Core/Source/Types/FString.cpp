/**
 * Created by rayfalling on 2020/8/29.
 * 
 * This file is an alternative string header for project.
 * Not use std::string in project because it not support utf-8.
 * Base type is WCHAR.
 * */
#include <iostream>
#include "Types/FString.h"

using namespace Engine::Core::Types;

FString::FString() noexcept {
    _string = nullptr;
    _length = 0;
}

FString::FString(const FString &string) noexcept {
    this->_string = string._string;
    this->_length = string._length;
    this->_const = string._const;
}

FString::FString(FString &&string) noexcept:
        _string(std::move(string._string)),
        _length(string._length),
        _const(string._const) {
}

[[maybe_unused]] FString::FString(std::string &string) noexcept {
    auto w_str = string2wstring(string);
    this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
    std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
    this->_length = w_str.length();
}

FString::FString(const std::string &string) noexcept {
    auto w_str = string2wstring(string);
    this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
    std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
    this->_length = w_str.length();
    _const = true;
}

FString::FString(char *string) noexcept {
    auto w_str = string2wstring(string);
    this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
    std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
    this->_length = w_str.length();
}

FString::FString(const char *string) noexcept {
    auto w_str = string2wstring(string);
    this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
    std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
    this->_length = w_str.length();
    _const = true;
}

FString::FString(std::wstring &str) noexcept {
    this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[str.length() + 1], std::default_delete<TCHAR[]>());
    std::memcpy(this->_string.get(), str.c_str(), (str.length() + 1) * sizeof(TCHAR));
    this->_length = str.length();
}

FString::FString(const std::wstring &str) noexcept {
    this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[str.length() + 1], std::default_delete<TCHAR[]>());
    std::memcpy(this->_string.get(), str.c_str(), (str.length() + 1) * sizeof(TCHAR));
    this->_length = str.length();
    _const = true;
}

FString::FString(char string[], int length) noexcept {
    auto w_str = string2wstring(string);
    this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
    std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
    this->_length = w_str.length();
}

FString::~FString() = default;

FString &FString::operator=(const std::string &Another) {
    auto w_str = string2wstring(Another);
    this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
    std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
    this->_length = w_str.length();
    _const = true;
    return *this;
}

FString &FString::operator=(const FString &Another) = default;

uint32 FString::Length() const {
    return _length;
}

std::string FString::toString() {
    return wstring2string(_string.get());
}



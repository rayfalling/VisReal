/**
 * Created by rayfalling on 2020/8/29.
 * 
 * This file is an alternative string header for project.
 * Not use std::string in project because it not support utf-8.
 * Base type is WCHAR.
 * */
#include "FString.h"

using namespace Engine::Core::Types;

FString::FString() {
    _string = nullptr;
    _length = 0;
}

FString::FString(const FString &string) {
    this->_string = string._string;
    this->_length = string._length;
    this->_const = string._const;
}

FString::~FString() {
    delete _string;
}

FString::FString(std::string &str) {
    _string = string2wstring(str).data();
    _length = str.length();
}

FString::FString(const std::string &str) {
    _string = string2wstring(str).data();
    _length = str.length();
    _const = true;
}

FString::FString(char *string) {
    auto w_str = string2wstring(string);
    this->_string = w_str.data();
    this->_length = w_str.length();
}

FString::FString(const char *string) {
    auto w_str = string2wstring(string);
    this->_string = w_str.data();
    this->_length = w_str.length();
    _const = true;
}

FString::FString(std::wstring &str) {
    this->_string = str.data();
    this->_length = str.length();
}

FString::FString(const std::wstring &str) {
    this->_string = const_cast<TCHAR *>(str.data());
    this->_length = str.length();
    _const = true;
}

FString::FString(char string[], int length) {
    this->_string = string2wstring(string).data();
    this->_length = length;
}

FString &FString::operator=(const std::string &Another) {
    auto w_str = string2wstring(Another);
    this->_string = w_str.data();
    this->_length = w_str.length();
    return *this;
}

FString &FString::operator=(const FString &Another) = default;

uint32 FString::Length() const {
    return _length;
}

std::string FString::toString() {
    return wstring2string(_string);
}

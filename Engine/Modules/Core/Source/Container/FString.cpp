/**
 * Created by rayfalling on 2020/8/29.
 * 
 * This file is an alternative string header for project.
 * Not use std::string in project because it not support utf-8.
 * Base type is WCHAR.
 * */
#include <iostream>
#include "Container/FString.h"

using namespace Engine::Core::Types;

FString::FString() noexcept {
	_string   = std::shared_ptr<TCHAR[]>(new TCHAR[17], std::default_delete<TCHAR[]>());
	_length   = 0;
	_capacity = 16;
	_const    = false;
}

FString::FString(const FString& string) noexcept {
	this->_string   = string._string;
	this->_length   = string._length;
	this->_capacity = string._capacity;
	this->_const    = string._const;
}

FString::FString(FString&& string) noexcept = default;

FString::FString(std::string& string) noexcept {
	std::wstring w_str = string2wstring(string);
	this->_string      = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
	std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
	this->_length   = w_str.length();
	this->_capacity = w_str.length();
	_const          = false;
}

FString::FString(const std::string& string) noexcept {
	std::wstring w_str = string2wstring(string);
	this->_string      = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
	std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
	this->_length   = w_str.length();
	this->_capacity = w_str.length();
	_const          = true;
}

FString::FString(char* string) noexcept {
	std::wstring w_str = string2wstring(string);
	this->_string      = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
	std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
	this->_length   = w_str.length();
	this->_capacity = w_str.length();
	_const          = false;
}

FString::FString(const char* string) noexcept {
	std::wstring w_str = string2wstring(string);
	this->_string      = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
	std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
	this->_length   = w_str.length();
	this->_capacity = w_str.length();
	_const          = true;
}

FString::FString(std::wstring& str) noexcept {
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[str.length() + 1], std::default_delete<TCHAR[]>());
	std::memcpy(this->_string.get(), str.c_str(), (str.length() + 1) * sizeof(TCHAR));
	this->_length   = str.length();
	this->_capacity = str.length();
	_const          = false;
}

FString::FString(const std::wstring& str) noexcept {
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[str.length() + 1], std::default_delete<TCHAR[]>());
	std::memcpy(this->_string.get(), str.c_str(), (str.length() + 1) * sizeof(TCHAR));
	this->_length   = str.length();
	this->_capacity = str.length();
	_const          = true;
}

FString::FString(char string[], int length) noexcept {
	std::wstring w_str = string2wstring(string);
	this->_string      = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
	std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
	this->_length   = w_str.length();
	this->_capacity = w_str.length();
	_const          = false;
}

FString::~FString() = default;

FString& FString::operator=(const std::string& Another) {
	auto w_str    = string2wstring(Another);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
	std::memcpy(this->_string.get(), w_str.c_str(), (w_str.length() + 1) * sizeof(TCHAR));
	this->_length   = w_str.length();
	this->_capacity = w_str.length();
	_const          = true;
	return *this;
}

FString& FString::operator=(const FString& Another) = default;

SIZE_T FString::Length() const {
	return _length;
}

std::string FString::toString() {
	return wstring2string(_string.get());
}

std::string FString::toString() const {
	return wstring2string(_string.get());
}

std::wstring FString::string2wstring(const std::string& src) {
	std::wstring_convert<converter, WCHAR> WStringConverter;
	return WStringConverter.from_bytes(src);
}

std::wstring FString::string2wstring(const char* src, int length) {
	std::wstring_convert<converter, WCHAR> WStringConverter;
	return WStringConverter.from_bytes(src, src + sizeof(char) * length);
}

std::string FString::wstring2string(const std::wstring& src) {
	std::wstring_convert<converter, WCHAR> WStringConverter;
	return WStringConverter.to_bytes(src);
}

std::string FString::wstring2string(const WCHAR* src, int length) {
	std::wstring_convert<converter, WCHAR> WStringConverter;
	return WStringConverter.to_bytes(src, src + sizeof(TCHAR) * length);
}

bool FString::operator==(const FString& string) {
	return _string == string._string && _length == string._length;
}

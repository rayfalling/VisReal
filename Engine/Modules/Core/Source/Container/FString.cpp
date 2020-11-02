/**
 * Created by rayfalling on 2020/8/29.
 * 
 * This file is an alternative string header for project.
 * Not use std::string in project because it not support utf-8.
 * Base type is WCHAR.
 * */
#include <iostream>
#include "Container/FString.h"

#include "Memory/MemoryUtils.h"

using namespace Engine::Core::Types;

FString::FString() noexcept {
	_string = std::shared_ptr<TCHAR[]>(new TCHAR[17], std::default_delete<TCHAR[]>());
	_length = 0;
	_capacity = 16;
	_const = false;
}

FString::FString(const FString& string) noexcept {
	this->_string = string._string;
	this->_length = string._length;
	this->_capacity = string._capacity;
	this->_const = string._const;
}

FString::FString(FString&& string) noexcept {
	this->_string.swap(string._string);
	this->_length = string._length;
	this->_capacity = string._capacity;
	this->_const = string._const;
}

FString::FString(std::string& string) {
	const auto wStr = String2Wstring(string);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
	_const = false;
}

FString::FString(const std::string& string) {
	const auto wStr = String2Wstring(string);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
	_const = true;
}

FString::FString(char* string) {
	const auto wStr = String2Wstring(string);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
	_const = false;
}

FString::FString(const char* string) {
	const auto w_str = String2Wstring(string);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[w_str.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), w_str.c_str(), w_str.length() + 1);
	this->_length = w_str.length();
	this->_capacity = w_str.length();
	_const = true;
}

FString::FString(std::wstring& str) {
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[str.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), str.c_str(), str.length() + 1);
	this->_length = str.length();
	this->_capacity = str.length();
	_const = false;
}

FString::FString(const std::wstring& str) {
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[str.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), str.c_str(), str.length() + 1);
	this->_length = str.length();
	this->_capacity = str.length();
	_const = true;
}

FString::FString(char string[], const int length) {
	const auto wStr = String2Wstring(string, length);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
	_const = false;
}

FString::~FString() = default;

FString& FString::operator=(const FString& another) {
	if (this != &another) {
		this->_string = another._string;
		this->_length = another._length;
		this->_capacity = another._capacity;
		this->_const = another._const;
	}
	return *this;
};

FString& FString::operator=(FString&& another) noexcept {
	if (this != &another) {
		this->_string.swap(another._string);
		this->_length = another._length;
		this->_capacity = another._capacity;
		this->_const = another._const;
	}
	return *this;
}

FString& FString::operator=(const std::string& another) {
	const auto wStr = String2Wstring(another);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
	_const = true;
	return *this;
}

FString& FString::operator=(std::string&& another) {
	const auto wStr = String2Wstring(another);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	MoveAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
	_const = true;
	return *this;
}

SIZE_T FString::Length() const {
	return _length;
}

std::string FString::ToString() {
	return Wstring2String(_string.get());
}

std::string FString::ToString() const {
	return Wstring2String(_string.get());
}

TCHAR* FString::GetData() const {
	return _string.get();
}

void FString::Append(FString& string) {
	_capacity = string.Length() + _length;
	auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity], std::default_delete<TCHAR[]>());
	MoveAssignItems(newData.get(), _string.get(), _length);
	CopyAssignItems(newData.get() + _length - 1, string.GetData(), string.Length() + 1);
	_string.swap(newData);
	_length = _capacity;
}

void FString::Append(const FString& string) {
	_capacity = string.Length() + _length;
	auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity], std::default_delete<TCHAR[]>());
	MoveAssignItems(newData.get(), _string.get(), _length);
	CopyAssignItems(newData.get() + _length - 1, string.GetData(), string.Length() + 1);
	_string.swap(newData);
	_length = _capacity;
}

void FString::Append(FString&& string) {
	_capacity = string.Length() + _length;
	auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity], std::default_delete<TCHAR[]>());
	MoveAssignItems(newData.get(), _string.get(), _length);
	MoveAssignItems(newData.get() + _length - 1, string.GetData(), string.Length() + 1);
	_string.swap(newData);
	_length = _capacity;
}

void FString::Append(std::string& string) {
	const auto wStr = String2Wstring(string);
	_capacity = wStr.length() + _length;
	auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity], std::default_delete<TCHAR[]>());
	MoveAssignItems(newData.get(), _string.get(), _length);
	CopyAssignItems(newData.get() + _length - 1, wStr.c_str(), wStr.length() + 1);
	_string.swap(newData);
	_length = _capacity;
}

void FString::Append(const std::string& string) {
	const auto wStr = String2Wstring(string);
	_capacity = wStr.length() + _length;
	auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity], std::default_delete<TCHAR[]>());
	MoveAssignItems(newData.get(), _string.get(), _length);
	CopyAssignItems(newData.get() + _length - 1, wStr.c_str(), wStr.length() + 1);
	_string.swap(newData);
	_length = _capacity;
}

void FString::Append(std::string&& string) {
	const auto wStr = String2Wstring(string);
	_capacity = wStr.length() + _length;
	auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity], std::default_delete<TCHAR[]>());
	MoveAssignItems(newData.get(), _string.get(), _length);
	MoveAssignItems(newData.get() + _length - 1, wStr.c_str(), wStr.length() + 1);
	_string.swap(newData);
	_length = _capacity;
}

std::wstring FString::String2Wstring(const std::string& src) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.from_bytes(src);
}

std::wstring FString::String2Wstring(const CHAR* src, const int length) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.from_bytes(src, src + length);
}

std::string FString::Wstring2String(const std::wstring& src) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.to_bytes(src);
}

std::string FString::Wstring2String(const WCHAR* src, const int length) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.to_bytes(src, src + length);
}

bool FString::operator==(const FString& string) const {
	return _string == string._string && _length == string._length;
}

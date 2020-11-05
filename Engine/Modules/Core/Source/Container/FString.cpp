/**
 * Created by rayfalling on 2020/8/29.
 * 
 * This file is an alternative string header for project.
 * Not use std::string in project because it not support utf-8.
 * Base type is WCHAR.
 * */

#include "Container/FString.h"

#include <cstdlib>
#include <iostream>
#include "Container/TArray.h"
#include "Marco/Constant.h"
#include "Memory/MemoryUtils.h"

using namespace Engine::Core::Types;

FString::FString() noexcept {
	_string = std::shared_ptr<TCHAR[]>(new TCHAR[17], std::default_delete<TCHAR[]>());
	_length = 0;
	_capacity = 16;
}

FString::FString(const FString& string) noexcept {
	this->_string = string._string;
	this->_length = string._length;
	this->_capacity = string._capacity;
}

FString::FString(FString&& string) noexcept {
	this->_string.swap(string._string);
	this->_length = string._length;
	this->_capacity = string._capacity;
}

FString::FString(const SIZE_T capacity) noexcept {
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[capacity + 1], std::default_delete<TCHAR[]>());;
	this->_length = 0;
	this->_capacity = capacity;
}

FString::FString(std::string& string) {
	const auto wStr = String2Wstring(string);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
}

FString::FString(const std::string& string) {
	const auto wStr = String2Wstring(string);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
}

FString::FString(char* string) {
	const auto wStr = String2Wstring(string);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
}

FString::FString(const char* string) {
	const auto wStr = String2Wstring(string);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
}

FString::FString(std::wstring& str) {
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[str.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), str.c_str(), str.length() + 1);
	this->_length = str.length();
	this->_capacity = str.length();
}

FString::FString(const std::wstring& str) {
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[str.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), str.c_str(), str.length() + 1);
	this->_length = str.length();
	this->_capacity = str.length();
}

FString::FString(CHAR string[], const SIZE_T length) {
	const auto wStr = String2Wstring(string, length);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
}

FString::FString(WCHAR string[], const SIZE_T length) {
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[length + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), string, length + 1);
	this->_length = length;
	this->_capacity = length;
}

FString::~FString() = default;

FString& FString::operator=(const FString& another) {
	if (this != &another) {
		this->_string = another._string;
		this->_length = another._length;
		this->_capacity = another._capacity;
	}
	return *this;
};

FString& FString::operator=(FString&& another) noexcept {
	if (this != &another) {
		this->_string.swap(another._string);
		this->_length = another._length;
		this->_capacity = another._capacity;
	}
	return *this;
}

FString& FString::operator=(const std::string& another) {
	const auto wStr = String2Wstring(another);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
	return *this;
}

FString& FString::operator=(std::string&& another) {
	const auto wStr = String2Wstring(another);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	MoveAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
	return *this;
}

SIZE_T FString::Length() const {
	return _length;
}

std::string FString::ToString() {
	return Wstring2String(_string.get(), _length);
}

std::string FString::ToString() const {
	return Wstring2String(_string.get(), _length);
}

TCHAR* FString::GetData() const {
	return _string.get();
}

void FString::Append(FString& string) {
	if (_capacity < string.Length() + _length) {
		_capacity = string.Length() + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		CopyAssignItems(newData.get() + _length, string.GetData(), string.Length() + 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		CopyAssignItems(_string.get() + _length, string.GetData(), string.Length() + 1);
		_length += string.Length();
	}
}

void FString::Append(const FString& string) {
	if (_capacity < string.Length() + _length) {
		_capacity = string.Length() + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		CopyAssignItems(newData.get() + _length, string.GetData(), string.Length() + 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		CopyAssignItems(_string.get() + _length, string.GetData(), string.Length() + 1);
		_length += string.Length();
	}
}

void FString::Append(FString&& string) {
	if (_capacity < string.Length() + _length) {
		_capacity = string.Length() + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		MoveAssignItems(newData.get() + _length, string.GetData(), string.Length() + 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		CopyAssignItems(_string.get() + _length, string.GetData(), string.Length() + 1);
		_length += string.Length();
	}
}

void FString::Append(std::string& string) {
	const auto wStr = String2Wstring(string);
	if (_capacity < string.length() + _length) {
		_capacity = wStr.length() + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		CopyAssignItems(newData.get() + _length, wStr.c_str(), wStr.length() + 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		CopyAssignItems(_string.get() + _length, wStr.c_str(), wStr.length() + 1);
		_length += wStr.length();
	}
}

void FString::Append(const std::string& string) {
	const auto wStr = String2Wstring(string);
	if (_capacity < string.length() + _length) {
		_capacity = wStr.length() + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		CopyAssignItems(newData.get() + _length, wStr.c_str(), wStr.length() + 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		CopyAssignItems(_string.get() + _length, wStr.c_str(), wStr.length() + 1);
		_length += wStr.length();
	}
}

void FString::Append(std::string&& string) {
	const auto wStr = String2Wstring(string);
	if (_capacity < string.length() + _length) {
		_capacity = wStr.length() + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		MoveAssignItems(newData.get() + _length, wStr.c_str(), wStr.length() + 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		MoveAssignItems(_string.get() + _length, wStr.c_str(), wStr.length() + 1);
		_length += wStr.length();
	}
}

void FString::Append(std::wstring& string) {
	if (_capacity < string.length() + _length) {
		_capacity = string.length() + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		CopyAssignItems(newData.get() + _length, string.c_str(), string.length() + 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		MoveAssignItems(_string.get() + _length, string.c_str(), string.length() + 1);
		_length += string.length();
	}
}

void FString::Append(const std::wstring& string) {
	if (_capacity < string.length() + _length) {
		_capacity = string.length() + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		CopyAssignItems(newData.get() + _length, string.c_str(), string.length() + 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		MoveAssignItems(_string.get() + _length, string.c_str(), string.length() + 1);
		_length += string.length();
	}
}

void FString::Append(std::wstring&& string) {
	if (_capacity < string.length() + _length) {
		_capacity = string.length() + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		MoveAssignItems(newData.get() + _length, string.c_str(), string.length() + 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		MoveAssignItems(_string.get() + _length, string.c_str(), string.length() + 1);
		_length += string.length();
	}
}

void FString::AppendChar(CHAR ch) {
	wchar_t wstring[1];
	#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
	std::mbstowcs(wstring, &ch, 1);
	#else
	std::mbstowcs(wstring, &ch, 1);
	#endif
	if (_capacity < 1 + _length) {
		_capacity = 1 + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		MoveAssignItems(newData.get() + _length, wstring, 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		MoveAssignItems(_string.get() + _length, wstring, 1);
		_length += 1;
	}
}

void FString::AppendChar(WCHAR ch) {
	if (_capacity < 1 + _length) {
		_capacity = 1 + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		MoveAssignItems(newData.get() + _length, &ch, 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		MoveAssignItems(_string.get() + _length, &ch, 1);
		_length += 1;
	}
}

TArray<FString> FString::Split(const CHAR separator) const {
	TArray<FString> array;
	SIZE_T it = 0, start = it;
	while (it < _length) {
		if (*(_string.get() + it) == separator) {
			array.Add(this->SubString(start, it - 1));
			start = it + 1;
			it++;
		}
		it++;
	}

	/* add the last string */
	if (start != _length) {
		array.Add(this->SubString(start, it));
	}

	return array;
}

FString FString::SubString(const SIZE_T start, const SIZE_T end) const {
	if (start > end || end > _length) {
		CoreLog::GetInstance().LogError(FSTRING_OUT_OF_INDEX_ERROR);
	}
	/*TODO error*/
	FString string(end - start + 1);
	string._length = end - start + 1;
	CopyAssignItems(string._string.get(), _string.get() + start, end - start + 1);
	return string;
}

FString FString::SubStringAt(const SIZE_T index, const SIZE_T count) const {
	if (index + count > _length) {
		CoreLog::GetInstance().LogError(FSTRING_OUT_OF_INDEX_ERROR);
	}
	/*TODO error*/
	FString string(count);
	string._length = count;
	CopyAssignItems(string._string.get(), _string.get() + index, count);
	return string;
}

std::wstring FString::String2Wstring(const std::string& src) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.from_bytes(src);
}

std::wstring FString::String2Wstring(const CHAR* src, const SIZE_T length) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.from_bytes(src, src + length);
}

std::string FString::Wstring2String(const std::wstring& src) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.to_bytes(src);
}

std::string FString::Wstring2String(const WCHAR* src, const SIZE_T length) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.to_bytes(src, src + length);
}

bool FString::operator==(const FString& string) const {
	return _string == string._string && _length == string._length;
}

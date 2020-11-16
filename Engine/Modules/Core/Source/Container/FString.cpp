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

FString::FString(const IndexType capacity) noexcept {
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[capacity + 1], std::default_delete<TCHAR[]>());
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

FString::FString(CHAR string[], const IndexType length) {
	const auto wStr = String2Wstring(string, length);
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[wStr.length() + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), wStr.c_str(), wStr.length() + 1);
	this->_length = wStr.length();
	this->_capacity = wStr.length();
}

FString::FString(WCHAR string[], const IndexType length) {
	this->_string = std::shared_ptr<TCHAR[]>(new TCHAR[length + 1], std::default_delete<TCHAR[]>());
	CopyAssignItems(this->_string.get(), string, length + 1);
	this->_length = length;
	this->_capacity = length;
}

FString::~FString() = default;

FString& FString::operator=(const FString& another) noexcept {
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

TCHAR& FString::operator[](IndexType& index) const {
	CheckIndex(index);
	return _string[index];
}

TCHAR& FString::operator[](const IndexType& index) const {
	CheckIndex(index);
	return _string[index];
}

TCHAR& FString::operator[](IndexType&& index) const {
	CheckIndex(index);
	return _string[index];
}

bool FString::operator==(const FString& string) const {
	return Equal(string);
}

bool FString::operator==(const std::string& string) const {
	return Equal(string);
}

bool FString::operator==(const std::wstring& string) const {
	return Equal(string);
}

FString::ReturnIndexType FString::Length() const {
	return _length;
}

std::string FString::ToString() {
	return Wstring2String(_string.get(), _length);
}

std::string FString::ToString() const {
	return Wstring2String(_string.get(), _length);
}

std::wstring FString::ToWString() {
	return std::wstring(_string.get(), _length);
}

std::wstring FString::ToWString() const {
	return std::wstring(_string.get(), _length);
}

TCHAR* FString::GetData() const {
	return _string.get();
}

FString::ReturnIndexType FString::BruteForceSearch(const FString& string) const {
	IndexType currentIndex = 0, searchIndex = 0;
	const auto length = string._length;
	auto isFind = false;
	while (!isFind) {
		auto* first = wmemchr(_string.get() + searchIndex, string[0], _length - searchIndex);
		if (_length - searchIndex < length || !first)
			return INDEX_NONE;
		searchIndex = currentIndex = first - _string.get();
		for (auto index = 0u; index < length; index ++) {
			if (_string[currentIndex + index] != string._string[index]) {
				searchIndex = currentIndex + index;
				isFind = false;
				break;
			}
			isFind = true;
		}
	}
	if (isFind)
		return currentIndex;
	return INDEX_NONE;
}

FString::ReturnIndexType FString::BoyerMooreHorspoolSearch(const FString& string) const {
	auto* const findPtr = std::search(
			_string.get(),
			_string.get() + _length,
			std::boyer_moore_horspool_searcher<wchar_t*>(
					string._string.get(),
					string._string.get() + string._length
					)
			);
	if (findPtr != _string.get() + _length)
		return std::distance(_string.get(), findPtr);
	return INDEX_NONE;

}

FString& FString::Append(const FString& string) {
	std::unique_lock<std::mutex> lock(_mutex);
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
	return *this;
}

FString& FString::Append(FString&& string) {
	std::unique_lock<std::mutex> lock(_mutex);
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
	return *this;
}

FString& FString::Append(const std::string& string) {
	std::unique_lock<std::mutex> lock(_mutex);
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
	return *this;
}

FString& FString::Append(std::string&& string) {
	std::unique_lock<std::mutex> lock(_mutex);
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
	return *this;
}

FString& FString::Append(const std::wstring& string) {
	std::unique_lock<std::mutex> lock(_mutex);
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
	return *this;
}

FString& FString::Append(std::wstring&& string) {
	std::unique_lock<std::mutex> lock(_mutex);
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
	return *this;
}

FString& FString::AppendChar(const CHAR& ch) {
	std::unique_lock<std::mutex> lock(_mutex);
	TCHAR wstring;
	#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
	std::mbstowcs(&wstring, &ch, 1);
	#else
	std::mbstowcs(&wstring, &ch, 1);
	#endif
	if (_capacity < 1 + _length) {
		_capacity = 1 + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		CopyAssignItems(newData.get() + _length, &wstring, 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		MoveAssignItems(_string.get() + _length, &wstring, 1);
		_length += 1;
	}
	return *this;
}

FString& FString::AppendChar(CHAR&& ch) {
	std::unique_lock<std::mutex> lock(_mutex);
	TCHAR wstring;
	#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
	std::mbstowcs(&wstring, &ch, 1);
	#else
	std::mbstowcs(&wstring, &ch, 1);
	#endif
	if (_capacity < 1 + _length) {
		_capacity = 1 + _length;
		auto newData = std::shared_ptr<TCHAR[]>(new TCHAR[_capacity + 1], std::default_delete<TCHAR[]>());
		MoveAssignItems(newData.get(), _string.get(), _length + 1);
		MoveAssignItems(newData.get() + _length, &wstring, 1);
		_string.swap(newData);
		_length = _capacity;
	} else {
		MoveAssignItems(_string.get() + _length, &wstring, 1);
		_length += 1;
	}
	return *this;
}

FString& FString::AppendChar(const WCHAR& ch) {
	std::unique_lock<std::mutex> lock(_mutex);
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
	return *this;
}

FString& FString::AppendChar(WCHAR&& ch) {
	std::unique_lock<std::mutex> lock(_mutex);
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
	return *this;
}

int32 FString::CompareTo(const FString& string) const {
	const auto length = Math::FMath::Min(_length, string._length);
	for (auto index = 0u; index < length; index++) {
		if (_string[index] == string._string[index])
			continue;
		return _string[index] < string._string[index] ? -1 : 1;
	}
	return _length == string._length ? 0 : _length < string._length ? -1 : 1;
}

int32 FString::CompareTo(const std::string& string) const {
	return CompareTo(FString(string));
}

int32 FString::CompareTo(const std::wstring& string) const {
	return CompareTo(FString(string));
}

bool FString::Equal(const FString& string) const {
	return _length == string._length && CompareItems(_string.get(), string.GetData(), _length);
}

bool FString::Equal(const std::string& string) const {
	return Equal(FString(string));
}

bool FString::Equal(const std::wstring& string) const {
	return Equal(FString(string));
}

bool FString::EndWith(const FString& string) const {
	if (string._length > _length) return false;
	for (auto index = 1u; index <= string._length; index++) {
		if (_string[_length - index] == string._string[string._length - index])
			continue;
		return false;
	}
	return true;
}

bool FString::EndWith(const std::string& string) const {
	return EndWith(FString(string));
}

bool FString::EndWith(const std::wstring& string) const {
	return EndWith(FString(string));
}

TArray<FString> FString::Split(const CHAR& separator) const {
	TArray<FString> array;
	IndexType it = 0, start = it;
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

bool FString::StartWith(const FString& string) const {
	if (string._length > _length) return false;
	for (auto index = 0u; index < string._length; index++) {
		if (_string[index] == string._string[index])
			continue;
		return false;
	}
	return true;
}

bool FString::StartWith(const std::string& string) const {
	return StartWith(FString(string));
}

bool FString::StartWith(const std::wstring& string) const {
	return StartWith(FString(string));
}

FString::ReturnIndexType FString::IndexOf(const CHAR& ch) const {
	TCHAR wch;
	#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
	std::mbstowcs(wstring, &ch, 1);
	#else
	std::mbstowcs(&wch, &ch, 1);
	#endif
	return IndexOf(wch);
}

FString::ReturnIndexType FString::IndexOf(const WCHAR& ch) const {
	auto* first = wmemchr(_string.get(), ch, _length);
	if (first) return first - _string.get();
	return INDEX_NONE;
}

FString::ReturnIndexType FString::IndexOf(const FString& string) const {
	if (string._length > _searchLengthLimit) {
		return BoyerMooreHorspoolSearch(string);
	}
	return BruteForceSearch(string);
}

FString::ReturnIndexType FString::IndexOf(const std::string& string) const {
	return IndexOf(FString(string));
}

FString::ReturnIndexType FString::IndexOf(const std::wstring& string) const {
	return IndexOf(FString(string));
}

FString::ReturnIndexType FString::LastIndexOf(const CHAR& ch) const {
	TCHAR wch;
	#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
	std::mbstowcs(wstring, &ch, 1);
	#else
	std::mbstowcs(&wch, &ch, 1);
	#endif
	return LastIndexOf(wch);
}

FString::ReturnIndexType FString::LastIndexOf(const WCHAR& ch) const {
	for (ReturnIndexType index = _length - 1; index >= 0; index--) {
		if (_string[index] == ch)
			return index;
	}
	return INDEX_NONE;
}

FString::ReturnIndexType FString::LastIndexOf(const FString& string) const {
	auto* findPtr = std::find_end(_string.get(), _string.get() + _length, string._string.get(), string._string.get() + string._length);
	if (findPtr == string._string.get() + string._length) {
		return INDEX_NONE;
	}
	return std::distance(_string.get(), findPtr);
}

FString::ReturnIndexType FString::LastIndexOf(const std::string& string) const {
	return LastIndexOf(FString(string));
}

FString::ReturnIndexType FString::LastIndexOf(const std::wstring& string) const {
	return LastIndexOf(FString(string));
}

FString FString::SubString(const IndexType start, const IndexType end) const {
	if (start > end || end > _length) {
		CoreLog::GetInstance().LogError(FSTRING_OUT_OF_INDEX_ERROR);
	}
	FString string(end - start + 1);
	string._length = end - start + 1;
	CopyAssignItems(string._string.get(), _string.get() + start, end - start + 1);
	return string;
}

FString FString::SubStringAt(const IndexType index, const IndexType count) const {
	if (index + count > _length) {
		CoreLog::GetInstance().LogError(FSTRING_OUT_OF_INDEX_ERROR);
	}
	FString string(count);
	string._length = count;
	CopyAssignItems(string._string.get(), _string.get() + index, count);
	return string;
}

FString& FString::Trim() {
	TrimStart();
	TrimEnd();
	return *this;
}

FString& FString::TrimStart() {
	IndexType count = 0;
	for (auto index = 0u; index < _length; index++) {
		if (_string[index] == _space)
			count++;
		else break;
	}
	return RemoveRange(0, count);
}

FString& FString::TrimEnd() {
	IndexType count = 0;
	for (ReturnIndexType index = _length - 1; index >= 0; --index) {
		if (_string[index] == _space)
			count++;
		else break;
	}
	return RemoveRange(_length - 1 - count, count);
}

FString& FString::Replace(FString& pattern, FString& replace) {
	std::unique_lock<std::mutex> lock(_mutex);
	/* TODO */
	return *this;
}

FString& FString::Remove(const IndexType index) {
	std::unique_lock<std::mutex> lock(_mutex);
	CheckIndex(index);
	MoveAssignItems(_string.get() + index, _string.get() + index + 1, _length - index - 1);
	_length = _length - 1;
	return *this;
}

FString& FString::RemoveRange(const IndexType index, const IndexType count) {
	std::unique_lock<std::mutex> lock(_mutex);
	CheckIndex(index);
	CheckIndex(index + count);
	MoveAssignItems(_string.get() + index, _string.get() + index + count, _length - index - count);
	_length = _length - count;
	return *this;
}

FString& FString::ResizeShrink() {
	std::unique_lock<std::mutex> lock(_mutex);
	const auto newPtr = std::shared_ptr<TCHAR[]>(new TCHAR[_length + 1], std::default_delete<TCHAR[]>());
	MoveAssignItems(newPtr.get(), _string.get(), _length + 1);
	this->_capacity = _length;
	return *this;
}

void FString::CheckIndex(const IndexType index) const {
	if (index > _length - 1 || _length == 0) {
		CoreLog::GetInstance().LogError(FSTRING_OUT_OF_INDEX_ERROR);
	}
}

std::wstring FString::String2Wstring(const std::string& src) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.from_bytes(src);
}

std::wstring FString::String2Wstring(const CHAR* src, const IndexType length) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.from_bytes(src, src + length);
}

std::string FString::Wstring2String(const std::wstring& src) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.to_bytes(src);
}

std::string FString::Wstring2String(const WCHAR* src, const IndexType length) {
	std::wstring_convert<converter, WCHAR> wStringConverter;
	return wStringConverter.to_bytes(src, src + length);
}

FString FString::operator+(const FString& another) const {
	return FString(*this).Append(another);
}

FString FString::operator+(const std::string& another) const {
	return FString(*this).Append(another);
}

FString FString::operator+(const std::wstring& another) const {
	return FString(*this).Append(another);
}

FString FString::operator+(const CHAR& another) const {
	return FString(*this).AppendChar(another);
}

FString FString::operator+(const WCHAR& another) const {
	return FString(*this).AppendChar(another);
}

FString& FString::operator+=(const FString& another) {
	return Append(another);
}

FString& FString::operator+=(const std::string& another) {
	return Append(another);
}

FString& FString::operator+=(const std::wstring& another) {
	return Append(another);
}

FString& FString::operator+=(const CHAR& another) {
	return AppendChar(another);
}

FString& FString::operator+=(const WCHAR& another) {
	return AppendChar(another);
}

const TCHAR* FString::Begin() const {
	return _string.get();
}

const TCHAR* FString::End() const {
	return _string.get() + _length;
}

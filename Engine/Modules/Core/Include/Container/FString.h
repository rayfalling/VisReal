/**
 * Created by rayfalling on 2020/8/29.
 *
 * This file is an alternative string header for project.
 * Not use std::string in project because it not support utf-8.
 * Base type is WCHAR.
 * */
#pragma once

#ifndef VISREAL_F_STRING_H
#define VISREAL_F_STRING_H

#include <codecvt>
#include <spdlog/fmt/fmt.h>

#include "Memory/MemoryUtils.h"
#include "Platform/PlatformTypes.h"

namespace Engine::Core::Types {

	template <typename T>
	class TArray;

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

		/* define index type */
		#ifdef PLATFORM_64BITS
		typedef uint64 IndexType;
		typedef int64 ReturnIndexType;
		#else
		typedef uint32 IndexType;
		typedef int32 ReturnIndexType;
		#endif

		private:
			/* Data ptr */
			std::shared_ptr<TCHAR[]> _string = nullptr;
			/* String Length */
			IndexType _length = 0;
			/* String max Length */
			IndexType _capacity = 0;
			/* Length to detect use which method */
			IndexType _searchLengthLimit = 8;

		public:
			/* construct for an empty string with default capacity 16 */
			FString() noexcept;
			FString(const FString& string) noexcept;
			FString(FString&& string) noexcept;

			/* construct for an empty string with specific capacity */
			explicit FString(IndexType capacity) noexcept;

			/* construct from std::string */
			explicit FString(std::string& string);
			explicit FString(const std::string& string);

			/* construct from std::wstring */
			explicit FString(std::wstring& str);
			explicit FString(const std::wstring& str);

			/* construct from char* */
			explicit FString(char* string);
			explicit FString(const char* string);

			/* construct from char[] */
			FString(CHAR string[], IndexType length);
			FString(WCHAR string[], IndexType length);

			~FString();

			[[nodiscard]] ReturnIndexType Length() const;

			/**
			 * override operator method
			 * make it can use like origin string
			 * */
		public:
			FString& operator=(const FString& another) noexcept;
			FString& operator=(FString&& another) noexcept;
			FString& operator=(const std::string& another);
			FString& operator=(std::string&& another);

			/* return TCHAR at index */
			TCHAR& operator[](IndexType& index) const;

			/* return TCHAR at index */
			TCHAR& operator[](const IndexType& index) const;

			/* return TCHAR at index */
			TCHAR& operator[](IndexType&& index) const;

			bool operator==(const FString& string) const;
			bool operator==(const std::string& string) const;
			bool operator==(const std::wstring& string) const;
		
			FString operator+(const FString& another) const;
			FString operator+(const std::string& another) const;
			FString operator+(const std::wstring& another) const;

			FString operator+(const CHAR& another) const;
			FString operator+(const WCHAR& another) const;

			FString& operator+=(const FString& another);
			FString& operator+=(const std::string& another);
			FString& operator+=(const std::wstring& another);
		
			FString& operator+=(const CHAR& another);
			FString& operator+=(const WCHAR& another);

			[[nodiscard]] std::string ToString();
			[[nodiscard]] std::string ToString() const;

			[[nodiscard]] TCHAR* GetData() const;

		private:
			/* brute force search */
			[[nodiscard]] ReturnIndexType BruteForceSearch(const FString& string) const;
			/* Boyer Moore Horspool string search method */
			[[nodiscard]] ReturnIndexType BoyerMooreHorspoolSearch(const FString& string) const;

		public:
			/**
			 * Append another string to current string
			 * */
			FString& Append(const FString& string);

			/**
			 * Append another string to current string
			 * */
			FString& Append(FString&& string);

			/**
			 * Append another string to current string
			 * */
			FString& Append(const std::string& string);

			/**
			 * Append another string to current string
			 * */
			FString& Append(std::string&& string);

			/**
			 * Append another string to current string
			 * */
			FString& Append(const std::wstring& string);

			/**
			 * Append another string to current string
			 * */
			FString& Append(std::wstring&& string);

			/**
			 * Append a single char current string
			 * */
			FString& AppendChar(const CHAR& ch);

			/**
			 * Append a single char current string
			 * */
			FString& AppendChar(CHAR&& ch);

			/**
			 * Append a single char current string
			 * */
			FString& AppendChar(const WCHAR& ch);

			/**
			 * Append a single char current string
			 * */
			FString& AppendChar(WCHAR&& ch);

			/**
			 * Compare two string by dictionary order
			 *
			 * @return 0 is equal, -1 is less than the compared one, 1 is more than the compared one.
			 * */
			[[nodiscard]] int32 CompareTo(const FString& string) const;

			/**
			 * Compare two string by dictionary order
			 *
			 * @return 0 is equal, -1 is less than the compared one, 1 is more than the compared one.
			 * */
			[[nodiscard]] int32 CompareTo(const std::string& string) const;
			/**
			 * Compare two string by dictionary order
			 *
			 * @return 0 is equal, -1 is less than the compared one, 1 is more than the compared one.
			 * */
			[[nodiscard]] int32 CompareTo(const std::wstring& string) const;

			/* if two strings are equal */
			[[nodiscard]] bool Equal(const FString& string) const;
		
			/* if two strings are equal */
			[[nodiscard]] bool Equal(const std::string& string) const;

			/* if two strings are equal */
			[[nodiscard]] bool Equal(const std::wstring& string) const;

			/* find the first position of a sub string */
			[[nodiscard]] ReturnIndexType IndexOf(const CHAR& ch) const;

			/* find the first position of a sub string */
			[[nodiscard]] ReturnIndexType IndexOf(const WCHAR& ch) const;

			/* find the first position of a sub string */
			[[nodiscard]] ReturnIndexType IndexOf(const FString& string) const;

			/* find the first position of a sub string */
			[[nodiscard]] ReturnIndexType IndexOf(const std::string& string) const;

			/* find the first position of a sub string */
			[[nodiscard]] ReturnIndexType IndexOf(const std::wstring& string) const;

			/* find the last position of a sub string */
			[[nodiscard]] ReturnIndexType LastIndexOf(const CHAR& ch) const;

			/* find the last position of a sub string */
			[[nodiscard]] ReturnIndexType LastIndexOf(const WCHAR& ch) const;

			/* find the last position of a sub string */
			[[nodiscard]] ReturnIndexType LastIndexOf(const FString& string) const;

			/* find the last position of a sub string */
			[[nodiscard]] ReturnIndexType LastIndexOf(const std::string& string) const;

			/* find the last position of a sub string */
			[[nodiscard]] ReturnIndexType LastIndexOf(const std::wstring& string) const;
		
			/**
			 * Split the string to multi string by separator
			 * */
			[[nodiscard]] TArray<FString> Split(const CHAR& separator) const;

			/**
			 * if the string is start with a given one
			 * */
			[[nodiscard]] bool StartWith(const FString& string) const;

			/**
			 * if the string is start with a given one
			 * */
			[[nodiscard]] bool StartWith(const std::string& string) const;

			/**
			 * if the string is start with a given one
			 * */
			[[nodiscard]] bool StartWith(const std::wstring& string) const;
		
			/**
			 * Get a sub string of current form [start, end]
			 *
			 * @param start		start index
			 * @param end		end index
			 * */
			[[nodiscard]] FString SubString(IndexType start, IndexType end) const;

			/**
			 * Get a sub string of current
			 *
			 * @param index		start index
			 * @param count		substring counts
			 * */
			[[nodiscard]] FString SubStringAt(IndexType index, IndexType count) const;

		protected:
			std::shared_ptr<TCHAR[]>& GetSharedPtr() {
				return _string;
			}

		private:
			/* check if the index is out of array size */
			void CheckIndex(IndexType index) const;

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
			static std::wstring String2Wstring(const std::string& src);

			/**
			 * convert from char* to wstring
			 * */
			static std::wstring String2Wstring(const char* src, IndexType length);

			/**
			 * convert from wstring to string
			 * */
			static std::string Wstring2String(const std::wstring& src);

			/**
			 * convert from WCHAR* to string
			 * */
			static std::string Wstring2String(const WCHAR* src, IndexType length);

			/* use fmt to format and generate */
			template <typename... Args>
			static FString Format(std::string& string, Args&& ...args);
			template <typename... Args>
			static FString Format(const std::string& string, Args&& ...args);
	};

	template <typename ... Args>
	FString FString::Format(std::string& string, Args&&... args) {
		FString value;
		auto formatted = String2Wstring(fmt::format(string, std::forward<Args>(args)...));
		value._string = std::shared_ptr<TCHAR[]>(new TCHAR[formatted.length() + 1], std::default_delete<TCHAR[]>());
		Core::CopyAssignItems(value._string.get(), formatted.c_str(), formatted.length() + 1);
		value._length = formatted.length();
		value._capacity = formatted.length();
		return value;
	}

	template <typename ... Args>
	FString FString::Format(const std::string& string, Args&&... args) {
		FString value;
		auto formatted = String2Wstring(fmt::format(string, std::forward<Args>(args)...));
		value._string = std::shared_ptr<TCHAR[]>(new TCHAR[formatted.length() + 1], std::default_delete<TCHAR[]>());
		Core::CopyAssignItems(value._string.get(), formatted.c_str(), formatted.length() + 1);
		value._length = formatted.length();
		value._capacity = formatted.length();
		return value;
	}
} // namespace Engine::Core::Types

#endif // VISREAL_F_STRING_H

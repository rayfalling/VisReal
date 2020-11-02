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
		private:
			/* Data ptr */
			std::shared_ptr<TCHAR[]> _string = nullptr;
			/* String Length */
			SIZE_T _length = 0;
			/* String max Length */
			SIZE_T _capacity = 0;

		public:
			FString() noexcept;
			FString(const FString& string) noexcept;
			FString(FString&& string) noexcept;

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
			FString(char string[], int length);

			~FString();

			[[nodiscard]] SIZE_T Length() const;

			/**
			 * override operator method
			 * make it can use like origin string
			 * */
		public:
			FString& operator=(const FString& another);
			FString& operator=(FString&& another) noexcept;
			FString& operator=(const std::string& another);
			FString& operator=(std::string&& another);

			/* overload operator==() */
			bool operator==(const FString& string) const;

			[[nodiscard]] std::string ToString();
			[[nodiscard]] std::string ToString() const;

			[[nodiscard]] TCHAR* GetData() const;

			/**
			 * Append another string to current
			 * */
			void Append(FString& string);

			/**
			 * Append another string to current
			 * */
			void Append(const FString& string);

			/**
			 * Append another string to current
			 * */
			void Append(FString&& string);

			/**
			 * Append another string to current
			 * */
			void Append(std::string& string);

			/**
			 * Append another string to current
			 * */
			void Append(const std::string& string);

			/**
			 * Append another string to current
			 * */
			void Append(std::string&& string);

			/**
			 * Split the string to multi string by separator
			 * */
			TArray<FString> Split(CHAR separator);

		protected:
			std::shared_ptr<TCHAR[]>& GetSharedPtr() {
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
			static std::wstring String2Wstring(const std::string& src);

			/**
			 * convert from char* to wstring
			 * */
			static std::wstring String2Wstring(const char* src, int length);

			/**
			 * convert from wstring to string
			 * */
			static std::string Wstring2String(const std::wstring& src);

			/**
			 * convert from WCHAR* to string
			 * */
			static std::string Wstring2String(const WCHAR* src, int length);

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

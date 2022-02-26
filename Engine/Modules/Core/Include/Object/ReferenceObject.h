/**
 * Created by Rayfalling on 2022/2/19.
 * */

#pragma once

#include <atomic>
#include <type_traits>

#ifndef VISREAL_REFERENCE_OBJECT_H
#define VISREAL_REFERENCE_OBJECT_H

namespace Engine::Core {
	template <class T, typename ...Args>
	class ControlBase {
		public:
			ControlBase(T* ptr) : _ptr(ptr) {
				_referenceCount.store(1, std::memory_order_relaxed);
			}

			~ControlBase() {
			}

			void Acquire() {
				_referenceCount.fetch_add(1, std::memory_order_acq_rel);
			}

			void Release() {
				if (_referenceCount.fetch_sub(1, std::memory_order_acq_rel) == 1)
					Destroy();
			}

			T* Get() {
				return _ptr;
			}

			[[nodiscard]] uint32_t GetRefCount() const {
				return _referenceCount.load();
			}

			T* operator*() {
				return _ptr;
			}

			void Swap(ControlBase<T>* other, const bool keepReferenceCount = false) {
				std::swap(_ptr, other->_ptr);

				if (!keepReferenceCount) {
					uint32_t oldReference = _referenceCount.load();
					_referenceCount.store(other->_referenceCount.load());
					other->_referenceCount.store(oldReference);
				}
			}

		protected:
			void Destroy() const {
				delete _ptr;
				delete this;
			}

		public:
			/** disallow copy external */
			ControlBase(const ControlBase& other) = delete;
			ControlBase(const ControlBase&& other) = delete;

			/** disallow assign external */
			const ControlBase& operator=(const ControlBase& other) = delete;
			const ControlBase& operator=(const ControlBase&& other) = delete;

		private:
			T*                   _ptr = nullptr;
			std::atomic_uint32_t _referenceCount;
	};

	template <class T>
	class ReferenceObject {
		static_assert(
			std::is_constructible_v<T>, u8"ReferenceObject must have construct function."
		);
		static_assert(
			std::is_destructible_v<T>, u8"ReferenceObject must have destruct function."
		);

		public:
			ReferenceObject() : _control(new ControlBase<T>(new T())) {
			}

			ReferenceObject(T* ptr) {
				_control = new ControlBase<T>(ptr);
			}

			~ReferenceObject() {
				Release();
			}

		protected:
			void Release() {
				if (_control != nullptr) {
					_control->Release();
					_control = nullptr;
				}
			}

		public:
			ReferenceObject(const ReferenceObject& other) {
				Release();
				_control = other._control;
				_control->Acquire();
			}

			ReferenceObject(const ReferenceObject&& other) noexcept {
				Release();
				_control = other._control;
				other._control = nullptr;
			}

			ReferenceObject& operator=(ReferenceObject& other) {
				if (this != &other) {
					Release();
					_control = other._control;
					_control->Acquire();
				}
				return *this;
			}

			ReferenceObject& operator=(ReferenceObject&& other) noexcept {
				Release();
				_control = other._control;
				other._control = nullptr;
				return *this;
			}

			T* operator*() {
				return _control->Get();
			}

			ReferenceObject& operator=(ReferenceObject other) {
				Release();
				_control = other._control;
				_control->Acquire();
				return *this;
			}

			T* operator->() const {
				return _control->Get();
			}

			T* Get() {
				return _control->Get();
			}

			[[nodiscard]] uint32_t GetRefCount() const {
				return _control->GetRefCount();
			}

			void Swap(ReferenceObject& other, const bool keepReferenceCount = false) {
				_control->Swap(other._control, keepReferenceCount);
			}

		private:
			ControlBase<T>* _control = nullptr;
	};
}

#endif //VISREAL_REFERENCE_OBJECT_H

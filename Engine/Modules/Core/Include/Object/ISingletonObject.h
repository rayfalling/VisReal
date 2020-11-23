/**
 * Created by Rayfalling on 2020/10/11.
 *
 * Singleton Factory Class Interface
 * */

#pragma once

#ifndef VISREAL_I_SINGLETON_OBJECT_H
#define VISREAL_I_SINGLETON_OBJECT_H

#include <mutex>

namespace Engine::Core {
	template <typename T>
	class ISingletonObject {
		friend class std::shared_ptr<T>;

		public:
			// Get Singleton Instance
			static T& GetInstance();
			static T* GetInstancePtr();

		protected:
			/** disallow construct external */
			ISingletonObject() noexcept;

			/** disallow destruct external */
			virtual ~ISingletonObject() noexcept;

		private:
			// Use shared_ptr to make sure that the allocated memory for instance
			// will be released when program exits (after main() ends).
			static T* _instance;
			static std::mutex _mutex;

		public:
			/** disallow copy external */
			ISingletonObject(const ISingletonObject& other) = delete;
			ISingletonObject(const ISingletonObject&& other) = delete;

			/** disallow assign external */
			const ISingletonObject& operator=(const ISingletonObject& other) = delete;
			const ISingletonObject& operator=(const ISingletonObject&& other) = delete;
	};

	template <typename T>
	T& ISingletonObject<T>::GetInstance() {
		if (_instance == nullptr) {
			_mutex.lock();
			_instance = new T();
			_mutex.unlock();
		}
		return *_instance;
	}

	template <typename T>
	T* ISingletonObject<T>::GetInstancePtr() {
		if (_instance == nullptr) {
			_mutex.lock();
			_instance = new T();
			_mutex.unlock();
		}
		return _instance;
	}

	template <typename T>
	ISingletonObject<T>::~ISingletonObject() noexcept = default;

	template <typename T>
	ISingletonObject<T>::ISingletonObject() noexcept = default;

	template <typename T>
	T* ISingletonObject<T>::_instance;

	template <typename T>
	std::mutex ISingletonObject<T>::_mutex;
}
#endif //VISREAL_I_SINGLETON_OBJECT_H

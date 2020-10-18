/**
 * Created by Rayfalling on 2020/10/11.
 *
 * Singleton Factory Class Interface
 * */

#ifndef VISREAL_SINGLETON_OBJECT_H
#define VISREAL_SINGLETON_OBJECT_H

#include <memory>
#include <mutex>

#include "EngineCoreExport.generate.h"

namespace Engine::Core {
    template<typename T>
    class ISingletonObject {

    public:
        // Get Singleton Instance
        static T &GetInstance();
        static T *GetInstancePtr();

    protected:
        /** disallow construct external */
        ISingletonObject() noexcept;

        /** disallow destruct external */
        virtual ~ISingletonObject() noexcept;

    private:
        // Use shared_ptr to make sure that the allocated memory for instance
        // will be released when program exits (after main() ends).
        static T *_instance;
    private:
        /** disallow copy external */
        ISingletonObject(const ISingletonObject &other);

        /** disallow assign external */
        const ISingletonObject &operator=(const ISingletonObject &other);
    };

    template<typename T>
    T &ISingletonObject<T>::GetInstance() {
        static std::mutex _mutex;
        if (_instance == nullptr) {
            _mutex.lock();
            _instance = new T();
            _mutex.unlock();
        }
        return *_instance;
    }

    template<typename T>
    T *ISingletonObject<T>::GetInstancePtr() {
        static std::mutex _mutex;
        if (_instance == nullptr) {
            _mutex.lock();
            _instance = new T();
            _mutex.unlock();
        }
        return _instance;
    }

    template<typename T>
    ISingletonObject<T>::~ISingletonObject() noexcept = default;

    template<typename T>
    ISingletonObject<T>::ISingletonObject() noexcept = default;

    template<typename T>
    T *ISingletonObject<T>::_instance = nullptr;
}
#endif //VISREAL_SINGLETON_OBJECT_H

/**
 * Created by Rayfalling on 2020/10/11.
 * */

#ifndef VISREAL_SINGLETON_OBJECT_H
#define VISREAL_SINGLETON_OBJECT_H

#include <memory>

template<typename T>
class ISingletonObject {

public:
    // 获取单实例对象
    static T &GetInstance();

protected:
    /** disallow construct external */
    ISingletonObject();

    /** disallow destruct external */
    virtual ~ISingletonObject() = 0;

    // Use auto_ptr to make sure that the allocated memory for instance
    // will be released when program exits (after main() ends).
    static std::unique_ptr<T> _instance;
private:
    /** disallow copy external */
    ISingletonObject(const ISingletonObject &other);

    /** disallow assign external */
    const ISingletonObject &operator=(const ISingletonObject &other);
};

template<typename T>
T &ISingletonObject<T>::GetInstance() {
    return _instance;
}

template<typename T>
ISingletonObject<T>::ISingletonObject() = default;

template <typename T>
std::unique_ptr<T> ISingletonObject<T>::_instance;

#endif //VISREAL_SINGLETON_OBJECT_H

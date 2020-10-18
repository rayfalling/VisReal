/**
 * Created by rayfalling on 2020/10/18.
 * */

#ifndef VISREAL_TMAP_H
#define VISREAL_TMAP_H

#include "PlatformTypes.h"
#include <mutex>

namespace Engine::Core::Types {
    template<typename Key, typename Value, typename Hash>
    class TMap {
    public:
        TMap(int size);
        ~TMap();
        bool Insert(const Key &key, const Value &value);
        bool Remove(const Key &key);
        Value &Find(const Key &key);
        Value &operator[](const Key &key);
    public:
        class MapItem {
        public:
            MapItem(Key key, Value value);


        private:
            Key _key;
            Value _value;
        };

    private:
        int32 _size;
        std::mutex _mutex;
    };

}

#endif //VISREAL_TMAP_H

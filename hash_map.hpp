
#pragma once

#include <vector>

#include "hash_slot.hpp"
#include "slot.hpp"

template <typename V>

class HashMap {
public:
    HashMap(int size) {
        this->size = size;
        map.assign(size, HashSlot<V>());
    }

    ~HashMap() = default;

    void write(int key, V data) {
        map[hash(key)].write_to_overflow(key, data);
    }

    V read(int key) {
        int idx;
        int h = hash(key);
        if (!map[h].key_is_in_hash_slot(key, &idx)) {
            return 0;
        }
        return map[h].read_from_overflow(idx);
    }

    void delete_key(int key) {
        int h = hash(key);
        int idx;
        if (!map[h].key_is_in_hash_slot(key, &idx)) {
            return;
        }
        map[h].remove_from_overflow(idx);
    }

    int max_overflow_in_map(void) {
        int max_overflow_size = 0;
        for (int i = 0; i < size; i++) {
            if (map[i].get_overflow_size() > max_overflow_size) {
                max_overflow_size = map[i].get_overflow_size();
            }
        }
        return max_overflow_size;
    }
    
private:
    int hash(int key) {
        key = abs(key);
        return key % size;
    }

    std::vector<HashSlot<V>> map;
    int size;
};
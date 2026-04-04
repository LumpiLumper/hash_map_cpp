
#pragma once

#include "hash_slot.hpp"
#include "slot.hpp"

template <typename V>

class HashMap {
public:
    HashMap::HashMap(int size) {
        this->size = size;
        map = new HashSlot[size];
    }

    HashMap::~HashMap() {
        delete[] map;
    }

    void HashMap::write(int key, V data) {
        map[hash(key)].write_to_overflow(key, data);
    }

    V HashMap::read(int key) {
        int idx;
        int h = hash(key);
        if (!map[h].key_is_in_hash_slot(key, &idx)) {
            return nullptr;
        }
        return map[h].read_from_overflow(idx);
    }

    void HashMap::delete_key(int key) {
        int h = hash(key);
        int idx;
        if (!map[h].key_is_in_hash_slot(key, &idx)) {
            return;
        }
        map[h].remove_slot_from_overflow(idx);
    }

    int HashMap::hash(int key) {
        key = abs(key);
        return key % size;
    }

    int HashMap::max_overflow_in_map(void) {
        int max_overflow_size = 0;
        for (int i = 0; i < size; i++) {
            if (map[i].get_overflow_size() > max_overflow_size) {
                max_overflow_size = map[i].get_overflow_size();
            }
        }
        return max_overflow_size;
    }
    
private:
    int HashMap::hash(int key) {
        key = abs(key);
        return key % size;
    }

    HashSlot *map;
    int size;
};
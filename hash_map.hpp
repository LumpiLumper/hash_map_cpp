
#pragma once

#include <vector>
#include <optional>

#include "hash_slot.hpp"
#include "slot.hpp"

template <typename K, typename D>

class HashMap {
public:
    HashMap(int size) {
        this->size = size;
        map.assign(size, HashSlot<K, D>());
    }

    ~HashMap() = default;

    void write(K key, D data) {
        map[hash(key)].write_to_overflow(key, data);
    }

    std::optional<D> read(K key) {
        int idx;
        int h = hash(key);
        if (!map[h].key_is_in_hash_slot(key, &idx)) {
            return std::nullopt;
        }
        return map[h].read_from_overflow(idx);
    }

    void delete_key(K key) {
        int h = hash(key);
        int idx;
        if (!map[h].key_is_in_hash_slot(key, &idx)) {
            return;
        }
        map[h].remove_from_overflow(idx);
    }

    void print_map(void) {
        std::cout << "---------- Map ----------" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << "Hash Slot " << i << ":" << std::endl;
            map[i].print_slots();
        }
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
    int hash(K key) {
        key = abs(key);
        return key % size;
    }

    std::vector<HashSlot<K, D>> map;
    int size;
};
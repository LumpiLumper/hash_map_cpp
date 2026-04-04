
#pragma once

#include <vector>
#include <optional>

#include "hash_slot.hpp"
#include "slot.hpp"


template <typename Key, typename Data>

class HashMap {
public:
    HashMap(int size) {
        this->size = size;
        map.assign(size, HashSlot<Key, Data>());
    }

    ~HashMap() = default;

    void write(const Key& key, const Data& data) {
        map[hash(key)].write_to_overflow(key, data);
    }

    std::optional<Data> read(const Key& key) {
        int h = hash(key);
        std::optional<int> idx = map[h].key_is_in_hash_slot(key);
        if (!idx.has_value()) {
            return std::nullopt;
        }
        return map[h].read_from_overflow(idx.value());
    }

    void delete_key(const Key& key) {
        int h = hash(key);
        std::optional<int> idx = map[h].key_is_in_hash_slot(key);
        if (!idx.has_value()) {
            return;
        }
        map[h].remove_from_overflow(idx.value());
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
    int hash(const Key& key) {
        int hashed_key = std::hash<Key>{}(key) % size;
        return hashed_key;
    }

    std::vector<HashSlot<Key, Data>> map;
    int size;
};
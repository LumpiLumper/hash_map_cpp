
#pragma once

#include <iostream>
#include <vector>
#include <optional>

#include "hash_slot.hpp"
#include "slot.hpp"


template <typename Key, typename Data>

class HashMap {
public:
    HashMap(int size) : HashMap(size, 0.7f) {}
    HashMap(int size, float target_load_factor) {
        map.assign(size, HashSlot<Key, Data>());
        this->target_load_factor = target_load_factor;
    }

    ~HashMap() = default;

    void write(const Key& key, const Data& data) {
        map[hash(key)].write_to_overflow(key, data);
        if (load_factor() > target_load_factor) {
            rehash();
        }
    }

    std::optional<Data> read(const Key& key) const {
        size_t h = hash(key);
        std::optional<int> idx = map[h].key_is_in_hash_slot(key);
        if (!idx.has_value()) {
            return std::nullopt;
        }
        return map[h].read_from_overflow(idx.value());
    }

    void delete_key(const Key& key) {
        size_t h = hash(key);
        std::optional<int> idx = map[h].key_is_in_hash_slot(key);
        if (!idx.has_value()) {
            return;
        }
        map[h].remove_from_overflow(idx.value());
    }

    void rehash(void) {
        int new_size;
        if (map.size() < 2) {
            new_size = 2;
        }
        else {
            new_size = map.size() + (map.size() / 2);
        }
        while(load_factor() > target_load_factor) {
            std::vector<HashSlot<Key, Data>> new_map;
            new_map = reassign_entries(new_size);
            map = std::move(new_map);
            new_size = new_size + (new_size / 2);
        }
    }

    void print_map(void) const {
        std::cout << "---------- Map ----------" << std::endl;
        for (int i = 0; i < map.size(); i++) {
            std::cout << "Hash Slot " << i << ":" << std::endl;
            map[i].print_slots();
        }
    }

    size_t max_overflow_in_map(void) const {
        size_t max_overflow_size = 0;
        for (int i = 0; i < static_cast<int>(map.size()); i++) {
            if (map[i].overflow_size() > max_overflow_size) {
                max_overflow_size = map[i].overflow_size();
            }
        }
        return max_overflow_size;
    }

    float load_factor(void) const {
        int n_entries = 0;
        
        for (int i = 0; i < map.size(); i++) {
            n_entries += map[i].overflow_size();
        }
        return static_cast<float>(n_entries) / map.size();
    }

    void set_target_load_factor(float target_load_factor) {
        this->target_load_factor = target_load_factor;
    }
    
private:
    size_t hash(const Key& key) const {
        size_t hashed_key = std::hash<Key>{}(key) % map.size();
        return hashed_key;
    }

    std::vector<HashSlot<Key, Data>> reassign_entries(int new_size){
        std::vector<HashSlot<Key, Data>> new_map;
        new_map.assign(new_size, HashSlot<Key, Data>());
        for (int i = 0; i < static_cast<int>(map.size()); i++) {
            for (int u = 0; u < map[i].overflow_size(); u++) {
                Slot<Key, Data> slot = map[i].get_slot(u);
                int hashed_key = std::hash<Key>{}(slot.get_key()) % new_size;
                new_map[hashed_key].write_to_overflow(slot.get_key(), slot.get_data());
            }
        }
        return new_map;
    }

    std::vector<HashSlot<Key, Data>> map;
    float target_load_factor;
};
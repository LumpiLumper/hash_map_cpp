
#pragma once

#include <iostream>
#include <vector>

#include "slot.hpp"

template <typename Key, typename Data>

class HashSlot {
public:
    HashSlot() {
        overflow.assign(0, Slot<Key, Data>());
    }

    ~HashSlot() = default;

    void write_to_overflow(const Key& key, const Data& data) {
        std::optional<int> idx = key_is_in_hash_slot(key);
        if (idx.has_value()) {
            overflow[idx.value()].update_data(data);
            return;
        }
        overflow.emplace_back(key, data);
        return;
    }

    Data read_from_overflow(int idx) const {
        return overflow[idx].get_data();
    }

    void remove_from_overflow(int idx) {
        overflow.erase(overflow.begin() + idx);
    }

    Slot<Key, Data> get_slot(int idx) {
        return overflow[idx];
    }

    std::optional<int> key_is_in_hash_slot(const Key& key) const {
        for (int i = 0; i < overflow.size(); i++) {
            if (key == overflow[i].get_key()) {
                return i;
            }
        }
        return std::nullopt;
    }

    void print_slots(void) const {
        if (overflow.size() > 0) {
            for (int u = 0; u < overflow.size(); u++) {
                std::cout << "  Slot " << u << ":" << std::endl;
                std::cout << "      Key: " << overflow[u].get_key() << std::endl;
                std::cout << "      Data: " << overflow[u].get_data() << std::endl;
            }
        }
        else {
            std::cout << "  Has no Slots" << std::endl;
        }
        std::cout << std::endl;
    }

    int overflow_size() const {
        return overflow.size();
    }

private:

    std::vector<Slot<Key, Data>> overflow;
};
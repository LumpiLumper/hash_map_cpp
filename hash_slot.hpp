
#pragma once

#include <vector>

#include "slot.hpp"

template <typename V>

class HashSlot {
public:
    HashSlot() {
        overflow_size = 0;
        overflow.assign(0, Slot<V>());
    }

    ~HashSlot() = default;

    void write_to_overflow(int key, V data) {
        int idx;
        if (key_is_in_hash_slot(key, &idx)) {
            overflow[idx].update_data(data);
            return;
        }
        overflow.emplace_back(key, data);
        overflow_size += 1;
        return;
    }

    V read_from_overflow(int idx) {
        return overflow[idx].read_from_slot();
    }

    void remove_from_overflow(int idx) {
        overflow.erase(overflow.begin() + idx);
        overflow_size -= 1;
    }

    bool key_is_in_hash_slot(int key, int* idx) {
        for (int i = 0; i < overflow_size; i++) {
            if (key == overflow[i].get_key()) {
                *idx = i;
                return true;
            }
        }
        return false;
    }

    int get_overflow_size() {
        return overflow_size;
    }

private:

    std::vector<Slot<V>> overflow;
    int overflow_size;
};
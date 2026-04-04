
#pragma once

#include <vector>

#include "slot.hpp"

template <typename K, typename D>

class HashSlot {
public:
    HashSlot() {
        overflow_size = 0;
        overflow.assign(0, Slot<K, D>());
    }

    ~HashSlot() = default;

    void write_to_overflow(K key, D data) {
        int idx;
        if (key_is_in_hash_slot(key, &idx)) {
            overflow[idx].update_data(data);
            return;
        }
        overflow.emplace_back(key, data);
        overflow_size += 1;
        return;
    }

    D read_from_overflow(int idx) {
        return overflow[idx].read_from_slot();
    }

    void remove_from_overflow(int idx) {
        overflow.erase(overflow.begin() + idx);
        overflow_size -= 1;
    }

    bool key_is_in_hash_slot(K key, int* idx) {
        for (int i = 0; i < overflow_size; i++) {
            if (key == overflow[i].get_key()) {
                *idx = i;
                return true;
            }
        }
        return false;
    }

    void print_slots(void) {
        if (overflow_size > 0) {
            for (int u = 0; u < overflow_size; u++) {
                std::cout << "  Slot ";
                std::cout << u << std::endl;
                std::cout << "      Key: ";
                std::cout << overflow[u].get_key() << std::endl;
                std::cout << "      Data: ";
                std::cout << overflow[u].read_from_slot() << std::endl;
            }
        }
        else {
            std::cout << "  Has no Slots" << std::endl;
        }
        std::cout << std::endl;
    }

    int get_overflow_size() {
        return overflow_size;
    }

private:

    std::vector<Slot<K, D>> overflow;
    int overflow_size;
};

#pragma once

#include "slot.hpp"


class HashSlot {
public:
    HashSlot();
    ~HashSlot();
    void write_to_overflow(int key, void* data);
    void remove_slot_from_overflow(int idx);
    void* read_from_overflow(int idx);
    bool key_is_in_hash_slot(int key, int* idx);
    int get_overflow_size();

private:
    void add_slot_to_overflow();
    Slot *overflow;
    int overflow_size;
};


#include "hash_slot.hpp"
#include "slot.hpp"

HashSlot::HashSlot() {
    overflow_size = 0;
    overflow = nullptr;
}

HashSlot::~HashSlot() {
    delete[] overflow;
}

void HashSlot::write_to_overflow(int key, void* data) {
    if (overflow_size == 0) {
        overflow = new Slot(key, data);
        overflow_size += 1;
        return;
    }
    int idx;
    if (key_is_in_hash_slot(key, &idx)) {
        overflow[idx].update_data(data);
        return;
    }
    add_slot_to_overflow();
    overflow[overflow_size - 1].set(key, data);
    return;
}

void HashSlot::remove_slot_from_overflow(int idx) {
    Slot* new_overflow = new Slot[overflow_size - 1];
    int new_idx = 0;
    for (int i = 0; i < overflow_size; i++) {
        if (i == idx) {
            continue;
        }
        new_overflow[new_idx] = overflow[i];
        new_idx++;
    }
    delete[] overflow;
    overflow = new_overflow;
    overflow_size -= 1;
}

void* HashSlot::read_from_overflow(int idx) {
    return overflow[idx].read_from_slot();
}

bool HashSlot::key_is_in_hash_slot(int key, int* idx) {
    for (int i = 0; i < overflow_size; i++) {
        if (key == overflow[i].get_key()) {
            *idx = i;
            return true;
        }
    }
    return false;
}

int HashSlot::get_overflow_size() {
    return overflow_size;
}

void HashSlot::add_slot_to_overflow() {
    Slot* new_overflow = new Slot[overflow_size + 1];
    for (int i = 0; i < overflow_size; i++) {
        new_overflow[i] = overflow[i];
    }
    delete[] overflow;
    overflow = new_overflow;
    overflow_size += 1;
}
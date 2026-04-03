

#include "hash_slot.hpp"
#include "slot.hpp"

HashSlot::HashSlot() {
    overflow_size = 0;
}

HashSlot::~HashSlot() {
    delete[] overflow;
}

void HashSlot::write(int key, void* data) {
    if (overflow_size == 0) {
        overflow = new Slot(key, 0, data);
        return;
    }
    
}

KeyChecker HashSlot::key_is_in_hash_slot(int key) {
    KeyChecker key_checker;

    for (int i = 0; i < overflow_size; i++) {
        if (key == overflow[i].get_key()) {
            key_checker.is_in_slot = true;
            key_checker.idx = i;
            return key_checker;
        }
    }
    return key_checker;
}

int HashSlot::get_overflow_size() {
    return overflow_size;
}
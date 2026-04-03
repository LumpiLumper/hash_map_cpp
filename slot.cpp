

#include "slot.hpp"

Slot::Slot(int key, int idx, void* data) {
    this->key = key;
    this->idx = idx;
    this->data = data;
    used = true;
}

Slot::~Slot() {
    delete &key;
    delete &idx;
    delete &data;
    delete &used;
}
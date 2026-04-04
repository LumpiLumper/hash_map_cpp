

#include "slot.hpp"

Slot::Slot(int key, void* data) {
    this->key = key;
    this->data = data;
}

Slot::~Slot() {
    delete &key;
    delete &data;
}

void Slot::set(int key, void* data) {
    this->key = key;
    this->data = data;
}

void* Slot::read_from_slot() {
    return data;
}

void Slot::update_data(void* data) {
    this->data = data;
}
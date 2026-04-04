
#pragma once

template <typename V>

class Slot {
public:
    Slot::Slot(int key, void* data) {
        this->key = key;
        this->data = data;
    }

    void Slot::set(int key, V data) {
        this->key = key;
        this->data = data;
    }

    V Slot::read_from_slot() {
        return data;
    }

    void Slot::update_data(V data) {
        this->data = data;
    }

private:
    int key;
    V data;
};

#pragma once

template <typename V>

class Slot {
public:
    Slot() : key(0), data(0) {}
    Slot(int key, V data) {
        this->key = key;
        this->data = data;
    }

    ~Slot() = default;

    void set(int key, V data) {
        this->key = key;
        this->data = data;
    }

    V read_from_slot() {
        return data;
    }

    int get_key() {
        return key;
    }

    void update_data(V data) {
        this->data = data;
    }

private:
    int key;
    V data;
};
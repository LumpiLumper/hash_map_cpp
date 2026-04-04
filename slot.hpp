
#pragma once

template <typename K, typename D>

class Slot {
public:
    Slot() : key(0), data(0) {}
    Slot(K key, D data) {
        this->key = key;
        this->data = data;
    }

    ~Slot() = default;

    D read_from_slot() {
        return data;
    }

    int get_key() {
        return key;
    }

    void update_data(D data) {
        this->data = data;
    }

private:
    K key;
    D data;
};
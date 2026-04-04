
#pragma once

template <typename Key, typename Data>

class Slot {
public:
    Slot() : key(), data() {}
    Slot(const Key& key, const Data& data) {
        this->key = key;
        this->data = data;
    }

    ~Slot() = default;

    Data read_from_slot() {
        return data;
    }

    Key get_key() {
        return key;
    }

    void update_data(const Data& data) {
        this->data = data;
    }

private:
    Key key;
    Data data;
};

#pragma once

class Slot {
public:
    Slot() : key(0), data(nullptr) {}
    Slot(int key, void* data);
    ~Slot();
    void set(int key, void* data);
    void* read_from_slot();
    int get_key();
    void update_data(void* data);

private:
    int key;
    void* data;
};
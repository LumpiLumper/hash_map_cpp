
#pragma once

class Slot {
public:
    Slot(int key, int idx, void* data);
    ~Slot();
    int get_key();

private:
    int key;
    int idx;
    void* data;
    bool used;
};
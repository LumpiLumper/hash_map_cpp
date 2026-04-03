
#pragma once

#include "hash_slot.hpp"
#include "slot.hpp"

class HashMap {
public:
    HashMap(int size);
    ~HashMap();
    int hash(int key);
    int max_overflow_in_map(void);
    void write(int key, void* data);
    void* read(int key);
    void rehash(void);

private:
    HashSlot *map;
    int size;
};
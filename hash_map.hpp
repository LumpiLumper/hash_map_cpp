
#pragma once

#include "hash_slot.hpp"
#include "slot.hpp"

class HashMap {
public:
    HashMap(int size);
    ~HashMap();
    void write(int key, void* data);
    void* read(int key);
    void delete_key(int key);
    void rehash(void);
    int max_overflow_in_map(void);

private:
    int hash(int key);
    
    HashSlot *map;
    int size;
};
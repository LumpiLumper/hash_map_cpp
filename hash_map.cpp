
#include "hash_map.hpp"

#include <iostream>


HashMap::HashMap(int size) {
    this->size = size;
    map = new HashSlot[size];
}

HashMap::~HashMap() {
    delete[] map;
}

int HashMap::hash(int key) {
    key = abs(key);
    return key % size;
}

int HashMap::max_overflow_in_map(void) {
    int max_overflow_size = 0;
    for (int i = 0; i < size; i++) {
        if (map[i].get_overflow_size() > max_overflow_size) {
            max_overflow_size = map[i].get_overflow_size();
        }
    }
    return max_overflow_size;
}

void HashMap::write(int key, void* data) {
    int h = hash(key);
    
    map[h].write(key, data);
}


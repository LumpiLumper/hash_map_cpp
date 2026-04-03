
#include "slot.hpp"


struct KeyChecker
{
    bool is_in_slot = false;
    int idx;
};


class HashSlot {
public:
    HashSlot();
    ~HashSlot();
    void write(int key, void* data);
    KeyChecker key_is_in_hash_slot(int key);
    int get_overflow_size();

private:
    Slot *overflow;
    int overflow_size;
};

/*
compile with:
g++ -g -o test test_hash_map.cpp

run with: 
valgrind --leak-check=full --track-origins=yes ./test
*/

#include <iostream>
#include <optional>

#include "hash_map.hpp"

using namespace std;

int passed = 0;
int failed = 0;

void check_found(int key, int data, optional<int> val) {
    if (val == data) {
        cout << "[PASSED] key " << key << " found with data " << val.value() << endl;
        passed += 1;
    }
    else if (val != NULL) {
        cout << "[FAILED] key " << key << " found with data " << val.value() << " expected data to be " << data << endl;
        failed += 1;
    }
    else {
        cout << "[FAILED] key " << key << " not found, expected found" << endl;
        failed += 1;
    }
}

void check_not_found(int key, optional<int> val) {
    if (val == nullopt) {
        cout << "[PASSED] key " << key << " not found" << endl;
        passed += 1;
    }
    else {
        std:cout << "[FAILED] key " << key << " found with data " << val.value() << ", expected not found" << endl;
        failed += 1;
    }
}

int main() {
    optional<int> val;
    HashMap<int, int> hash_map(10);

    hash_map.write(5, 10);
    val = hash_map.read(5);
    check_found(5, 10, val);
    
    val = hash_map.read(6);
    check_not_found(6, val);

    hash_map.write(5, 11);
    val = hash_map.read(5);
    check_found(5, 11, val);
    hash_map.write(15, 75);
    val = hash_map.read(15);
    check_found(15, 75, val);

    hash_map.print_map();

    hash_map.delete_key(5);
    val = hash_map.read(5);
    check_not_found(5, val);

    hash_map.write(0, 0);
    val = hash_map.read(0);
    check_found(0, 0, val);

    cout << endl;
    cout << "failed: " << failed << endl;
    cout << "passed: " << passed << endl;

    return 0;
}
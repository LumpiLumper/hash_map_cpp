
/*
compile with:
g++ -g -o test test_hash_map.cpp

run with: 
valgrind --leak-check=full --track-origins=yes ./test
*/

#include <iostream>
#include <optional>
#include <memory>
#include <string>

#include "hash_map.hpp"

using namespace std;

int passed = 0;
int failed = 0;


template <typename Key, typename Data>
void check_found(Key key, Data data, optional<Data> val) {
    if (val == data) {
        cout << "[PASSED] key " << key << " found with data " << val.value() << endl;
        passed += 1;
    }
    else if (val.has_value()) {
        cout << "[FAILED] key " << key << " found with data " << val.value() << " expected data to be " << data << endl;
        failed += 1;
    }
    else {
        cout << "[FAILED] key " << key << " not found, expected found" << endl;
        failed += 1;
    }
}

template <typename Key, typename Data>
void check_not_found(Key key, optional<Data> val) {
    if (!val.has_value()) {
        cout << "[PASSED] key " << key << " not found" << endl;
        passed += 1;
    }
    else {
        cout << "[FAILED] key " << key << " found with data " << val.value() << ", expected not found" << endl;
        failed += 1;
    }
}

int main() {
    optional<int> val;

    auto hash_map = std::make_unique<HashMap<int, int>>(10);

    hash_map->write(5, 10);
    val = hash_map->read(5);
    check_found<int, int>(5, 10, val);
    
    val = hash_map->read(6);
    check_not_found<int, int>(6, val);

    hash_map->write(5, 11);
    val = hash_map->read(5);
    check_found<int, int>(5, 11, val);
    hash_map->write(15, 75);
    val = hash_map->read(15);
    check_found<int, int>(15, 75, val);

    cout << "load factor: " << hash_map->load_factor() << endl;

    hash_map->print_map();

    hash_map->delete_key(5);
    val = hash_map->read(5);
    check_not_found<int, int>(5, val);

    hash_map->write(0, 0);
    val = hash_map->read(0);
    check_found<int, int>(0, 0, val);

    int key_and_data[10][2] = {{10, 58},
                                {4, 627},
                                {75, 0,},
                                {0, 81},
                                {8624, 5137},
                                {7, 452},
                                {458, 72},
                                {1, 562},
                                {5, 753},
                                {8741, 5621}};
    
    for (int i = 0; i < 10; i++) {
        int key = key_and_data[i][0];
        int data = key_and_data[i][1];

        hash_map->write(key, data);
    }

    for (int i = 0; i < 10; i++) {
        int key = key_and_data[i][0];
        int data = key_and_data[i][1];
        val = hash_map->read(key);
        check_found<int, int>(key, data, val);
    }

    cout << "before rehash:" << endl;
    cout << "load factor: " << hash_map->load_factor() << endl;

    hash_map->rehash();

    cout << "after rehash:" << endl;
    cout << "load factor: " << hash_map->load_factor() << endl;

    hash_map->print_map();

    for (int i = 0; i < 10; i++) {
        int key = key_and_data[i][0];
        int data = key_and_data[i][1];
        val = hash_map->read(key);
        check_found<int, int>(key, data, val);
    }

    hash_map.reset();

    auto string_hash_map = std::make_unique<HashMap<std::string, int>>(10);
    
    optional<int> string_val;

    string_hash_map->write("Jon", 43);
    string_val = string_hash_map->read("Jon");
    check_found<std::string, int>("Jon", 43, string_val);



    cout << endl;
    cout << "failed: " << failed << endl;
    cout << "passed: " << passed << endl;

    return 0;
}
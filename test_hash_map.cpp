
#include <iostream>
#include <optional>

#include "hash_map.hpp"

using namespace std;


int main() {

    HashMap<float> hash_map(7.2014);

    hash_map.write(5, 10);
    auto val = hash_map.read(5);

    if (val == 10) {
        std::cout << "good\n";
    }
    else {
        std::cout << "bad\n";
    }

    return 0;
}
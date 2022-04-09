

#include <iostream>
#include "VolumeGridScanner.hpp"

int main() {
    cadcam::VolumeGridScanner<size_t> indexScanner{
        {0, 0, 0},
        {2, 2, 2},
        1
    };

    while (indexScanner.InProgress()) {
        auto index = indexScanner.NextPoint();
        std::cout << index.x() << " " << index.y() << " " << index.z() << std::endl;
    }

    return 0;
}

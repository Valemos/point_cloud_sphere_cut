

#include <iostream>
#include "VolumeGridScanner.hpp"
#include "Cylinder.hpp"

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

    // test cylinder
    cadcam::Cylinder cylinder {
        {3, 0, 0},
        {0, 7, 0},
        1.2
    };

    std::cout
        << "test cylinder" << std::endl
        << cylinder.ContainsPoint({1, 2, 0}) << std::endl
        << not cylinder.ContainsPoint({0, 3, 0}) << std::endl
        << not cylinder.ContainsPoint({0, 8, 0}) << std::endl;

    return 0;
}

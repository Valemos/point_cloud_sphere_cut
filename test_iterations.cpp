

#include <iostream>
#include "VolumeGridScanner.hpp"
#include "Cylinder.hpp"
#include "Sphere.hpp"

void TestSphere() {
    cadcam::Sphere sphere {{0.5, 0.5, 0.5}, 0.5};

    std::cout << "sphere points" << std::endl;
    const cadcam::GridParameters3d<double> grid {1};
    for (const auto& point : sphere.GetInternalPoints(grid)) {
        std::cout << point.x() << " " << point.y() << " " << point.z() << std::endl;
    }
}

void TestCylinder() {
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
}

void TestScanner() {
    cadcam::VolumeGridScanner<size_t> indexScanner{{
                                                       {0, 0, 0},
                                                       {2, 2, 2},
                                                       1
                                                   }};

    while (indexScanner.InProgress()) {
        auto index = indexScanner.NextPoint();
        std::cout << index.x() << " " << index.y() << " " << index.z() << std::endl;
    }
}

int main() {
    TestScanner();
    TestCylinder();
    TestSphere();
    return 0;
}

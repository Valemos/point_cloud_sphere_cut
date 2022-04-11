#include <gtest/gtest.h>

#include "VolumeGridScanner.hpp"
#include "Cylinder.hpp"
#include "Sphere.hpp"


using point3d = cadcam::mwTPoint3d<double>;


template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}


std::string pointToString(const point3d &point) {
    return {
        to_string_with_precision(point.x(), 10) + ',' +
        to_string_with_precision(point.y(), 10) + ',' +
        to_string_with_precision(point.z(), 10)
    };
}

void vectorsEq(const std::vector<point3d>& first, const std::vector<point3d>& second) {
    ASSERT_EQ(first.size(), second.size());
    for (int i = 0; i < first.size(); ++i) {
        ASSERT_TRUE(first[i] == second[i])
            << pointToString(first[i]) << " != "
            << pointToString(second[i]);
    }
}


TEST(TestBasic, TestPointEquality) {
    ASSERT_TRUE(point3d(1, 1, 1) == point3d(1, 1, 1));
}

TEST(TestSurfaces, TestSphereEdges)
{
    point3d center {0.5, 0.5, 0.5};
    cadcam::Sphere sphere {center,
                           ~(center - point3d(0, 0, 0))};

    std::vector<point3d> expectedPoints {
        {0, 0, 0},
        {1, 0, 0},
        {0, 1, 0},
        {1, 1, 0},
        {0, 0, 1},
        {1, 0, 1},
        {0, 1, 1},
        {1, 1, 1}
    };
    auto resultPoints = sphere.GetInternalPoints(cadcam::GridParameters3d<double>{1});
    vectorsEq(resultPoints, expectedPoints);
}

TEST(TestSurfaces, TestSphereSmallerThanCell) {
    cadcam::Sphere sphere {{1.1, 1.1, 1.1}, 0.5};

    std::vector<point3d> expectedPoints {
        {1, 1, 1}
    };

    auto resultPoints = sphere.GetInternalPoints(cadcam::GridParameters3d<double>{1});
    vectorsEq(resultPoints, expectedPoints);
}

TEST(TestSurfaces, TestCylinder) {
    cadcam::Cylinder cylinder {
        {3, 0, 0},
        {0, 7, 0},
        1.2
    };

    EXPECT_TRUE(cylinder.ContainsPoint({1, 2, 0}));
    EXPECT_FALSE(cylinder.ContainsPoint({0, 3, 0}));
    EXPECT_FALSE(cylinder.ContainsPoint({0, 8, 0}));
}

TEST(TestIterators, TestSinglePoint) {
    cadcam::VolumeGridScanner<double> scanner{{
        {1, 1, 1},
        {1, 1, 1},
        1
    }};

    ASSERT_TRUE(scanner.InProgress());
    auto new_point = scanner.NextPoint();
    ASSERT_TRUE(new_point == point3d(1, 1, 1));
    ASSERT_FALSE(scanner.InProgress());
}

TEST(TestIterators, TestScanner) {
    cadcam::VolumeGridScanner<size_t> indexScanner{{
                                                       {0, 0, 0},
                                                       {1, 1, 1},
                                                       1
                                                   }};

    std::vector<cadcam::mwTPoint3d<size_t>> expectedPoints {
        {0, 0, 0},
        {1, 0, 0},
        {0, 1, 0},
        {1, 1, 0},
        {0, 0, 1},
        {1, 0, 1},
        {0, 1, 1},
        {1, 1, 1}
    };

    int i_exp = 0;
    while (indexScanner.InProgress()) {
        auto point = indexScanner.NextPoint();
        ASSERT_TRUE(expectedPoints[i_exp++] == point);
    }
}

TEST(TestGrid, TestSnapToGrid) {
    const cadcam::GridParameters3d<double> grid {1.5};
    EXPECT_TRUE(grid.RoundDown({0.4, -0.4, 0.9})
                == point3d(0, -1.5, 0));
    EXPECT_TRUE(grid.RoundDown({1.1, 2.1, 3.1})
                == point3d(0, 1.5, 3));
    EXPECT_TRUE(grid.RoundUp({0.1, -0.9, 0.6})
                == point3d(1.5, 0, 1.5));
}

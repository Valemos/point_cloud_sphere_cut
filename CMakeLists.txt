cmake_minimum_required(VERSION 3.20)
project(cutSphereMove)


add_library(pointCloud
        src/CreateSkin.cpp
        src/Cylinder.cpp
        src/mwArcFunction.cpp
        src/mwException.cpp
        src/mwIdxRangeException.cpp
        src/PointCloud.cpp
        src/Sphere.cpp
        src/SphereLinearMotion.cpp
        src/VolumeGridScanner.cpp
        src/GridParameters3d.cpp
        )
target_include_directories(pointCloud PUBLIC include)

add_executable(cutSphereMove cutSphereMove.cpp)
target_link_libraries(cutSphereMove PRIVATE pointCloud)
set_target_properties(cutSphereMove PROPERTIES CXX_STANDARD 11)

enable_testing()
find_package(GTest REQUIRED)

add_executable(testComponents test/testComponents.cpp)
target_include_directories(testComponents PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(testComponents PUBLIC pointCloud ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
set_target_properties(testComponents PROPERTIES CXX_STANDARD 11)

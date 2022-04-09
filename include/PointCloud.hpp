#pragma once

#include <vector>
#include <functional>
#include <mwTPoint3d.hpp>
#include <glob.h>
#include "Volume.hpp"

namespace cadcam {
class PointCloud {
public:

    typedef mwTPoint3d<double> point3d;

    PointCloud(const point3d &referencePoint,
               unsigned long nx,
               unsigned long ny,
               unsigned long nz,
               double delta);

    void AddPoint(const point3d &position);
    void RemovePoint(const point3d &position);
    void RemoveIntersection(const Volume *volume);

    size_t sizeX() const;
    size_t sizeY() const;
    size_t sizeZ() const;

private:
    const point3d referencePoint_;
    std::vector<std::vector<std::vector<bool>>> points_;
    const double delta_;

    void SetPoint(const point3d &position, bool value);
    point3d IndicesToPoint(size_t x, size_t y, size_t z);
};
}

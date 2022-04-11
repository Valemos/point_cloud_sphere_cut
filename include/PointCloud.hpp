#pragma once

#include <vector>
#include <functional>
#include "mwTPoint3d.hpp"
#include "Volume.hpp"
#include "GridParameters3d.hpp"


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

    void SaveSkin(const std::string &fileName);

private:
    GridParameters3d<double> grid_;
    std::vector<std::vector<std::vector<bool>>> points_;

    void SetPoint(const point3d &position, bool value);
    std::vector<point3d> GetSkinPoints();
};
}

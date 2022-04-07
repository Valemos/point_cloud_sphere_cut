#include "PointCloud.hpp"
#include <VolumeGridScanner.hpp>
#include <VolumeGridScanner.hpp>

cadcam::PointCloud::PointCloud(const point3d &referencePoint,
                               unsigned long nx,
                               unsigned long ny,
                               unsigned long nz,
                               double delta)
                               : referencePoint_(referencePoint),
                                 delta_(delta) {
    points_.resize(nx);
    for (int x = 0; x < nx; x++) {
        points_[x].resize(ny);
        for (int y = 0; y < ny; y++) {
            points_[x][y].resize(nz, false);
        }
    }
}

void cadcam::PointCloud::AddPoint(const point3d &position) {
    SetPoint(position, true);
}

void cadcam::PointCloud::RemovePoint(const point3d &position) {
    SetPoint(position, false);
}

void cadcam::PointCloud::SetPoint(const point3d &position, bool value) {
    points_
        [static_cast<size_t>(position.x() / delta_)]
        [static_cast<size_t>(position.y() / delta_)]
        [static_cast<size_t>(position.z() / delta_)] = value;
}

void cadcam::PointCloud::RemoveIntersection(const Volume *volume) {
    // TODO "project" grid on volume and sample points_ from it
    // if point is inside volume, it should be returned and removed from point cloud

    IteratePoints();
}

void cadcam::PointCloud::IteratePoints() {
    cadcam::VolumeGridScanner<size_t> indexStepper{
        {0, 0, 0},
        {sizeX(), sizeY(), sizeZ()},
        1
    };

    while (indexStepper.) {

    }
}

cadcam::PointCloud::point3d cadcam::PointCloud::IndicesToPoint(int x, int y, int z) {
    return {
        x * delta_ + referencePoint_.x(),
        y * delta_ + referencePoint_.y(),
        z * delta_ + referencePoint_.z(),
    };
}

size_t cadcam::PointCloud::sizeX() const {
    return points_.size();
}

size_t cadcam::PointCloud::sizeY() const {
    return points_[0].size();
}

size_t cadcam::PointCloud::sizeZ() const {

}


#include "PointCloud.hpp"
#include <VolumeGridScanner.hpp>

cadcam::PointCloud::PointCloud(const point3d &referencePoint,
                               unsigned long nx,
                               unsigned long ny,
                               unsigned long nz,
                               double delta) :
                               grid_{
                                referencePoint,
                                delta
                                } {
    grid_.SetFinish(grid_.IndexToPoint({nx, ny, nz}));
    points_.resize(nx);
    for (size_t x = 0; x < nx; x++) {
        points_[x].resize(ny);
        for (size_t y = 0; y < ny; y++) {
            points_[x][y].resize(nz, true);
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
    auto index = grid_.PointToIndex(position);
    points_[index.x()][index.y()][index.z()] = value;
}

void cadcam::PointCloud::RemoveIntersection(const std::shared_ptr<Volume>& volume) {
    for (const auto& point : volume->GetInternalPoints(grid_)) {
        RemovePoint(point);
    }
}

size_t cadcam::PointCloud::sizeX() const {
    return points_.size();
}

size_t cadcam::PointCloud::sizeY() const {
    if (sizeX() > 0) {
        return points_[0].size();
    }
    return 0;
}

size_t cadcam::PointCloud::sizeZ() const {
    if (sizeY() > 0) {
        return points_[0][0].size();
    }
    return 0;
}

std::vector<cadcam::PointCloud::point3d> cadcam::PointCloud::GetSkinPoints() {
    std::vector<point3d> skinPoints {};
    skinPoints.reserve(sizeX() * sizeY());

    for (size_t x = 0; x < sizeX(); ++x) {
        for (size_t y = 0; y < sizeY(); ++y) {
            auto& zColumn = points_[x][y];
            size_t topPointIndex = sizeZ();
            while(not zColumn[topPointIndex]) {
                topPointIndex--;
            }
            skinPoints.push_back(grid_.IndexToPoint({x, y, topPointIndex}));
        }
    }

    return skinPoints;
}


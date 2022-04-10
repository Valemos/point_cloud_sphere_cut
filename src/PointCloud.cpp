#include "PointCloud.hpp"
#include <VolumeGridScanner.hpp>
#include <VolumeGridScanner.hpp>
#include <fstream>

cadcam::PointCloud::PointCloud(const point3d &referencePoint,
                               unsigned long nx,
                               unsigned long ny,
                               unsigned long nz,
                               double delta) :
                               grid_{
                                referencePoint,
                                IndicesToPoint(nx, ny, nz),
                                delta
                                } {
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
    points_
        [static_cast<size_t>(position.x() / grid_.step() - grid_.start().x())]
        [static_cast<size_t>(position.y() / grid_.step() - grid_.start().y())]
        [static_cast<size_t>(position.z() / grid_.step() - grid_.start().z())] = value;
}

void cadcam::PointCloud::RemoveIntersection(const Volume *volume) {
    for (const auto& point : volume->GetInternalPoints(grid_)) {
        RemovePoint(point);
    }
}

cadcam::PointCloud::point3d cadcam::PointCloud::IndicesToPoint(size_t x, size_t y, size_t z) {
    return {
        static_cast< double >(x) * grid_.step() + grid_.start().x(),
        static_cast< double >(y) * grid_.step() + grid_.start().y(),
        static_cast< double >(z) * grid_.step() + grid_.start().z(),
    };
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

void cadcam::PointCloud::SaveSkin(const std::string &fileName) {
    std::ofstream stream {fileName};
    for (const auto& point : GetSkinPoints()) {
        stream << point.x() << ' ' << point.y() << ' ' << point.z() << '\n';
    }
    stream.close();
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
            skinPoints.push_back(IndicesToPoint(x, y, topPointIndex));
        }
    }

    return skinPoints;
}


#include "PointCloud.hpp"
#include <VolumeGridScanner.hpp>
#include <VolumeGridScanner.hpp>
#include <fstream>

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
    cadcam::VolumeGridScanner<size_t> indexScanner{
        {0, 0, 0},
        {sizeX() - 1, sizeY() - 1, sizeZ() - 1},
        1
    };

    cadcam::VolumeGridScanner<double> pointScanner{
        referencePoint_,
        IndicesToPoint(sizeX() - 1, sizeY() - 1, sizeZ() - 1),
        delta_
    };

    while (indexScanner.InProgress()) {
        auto index = indexScanner.NextPoint();
        auto point = pointScanner.NextPoint();

        auto isPointExists = points_.at(index.x()).at(index.y()).at(index.z());
        if (isPointExists) {
            if (volume->ContainsPoint(point)) {
                isPointExists = false;
            }
        }
    }
}

cadcam::PointCloud::point3d cadcam::PointCloud::IndicesToPoint(size_t x, size_t y, size_t z) {
    return {
        static_cast< double >(x) * delta_ + referencePoint_.x(),
        static_cast< double >(y) * delta_ + referencePoint_.y(),
        static_cast< double >(z) * delta_ + referencePoint_.z(),
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
        stream << point.x() << " " << point.y() << " " << point.z() << '\n';
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


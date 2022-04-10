#include "Sphere.hpp"
#include "SphereLinearMotion.hpp"
#include "VolumeGridScanner.hpp"

cadcam::Sphere::Sphere(const mwTPoint3d<double>& center, double radius) : center_(center), radius_(radius){

}

bool cadcam::Sphere::ContainsPoint(const mwTPoint3d<double> &point) const {
    auto distanceSquared = point - center_;
    return distanceSquared * distanceSquared < radius_ * radius_;
}

const cadcam::mwTPoint3d<double> &cadcam::Sphere::center() const {
    return center_;
}

void cadcam::Sphere::SetCenter(const mwTPoint3d<double> &center) {
    center_ = center;
}

double cadcam::Sphere::radius() const {
    return radius_;
}

std::vector<cadcam::mwTPoint3d<double>>
cadcam::Sphere::GetInternalPoints(const cadcam::GridParameters3d<double> &grid) const {
    std::vector<mwTPoint3d<double>> points;

    auto sphereStart = center_ - mwTPoint3d<double>{radius_, radius_, radius_};
    auto sphereFinish = center_ + mwTPoint3d<double>{radius_, radius_, radius_};

    // todo add correct grid parameters
    VolumeGridScanner<double> scanner {{
                                           grid.SnapToGrid(sphereStart),
                                           grid.SnapToGrid(sphereFinish),
                                           grid.step()
                                        }};

    while (scanner.InProgress()) {
        auto point = scanner.NextPoint();
        if (ContainsPoint(point)) {
            points.push_back(point);
        }
    }

    return points;
}

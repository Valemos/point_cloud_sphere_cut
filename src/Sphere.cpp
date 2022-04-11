#include "Sphere.hpp"
#include "SphereLinearMotion.hpp"
#include "VolumeGridScanner.hpp"


cadcam::Sphere::Sphere(const mwTPoint3d<double>& center, double radius) :
    center_(center), radius_(radius), radiusSquared_(radius * radius) {
}

bool cadcam::Sphere::ContainsPoint(const mwTPoint3d<double> &point) const {
    auto difference = point - center_;
    return isLessOrEq(difference * difference, radiusSquared_);
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

    cadcam::GridParameters3d<double> sphereRegion {
        grid.RoundDown(sphereStart),
        grid.RoundUp(sphereFinish),
    grid.step()
    };

    ScanRegion(sphereRegion, points);
    return points;
}

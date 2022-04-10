#include <vector>
#include <SphereLinearMotion.hpp>

cadcam::SphereLinearMotion::SphereLinearMotion(
    const Sphere& startSphere,
    const mwTPoint3d<double>& destination)
    : sphere(destination, startSphere.radius()),
      cylinder(startSphere.center(), destination, startSphere.radius()) {
}

bool cadcam::SphereLinearMotion::ContainsPoint(const mwTPoint3d<double> &point) const {
    if (cylinder.ContainsPoint(point)) return true;
    if (sphere.ContainsPoint(point)) return true;
    return false;
}

std::vector<cadcam::mwTPoint3d<double>>
cadcam::SphereLinearMotion::GetInternalPoints(const cadcam::GridParameters3d<double> &grid) const {
    return std::vector<mwTPoint3d<double>>();
}


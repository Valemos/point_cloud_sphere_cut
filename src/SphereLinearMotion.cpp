#include <vector>
#include <SphereLinearMotion.hpp>

cadcam::SphereLinearMotion::SphereLinearMotion(
    const Sphere& sphere,
    const mwTPoint3d<double>& destination)
    : sphere(destination, sphere.radius()),
      cylinder(sphere.center(), destination, sphere.radius()) {
}

bool cadcam::SphereLinearMotion::ContainsPoint(const mwTPoint3d<double> &point) const {
    if (cylinder.ContainsPoint(point)) return true;
    if (sphere.ContainsPoint(point)) return true;
    return false;
}


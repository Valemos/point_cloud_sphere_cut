#include "Sphere.hpp"
#include "SphereLinearMotion.hpp"

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

const float & cadcam::Sphere::radius() const {
    return radius_;
}

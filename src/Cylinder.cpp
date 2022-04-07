#include <vector>
#include "Cylinder.hpp"

cadcam::Cylinder::Cylinder(const mwTPoint3d<double>& start,
                           const mwTPoint3d<double>& end,
                           float radius)
    : start_(start), end_(end), radius_(radius){
}

bool cadcam::Cylinder::ContainsPoint(const mwTPoint3d<double> &point) const {
    return false;
}

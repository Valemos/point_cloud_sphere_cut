#include "Cylinder.hpp"

cadcam::Cylinder::Cylinder(const mwTPoint3d<double>& start,
                           const mwTPoint3d<double>& finish,
                           double radius)
    : start_(start), finish_(finish), radius_(radius){

    // precalculate inverse of system of equations to save on computations
    double equations[2][2] = {
        {1 + start_ * start_, 1 + start_ * finish_},
        {1 + start_ * finish_, 1 + finish_ * finish_}
    };

    double det = equations[0][0] * equations[1][1] - equations[0][1] * equations[1][0];

    inverseEquations[0][0] = equations[1][1] / det;
    inverseEquations[0][1] = -equations[0][1] / det;
    inverseEquations[1][0] = -equations[1][0] / det;
    inverseEquations[1][1] = equations[0][0] / det;
}

bool cadcam::Cylinder::ContainsPoint(const mwTPoint3d<double> &point) const {
    // infinite line parameters
    auto e = finish_ - start_;
    auto m = start_ % finish_;

    auto distanceToLine = ~(e % (point - start_)) / ~e;
    if (distanceToLine > radius_)
        return false;

    auto closestPoint = point + (e % (m + e % point)) / (e * e);

    // conversion to barycentric coordinates
    double results[2] = {
        1 + closestPoint * start_,
        1 + closestPoint * finish_
    };

    double barycentricParams[2] = {
        results[0] * inverseEquations[0][0] + results[1] * inverseEquations[0][1],
        results[0] * inverseEquations[1][0] + results[1] * inverseEquations[1][1]
    };

    // check if point is in bounds of cylinder
    return barycentricParams[0] >= 0 and barycentricParams[0] <= 1 and
            barycentricParams[1] >= 0 and barycentricParams[1] <= 1;
}

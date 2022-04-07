#pragma once

#include "Volume.hpp"
#include "Sphere.hpp"
#include "Cylinder.hpp"

namespace cadcam {
class SphereLinearMotion : public Volume {
public:
    SphereLinearMotion(const Sphere& sphere, const mwTPoint3d<double>& destination);

    bool ContainsPoint(const mwTPoint3d<double> &point) const override;

private:
    Sphere sphere;
    Cylinder cylinder;
};
}



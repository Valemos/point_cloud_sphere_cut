#pragma once

#include <memory>
#include "Volume.hpp"
#include "Sphere.hpp"
#include "Cylinder.hpp"

namespace cadcam {
class SphereLinearMotion : public Volume {
public:
    SphereLinearMotion(const std::shared_ptr<Sphere>& startSphere, const mwTPoint3d<double>& destination);

    bool ContainsPoint(const mwTPoint3d<double> &point) const override;
    std::vector<mwTPoint3d<double>> GetInternalPoints(const GridParameters3d<double> &grid) const override;
private:
    Sphere sphere_;
    Cylinder cylinder_;
};
}



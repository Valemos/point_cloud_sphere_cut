#pragma once

#include <mwTPoint3d.hpp>
#include "Volume.hpp"

namespace cadcam {
class Cylinder : public Volume {
public:
    Cylinder(const mwTPoint3d<double>& start, const mwTPoint3d<double>& finish, double radius);
    bool ContainsPoint(const mwTPoint3d<double> &point) const override;
    std::vector<mwTPoint3d<double>> GetInternalPoints(const GridParameters3d<double> &grid) const override;

private:
    mwTPoint3d<double> start_;
    mwTPoint3d<double> finish_;
    double radius_;

    double inverseEquations[2][2] {};
};
}



#pragma once

#include <mwTPoint3d.hpp>
#include "Volume.hpp"

namespace cadcam {
class Cylinder : public cadcam::Volume {
public:
    Cylinder(const mwTPoint3d<double>& start, const mwTPoint3d<double>& end, float radius);
    bool ContainsPoint(const mwTPoint3d<double> &point) const override;

private:
    mwTPoint3d<double> start_;
    mwTPoint3d<double> end_;
    float radius_;
};
}



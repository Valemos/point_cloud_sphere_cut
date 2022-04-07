#pragma once

#include <vector>
#include "Volume.hpp"
#include <mwTPoint3d.hpp>


namespace cadcam {
class Sphere : public Volume {
public:
    Sphere(const mwTPoint3d<double>& center, double radius);
    Sphere(Sphere &other) = default;

    const mwTPoint3d<double> & center() const;
    void SetCenter(const mwTPoint3d<double> &center);
    const float & radius() const;
    bool ContainsPoint(const mwTPoint3d<double> &point) const override;

private:
    mwTPoint3d<double> center_;
    float radius_;
};
}
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
    double radius() const;
    bool ContainsPoint(const mwTPoint3d<double> &point) const override;
    std::vector<mwTPoint3d<double>> GetInternalPoints(const GridParameters3d<double> &grid) const override;
private:
    mwTPoint3d<double> center_;
    double radius_;
    double radiusSquared_;
};
}
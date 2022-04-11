#pragma once

#include "mwTPoint3d.hpp"
#include <cmath>

namespace cadcam {
template < class T > class GridParameters3d {
public:

    explicit GridParameters3d(T step) : start_{0, 0, 0}, finish_{INFINITY, INFINITY, INFINITY}, step_(step) {
    }

    GridParameters3d(const mwTPoint3d<T> &start,
                     const mwTPoint3d<T> &finish,
                     T step) :
                     start_(start),
                     finish_(finish),
                     step_(step) {
    }

    const mwTPoint3d<T> & start() const {
        return start_;
    }

    const mwTPoint3d<T> & finish() const {
        return finish_;
    }

    const T & step() const {
        return step_;
    }

    mwTPoint3d<T> SnapDown(const mwTPoint3d<T>& point) const {
        return {
            RoundToStepDown(point.x(), start_.x()),
            RoundToStepDown(point.y(), start_.y()),
            RoundToStepDown(point.z(), start_.z())
        };
    }

    mwTPoint3d<T> SnapUp(const mwTPoint3d<T>& point) const {
        return {
            RoundToStepUp(point.x(), start_.x()),
            RoundToStepUp(point.y(), start_.y()),
            RoundToStepUp(point.z(), start_.z())
        };
    }

private:
    mwTPoint3d<T> start_{};
    mwTPoint3d<T> finish_{};
    T step_{};

    inline T RoundToStepDown(T value, T centerOffset) const {
        auto gridCell = std::floor((value - centerOffset) / step_);
        return gridCell * step_ + centerOffset;
    }

    inline T RoundToStepUp(T value, T centerOffset) const {
        auto gridCell = std::ceil((value - centerOffset) / step_);
        return gridCell * step_ + centerOffset;
    }
};
}



#pragma once

#include "mwTPoint3d.hpp"

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

    mwTPoint3d<double> SnapToGrid(const mwTPoint3d<double>& point) const {
        return {
            RoundToStep(point.x(), start_.x()),
            RoundToStep(point.y(), start_.y()),
            RoundToStep(point.z(), start_.z())
        };
    }

private:
    mwTPoint3d<T> start_{};
    mwTPoint3d<T> finish_{};
    T step_{};

    inline T RoundToStep(T value, T centerOffset) const {
        auto gridCell = static_cast<long long>((value - centerOffset) / step_);
        return gridCell * step_ + centerOffset;
    }
};
}



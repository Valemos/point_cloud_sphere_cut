#pragma once

#include "mwTPoint3d.hpp"
#include <cmath>

namespace cadcam {
template<class T>
class GridParameters3d {
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

    GridParameters3d(const mwTPoint3d<T> &start,
                     T step) :
        start_(start),
        finish_{INFINITY, INFINITY, INFINITY},
        step_(step) {
    }

    const mwTPoint3d<T> &start() const {
        return start_;
    }

    const mwTPoint3d<T> &finish() const {
        return finish_;
    }

    void SetFinish(const mwTPoint3d<double>& point) {
        finish_ = point;
    }

    const T &step() const {
        return step_;
    }

    /*
     * rounds given point to closest grid node in given direction
     */
    mwTPoint3d<T> SnapDown(const mwTPoint3d<T> &point) const {
        return {
            RoundToStepDown(point.x(), start_.x()),
            RoundToStepDown(point.y(), start_.y()),
            RoundToStepDown(point.z(), start_.z())
        };
    }

    mwTPoint3d<T> SnapUp(const mwTPoint3d<T> &point) const {
        return {
            RoundToStepUp(point.x(), start_.x()),
            RoundToStepUp(point.y(), start_.y()),
            RoundToStepUp(point.z(), start_.z())
        };
    }

    /*
     * Index <-> Point Conversion functions
     *
     * It is assumed, that start_ point is (0, 0, 0)
     * and all points are located at grid nodes in +x, +y and +z directions
     * otherwise overflow might happen
     */
    mwTPoint3d<size_t> PointToIndex(const mwTPoint3d<T> &point) const {
        return {
            static_cast<size_t>(point.x() / step_ - start_.x()),
            static_cast<size_t>(point.y() / step_ - start_.y()),
            static_cast<size_t>(point.z() / step_ - start_.z()),
        };
    }

    mwTPoint3d<T> IndexToPoint(const mwTPoint3d<size_t> &index) const {
        return {
            static_cast< double >(index.x()) * step_ + start_.x(),
            static_cast< double >(index.y()) * step_ + start_.y(),
            static_cast< double >(index.z()) * step_ + start_.z()
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



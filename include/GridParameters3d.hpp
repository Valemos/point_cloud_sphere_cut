#pragma once

#include "mwTPoint3d.hpp"
#include <cmath>

namespace cadcam {
template<class T>
class GridParameters3d {
public:

    explicit GridParameters3d(T step);

    GridParameters3d(const mwTPoint3d<T> &start,
                     T step);

    GridParameters3d(const mwTPoint3d<T> &start,
                     const mwTPoint3d<T> &finish,
                     T step);

    const mwTPoint3d<T> &start() const;
    const mwTPoint3d<T> &finish() const;
    void SetFinish(const mwTPoint3d<double>& point);
    const T &step() const;

    /*
     * rounds given point to closest grid node in given direction
     */
    mwTPoint3d<T> RoundDown(const mwTPoint3d<T> &point) const;
    mwTPoint3d<T> RoundUp(const mwTPoint3d<T> &point) const;

    /*
     * Index <-> Point Conversion functions
     *
     * It is assumed, that start_ point is (0, 0, 0)
     * and all points are located at grid nodes in +x, +y and +z directions
     * otherwise overflow might happen
     */
    mwTPoint3d<size_t> PointToIndex(const mwTPoint3d<T> &point) const;
    mwTPoint3d<T> IndexToPoint(const mwTPoint3d<size_t> &index) const;

private:
    mwTPoint3d<T> start_{};
    mwTPoint3d<T> finish_{};
    T step_{};

    inline T RoundToStepDown(T value, T centerOffset) const;
    inline T RoundToStepUp(T value, T centerOffset) const;
};



template<class T>
GridParameters3d<T>::GridParameters3d(T step) : start_{0, 0, 0}, finish_{INFINITY, INFINITY, INFINITY}, step_(step) {
}

template<class T>
GridParameters3d<T>::GridParameters3d(const mwTPoint3d<T> &start, T step) :
    start_(start),
    finish_{INFINITY, INFINITY, INFINITY},
    step_(step) {
}

template<class T>
GridParameters3d<T>::GridParameters3d(const mwTPoint3d<T> &start, const mwTPoint3d<T> &finish, T step) :
    start_(start),
    finish_(finish),
    step_(step) {
}

template<class T>
const mwTPoint3d<T> &GridParameters3d<T>::start() const {
    return start_;
}

template<class T>
const mwTPoint3d<T> &GridParameters3d<T>::finish() const {
    return finish_;
}

template<class T>
void GridParameters3d<T>::SetFinish(const mwTPoint3d<double> &point) {
    finish_ = point;
}

template<class T>
const T &GridParameters3d<T>::step() const {
    return step_;
}

template<class T>
mwTPoint3d<T> GridParameters3d<T>::RoundDown(const mwTPoint3d<T> &point) const {
    return {
        RoundToStepDown(point.x(), start_.x()),
        RoundToStepDown(point.y(), start_.y()),
        RoundToStepDown(point.z(), start_.z())
    };
}

template<class T>
mwTPoint3d<T> GridParameters3d<T>::RoundUp(const mwTPoint3d<T> &point) const {
    return {
        RoundToStepUp(point.x(), start_.x()),
        RoundToStepUp(point.y(), start_.y()),
        RoundToStepUp(point.z(), start_.z())
    };
}

template<class T>
mwTPoint3d<size_t> GridParameters3d<T>::PointToIndex(const mwTPoint3d<T> &point) const {
    return {
        static_cast<size_t>(point.x() / step_ - start_.x()),
        static_cast<size_t>(point.y() / step_ - start_.y()),
        static_cast<size_t>(point.z() / step_ - start_.z()),
    };
}

template<class T>
mwTPoint3d<T> GridParameters3d<T>::IndexToPoint(const mwTPoint3d<size_t> &index) const {
    return {
        static_cast< double >(index.x()) * step_ + start_.x(),
        static_cast< double >(index.y()) * step_ + start_.y(),
        static_cast< double >(index.z()) * step_ + start_.z()
    };
}

template<class T>
T GridParameters3d<T>::RoundToStepDown(T value, T centerOffset) const {
    auto gridCell = std::floor((value - centerOffset) / step_);
    return gridCell * step_ + centerOffset;
}

template<class T>
T GridParameters3d<T>::RoundToStepUp(T value, T centerOffset) const {
    auto gridCell = std::ceil((value - centerOffset) / step_);
    return gridCell * step_ + centerOffset;
}
}



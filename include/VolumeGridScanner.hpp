#pragma once

#include <mwTPoint3d.hpp>
#include "GridParameters3d.hpp"

namespace cadcam {
template < class T > class VolumeGridScanner {
public:
    explicit VolumeGridScanner(cadcam::GridParameters3d<T> grid);

    mwTPoint3d<T> NextPoint();
    void IncrementX();
    void IncrementY();
    void IncrementZ();

    bool InProgress() const {
        return inProgress_;
    }

private:
    mwTPoint3d<T> currentPoint_{};
    GridParameters3d<T> grid_;

    bool inProgress_ {true};
};

template<class T>
VolumeGridScanner<T>::VolumeGridScanner(cadcam::GridParameters3d<T> grid) : grid_(grid) {
}

template<class T>
void VolumeGridScanner<T>::IncrementX() {
    currentPoint_.x(currentPoint_.x() + grid_.step());
    if (currentPoint_.x() > grid_.finish().x()) {
        currentPoint_.x(grid_.start().x());
        IncrementY();
    }
}

template<class T>
void VolumeGridScanner<T>::IncrementY() {
    currentPoint_.y(currentPoint_.y() + grid_.step());
    if (currentPoint_.y() > grid_.finish().y()) {
        currentPoint_.y(grid_.start().y());
        IncrementZ();
    }
}

template<class T>
void VolumeGridScanner<T>::IncrementZ() {
    currentPoint_.z(currentPoint_.z() + grid_.step());
    if (currentPoint_.z() > grid_.finish().z()) {
        inProgress_ = false;
    }
}

template<class T>
mwTPoint3d<T> VolumeGridScanner<T>::NextPoint() {
    mwTPoint3d<T> point {currentPoint_};
    IncrementX();
    return point;
}
}

#pragma once

#include <mwTPoint3d.hpp>

namespace cadcam {
template < class T > class VolumeGridScanner {
public:
    explicit VolumeGridScanner(T gridStep);
    VolumeGridScanner(const mwTPoint3d<T>& startPoint,
                      const mwTPoint3d<T>& finishPoint,
                      T gridStep);

    mwTPoint3d<T> NextPoint();

    void IncrementX();
    void IncrementY();
    void IncrementZ();

    bool InProgress() const {
        return inProgress_;
    }

private:
    mwTPoint3d<T> startPoint_{};
    mwTPoint3d<T> finishPoint_{};
    mwTPoint3d<T> currentPoint_{};
    T step_{};

    bool inProgress_ {true};
};

template<class T>
VolumeGridScanner<T>::VolumeGridScanner(T gridStep) : step_(gridStep) {
}


template<class T>
VolumeGridScanner<T>::VolumeGridScanner(const mwTPoint3d<T> &startPoint,
                                        const mwTPoint3d<T> &finishPoint,
                                        T gridStep) :
                                        startPoint_(startPoint),
                                        finishPoint_(finishPoint),
                                        currentPoint_(startPoint),
                                        step_(gridStep) {
}

template<class T>
void VolumeGridScanner<T>::IncrementX() {
    currentPoint_.x(currentPoint_.x() + step_);
    if (currentPoint_.x() > finishPoint_.x()) {
        currentPoint_.x(startPoint_.x());
        IncrementY();
    }
}

template<class T>
void VolumeGridScanner<T>::IncrementY() {
    currentPoint_.y(currentPoint_.y() + step_);
    if (currentPoint_.y() > finishPoint_.y()) {
        currentPoint_.y(startPoint_.y());
        IncrementZ();
    }
}

template<class T>
void VolumeGridScanner<T>::IncrementZ() {
    currentPoint_.z(currentPoint_.z() + step_);
    if (currentPoint_.z() > finishPoint_.z()) {
        inProgress_ = false;
    }
}

template<class T>
mwTPoint3d<T> VolumeGridScanner<T>::NextPoint() {
    IncrementX();
    return currentPoint_;
}
}

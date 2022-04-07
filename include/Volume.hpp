#pragma once

#include <mwTPoint3d.hpp>

namespace cadcam {
class Volume {
public:
    virtual bool ContainsPoint(const mwTPoint3d<double>& point) const = 0;
};
}



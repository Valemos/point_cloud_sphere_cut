#pragma once

#include "mwTPoint3d.hpp"
#include "GridParameters3d.hpp"
#include "VolumeGridScanner.hpp"

namespace cadcam {
class Volume {
public:
    virtual bool ContainsPoint(const mwTPoint3d<double>& point) const = 0;
    virtual std::vector<mwTPoint3d<double>> GetInternalPoints(const GridParameters3d<double>& grid) const = 0;
    void ScanRegion(const GridParameters3d<double>& region, std::vector<mwTPoint3d<double>>& results) const;
};
}

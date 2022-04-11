#include "Volume.hpp"


void cadcam::Volume::ScanRegion(const cadcam::GridParameters3d<double>& region,
                                std::vector<cadcam::mwTPoint3d<double>>& results) const {
    VolumeGridScanner<double> scanner {region};
    while (scanner.InProgress()) {
        auto point = scanner.NextPoint();
        if (ContainsPoint(point)) {
            results.push_back(point);
        }
    }
}
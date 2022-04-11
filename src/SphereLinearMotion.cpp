#include <vector>
#include <SphereLinearMotion.hpp>

cadcam::SphereLinearMotion::SphereLinearMotion(
    const std::shared_ptr<Sphere>& startSphere,
    const mwTPoint3d<double>& destination)
    : sphere_(destination, startSphere->radius()),
      cylinder_(startSphere->center(), destination, startSphere->radius()) {
}

bool cadcam::SphereLinearMotion::ContainsPoint(const mwTPoint3d<double> &point) const {
    if (cylinder_.ContainsPoint(point)) return true;
    if (sphere_.ContainsPoint(point)) return true;
    return false;
}

std::vector<cadcam::mwTPoint3d<double>>
cadcam::SphereLinearMotion::GetInternalPoints(const cadcam::GridParameters3d<double> &grid) const {
    auto movePoints = sphere_.GetInternalPoints(grid);
    auto cylinderPoints = cylinder_.GetInternalPoints(grid);

    movePoints.reserve(movePoints.size() + cylinderPoints.size());
    movePoints.insert(movePoints.end(), cylinderPoints.begin(), cylinderPoints.end());

    return movePoints;
}


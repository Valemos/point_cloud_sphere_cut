#include <CreateSkin.hpp>
#include "PointCloud.hpp"
#include "Sphere.hpp"
#include "SphereLinearMotion.hpp"

void CreateSkin( const cadcam::mwTPoint3d<double>& refPoint,
				const unsigned long nx, const unsigned long ny, 
				const unsigned long nz, const double sphereRad, 
				mwDiscreteFunction &func, const double deltaT, 
				const double delta, const std::string &skinFileName )
{
    cadcam::PointCloud cloud{refPoint, nx, ny, nz, delta};

    double time = func.GetBeginParameter();
    cadcam::Sphere sphereTool {func.Evaluate(time), sphereRad};
    time += deltaT;

    cloud.RemoveIntersection(&sphereTool);

    while(time <= func.GetEndParameter()) {
        auto next_point = func.Evaluate(time);
        time += deltaT;

        cadcam::SphereLinearMotion motion(sphereTool, next_point);
        cloud.RemoveIntersection(&motion);
    }

    cloud.SaveSkin(skinFileName);
}

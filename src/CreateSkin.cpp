#include <CreateSkin.hpp>
#include <iostream>
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
    auto nextPoint = func.Evaluate(time);
    time += deltaT;

    // remove initial tool position
    cadcam::Sphere sphereTool {nextPoint, sphereRad};
    cloud.RemoveIntersection(&sphereTool);

    while(time <= func.GetEndParameter()) {
        nextPoint = func.Evaluate(time);
        time += deltaT;

        // remove resulting movement
        cadcam::SphereLinearMotion motion(sphereTool, nextPoint);
        cloud.RemoveIntersection(&motion);

        sphereTool.SetCenter(nextPoint);
        std::cout << "time: " << time << " / " << func.GetEndParameter() << '\n';
    }
    std::cout << std::flush;

    cloud.SaveSkin(skinFileName);
}

#include <CreateSkin.hpp>
#include <iostream>
#include <fstream>
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
    auto sphereTool = std::make_shared<cadcam::Sphere>(nextPoint, sphereRad);
    cloud.RemoveIntersection(sphereTool);

    while(time <= func.GetEndParameter()) {
        nextPoint = func.Evaluate(time);
        time += deltaT;

        // remove resulting movement
        auto motion = std::make_shared<cadcam::SphereLinearMotion>(sphereTool, nextPoint);
        cloud.RemoveIntersection(std::move(motion));

        sphereTool->SetCenter(nextPoint);
        std::cout << "time: " << time << " / " << func.GetEndParameter() << '\n';
    }
    std::cout << std::flush;


    std::ofstream stream {skinFileName};
    for (const auto& point : cloud.GetSkinPoints()) {
        stream << point.x() << ' ' << point.y() << ' ' << point.z() << '\n';
    }
    stream.close();
}

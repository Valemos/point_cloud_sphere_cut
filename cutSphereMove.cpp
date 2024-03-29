#include <string>

#include <mwTPoint3d.hpp>
#include <mwArcFunction.hpp>
#include "include/CreateSkin.hpp"

//#############################################################################

int main(int argc, char* argv[])
{

	//Point cloud reference point at 0, 0, 0
	cadcam::mwTPoint3d<double> referencePoint( 0., 0., 0. );

	//Number of points_ in x direction
	const unsigned long nx = 1000;

	//Number of points_ in y direction
	const unsigned long ny = 500;

	//Number of points_ in z direction
	const unsigned long nz = 100;

	//Distance between points_ in the point grid (same fo x, y and z directions)
	const double delta = 1.;

	//Discrete step_ for move function calculation
	const double deltaT = 0.01;

	//Radius of the sphere_
	const double sphereRad = 5.;

	//Name of the file to write the skin data to
	const std::string skinFileName( "./test.asc" );

	//Function object to be evaluated
	mwArcFunction func( 0., 1., 150. );

	//Evaluation here
	CreateSkin( referencePoint, nx, ny, nz, sphereRad, func, deltaT, delta, skinFileName );

	return 0;
}

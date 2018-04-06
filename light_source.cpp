/***********************************************************

	Starter code for Assignment 3

	Implements light_source.h

***********************************************************/

#include <cmath>
#include "light_source.h"

using namespace std;

void PointLight::shade(Ray3D& ray) {
	// TODO: implement this function to fill in values for ray.col
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray
	// is available.  So be sure that traverseScene() is called on the ray
	// before this function.
  if (ray.intersection.none == false) {
    // vector initialization
    Point3D light_pos = PointLight::get_position();
  	Vector3D light_dir = light_pos - ray.intersection.point;
  	light_dir.normalize();

  	Vector3D normal = ray.intersection.normal;
  	normal.normalize();

  	Vector3D view_dir = -ray.dir;
  	view_dir.normalize();

  	Vector3D reflect_dir = 2.0 * normal.dot(light_dir)* normal - light_dir;
  	reflect_dir.normalize();

    // ambient
  	Color ambient;
    ambient = ray.intersection.mat->ambient * PointLight::col_ambient;

    // diffuse
    Color diffuse;
    diffuse = ray.intersection.mat->diffuse * PointLight::col_diffuse * (fmax(0.0, normal.dot(light_dir)));
  	
    // specular
  	Color specular =
    ray.intersection.mat->specular * PointLight::col_specular * (pow(fmax(0.0, view_dir.dot(reflect_dir)), ray.intersection.mat->specular_exp));

    // put them together
    Color new_color = ambient + diffuse + specular;
    new_color.clamp();

    ray.col = new_color + ray.col;
  	ray.col.clamp();
	}

}

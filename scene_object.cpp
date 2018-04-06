/***********************************************************

	Starter code for Assignment 3

	Implements scene_object.h

***********************************************************/

#include <cmath>
#include "scene_object.h"

bool UnitSquare::intersect(Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld) {
	// TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0),
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point,
	// intersection.normal, intersection.none, intersection.t_value.
	//
	// HINT: Remember to first transform the ray into object space
	// to simplify the intersection test.
	//Transform the ray
	Point3D model_origin = worldToModel*ray.origin;
	Vector3D model_dir = worldToModel*ray.dir;

	// assume ray intersects with x-y plane to get t,
	// check if it's inside the square later.
	double t = 0.0 - model_origin[2] / model_dir[2];

	// move intersection point a bit closer to origin to deal with numerical issue
	Point3D intersection = model_origin + (t - 1.0e-13) * model_dir;
	double x = intersection[0];
	double y = intersection[1];

	// invalid t value
	if (t <= 0) {
		return false;
	}
	Vector3D normal(0.0, 0.0, 1.0);
	// check if intersection inside the square
	if (x <= 0.5 && x >= -0.5 && y <= 0.5 && y >= -0.5) {
		// check if intersection is cloer than the previous one
		if (ray.intersection.none || t < ray.intersection.t_value) {
			ray.intersection.none = false;
			ray.intersection.point = modelToWorld*intersection;
			ray.intersection.normal = transNorm(worldToModel, normal);
			ray.intersection.normal.normalize();
			ray.intersection.t_value = t;
			return true;
		}
	}

	return false;
}

bool UnitSphere::intersect(Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld) {
	// TODO: implement intersection code for UnitSphere, which is centred
	// on the origin.
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point,
	// intersection.normal, intersection.none, intersection.t_value.
	//
	// HINT: Remember to first transform the ray into object space
	// to simplify the intersection test.
	Point3D center(0, 0, 0);
	double radius = 1.0;

	Point3D model_origin = worldToModel*ray.origin;
	Vector3D model_dir = worldToModel*ray.dir;
	Vector3D diff = model_origin - center;

	// At^2 + Bt + C = 0
	// [ dir.dir*t^2 ] + [ 2*t*dir.ori ] + [ ori.ori - R^2 ] = 0
	double A = model_dir.dot(model_dir);
	double B = 2.0 * diff.dot(model_dir);
	double C = diff.dot(diff) - radius * radius;
	double under_sqrt = (B*B) - 4.0*(A*C);

	// no root
	if (under_sqrt < 0) {
		return false;
	}
	// find roots
	double t1 = (-B + sqrt(under_sqrt)) / (2.0*A);
	double t2 = (-B - sqrt(under_sqrt)) / (2.0*A);
	double t = 0.0;

	// choose appropriate t
	if (t1 < 0 && t2 < 0) {
		return false;
	}
	// one negative one positive, choose the positve one
	if (t1 * t2 < 0) {
		t = std::max(t1, t2);
	}
	// both positve, choose the smaller one
	if (t1 * t2 > 0) {
		t = std::min(t1, t2);
	}
	// incase t_1 or t_2 is zero
	if (t <= 0) return false;

	// move intersection point a bit closer to origin to deal with numerical issue
	Point3D intersection = model_origin + (t - 1.0e-13) * model_dir;
	if (ray.intersection.none || t < ray.intersection.t_value) {
		ray.intersection.none = false;
		ray.intersection.point = modelToWorld*intersection;
		ray.intersection.normal = transNorm(worldToModel, (intersection - center));
		ray.intersection.normal.normalize();
		ray.intersection.t_value = t;
		return true;
	}
	return false;
}


void SceneNode::rotate(char axis, double angle) {
	Matrix4x4 rotation;
	double toRadian = 2*M_PI/360.0;
	int i;

	for (i = 0; i < 2; i++) {
		switch(axis) {
			case 'x':
				rotation[0][0] = 1;
				rotation[1][1] = cos(angle*toRadian);
				rotation[1][2] = -sin(angle*toRadian);
				rotation[2][1] = sin(angle*toRadian);
				rotation[2][2] = cos(angle*toRadian);
				rotation[3][3] = 1;
			break;
			case 'y':
				rotation[0][0] = cos(angle*toRadian);
				rotation[0][2] = sin(angle*toRadian);
				rotation[1][1] = 1;
				rotation[2][0] = -sin(angle*toRadian);
				rotation[2][2] = cos(angle*toRadian);
				rotation[3][3] = 1;
			break;
			case 'z':
				rotation[0][0] = cos(angle*toRadian);
				rotation[0][1] = -sin(angle*toRadian);
				rotation[1][0] = sin(angle*toRadian);
				rotation[1][1] = cos(angle*toRadian);
				rotation[2][2] = 1;
				rotation[3][3] = 1;
			break;
		}
		if (i == 0) {
			this->trans = this->trans*rotation;
			angle = -angle;
		}
		else {
			this->invtrans = rotation*this->invtrans;
		}
	}
}

void SceneNode::translate(Vector3D trans) {
	Matrix4x4 translation;

	translation[0][3] = trans[0];
	translation[1][3] = trans[1];
	translation[2][3] = trans[2];
	this->trans = this->trans*translation;
	translation[0][3] = -trans[0];
	translation[1][3] = -trans[1];
	translation[2][3] = -trans[2];
	this->invtrans = translation*this->invtrans;
}

void SceneNode::scale(Point3D origin, double factor[3] ) {
	Matrix4x4 scale;

	scale[0][0] = factor[0];
	scale[0][3] = origin[0] - factor[0] * origin[0];
	scale[1][1] = factor[1];
	scale[1][3] = origin[1] - factor[1] * origin[1];
	scale[2][2] = factor[2];
	scale[2][3] = origin[2] - factor[2] * origin[2];
	this->trans = this->trans*scale;
	scale[0][0] = 1/factor[0];
	scale[0][3] = origin[0] - 1/factor[0] * origin[0];
	scale[1][1] = 1/factor[1];
	scale[1][3] = origin[1] - 1/factor[1] * origin[1];
	scale[2][2] = 1/factor[2];
	scale[2][3] = origin[2] - 1/factor[2] * origin[2];
	this->invtrans = scale*this->invtrans;
}

void createEnvPlanes(Scene& envPlanes, double distance){
	Point3D origin = Point3D(0, 0, 0);
	double factor[3] = {distance * 2, distance * 2, distance * 2};

	// index 0: posx plane, red
	Material * posx_mat = new Material(Color(1, 0, 0), Color(1, 0, 0), Color(1, 0, 0), 10);
	SceneNode * posx_plane = new SceneNode(new UnitSquare(), posx_mat);
	posx_plane->translate(Vector3D(distance, 0, 0));
	posx_plane->scale(origin, factor);
	posx_plane->rotate('y', 90);
	envPlanes.push_back(posx_plane);

	// index 1: negx plane, orange
	Material * negx_mat = new Material(Color(1, 0.65, 0), Color(1, 0.65, 0), Color(1, 0.65, 0), 10);
	SceneNode * negx_plane = new SceneNode(new UnitSquare(), negx_mat);
	negx_plane->translate(Vector3D(-distance, 0, 0));
	negx_plane->scale(origin, factor);
	negx_plane->rotate('y', 90);
	envPlanes.push_back(negx_plane);

	// index 2: posy plane, green
	Material * posy_mat = new Material(Color(0, 1, 0), Color(0, 1, 0), Color(0, 1, 0), 10);
	SceneNode * posy_plane = new SceneNode(new UnitSquare(), posy_mat);
	posy_plane->translate(Vector3D(0, distance, 0));
	posy_plane->scale(origin, factor);
	posy_plane->rotate('x', 90);
	envPlanes.push_back(posy_plane);

	// index 3: negy plane, yellow
	Material * negy_mat = new Material(Color(1, 1, 0), Color(1, 1, 0), Color(1, 1, 0), 10);
	SceneNode * negy_plane = new SceneNode(new UnitSquare(), negy_mat);
	negy_plane->translate(Vector3D(0, -distance, 0));
	negy_plane->scale(origin, factor);
	negy_plane->rotate('x', 90);
	envPlanes.push_back(negy_plane);

	// index 4: posz plane, blue
	Material * posz_mat = new Material(Color(0, 0, 1), Color(0, 0, 1), Color(0, 0, 1), 10);
	SceneNode * posz_plane = new SceneNode(new UnitSquare(), posz_mat);
	posz_plane->translate(Vector3D(0, 0, distance));
	posz_plane->scale(origin, factor);
	envPlanes.push_back(posz_plane);

	// index 5: negz plane, purple
	Material * negz_mat = new Material(Color(0.5, 0, 0.5), Color(0.5, 0, 0.5), Color(0.5, 0, 0.5), 10);
	SceneNode * negz_plane = new SceneNode(new UnitSquare(), negz_mat);
	negz_plane->translate(Vector3D(0, 0, -distance));
	negz_plane->scale(origin, factor);
	envPlanes.push_back(negz_plane);
}
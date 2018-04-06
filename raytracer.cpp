/***********************************************************

	Starter code for Assignment 3

	Implementations of functions in raytracer.h,
	and the main function which specifies the scene to be rendered.

***********************************************************/


#include "raytracer.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#pragma omp parallel for

/***********************************************************
helper funcitons
***********************************************************/
/** return the a rand double in a specific range */
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

/** return the reflection ray given incident ray */
Ray3D reflection(Ray3D& incident_ray) {
    Ray3D reflect_ray;

    Vector3D normal = (incident_ray.intersection.normal);
    normal.normalize();
    Point3D start = incident_ray.intersection.point;

    Vector3D incident_dir = incident_ray.dir;
    Vector3D reflect_dir = incident_dir + 2.0 * (-1*normal.dot(incident_dir)) * normal;
    reflect_ray.origin = start;
    reflect_ray.dir = reflect_dir;

    return reflect_ray;
}

/** return rays from the intersection to SPHERE light sources */
Ray3D toLightRandom(int sNum, Ray3D& incident_ray, LightSource* light) {
    Ray3D toLight_ray;
    Point3D start = incident_ray.intersection.point;
	Point3D light_pos;

    if (sNum == 1) {
    	light_pos = light->get_position();
    }else {
	    double radius = 2.5;
	    double r = fRand(0.0, radius);
	    float theta = fRand(0.0, M_PI);
	    float phi = fRand(0.0, 2 * M_PI);
	    // Point3D light_pos = light->get_position();
	    light_pos = light->get_position()
	                        + Vector3D(r*sin(theta)*cos(phi),r*sin(theta)*cos(phi),r*cos(phi));
    }
    Vector3D toLight_dir = light_pos - start;
    toLight_dir.normalize();
    toLight_ray.origin = start;
    toLight_ray.dir = toLight_dir;

    return toLight_ray;
}

/** return rays from the intersection to light sources */
Ray3D toLight(Ray3D& incident_ray, LightSource* light) {
    Ray3D toLight_ray;

    Point3D start = incident_ray.intersection.point;

    Point3D light_pos = light->get_position();

    Vector3D toLight_dir = light_pos - start;
    toLight_dir.normalize();

    toLight_ray.origin = start;
    toLight_ray.dir = toLight_dir;

    return toLight_ray;
}

/** change the col attribute in Ray3D ray */
void setRayCol(Ray3D& ray, double numerator, double denominator) {
    ray.col = ray.col * (numerator / denominator);
}

/** return glossy reflection ray */
Ray3D glossy_reflection(Ray3D& incident_ray, double roughness) {
    Ray3D reflect_ray;
    Vector3D normal = (incident_ray.intersection.normal);
    normal.normalize();
    Point3D start = incident_ray.intersection.point;

    Vector3D incident_dir = incident_ray.dir;
    Vector3D reflect_dir = incident_dir + 2.0 * (-1*normal.dot(incident_dir)) * normal;
    reflect_dir.normalize();

    //Orthonormal basis at intersection point
    Vector3D u = reflect_dir.cross(normal);
    u.normalize();
    Vector3D v = reflect_dir.cross(u);
    v.normalize();

    // Choose uniformly sampled random direction to send the ray in
    double theta = fRand(0.0, 2*M_PI) * roughness;
    double phi = fRand(0.0, 2*M_PI) * roughness;
    double x = sin(theta) * cos(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(theta);

    // Convert sample to world coordinates using the orthonormal basis
    reflect_dir = x * u + y * v + z * reflect_dir;
    reflect_dir.normalize();

    reflect_ray.origin = start;
    reflect_ray.dir = reflect_dir;

    return reflect_ray;
}

Ray3D antiAliasRay(int aNum, int i, int j, Camera& camera, Image& image) {
    Point3D origin(0, 0, 0);
    Ray3D aRay;
    Point3D imagePlane;
    Matrix4x4 viewToWorld = camera.initInvViewMatrix();
    double factor = (double(image.height)/2)/tan(camera.fov*M_PI/360.0);

    if (aNum == 1) {
        imagePlane[0] = (-double(image.width)/2 + 0.5 + j)/factor;
        imagePlane[1] = (-double(image.height)/2 + 0.5 + i)/factor;
        imagePlane[2] = -1;
    } else {
        double height_off = ((double) rand() / (RAND_MAX));
        double width_off = ((double) rand() / (RAND_MAX));
        imagePlane[0] = (-double(image.width)/2 + height_off + j)/factor;
        imagePlane[1] = (-double(image.height)/2 + width_off + i)/factor;
        imagePlane[2] = -1;
    }
    Vector3D aDir = imagePlane - origin;
    aRay.dir = viewToWorld * aDir;
    aRay.dir.normalize();
    aRay.origin = viewToWorld * origin;

    return aRay;
}

Ray3D depthOfFieldRay(int dNum, double R, double f, Point3D& focalPoint, Camera& camera) {
    Ray3D dRay;
    Point3D origin(0, 0, 0);
    Matrix4x4 viewToWorld = camera.initInvViewMatrix();

    if (dNum == 1) {
        Vector3D dDir = focalPoint - (viewToWorld * origin); // focalPoint already in world
        dRay.origin =  viewToWorld * origin;
        dRay.dir = dDir;
        dRay.dir.normalize();
    } else {
        double r = fRand(0.0, R);
        double theta = fRand(0.0, 2*M_PI);
        double x = r * cos(theta);
        double y = r * sin(theta);

        Point3D dOrigin(x, y, 0);
        Vector3D dDir = focalPoint - (viewToWorld * dOrigin);
        dRay.origin =  viewToWorld * dOrigin;
        dRay.dir = dDir;
        dRay.dir.normalize();
    }

    return dRay;
}


/***********************************************************
provided functions
***********************************************************/
int Raytracer::traverseScene(Scene& scene, Ray3D& ray)  {
    int intersect = -1;
    for (size_t i = 0; i < scene.size(); ++i) {
        SceneNode* node = scene[i];
        if (node->obj->intersect(ray, node->worldToModel, node->modelToWorld)) {
            ray.intersection.mat = node->mat;
            intersect = i;
        }
    }
    return intersect;
}

void Raytracer::computeTransforms(Scene& scene) {
    // right now this method might seem redundant. But if you decide to implement
    // scene graph this is where you would propagate transformations to child nodes

    for (size_t i = 0; i < scene.size(); ++i) {
        SceneNode* node = scene[i];

        node->modelToWorld = node->trans;
        node->worldToModel = node->invtrans;
    }
}

void Raytracer::computeShading(Ray3D& ray, Scene& scene, LightList& light_list,
                               int sNum) {
    for (size_t  i = 0; i < light_list.size(); ++i) {
        LightSource* light = light_list[i];

        /** soft shadows */
        int num_HitLight = 0;

        for (int j = 0; j < sNum ; ++j) {
            Ray3D toLight_ray = toLightRandom(sNum, ray, light);
            traverseScene(scene, toLight_ray);
            // if the ray did not hit any thing but the light
            if (toLight_ray.intersection.none) {
                num_HitLight = num_HitLight + 1;
            } else {
                // if ray hit light before it hit any object, shade it.
                Vector3D toLight = light->get_position() - toLight_ray.origin;
                double t_light = toLight.norm();
                if(toLight_ray.intersection.t_value >= t_light) {
                    num_HitLight = num_HitLight + 1;
                }
            }
        }
        light->shade(ray);
        setRayCol(ray, num_HitLight, sNum);
    }
}


void Raytracer::computeEnvMapping(Ray3D& ray, Scene& envPlanes, 
								  vector<Image *>& envImages) {
    traverseScene(envPlanes, ray);

    if (!ray.intersection.none) {
        // compute uv value, and plane index
        double x = ray.intersection.point[0];
        double y = ray.intersection.point[1];
        double z = ray.intersection.point[2];
        int i;
        double u;
        double v;
        xyz_to_iuv(x, y, z, &i, &u, &v);

        int width = envImages[0]->width;
        int height = envImages[0]->height;
        int uInt = floor(u*width);
        int vInt = floor(v*height);

        // set color
        Color envColor = Color();
        envImages[i]->getColorAtPixel(uInt, vInt, envColor);
        ray.col = ray.col + 1.0 * envColor;
        ray.col.clamp();
    }
}

void Raytracer::computeTextureMapping(Ray3D& ray, SceneNode * node, Image * image){
   
    // compute uv value
    Point3D intersection = ray.intersection.point;
    Point3D center = node->modelToWorld * Point3D(0, 0, 0);
    double u;
    double v;
    xyz_to_uv(intersection, center, &u, &v);

    int width = image->width;
    int height = image->height;
    int uInt = floor(u*width);
    int vInt = floor(v*height);

    // set color
    Color textureColor = Color();
    image->getColorAtPixel(uInt, vInt, textureColor);
    ray.col = ray.col + 1.0 * textureColor;
    ray.col.clamp();
}


Color Raytracer::shadeRay(Ray3D& ray, Scene& scene, LightList& light_list, int numReflection,
                          Scene& envPlanes, vector<Image *>& envImages, vector<Image *>& textureImages, int sNum, int gNum) {
    
    Color col(0.0, 0.0, 0.0);
    int intersect = traverseScene(scene, ray);

    // if the ray hit some object, set light color and texture color
    if (!ray.intersection.none) {
        computeShading(ray, scene, light_list, sNum);
        if (textureImages.size() > 0){
            Image * textureImage = textureImages[intersect];
            if (textureImage->width > 0 && textureImage->height > 0){
                SceneNode * node = scene[intersect];
                computeTextureMapping(ray, node, textureImage);
            }   
        }
        col = ray.col;
        // You'll want to call shadeRay recursively (with a different ray,
        // of course) here to implement reflection/refraction effects.
        if (numReflection > 0) {
            /** glossy reflection */
            Color reflectionCol(0.0, 0.0, 0.0);
            if (gNum > 1) {
                for (int i = 0; i < gNum; i++) {
                    Ray3D reflectionRay = glossy_reflection(ray, 1.0);
                    reflectionCol = reflectionCol + ((1.0 / gNum) * shadeRay(reflectionRay, scene, light_list, numReflection-1, envPlanes, envImages, textureImages, sNum, 1));
                }
            }
            else {
                Ray3D reflectionRay = reflection(ray);
                reflectionCol = shadeRay(reflectionRay, scene, light_list, numReflection-1, envPlanes, envImages, textureImages, sNum, 1);
            }
            col = 1.0 * col + 0.5 * reflectionCol;
            col.clamp();
        }
    } 
    else if (envPlanes.size() > 0 && envImages.size() > 0) {
        // if the ray did not hit anythin in scene, map environment color to it
        computeEnvMapping(ray, envPlanes, envImages);
        col = ray.col;
    }

    return col;
}


void Raytracer::render(Camera& camera, Scene& scene, LightList& light_list, Image& image,
                       bool aFlag, bool dFlag, bool sFlag, bool gFlag,
                       Scene envPlanes, vector<Image *> envImages, vector<Image *> textureImages) {
    computeTransforms(scene);
    computeTransforms(envPlanes);

    Matrix4x4 viewToWorld = camera.initInvViewMatrix();
    double factor = (double(image.height)/2)/tan(camera.fov*M_PI/360.0);

    int numReflection = 3;
    int aNum = 16;
    int dNum = 8;
    int sNum = 250;
    int gNum = 30;
    if (!aFlag) {
        aNum = 1;
    }
    if (!dFlag) {
        dNum = 1;
    }
    if (!sFlag) {
    	sNum = 1;
    }
    if (!gFlag) {
    	gNum = 1;
    }

    // Construct a ray for each pixel.
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            // Sets up ray origin and direction in view space,
            // image plane is at z = -1.
            Point3D origin(0, 0, 0);

            // anti-aliasing
            Color aCol(0.0, 0.0, 0.0);
            for (int a = 0; a < aNum; a++) {
                Ray3D aRay = antiAliasRay(aNum, i, j, camera, image);

                // depth of field
                double R = 0.1;
                double f = 8.0;
                Point3D focalPoint = aRay.origin + f * aRay.dir;
                Color dCol(0.0, 0.0, 0.0);
                for (int d = 0; d < dNum; d++) {
                    Ray3D dRay = depthOfFieldRay(dNum, R, f, focalPoint, camera);
                    dCol = dCol + (1.0 / dNum) * shadeRay(dRay, scene, light_list, numReflection, envPlanes, envImages, textureImages, sNum, gNum);
                }
                aCol = aCol + (1.0 / aNum) * dCol;
            }

            image.setColorAtPixel(i, j, aCol);
        }
    }
}

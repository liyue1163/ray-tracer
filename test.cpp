#include <cstdlib>
#include "util.h"
#include "raytracer.h"
using namespace std;

int main(int argc, char* argv[]) {
    // test arguments
    cout << "argv" << argv << endl; 

 //    // test xyz_to_iuv
 //    double x = 0.0;
 //    double y = 1.0;
 //    double z = 0.0;
 //    int index;
 //    double u;
 //    double v;
 //    xyz_to_iuv(x, y, z, &index, &u, &v);
 //    cout << "index: " << index << endl;
 //    cout << "u: " << u << endl;
 //    cout << "v: " << v << endl << endl;
  
 //    x = 10.0;
 //    y = -4.0;
 //    z = 8.0;
 //    xyz_to_iuv(x, y, z, &index, &u, &v);
 //    cout << "index: " << index << endl;
 //    cout << "u: " << u << endl;
 //    cout << "v: " << v << endl << endl;

 //    x = 10.0;
 //    y = -8.0;
 //    z = 8.0;
 //    xyz_to_iuv(x, y, z, &index, &u, &v);
 //    cout << "index: " << index << endl;
 //    cout << "u: " << u << endl;
 //    cout << "v: " << v << endl << endl;


 //    // test Image
 //    // create a 2x2 image
 //    int width = 2;
 //    int height = 2;
 //    Image image = Image(width, height);
 //    Color red = Color(1, 0, 0);
 //    Color green = Color(0, 1, 0);
 //    Color blue = Color(0, 0, 1);
 //    Color black = Color(0, 0, 0);
 //    image.setColorAtPixel(0, 0, red);
 //    image.setColorAtPixel(0, 1, green);
 //    image.setColorAtPixel(1, 0, blue);
 //    image.setColorAtPixel(1, 1, black);
 //    image.flushPixelBuffer("textures/2x2.bmp");


 //    // test Images' methods
 //    // getColorAtPixel, expecting black
 //    Color col = Color();
 //    image.getColorAtPixel(1, 1, col);
 //    cout << "color at (1, 1) before reset: " << col << endl;

 //    // setPixelBuffer, expecting red at (1, 1)
 //    unsigned char * rarray = new unsigned char[4];
 //    rarray[0] = 255;
 //    rarray[1] = 255;
 //    rarray[2] = 255;
 //    rarray[3] = 255;
 //    cout << "rarray: " << +rarray[0] << ", " << +rarray[1] << ", " << +rarray[2] << ", " << +rarray[3] << endl;
 //    image.setPixelBuffer('r', rarray);
 //    image.getColorAtPixel(1, 1, col);
 //    cout << "color at (1, 1) after reset: " << col << endl << endl;


 //    // test image constructor with unsigned char arrays
 //    unsigned char * garray = new unsigned char[4];
 //    garray[0] = 255;
 //    garray[1] = 255;
 //    garray[2] = 255;
 //    garray[3] = 255;
 //    cout << "garray: " << +garray[0] << ", " << +garray[1] << ", " << +garray[2] << ", " << +garray[3] << endl;

 //    unsigned char * barray = new unsigned char[4];
 //    barray[0] = 255;
 //    barray[1] = 255;
 //    barray[2] = 255;
 //    barray[3] = 255;
 //    cout << "barray: " << +barray[0] << ", " << +barray[1] << ", " << +barray[2] << ", " << +barray[3] << endl;

 //    Image new_image = Image(2, 2, rarray, garray, barray);
 //    new_image.getColorAtPixel(1, 1, col);
 //    cout << "color at (1, 1) after created a new_image: " << col << endl << endl;


 //    // test createEnvImages
 //    vector<Image *> envImages;
 //    createEnvImages(envImages, "textures/t1/t1_bmp_512", 512, 512);
 //    Image * posx_image = envImages[0];
 //    posx_image->getColorAtPixel(0, 0, col);
 //    cout << "color at (0, 0) in posx.bmp: " << col << endl;
 //    posx_image->getColorAtPixel(511, 511, col);
 //    cout << "color at (511, 511) in posx.bmp: " << col << endl;
 //    posx_image->getColorAtPixel(256, 256, col);
 //    cout << "color at (256, 256) in posx.bmp: " << col << endl << endl;

 //    Image * negx_image = envImages[1];
 //    negx_image->getColorAtPixel(0, 0, col);
 //    cout << "color at (0, 0) in negx.bmp: " << col << endl;
 //    negx_image->getColorAtPixel(511, 511, col);
 //    cout << "color at (511, 511) in negx.bmp: " << col << endl;
 //    negx_image->getColorAtPixel(256, 256, col);
 //    cout << "color at (256, 256) in negx.bmp: " << col << endl << endl;

 //    Image * posy_image = envImages[2];
 //    posy_image->getColorAtPixel(0, 0, col);
 //    cout << "color at (0, 0) in posy.bmp: " << col << endl;
 //    posy_image->getColorAtPixel(511, 511, col);
 //    cout << "color at (511, 511) in posy.bmp: " << col << endl;
 //    posy_image->getColorAtPixel(256, 256, col);
 //    cout << "color at (256, 256) in posy.bmp: " << col << endl << endl;

 //    Image * negy_image = envImages[3];
 //    negy_image->getColorAtPixel(0, 0, col);
 //    cout << "color at (0, 0) in negy.bmp: " << col << endl;
 //    negy_image->getColorAtPixel(511, 511, col);
 //    cout << "color at (511, 511) in negy.bmp: " << col << endl;
 //    negy_image->getColorAtPixel(256, 256, col);
 //    cout << "color at (256, 256) in negy.bmp: " << col << endl << endl;

 //    Image * posz_image = envImages[4];
 //    posz_image->getColorAtPixel(0, 0, col);
 //    cout << "color at (0, 0) in posz.bmp: " << col << endl;
 //    posz_image->getColorAtPixel(511, 511, col);
 //    cout << "color at (511, 511) in posz.bmp: " << col << endl;
 //    posz_image->getColorAtPixel(256, 256, col);
 //    cout << "color at (256, 256) in posz.bmp: " << col << endl << endl;

 //    Image * negz_image = envImages[5];
 //    negz_image->getColorAtPixel(0, 0, col);
 //    cout << "color at (0, 0) in negz.bmp: " << col << endl;
 //    negz_image->getColorAtPixel(511, 511, col);
 //    cout << "color at (511, 511) in negz.bmp: " << col << endl;
 //    negz_image->getColorAtPixel(256, 256, col);
 //    cout << "color at (256, 256) in negz.bmp: " << col << endl << endl;


 //    // test createEnvPlanes
 //    cout << "reached createEnvPlanes part in test.cpp" << endl;
 //    Scene envPlanes;
	// LightList light_list;
	// Raytracer raytracer;	
 //    width = 100;
 //    height = 100;
 //    createEnvPlanes(envPlanes, 10);
 //    PointLight* pLight1 = new PointLight(Point3D(5,0,0), Color(0.9,0.9,0.9));
	// light_list.push_back(pLight1);
 //    PointLight* pLight2 = new PointLight(Point3D(15,15,15), Color(0.9,0.9,0.9));
	// light_list.push_back(pLight2);

 //    Camera env_camera1(Point3D(20, 20, 20), Vector3D(-1, -1, -1), Vector3D(0, 0, 1), 60.0);
 //    Image env_image1(width, height);
 //    raytracer.render(env_camera1, envPlanes, light_list, env_image1);
 //    env_image1.flushPixelBuffer("results/env1.bmp");
 //    cout << "image1 saved to results/env1.bmp" << endl;

 //    Camera env_camera2(Point3D(-9.5, 0, 0), Vector3D(1, 0, 0), Vector3D(0, 0, 1), 60.0);
 //    Image env_image2(width, height);
 //    raytracer.render(env_camera2, envPlanes, light_list, env_image2);
 //    env_image2.flushPixelBuffer("results/env2.bmp");
 //    cout << "image2 saved to results/env2.bmp" << endl << endl;


 //    // test environment mapping
	// Scene scene;	
	// Material gold(Color(0.3, 0.3, 0.3), Color(0.75164,0.60648,0.22648),
	// 	Color(0.628281, 0.555802, 0.366065),
	// 	51.2); 
	// SceneNode* sphere = new SceneNode(new UnitSphere(), &gold);
	// scene.push_back(sphere);   

	// width = 200;
	// height = 200;

 //    Camera env_camera(Point3D(-5, 0, 0), Vector3D(1, 0, 0), Vector3D(0, 0, 1), 60.0);
 //    Image env_image(width, height);
 //    raytracer.render(env_camera, scene, light_list, env_image, envPlanes, envImages);
 //    // raytracer.render(env_camera, scene, light_list, env_image);    
 //    env_image.flushPixelBuffer("results/env.bmp");
 //    cout << "image saved to results/env.bmp" << endl << endl;


    // test xyz_to_uv
    Point3D intersection(1, 0, 0);
    Point3D center(0, 0, 0);
    double u;
    double v;
    xyz_to_uv(intersection, center, &u, &v);
    cout << "u: " << u << ", v: " << v << endl;


    return 0;
}
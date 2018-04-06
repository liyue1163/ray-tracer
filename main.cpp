/***********************************************************

	Starter code for Assignment 3

***********************************************************/

#include <cstdlib>
#include "raytracer.h"

int main(int argc, char* argv[])
{
	// Build your scene and setup your camera here, by calling
	// functions from Raytracer.  The code here sets up an example
	// scene and renders it from two different view points, DO NOT
	// change this if you're just implementing part one of the
	// assignment.
	Raytracer raytracer;
	LightList light_list;
	Scene scene;

	int width = 320;
	int height = 240;

	// add some flags to control the features
	bool eFlag = false; // environment mapping
	bool dFlag = false; // depth of feild
	bool gFlag = false; // glossy reflection
	bool aFlag = false; // anti-aliasing
	bool sFlag = false; // soft shadow and augmented lighting
	bool tFlag = false; // texture mapping
	int f = 0;	
	if (argc == 2) {
		if (argv[1][0] != '-'){
			cout << "please enter both width and height" << endl;
			return 1;
		}
		f = 1;
	}else if (argc > 2){
		if (argv[1][0] != '-'){
			if (argv[2][0] != '-'){
				width = atoi(argv[1]);
				height = atoi(argv[2]);
				f = 3;
			}else{
				cout << "please enter both width and height" << endl;
				return 1;	
			}	
		}
		f = 1;
	}
	for (f; f < argc; f++){
		switch (argv[f][1]){
			case 'e': eFlag = true; cout << "environment mapping on" << endl; break;
			case 'd': dFlag = true; cout << "depth of feild on" << endl; break;
			case 'g': gFlag = true; cout << "glossy reflection on" << endl; break;
			case 'a': aFlag = true; cout << "anti-aliasing on" << endl; break;
			case 's': sFlag = true; cout << "soft shadow on" << endl; break;
			case 't': tFlag = true; cout << "texture mapping on" << endl; break;
		}
	}		

	// Define materials for shading.
	Material gold(Color(0.3, 0.3, 0.3), Color(0.75164,0.60648,0.22648),
		Color(0.628281, 0.555802, 0.366065),
		51.2);
	Material jade(Color(0, 0, 0), Color(0.54,0.89,0.63),
		Color(0.316228,0.316228,0.316228),
		12.8);

	// Defines a point light source.
	PointLight* pLight = new PointLight(Point3D(0,0,5), Color(0.9,0.9,0.9));
	light_list.push_back(pLight);

	// Add a unit square into the scene with material mat.
	SceneNode* sphere_2 = new SceneNode(new UnitSphere(), &gold);
	scene.push_back(sphere_2);

	SceneNode* sphere_1 = new SceneNode(new UnitSphere(), &gold);
	scene.push_back(sphere_1);
	SceneNode* plane = new SceneNode(new UnitSquare(), &jade);
	scene.push_back(plane);

	// Apply some transformations to the sphere and unit square.
	sphere_2->translate(Vector3D(-0.3, 0, -2));
	sphere_2->rotate('x', -45);
	sphere_2->rotate('z', 45);

	double factor1[3] = { 1.0, 2.0, 1.0 };
	sphere_1->translate(Vector3D(0, 0, -5));
	sphere_1->rotate('x', -45);
	sphere_1->rotate('z', 45);
	sphere_1->scale(Point3D(0, 0, 0), factor1);

	double factor2[3] = { 6.0, 6.0, 6.0 };
	plane->translate(Vector3D(0, 0, -7));
	plane->rotate('z', 45);
	plane->scale(Point3D(0, 0, 0), factor2);

	// Render the scene, feel free to make the image smaller for
	// testing purposes.
	vector<Image *> envImages;
	vector<Image *> textureImages;
    Scene envPlanes;

	if (eFlag) {
	    createEnvImages(envImages, "textures/t1/t1_bmp_512", 512, 512);		
	    createEnvPlanes(envPlanes, 20);   
	}
	if (tFlag){
		const char* args0[] = {"textures/earth/earthmap.bmp", "\0", "\0"};
 		const int args1[] = {1000, 0, 0};
 		const int args2[] = {500, 0, 0};
 		vector<string> file_in_names(args0, args0+3);
		vector<int> widths(args1, args1+3);
		vector<int> heights(args2, args2+3);
		createTextureImages(textureImages, file_in_names, widths, heights);
	}
	
	Camera camera1(Point3D(1, 0, 0), Vector3D(0, 0, -1), Vector3D(0, 1, 0), 60.0);
	Image image1(width, height);
	raytracer.render(camera1, scene, light_list, image1, aFlag, dFlag, sFlag, gFlag, envPlanes, envImages, textureImages); //render 3D scene to image
	image1.flushPixelBuffer("results/view1.bmp"); //save rendered image to file

	// Render it from a different point of view.
	Camera camera2(Point3D(4, 2, 1), Vector3D(-4, -2, -6), Vector3D(0, 1, 0), 60.0);
	//Camera camera2(Point3D(-4, -2, -6), Vector3D(3, 3, -1), Vector3D(0, 1, 0), 60.0);
	Image image2(width, height);
	raytracer.render(camera2, scene, light_list, image2, aFlag, dFlag, sFlag, gFlag, envPlanes, envImages, textureImages);
	image2.flushPixelBuffer("results/view2.bmp");

	// Free memory
	for (size_t i = 0; i < scene.size(); ++i) {
		delete scene[i];
	}

	for (size_t i = 0; i < light_list.size(); ++i) {
		delete light_list[i];
	}
	
	for (size_t i = 0; i < envPlanes.size(); ++i) {
		delete envPlanes[i];
	}

	for (size_t i = 0; i < envImages.size(); ++i) {
		delete envImages[i];
	}
	return 0;
}

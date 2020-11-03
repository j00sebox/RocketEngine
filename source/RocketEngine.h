#ifndef RENGINE_H
#define RENGINE_H

#include "SceneNode.h"
//needed to load pcx files
#include <nds/arm9/image.h>
#include <time.h>

class RocketEngine
{
public:
	RocketEngine() { }

	// sets generic settings for openGL
	void init();

	// changes camera position and calls render fucntion
	void Run();

	// add object to scene graph and sets some values for it
	void CreateObject(GeometryNode* node, GeometryNode* parent, GL_GLBEGIN_ENUM geoRenderType, Geometry geoType, Vec3D* vertices, int size, Vec3D boundingBox, bool col);

private:
	// walks through all nodes in scene
	void Render();

	// initial nodes in scene graph
	SceneNode root;
	CameraNode fpCam;

	// changes in camera position for every game loo[
	float posx = 0.0f;
	float posz = 0.0f;

	// the walkbias variables are use to give the appearence of real walking
	float walkbias = 0; 
	float walkbiasangle = 0;

	float camy = 0.0f;
	float lookAngle = 90.0f; // initial lookangle for camera

};

#endif // !RENGINE_H

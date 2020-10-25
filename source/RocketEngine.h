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

	// load given texture to be used in scene
	int LoadTextures(const u8 text []);

	// add object to scene graph and sets some values for it
	void CreateObject(GeometryNode* node, GeometryNode* parent, GL_GLBEGIN_ENUM geoRenderType, Geometry geoType, Vec3D* vertices, int size, Vec3D boundingBox, bool col);

	// faster way to make a quad and only one vertex is needed
	void QuickQuad(GeometryNode* quad, float x, float y, float z, float width, float height, float depth);

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
	int texture[1]; // Storage For One Texture

};

#endif // !RENGINE_H

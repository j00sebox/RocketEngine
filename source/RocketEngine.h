#ifndef RENGINE_H
#define RENGINE_H

#include "SceneNode.h"

class RocketEngine
{
public:
	RocketEngine() {}

	void init();

	void Run();

	void Render();

	void SetColorMode(bool choice);

	void CreateObject(GeometryNode* node, GL_GLBEGIN_ENUM geoRenderType, Geometry geoType, Vec3D* vertices, Vec3D boundingBox);

	void QuickQuad(GeometryNode* quad, float x, float y, float z, float width, float height, float depth);

private:
	SceneNode root;
	CameraNode fpCam;
	bool colourMode = false;
	float posx = 0.0f;
	float posz = 0.0f;
	float walkbias = 0;
	float walkbiasangle = 0;
	float camy = 0.0f;
	float lookAngle = 90.0f;
	int texture[1]; // Storage For One Texture

};

#endif // !RENGINE_H

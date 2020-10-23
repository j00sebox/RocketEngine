#ifndef SCENENODE_H
#define SCENENODE_H


#include <nds.h>
//#include <nds/arm9/boxtest.h>
#include <list>
#include <vector>
#include <cstdio>
#include <stdio.h>
#include <string>

#define POLYGON_LIMIT 4000

extern int polygons;

class SceneNode
{
public:
	// constructor
	SceneNode() { }

	// destructor - calls destroy
	virtual ~SceneNode() { Destroy(); }

	// release this object from memory
	void Release() { delete this; }

	// update our scene node
	virtual void Update();

	// destroy all the children
	void Destroy();

	void AddChild(SceneNode* pNode);

	// list of children
	std::list<SceneNode*> childList;
};

struct Vec3D {
	Vec3D(float a = 0, float b = 0, float c = 0)
	{
		x = a; y = b; z = c;
	}

	float x, y, z;
};

enum Geometry {
	TRIANGLE = 3,
	QUAD
};

class CameraNode : public SceneNode
{
public:
	CameraNode() { }
	~CameraNode() { }

	void UpdateCameraPos(float dx, float dy, float dz);

	void UpdateCameraLook(float dx, float dy, float dz);

	void SetCameraPos(float x, float y, float z);

	void SetCameraPosY(float y);

	void SetCameraLook(float x, float y, float z);

	void SetCameraLookX(float x);

	void SetCameraLookY(float y);

	void SetCameraLookZ(float z);

	float GetPosX() { return eye.x; }
	float GetPosY() { return eye.y; }
	float GetPosZ() { return eye.z; }

	void Update();

private:
	Vec3D eye;
	Vec3D lookAt;
};

class GeometryNode : public SceneNode
{
public:
	GeometryNode() { }
	GeometryNode(float x, float y, float z) { coord.x = x; coord.y = y; coord.z = z; rot.x = 0.0f; rot.y = 0.0f; rot.z = 0.0f; }
	~GeometryNode() { }

	void Update();

	void Offset(float x, float y, float z)
	{
		offset.x = x;
		offset.y = y;
		offset.z = z;
	}

	void AddVertex(float x, float y, float z);

	void AddColour(float r, float g, float b);

	void UpdateRot(float dx, float dy, float dz);

	void UpdateCoord(float dx, float dy, float dz);

	void SetRot(float x, float y, float z) { rot.x = x; rot.y = y; rot.z = z; }

	void SetCoord(float x, float y, float z); 

	void SetGeometryType(GL_GLBEGIN_ENUM geoRenderType, Geometry geoType) { geometryRenderType = geoRenderType;  geometryType = geoType; }

	void CreateBoundingBox(float width, float height, float depth);

	float GetCoordX() { return coord.x; }
	float GetCoordY() { return coord.y; }
	float GetCoordZ() { return coord.z; }

private:
	Vec3D coord;
	Vec3D offset;
	Vec3D rot;
	Vec3D boundingBox;
	m4x4 position;
	m4x4 vector;
	Geometry geometryType;
	GL_GLBEGIN_ENUM geometryRenderType;
	std::vector<Vec3D> vertices;
	std::vector<Vec3D> colours;
	std::vector<Vec3D> textures;
	void Draw();

};

#endif

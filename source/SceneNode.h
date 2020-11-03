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

// easy way to store objects that need 3 points
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

	// update camera position
	void UpdateCameraPos(float dx, float dy, float dz);

	// update where camera is looking at
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
	Vec3D eye; // where camera is positioned
	Vec3D lookAt; // what camera is looking at
};

class GeometryNode : public SceneNode
{
public:
	GeometryNode() { scale.x = 1.0f; scale.y = 1.0f; scale.z = 1.0f; }
	// optional constructor can set initial position
	GeometryNode(float x, float y, float z) { coord.x = x; coord.y = y; coord.z = z; rot.x = 0.0f; rot.y = 0.0f; rot.z = 0.0f; scale.x = 1.0f; scale.y = 1.0f; scale.z = 1.0f; }
	~GeometryNode() { }

	// native update function to handle all the transformations and drawing for this object
	void Update();

	// if child, offset can be set with this
	void Offset(float x, float y, float z)
	{
		offset.x = x;
		offset.y = y;
		offset.z = z;
	}

	// add vertex to object
	void AddVertex(float x, float y, float z);

	// add colour, order added matters
	void AddColour(float r, float g, float b);

	// add texture coords, need one for each vertex
	void AddTextCoord(float x, float y);

	// will update rotation vector with provided changes
	void UpdateRot(float dx, float dy, float dz);

	// will update coordinate vector with provided changes
	void UpdateCoord(float dx, float dy, float dz);

	// can set desired rotation vector
	void SetRot(float x, float y, float z) { rot.x = x; rot.y = y; rot.z = z; }

	// can set desired coordinate vector
	void SetCoord(float x, float y, float z); 

	// set desired scale vector
	void SetScale(float x, float y, float z);

	// choose if the object uses RGB15 colour or textures
	void SetColourMode(bool choice) { colour = choice; }

	// give object a geometry type to be used when drawing, e.g. QUAD vs TRIANGLE
	void SetGeometryType(GL_GLBEGIN_ENUM geoRenderType, Geometry geoType) { geometryRenderType = geoRenderType;  geometryType = geoType; }

	// bounding box needed to tell when object is offscreen 
	void CreateBoundingBox(float width, float height, float depth);

	bool LoadTexture(const u8 text[]);

	// getter functions for coordinate vector
	float GetCoordX() { return coord.x; }
	float GetCoordY() { return coord.y; }
	float GetCoordZ() { return coord.z; }

private:
	Vec3D coord; // coordinate vector
	Vec3D offset; // parent offset vector
	Vec3D rot; // rotation vector
	Vec3D scale; // scale vector
	Vec3D boundingBox; 
	bool colour; // if colour is being used or not
	Geometry geometryType; // used for knowing how many vertices make a face
	GL_GLBEGIN_ENUM geometryRenderType; // GL enum used for glBegin()
	std::vector<Vec3D> vertices; 
	std::vector<Vec3D> colours;
	sImage pcx;
	int textureID;
	std::vector<Vec3D> textureCoords;
	void ColourDraw();
	void TextureDraw();

};

#endif

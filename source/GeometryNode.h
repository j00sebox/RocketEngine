#ifndef GEONODE_H
#define GEONODE_H

#include "SceneNode.h"

class GeometryNode : public SceneNode
{
public:
	GeometryNode() { scale.x = 1.0f; scale.y = 1.0f; scale.z = 1.0f; }
	// optional constructor can set initial position
	GeometryNode(float x, float y, float z) { coord.x = x; coord.y = y; coord.z = z; rot.x = 0.0f; rot.y = 0.0f; rot.z = 0.0f; scale.x = 1.0f; scale.y = 1.0f; scale.z = 1.0f; }
	~GeometryNode() { }

	// native update function to handle all the transformations and drawing for this object
	void Update();

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

	// load given texture for this geometry
	bool LoadTexture(const u8 text[]);

	// getter functions for coordinate vector
	float GetCoordX() { return coord.x; }
	float GetCoordY() { return coord.y; }
	float GetCoordZ() { return coord.z; }

private:
	Vec3D origBB; // original bounding box for the geometry, reference point for when scale changes
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
#ifndef SCENENODE_H
#define SCENENODE_H

#include <nds.h>
#include <list>
#include <vector>
#include <stdio.h>

#define POLYGON_LIMIT 4000

extern int polygons;

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

class SceneNode
{
public:
	// constructor
	SceneNode() { }

	// destructor
	virtual ~SceneNode();

	// release this object from memory
	void Release() { delete this; }

	// update our scene node
	virtual void Update();

	void AddChild(SceneNode* pNode);

	Vec3D coord; // coordinate vector
	Vec3D rot; // rotation vector
	Vec3D scale; // scale vector

	// list of children
	std::list<SceneNode*> childList;
};


#endif

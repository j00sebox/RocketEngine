#include <nds.h>
#include <list>
#include <vector>

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

private:
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

class GeometryNode : public SceneNode
{
public:
	GeometryNode(float x, float y, float z) { coord.x = x; coord.y = y; coord.z = z; rot.x = 0.0f; rot.y = 0.0f; rot.z = 0.0f; }
	~GeometryNode() { }

	void Draw();

	void Update();

	void AddVertex(float x, float y, float z);

	void AddColour(float r, float g, float b);

	void UpdateRot(float dx, float dy, float dz);

private:
	Vec3D coord;
	Vec3D rot;
	std::vector<Vec3D> vertices;
	std::vector<Vec3D> colours;
	void Transform();

};


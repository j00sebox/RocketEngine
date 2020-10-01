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

struct Vertex {
	Vertex(float a = 0, float b = 0, float c = 0)
	{
		x = a; y = b; z = c;
	}

	float x, y, z;
};

class GeometryNode : public SceneNode
{
public:
	GeometryNode() { }
	~GeometryNode() { }


	void Update();

	void AddVertex(float x, float y, float z);

private:
	std::vector<Vertex> vertices;

};

class TransformNode : public SceneNode
{
public:
	TransformNode() { }
	~TransformNode() { }

	void SetMatrix(m4x4 m);

	void Update(void);

private:
	m4x4* matrix_transform;
};

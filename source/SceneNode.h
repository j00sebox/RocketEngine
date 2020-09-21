#include <nds.h>

class ScenceNode
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

class GeometryNode : public SceneNode
{
public:
	GeometryNode() { }
	~GeometryNode() { }

	void Update()
	{
		// Draw 

		SceneNode::Update();
	}
};

class TransformNode : public ScenceNode
{
public:
	TransformNode() { }
	TransformNode() { }

	void SetMatrix(float m[4][4]);

	void Update(void);

private:
	float matrix_transform[4][4];
};

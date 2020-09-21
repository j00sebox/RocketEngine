#include "SceneNode.h"

ScenceNode::AddChild(SceneNode* pNode)
{
	childList.push_back(pNode);
}

ScenceNode::Update()
{
	// loop through the list and update the children
	for (std::list<SceneNode*>::iterator i = childList.begin();
		i != childList.end(); i++)
	{
		(*i)->Update();
	}
}

void ScenceNode::Destroy()
{
	// loop through and delete children
	for (std::list<SceneNode*>::iterator i = childList.begin();
		i != childList.end(); i++)
		(*i)->Release();

	childList.clear();
}


TransformNode::SetMatrix(float m[4][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			matrix_transform[i][j] = m[i][j];
}

TransformNode::Update()
{
	// save current transform
	glPushMatrix();

	// load the transform assigned to this node
	glLoadMatrix((float*)matrix_transform);

	// Update Nodes that use this transform
	SceneNode::Update();

	// recover the initial matrix transform
	glPopMatrix();
}
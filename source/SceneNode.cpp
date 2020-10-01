#include "SceneNode.h"

void SceneNode::AddChild(SceneNode* pNode)
{
	childList.push_back(pNode);
}

void SceneNode::Update()
{
	// loop through the list and update the children
	for (std::list<SceneNode*>::iterator i = childList.begin();
		i != childList.end(); i++)
	{
		(*i)->Update();
	}
}

void SceneNode::Destroy()
{
	// loop through and delete children
	for (std::list<SceneNode*>::iterator i = childList.begin();
		i != childList.end(); i++)
		(*i)->Release();

	childList.clear();
}

void GeometryNode::Update()
{
	// Draw 
	glBegin(GL_QUADS);
	for (int i = 0; i < (int)vertices.size(); i++)
	{
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();

	SceneNode::Update();
}

void GeometryNode::AddVertex(float x, float y, float z)
{
	vertices.push_back(Vertex(x, y, z));
}

void TransformNode::SetMatrix(m4x4 m)
{
	*matrix_transform = m;
}

void TransformNode::Update()
{
	// save current transform
	glPushMatrix();

	// load the transform assigned to this node
	glLoadMatrix4x4(matrix_transform);

	// Update Nodes that use this transform
	SceneNode::Update();

	// recover the initial matrix transform
	glPopMatrix(0);
}
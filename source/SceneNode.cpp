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

void GeometryNode::Draw()
{
	// Draw 
	glBegin(GL_QUADS);

	int c = 0;

	for (int i = 0; i < (int)vertices.size(); i++)
	{
		if (i % 4 == 0) {
			glColor3f(colours[c].x, colours[c].y, colours[c].z);
			c++;
		}
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();

}

void GeometryNode::Update()
{

	glPushMatrix();

	glLoadIdentity();

	glTranslatef(coord.x, coord.y, coord.z);

	glRotateX(rot.x);
	glRotateY(rot.y);
	glRotateZ(rot.x);

	Draw();

	// recover the initial matrix transform
	glPopMatrix(0);

	SceneNode::Update();
}

void GeometryNode::AddVertex(float x, float y, float z)
{
	vertices.push_back(Vec3D(x, y, z));
}

void GeometryNode::AddColour(float r, float g, float b)
{
	colours.push_back(Vec3D(r, g, b));
}

void GeometryNode::UpdateRot(float dx, float dy, float dz)
{
	rot.x += dx;
	rot.y += dy;
	rot.z += dz;
}
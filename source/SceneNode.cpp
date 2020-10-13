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

void CameraNode::UpdateCameraPos(float dx, float dy, float dz)
{
	eye.x += dx; eye.y += dy; eye.z += dz;
}

void CameraNode::UpdateCameraLook(float dx, float dy, float dz)
{
	lookAt.x += dx; lookAt.y += dy; lookAt.z += dz;
}

void CameraNode::SetCameraPos(float x, float y, float z)
{
	eye.x = x; eye.y = y; eye.z = z;
}

void CameraNode::SetCameraPosY(float y)
{
	eye.y = y;
}

void CameraNode::SetCameraLook(float x, float y, float z)
{
	lookAt.x = x; lookAt.y = y; lookAt.z = z;
}

void CameraNode::SetCameraLookX(float x)
{
	lookAt.x = x;
}

void CameraNode::SetCameraLookY(float y)
{
	lookAt.y = y;
}

void CameraNode::SetCameraLookZ(float z)
{
	lookAt.z = z;
}

void CameraNode::Update()
{
	glPushMatrix();

	glLoadIdentity();

	gluLookAt(eye.x, eye.y, eye.z, lookAt.x, lookAt.y, lookAt.z, 0.0f, 1.0f, 0.0f);

	SceneNode::Update();

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

	glPopMatrix(0);

	glTranslatef((coord.x + offset.x), (coord.y + offset.y), (coord.z + offset.z));

	glRotateX(rot.x);
	glRotateY(rot.y);
	glRotateZ(rot.x);

	int test = BoxTestf(vertices[0].x, vertices[0].y, vertices[0].z, boundingBox.x, boundingBox.y, boundingBox.z);

	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0 | POLY_FORMAT_LIGHT1 | POLY_FORMAT_LIGHT2);

	if (test != 0)
	{

		Draw();

		SceneNode::Update();
	}

	// recover the initial matrix transform
	glPopMatrix(0);
	
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

void GeometryNode::CreateBoundingBox(float width, float height, float depth)
{
	boundingBox.x = width; boundingBox.y = height; boundingBox.z = depth;
}

#include "CameraNode.h"

void CameraNode::UpdateCameraPos(float dx, float dy, float dz)
{
	coord.x += dx; coord.y += dy; coord.z += dz;
}

void CameraNode::UpdateCameraLook(float dx, float dy, float dz)
{
	rot.x += dx; rot.y += dy; rot.z += dz;
}

void CameraNode::SetCameraPos(float x, float y, float z)
{
	coord.x = x; coord.y = y; coord.z = z;
}

void CameraNode::SetCameraPosY(float y)
{
	coord.y = y;
}

void CameraNode::SetCameraLook(float x, float y, float z)
{
	rot.x = x; rot.y = y; rot.z = z;
}

void CameraNode::SetCameraLookX(float x)
{
	rot.x = x;
}

void CameraNode::SetCameraLookY(float y)
{
	rot.y = y;
}

void CameraNode::SetCameraLookZ(float z)
{
	rot.z = z;
}

void CameraNode::Update()
{
	// push current matrix to stack
	glPushMatrix();

	polygons = 0;

	// camera nodes need specialized update in order to set the camera properly
	for (std::list<SceneNode*>::iterator i = childList.begin();
		i != childList.end(); i++)
	{
		glLoadIdentity();

		gluLookAt(coord.x, coord.y, coord.z, rot.x, rot.y, rot.z, 0.0f, 1.0f, 0.0f);

		(*i)->Update();
	}

	// recover initial matrix
	glPopMatrix(0);

}

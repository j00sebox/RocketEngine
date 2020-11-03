
#include "CameraNode.h"

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
	// push current matrix to stack
	glPushMatrix();

	polygons = 0;

	// camera nodes need specialized update in order to set the camera properly
	for (std::list<SceneNode*>::iterator i = childList.begin();
		i != childList.end(); i++)
	{
		glLoadIdentity();

		gluLookAt(eye.x, eye.y, eye.z, lookAt.x, lookAt.y, lookAt.z, 0.0f, 1.0f, 0.0f);

		(*i)->Update();
	}

	// recover initial matrix
	glPopMatrix(0);

}

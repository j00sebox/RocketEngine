#ifndef CAMNODE_H
#define CAMNODE_H

#include "SceneNode.h"

class CameraNode : public SceneNode
{
public:
	CameraNode() { }
	~CameraNode() { }

	// update camera position
	void UpdateCameraPos(float dx, float dy, float dz);

	// update where camera is looking at
	void UpdateCameraLook(float dx, float dy, float dz);

	void SetCameraPos(float x, float y, float z);

	void SetCameraPosY(float y);

	void SetCameraLook(float x, float y, float z);

	void SetCameraLookX(float x);

	void SetCameraLookY(float y);

	void SetCameraLookZ(float z);

	float GetPosX() { return coord.x; }
	float GetPosY() { return coord.y; }
	float GetPosZ() { return coord.z; }

	void Update();
};

#endif

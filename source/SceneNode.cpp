#include "SceneNode.h"

int polygons;

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
	// push current matrix to stack
	glPushMatrix();

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

void GeometryNode::Draw()
{
		// Draw 
		glBegin(geometryRenderType);

		int c = 0;

		for (int i = 0; i < (int)vertices.size(); i++)
		{
			if (i % geometryType == 0) {
				glColor3f(colours[c].x, colours[c].y, colours[c].z);
				c++;
			}
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}

		glEnd();
}

void GeometryNode::Update()
{
	// get amount of polygons currently on screen
	glGetInt(GL_GET_POLYGON_RAM_COUNT, &polygons);

	// if polygons are below the limit then object can be drawn
	if (polygons <= POLYGON_LIMIT)
	{
		glTranslatef((coord.x + offset.x), (coord.y + offset.y), (coord.z + offset.z));

		glRotateX(rot.x);
		glRotateY(rot.y);
		glRotateZ(rot.x);

		// check if the object is in view of the frustrum, if not don't draw
		int test = BoxTestf(vertices[0].x, vertices[0].y, vertices[0].z, boundingBox.x, boundingBox.y, boundingBox.z);

		// bug with box test these values need to be set again after calling
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0 | POLY_FORMAT_LIGHT1 | POLY_FORMAT_LIGHT2);

		// check if test passes
		if (test != 0)
		{
			// draw this node's geometry
			Draw();

			// update children if any
			SceneNode::Update();
		}
	}
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

void GeometryNode::UpdateCoord(float dx, float dy, float dz)
{
	coord.x += dx;
	coord.y += dy;
	coord.z += dz;
}

void GeometryNode::SetCoord(float x, float y, float z)
{
	coord.x = x; 
	coord.y = y; 
	coord.z = z; 
}

void GeometryNode::CreateBoundingBox(float width, float height, float depth)
{
	boundingBox.x = width; boundingBox.y = height; boundingBox.z = depth;
}
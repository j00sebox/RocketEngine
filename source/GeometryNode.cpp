
#include "GeometryNode.h"


void GeometryNode::ColourDraw()
{
	// Draw 
	glBegin(geometryRenderType);


	int c = 0;

	for (int i = 0; i < (int)vertices.size(); i++)
	{
		// this controls when colour is added
		// once a face of the object is made then colour is added
		if (i % geometryType == 0) {
			glNormal3f(0.0f, 0.0f, 1.0f); // add normal to interact with the lighting
			glColor3f(colours[c].x, colours[c].y, colours[c].z);
			c++;
			polygons++;
		}
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}

	glEnd();
}

void GeometryNode::TextureDraw()
{
	// set current texture as one binded to node's id
	glBindTexture(0, textureID);

	// Draw 
	glBegin(geometryRenderType);

	for (int i = 0; i < (int)vertices.size(); i++)
	{
		if (i % geometryType == 0) {
			glNormal3f(0.0f, 0.0f, 1.0f); // add normal to interact with the lighting
			polygons++;
		}
		// this version need a texture coord for every vertex
		glTexCoord2f(textureCoords[i].x, textureCoords[i].y);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);

	}

	glEnd();

	// clear current texture
	glBindTexture(0, 0);
}

void GeometryNode::Update()
{
	// if polygons are below the limit then object can be drawn
	if (polygons <= POLYGON_LIMIT)
	{
		glTranslatef((coord.x + offset.x), (coord.y + offset.y), (coord.z + offset.z));

		glRotateX(rot.x);
		glRotateY(rot.y);
		glRotateZ(rot.x);

		glScalef(scale.x, scale.y, scale.z);

		// check if the object is in view of the frustrum, if not don't draw
		int test = BoxTestf(vertices[0].x, vertices[0].y, vertices[0].z, boundingBox.x, boundingBox.y, boundingBox.z);

		// bug with box test these values need to be set again after calling
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0 | POLY_FORMAT_LIGHT1 | POLY_FORMAT_LIGHT2);

		// check if test passes
		if (test != 0)
		{
			// draw this node's geometry
			if (colour)
				ColourDraw();
			else
				TextureDraw();

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

void GeometryNode::AddTextCoord(float x, float y)
{
	textureCoords.push_back(Vec3D(x, y));
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

void GeometryNode::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void GeometryNode::CreateBoundingBox(float width, float height, float depth)
{
	boundingBox.x = width; boundingBox.y = height; boundingBox.z = depth;
}

bool GeometryNode::LoadTexture(const u8 text[])
{
	//load our texture
	loadPCX((u8*)text, &pcx);

	image8to16(&pcx);

	// generate name for texture (id) and store it 
	glGenTextures(1, &textureID);

	// image data is binded to the id
	glBindTexture(0, textureID);
	glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_128, TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, pcx.image.data8);

	glBindTexture(0, 0);

	return true;
}
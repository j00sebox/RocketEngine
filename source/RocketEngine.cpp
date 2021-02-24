#include "RocketEngine.h"

// trig functions that use degrees instead of radians
// also don't need to include math.h
float sin(float angle)
{
	int32 s = sinLerp((short)(angle * DEGREES_IN_CIRCLE / 360));

	return f32tofloat(s);
}

float cos(float angle)
{
	int32 c = cosLerp((short)(angle * DEGREES_IN_CIRCLE / 360));

	return f32tofloat(c);
}

void RocketEngine::init()
{
	// Setup the Main screen for 3D 
	videoSetMode(MODE_0_3D);

	// set BankA so it can do textures
	vramSetBankA(VRAM_A_TEXTURE);      

	// sets up bottom screen
	consoleDemoInit();

	// initialize the geometry engine
	glInit();

	// enable textures
	glEnable(GL_TEXTURE_2D);

	// enable antialiasing
	glEnable(GL_ANTIALIAS);

	// setup the rear plane
	glClearColor(0, 0, 0, 31); // BG must be opaque for AA to work
	glClearPolyID(63); // BG must have a unique polygon ID for AA to work
	glClearDepth(0x7FFF);

	// Set our viewport to be the same size as the screen
	glViewport(0, 0, 255, 191);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 256.0 / 192.0, 0.1, 100);

	// Set the current matrix to be the model matrix
	glMatrixMode(GL_MODELVIEW);

	//need to set up some material properties since DS does not have them set by default
	glMaterialf(GL_AMBIENT, RGB15(16, 16, 16));
	glMaterialf(GL_DIFFUSE, RGB15(16, 16, 16));
	glMaterialf(GL_SPECULAR, BIT(15) | RGB15(8, 8, 8));
	glMaterialf(GL_EMISSION, RGB15(16, 16, 16));

	//ds uses a table for shinyness..this generates a half-ass one
	glMaterialShinyness();

	//ds specific, several attributes can be set here       
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0 | POLY_FORMAT_LIGHT1 | POLY_FORMAT_LIGHT2);

	glLight(0, RGB15(31, 31, 31), 0, floattov10(-1.0), 0);
	
	// add camera to scene graph
	root.AddChild(&fpCam);

	// set initial position for camera
	fpCam.SetCameraPos(0.0f, 1.0f, -10.0f);

	printf("CONTROLS:\n");
	printf("D-Pad Up: Move Forwards\n");
	printf("D-Pad Down: Move Backwards\n");
	printf("D-Pad Right: Turn Right\n");
	printf("D-Pad Left: Turn Left\n");
	printf("A: Look Up\n");
	printf("B: Look Down\n");
}

void RocketEngine::Run()
{
	// look what keys are being pressed
	scanKeys();

	int held = keysHeld();

	// check what keys are being pressed
	// left and right keys are responsible for changing the yaw
	if (held & KEY_LEFT)
	{
		lookAngle -= 3.0f;
	}
	if (held & KEY_RIGHT)
	{
		lookAngle += 3.0f;
	}
	// up and down keys change the cameras position
	if (held & KEY_UP)
	{
		posx = (float)cos(lookAngle) * 0.05f;
		posz = (float)sin(lookAngle) * 0.05f;

		if (walkbiasangle >= 359.0f)
		{
			walkbiasangle = 0.0f;
		}
		else
		{
			walkbiasangle += 10;
		}

		walkbias = (float)sin(walkbiasangle) / 20.0f;
	}
	if (held & KEY_DOWN)
	{
		posx = -(float)cos(lookAngle) * 0.05f;
		posz = -(float)sin(lookAngle) * 0.05f;

		if (walkbiasangle <= 1.0f)
		{
			walkbiasangle = 359.0f;
		}
		else
		{
			walkbiasangle -= 10;
		}
		walkbias = (float)sin(walkbiasangle) / 20.0f;
	}
	// a & b keys change the y value the camera is looking at
	if (held & KEY_A)
	{
		camy += 0.1f;
	}
	if (held & KEY_B)
	{
		camy -= 0.1f;
	}

	// redraw all objects in scene
	Render();

	// flush to screen      
	glFlush(0);

	// wait for the screen to refresh
	swiWaitForVBlank();

	// camera bobs up and down to give the appearence of normal walking
	fpCam.SetCameraPosY(walkbias - 0.25f);

	// update where camera origin is
	fpCam.UpdateCameraPos(posx, 0.0f, posz);

	// set where camera should be looking now based on it's position and lookangle
	fpCam.SetCameraLook(fpCam.GetPosX() + cos(lookAngle), camy, fpCam.GetPosZ() + sin(lookAngle));

	iprintf("\x1b[10;0HPolygons = %i", polygons);

	posx = 0.0f; posz = 0.0f;
}

// render only needs to call the root's update function to kick off 
// the scene graph update
void RocketEngine::Render()
{
	root.Update();
}

void RocketEngine::CreateObject(GeometryNode* newObj, GeometryNode* parent, GL_GLBEGIN_ENUM geoRenderType, Geometry geoType, Vec3D vertices[], int size, Vec3D boundingBox, bool col)
{
	// add it to scenegraph
	if (parent == NULL)
		fpCam.AddChild(&(*newObj));
	else
		parent->AddChild(&(*newObj));

	// set kind of geometry
	newObj->SetGeometryType(geoRenderType, geoType);

	newObj->SetColourMode(col);
	
	for (int i = 0; i < size; i++)
	{
		newObj->AddVertex(vertices[i].x, vertices[i].y, vertices[i].z);
	}

	newObj->CreateBoundingBox(boundingBox.x, boundingBox.y, boundingBox.z);
}

void RocketEngine::AddCubeToScene(GeometryNode* newCube, bool col)
{
	Vec3D vertexC(-1.0f, -1.0f, -1.0f);
	Vec3D bbC(2.0f, 2.0f, 2.0f);

	int width = bbC.x;
	int height = bbC.y;
	int depth = bbC.z;

	fpCam.AddChild(&(*newCube));

	newCube->SetColourMode(col);

	newCube->AddVertex(vertexC.x, vertexC.y, vertexC.z);
	newCube->AddVertex(vertexC.x + width, vertexC.y, vertexC.z);
	newCube->AddVertex(vertexC.x + width, vertexC.y + height, vertexC.z);
	newCube->AddVertex(vertexC.x, vertexC.y + height, vertexC.z);

	//z + depth face
	newCube->AddVertex(vertexC.x, vertexC.y, vertexC.z + depth);
	newCube->AddVertex(vertexC.x, vertexC.y + height, vertexC.z + depth);
	newCube->AddVertex(vertexC.x + width, vertexC.y + height, vertexC.z + depth);
	newCube->AddVertex(vertexC.x + width, vertexC.y, vertexC.z + depth);

	//x  face
	newCube->AddVertex(vertexC.x, vertexC.y, vertexC.z);
	newCube->AddVertex(vertexC.x, vertexC.y + height, vertexC.z);
	newCube->AddVertex(vertexC.x, vertexC.y + height, vertexC.z + depth);
	newCube->AddVertex(vertexC.x, vertexC.y, vertexC.z + depth);

	//x + width face
	newCube->AddVertex(vertexC.x + width, vertexC.y, vertexC.z);
	newCube->AddVertex(vertexC.x + width, vertexC.y, vertexC.z + depth);
	newCube->AddVertex(vertexC.x + width, vertexC.y + height, vertexC.z + depth);
	newCube->AddVertex(vertexC.x + width, vertexC.y + height, vertexC.z);

	//y  face
	newCube->AddVertex(vertexC.x, vertexC.y, vertexC.z);
	newCube->AddVertex(vertexC.x, vertexC.y, vertexC.z + depth);
	newCube->AddVertex(vertexC.x + width, vertexC.y, vertexC.z + depth);
	newCube->AddVertex(vertexC.x + width, vertexC.y, vertexC.z);

	//y  + height face
	newCube->AddVertex(vertexC.x, vertexC.y + height, vertexC.z);
	newCube->AddVertex(vertexC.x + width, vertexC.y + height, vertexC.z);
	newCube->AddVertex(vertexC.x + width, vertexC.y + height, vertexC.z + depth);
	newCube->AddVertex(vertexC.x, vertexC.y + height, vertexC.z + depth);

	newCube->SetGeometryType(GL_QUADS, QUAD);

	newCube->CreateBoundingBox(bbC.x, bbC.y, bbC.z);
}

void RocketEngine::AddQuadToScene(GeometryNode* newQuad, bool col)
{
	fpCam.AddChild(&(*newQuad));

	newQuad->SetColourMode(col);

	newQuad->AddVertex(1.0f, 0.0f, 1.0f);
	newQuad->AddVertex(-1.0f, 0.0f, 1.0f);
	newQuad->AddVertex(-1.0f, 0.0f, -1.0f);
	newQuad->AddVertex(1.0f, 0.0f, -1.0f);

	newQuad->SetGeometryType(GL_QUADS, QUAD);

	newQuad->CreateBoundingBox(2.0f, 0.0f, 2.0f);

}

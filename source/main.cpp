#include <stdio.h>
#include "SceneNode.h"
#include <malloc.h>
//needed to load pcx files
#include <nds/arm9/image.h>

//#include "drunkenlogo_pcx.h"

void init();
void Render();

float posx = 0.0f;
float posz = 0.0f;

float walkbias = 0;
float walkbiasangle = 0;
float camy = 0.0f;
float lookAngle = 0.0f;
std::vector<SceneNode*> scene;

SceneNode root;

int     texture[1];                     // Storage For One Texture

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

void GetCurrentMatrix(m4x4* curr)
{
	glGetFixed(GL_GET_MATRIX_POSITION, curr->m);
}

//int LoadGLTextures()                                                                    
//{
//	sImage pcx;
//
//	//load our texture
//	loadPCX((u8*)drunkenlogo_pcx, &pcx);
//
//	image8to16(&pcx);
//
//	glGenTextures(1, &texture[0]);
//	glBindTexture(0, texture[0]);
//	glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_128, TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, pcx.image.data8);
//
//	imageDestroy(&pcx);
//
//	return TRUE;
//}

int main() {

	init();

	CameraNode fpCam;

	GeometryNode floor(0.0f, 0.0f, -5.0f);

	GeometryNode cube(0.0f, 0.0f, -5.0f);

	root.AddChild(&fpCam);
	root.AddChild(&cube);
	root.AddChild(&floor);

	fpCam.SetCameraPos(0.0f, 1.0f, -10.0f);

	// Reset The View
	glLoadIdentity();  
                                                                     
	// Create floor
	floor.AddColour(1.0f, 1.0f, 1.0f);
	floor.AddVertex(-150.0, -3.0, -150.0); 
	floor.AddVertex(150.0, -3.0, -150.0); 
	floor.AddVertex(150.0, -3.0, 150.0); 
	floor.AddVertex(-150.0, -3.0, 150.0); 

	/*****************Cube********************/

	// Front Face
	cube.AddColour(1.0f, 0.0f, 0.0f);
	cube.AddVertex(-1.0f, -1.0f, 1.0f); 
	cube.AddVertex(1.0f, -1.0f, 1.0f); 
	cube.AddVertex(1.0f, 1.0f, 1.0f); 
	cube.AddVertex(-1.0f, 1.0f, 1.0f); 

	// Back Face
	cube.AddColour(0.0f, 1.0f, 1.0f);
	cube.AddVertex(-1.0f, -1.0f, -1.0f); 
	cube.AddVertex(-1.0f, 1.0f, -1.0f); 
	cube.AddVertex(1.0f, 1.0f, -1.0f); 
	cube.AddVertex(1.0f, -1.0f, -1.0f); 

	// Top Face
	cube.AddColour(1.0f, 0.0f, 1.0f);
	cube.AddVertex(-1.0f, 1.0f, -1.0f); 
	cube.AddVertex(-1.0f, 1.0f, 1.0f); 
	cube.AddVertex(1.0f, 1.0f, 1.0f); 
	cube.AddVertex(1.0f, 1.0f, -1.0f); 

	// Bottom Face
	cube.AddColour(0.75f, 0.0f, 1.0f);
	cube.AddVertex(-1.0f, -1.0f, -1.0f); 
	cube.AddVertex(1.0f, -1.0f, -1.0f); 
	cube.AddVertex(1.0f, -1.0f, 1.0f); 
	cube.AddVertex(-1.0f, -1.0f, 1.0f); 

	// Right face
	cube.AddColour(1.0f, 1.0f, 0.0f);
	cube.AddVertex(1.0f, -1.0f, -1.0f); 
	cube.AddVertex(1.0f, 1.0f, -1.0f); 
	cube.AddVertex(1.0f, 1.0f, 1.0f); 
	cube.AddVertex(1.0f, -1.0f, 1.0f); 

	// Left Face
	cube.AddColour(1.0f, 0.5f, 0.0f);
	cube.AddVertex(-1.0f, -1.0f, -1.0f); 
	cube.AddVertex(-1.0f, -1.0f, 1.0f); 
	cube.AddVertex(-1.0f, 1.0f, 1.0f); 
	cube.AddVertex(-1.0f, 1.0f, -1.0f); 

	/*****************************************/


	while (1)
	{
		scanKeys();

		int held = keysHeld();

		if (held & KEY_LEFT)
		{
			lookAngle += 0.5f;
			camy = lookAngle;
		}
		if (held & KEY_RIGHT)
		{
			lookAngle -= 0.5f;
			camy = lookAngle;

		}
		if (held & KEY_UP)
		{
			posx = (float)sin(lookAngle) * 0.05f;
			posz = (float)cos(lookAngle) * 0.05f;

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
			posx = -(float)sin(lookAngle) * 0.05f;
			posz = -(float)cos(lookAngle) * 0.05f;

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

		Render();

		// flush to screen      
		glFlush(0);

		// wait for the screen to refresh
		swiWaitForVBlank();

		fpCam.SetCameraPosY(walkbias - 0.25f);

		fpCam.UpdateCameraPos(posx, 0.0f, posz);

		fpCam.SetCameraLookX(camy);

		cube.UpdateRot(0.3, 0.1, 0.4);

		posx = 0.0f; posz = 0.0f;
	}

	return 0;
}

// initialize generic settings for now
void init()
{
	// Setup the Main screen for 3D 
	videoSetMode(MODE_0_3D);
	//vramSetBankA(VRAM_A_TEXTURE);                        //NEW  must set up some memory for textures

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

	//LoadGLTextures();

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
	glLight(1, RGB15(31, 31, 31), 0, 0, floattov10(-1.0));
	glLight(2, RGB15(31, 31, 31), 0, 0, floattov10(1.0));
}

void Render()
{
	root.Update();
}

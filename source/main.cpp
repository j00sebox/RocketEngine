#include <stdio.h>
#include "SceneNode.h"
#include <malloc.h>
//needed to load pcx files
#include <nds/arm9/image.h>

#include "drunkenlogo_pcx.h"

int DrawGLScene();
void init();
void ChangeScene();

float   xrot;                           // X Rotation
float   yrot;                           // Y Rotation 
float   zrot;                           // Z Rotation 

int     texture[1];                     // Storage For One Texture

int LoadGLTextures()                                                                    
{
	sImage pcx;

	//load our texture
	loadPCX((u8*)drunkenlogo_pcx, &pcx);

	image8to16(&pcx);

	glGenTextures(1, &texture[0]);
	glBindTexture(0, texture[0]);
	glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_128, TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, pcx.image.data8);

	imageDestroy(&pcx);

	return TRUE;
}

int main() {

	init();

	SceneNode root;

	TransformNode firstTransform;
	GeometryNode cube;

	root.AddChild(&firstTransform);
	firstTransform.AddChild(&cube);

	glLoadIdentity();                                                                       // Reset The View

	glTranslatef(0.0f, 0.0f, -5.0f);

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

	m4x4 t;
	m4x4* pos = &t;

	glGetFixed(GL_GET_MATRIX_POSITION, pos->m);

	firstTransform.SetMatrix(*pos);

	glMatrixMode(GL_MODELVIEW);

	// Front Face
	cube.AddVertex(-1.0f, -1.0f, 1.0f);
	cube.AddVertex(1.0f, -1.0f, 1.0f);
	cube.AddVertex(1.0f, 1.0f, 1.0f);
	cube.AddVertex(-1.0f, 1.0f, 1.0f);
	// Back Face
	cube.AddVertex(-1.0f, -1.0f, -1.0f);
	cube.AddVertex(-1.0f, 1.0f, -1.0f);
	cube.AddVertex(1.0f, 1.0f, -1.0f);
	cube.AddVertex(1.0f, -1.0f, -1.0f);
	// Top Face
	cube.AddVertex(-1.0f, 1.0f, -1.0f);
	cube.AddVertex(-1.0f, 1.0f, 1.0f);
	cube.AddVertex(1.0f, 1.0f, 1.0f);
	cube.AddVertex(1.0f, 1.0f, -1.0f);
	// Bottom Face
	cube.AddVertex(-1.0f, -1.0f, -1.0f);
	cube.AddVertex(1.0f, -1.0f, -1.0f);
	cube.AddVertex(1.0f, -1.0f, 1.0f);
	cube.AddVertex(-1.0f, -1.0f, 1.0f);
	// Right face
	cube.AddVertex(1.0f, -1.0f, -1.0f);
	cube.AddVertex(1.0f, 1.0f, -1.0f);
	cube.AddVertex(1.0f, 1.0f, 1.0f);
	cube.AddVertex(1.0f, -1.0f, 1.0f);
	// Left Face
	cube.AddVertex(-1.0f, -1.0f, -1.0f);
	cube.AddVertex(-1.0f, -1.0f, 1.0f);
	cube.AddVertex(-1.0f, 1.0f, 1.0f);
	cube.AddVertex(-1.0f, 1.0f, -1.0f);


	while (1)
	{
		// set the color of the vertices to be drawn
		glColor3f(1, 1, 1);

		//DrawGLScene();

		glLoadIdentity();                                                                       // Reset The View

		glTranslatef(0.0f, 0.0f, -5.0f);

		glRotatef(xrot, 1.0f, 0.0f, 0.0f);
		glRotatef(yrot, 0.0f, 1.0f, 0.0f);
		glRotatef(zrot, 0.0f, 0.0f, 1.0f);

		glGetFixed(GL_GET_MATRIX_POSITION, pos->m);

		firstTransform.SetMatrix(*pos);

		glMatrixMode(GL_MODELVIEW);

		root.Update();

		// flush to screen      
		glFlush(0);

		// wait for the screen to refresh
		swiWaitForVBlank();

		xrot += 0.3f;
		yrot += 0.2f;
		zrot += 0.4f;
	}

	return 0;
}

// initialize generic settings for now
void init()
{
	// Setup the Main screen for 3D 
	videoSetMode(MODE_0_3D);
	vramSetBankA(VRAM_A_TEXTURE);                        //NEW  must set up some memory for textures

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

	LoadGLTextures();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 256.0 / 192.0, 0.1, 100);

	glLight(0, RGB15(31, 31, 31), 0, floattov10(-1.0), 0);

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

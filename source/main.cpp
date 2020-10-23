
#include "RocketEngine.h"
#include <malloc.h>
//#include <math.h> 
//needed to load pcx files
#include <nds/arm9/image.h>

//#include "drunkenlogo_pcx.h"



//void LoadOBJFile(std::string fname, GeometryNode* node)
//{
//	std::ifstream readFile;
//	readFile.open(fname);
//
//	if (!readFile.is_open())
//	{
//		std::cout << "Cannot open file!";
//	}
//
//	Vec3D vertex;
//	std::vector<Vec3D> vertices;
//
//	std::string line;
//
//	char startingChar; // Stores the starting character of the line
//
//	int i1, i2, i3; // indexes of the vertices
//
//	// iterate through all lines in file
//	while (std::getline(readFile, line))
//	{
//		std::strstream st;
//		st << line;
//
//		// indicates vertex data
//		if (line[0] == 'v')
//		{
//			st >> startingChar >> vertex.x >> vertex.y >> vertex.z;
//			node->AddVertex(vertex.x, vertex.y, vertex.z);
//		}
//		// indicates traingle face data
//		else if (line[0] == 'f')
//		{
//			/*st >> startingChar >> i1 >> i2 >> i3;
//			node->AddVertex(vertices[i1 - 1], vertices[i2 - 1], vertices[i3 - 1]);*/
//		}
//	}
//
//}

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

	RocketEngine re;

	// initialize generic settings for openGl
	re.init();

	//GeometryNode floor(0.0f, 0.0f, -5.0f);

	/*****************Cube********************/

	GeometryNode cube(0.0f, 3.0f, -5.0f);
	Vec3D vertex(-1.0f, -1.0f, -1.0f);
	Vec3D bb(2.0f, 2.0f, 2.0f);
	re.CreateObject(&cube, GL_QUADS, QUAD, &vertex, bb);

	// Front Face
	cube.AddColour(1.0f, 0.0f, 0.0f);

	// Back Face
	cube.AddColour(0.0f, 1.0f, 1.0f);

	// Top Face
	cube.AddColour(1.0f, 0.0f, 1.0f);

	// Bottom Face
	cube.AddColour(0.75f, 0.0f, 1.0f);

	// Right face
	cube.AddColour(1.0f, 1.0f, 0.0f);

	// Left Face
	cube.AddColour(1.0f, 0.5f, 0.0f);

	/*****************************************/

	//GeometryNode py1;

	//py1.Offset(1.0f, 0.0f, 0.0f);

	//py1.SetRot(90.0f, 0.0f, 0.0f);

	////GeometryNode teapot(0.0f, 5.0f, -5.0f);

	//// create scene graph

	//
	////fpCam.AddChild(&teapot); 

	//floor.SetGeometryType(GL_QUADS, QUAD);
 //                                                                    
	//// Create floor
	//floor.AddColour(1.0f, 1.0f, 1.0f);
	//floor.AddVertex(-300.0, -3.0, -300.0);
	//floor.AddVertex(300.0, -3.0, -300.0);
	//floor.AddVertex(300.0, -3.0, 300.0);
	//floor.AddVertex(-300.0, -3.0, 300.0);

	//floor.CreateBoundingBox(600.0f, 0.0f, 600.0f);

	///*****************Pyramid********************/

	//py1.SetGeometryType(GL_TRIANGLES, TRIANGLE);

	//py1.AddColour(1.0f, 0.0f, 1.0f);     // Red
	//py1.AddVertex(0.0f, 1.0f, 0.0f);    // Green
	//py1.AddVertex(1.0f, 2.0f, 1.0f);    // Blue
	//py1.AddVertex(1.0f, 2.0f, -1.0f);

	//py1.AddColour(0.0f, 1.0f, 0.0f);     // Red
	//py1.AddVertex(0.0f, 1.0f, 0.0f);    // Blue
	//py1.AddVertex(1.0f, 0.0f, 1.0f);    // Green
	//py1.AddVertex(1.0f, 0.0f, -1.0f);

	//py1.AddColour(0.0f, 0.0f, 1.0f);     // Red
	//py1.AddVertex(0.0f, 1.0f, 0.0f);    // Blue
	//py1.AddVertex(1.0f, 0.0f, 1.0f);     // Green
	//py1.AddVertex(1.0f, 2.0f, 1.0f);

	//py1.AddColour(0.0f, 1.0f, 1.0f);     // Red
	//py1.AddVertex(0.0f, 1.0f, 0.0f);    // Blue
	//py1.AddVertex(1.0f, 2.0f, -1.0f);    // Green
	//py1.AddVertex(1.0f, 0.0f, -1.0f);

	//py1.CreateBoundingBox(2.0f, 2.0f, 2.0f);

	/*teapot.SetGeometryType(GL_TRIANGLES, TRIANGLE);

	LoadOBJFile("teapot.obj", &teapot);

	teapot.CreateBoundingBox(2.0f, 2.0f, 2.0f);*/


	while (1)
	{
		re.Run();

		cube.UpdateRot(0.3, 0.1, 0.4);
	}

	return 0;
}


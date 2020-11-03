
#include "RocketEngine.h"

// textures
#include "Mud_pcx.h"
#include "drunkenlogo_pcx.h"

int main() {

	/*******DEMO*******/

	// instance of the engine
	RocketEngine re;

	// initialize generic settings for openGl
	re.init();

	/*****************Cube********************/

	GeometryNode cube(0.0f, 3.0f, -5.0f);
	Vec3D vertexC(-1.0f, -1.0f, -1.0f);
	Vec3D bbC(2.0f, 2.0f, 2.0f);
	
	int width = bbC.x;
	int height = bbC.y;
	int depth = bbC.z;

	Vec3D verticiesCube[24] = {
		//z  face
		Vec3D(vertexC.x, vertexC.y, vertexC.z),
		Vec3D(vertexC.x + width, vertexC.y, vertexC.z),
		Vec3D(vertexC.x + width, vertexC.y + height, vertexC.z),
		Vec3D(vertexC.x, vertexC.y + height, vertexC.z),

		//z + depth face
		Vec3D(vertexC.x, vertexC.y, vertexC.z + depth),
		Vec3D(vertexC.x, vertexC.y + height, vertexC.z + depth),
		Vec3D(vertexC.x + width, vertexC.y + height, vertexC.z + depth),
		Vec3D(vertexC.x + width, vertexC.y, vertexC.z + depth),

		//x  face
		Vec3D(vertexC.x, vertexC.y, vertexC.z),
		Vec3D(vertexC.x, vertexC.y + height, vertexC.z),
		Vec3D(vertexC.x, vertexC.y + height, vertexC.z + depth),
		Vec3D(vertexC.x, vertexC.y, vertexC.z + depth),

		//x + width face
		Vec3D(vertexC.x + width, vertexC.y, vertexC.z),
		Vec3D(vertexC.x + width, vertexC.y, vertexC.z + depth),
		Vec3D(vertexC.x + width, vertexC.y + height, vertexC.z + depth),
		Vec3D(vertexC.x + width, vertexC.y + height, vertexC.z),

		//y  face
		Vec3D(vertexC.x, vertexC.y, vertexC.z),
		Vec3D(vertexC.x, vertexC.y, vertexC.z + depth),
		Vec3D(vertexC.x + width, vertexC.y, vertexC.z + depth),
		Vec3D(vertexC.x + width, vertexC.y, vertexC.z),

		//y  + height face
		Vec3D(vertexC.x, vertexC.y + height, vertexC.z),
		Vec3D(vertexC.x + width, vertexC.y + height, vertexC.z),
		Vec3D(vertexC.x + width, vertexC.y + height, vertexC.z + depth),
		Vec3D(vertexC.x, vertexC.y + height, vertexC.z + depth),
	};

	re.CreateObject(&cube, NULL, GL_QUADS, QUAD, verticiesCube, 24, bbC, false);

	cube.LoadTexture(Mud_pcx);

	// add colours/texture to the cube 

	//// Front Face
	cube.AddTextCoord(0.0f, 0.0f);
	cube.AddTextCoord(1.0f, 0.0f);
	cube.AddTextCoord(1.0f, 1.0f);
	cube.AddTextCoord(0.0f, 1.0f);
	//cube.AddColour(1.0f, 0.0f, 0.0f);

	//// Back Face
	cube.AddTextCoord(1.0f, 0.0f);
	cube.AddTextCoord(1.0f, 1.0f);
	cube.AddTextCoord(0.0f, 1.0f);
	cube.AddTextCoord(0.0f, 0.0f);
	//cube.AddColour(0.0f, 1.0f, 1.0f);

	//// Top Face
	cube.AddTextCoord(0.0f, 1.0f);
	cube.AddTextCoord(0.0f, 0.0f);
	cube.AddTextCoord(1.0f, 0.0f);
	cube.AddTextCoord(1.0f, 1.0f);
	//cube.AddColour(1.0f, 0.0f, 1.0f);

	//// Bottom Face
	cube.AddTextCoord(1.0f, 1.0f);
	cube.AddTextCoord(0.0f, 1.0f);
	cube.AddTextCoord(0.0f, 0.0f);
	cube.AddTextCoord(1.0f, 0.0f);
	//cube.AddColour(0.75f, 0.0f, 1.0f);

	//// Right face
	cube.AddTextCoord(1.0f, 0.0f);
	cube.AddTextCoord(1.0f, 1.0f);
	cube.AddTextCoord(0.0f, 1.0f);
	cube.AddTextCoord(0.0f, 0.0f);
	//cube.AddColour(1.0f, 1.0f, 0.0f);

	//// Left Face
	cube.AddTextCoord(0.0f, 0.0f);
	cube.AddTextCoord(1.0f, 0.0f);
	cube.AddTextCoord(1.0f, 1.0f);
	cube.AddTextCoord(0.0f, 1.0f);
	//cube.AddColour(1.0f, 0.5f, 0.0f);

	/*****************Floor********************/

	// create floor
	GeometryNode floor(0.0f, 0.0f, -5.0f);
	Vec3D bbF(600.0f, 0.0f, 600.0f);
	
	Vec3D verticesFloor[4] = { Vec3D(-300.0, -3.0, -300.0), Vec3D(-300.0, -3.0, 300.0), Vec3D(300.0, -3.0, 300.0), Vec3D(300.0, -3.0, -300.0) };

	re.CreateObject(&floor, NULL, GL_QUADS, QUAD, verticesFloor, 4, bbF, false);

	floor.LoadTexture(drunkenlogo_pcx);

	floor.AddTextCoord(0.0f, 1.0f);
	floor.AddTextCoord(0.0f, 0.0f);
	floor.AddTextCoord(1.0f, 0.0f);
	floor.AddTextCoord(1.0f, 1.0f);

	//floor.AddColour(1.0f, 1.0f, 1.0f);


	/*****************Pyramid********************/

	GeometryNode py1(1.0f, 0.0f, -2.0f);

	Vec3D verticiesP1[12] = { Vec3D(0.0f, 1.0f, 0.0f), Vec3D(1.0f, 2.0f, 1.0f), Vec3D(1.0f, 2.0f, -1.0f),
		Vec3D(0.0f, 1.0f, 0.0f), Vec3D(1.0f, 0.0f, 1.0f), Vec3D(1.0f, 0.0f, -1.0f),
		Vec3D(0.0f, 1.0f, 0.0f), Vec3D(1.0f, 0.0f, 1.0f), Vec3D(1.0f, 2.0f, 1.0f),
		Vec3D(0.0f, 1.0f, 0.0f), Vec3D(1.0f, 2.0f, -1.0f), Vec3D(1.0f, 0.0f, -1.0f) };
	Vec3D bbP1(2.0f, 2.0f, 2.0f);

	re.CreateObject(&py1, &cube, GL_TRIANGLES, TRIANGLE, verticiesP1, 12, bbC, true);

	py1.SetRot(90.0f, 0.0f, 0.0f);

	py1.AddColour(1.0f, 0.0f, 1.0f);

	py1.AddColour(0.0f, 1.0f, 0.0f); 

	py1.AddColour(0.0f, 0.0f, 1.0f); 

	py1.AddColour(0.0f, 1.0f, 1.0f);

	while (1)
	{
		re.Run();

		cube.UpdateRot(0.3, 0.1, 0.4);
		
	}

	return 0;
}


#include "RocketEngine.h"

// textures
#include "Mud_pcx.h"


int main() {

	// instance of the engine
	RocketEngine re;

	// initialize generic settings for openGl
	re.init();

	re.LoadTextures(Mud_pcx);

	/*****************Cube********************/

	GeometryNode cube(0.0f, 3.0f, -5.0f);
	Vec3D vertexC(-1.0f, -1.0f, -1.0f);
	Vec3D bbC(2.0f, 2.0f, 2.0f);
	re.CreateObject(&cube, NULL, GL_QUADS, QUAD, &vertexC, 0, bbC, false);

	// add colours to the cube 

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
	Vec3D vertexF(-300.0, -3.0, -300.0);
	Vec3D bbF(600.0f, 0.0f, 600.0f);
	re.CreateObject(&floor, NULL, GL_QUADS, QUAD, &vertexF, 0, bbF, true);

	floor.AddColour(1.0f, 1.0f, 1.0f);
	floor.AddColour(1.0f, 1.0f, 1.0f);
	floor.AddColour(1.0f, 1.0f, 1.0f);
	floor.AddColour(1.0f, 1.0f, 1.0f);
	floor.AddColour(1.0f, 1.0f, 1.0f);
	floor.AddColour(1.0f, 1.0f, 1.0f);

	/*****************Pyramid********************/

	GeometryNode py1;

	Vec3D verticiesP1[12] = { Vec3D(0.0f, 1.0f, 0.0f), Vec3D(1.0f, 2.0f, 1.0f), Vec3D(1.0f, 2.0f, -1.0f),
		Vec3D(0.0f, 1.0f, 0.0f), Vec3D(1.0f, 0.0f, 1.0f), Vec3D(1.0f, 0.0f, -1.0f),
		Vec3D(0.0f, 1.0f, 0.0f), Vec3D(1.0f, 0.0f, 1.0f), Vec3D(1.0f, 2.0f, 1.0f),
		Vec3D(0.0f, 1.0f, 0.0f), Vec3D(1.0f, 2.0f, -1.0f), Vec3D(1.0f, 0.0f, -1.0f) };
	Vec3D bbP1(2.0f, 2.0f, 2.0f);

	re.CreateObject(&py1, &cube, GL_TRIANGLES, TRIANGLE, verticiesP1, 12, bbC, true);

	py1.Offset(1.0f, 0.0f, -2.0f);
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


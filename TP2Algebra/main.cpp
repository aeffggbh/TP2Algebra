#include <iostream>
#include "raylib.h"


struct VecRect
{
	Vector3 startPos;
	Vector3 finishPos;
	Vector3 rotationAngles;
	float magnitude;
};

struct Cube
{
	VecRect vecA2;
	VecRect vecB2;
	VecRect vecC2;
	VecRect vecC3;
	VecRect vecC4;
};

Camera3D camera;

VecRect vectorA;
VecRect vectorB;
VecRect vectorC;
Cube cube;

float n = 2;

void Init();
void Update();
void Draw();
void BuildCube();
void BuildPyramid();
void DrawFirstCube();
void InitVectors();
void InitCamera();

int main(void)
{
	srand(time(NULL));

	Init();

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		Update();
		Draw();
	}

	CloseWindow();

	return 0;
}

void Init()
{
	const int screenWidth = 800;
	const int screenHeight = 500;
	InitWindow(screenWidth, screenHeight, "TP2 Algebra");

	InitCamera();
	InitVectors();
	BuildCube();

}

void Update()
{

}

void BuildCube()
{
	cube.vecC2 = vectorC;
	cube.vecC2.startPos = vectorB.finishPos;
	cube.vecC2.finishPos.x = cube.vecC2.magnitude * cos(cube.vecC2.rotationAngles.y) * cos(cube.vecC2.rotationAngles.z);
	cube.vecC2.finishPos.y = cube.vecC2.magnitude * sin(cube.vecC2.rotationAngles.x) * cos(cube.vecC2.rotationAngles.y);
	cube.vecC2.finishPos.z = cube.vecC2.magnitude * sin(cube.vecC2.rotationAngles.z);

	
	/*VecRect aux = vectorB;
	aux.startPos = vectorB.finishPos;
	aux.rotationAngles.x *= -1;
	aux.rotationAngles.y *= -1;
	aux.rotationAngles.z *= -1;
	aux.finishPos.x = aux.magnitude * cos(aux.rotationAngles.y) * cos(aux.rotationAngles.z);
	aux.finishPos.y = aux.magnitude * sin(aux.rotationAngles.x) * cos(aux.rotationAngles.y);
	aux.finishPos.z = aux.magnitude * sin(aux.rotationAngles.z);

	DrawLine3D(aux.startPos, aux.finishPos, PINK);*/

	/*cube.vecA2 = vectorA;
	Vector3 aux;
	aux.x = vectorB.finishPos.x + vectorA.finishPos.x;
	aux.y = vectorB.finishPos.y + vectorA.finishPos.y;
	aux.z = vectorB.finishPos.z + vectorA.finishPos.z;
	cube.vecA2.startPos = aux;

	cube.vecB2.startPos = cube.vecA2.finishPos;
	cube.vecB2.finishPos = vectorB.finishPos;*/

}

void BuildPyramid()
{

}

void Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	BeginMode3D(camera);
	DrawFirstCube();
	//DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);

	EndMode3D();

	EndDrawing();
}

void DrawFirstCube()
{
	DrawLine3D(vectorA.startPos, vectorA.finishPos, RED);
	DrawLine3D(vectorB.startPos, vectorB.finishPos, BLUE);
	DrawLine3D(vectorC.startPos, vectorC.finishPos, GREEN);
	DrawLine3D(cube.vecC2.startPos, cube.vecC2.finishPos, GREEN);
	//DrawLine3D(cube.vecB2.startPos, cube.vecB2.finishPos, BROWN);

}

void InitVectors()
{
	const int maxMagnitude = 1000;

	int maxDegrees = 360;

	Vector3 startPos = { 0.0f, 0.0f, 0.0f, };

	VecRect aux;
	vectorA.startPos = startPos;
	vectorA.rotationAngles = { (float)(rand() % maxDegrees), (float)(rand() % maxDegrees), (float)(rand() % maxDegrees) };
	vectorA.magnitude = 200.0f;

	vectorA.finishPos.x = vectorA.magnitude * cos(vectorA.rotationAngles.y) * cos(vectorA.rotationAngles.z);
	vectorA.finishPos.y = vectorA.magnitude * sin(vectorA.rotationAngles.x) * cos(vectorA.rotationAngles.y);
	vectorA.finishPos.z = vectorA.magnitude * sin(vectorA.rotationAngles.z);

	aux = vectorA;
	aux.rotationAngles.x *= -1;
	aux.rotationAngles.y *= -1;
	aux.rotationAngles.z *= -1;

	vectorB.rotationAngles.x = vectorA.rotationAngles.x * aux.rotationAngles.x;
	vectorB.rotationAngles.y = vectorA.rotationAngles.y * aux.rotationAngles.y;
	vectorB.rotationAngles.z = vectorA.rotationAngles.z * aux.rotationAngles.z;

	vectorB.magnitude = vectorA.magnitude;
	vectorB.finishPos.x = vectorB.magnitude * cos(vectorB.rotationAngles.y) * cos(vectorB.rotationAngles.z);
	vectorB.finishPos.y = vectorB.magnitude * sin(vectorB.rotationAngles.x) * cos(vectorB.rotationAngles.y);
	vectorB.finishPos.z = vectorB.magnitude * sin(vectorB.rotationAngles.z);

	vectorC.magnitude = (1 / n) * vectorA.magnitude;

	vectorC.startPos = startPos;

	//cross product
	vectorC.rotationAngles.x = vectorA.rotationAngles.x * vectorB.rotationAngles.x;
	vectorC.rotationAngles.y = vectorA.rotationAngles.y * vectorB.rotationAngles.y;
	vectorC.rotationAngles.z = vectorA.rotationAngles.z * vectorB.rotationAngles.z;

	vectorC.finishPos.x = vectorC.magnitude * cos(vectorC.rotationAngles.y) * cos(vectorC.rotationAngles.z);
	vectorC.finishPos.y = vectorC.magnitude * sin(vectorC.rotationAngles.x) * cos(vectorC.rotationAngles.y);
	vectorC.finishPos.z = vectorC.magnitude * sin(vectorC.rotationAngles.z);

}

void InitCamera()
{
	camera.position = { 0.0f, 400.0f, 10.0f };  // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 64.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

}
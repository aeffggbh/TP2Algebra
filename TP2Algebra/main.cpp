#include <iostream>
#include "raylib.h"

void Update();
void Draw();

struct VecRect
{
	Vector3 startPos;
	Vector3 finishPos;
	Vector3 rotationAngles;
	float magnitude;
};

Camera3D camera;

VecRect vectorA;
VecRect vectorB;
VecRect vectorC;

float n = 2;

int main(void)
{
	srand(time(NULL));

	camera.position = { 0.0f, 400.0f, 10.0f };  // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 64.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	const int screenWidth = 800;
	const int screenHeight = 500;
	InitWindow(screenWidth, screenHeight, "TP2 Algebra");

	const int maxMagnitude = 1000;

	int maxDegrees = 360;

	Vector3 startPos = { 0.0f, 0.0f, 0.0f, };

	VecRect aux;
	vectorA.startPos = startPos;
	vectorA.rotationAngles = { (float)(rand() % maxDegrees), (float)(rand() % maxDegrees), (float)(rand() % maxDegrees) };
	vectorA.magnitude = 50.0f;

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

	int mag = sqrt(pow(vectorA.finishPos.x - vectorA.startPos.x, 2.0f) + pow(vectorA.finishPos.y - vectorA.startPos.y, 2.0f) + pow(vectorA.finishPos.z - vectorA.startPos.z, 2.0f));

	vectorC.magnitude = 1 / n * vectorA.magnitude;

	vectorC.startPos = startPos;

	vectorC.rotationAngles.x = vectorA.rotationAngles.x * vectorB.rotationAngles.x;
	vectorC.rotationAngles.y = vectorA.rotationAngles.y * vectorB.rotationAngles.y;
	vectorC.rotationAngles.z = vectorA.rotationAngles.z * vectorB.rotationAngles.z;

	vectorC.finishPos.x = vectorC.magnitude * cos(vectorC.rotationAngles.y) * cos(vectorC.rotationAngles.z);
	vectorC.finishPos.y = vectorC.magnitude * sin(vectorC.rotationAngles.x) * cos(vectorC.rotationAngles.y);
	vectorC.finishPos.z = vectorC.magnitude * sin(vectorC.rotationAngles.z);

	std::cout << "mag: " << vectorA.magnitude << std::endl;
	std::cout << "mag (calculada): " << mag << std::endl;
	std::cout << "x: " << vectorA.finishPos.x << std::endl;
	std::cout << "y: " << vectorA.finishPos.y << std::endl;
	std::cout << "z: " << vectorA.finishPos.z << std::endl;

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		Update();
		Draw();
	}

	CloseWindow();

	return 0;
}

void Update()
{

}

void Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	BeginMode3D(camera);

	DrawLine3D(vectorA.startPos, vectorA.finishPos, RED);
	DrawLine3D(vectorB.startPos, vectorB.finishPos, BLUE);
	DrawLine3D(vectorC.startPos,vectorC.finishPos, GREEN);

	//DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);

	EndMode3D();

	EndDrawing();
}
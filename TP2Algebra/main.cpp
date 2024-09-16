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

int main(void)
{
	srand(time(NULL));

	const int screenWidth = 800;
	const int screenHeight = 500;
	InitWindow(screenWidth, screenHeight, "TP2 Algebra");

	const int maxMagnitude = 1000;

	int maxDegrees = 360;

	Vector3 startPos = { 0.0f, 0.0f, 0.0f, };

	VecRect vectorA;
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

	VecRect vectorB;
	
	vectorB.rotationAngles.x = aux.rotationAngles.x * vectorA.rotationAngles.x;
	vectorB.rotationAngles.y = aux.rotationAngles.y * vectorA.rotationAngles.y;
	vectorB.rotationAngles.z = aux.rotationAngles.z * vectorA.rotationAngles.z;


	int mag = sqrt(pow(vectorA.finishPos.x - vectorA.startPos.x, 2.0f) + pow(vectorA.finishPos.y - vectorA.startPos.y, 2.0f) + pow(vectorA.finishPos.z - vectorA.startPos.z, 2.0f));

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


	EndDrawing();
}
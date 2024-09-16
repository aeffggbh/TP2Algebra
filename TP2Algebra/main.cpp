#include <iostream>
#include "raylib.h"

void Update();
void Draw();

struct VecRect
{
	Vector3 pos;
	Vector3 rotationAngles;
	float magnitude;
};

int main(void)
{
	srand(time(NULL));
		
	const int screenWidth = 800;
	const int screenHeight = 500;
	const int maxMagnitude = 1000;

	int maxDegrees = 360;
	//const int maxPoints = 3;

	Vector3 startPos = { 0.0f, 0.0f, 0.0f, };

	VecRect vectorA;
	VecRect vectorB;
	VecRect vectorC;

	vectorA.pos = startPos;
	vectorA.rotationAngles = { (float)(rand() % maxDegrees), (float)(rand() % maxDegrees), (float)(rand() % maxDegrees) };
	vectorA.magnitude = GetRandomValue(0, maxMagnitude) / 10;


	//Vector3 points[maxPoints] = { a, b, c };

	InitWindow(screenWidth, screenHeight, "TP2 Algebra");

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
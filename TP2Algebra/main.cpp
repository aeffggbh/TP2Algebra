#include <iostream>
#include "raylib.h"

void Update();
void Draw();

int main(void)
{
	srand(time(NULL));

	const int screenWidth = 800;
	const int screenHeight = 500;
	int maxDegrees = 360;
	//const int maxPoints = 3;

	vector3 startPos = { 0.0f, 0.0f, 0.0f, };

	Vector3 vectorA = { rand(0, maxDegrees), rand(0, maxDegrees, rand(0, maxDegrees) };
	Vector3 vectorB = { 0.0f, 0.0f, 0.0f };
	Vector3 vectorC = { 0.0f, 0.0f, 0.0f };

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
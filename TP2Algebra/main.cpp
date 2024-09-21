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
	VecRect vecA3;
	VecRect vecA4;

	VecRect vecB2;
	VecRect vecB3;
	VecRect vecB4;

	VecRect vecC2;
	VecRect vecC3;
	VecRect vecC4;
};

Camera3D camera;

VecRect vectorA;
VecRect vectorB;
VecRect vectorC;
Cube cube;

float n = 5;

void Init();
void Update();
void Draw();
void BuildCube();
void BuildPyramid();
void DrawFirstCube();
void InitVectors();
void InitCamera();

void GetFinishPosition(VecRect& vector);
Vector3 GetCrossProduct(Vector3 rotationA, Vector3 rotationB);

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

	DisableCursor();
}

void Update()
{
	UpdateCameraPro(&camera,
		Vector3{
		(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) * 0.1f -      // Move forward-backward
			(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) * 0.1f,
			(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) * 0.1f -   // Move right-left
			(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) * 0.1f,
			0.0f                                                // Move up-down
		},
		Vector3{
		GetMouseDelta().x * 0.05f,                            // Rotation: yaw
			GetMouseDelta().y * 0.05f,                            // Rotation: pitch
			0.0f                                                // Rotation: roll
		},
		GetMouseWheelMove() * 2.0f);                              // Move to target (zoom)
}

void BuildCube()
{
	cube.vecA2 = vectorA;
	cube.vecA2.startPos = vectorB.finishPos;
	GetFinishPosition(cube.vecA2);

	cube.vecB2 = vectorB;
	cube.vecB2.startPos = vectorA.finishPos;
	GetFinishPosition(cube.vecB2);

	cube.vecC2 = vectorC;
	cube.vecC2.startPos = vectorB.finishPos;
	GetFinishPosition(cube.vecC2);

	cube.vecC3 = vectorC;
	cube.vecC3.startPos = vectorA.finishPos;
	GetFinishPosition(cube.vecC3);

	cube.vecC4 = vectorC;
	cube.vecC4.startPos = cube.vecA2.finishPos;
	GetFinishPosition(cube.vecC4);

	cube.vecA3 = vectorA;
	cube.vecA3.startPos = cube.vecC2.finishPos;
	GetFinishPosition(cube.vecA3);

	cube.vecA4 = vectorA;
	cube.vecA4.startPos = vectorC.finishPos;
	GetFinishPosition(cube.vecA4);

	cube.vecB3 = vectorB;
	cube.vecB3.startPos = cube.vecC3.finishPos;
	GetFinishPosition(cube.vecB3);

	cube.vecB4 = vectorB;
	cube.vecB4.startPos = vectorC.finishPos;
	GetFinishPosition(cube.vecB4);
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

	EndMode3D();

	EndDrawing();
}

void DrawFirstCube()
{
	DrawLine3D(vectorA.startPos, vectorA.finishPos, RED);
	DrawLine3D(vectorB.startPos, vectorB.finishPos, BLUE);
	DrawLine3D(vectorC.startPos, vectorC.finishPos, GREEN);

	DrawLine3D(cube.vecA2.startPos, cube.vecA2.finishPos, RED);
	DrawLine3D(cube.vecA3.startPos, cube.vecA3.finishPos, RED);
	DrawLine3D(cube.vecA4.startPos, cube.vecA4.finishPos, RED);

	DrawLine3D(cube.vecB2.startPos, cube.vecB2.finishPos, BLUE);
	DrawLine3D(cube.vecB3.startPos, cube.vecB3.finishPos, BLUE);
	DrawLine3D(cube.vecB4.startPos, cube.vecB4.finishPos, BLUE);

	DrawLine3D(cube.vecC2.startPos, cube.vecC2.finishPos, GREEN);
	DrawLine3D(cube.vecC3.startPos, cube.vecC3.finishPos, GREEN);
	DrawLine3D(cube.vecC4.startPos, cube.vecC4.finishPos, GREEN);
}

void InitVectors()
{
	const int maxMagnitude = 1000;

	int maxDegrees = 360;

	Vector3 startPos = { 0.0f, 0.0f, 0.0f, };

	VecRect aux;
	vectorA.startPos = startPos;
	vectorA.rotationAngles = { (float)(rand() % maxDegrees), (float)(rand() % maxDegrees), (float)(rand() % maxDegrees) };
	//vectorA.rotationAngles = { 0,90,45 };
	vectorA.magnitude = 200.0f;

	GetFinishPosition(vectorA);

	aux = vectorA;
	aux.rotationAngles.x *= -1;
	aux.rotationAngles.y *= -1;
	aux.rotationAngles.z *= -1;


	//Vector B
	vectorB.rotationAngles = GetCrossProduct(vectorA.rotationAngles, aux.rotationAngles);

	vectorB.magnitude = vectorA.magnitude;
	GetFinishPosition(vectorB);


	//Vector C
	vectorC.magnitude = (1 / n) * vectorA.magnitude;
	vectorC.startPos = startPos;

	vectorC.rotationAngles = GetCrossProduct(vectorA.rotationAngles, vectorB.rotationAngles);
	GetFinishPosition(vectorC);

}

void InitCamera()
{
	camera.position = { 0.0f, 0.0f, 10.0f };  // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 64.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

}

void GetFinishPosition(VecRect& vector)
{
	vector.finishPos.x = vector.startPos.x + vector.magnitude * cos(vector.rotationAngles.y) * cos(vector.rotationAngles.z);
	vector.finishPos.y = vector.startPos.y + vector.magnitude * sin(vector.rotationAngles.x) * cos(vector.rotationAngles.y);
	vector.finishPos.z = vector.startPos.z + vector.magnitude * sin(vector.rotationAngles.z);
}

Vector3 GetCrossProduct(Vector3 rotationA, Vector3 rotationB)
{
	Vector3 rotation;

	rotation.x = rotationA.x * rotationB.x;
	rotation.y = rotationA.y * rotationB.y;
	rotation.z = rotationA.z * rotationB.z;

	return rotation;
}

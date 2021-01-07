#pragma once
#include <iostream>
#include <string>
#include <random>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <string>
#include <Eigen/Core>
#include "Header.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

using namespace std;

/*
*	2020. 11. 07
*	니크네임
*	공부한 수학 점검할 겸, C++손에 익힐겸 진행한 콘솔로 3D연산 공부
*/


World* Singleton::world = new World();
Render* Singleton::render = new Render();
GameObject* Singleton::camera = Singleton::world->CreateGameobject();
Pixel* Singleton::pixels = new Pixel[SCREEN_WIDTH * SCREEN_HEIGHT];

int main()
{
	Buffer<Input> buffer{ 128 };

	GameObject* Box1 = Singleton::world->CreateBox();
	Transform* box1_Transform = Box1->GetComponent<Transform>();
	box1_Transform->position = { 2, 0.5, 5 };
	box1_Transform->localScale = { 2, 2, 2};

	GameObject* Box2 = Singleton::world->CreateBox();
	Transform* box2_Transform = Box2->GetComponent<Transform>();
	box2_Transform->position = { -2, 0.5, 5 };
	box2_Transform->localScale = { 2, 2, 2 };
	
	auto cameraComponent = Singleton::camera->AddComponent(new CameraComponent());
	Transform* cameraTransform = Singleton::camera->GetComponent<Transform>();
	cameraTransform->position = { 0, 0.5, 0 };
	cameraTransform->rotation = { 0, 0, 0 };
	cameraTransform->localScale = { 1, 1, 1 };

	float time = 0;
	float targetFrame = 60;
	float waitMilliSecond = 1000 / targetFrame;

	while (true)
	{
		auto start = clock();
		buffer.Clear();

		Singleton::world->WorldUpdate();
		Singleton::render->Rendering();
		box1_Transform->rotation = { 0, time * (1/2.0f) * D2R, 0 };

		auto end = clock();
		this_thread::sleep_for(chrono::milliseconds(((long)waitMilliSecond - (end - start)) < 0 ? 0 : ((long)waitMilliSecond - (end - start)))); // 60프레임 유지
		++time;
	}
	
	cout << "end\n";
}

/*
* 		Singleton::input(&buffer);
		for (int i = 0; i < buffer.index; i++)
		{
			//cout << buffer.arr[i].keyCode;
			switch (buffer.arr[i].keyCode)
			{
				case (unsigned short)'a':
				{
					trans3->position = trans3->position + float3{ -0.5, 0, 0 };
					break;
				}
				case (unsigned short)'d':
				{
					trans3->position = trans3->position + float3{ 0.5, 0, 0 };
					break;
				}
				case (unsigned short)'w':
				{
					trans3->position = trans3->position + float3{ 0, 0, 0.5 };
					break;
				}
				case (unsigned short)'s':
				{
					trans3->position = trans3->position + float3{ 0, 0, -0.5 };
					break;
				}
				case 75:
				{
					trans3->rotation = trans3->rotation + float3{ 0, 10 * D2R, 0 };
					break;
				}
				case 72:
				{
					trans3->rotation = trans3->rotation + float3{ -10 * D2R, 0, 0 };
					break;
				}
				case 77:
				{
					trans3->rotation = trans3->rotation + float3{ 0, -10 * D2R, 0 };
					break;
				}
				case 80:
				{
					trans3->rotation = trans3->rotation + float3{ 10 * D2R, 0, 0 };
					break;
				}
			}
		}
*/
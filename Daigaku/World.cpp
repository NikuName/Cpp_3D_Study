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

using namespace std;

using Eigen::MatrixXd;
using Eigen::VectorXd;


World::World()
{

}

GameObject* World::CreateGameobject()
{
	GameObject* obj = new GameObject();
	objects->push_back(obj);
	return obj;
}
void World::WorldUpdate()
{
	for (int i = 0; i < objects->size(); i++)
	{
		(*objects)[i]->Update();
	}
}

World::~World()
{
	for (int i = 0; i < objects->size(); i++)
		delete (*objects)[i];
	delete objects;
}

GameObject* World::CreateBox() //Box 버텍스, 트라이앵글 생성
{
	GameObject* gameObject = Singleton::world->CreateGameobject();
	MeshFilter* mf = gameObject->AddComponent(new MeshFilter());
	MeshRenderer* mr = gameObject->AddComponent(new MeshRenderer());
	Transform* trans = gameObject->GetComponent<Transform>();

	mf->vertexs->push_back({ 0.5, 0.5, -0.5, 1 });
	mf->vertexs->push_back({ -0.5, 0.5, -0.5, 1 });
	mf->vertexs->push_back({ -0.5, -0.5, -0.5, 1 });
	mf->vertexs->push_back({ 0.5, -0.5, -0.5, 1 });

	mf->vertexs->push_back({ -0.5, 0.5, 0.5, 1 });
	mf->vertexs->push_back({ 0.5, 0.5, 0.5, 1 });
	mf->vertexs->push_back({ 0.5, -0.5, 0.5, 1 });
	mf->vertexs->push_back({ -0.5, -0.5, 0.5, 1 });

	mf->vertexs->push_back({ 0.5, 0.5, 0.5, 1 });
	mf->vertexs->push_back({ 0.5, 0.5, -0.5, 1 });
	mf->vertexs->push_back({ 0.5, -0.5, -0.5, 1 });
	mf->vertexs->push_back({ 0.5, -0.5, 0.5, 1 });

	mf->vertexs->push_back({ -0.5, 0.5, -0.5, 1 });
	mf->vertexs->push_back({ -0.5, 0.5, 0.5, 1 });
	mf->vertexs->push_back({ -0.5, -0.5, 0.5, 1 });
	mf->vertexs->push_back({ -0.5, -0.5, -0.5, 1 });

	mf->vertexs->push_back({ 0.5, 0.5, 0.5, 1 });
	mf->vertexs->push_back({ -0.5, 0.5, 0.5, 1 });
	mf->vertexs->push_back({ -0.5, 0.5, -0.5, 1 });
	mf->vertexs->push_back({ 0.5, 0.5, -0.5, 1 });

	mf->vertexs->push_back({ 0.5, -0.5, -0.5, 1 });
	mf->vertexs->push_back({ -0.5, -0.5, -0.5, 1 });
	mf->vertexs->push_back({ -0.5, -0.5, 0.5, 1 });
	mf->vertexs->push_back({ 0.5, -0.5, 0.5, 1 });


	mf->triangles->push_back(0);
	mf->triangles->push_back(1);
	mf->triangles->push_back(2);
	mf->triangles->push_back(0);
	mf->triangles->push_back(2);
	mf->triangles->push_back(3);

	mf->triangles->push_back(4);
	mf->triangles->push_back(5);
	mf->triangles->push_back(6);
	mf->triangles->push_back(4);
	mf->triangles->push_back(6);
	mf->triangles->push_back(7);

	mf->triangles->push_back(8);
	mf->triangles->push_back(9);
	mf->triangles->push_back(10);
	mf->triangles->push_back(8);
	mf->triangles->push_back(10);
	mf->triangles->push_back(11);

	mf->triangles->push_back(12);
	mf->triangles->push_back(13);
	mf->triangles->push_back(14);
	mf->triangles->push_back(12);
	mf->triangles->push_back(14);
	mf->triangles->push_back(15);

	mf->triangles->push_back(16);
	mf->triangles->push_back(17);
	mf->triangles->push_back(18);
	mf->triangles->push_back(16);
	mf->triangles->push_back(18);
	mf->triangles->push_back(19);

	mf->triangles->push_back(20);
	mf->triangles->push_back(21);
	mf->triangles->push_back(22);
	mf->triangles->push_back(20);
	mf->triangles->push_back(22);
	mf->triangles->push_back(23);

	mf->uv->push_back({ 1, 1 });
	mf->uv->push_back({ 0, 1 });
	mf->uv->push_back({ 0, 0 });
	mf->uv->push_back({ 1, 0 });

	trans->position = { 0, 0, 0 };
	trans->rotation = { 0, 0, 0 };
	trans->localScale = { 1, 1, 1 };
	return gameObject;
}
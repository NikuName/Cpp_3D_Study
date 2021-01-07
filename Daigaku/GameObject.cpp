#include <iostream>
#include <string>
#include <random>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <string>
#include <Eigen/Dense>
#include "Header.h"

using namespace std;

using Eigen::MatrixXd;
using Eigen::VectorXd;


GameObject::GameObject()
{
	idle();
}
GameObject::GameObject(string name)
{
	this->name = name;
	idle();
}

void GameObject::idle()
{
	AddComponent(new Transform());
}

void GameObject::Update()
{
	for (int i = 0; i < list->size(); i++)
	{
		(*list)[i]->Update();
	}
}
template Transform* GameObject::AddComponent<Transform>(Transform*);
template CameraComponent* GameObject::AddComponent<CameraComponent>(CameraComponent*);
template MeshFilter* GameObject::AddComponent<MeshFilter>(MeshFilter*);
template MeshRenderer* GameObject::AddComponent<MeshRenderer>(MeshRenderer*);
template <typename T> T* GameObject::AddComponent(T* element)
{
	Component* comp;
	list->push_back(comp = (Component*)(element));
	comp->gameObject = this;
	return element;
}

template Transform* GameObject::GetComponent<Transform>();
template CameraComponent* GameObject::GetComponent<CameraComponent>();
template MeshFilter* GameObject::GetComponent<MeshFilter>();
template MeshRenderer* GameObject::GetComponent<MeshRenderer>();
template <typename T> T* GameObject::GetComponent()
{
	T* element = nullptr;
	for (int i = 0; i < list->size(); i++)
		if (((element = dynamic_cast<T*>((*list)[i]))) != nullptr)
			break;
	return element;
}

GameObject::~GameObject()
{
	for (int i = 0; i < list->size(); i++)
		delete (*list)[i];
	list->clear();
	delete list;
}
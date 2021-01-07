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
/*
* ¹Ì¿Ï¼º
*/
Input::Input()
{

}
Input& Input::operator=(const Input& other)
{
	isKeyBoard = other.isKeyBoard;
	isMouse = other.isMouse;
	press = other.press;
	keyCode = other.keyCode;
	mouseType = other.mouseType;
	return *this;
}
void Input::SetKeyBoard(unsigned short keyCode, int press)
{
	isKeyBoard = true;
	this->press = press;
	this->keyCode = keyCode;
}
void Input::SetMouse(unsigned char mouseType, int press)
{
	isMouse = true;

}
void Input::Clear()
{
	isMouse = false;
	isKeyBoard = false;
	press = -1;
	keyCode = 'A';
	mouseType = 0;
}

void Debug::Log(const string str)
{
	cout << str << '\n';
}


void Singleton::input(Buffer<Input>* buffer)
{
	int c = _getch();
	auto& in = buffer->Add();
	in.Clear();
	in.SetKeyBoard(c, 0);
}

template Buffer<Input>::Buffer(int size);
template Input& Buffer<Input>::Add();
template void Buffer<Input>::Clear();
template Buffer<Input>::~Buffer();

template <typename T>
Buffer<T>::Buffer(int size)
{
	this->size = size;
	this->index = 0;
	arr = new T[this->size];
}
template <typename T>
T& Buffer<T>::Add()
{
	return arr[index++];
}
template <typename T>
void Buffer<T>::Clear()
{
	index = 0;
}
template <typename T>
Buffer<T>::~Buffer()
{
	if (arr != nullptr)
		delete[] arr;
}
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
*	내부 사용을 행렬 라이브러리
*	연산은 외부 Eigen이라는 라이브러리에서 연산력을 빌려왔으며
*	사용성 개선을 위해 래핑한 클래스이다.
*/


floatNM::floatNM(int x, int y)
{
	cSize = x;
	rSize = y;
}
floatNM::floatNM(const floatNM& other)
{
	cSize = other.cSize;
	rSize = other.rSize;
	for (int i = 0; i < cSize; i++)
		for (int j = 0; j < rSize; j++)
			set(i, j, other.get(i, j));

}
floatNM::floatNM(float4 coloum1, float4 coloum2, float4 coloum3, float4 coloum4)
{
	cSize = 4;
	rSize = 4;
	set(coloum1, coloum2, coloum3, coloum4);
}
floatNM::floatNM(int x, int y, float4 coloum1, float4 coloum2, float4 coloum3, float4 coloum4)
{
	cSize = x;
	rSize = y;
	set(coloum1, coloum2, coloum3, coloum4);
}
MatrixXd floatNM::getMetrix()
{
	MatrixXd m = MatrixXd(cSize, rSize);
	for (int i = 0; i < cSize; i++)
		for (int j = 0; j < rSize; j++)
			m(i, j) = get(i, j);
	return m;
}
void floatNM::setMetrix(const MatrixXd& m)
{
	for (int i = 0; i < cSize; i++)
		for (int j = 0; j < rSize; j++)
			set(i, j, m(i, j));
}
MatrixXd floatNM::M2M(floatNM m)
{
	return m.getMetrix();
}
floatNM floatNM::M2M(MatrixXd m)
{
	floatNM m2 = floatNM(4, 4);
	m2.setMetrix(m);
	return m2;
}
float floatNM::get(int x, int y) const
{
	if (x < cSize && y < rSize)
		return a[(y * maxCount) + x];
}
void floatNM::set(int x, int y, float value)
{
	if (x < cSize && y < rSize)
	{
		a[(y * maxCount) + x] = value;
	}
}
void floatNM::set(float4& coloum1, float4& coloum2, float4& coloum3, float4& coloum4)
{
	setColoum(0, coloum1);
	setColoum(1, coloum2);
	setColoum(2, coloum3);
	setColoum(3, coloum4);
}
float4 floatNM::getColoum(int iRow)
{
	float4 result;
	for (int i = 0; i < cSize; i++)
		result[i] = get(i, iRow);
	return result;
}
float4 floatNM::getRow(int iColoum)
{
	float4 result;
	for (int i = 0; i < rSize; i++)
		result[i] = get(iColoum, i);
	return result;
}

void floatNM::setColoum(int iRow, float4& vectors)
{
	for (int i = 0; i < cSize; i++)
		set(i, iRow, vectors[i]);
}
void floatNM::setRow(int iColoum, float4& vectors)
{
	for (int i = 0; i < rSize; i++)
		set(iColoum, i, vectors[i]);
}
floatNM floatNM::operator*(const floatNM& other)
{
	floatNM result = floatNM::zero();
	result.rSize = rSize;
	result.cSize = other.cSize;
	for (int i = 0; i < result.rSize; i++)
	{
		for (int j = 0; j < result.cSize; j++)
		{
			for (int k = 0; k < cSize; k++)
			{
				result.set(j, i, (result.get(j, i) + (get(k, i) * other.get(j, k))));
			}
		}
	}
	return result;
}
floatNM floatNM::zero()
{
	return
	{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};
}
floatNM floatNM::identity()
{
	return
	{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
}

// IToString을(를) 통해 상속됨
void floatNM::ToString()
{
	for (int j = 0; j < rSize; j++)
	{
		for (int i = 0; i < cSize; i++)
		{
			cout << get(i, j) << ", ";
		}
		cout << '\n';
	}
}


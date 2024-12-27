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


Render::Render()
{
	consoleWindow = GetConsoleWindow();
	consoleDC = GetDC(consoleWindow);
	system("mode con: lines=45 cols=160");

	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD bufferSize = { SCREEN_WIDTH*2, SCREEN_HEIGHT };
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

	wcscpy_s(cfi.FaceName, L"Consolas");
	cfi.dwFontSize.Y = 18;  // 글자 크기 설정 (원하는 크기로 조정 가능)

	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

	for (int i = 0; i < SCREEN_WIDTH; i++)
		for (int j = 0; j < SCREEN_HEIGHT; j++)
			tempDepthBuffer[i][j] = 1;
}

void Render::Init()
{

}

void Render::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void Render::cls()
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	std::cout.flush();

	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);
	SetConsoleCursorPosition(hOut, topLeft);
}

/*
*	최종적으로 화면에 렌더링
*/
void Render::Rendering()
{
	for (int i = 0; i < SCREEN_WIDTH; i++)
		for (int j = 0; j < SCREEN_HEIGHT; j++)
			tempDepthBuffer[i][j] = 1;

	for (int i = 0; i < Singleton::world->objects->size(); i++)
	{
		MeshRenderer* MR = (*(Singleton::world->objects))[i]->GetComponent<MeshRenderer>();
		if(MR != nullptr)
			MR->Randering();
	}
	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		tempConsoleLineData[y] = "";
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			const char* ch = Singleton::pixels[(y * SCREEN_WIDTH) + x].isEnable ? "█" : "　"; // █,　
			tempConsoleLineData[y] += ch;
			Singleton::pixels[(y * SCREEN_WIDTH) + x].isEnable = false;
		}
		setCursorPosition(0, y);
		cout.write((tempConsoleLineData[y]).c_str(), (tempConsoleLineData[y]).size());
	}
	std::cout.flush();
}

void Render::lineBresenham(vector<float2>* lists, int x0, int y0, int x1, int y1) // 브레젠험 알고리즘
{
	int dy = y1 - y0;
	int dx = x1 - x0;
	int stepx, stepy;
	if (dy < 0)
	{                                 // 기울기를 양수처리함
		dy = -dy;
		stepy = -1;
	}
	else
		stepy = 1;

	if (dx < 0)
	{
		dx = -dx;
		stepx = -1;
	}
	else
		stepx = 1;
	dy <<= 1;                                     // dy*2 와 같은 의미(비트연산)
	dx <<= 1;                                     // dx*2 와 같은 의미(비트연산)
	lists->push_back({ (float)x0, (float)y0 });                         // 슈도 메소드
	if (dx > dy) {
		int fraction = dy - (dx >> 1);     // dx>>1 은 dx/2와 같은 의미(비트연산)
		while (x0 != x1) {
			if (fraction >= 0) {
				y0 += stepy;
				fraction -= dx;                 // fraction -= 2*dx 과 같은 의미
			}
			x0 += stepx;
			fraction += dy;                     // fraction -= 2*dy 과 같은 의미
			lists->push_back({ (float)x0, (float)y0 });
		}
	}
	else {
		int fraction = dx - (dy >> 1);
		while (y0 != y1) {
			if (fraction >= 0) {
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			lists->push_back({ (float)x0, (float)y0 });
		}
	}
}

Render::~Render()
{

}
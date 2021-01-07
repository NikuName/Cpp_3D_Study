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
#include <Eigen/Dense>


#define D2R 0.0174532f
#define R2D 57.295779f

using namespace std;

using Eigen::MatrixXd;
using Eigen::VectorXd;

class Transform;
class Render;
class Pixel;
class float4;
struct floatNM;
struct Debug;
class Component;
class CameraComponent;
class MeshRenderer;

typedef float4 float3;
typedef float4 float2;
typedef float4 Vector2;
typedef float4 Vector3;
typedef float4 Vector4;

static const int SCREEN_WIDTH = 80, SCREEN_HEIGHT = 45;

class GameObject
{
public:
	string name;
	string tag;
	vector<Component*>* list = new vector<Component*>();
	GameObject(string);
	GameObject();
	void idle();
	void Update();
	template <typename T> T* AddComponent(T* element);
	template <typename T> T* GetComponent();
	~GameObject();
};

struct Debug
{
	static void Log(const string str);
};

class float4
{
public:
	float x = 0, y = 0, z = 0, w = 0;
	float4();
	float4(float x);
	float4(float x, float y);
	float4(float x, float y, float z);
	float4(float x, float y, float z, float w);
	float4(const float4& vector);
	float4& operator=(const float4* vector);
	float4& operator=(const float4& vect2);
	float4& operator*(const float& value);
	float4& operator/(const float& value);
	float4& operator+(const float4& vector);
	float4& operator-(const float4& vector);
	float& operator[](int index);
	static float Dot(float4 v1, float4 v2);
	static float4 Cross(float4 v1, float4 v2);
	float sqrtDistance();
	float distance();
	void ToString();
	VectorXd getVector();
	void setVector(const VectorXd& v);
	static VectorXd V2V(float4 v);
	static float4 V2V(VectorXd v);
	float4 normalized();
	~float4();
};

struct floatNM
{
	static const int maxCount = 4;
	int rSize = 0;
	int cSize = 0;
	float a[maxCount * maxCount];

	floatNM(int x, int y);
	floatNM(const floatNM& other);
	floatNM(float4 coloum1, float4 coloum2, float4 coloum3, float4 coloum4);
	floatNM(int x, int y, float4 coloum1, float4 coloum2, float4 coloum3, float4 coloum4);
	MatrixXd getMetrix();
	void setMetrix(const MatrixXd& m);
	static MatrixXd M2M(floatNM m);
	static floatNM M2M(MatrixXd m);
	float get(int x, int y) const;
	void set(int x, int y, float value);
	void set(float4& coloum1, float4& coloum2, float4& coloum3, float4& coloum4);
	float4 getColoum(int iRow);
	float4 getRow(int iColoum);
	void setColoum(int iRow, float4& vectors);
	void setRow(int iColoum, float4& vectors);
	floatNM operator*(const floatNM& other);
	static floatNM zero();
	static floatNM identity();
	void ToString();
};
struct Input
{
	bool isKeyBoard = false;
	bool isMouse = false;
	int press = -1;
	unsigned short keyCode = 'A';
	unsigned char mouseType = 0;
	Input();
	Input& operator=(const Input& other);
	void SetKeyBoard(unsigned short shortkeyCode, int press);
	void SetMouse(unsigned char mouseType, int press);
	void Clear();
};


class Component
{
public:
	GameObject* gameObject = nullptr;
	virtual void Start();
	virtual void Update();
	~Component();
};

class Transform : public Component
{
public:
	float3 position;
	float3 rotation;
	float3 localScale;

	MatrixXd LocalToWorld();
	MatrixXd WorldToLocal();
	virtual void Start();
	virtual void Update();
};

class MeshFilter : public Component
{
public:
	vector<float4>* vertexs = new vector<float4>();
	vector<int>* triangles = new vector<int>();
	vector<float2>* uv = new vector<float2>();
	virtual void Start();
	virtual void Update();
	~MeshFilter();
};

class MeshRenderer : public Component
{
public:
	virtual void Start();
	virtual void Update();
	virtual void Randering();
};

class CameraComponent : public Component
{
public:
	float f = 1000;
	float n = 0.1;
	float w = n * tan(60 * 0.0174532);
	float h = w * ((float)SCREEN_HEIGHT / SCREEN_WIDTH);
	floatNM ViewM;
	floatNM ProjectionMatrix;
	CameraComponent();
	MatrixXd WorldToCamera();
	virtual void Start();
	virtual void Update();
};


class World
{
public:
	vector<GameObject*>* objects = new vector<GameObject*>();

	World();
	GameObject* CreateGameobject();
	GameObject* CreateBox();
	void WorldUpdate();
	~World();
};

template <typename T> class Buffer
{
public:
	int size = 0;
	T* arr;
	int index = 0;

	Buffer(int size);
	T& Add();
	void Clear();
	~Buffer();
};

class Pixel
{
public:
	bool isEnable = false;
	float3 color;
	float3 position;
	float3 normal;
	Transform* trans;
};

class Render
{
public:
	void setCursorPosition(int x, int y);
	Render();
	void cls();
	string tempConsoleLineData[SCREEN_HEIGHT];
	int i = 0;
	HWND consoleWindow;
	HDC consoleDC;
	void Rendering();
	~Render();
	static void lineBresenham(vector<float2>* lists, int x0, int y0, int x1, int y1);
};

class Singleton
{
public:
	static World* world;
	static Render* render;
	static Pixel* pixels;
	static GameObject* camera;
	static World* getWorld()
	{
		return world;
	}
	static void input(Buffer<Input>* buffer);
};
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




void Component::Start()
{

}
void Component::Update()
{

}
Component::~Component()
{
	gameObject = nullptr;
}



MatrixXd Transform::LocalToWorld()
{
	MatrixXd result = MatrixXd(4, 4);
	float3 angle = rotation;
	MatrixXd rotationMatrix =
		floatNM { 4, 4,
		{ 1, 0, 0, 0 },
		{ 0, cos(angle.x), sin(angle.x), 0 },
		{ 0, -sin(angle.x), cos(angle.x), 0 },
		{ 0, 0, 0, 1 }
	}.getMetrix() *
		floatNM { 4, 4,
		{ cos(angle.y), 0, sin(angle.y), 0 },
		{ 0, 1, 0, 0 },
		{ -sin(angle.y), 0, cos(angle.y), 0 },
		{ 0, 0, 0, 1 }
	}.getMetrix()*
		floatNM { 4, 4,
		{ cos(angle.z), -sin(angle.z), 0, 0 },
		{ sin(angle.z), cos(angle.z), 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	}.getMetrix();

	MatrixXd positionMatrix = floatNM{
		4, 4,
		{ localScale.x, 0, 0, 0 },
		{ 0, localScale.y, 0, 0 },
		{ 0, 0, localScale.z, 0 },
		{ 0, 0, 0, 1 }
	}.getMetrix();

	MatrixXd scaleMatrix = floatNM{
		4, 4,
		{ 1, 0, 0, position.x },
		{ 0, 1, 0, position.y },
		{ 0, 0, 1, position.z },
		{ 0, 0, 0, 1 }
	}.getMetrix();
	result = positionMatrix * rotationMatrix * scaleMatrix;
	return result;
}
MatrixXd Transform::WorldToLocal()
{
	return LocalToWorld().inverse();
}
void Transform::Start()
{

}
void Transform::Update()
{
	//cout << "This Is Transform" << '\n';
}




void MeshFilter::Start()
{

}
void MeshFilter::Update()
{
	//cout << "This Is MeshFilter" << '\n';
}
MeshFilter::~MeshFilter()
{
	delete vertexs;
	delete triangles;
	delete uv;
}




void MeshRenderer::Start()
{

}
void MeshRenderer::Update()
{

}

void MeshRenderer::Randering()
{
	MeshFilter* mf = gameObject->GetComponent<MeshFilter>();
	Transform* trans = gameObject->GetComponent<Transform>();
	CameraComponent* cc = Singleton::camera->GetComponent<CameraComponent>();
	MatrixXd VP = floatNM::M2M(cc->ProjectionMatrix).transpose() * cc->WorldToCamera().transpose();
	MatrixXd MVP = VP * trans->LocalToWorld().transpose(); // 모델 행렬, 프로젝션 행렬, 뷰 행렬의 연산 사용

	vector<float2> list{};
	//	트라이 앵글 정보를 기반으로 해당 버텍스를 찾아서
	//	브레젠험 알고리즘을 통해 선분을 깔끔하게 만든 뒤
	//	출력할 화면 버퍼에 저장하는 방식.
	for (int i = 0; i < mf->triangles->size(); i += 3)
	{
		float4 v1 = float4::V2V(MVP * float4::V2V((*(mf->vertexs))[((*(mf->triangles))[i])]));
		float4 v2 = float4::V2V(MVP * float4::V2V((*(mf->vertexs))[((*(mf->triangles))[i+1])]));
		float4 v3 = float4::V2V(MVP * float4::V2V((*(mf->vertexs))[((*(mf->triangles))[i+2])]));
		v1 = v1 / v1.w;
		v2 = v2 / v2.w;
		v3 = v3 / v3.w;

		float2 pos1 = { roundf(SCREEN_WIDTH * (v1.x * 0.5 + 0.5)), roundf(SCREEN_HEIGHT - (SCREEN_HEIGHT * (v1.y * 0.5 + 0.5)) - 1.0) };
		float2 pos2 = { roundf(SCREEN_WIDTH * (v2.x * 0.5 + 0.5)), roundf(SCREEN_HEIGHT - (SCREEN_HEIGHT * (v2.y * 0.5 + 0.5)) - 1.0) };
		float2 pos3 = { roundf(SCREEN_WIDTH * (v3.x * 0.5 + 0.5)), roundf(SCREEN_HEIGHT - (SCREEN_HEIGHT * (v3.y * 0.5 + 0.5)) - 1.0) };
		
		list.clear();
		Render::lineBresenham(&list, pos1.x, pos1.y, pos2.x, pos2.y);
		Render::lineBresenham(&list, pos1.x, pos1.y, pos3.x, pos3.y);
		Render::lineBresenham(&list, pos2.x, pos2.y, pos3.x, pos3.y);

		for (int j = 0; j < list.size(); j++)
		{
			int x = (int)list[j].x;
			int y = (int)list[j].y;
			if ((x >= 0 && x < SCREEN_WIDTH) && (y >= 0 && y < SCREEN_HEIGHT))
				Singleton::pixels[(y * SCREEN_WIDTH) + x].isEnable = true;
		}
	}
}



CameraComponent::CameraComponent() : ViewM{ 4, 4 }, ProjectionMatrix{ 4, 4 }
{

}
MatrixXd CameraComponent::WorldToCamera()
{
	auto trans = gameObject->GetComponent<Transform>();
	MatrixXd m = trans->LocalToWorld();
	float3 r, u, f;
	r.setVector(m * float3(1, 0, 0).getVector());
	u.setVector(m * float3(0, 1, 0).getVector());
	f.setVector(m * float3(0, 0, 1).getVector());
	f * -1;
	return floatNM::M2M(floatNM{
		{r.x, u.x, f.x, trans->position.x},
		{r.y, u.y, f.y, trans->position.y},
		{r.z, u.z, f.z, trans->position.z},
		{0, 0, 0, 1}
		}).inverse();
}

void CameraComponent::Start()
{
	ProjectionMatrix =
	{
		{ (2 * n) / w, 0, 0, 0 },
		{ 0, (2 * n) / h, 0, 0 },
		{ 0, 0, (-(f + n)) / (f - n), (-1 * 2 * f * n) / (f - n) },
		{ 0, 0, -1, 0 }
	};
}
void CameraComponent::Update()
{
	auto* trans = gameObject->GetComponent<Transform>();
	float3 angle = trans->rotation;

	ProjectionMatrix =
	{
		{ (2 * n) / w, 0, 0, 0 },
		{ 0, (2 * n) / h, 0, 0 },
		{ 0, 0, (-(f + n)) / (f - n), (-1 * 2 * f * n) / (f - n) },
		{ 0, 0, -1, 0 }
	};
}
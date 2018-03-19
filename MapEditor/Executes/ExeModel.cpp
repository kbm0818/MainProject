#include "stdafx.h"
#include "ExeModel.h"
#include "../Environments/Sky.h"
#include "../Meshes/Plane.h"

ExeModel::ExeModel(ExecuteValues* values)
	: Execute(values)
{
	D3DDesc desc;
	D3D::GetDesc(&desc);

	sky = new Sky();
	plane = new Plane();
}

ExeModel::~ExeModel()
{
	SAFE_DELETE(plane);
	SAFE_DELETE(sky);
}

void ExeModel::Update()
{
	sky->Update(values->MainCamera);
	plane->Update();
}

void ExeModel::PreRender()
{
	
}

void ExeModel::Render()
{
	sky->Render();
	plane->Render();
}

void ExeModel::PostRender()
{
	sky->PostRender();
	plane->PostRender();
}

void ExeModel::ResizeScreen()
{
	
}

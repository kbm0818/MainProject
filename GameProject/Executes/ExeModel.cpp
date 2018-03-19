#include "stdafx.h"
#include "ExeModel.h"
#include "../Environments/Sky.h"
#include "../Environments/Terrain.h"

ExeModel::ExeModel(ExecuteValues* values)
	: Execute(values)
{
	D3DDesc desc;
	D3D::GetDesc(&desc);

	sky = new Sky();
	terrain = new Terrain();
}

ExeModel::~ExeModel()
{
	SAFE_DELETE(terrain);
	SAFE_DELETE(sky);
}

void ExeModel::Update()
{
	sky->Update(values->MainCamera);
	terrain->Update(values);
}

void ExeModel::PreRender()
{
	
}

void ExeModel::Render()
{
	sky->Render();
	terrain->Render();
}

void ExeModel::PostRender()
{
	sky->PostRender();
	terrain->PostRender();
}

void ExeModel::ResizeScreen()
{
	
}

#include "stdafx.h"
#include "Editor.h"
#include "./Cameras/CameraFactory.h"
#include "./Cameras/FirstPerson.h"

#include "./Environment/Sky.h"
#include "./Environment/Terrain.h"
#include "./Environment/Brush.h"

#include "./Utilities/String.h"

#include "Model/FbxLoader.h"


#define TERRAIN Editor::Get()->GetTerrain()
#define BRUSH Editor::Get()->GetTerrain()->GetBrush()
#define SKY Editor::Get()->GetSky()

Editor::Editor()
	: pickModelIndex(-1)
{
	D3DDesc desc;
	D3D::GetDesc(&desc);

	camera = CameraFactory::Create<FirstPerson>();
	camera->SetPerspective(desc.width, desc.height, (float)D3DX_PI * 0.25f, 0.1f, 1000.0f);
	camera->SetPosition(0, 5, -20);

	sky = new Sky();
	terrain = new Terrain();
	
	Model* temp = new Model();
	FbxLoader::Create("../../_Contents/Models/Campfire.fbx", &temp);

	AddModels(temp);

}

Editor::~Editor()
{
	for (size_t i = 0; i < models.size(); i++)
	{
		SAFE_DELETE(models[i]);
	}

	SAFE_DELETE(terrain);
	SAFE_DELETE(sky);
}

void Editor::BeginUpdate()
{
}

void Editor::Update()
{
	sky->Update(camera);
	terrain->Update(camera);

	for (size_t i = 0; i < models.size(); i++)
	{
		models[i]->Update();
	}
}

void Editor::EndUpdate()
{
	if (Keyboard::Get()->Press('W'))
		camera->MoveForward();
	else if (Keyboard::Get()->Press('S'))
		camera->MoveBackward();

	if (Keyboard::Get()->Press('A'))
		camera->MoveLeft();
	else if (Keyboard::Get()->Press('D'))
		camera->MoveRight();

	if (Keyboard::Get()->Press('Q'))
		camera->MoveDown();
	else if (Keyboard::Get()->Press('E'))
		camera->MoveUp();

	if (Mouse::Get()->Press(1))
	{
		D3DXVECTOR3 move = Mouse::Get()->GetMoveValue();

		camera->Rotate(D3DXVECTOR2(move.y, move.x));
	}
}

void Editor::PreRender()
{
}

void Editor::Render()
{
	sky->Render(camera);
	terrain->Render(camera);

	for (size_t i = 0; i < models.size(); i++)
	{
		models[i]->Render(camera);
	}
}

void Editor::PostRender()
{
}

/////////////////////SetShader///////////////////////////

DLL void Cs_SetSkyShader(const char* file)
{
	wstring temp = CA2CT(file);

	Editor::Get()->GetSky()->SetShader(temp);
}

DLL void Cs_SetTerrainShader(const char* file)
{
	wstring temp = CA2CT(file);

	Editor::Get()->GetTerrain()->SetShader(temp);
}

////////////////////////////////////////////////

///////////////////Sky DLL///////////////////////////
DLL void Cs_SetSkyCenterColor(int center)
{
	SKY->SetSkyBufferCenter(center);
}

DLL void Cs_SetSkyApexColor(int apex)
{
	SKY->SetSkyBufferApex(apex);
}
//////////////////////////////////////////////

///////////////////Terrain DLL///////////////////////////
DLL UINT Cs_GetTerrainWidth(const char* file)
{
	return TERRAIN->GetWidth();
}

DLL void Cs_SetTerrainWidth(const UINT width)
{
	return TERRAIN->SetWidth(width);
}

DLL UINT Cs_GetTerrainHeight(const char* file)
{
	return TERRAIN->GetHeight();
}

DLL void Cs_SetTerrainHeight(const UINT height)
{
	return TERRAIN->SetHeight(height);
}

DLL void Cs_SetTerrainSize(const UINT width, const UINT height)
{
	return TERRAIN->SetSize(width,height);
}

DLL UINT Cs_GetTerrainDiffuseColor()
{
	return TERRAIN->GetDiffuseColor();
}

DLL UINT Cs_GetTerrainAmbientColor()
{
	return TERRAIN->GetAmbientColor();
}

DLL void Cs_SetTerrainDiffuseColor(const int diffuse)
{
	return TERRAIN->SetDiffuseColor(diffuse);
}

DLL void Cs_SetTerrainAmbientColor(const int ambient)
{
	return TERRAIN->SetAmbientColor(ambient);
}

DLL void Cs_SetTerrainDiffuseFile(const char* file)
{
	wstring temp = CA2CT(file);

	TERRAIN->SetDiffuseFile(temp);
}

DLL void Cs_SetTerrainStage1File(const char* file)
{
	wstring temp = CA2CT(file);

	TERRAIN->SetStage1File(temp);
}

DLL void Cs_SetTerrainStage2File(const char* file)
{
	wstring temp = CA2CT(file);

	TERRAIN->SetStage2File(temp);
}

DLL void Cs_SetTerrainStage3File(const char* file)
{
	wstring temp = CA2CT(file);

	TERRAIN->SetStage3File(temp);
}

DLL void Cs_SetTerrainStage4File(const char* file)
{
	wstring temp = CA2CT(file);

	TERRAIN->SetStage4File(temp);
}

///////////////BRUSH DLL////////////////////////////////
DLL int Cs_GetTerrainBrushType()
{
	return (int)(BRUSH->GetBrushType());
}
DLL void Cs_SetTerrainBrushType(int type)
{
	BRUSH->SetBrushType(type);
}

DLL int Cs_GetTerrainBrushShape()
{
	return (int)(BRUSH->GetBrushShape());
}
DLL void Cs_SetTerrainBrushShape(int type)
{
	BRUSH->SetBrushShape(type);
}

DLL int Cs_GetTerrainBrushSplattingImage()
{
	return (int)(BRUSH->GetBrushSplattingImage());
}
DLL void Cs_SetTerrainBrushSplattingImage(int type)
{
	BRUSH->SetBrushSplattingImage(type);
}

DLL float Cs_GetTerrainBrushSize()
{
	return BRUSH->GetBrushSize();
}
DLL void Cs_SetTerrainBrushSize(float size)
{
	BRUSH->SetBrushSize(size);
}

DLL float Cs_GetTerrainBrushValue()
{
	return BRUSH->GetBrushValue();
}
DLL void Cs_SetTerrainBrushValue(float value)
{
	BRUSH->SetBrushValue(value);
}

DLL bool Cs_GetBrushHeightLock()
{
	return BRUSH->GetBrushHeightLock();
}
DLL void Cs_SetBrushHeightLock(bool lock)
{
	BRUSH->SetBrushHeightLock(lock);
}
//////////////Converter DLL//////////////////////////

DLL void Cs_ConverterFbxFileTobin(const char* file)
{
	//wstring path = CA2CT(file);
//	FbxConverter converter = FbxConverter();
//	converter.FbxToBin(path, FbxConverter::destModelsPath);
}

///////////////////Models DLL//////////////////////////////////
DLL int Cs_AddModels(int px, int py, const char* file)
{
	Camera* tempCamera = Editor::Get()->GetCamera();
	D3DXVECTOR3 position = BRUSH->GetPickPosition(px, py, tempCamera);

	if (position != D3DXVECTOR3(-1.0f, -1.0f, -1.0f))
	{
		string path = CA2CA(file);
		Model* temp = new Model();
		FbxLoader::Create(path, &temp);

		temp->SetTranslate(position);
	
		Editor::Get()->AddModels(temp);

		return Editor::Get()->GetModelsSize() - 1;
	}
	else
		return -1;
	
}

DLL void Cs_GetModelInfo(int index, Editor::ModelInfo info)
{
	Editor::ModelInfo temp = Editor::Get()->GetModelInfo(index);
	memccpy(&info, &temp, 0, sizeof(Editor::ModelInfo));
}

DLL UINT Cs_GetModelsSize()
{
	return Editor::Get()->GetModelsSize();
}

DLL int Cs_GetModelName(int index, char* file)
{
	string temp = Editor::Get()->GetModelName(index);
	strcpy(file, temp.c_str());

	return temp.length();
}

DLL LPCTSTR Cs_GetString()
{
	CString temString = CString(_T("test"));
	return (LPCTSTR)temString;
}

////////////////////////////////////////////////////////////



Editor* Editor::instance = NULL;

void Editor::Create()
{
	assert(instance == NULL);

	instance = new Editor();
}

void Editor::Delete()
{
	SAFE_DELETE(instance);
}

Editor * Editor::Get()
{
	assert(instance != NULL);

	return instance;
}

void Editor::AddModels(Model * model)
{
	models.push_back(model);
}

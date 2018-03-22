#include "stdafx.h"
#include "Program.h"
#include "Editor.h"

Program* Program::program = NULL;

void Program::Create(HWND handle, float width, float height)
{
	D3DDesc desc;
	desc.appName = L"";
	desc.instance = NULL;
	desc.bFullScreen = false;
	desc.bVsync = false;
	desc.color = 0xFF0000FF;
	desc.width = width;
	desc.height = height;
	desc.mainHandle = handle;
	D3D::SetDesc(desc);

	program = new Program();
}

void Program::Delete()
{
	SAFE_DELETE(program);
}

void Program::Initialize()
{
	Shader::Create();
	States::Create();
	BackBuffer::Create();

	Editor::Create();
}

void Program::Destroy()
{
	Editor::Delete();

	BackBuffer::Delete();
	States::Delete();
	Shader::Delete();
}

void Program::BeginUpdate()
{
	Time::Get()->Update();

	if (bFocus == true)
	{
		Mouse::Get()->Update();
		Keyboard::Get()->Update();
	}
	
	Editor::Get()->BeginUpdate();
}

void Program::Update()
{
	Editor::Get()->Update();
}

void Program::EndUpdate()
{
	Editor::Get()->EndUpdate();
}

void Program::PreRender()
{
	Editor::Get()->PreRender();
}

void Program::Render()
{
	BackBuffer::Get()->SetTarget();
	D3D::Get()->BeginScene();
	{
		Editor::Get()->Render();
	}
	D3D::Get()->EndScene();
}

void Program::PostRender()
{
	Editor::Get()->PostRender();
}

//////////////////////////////////////////////////

DLL void Cs_Create(HWND handle, float width, float height)
{
	Program::Create(handle, width, height);
	Program::Get()->Initialize();
}

DLL void Cs_Destroy()
{
	Program::Get()->Destroy();
	Program::Delete();
}

DLL void Cs_Update()
{
	Program::Get()->BeginUpdate();
	Program::Get()->Update();
	Program::Get()->EndUpdate();
}

DLL void Cs_Render()
{
	Program::Get()->PreRender();
	Program::Get()->Render();
	Program::Get()->PostRender();
}

DLL void Cs_WndProc(MSG message)
{
	Program::Get()->WndProc(message.message, message.wParam, message.lParam);
}

DLL void Cs_SetFocus(bool bFocus)
{
	Program::Get()->SetFocus(bFocus);
}
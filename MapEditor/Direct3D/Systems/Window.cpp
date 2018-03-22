#include "../stdafx.h"
#include "Window.h"

Window::Window()
{
	D3DDesc desc;
	D3D::GetDesc(&desc);


	D3D::Create();
	Keyboard::Create();
	Mouse::Create();
	Time::Create();
	Time::Get()->Start();
}

Window::~Window()
{
	Time::Delete();
	Mouse::Delete();
	Keyboard::Delete();
}

void Window::WndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	Mouse::Get()->InputProc(message, wParam, lParam);
}

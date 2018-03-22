#pragma once
#include "./Systems/Window.h"

class Program : public Window
{
public:
	static void Create(HWND handle, float width, float height);
	static void Delete();

	static Program* Get() { return program; }

	void SetFocus(bool bFocus) { this->bFocus = bFocus; }

	void Initialize();
	void Destroy();

	void BeginUpdate();
	void Update();
	void EndUpdate();

	void PreRender();
	void Render();
	void PostRender();

private:
	static Program* program;

	bool bFocus;
};
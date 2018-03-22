#pragma once

class Window
{
public:
	Window();
	~Window();

	void WndProc(UINT message, WPARAM wParam, LPARAM lParam);

	virtual void Initialize() = 0;
	virtual void Destroy() = 0;
	
	virtual void BeginUpdate() = 0;
	virtual void Update() = 0;
	virtual void EndUpdate() = 0;

	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
};
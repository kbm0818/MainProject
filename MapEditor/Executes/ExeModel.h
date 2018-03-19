#pragma once
#include "Execute.h"

class ExeModel : public Execute
{
public:
	ExeModel(ExecuteValues* values);
	~ExeModel();

	void Update();

	void PreRender();
	void Render();
	void PostRender();

	void ResizeScreen();

private:
	class Sky* sky;
	class Plane* plane;
};
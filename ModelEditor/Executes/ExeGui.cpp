#include "stdafx.h"
#include "ExeGui.h"

ExeGui::ExeGui(ExecuteValues* values)
	: Execute(values)
	, count(0)
	, bShowDemo(false)
	, bShowAnother(false)
{
	
}

ExeGui::~ExeGui()
{
}

void ExeGui::Update()
{
}

void ExeGui::PreRender()
{
}

void ExeGui::Render()
{
	
}

void ExeGui::PostRender()
{
	{
		ImGui::Text("Hello, world!");

		ImGui::Checkbox("Demo Window", &bShowDemo);
		ImGui::Checkbox("Another Window", &bShowAnother);

		if (ImGui::Button("Button"))
			count++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", count);

		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	if (bShowAnother == true)
	{
		ImGui::Begin("Another Window", &bShowAnother, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			bShowAnother = false;

		ImGui::End();
	}

	if (bShowDemo == true)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
		ImGui::ShowDemoWindow(&bShowDemo);
	}
}

void ExeGui::ResizeScreen()
{
}

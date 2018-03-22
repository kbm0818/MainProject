#pragma once

class Sky;
class Terrain;
class ModelScene;
class Editor
{
public:
	struct ModelInfo
	{
	public:
		D3DXVECTOR3 translate, rotate, scale;
		string modelName;

		ModelInfo(Model* model)
		{
			modelName = model->GetStringName();
			translate = model->GetTranslate();
			rotate = model->GetRotate();
			scale = model->GetScale();
		}

		ModelInfo()
		{
			modelName = "";
			translate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	};

public:
	static void Create();
	static void Delete();

	static Editor* Get();

	Sky* GetSky() { return sky; }
	Terrain* GetTerrain() { return terrain; }

	void AddModels(Model* model);

	UINT GetModelsSize()
	{
		return (UINT)(models.size());
	}

	ModelInfo GetModelInfo(int index)
	{
		if (index >= models.size())
			return ModelInfo();
		
		return ModelInfo(models[index]);
	}

	string GetModelName(int index)
	{
		if (index >= models.size())
			return "";

		return models[index]->GetStringName();
	}

	Camera* GetCamera() { return this->camera; }

private:
	friend class Program;

	static Editor* instance;
	
	Editor();
	~Editor();

	void BeginUpdate();
	void Update();
	void EndUpdate();

	void PreRender();
	void Render();
	void PostRender();

	Sky* sky;
	Terrain* terrain;

	vector<Model*> models;
	int pickModelIndex;

	Camera* camera;

};
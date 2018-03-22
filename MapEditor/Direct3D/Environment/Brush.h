#pragma once

class Terrain;
class BrushBuffer;
class GridBuffer;
class Brush
{
public:
	Brush(Terrain* target);
	~Brush();

	void Update(Camera* camera);

	enum class BrushType
	{
		HeightBrush = 0, SplattingBrush,
	};

	enum class BrushShape
	{
		Rectangle = 0, Circle,
	};

	enum class BrushSplattingImage
	{
		stage1 = 0, stage2, stage3, stage4,
	};

	Brush::BrushType GetBrushType();
	Brush::BrushShape GetBrushShape();
	Brush::BrushSplattingImage GetBrushSplattingImage();
	float GetBrushSize();
	float GetBrushValue();
	bool GetBrushHeightLock();

	void SetBrushType(int type);
	void SetBrushShape(int type);
	void SetBrushSplattingImage(int type);
	void SetBrushSize(float size);
	void SetBrushValue(float value);
	void SetBrushHeightLock(bool lock);

	void SetPSBuffer(int index);

	void SetGridThickness(float value);
	void SetGridSpace(float value);

	void SetPSGridBuffer(int index);

	D3DXVECTOR3 GetPickPosition(Camera* camera);
	D3DXVECTOR3 GetPickPosition(float px, float py, Camera* camera);

private:
	D3DXVECTOR3 CheckMouseIndex(Camera* camera);
	D3DXVECTOR3 CheckMouseIndex(float px, float py, Camera* camera);

	void AdjustHeight(D3D11_BOX* box, D3DXVECTOR3& position);

private:
	BrushType brushType;
	BrushShape brushShape;
	BrushSplattingImage brushSplattingImage;

	float brushSize; 
	float brushValue;
	bool brushHeightLock;

	BrushBuffer* brushBuffer;
	GridBuffer* gridBuffer;
	
	typedef VertexColorTexture2Normal VertexType;

	Terrain* target;
};
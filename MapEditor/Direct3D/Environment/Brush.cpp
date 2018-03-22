#include "../stdafx.h"
#include "Terrain.h"
#include "Brush.h"
#include "BrushBuffer.h"
#include "GridBuffer.h"

Brush::Brush(Terrain * target)
	:target(target)
	, brushType(BrushType::HeightBrush), brushShape(BrushShape::Rectangle)
	, brushSize(4.0f), brushValue(10.0f), brushSplattingImage(BrushSplattingImage::stage1)
	, brushHeightLock(false)
{
	brushBuffer = new BrushBuffer();
	brushBuffer->SetBrushSize(brushSize);
	brushBuffer->SetBrushShaper((float)brushShape);

	gridBuffer = new GridBuffer();
	gridBuffer->SetThickness(1.0f);
	gridBuffer->SetGridSpace(10.0f);
}

Brush::~Brush()
{
	SAFE_DELETE(gridBuffer);
	SAFE_DELETE(brushBuffer);
}

void Brush::Update(Camera* camera)
{
		D3DXVECTOR3 position = CheckMouseIndex(camera);
		if (position.x > -1.0f && position.y > -1.0f && position.z > -1.0f)
		{
			brushBuffer->SetPickPosition(position);

			if (Mouse::Get()->Press(0))
			{
				D3D11_BOX box;
				box.left = (UINT)position.x - (UINT)brushSize;
				box.top = (UINT)position.z + (UINT)brushSize;
				box.right = (UINT)position.x + (UINT)brushSize;
				box.bottom = (UINT)position.z - (UINT)brushSize;

				if (box.left < 0 || box.left > target->width) box.left = 0;
				if (box.top >= target->height) box.top = target->height;
				if (box.right >= target->width) box.right = target->width;
				if (box.bottom < 0 || box.bottom > target->height) box.bottom = 0;

				AdjustHeight(&box, position);
			}
		}
	
}

Brush::BrushType Brush::GetBrushType()
{
	return brushType;
}

Brush::BrushShape Brush::GetBrushShape()
{
	return brushShape;
}

Brush::BrushSplattingImage Brush::GetBrushSplattingImage()
{
	return brushSplattingImage;
}

float Brush::GetBrushSize()
{
	return brushSize;
}

float Brush::GetBrushValue()
{
	return brushValue;
}

bool Brush::GetBrushHeightLock()
{
	return brushHeightLock;
}

void Brush::SetBrushType(int type)
{
	brushType = (BrushType)type;
}

void Brush::SetBrushShape(int type)
{
	brushShape = (BrushShape)type;
	brushBuffer->SetBrushShaper((float)brushShape);
}

void Brush::SetBrushSplattingImage(int type)
{
	brushSplattingImage = (BrushSplattingImage)type;
}

void Brush::SetBrushSize(float size)
{
	brushSize = size;
	brushBuffer->SetBrushSize(brushSize);
}

void Brush::SetBrushValue(float value)
{
	brushValue = value;
}

void Brush::SetBrushHeightLock(bool lock)
{
	brushHeightLock = lock;
}

void Brush::SetPSBuffer(int index)
{
	brushBuffer->SetPSBuffer(index);
}

void Brush::SetGridThickness(float value)
{
	gridBuffer->SetThickness(value);
}

void Brush::SetGridSpace(float value)
{
	gridBuffer->SetGridSpace(value);
}

void Brush::SetPSGridBuffer(int index)
{
	gridBuffer->SetPSBuffer(index);
}

D3DXVECTOR3 Brush::GetPickPosition(Camera * camera)
{
	D3DXVECTOR3 position = CheckMouseIndex(camera);
	return position;
}

D3DXVECTOR3 Brush::GetPickPosition(float px, float py, Camera * camera)
{
	D3DXVECTOR3 position = CheckMouseIndex(px, py, camera);
	return position;
}

D3DXVECTOR3 Brush::CheckMouseIndex(Camera* camera)
{
	D3DXVECTOR3 origin, direction;
	camera->GetRay(&origin, &direction, target->world);

	for (UINT z = 0; z < target->height; z++)
	{
		for (UINT x = 0; x < target->width; x++)
		{
			UINT index0 = (target->width + 1) * z + x;
			UINT index1 = (target->width + 1) * (z + 1) + x;
			UINT index2 = (target->width + 1) * z + x + 1;
			UINT index3 = (target->width + 1) * (z + 1) + x + 1;

			D3DXVECTOR3 v0 = target->vertexData[index0].position;
			D3DXVECTOR3 v1 = target->vertexData[index1].position;
			D3DXVECTOR3 v2 = target->vertexData[index2].position;
			D3DXVECTOR3 v3 = target->vertexData[index3].position;

			float u, v, distance;

			BOOL check;
			check = D3DXIntersectTri
			(
				&v0, &v1, &v2
				, &origin, &direction
				, &u, &v, &distance
			);
			if (check == TRUE)
			{
				v0 += u * (v1 - v0) + v * (v2 - v0);
				return v0;
			}

			check = D3DXIntersectTri
			(
				&v3, &v1, &v2
				, &origin, &direction
				, &u, &v, &distance
			);
			if (check == TRUE)
			{
				v3 += u * (v1 - v3) + v * (v2 - v3);
				return v3;
			}
		}//for(x)
	}//for(y)
	
	return D3DXVECTOR3(-1, -1, -1);
}

D3DXVECTOR3 Brush::CheckMouseIndex(float px, float py, Camera * camera)
{
	D3DXVECTOR3 origin, direction;
	camera->GetRay(px, py, &origin, &direction, target->world);

	for (UINT z = 0; z < target->height; z++)
	{
		for (UINT x = 0; x < target->width; x++)
		{
			UINT index0 = (target->width + 1) * z + x;
			UINT index1 = (target->width + 1) * (z + 1) + x;
			UINT index2 = (target->width + 1) * z + x + 1;
			UINT index3 = (target->width + 1) * (z + 1) + x + 1;

			D3DXVECTOR3 v0 = target->vertexData[index0].position;
			D3DXVECTOR3 v1 = target->vertexData[index1].position;
			D3DXVECTOR3 v2 = target->vertexData[index2].position;
			D3DXVECTOR3 v3 = target->vertexData[index3].position;

			float u, v, distance;

			BOOL check;
			check = D3DXIntersectTri
			(
				&v0, &v1, &v2
				, &origin, &direction
				, &u, &v, &distance
			);
			if (check == TRUE)
			{
				v0 += u * (v1 - v0) + v * (v2 - v0);
				return v0;
			}

			check = D3DXIntersectTri
			(
				&v3, &v1, &v2
				, &origin, &direction
				, &u, &v, &distance
			);
			if (check == TRUE)
			{
				v3 += u * (v1 - v3) + v * (v2 - v3);
				return v3;
			}
		}//for(x)
	}//for(y)

	return D3DXVECTOR3(-1, -1, -1);
}

void Brush::AdjustHeight(D3D11_BOX* box, D3DXVECTOR3& position)
{
	for (UINT z = box->bottom; z <= box->top; z++)
	{
		for (UINT x = box->left; x <= box->right; x++)
		{
			UINT index = z * (target->width + 1) + x;
			
			switch (brushShape)
			{
			case BrushShape::Rectangle:
				if (brushType == BrushType::HeightBrush)
				{
					if (brushHeightLock == true)
						target->vertexData[index].position.y = brushValue * 0.01f;
					else
						target->vertexData[index].position.y += brushValue * 0.01f;
				}
				else
				{
					switch (brushSplattingImage)
					{
					case BrushSplattingImage::stage1:
						target->vertexData[index].color.r += brushValue* 0.01f;
						break;
					case BrushSplattingImage::stage2:
						target->vertexData[index].color.g += brushValue* 0.01f;
						break;
					case BrushSplattingImage::stage3:
						target->vertexData[index].color.b += brushValue* 0.01f;
						break;
					case BrushSplattingImage::stage4:
						target->vertexData[index].color.a += brushValue* 0.01f;
						break;
					}
				}
				break;
			case BrushShape::Circle:
				D3DXVECTOR2 temp = D3DXVECTOR2(position.x, position.z) - D3DXVECTOR2(target->vertexData[index].position.x, target->vertexData[index].position.z);
				float length = D3DXVec2Length(&temp);

				if (length <= brushSize)
				{
					if (brushType == BrushType::HeightBrush)
					{
						if (brushHeightLock == true)
						{
							target->vertexData[index].position.y = brushValue * cos(length / brushSize) * 0.01f;
						}
						else
						{
							target->vertexData[index].position.y += brushValue * cos(length / brushSize) * 0.01f;
						}
					}
					else
					{
						switch (brushSplattingImage)
						{
						case BrushSplattingImage::stage1:
							target->vertexData[index].color.r += brushValue* 0.01f;
							break;
						case BrushSplattingImage::stage2:
							target->vertexData[index].color.g += brushValue* 0.01f;
							break;
						case BrushSplattingImage::stage3:
							target->vertexData[index].color.b += brushValue* 0.01f;
							break;
						case BrushSplattingImage::stage4:
							target->vertexData[index].color.a += brushValue* 0.01f;
							break;
						}
					}
				}
				break;
			}
		}
	}

	target->CalcNormalVector();

	D3D::GetDC()->UpdateSubresource
	(
		target->vertexBuffer
		, 0
		, NULL
		, target->vertexData
		, sizeof(VertexType) * target->vertexCount
		, 0
	);
}
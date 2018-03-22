#include "../stdafx.h"
#include "Converter.h"
#include "ConverterScene.h"
#include "ConverterPart.h"
#include "ConverterMaterial.h"
#include "ConverterBuffer.h"
#include "ConverterBoneWeights.h"
#include "ConverterAnimation.h"
#include "ConverterAnimationKeyFrames.h"
#include "ConverterAnimationController.h"


Converter::Converter(ConverterScene* ConverterScene)
	:ConverterScene(ConverterScene)
{
}

Converter::Converter(ConverterScene* ConverterScene, wstring name)
	: ConverterScene(ConverterScene), name(name)
{
	D3DXMatrixIdentity(&absoluteTransform);
	D3DXMatrixIdentity(&matGeometricOffset);
	D3DXMatrixIdentity(&matAnimationTransform);
}

Converter::Converter(const Converter & otherConverter)
{
	ConverterScene = otherConverter.ConverterScene;

	name = otherConverter.name;

	absoluteTransform = otherConverter.absoluteTransform;
	matGeometricOffset = otherConverter.matGeometricOffset;
	matAnimationTransform = otherConverter.matAnimationTransform;

	size_t partsCount = otherConverter.parts.size();
	parts.reserve(partsCount);
	for (size_t i = 0; i < partsCount; i++)
	{
		ConverterPart* part = new ConverterPart(*(otherConverter.parts[i]));
		part->SetConverter(this);
		parts.push_back(part);
	}

	//ConverterBuffer = (ConverterBuffer != NULL) ? otherConverter.ConverterBuffer : NULL;

	size_t animationKeyFramesCount = otherConverter.animationKeyFrames.size();

	map<wstring, ConverterAnimationKeyFrames*>::const_iterator iter;
	for (iter = otherConverter.animationKeyFrames.begin(); iter != otherConverter.animationKeyFrames.end(); ++iter)
	{
		wstring tempName = iter->first;
		ConverterAnimationKeyFrames tempKeyFrames = *(iter->second);

		animationKeyFrames.insert({ tempName, new ConverterAnimationKeyFrames(tempKeyFrames) });
	}
}

Converter::~Converter()
{
	map<wstring, ConverterAnimationKeyFrames*>::iterator iter;
	for (iter = animationKeyFrames.begin(); iter != animationKeyFrames.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	for (size_t i = 0; i < parts.size(); i++)
		SAFE_DELETE(parts[i]);
}

void Converter::Update(bool isAnimation)
{
	for each(ConverterPart* part in parts)
		part->Update(isAnimation);
}

void Converter::Render()
{
	for each(ConverterPart* part in parts)
		part->Render();
}

//void Converter::SetConverterBuffer(ConverterBuffer * ConverterBuffer)
//{
//	this->ConverterBuffer = ConverterBuffer; 
//	
//	for (size_t i = 0; i < parts.size(); i++)
//		parts[i]->SetConverterBuffer(ConverterBuffer);
//}

void Converter::AddAnimationKeyFrames(ConverterAnimationKeyFrames * animationKeyFrames)
{
	this->animationKeyFrames.insert({ animationKeyFrames->GetAnimationName(), animationKeyFrames });
}

ConverterAnimationKeyFrames * Converter::GetAnimationKeyFrames(wstring animationName)
{
	map<wstring, ConverterAnimationKeyFrames*>::iterator iter;
	for (iter = animationKeyFrames.begin(); iter != animationKeyFrames.end(); ++iter)
	{
		if (iter->first == animationName)
			return iter->second;
	}

	assert(false); // map에 animationName에 하당하는 Key가 없는 경우

	return NULL;
}

void Converter::AddVertex(ConverterMaterial * material, D3DXVECTOR3 position, D3DXVECTOR3 normal, D3DXVECTOR2 uv, const ConverterBoneWeights& boneWeights)
{
	bool isNew = true;

	ConverterPart* part = NULL;
	for (size_t i = 0; i < parts.size(); i++)
	{
		part = parts[i];

		if (material == part->GetMaterial())
		{
			part->AddVertex(position, normal, uv, boneWeights);
			isNew = false;
		}
	}
	 
	if (isNew == true)
	{
		//part = new ConverterPart(this, material, ConverterBuffer);
		part = new ConverterPart(this, material);
		part->AddVertex(position, normal, uv, boneWeights);
		
		parts.push_back(part);
	}
}

void Converter::CreateData()
{
	for each(ConverterPart* part in parts)
		part->CreateData();
}

void Converter::CreateBuffer()
{
	for each(ConverterPart* part in parts)
		part->CreateBuffer();
}

void Converter::Export(BinaryWriter * bw)
{
	bw->Write(name);

	bw->Write(absoluteTransform);
	bw->Write(matGeometricOffset);
	bw->Write(matAnimationTransform);

	bw->Write(parts);

	bw->Write(animationKeyFrames);
}

void Converter::Import(BinaryReader * br)
{
	name = br->WString();

	absoluteTransform = br->Matrix();
	matGeometricOffset = br->Matrix();
	matAnimationTransform = br->Matrix();

	UINT partsCount = br->UInt();
	parts.clear();
	parts.reserve(partsCount);
	for (size_t i = 0; i < partsCount; i++)
	{
		ConverterPart* ConverterPart = new ConverterPart(this);
		ConverterPart->Import(br);
		parts.push_back(ConverterPart);
	}

	animationKeyFrames.clear();
	UINT animationKeyFramesCount = br->UInt();
	for (size_t i = 0; i < animationKeyFramesCount; i++)
	{
		wstring name = br->WString();
		ConverterAnimationKeyFrames* ConverterAnimationKeyFrames = new ConverterAnimationKeyFrames();
		ConverterAnimationKeyFrames->Import(br);
		animationKeyFrames.insert(make_pair(name, ConverterAnimationKeyFrames));
	}
}

void Converter::UpdateAnimation(ConverterAnimationController * animationController)
{
	if (animationController != NULL)
	{
		ConverterAnimation* animation = animationController->GetCurrentAnimation();

		if (animation != NULL)
		{
			ConverterAnimationKeyFrames* keyFrames = NULL;
			map<wstring, ConverterAnimationKeyFrames*>::iterator iter;
			for (iter = animationKeyFrames.begin(); iter != animationKeyFrames.end(); ++iter)
			{
				if (iter->first == animation->GetName())
				{
					keyFrames = iter->second;

					break;
				}
			}
			
			if (keyFrames != NULL)
			{
				int keyFrame = animationController->GetCurrentKeyFrame();
				matAnimationTransform = keyFrames->GetKeyFrameTransform(keyFrame);
				
				return;
			}
		}
	}

	D3DXMatrixIdentity(&matAnimationTransform);
}

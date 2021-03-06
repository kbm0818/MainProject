#include "../stdafx.h"
#include "ConverterBoneWeights.h"

const UINT ConverterBoneWeights::MaxBonesPerVertex = 4;
const UINT ConverterBoneWeights::MaxBonesPerMax = 100;

ConverterBoneWeights::ConverterBoneWeights()
	: sumWeight(0.0f)
{

}

ConverterBoneWeights::ConverterBoneWeights(const ConverterBoneWeights & otherConverterBoneWeights)
{
	this->sumWeight = otherConverterBoneWeights.sumWeight;

	boneWeights.clear();
	boneWeights.assign(otherConverterBoneWeights.boneWeights.begin(), otherConverterBoneWeights.boneWeights.end());
}

ConverterBoneWeights::~ConverterBoneWeights()
{
}

void ConverterBoneWeights::AddBoneWeight(int boneIndex, float boneWeight)
{
	if (boneWeight <= 0.0f)
		return;

	sumWeight += boneWeight;

	// 중복체크
	bool isAdded = false;
	std::vector<std::pair<int, float>>::iterator it;
	for (it = boneWeights.begin(); it != boneWeights.end(); it++)
	{
		if (boneWeight > it->second)
		{
			boneWeights.insert(it, std::make_pair(boneIndex, boneWeight));
			isAdded = true;
			break;
		}
	}

	if (isAdded == false)
		boneWeights.push_back(make_pair(boneIndex, boneWeight));
}

void ConverterBoneWeights::AddBoneWeight(std::pair<int, float> boneWeightPair)
{
	AddBoneWeight(boneWeightPair.first, boneWeightPair.second);
}

void ConverterBoneWeights::AddBoneWeights(const ConverterBoneWeights & boneWeights)
{
	for (int i = 0; i < boneWeights.GetBoneWeightCount(); ++i)
	{
		AddBoneWeight(boneWeights.GetBoneWeight(i));
	}
}

/********************************************************************************
 @brief
 Vertex에 영향을 주는 Bone의 수가 최대치를 넘지 않도록 조정
********************************************************************************/
void ConverterBoneWeights::Validate()
{
	sumWeight = 0.0f;
	int i = 0;

	vector<pair<int, float>>::iterator it = boneWeights.begin();
	while (it != boneWeights.end())
	{
		// Bone Weight의 최대치를 넘어가면 최대치 이상의 BoneWeight 삭제
		if (i >= MaxBonesPerVertex)
		{
			it = boneWeights.erase(it);
		}
		else
		{
			// 최대치 안의 Weight값들만 합산
			sumWeight += it->second;

			++i; ++it;
		}
	}
}

/********************************************************************************
 @brief
 각 BoneWeight값을 총 BoneWeight의 합에 대한 비율로 변환
 모든 BoneWeight의 값의 합이 1이 되도록 설정
********************************************************************************/
void ConverterBoneWeights::Normalize()
{
	Validate(); //Bone Weight의 수가 유효하도록 설정
	
	float fScale = 1.0f / sumWeight;
	std::vector<std::pair<int, float>>::iterator it = boneWeights.begin();
	
	while (it != boneWeights.end())
	{
		it->second *= fScale;

		++it;
	}
}

/********************************************************************************
 @brief
 모든 Bone Weight 정보를 하나의 Blend Weights Class 취합하여 반환
********************************************************************************/
ConverterBlendWeights ConverterBoneWeights::GetBlendWeights()
{
	ConverterBlendWeights blendWeights;

	int i = 0;
	vector<pair<int, float>>::iterator it = boneWeights.begin();
	while (it != boneWeights.end())
	{
		blendWeights.SetBlendWeight(i, it->first, it->second);
		++i;
		++it;

		if (i >= MaxBonesPerVertex)
			break;
	}

	return blendWeights;
}
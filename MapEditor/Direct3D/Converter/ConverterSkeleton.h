#pragma once
#include "../Utility/BinaryInputOutputHandler.h"
#include "ConverterEnums.h"

/********************************************************************************
 @brief
 모든 Skeleton Bone의 정보를 계산하여 저장하는 Class

 각 Bone을 (Name, Index)로 구분하여 입출력

********************************************************************************/

class ConverterSkeletonBone;
class ConverterAnimationController;
class ConverterSkeleton : public BinaryInputOutputHandler
{
public:
	ConverterSkeleton();
	ConverterSkeleton(const ConverterSkeleton& otherSkeleton);
	~ConverterSkeleton();

	void AddSkeletonBone(ConverterSkeletonBone* skeletonBone);
	ConverterSkeletonBone* FindBone(wstring boneName);
	int FindBoneIndex(wstring boneName);

	D3DXMATRIX& GetBoneAnimationTransform(int boneIdx);

	ConverterSkeletonBone* GetSkeletonBone(int index);
	const vector<pair<wstring, ConverterSkeletonBone *>>& GetSkeletonBones() { return skeletonBones; }
	
	D3DXMATRIX* GetSkinTransforms() { return skinTransforms; }

	int GetBoneCount() { return boneCount; }

	void AddAnimationFromOtherSkeleton(wstring srcAnimName, wstring dstAnimName, ConverterSkeleton& srcSkeleton);

	void UpdateAnimation(ConverterAnimationController* animationController); ///매 프레임마다 모든 본의 Transform 정보를 갱신

	virtual void Export(BinaryWriter* bw);
	virtual void Import(BinaryReader* br);

private:
	void BuildBoneTransforms(ConverterAnimationController* animationController, wstring animationName, RootType rootType);

	int boneCount;

	typedef pair<wstring, ConverterSkeletonBone *> Pair;
	vector<Pair> skeletonBones;

	D3DXMATRIX* skinTransforms; /// 최종적으로 Vertex에 적용될 Transform Matrix 배열
	D3DXMATRIX* boneAnimationTransforms; /// 각 Bone의 Transform Matrix 배열
	 
};

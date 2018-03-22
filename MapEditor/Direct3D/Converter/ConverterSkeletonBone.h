#pragma once
#include "../Utility/BinaryInputOutputHandler.h"

/********************************************************************************
 @brief
 Skeleton Bone의 정보를 저장하는 Class

 Bone의 Name, Index를 저장
 Bone의 Animation 별 모든 ConverterAnimationKeyFrames를 저장

 BindPoseTransform 
	=> Root Space(Binding Space or Local Space) 좌표계에서 Bone의 Tranfrom

 BoneReferenceTransform =>
	=> Bone Space 좌표계 기준의 Cluster의 Transfrom
********************************************************************************/
class ConverterAnimationKeyFrames;
class ConverterSkeletonBone : public BinaryInputOutputHandler
{
public:
	ConverterSkeletonBone();
	ConverterSkeletonBone(wstring name, int parentBoneIndex);
	ConverterSkeletonBone(const ConverterSkeletonBone& otherSkeletonBone);
	~ConverterSkeletonBone();

	void AddAnimationKeyFrames(ConverterAnimationKeyFrames* keyFrames);
	
	void SetBindPoseTransform(const D3DXMATRIX& matBindPoseTransform);
	void SetBoneReferenceTransform(const D3DXMATRIX& matBoneReferenceTransform);

	ConverterAnimationKeyFrames* GetAnimationKeyFrames(wstring animationName);

	const D3DXMATRIX& GetBindPoseTransform() 
	{ 
		return matBindPoseTransform; 
	}

	const D3DXMATRIX& GetInvBindPoseTransform() 
	{ 
		return matInvBindPoseTransform; 
	}

	const D3DXMATRIX& GetBoneReferenceTransform() 
	{ 
		return matBoneReferenceTransform; 
	}

	const D3DXMATRIX& GetInvBoneReferenceTransform() 
	{ 
		return matInvBoneReferenceTransform; 
	}

	wstring GetName() { return name; }
	int GetParentBoneIndex() { return parentBoneIndex; }

	virtual void Export(BinaryWriter* bw);
	virtual void Import(BinaryReader* br);

private:

	wstring name;

	D3DXMATRIX matBindPoseTransform;
	D3DXMATRIX matInvBindPoseTransform;
	D3DXMATRIX matBoneReferenceTransform;
	D3DXMATRIX matInvBoneReferenceTransform;

	int parentBoneIndex;

	map<wstring, ConverterAnimationKeyFrames *> animationKeyFrames;
};
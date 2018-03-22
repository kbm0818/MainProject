#include "../stdafx.h"
#include "ConverterAnimationKeyFrames.h"

ConverterAnimationKeyFrames::ConverterAnimationKeyFrames(wstring animationName)
	: animationName(animationName)
{
	
}

ConverterAnimationKeyFrames::ConverterAnimationKeyFrames(ConverterAnimationKeyFrames & other)
{
	animationName = other.animationName;
	keyFrames = other.keyFrames;
}

ConverterAnimationKeyFrames::~ConverterAnimationKeyFrames()
{

}

void ConverterAnimationKeyFrames::AddKeyFrame(const D3DXMATRIX & transform)
{
	keyFrames.push_back(make_pair(transform, ConverterAnimationQuaternionKeyFrame(transform)));
}

wstring ConverterAnimationKeyFrames::GetAnimationName()
{
	return animationName;
}

void ConverterAnimationKeyFrames::SetAnimationName(wstring animationName)
{
	this->animationName = animationName;
}

const D3DXMATRIX & ConverterAnimationKeyFrames::GetKeyFrameTransform(int keyFrame) const
{
	return keyFrames[keyFrame].first;
}

const ConverterAnimationQuaternionKeyFrame & ConverterAnimationKeyFrames::GetQuaternionKeyFrame(int keyFrame) const
{
	return keyFrames[keyFrame].second;
}

void ConverterAnimationKeyFrames::Export(BinaryWriter * bw)
{
	bw->Write(animationName);

	UINT keyFramesCount = keyFrames.size();
	bw->Write(keyFramesCount);
	for (size_t i = 0; i < keyFramesCount; i++)
	{
		bw->Write(keyFrames[i].first);
		keyFrames[i].second.Export(bw);
	}
}

void ConverterAnimationKeyFrames::Import(BinaryReader * br)
{
	animationName = br->WString();
	
	UINT keyFramesCount = br->UInt();
	keyFrames.clear();
	keyFrames.reserve(keyFramesCount);
	for (size_t i = 0; i < keyFramesCount; i++)
	{
		D3DXMATRIX transform = br->Matrix();
		ConverterAnimationQuaternionKeyFrame quternion;
		quternion.Import(br);
		keyFrames.push_back(make_pair(transform, quternion));
	}
}

void ConverterAnimationQuaternionKeyFrame::Export(BinaryWriter * bw)
{
	bw->Write(q);
	bw->Write(translation);
}

void ConverterAnimationQuaternionKeyFrame::Import(BinaryReader * br)
{
	q = br->Quaternion();
	translation = br->Vector3();
}

#include "../stdafx.h"
#include "ConverterAnimation.h"

ConverterAnimation::ConverterAnimation() 
	: name(L""), keyFrameCount(0), frameRate(0), defaultFrameRate(0)
	, rootType(RootType::RootType_Default), isLoop(true), isEnd(false)
{
}

ConverterAnimation::ConverterAnimation(wstring name, int frameCount, float defaultFrameRate)
	: name(name), keyFrameCount(frameCount), frameRate(defaultFrameRate), defaultFrameRate(defaultFrameRate)
	, rootType(RootType::RootType_Default), isLoop(true), isEnd(false)
{
	
}

ConverterAnimation::~ConverterAnimation()
{
}

void ConverterAnimation::Export(BinaryWriter * bw)
{
	bw->Write(name);

	bw->Write((int)rootType);

	bw->Write(keyFrameCount);
	bw->Write(frameRate);
	bw->Write(defaultFrameRate);

	bw->Write(isLoop);
	bw->Write(isEnd);
}

void ConverterAnimation::Import(BinaryReader * br)
{
	name = br->WString();

	rootType  = (RootType)br->Int();

	keyFrameCount = br->Int();
	frameRate = br->Float();
	defaultFrameRate = br->Float();

	isLoop = br->Bool();
	isEnd = br->Bool();
}

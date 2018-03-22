#pragma once
#include "BinaryInputOutputHandler.h"

class ConverterScene;
class ConverterPart;
class ConverterMaterial;
class ConverterBuffer;
class ConverterBoneWeights;
class ConverterAnimationKeyFrames;
class ConverterAnimationController;

class Converter : public BinaryInputOutputHandler
{
public:
	Converter(ConverterScene* ConverterScene);
	Converter(ConverterScene* ConverterScene, wstring name);
	Converter(const Converter& otherConverter);
	~Converter();

	void Update(bool isAnimation);
	void UpdateAnimation(ConverterAnimationController* animationController);
	void Render();

	ConverterScene* GetConverterScene() { return ConverterScene; }
	
	wstring GetName() { return name; }

	//void SetConverterBuffer(ConverterBuffer* ConverterBuffer);

	void SetGeometricOffset(const D3DXMATRIX& matGeometricOffset) { this->matGeometricOffset = matGeometricOffset; }
	D3DXMATRIX GetGeometricOffset() { return matGeometricOffset; }

	D3DXMATRIX GetAbsoluteTransform() { return absoluteTransform; }
	void SetAbsoluteTransform(const D3DXMATRIX& absoluteTransform) { this->absoluteTransform = absoluteTransform; }

	D3DXMATRIX GetAnimationTransform() { return matAnimationTransform; };
	void SetAnimationTransform(const D3DXMATRIX& matAnimationTransform) { this->matAnimationTransform = matAnimationTransform; }

	void AddVertex(ConverterMaterial * material, D3DXVECTOR3 position, D3DXVECTOR3 normal, D3DXVECTOR2 uv, const ConverterBoneWeights& boneWeights);
	void CreateData();
	void CreateBuffer();

	virtual void Export(BinaryWriter* bw);
	virtual void Import(BinaryReader* br);

private:
	ConverterScene* ConverterScene;

	wstring name;

	D3DXMATRIX absoluteTransform;
	D3DXMATRIX matGeometricOffset;
	D3DXMATRIX matAnimationTransform;

	vector<ConverterPart *> parts;
};
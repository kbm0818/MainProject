#include "../stdafx.h"
#include "ModelMaterial.h"

ModelMaterial::ModelMaterial(int number, FbxSurfaceMaterial* material)
	: number(number)
	, ambient(0, 0, 0, 1), diffuse(0, 0, 0, 1), specular(0, 0, 0, 1), emissive(0, 0, 0, 1)
	, shininess(0.0f)
	, ambientFile(""), diffuseFile(""), specularFile(""), emissiveFile(""), normalMapFile("")
	, ambientView(NULL), diffuseView(NULL), specularView(NULL), emissiveView(NULL), normalMapView(NULL)
{
	ambient = GetProperty(material, FbxSurfaceMaterial::sAmbient, FbxSurfaceMaterial::sAmbientFactor, &ambientFile);
	diffuse = GetProperty(material, FbxSurfaceMaterial::sDiffuse, FbxSurfaceMaterial::sDiffuseFactor, &diffuseFile);
	specular = GetProperty(material, FbxSurfaceMaterial::sSpecular, FbxSurfaceMaterial::sSpecularFactor, &specularFile);
	emissive = GetProperty(material, FbxSurfaceMaterial::sEmissive, FbxSurfaceMaterial::sEmissiveFactor, &emissiveFile);
	GetProperty(material, FbxSurfaceMaterial::sNormalMap, &normalMapFile);

	FbxProperty shininessProp = material->FindProperty(FbxSurfaceMaterial::sShininess);
	if (shininessProp.IsValid() == true)
		shininess = (float)shininessProp.Get<FbxDouble>();

	
	CreateView(ambientFile, &ambientView);
	CreateView(diffuseFile, &diffuseView);
	CreateView(specularFile, &specularView);
	CreateView(emissiveFile, &emissiveView);
	CreateView(normalMapFile, &normalMapView);
}

ModelMaterial::ModelMaterial()
{
}

ModelMaterial::~ModelMaterial()
{
	SAFE_RELEASE(ambientView);
	SAFE_RELEASE(diffuseView);
	SAFE_RELEASE(specularView);
	SAFE_RELEASE(emissiveView);
	SAFE_RELEASE(normalMapView);
}

void ModelMaterial::CreateView(string path, ID3D11ShaderResourceView ** view)
{
	if (path.length() < 1) return;

	DWORD fileValue = GetFileAttributesA(path.c_str());
	if (fileValue < 0xFFFFFFFF)
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFileA
		(
			D3D::GetDevice()
			, path.c_str()
			, NULL
			, NULL
			, view
			, NULL
		);
		assert(SUCCEEDED(hr));
	}
}

void ModelMaterial::OpenBinary(BinaryReader * reader)
{
	number = reader->UInt();
	ambient = reader->Color4f();
	emissive = reader->Color4f();
	diffuse = reader->Color4f();
	specular = reader->Color4f();
	shininess = reader->Float();

	ambientFile = reader->String();
	emissiveFile = reader->String();
	diffuseFile = reader->String();
	specularFile = reader->String();
	normalMapFile = reader->String();

	CreateView(ambientFile, &ambientView);
	CreateView(emissiveFile, &emissiveView);
	CreateView(diffuseFile, &diffuseView);
	CreateView(specularFile, &specularView);
	CreateView(normalMapFile, &normalMapView);
}

void ModelMaterial::SaveBinary(BinaryWriter * writer)
{
	writer->Write(number);
	writer->Write(ambient);
	writer->Write(emissive);
	writer->Write(diffuse);
	writer->Write(specular);
	writer->Write(shininess);

	writer->Write(ambientFile);
	writer->Write(emissiveFile);
	writer->Write(diffuseFile);
	writer->Write(specularFile);
	writer->Write(normalMapFile);
}

D3DXCOLOR ModelMaterial::GetProperty(FbxSurfaceMaterial * material, const char * name, const char * factorName, string * textureName)
{
	D3DXCOLOR color(0, 0, 0, 1);

	FbxProperty prop = material->FindProperty(name);
	FbxProperty factorProp = material->FindProperty(factorName);
	if (prop.IsValid() == true && factorProp.IsValid() == true)
	{
		FbxDouble3 temp = prop.Get<FbxDouble3>();
		double factor = factorProp.Get<FbxDouble>();

		if (factor != 1.0)
		{
			temp[0] *= factor;
			temp[1] *= factor;
			temp[2] *= factor;
		}

		color.r = (float)temp[0];
		color.g = (float)temp[1];
		color.b = (float)temp[2];
	}
	
	if (prop.IsValid() == true)
	{
		UINT count = prop.GetSrcObjectCount<FbxFileTexture>();
		if (count > 0)
		{
			FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>();
			if (texture != NULL)
				*textureName = (const char *)texture->GetFileName();
		}
		else
		{
			*textureName = "";
		}
	}

	return color;
}
void ModelMaterial::GetProperty(FbxSurfaceMaterial * material, const char * name, string * textureName)
{
	FbxProperty prop = material->FindProperty(name);

	if (prop.IsValid() == true)
	{
		UINT count = prop.GetSrcObjectCount<FbxFileTexture>();
		if (count > 0)
		{
			FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>();
			if (texture != NULL)
				*textureName = (const char *)texture->GetFileName();
		}
		else
		{
			*textureName = "";
		}
	}
}
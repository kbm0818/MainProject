#pragma once

class FbxConverter
{
public:
	FbxConverter();
	~FbxConverter();

	void FbxToBin(wstring path, wstring destPath);

	static wstring destModelsPath;

private:
	void Convert(wstring path, wstring destPath);
	void FindAllFiles(vector<wstring>* fileNames, wstring FilePath);

private:
	wstring path;
	wstring destPath;

	vector<wstring> files;
};
#pragma once

class String
{
public:
	static void SplitString(vector<string>* result, string origin, string tok);
	static void SplitString(vector<wstring>* result, wstring origin, wstring tok);

	static void SplitFilePath(string fullPath, string* filePath = NULL, string* fileName = NULL);
	static void SplitFilePath(wstring fullPath, wstring* filePath = NULL, wstring* fileName = NULL);

	static void SplitFileNameOnly(string fullPath, string* fileName);
	static void SplitFileNameOnly(wstring fullPath, wstring* fileName);

	static bool StartsWith(string str, string comp);
	static bool StartsWith(wstring str, wstring comp);

	static bool Contain(string str, string comp);
	static bool Contain(wstring str, wstring comp);

	static void Replace(string* str, string comp, string rep);
	static void Replace(wstring* str, wstring comp, wstring rep);

	static wstring StringToWString(string value);
	static string WStringToString(wstring value);

	static const char* ToCSharp(string value);
};
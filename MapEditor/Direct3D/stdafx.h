#pragma once

#include <Windows.h>
#include <assert.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>

#include <atlstr.h> 

using namespace std;

#include <atlbase.h>
#include <atlconv.h>

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

//#define FBXSDK_SHARED
#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk-md.lib")
using namespace fbxsdk;

#define SAFE_RELEASE(p){ if(p){ (p)->Release(); (p) = NULL; } }
#define SAFE_DELETE(p){ if(p){ delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p){ if(p){ delete [] (p); (p) = NULL; } }

#define DLL extern "C" __declspec(dllexport)

const wstring Contents = L"../../_Contents/";
const wstring Shaders = L"../../_Shaders/";
const wstring Cpps = L"../Direct3D/";


#include "./Systems/D3D.h"
#include "./Systems/Keyboard.h"
#include "./Systems/Mouse.h"
#include "./Systems/Time.h"

#include "./Renders/BackBuffer.h"
#include "./Renders/VertexLayouts.h"
#include "./Renders/States.h"

#include "./Cameras/Camera.h"
#include "./Cameras/CameraFactory.h"

#include "./Shaders/Shader.h"

#include "./Model/Model.h"

#include "Utilities/BinaryFile.h"
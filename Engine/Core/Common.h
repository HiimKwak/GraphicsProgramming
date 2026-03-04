#pragma once
#pragma warning(disable: 4251)

// D3D 쪽의 리소스 해제할 때 사용할 함수.
template<typename T>
void SafeRelease(T*& resource)
{
	if (resource)
	{
		resource->Release();
		resource = nullptr;
	}
}

#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

#if defined(ENGINE_BUILD_DLL)
#define CRAFT_API DLLEXPORT
#else
#define CRAFT_API DLLIMPORT
#endif
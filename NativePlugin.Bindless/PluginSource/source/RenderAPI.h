#pragma once

#include "Unity/IUnityGraphics.h"

#include <stddef.h>

struct IUnityInterfaces;

struct BindlessCompute {
	void* outputUav;
	void** srvs;
	unsigned numSrvs;
	unsigned x, y, z;
};

struct BindlessTextureList {
	void** srvs;
	unsigned numSrvs;
	unsigned unused;
};

enum class BindlessTextureType {
	None = 0,
	Resource,
	SRV
};

// 8 + 4 + 4 = 16 bytes.
struct BindlessTexture {
	void* handle;
	BindlessTextureType type : 8;
	unsigned minMip : 8;
	unsigned maxMip : 8;
	unsigned forceFormat : 8;
	unsigned unused;
};

class RenderAPI
{
public:
	virtual ~RenderAPI() { }

	virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces) = 0;
	virtual bool GetUsesReverseZ() = 0;
	virtual int SetBindlessTextures(int offset, unsigned numTextures, BindlessTexture* textures) = 0;
	virtual void SetCurrentBindlessOffset(void* eventData) = 0;

	virtual void HookSetFunctions() {

	}
};


// Create a graphics API implementation instance for the given API type.
RenderAPI* CreateRenderAPI(UnityGfxRenderer apiType);


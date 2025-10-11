// Example low level rendering Unity plugin

#include "PlatformBase.h"
#include "RenderAPI.h"
#include "Unity/IUnityLog.h"

#include <assert.h>
#include <math.h>
#include <vector>
//#include "Unity/IUnityGraphicsVulkan.h"
#include "UAL/UnityLog.h"

// --------------------------------------------------------------------------
// UnitySetInterfaces

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);

IUnityInterfaces* s_UnityInterfaces = NULL;
IUnityGraphics* s_Graphics = NULL;

static inline void PrintDemoMessage() {
	UnityLog::LogWarning("Plugin demo for TrueTrace. Has limited functionality.\nOnly supports 2048 textures without dynamic offsets\nFull version supports bindles for graphics shaders\nFor more info contact #Meetem in Discord.\n");
}

extern "C" UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces * unityInterfaces)
{
	s_UnityInterfaces = unityInterfaces;
	UnityLog::Initialize(s_UnityInterfaces);

#ifdef BINDLESS_TRUETRACE_DEMO
	PrintDemoMessage();
#endif

	s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
	s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);
	//first_event_id = s_Graphics->ReserveEventIDRange(10);

	/*
#if SUPPORT_VULKAN
	UNITY_LOG(s_Log, "GfxInit...\n");

	if (s_Graphics->GetRenderer() == kUnityGfxRendererNull)
	{
		UNITY_LOG(s_Log, "Null render device\n");

		extern void RenderAPI_Vulkan_OnPluginLoad(IUnityInterfaces*);
		RenderAPI_Vulkan_OnPluginLoad(unityInterfaces);
	}
#endif // SUPPORT_VULKAN
	*/

	// Run OnGraphicsDeviceEvent(initialize) manually on plugin load
	//OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

extern "C" UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginUnload()
{
#ifdef BINDLESS_TRUETRACE_DEMO
	PrintDemoMessage();
#endif

	s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
}

#if UNITY_WEBGL
typedef void	(UNITY_INTERFACE_API* PluginLoadFunc)(IUnityInterfaces* unityInterfaces);
typedef void	(UNITY_INTERFACE_API* PluginUnloadFunc)();

extern "C" void	UnityRegisterRenderingPlugin(PluginLoadFunc loadPlugin, PluginUnloadFunc unloadPlugin);

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API RegisterPlugin()
{
	UnityRegisterRenderingPlugin(UnityPluginLoad, UnityPluginUnload);
}
#endif

// --------------------------------------------------------------------------
// GraphicsDeviceEvent
static RenderAPI* s_CurrentAPI = NULL;
static UnityGfxRenderer s_DeviceType = kUnityGfxRendererNull;

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	// Create graphics API implementation upon initialization
	if (eventType == kUnityGfxDeviceEventInitialize)
	{
		assert(s_CurrentAPI == NULL);
		s_DeviceType = s_Graphics->GetRenderer();
		s_CurrentAPI = CreateRenderAPI(s_DeviceType);

#ifdef BINDLESS_TRUETRACE_DEMO
		PrintDemoMessage();
#endif

	}

	// Let the implementation process the device related events
	if (s_CurrentAPI)
	{
		s_CurrentAPI->ProcessDeviceEvent(eventType, s_UnityInterfaces);
	}

	// Cleanup graphics API implementation upon shutdown
	if (eventType == kUnityGfxDeviceEventShutdown)
	{
		delete s_CurrentAPI;
		s_CurrentAPI = NULL;
		s_DeviceType = kUnityGfxRendererNull;
	}
}

static void UNITY_INTERFACE_API OnRenderEventAndData(int eventID, void* data)
{
	// Unknown / unsupported graphics device type? Do nothing
	if (s_CurrentAPI == NULL)
		return;

	if (eventID == 2147473649) {
		s_CurrentAPI->SetCurrentBindlessOffset(data);
	}
}

// --------------------------------------------------------------------------
// GetRenderEventFunc, an example function we export which is used to get a rendering event callback function.
extern "C" UNITY_INTERFACE_EXPORT UnityRenderingEventAndData UNITY_INTERFACE_API MeetemBindless_GetRenderEventFuncWithData()
{
	return OnRenderEventAndData;
}

unsigned long numTextureUpdates = 0;
extern "C" UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API MeetemBindless_SetBindlessTextures(int offset, int numTextures, BindlessTexture * textures)
{
	if (s_CurrentAPI == nullptr || textures == nullptr || numTextures <= 0)
		return 0;

#ifdef BINDLESS_TRUETRACE_DEMO
	if (numTextureUpdates % 4 == 0) {
		PrintDemoMessage();
	}

	numTextureUpdates++;
#endif

	return s_CurrentAPI->SetBindlessTextures(offset,(unsigned)numTextures, textures);
}
# DX12 Bindless Plugin for Unity3D
This is a proof of concept plugin for using bindless resources.

## Features
* Graphics and Compute shaders are supported.
* Hasstle-free setup.

## Limitations
* Proof of concept doesn't support UAVs or RTVs. 
* DX12 on Windows only (can work on Linux though via Proton or something).
* Consoles are not supported, but the support can technically be added, but it will require some effort.

## Usage
It is recommended to use `#pragma use_dxc` shader compiler. 
You don't need much of an effort, just follow the sample below:

```cpp
// register t31 is registered to be the "bindless" slot
// so you declare your bindless tables like that,
// and descriptor patching will do the job.
Texture2D TextureTable[2048] : register(t31, space0);

// Sample usage:
float4 v = Texture2DTable[texIdFlat].Load(uint3(id.x % 64, id.y % 64, 0));
```

To setup the textures into bindless slots or setup a current frame offset (to double-buffer your bindings) use the following functions:
```cs
public static class BindlessPlugin{
    public static void SetBindlessGlobalOffset(this CommandBuffer cmdBuf, int offset);

    public static void SetBindlessTextures(this BindlessTexture[] array, int shaderOffset, int arrayOffset = 0, int count = 0);
}
```

Check out the `SetupBindlessTextures.cs` for a more clear example.


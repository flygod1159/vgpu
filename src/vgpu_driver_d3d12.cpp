// Copyright © Amer Koleci and Contributors.
// Licensed under the MIT License (MIT). See LICENSE in the repository root for more information.

#if VGPU_DRIVER_D3D12
#include "vgpu_driver.h"

// Use the C++ standard templated min/max
#define NOMINMAX
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP
#define NOMCX
#define NOSERVICE
#define NOHELP
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <dxgi1_6.h>
#include "directx/d3d12.h"
#define D3D12MA_D3D12_HEADERS_ALREADY_INCLUDED
#include "D3D12MemAlloc.h"

/* Device */
typedef struct d3d12_renderer
{
    VGPUDeviceImpl* parentDevice;

    IDXGIFactory4* factory;
} d3d12_renderer;

static void d3d12_destroy(VGPUDevice device)
{
    VGPU_UNUSED(device);
}

static VGPUBuffer d3d12_createBuffer(VGPU_Renderer* driverData, const vgpu_buffer_desc* desc, const void* initData)
{
    VGPU_UNUSED(driverData);
    VGPU_UNUSED(desc);
    VGPU_UNUSED(initData);

    return NULL;
}

static void d3d12_destroyBuffer(VGPU_Renderer* driverData, VGPUBuffer buffer)
{
    VGPU_UNUSED(driverData);
    VGPU_UNUSED(buffer);
}

static bool d3d12IsAvailable(void)
{
    return true;
}

static VGPUDevice d3d12CreateDevice(VGPUValidationMode validationMode)
{
    if (!d3d12IsAvailable())
        return NULL;

    VGPU_UNUSED(validationMode);

    VGPUDevice device = (VGPUDeviceImpl*)VGPU_MALLOC(sizeof(VGPUDeviceImpl));
    ASSIGN_DRIVER(d3d12);

    d3d12_renderer* renderer = (d3d12_renderer*)VGPU_MALLOC(sizeof(d3d12_renderer));
    memset(renderer, 0, sizeof(d3d12_renderer));
    renderer->parentDevice = device;
    device->driverData = (VGPU_Renderer*)renderer;

    return device;
}

vgpu_driver d3d12_driver = {
    VGPU_BACKEND_D3D12,
    d3d12IsAvailable,
    d3d12CreateDevice
};
#endif /* VGPU_DRIVER_D3D12 */

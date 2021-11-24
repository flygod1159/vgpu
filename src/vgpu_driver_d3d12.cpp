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

#ifdef USING_DIRECTX_HEADERS
#include <directx/dxgiformat.h>
#include <directx/d3d12.h>
#else
#include <d3d12.h>
#endif

#include <dxgi1_6.h>

/* Device */
typedef struct d3d12_renderer
{
    vgpu_device_t* parent_device;

    bool debug_utils;
    IDXGIFactory4* factory;
} d3d12_renderer;

static void d3d12_destroy(VGPUDevice device)
{
}

static VGPUBuffer d3d12_createBuffer(vgpu_renderer* driver_data, const vgpu_buffer_desc* desc, const void* initData)
{
    return NULL;
}

static void d3d12_destroyBuffer(vgpu_renderer* driver_data, VGPUBuffer buffer)
{
}


static bool d3d12IsAvailable(void)
{
    return true;
}

static VGPUDevice d3d12CreateDevice(VGPU_ValidationMode validationMode)
{
    if (!d3d12IsAvailable())
        return NULL;

    VGPUDevice device = (vgpu_device_t*)VGPU_MALLOC(sizeof(vgpu_device_t));
    ASSIGN_DRIVER(d3d12);

    d3d12_renderer* renderer = (d3d12_renderer*)VGPU_MALLOC(sizeof(d3d12_renderer));
    memset(renderer, '\0', sizeof(d3d12_renderer));
    renderer->parent_device = device;
    device->driverData = (vgpu_renderer*)renderer;

    return device;
}

vgpu_driver d3d12_driver = {
    VGPU_BACKEND_D3D12,
    d3d12IsAvailable,
    d3d12CreateDevice
};
#endif /* VGPU_DRIVER_D3D12 */

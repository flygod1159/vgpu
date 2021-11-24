// Copyright © Amer Koleci and Contributors.
// Licensed under the MIT License (MIT). See LICENSE in the repository root for more information.

#ifndef _VGPU_DRIVER_H
#define _VGPU_DRIVER_H

#include "vgpu.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef VGPU_ASSERT
#   include <assert.h>
#   define VGPU_ASSERT(c) assert(c)
#endif

#ifndef VGPU_MALLOC
#   include <stdlib.h>
#   define VGPU_MALLOC(s) malloc(s)
#   define VGPU_FREE(p) free(p)
#endif

_VGPU_EXTERN void VGPU_LogInfo(const char* fmt, ...);
_VGPU_EXTERN void VGPU_LogWarn(const char* fmt, ...);
_VGPU_EXTERN void VGPU_LogError(const char* fmt, ...);

typedef struct vgpu_renderer vgpu_renderer;

struct vgpu_device_t {
    void (*destroy)(VGPUDevice device);

    VGPUBuffer(*createBuffer)(vgpu_renderer* driverData, const vgpu_buffer_desc* desc, const void* initData);
    void (*destroyBuffer)(vgpu_renderer* driverData, VGPUBuffer buffer);

    /* Opaque pointer for the driver */
    vgpu_renderer* driverData;
};

typedef struct vgpu_driver
{
    VGPU_Backend backend;
    bool(*isAvailable)(void);
    VGPUDevice(*createDevice)(VGPU_ValidationMode validationMode);
} vgpu_driver;

#define ASSIGN_DRIVER_FUNC(func, name) \
	device->func = name##_##func;
#define ASSIGN_DRIVER(name) \
    ASSIGN_DRIVER_FUNC(destroy, name) \
    ASSIGN_DRIVER_FUNC(createBuffer, name) \
    ASSIGN_DRIVER_FUNC(destroyBuffer, name) \

_VGPU_EXTERN vgpu_driver vulkan_driver;
_VGPU_EXTERN vgpu_driver d3d12_driver;

#endif /* _VGPU_DRIVER_H */

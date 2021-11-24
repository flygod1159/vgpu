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

#define VGPU_STATIC_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define VGPU_UNUSED(x) ((void) x)

#if defined(__clang__)
#define VGPU_DISABLE_WARNINGS() \
    _Pragma("clang diagnostic push")\
	_Pragma("clang diagnostic ignored \"-Wall\"") \
	_Pragma("clang diagnostic ignored \"-Wextra\"") \
	_Pragma("clang diagnostic ignored \"-Wtautological-compare\"")

#define VGPU_ENABLE_WARNINGS() \
	_Pragma("clang diagnostic pop")
#elif defined(__GNUC__) || defined(__GNUG__)
#	define VGPU_DISABLE_WARNINGS() \
	_Pragma("GCC diagnostic push") \
	_Pragma("GCC diagnostic ignored \"-Wall\"") \
	_Pragma("clang diagnostic ignored \"-Wextra\"") \
	_Pragma("clang diagnostic ignored \"-Wtautological-compare\"")

#define VGPU_ENABLE_WARNINGS() _Pragma("GCC diagnostic pop")
#elif defined(_MSC_VER)
#   define VGPU_DISABLE_WARNINGS() __pragma(warning(push, 0))
#   define VGPU_ENABLE_WARNINGS()  __pragma(warning(pop))
#endif

_VGPU_EXTERN void VGPU_LogInfo(const char* fmt, ...);
_VGPU_EXTERN void VGPU_LogWarn(const char* fmt, ...);
_VGPU_EXTERN void VGPU_LogError(const char* fmt, ...);

typedef struct VGPU_Renderer VGPU_Renderer;

struct vgpu_device_t {
    void (*destroy)(VGPUDevice device);

    VGPUBuffer(*createBuffer)(VGPU_Renderer* driverData, const vgpu_buffer_desc* desc, const void* initData);
    void (*destroyBuffer)(VGPU_Renderer* driverData, VGPUBuffer buffer);

    /* Opaque pointer for the driver */
    VGPU_Renderer* driverData;
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

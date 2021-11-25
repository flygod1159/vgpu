// Copyright © Amer Koleci and Contributors.
// Licensed under the MIT License (MIT). See LICENSE in the repository root for more information.

#ifndef VGPU_H
#define VGPU_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(VGPU_SHARED_LIBRARY)
#   if defined(_MSC_VER)
#       ifdef VGPU_EXPORTS
#           define _VGPU_API_DECL __declspec(dllexport)
#       else
#           define _VGPU_API_DECL __declspec(dllimport)
#       endif
#   else
#       define _VGPU_API_DECL __attribute__((visibility("default")))
#   endif
#else
#   define _VGPU_API_DECL
#endif

#ifdef __cplusplus
#   define _VGPU_EXTERN extern "C"
#else
#   define _VGPU_EXTERN extern
#endif

#define VGPU_API _VGPU_EXTERN _VGPU_API_DECL

#if defined(_WIN32)
#   define VGPU_API_CALL __cdecl
#else
#   define VGPU_API_CALL
#endif

typedef struct VGPUDeviceImpl* VGPUDevice;
typedef struct VGPUTextureImpl* VGPUTexture;
typedef struct VGPUBufferImpl* VGPUBuffer;

typedef enum VGPULogType {
    VGPU_LOG_TYPE_INFO = 0,
    VGPU_LOG_TYPE_WARN,
    VGPU_LOG_TYPE_DEBUG,
    VGPU_LOG_TYPE_ERROR,
    _VGPU_LOG_TYPE_FORCE_U32 = 0x7FFFFFFF
} VGPULogType;

typedef enum VGPUBackend {
    _VGPU_BACKEND_DEFAULT,
    VGPU_BACKEND_VULKAN,
    VGPU_BACKEND_D3D12,

    _VGPU_BACKEND_NUM,
    _VGPU_BACKEND_FORCE_U32 = 0x7FFFFFFF
} VGPUBackend;

typedef enum VGPUValidationMode {
    /// No validation is enabled.
    VGPU_VALIDATION_MODE_DISABLED,
    /// Print warnings and errors
    VGPU_VALIDATION_MODE_ENABLED,
    /// Print all warnings, errors and info messages
    VGPU_VALIDATION_MODE_VERBOSE,
    /// Enable GPU-based validation
    VGPU_VALIDATION_MODE_GPU,
    _VGPU_VALIDATION_MODE_FORCE_U32 = 0x7FFFFFFF
} VGPUValidationMode;

typedef struct vgpu_buffer_desc {
    uint64_t size;
} vgpu_buffer_desc;

typedef void (VGPU_API_CALL* vgpuLogFunc)(VGPULogType type, const char* msg);
VGPU_API void VGPU_SetLogCallback(vgpuLogFunc func);

VGPU_API VGPUDevice vgpuCreateDevice(VGPUValidationMode validationMode);
VGPU_API void vgpuDestroyDevice(VGPUDevice device);

VGPU_API VGPUBuffer vgpuCreateBuffer(VGPUDevice device, const vgpu_buffer_desc* desc, const void* initialData);
VGPU_API void vgpuDestroyBuffer(VGPUDevice device, VGPUBuffer buffer);


#endif /* VGPU_H */

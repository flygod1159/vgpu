// Copyright © Amer Koleci and Contributors.
// Licensed under the MIT License (MIT). See LICENSE in the repository root for more information.

#ifndef VGPU_H
#define VGPU_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(VGPU_SHARED_LIBRARY_BUILD)
#   if defined(_MSC_VER)
#       define VGPU_API __declspec(dllexport)
#   elif defined(__GNUC__)
#       define VGPU_API __attribute__((visibility("default")))
#   else
#       define VGPU_API
#       pragma warning "Unknown dynamic link import/export semantics."
#   endif
#elif defined(VGPU_SHARED_LIBRARY_INCLUDE)
#   if defined(_MSC_VER)
#       define VGPU_API __declspec(dllimport)
#   else
#       define VGPU_API
#   endif
#else
#   define VGPU_API
#endif

#ifdef __cplusplus
#   define _VGPU_EXTERN extern "C"
#else
#   define _VGPU_EXTERN extern
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    typedef struct vgpu_device_t* vgpu_device;

    typedef enum vgpu_backend {
        _VGPU_BACKEND_DEFAULT,
        VGPU_BACKEND_VULKAN,
        VGPU_BACKEND_D3D12,

        _VGPU_BACKEND_NUM,
        _VGPU_BACKEND_FORCE_U32 = 0x7FFFFFFF
    } vgpu_backend;


    VGPU_API vgpu_device vgpuCreateDevice(void);
    VGPU_API void vgpuDestroyDevice(vgpu_device device);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VGPU_H */

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

struct vgpu_device_t {
    void (*destroy)(vgpu_device device);
};

typedef struct vgpu_driver
{
    vgpu_backend backend;
    vgpu_device(*createDevice)(void);
} vgpu_driver;

_VGPU_EXTERN vgpu_driver vulkan_driver;
_VGPU_EXTERN vgpu_driver d3d12_driver;

#endif /* _VGPU_DRIVER_H */

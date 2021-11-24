// Copyright © Amer Koleci and Contributors.
// Licensed under the MIT License (MIT). See LICENSE in the repository root for more information.

#ifndef _VGPU_DRIVER_H
#define _VGPU_DRIVER_H

#include "vgpu.h"
#include <stdio.h>
#include <stdlib.h>

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

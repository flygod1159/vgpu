// Copyright © Amer Koleci and Contributors.
// Licensed under the MIT License (MIT). See LICENSE in the repository root for more information.

#include "vgpu_driver.h"

/* Drivers */

static const vgpu_driver* drivers[] = {
#if VGPU_DRIVER_D3D12
    & d3d12_driver,
#endif
#if VGPU_DRIVER_VULKAN
    & vulkan_driver,
#endif
    NULL
};

vgpu_device vgpuCreateDevice(void)
{
    for (int i = 0; drivers[i] != NULL; i += 1)
    {

    }

    return drivers[1]->createDevice();
}

void vgpuDestroyDevice(vgpu_device device)
{
    if (device == NULL)
    {
        return;
    }

    device->destroy(device);
}

// Copyright © Amer Koleci and Contributors.
// Licensed under the MIT License (MIT). See LICENSE in the repository root for more information.

#if VGPU_DRIVER_D3D12
#include "vgpu_driver.h"

static vgpu_device d3d12CreateDevice(void) {
    return NULL;
}

vgpu_driver d3d12_driver = {
    VGPU_BACKEND_D3D12,
    d3d12CreateDevice
};
#endif /* VGPU_DRIVER_D3D12 */

// Copyright © Amer Koleci and Contributors.
// Licensed under the MIT License (MIT). See LICENSE in the repository root for more information.

#if VGPU_DRIVER_VULKAN
#include "vgpu_driver.h"
#include "volk.h"
#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"
#include "spirv_reflect.h"

static vgpu_device vulkanCreateDevice(void) {
    return NULL;
}

vgpu_driver vulkan_driver = {
    VGPU_BACKEND_VULKAN,
    vulkanCreateDevice
};

#endif /* VGPU_DRIVER_VULKAN */

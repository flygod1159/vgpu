// Copyright © Amer Koleci and Contributors.
// Licensed under the MIT License (MIT). See LICENSE in the repository root for more information.

#include "vgpu_driver.h"
#include <stdarg.h>

/* Log */
static vgpuLogFunc s_LogFunc = NULL;

#define VGPU_LOG_MAX_MESSAGE_SIZE 1024

void VGPU_LogInfo(const char* format, ...)
{
    if (s_LogFunc == NULL)
        return;

    char msg[VGPU_LOG_MAX_MESSAGE_SIZE];
    va_list ap;
    va_start(ap, format);
    vsnprintf(msg, sizeof(char) * VGPU_LOG_MAX_MESSAGE_SIZE, format, ap);
    va_end(ap);
    s_LogFunc(VGPU_LOG_TYPE_INFO, msg);
}

void VGPU_LogWarn(const char* fmt, ...)
{
    if (s_LogFunc == NULL)
        return;

    char msg[VGPU_LOG_MAX_MESSAGE_SIZE];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);
    s_LogFunc(VGPU_LOG_TYPE_WARN, msg);
}

void VGPU_LogError(const char* fmt, ...)
{
    if (s_LogFunc == NULL)
        return;

    char msg[VGPU_LOG_MAX_MESSAGE_SIZE];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);
    s_LogFunc(VGPU_LOG_TYPE_ERROR, msg);
}

#undef VGPU_LOG_MAX_MESSAGE_SIZE

void VGPU_SetLogCallback(vgpuLogFunc func)
{
    s_LogFunc = func;
}

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

VGPUDevice vgpuCreateDevice(VGPUValidationMode validationMode)
{
    for (int i = 0; drivers[i] != NULL; i += 1)
    {

    }

    return drivers[1]->createDevice(validationMode);
}

void vgpuDestroyDevice(VGPUDevice device)
{
    if (device == NULL)
    {
        return;
    }

    device->destroy(device);
}

VGPUBuffer vgpuCreateBuffer(VGPUDevice device, const vgpu_buffer_desc* desc, const void* initialData)
{
    if (device == NULL)
    {
        return NULL;
    }

    return device->createBuffer(device->driverData, desc, initialData);
}

void vgpuDestroyBuffer(VGPUDevice device, VGPUBuffer buffer)
{
    if (device == NULL || buffer == NULL)
    {
        return;
    }

    device->destroyBuffer(device->driverData, buffer);
}

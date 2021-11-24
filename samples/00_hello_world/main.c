// Copyright © Amer Koleci and Contributors.
// Distributed under the MIT license. See the LICENSE file in the project root for more information.

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <vgpu.h>
#include <stdio.h>
#include <stdlib.h>

const char* kAppName = "00 - Hello World";
const uint32_t kWindowWidth = 1280;
const uint32_t kWindowHeight = 720;

VGPUDevice gpu_device = NULL;

static void app_glfw_error(int error, const char* description)
{
    //LOG("Error " << error << ":" << description);
}

static void vgpu_log_callback(VGPU_LogType type, const char* msg)
{
    switch (type)
    {
    case VGPU_LOG_TYPE_INFO:
        printf("INFO: %s\n", msg);
        break;

    case VGPU_LOG_TYPE_WARN:
        printf("WARN: %s\n", msg);
        break;

    case VGPU_LOG_TYPE_ERROR:
        printf("ERROR: %s\n", msg);
        break;

    default:
        break;
    }
}

void draw_frame(void) {
}

int main(int argc, char** argv)
{
    glfwSetErrorCallback(app_glfw_error);
    if (!glfwInit()) {
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(kWindowWidth, kWindowHeight, kAppName, NULL, NULL);

    VGPU_SetLogCallback(vgpu_log_callback);
    gpu_device = vgpuCreateDevice(VGPU_VALIDATION_MODE_ENABLED);

    vgpu_buffer_desc buffer_desc;
    buffer_desc.size = 64;
    VGPUBuffer buffer = vgpuCreateBuffer(gpu_device, &buffer_desc, NULL);

    while (!glfwWindowShouldClose(window))
    {
        draw_frame();
        glfwPollEvents();
    }

    vgpuDestroyDevice(gpu_device);

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}

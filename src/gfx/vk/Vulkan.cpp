#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include <Phoenix/gfx/vk/Vulkan.hpp>
#include <string>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_funcs.hpp>
#include <vulkan/vulkan_structs.hpp>

#include <Phoenix/Log.hpp>

#define CHECK_RESULT_ENUM(e) if (result == e) { PHNX_ERR("Error: %s", #e); }

namespace phnx {
    namespace VK {
        Context::Context(std::string appName) {
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = appName.c_str();
            appInfo.pEngineName = "Phoenix";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_VERSION_1_0;
            appInfo.pNext = nullptr;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pNext = nullptr;
            createInfo.pApplicationInfo = &appInfo;
            createInfo.enabledLayerCount = 0;
            createInfo.ppEnabledLayerNames = nullptr;

            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;

            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            createInfo.enabledExtensionCount = glfwExtensionCount;
            createInfo.ppEnabledExtensionNames = glfwExtensions;

            PHNX_INFO("Creating Instance");

            CheckError(vkCreateInstance(&createInfo, nullptr, &mInstance));
            PHNX_INFO("Creating Instance");
        }

        void CheckError(VkResult result) {
            PHNX_INFO("Result: %d", result);

            if (result == VK_SUCCESS) {return;}

            CHECK_RESULT_ENUM(VK_ERROR_EXTENSION_NOT_PRESENT)
            CHECK_RESULT_ENUM(VK_ERROR_FORMAT_NOT_SUPPORTED)
            CHECK_RESULT_ENUM(VK_ERROR_LAYER_NOT_PRESENT)
            CHECK_RESULT_ENUM(VK_ERROR_INITIALIZATION_FAILED)
        }
    }
}
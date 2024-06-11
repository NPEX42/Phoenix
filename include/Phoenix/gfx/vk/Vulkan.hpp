#pragma once
#include <vector>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>

namespace phnx {
    namespace VK {
        class Context {
            public:
                Context(std::string appName);
                VkInstance* const Instance() { return &mInstance; }
            private:
                VkInstance mInstance;
        };

        void CheckError(VkResult result);

    }

}

#ifndef SVulkanContext_H
#define SVulkanContext_H

#include <cstdlib>

#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES            // do not declared prototypes, so I can load dynamically!
#include <vulkan.h>

struct shader_uniform {

    VkBuffer buffer;
    VkDeviceMemory memory;

    float *projectionMatrix;
    float *viewMatrix;
    float *modelMatrix;

};

struct SVulkanContext 
{                                
    uint32_t width;
    uint32_t height;

    float cameraZ;
    int32_t cameraZDir;

    uint32_t presentQueueIdx;
    VkQueue presentQueue;

    VkInstance instance;

    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;

    VkImage *presentImages;
    VkImage depthImage;
    VkImageView depthImageView;
    VkFramebuffer *frameBuffers;

    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkPhysicalDeviceMemoryProperties memoryProperties;

    VkDevice device;

    VkCommandBuffer setupCmdBuffer;
    VkCommandBuffer drawCmdBuffer;

    VkRenderPass renderPass;

    VkBuffer vertexInputBuffer;

    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;
    VkDescriptorSet descriptorSet;

    shader_uniform uniforms;

    VkDebugUtilsMessengerEXT callback;
};

#endif
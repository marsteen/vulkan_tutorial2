
#ifndef CVulkanBase_H
#define CVulkanBase_H

#include <SVulkanContext.h>

class CVulkanBase
{
    public:

		void setWindowSize(int width, int height);
        void initVulkan(HINSTANCE hInstance, HWND windowHandle);
        void renderVulkan();
        void finishVulkan();

    protected:

        SVulkanContext context;

};

#endif
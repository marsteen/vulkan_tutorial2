#include <windows.h>
#include <CVulkanBase.h>

static CVulkanBase* vulkanBase;
                        
LRESULT CALLBACK WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
    switch( uMsg ) {
        case WM_CLOSE: { 
            PostQuitMessage( 0 );
            break;
        }
        case WM_PAINT: 
        {
            if (vulkanBase != NULL)
            {
                vulkanBase->renderVulkan();
            }
            break;
        }
        default: {
            break;
        }
    }
    
    // a pass-through for now. We will return to this callback
    return DefWindowProc( hwnd, uMsg, wParam, lParam );
}


#define WINDOW_WIDTH 800
#define WINDOW_HEIGTH 600

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {

    WNDCLASSEX windowClass = {};
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = "VulkanWindowClass";
    RegisterClassEx( &windowClass );


    HWND windowHandle = CreateWindowEx( 0, 
                                        "VulkanWindowClass",
                                        "Core",
                                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                        100, 
                                        100, 
                                        WINDOW_WIDTH,
                                        WINDOW_HEIGTH,
                                        NULL,
                                        NULL,
                                        hInstance,
                                        NULL );

    vulkanBase = new CVulkanBase();
    vulkanBase->setWindowSize(800, 600);
    vulkanBase->initVulkan(hInstance, windowHandle);



    MSG msg;
    bool done = false;
    while( !done ) {
        PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );
        if( msg.message == WM_QUIT ) {
            done = true;
        } else {
            TranslateMessage( &msg ); 
            DispatchMessage( &msg );
        }

        RedrawWindow( windowHandle, NULL, NULL, RDW_INTERNALPAINT );
    }


    vulkanBase->finishVulkan();


    return msg.wParam;
}
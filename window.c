#include "window.h"
#include "defs.h"

Frame frame = {0};

void startWindow(WND_INSTANCE hInstance, void (*loopFunction)(), void (*keyCallbackFunction)(u32int),
                 void (*mouseCallbackFunction)(Click, u32int, u32int), byte targetFps) {
    windowClass.lpfnWndProc = WindowProcessMessage;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = title;

    RegisterClass(&windowClass);

    frame_bitmap_info.bmiHeader.biSize = sizeof(frame_bitmap_info.bmiHeader);
    frame_bitmap_info.bmiHeader.biPlanes = 1;
    frame_bitmap_info.bmiHeader.biBitCount = sizeof(u32int) * 8;
    frame_bitmap_info.bmiHeader.biCompression = BI_RGB;
    frame_device_context = CreateCompatibleDC(0);

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int windowX = (screenWidth - WND_GAME_DFLT_WIDTH) / 2;
    int windowY = (screenHeight - WND_GAME_DFLT_HEIGHT) / 2;

    windowHandle = CreateWindow(title, title, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
                                windowX, windowY, WND_GAME_DFLT_WIDTH, WND_GAME_DFLT_HEIGHT, NULL, NULL, hInstance,
                                NULL);

    keyCallback = keyCallbackFunction;
    mouseCallback = mouseCallbackFunction;

    if (windowHandle == NULL) {
        exit(-1);
    }

    windowTargetFps = targetFps;
    initTimer();
    while (!quit) {
        static MSG message = {0};
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            DispatchMessage(&message);
        }

        loopFunction();
        redraw();
        waitForNextFrame();
    }
}

void closeWindow() {
    quit = true;
}

static void redraw() {
    InvalidateRect(windowHandle, NULL, FALSE);
    UpdateWindow(windowHandle);
}

static LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_QUIT:
        case WM_DESTROY: {
            closeWindow();
        }
            break;

#ifndef WOLF3D_EDITOR_MODE
        case WM_SETCURSOR: {
            SetCursor(NULL);
            return true;
        }
#endif

        case WM_PAINT: {
            static PAINTSTRUCT paint;
            static HDC device_context;
            device_context = BeginPaint(window_handle, &paint);
            BitBlt(device_context,
                   paint.rcPaint.left, paint.rcPaint.top,
                   paint.rcPaint.right - paint.rcPaint.left, paint.rcPaint.bottom - paint.rcPaint.top,
                   frame_device_context,
                   paint.rcPaint.left, paint.rcPaint.top,
                   SRCCOPY);
            EndPaint(window_handle, &paint);
        }
            break;

        case WM_SIZE: {
            frame_bitmap_info.bmiHeader.biWidth = LOWORD(lParam);
            frame_bitmap_info.bmiHeader.biHeight = HIWORD(lParam);

            if (frame_bitmap) DeleteObject(frame_bitmap);
            frame_bitmap = CreateDIBSection(NULL, &frame_bitmap_info, DIB_RGB_COLORS, (void **) &frame.pixels, 0, 0);
            SelectObject(frame_device_context, frame_bitmap);

            frame.width = LOWORD(lParam);
            frame.height = HIWORD(lParam);
        }
            break;

        case WM_KEYDOWN: {
            if (keyCallback != NULL)
                keyCallback(wParam);
        }
            break;

        case WM_LBUTTONDOWN: {
            if (mouseCallback != NULL)
                mouseCallback(CLICK_LEFT, LOWORD(lParam), HIWORD(lParam));
        }
            break;

        case WM_RBUTTONDOWN: {
            if (mouseCallback != NULL)
                mouseCallback(CLICK_RIGHT, LOWORD(lParam), HIWORD(lParam));
        }
            break;

        default: {
            return DefWindowProc(window_handle, message, wParam, lParam);
        }
    }
    return 0;
}

static void initTimer() {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&lastTime);
}

static void waitForNextFrame() {
    while (true) {
        QueryPerformanceCounter(&currentTime);
        LONGLONG elapsedTime = currentTime.QuadPart - lastTime.QuadPart;
        if ((elapsedTime * 1000 / frequency.QuadPart) >= WND_FRAME_TIME) {
            lastTime = currentTime;
            break;
        }
    }
}
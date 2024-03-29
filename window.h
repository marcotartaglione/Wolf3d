#ifndef WOLF3D_WINDOW_H
#define WOLF3D_WINDOW_H

#include "defs.h"
#include <windows.h>

#define WND_GAME_DFLT_WIDTH   1280
#define WND_GAME_DFLT_HEIGHT  800

#define WND_CLASS       WNDCLASS
#define WND_HANDLE      HWND
#define WND_INSTANCE    HINSTANCE

//
// Local variables
//
static const char title[] = "Wolf3D";
static WND_CLASS windowClass;
static WND_HANDLE windowHandle;

//
// GDI structures
//
static BITMAPINFO frame_bitmap_info;          // pixel format details
static HBITMAP frame_bitmap = 0;              // bitmap info + array data
static HDC frame_device_context = 0;          // pointer to bitmap handle

static char quit = false;

typedef struct {
    int width;
    int height;
    u32int *pixels;
} Frame;

extern Frame frame;

//
// External functions
//
static void (*keyCallback)(u32int);
static void (*mouseCallback)(u32int, u32int);

void startWindow(WND_INSTANCE hInstance, void (*loopFunction)(), void (*keyCallbackFunction)(u32int), void (*mouseCallbackFunction)(u32int, u32int));
void closeWindow();

//
// Internal functions
//
static void redraw();
static LRESULT CALLBACK WindowProcessMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // WOLF3D_WINDOW_H
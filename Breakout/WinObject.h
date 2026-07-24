#pragma once
#include <Windows.h>

struct WinObject
{
        // Handle to the actual Win32 window
        HWND hwnd = nullptr;

        // Position
        float x = 0.0f;
        float y = 0.0f;

        // Size
        int width = 150;
        int height = 80;

        bool destroyed = false;
};
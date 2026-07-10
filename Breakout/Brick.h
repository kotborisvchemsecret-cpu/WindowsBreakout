#pragma once

#include <Windows.h>

struct Brick
{
    // Handle to the actual Win32 window
    HWND hwnd = nullptr;

    // Position
    float x = 0.0f;
    float y = 0.0f;

    // Velocity (pixels per second)
    float vx = 0.0f;
    float vy = 0.0f;

    // Size
    int width = 150;
    int height = 80;

	bool destroyed = false;
};

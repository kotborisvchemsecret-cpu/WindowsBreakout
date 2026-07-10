#pragma once

#include <Windows.h>

struct Ball
{
    HWND hwnd = nullptr;


    float x = 600.0f;
    float y = 600.0f;

    float vx = 0.0f;
    float vy = 0.0f;

    float radius = 25.0f;
};
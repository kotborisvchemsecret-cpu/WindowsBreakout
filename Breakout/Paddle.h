#pragma once
#include <Windows.h>

struct Paddle
{
    HWND hwnd = nullptr;

    float x = 400;
    float y = 700;

    int width = 200;
    int height = 20;
};
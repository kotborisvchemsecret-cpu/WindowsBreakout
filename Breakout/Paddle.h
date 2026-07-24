#pragma once
#include "WinObject.h"

struct Paddle : WinObject
{
    float x = 400;      
    float y = 700;      

    int width = 200;    
    int height = 25;
    float previousX = 0;
    float previousY = 0;

    float vx = 0;
    float vy = 0;
};
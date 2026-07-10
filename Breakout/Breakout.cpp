// Breakout.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Breakout.h"
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"
#include <vector>

// Global Variables:
std::vector<Brick> bricks; // Vector to hold all the bricks
Ball ball;
Paddle paddle;
HINSTANCE hInst;                                // current instance
const wchar_t CLASS_NAME[] = L"BrickWindow";
const wchar_t WINDOW_TITLE[] = L"Breakout";

const int rows = 5;
const int cols = 10;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void UpdateGame(float dt);
void UpdateBall(float dt);
void RemoveDestroyedBricks();
void HandleCollisions();
bool CheckCollision(const Ball& ball, const Brick& brick);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
	hInst = hInstance; // Store instance handle in our global variable
    MyRegisterClass(hInstance);


    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            Brick brick{};
            brick.x = col * brick.width + 25;
            brick.y = row * brick.height + 25;

			brick.hwnd = CreateWindowEx(
                0,
                CLASS_NAME,
                L"Notepad",
				WS_OVERLAPPEDWINDOW,
                brick.x,
				brick.y,
				brick.width,
				brick.height,
                nullptr,
				nullptr,
                hInst,
				nullptr);

            ShowWindow(brick.hwnd, SW_SHOW);

            bricks.push_back(brick);
        }
	}
    paddle.hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Paddle",
        WS_POPUP,
        (int)paddle.x,
        (int)paddle.y,
        paddle.width,
        paddle.height,
        nullptr,
        nullptr,
        hInst,
        nullptr);

    ShowWindow(paddle.hwnd, SW_SHOW);

    ball.hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Ball",
        WS_POPUP,
        (int)ball.x,
        (int)ball.y,
        (int)(ball.radius * 2),
        (int)(ball.radius * 2),
        nullptr,
        nullptr,
        hInst,
        nullptr);

    ShowWindow(ball.hwnd, SW_SHOW);

    MSG msg;


    const double dt = 1.0 / 60.0;

    while (true)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                return 0;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        UpdateGame(dt);
    }
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};

    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = CLASS_NAME;

    return RegisterClassExW(&wcex);
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rc;
        GetClientRect(hWnd, &rc);

        FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void UpdateGame(float dt)
{
    UpdateBall(dt);

    HandleCollisions();

    RemoveDestroyedBricks();
}

void UpdateBall(float dt)
{
    // Update the ball's position based on its velocity:
    ball.x += ball.vx * dt;
    ball.y += ball.vy * dt;

	MoveWindow(ball.hwnd, (int)ball.x, (int)ball.y, (int)(ball.radius * 2), (int)(ball.radius * 2), TRUE);
}

void RemoveDestroyedBricks()
{
    // Remove destroyed bricks from the vector
    bricks.erase(std::remove_if(bricks.begin(), bricks.end(),
        [](const Brick& brick) { return brick.destroyed; }),
        bricks.end());
}

void HandleCollisions()
{
    // Check for collisions between the ball and each brick
    for (Brick& brick : bricks)
    {
        if (!brick.destroyed && CheckCollision(ball, brick))
        {
            // Handle collision response (e.g., reverse ball direction)
            ball.vy = -ball.vy; // Simple response: reverse vertical velocity
            brick.destroyed = true; // Mark the brick as destroyed
        }
    }
}

bool CheckCollision(const Ball& ball, const Brick& brick)
{
    // Simple AABB collision detection
    return ((ball.x < (brick.x + brick.width)) &&
            ((ball.x + ball.radius) > brick.x) &&
            (ball.y < (brick.y + brick.height)) &&
            ((ball.y + ball.radius) > brick.y));
}
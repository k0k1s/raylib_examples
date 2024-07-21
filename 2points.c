#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define LENGTH 200.0f // length of the link

int main(void)
{
    // Initialization
    const int screenWidth = 1000;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib - 2 Points with Distance");

    SetTargetFPS(60);

    Vector2 fixedPoint = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 movablePoint = fixedPoint; // Initialize movable point to be at the fixed point

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            movablePoint = GetMousePosition();
        }

        // Calculate the distance between the fixed and movable points
        float distance = sqrtf(powf(movablePoint.x - fixedPoint.x, 2) + powf(movablePoint.y - fixedPoint.y, 2));

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the fixed point
        DrawCircle((int)fixedPoint.x, (int)fixedPoint.y, 10, BLUE);
        DrawText("Fixed Point", (int)fixedPoint.x + 15, (int)fixedPoint.y - 10, 10, BLUE);

        // Draw the movable point
        DrawCircle((int)movablePoint.x, (int)movablePoint.y, 10, RED);
        DrawText("Movable Point", (int)movablePoint.x + 15, (int)movablePoint.y - 10, 10, RED);

        // Draw a line between the fixed point and the movable point
        DrawLine((int)fixedPoint.x, (int)fixedPoint.y, (int)movablePoint.x, (int)movablePoint.y, BLACK);

        // Draw the distance between the points
        char distanceText[50];
        snprintf(distanceText, sizeof(distanceText), "Distance: %.2f", distance);
        DrawText(distanceText, (int)((fixedPoint.x + movablePoint.x) / 2), (int)((fixedPoint.y + movablePoint.y) / 2) - 10, 10, DARKGRAY);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}

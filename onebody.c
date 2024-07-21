#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define INITIAL_LENGTH 200.0f // Initial radius of the circle on which movable point rotates
#define BASE_ROTATION_SPEED 0.02f // Base speed of rotation

int main(void)
{
    // Initialization
    const int screenWidth = 1000;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib - Rotating Point with Adjustable Distance");

    SetTargetFPS(60);

    Vector2 fixedPoint = { screenWidth / 2.0f, screenHeight / 2.0f };
    float angle = 0.0f; // Initial angle
    float length = INITIAL_LENGTH; // Radius of rotation

    // Position of the movable point
    Vector2 movablePoint = {
        fixedPoint.x + length * cos(angle),
        fixedPoint.y + length * sin(angle)
    };

    // Main game loop
    while (!WindowShouldClose()) {
        // Calculate the distance between the fixed point and movable point
        float distance = length;

        // Update rotation speed based on distance
        float rotationSpeed = BASE_ROTATION_SPEED * (0.8f / (distance / INITIAL_LENGTH));

        // Update angle
        angle += rotationSpeed; // Increment the angle for rotation

        // Update length and movable point position on mouse click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();
            length = sqrtf(powf(mousePosition.x - fixedPoint.x, 2) + powf(mousePosition.y - fixedPoint.y, 2));
            angle = atan2f(mousePosition.y - fixedPoint.y, mousePosition.x - fixedPoint.x);
        }

        // Calculate the position of the movable point
        movablePoint.x = fixedPoint.x + length * cos(angle);
        movablePoint.y = fixedPoint.y + length * sin(angle);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the fixed point
        DrawCircle((int)fixedPoint.x, (int)fixedPoint.y, 10, BLUE);
        DrawText("Fixed Point", (int)fixedPoint.x + 15, (int)fixedPoint.y - 10, 10, BLUE);

        // Draw the movable point
        DrawCircle((int)movablePoint.x, (int)movablePoint.y, 10, RED);
        DrawText("Movable Point", (int)movablePoint.x + 15, (int)movablePoint.y - 10, 10, RED);

    
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}

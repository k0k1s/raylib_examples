#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define INITIAL_LENGTH 200.0f // Initial radius of the circle on which movable point rotates
#define BASE_ROTATION_SPEED 0.02f // Base speed of rotation
#define TRAIL_LENGTH 800 // Number of points in the trail
#define TRAIL_RADIUS 1 // Radius of the trail circles

int main(void)
{
    // Initialization
    const int screenWidth = 1000;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib - Rotating Point with Trail");

    SetTargetFPS(60);

    Vector2 fixedPoint = { screenWidth / 2.0f, screenHeight / 2.0f };
    float angle = 0.0f; // Initial angle
    float length = INITIAL_LENGTH; // Radius of rotation

    // Position of the movable point
    Vector2 movablePoint = {
        fixedPoint.x + length * cos(angle),
        fixedPoint.y + length * sin(angle)
    };

    // Trail buffer and variables
    Vector2 trail[TRAIL_LENGTH] = {0};
    int trailIndex = 0;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update angle
        float distance = length;
        float rotationSpeed = BASE_ROTATION_SPEED * (0.8f / (distance / INITIAL_LENGTH));
        angle += rotationSpeed;

        // Update length and movable point position on mouse click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();
            length = sqrtf(powf(mousePosition.x - fixedPoint.x, 2) + powf(mousePosition.y - fixedPoint.y, 2));
            angle = atan2f(mousePosition.y - fixedPoint.y, mousePosition.x - fixedPoint.x);

            // Reset the trail
            for (int i = 0; i < TRAIL_LENGTH; i++) {
                trail[i] = movablePoint; // You can also use {0, 0} to completely clear
            }
            trailIndex = 0; // Reset the trail index
        }

        // Calculate the position of the movable point
        movablePoint.x = fixedPoint.x + length * cos(angle);
        movablePoint.y = fixedPoint.y + length * sin(angle);

        // Update the trail
        trail[trailIndex] = movablePoint;
        trailIndex = (trailIndex + 1) % TRAIL_LENGTH; // Move to the next index, wrapping around if needed

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the fixed point
        DrawCircle((int)fixedPoint.x, (int)fixedPoint.y, 10, BLUE);
        DrawText("Fixed Point", (int)fixedPoint.x + 15, (int)fixedPoint.y - 10, 10, BLUE);

        // Draw the movable point
        DrawCircle((int)movablePoint.x, (int)movablePoint.y, 10, RED);
        DrawText("Movable Point", (int)movablePoint.x + 15, (int)movablePoint.y - 10, 10, RED);

        // Draw the trail as circles
        for (int i = 0; i < TRAIL_LENGTH; i++) {
            int index = (trailIndex + i) % TRAIL_LENGTH;
            DrawCircle((int)trail[index].x, (int)trail[index].y, TRAIL_RADIUS, RED);
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}

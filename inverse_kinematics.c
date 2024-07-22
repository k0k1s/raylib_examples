#include "raylib.h"
#include <math.h>

#define LINK1_LENGTH 150.0f // Length of the first link
#define LINK2_LENGTH 150.0f // Length of the second link
#define MAX_TRAIL_LENGTH 100 // Maximum number of points in the trail

typedef struct {
    Vector2 positions[MAX_TRAIL_LENGTH];
    int size;
} Trail;

void AddPointToTrail(Trail *trail, Vector2 point) {
    // Add new point to the trail
    if (trail->size < MAX_TRAIL_LENGTH) {
        trail->positions[trail->size++] = point;
    } else {
        // Shift the points to make room for the new point
        for (int i = 0; i < MAX_TRAIL_LENGTH - 1; i++) {
            trail->positions[i] = trail->positions[i + 1];
        }
        trail->positions[MAX_TRAIL_LENGTH - 1] = point;
    }
}

// Function to calculate the angles for inverse kinematics
void CalculateIK(Vector2 target, Vector2 origin, float* angle1, float* angle2) {
    // Calculate the distance from origin to the target
    float dx = target.x - origin.x;
    float dy = target.y - origin.y;
    float distance = sqrtf(dx * dx + dy * dy);

    // Check if the target is within reach
    if (distance > (LINK1_LENGTH + LINK2_LENGTH)) {
        distance = LINK1_LENGTH + LINK2_LENGTH;
    }

    // Calculate the angle of the second joint
    float angle2_temp = acosf((distance * distance - LINK1_LENGTH * LINK1_LENGTH - LINK2_LENGTH * LINK2_LENGTH) / 
                              (2 * LINK1_LENGTH * LINK2_LENGTH));
    *angle2 = angle2_temp - PI;

    // Calculate the angle of the first joint
    float k1 = LINK1_LENGTH + LINK2_LENGTH * cosf(*angle2);
    float k2 = LINK2_LENGTH * sinf(*angle2);
    *angle1 = atan2f(dy, dx) - atan2f(k2, k1);
}

int main(void)
{
    // Initialization
    const int screenWidth = 1000;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib - IK with Trail");

    SetTargetFPS(60);

    Vector2 origin = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 target = origin;

    float angle1 = 0.0f; // Angle of the first joint
    float angle2 = 0.0f; // Angle of the second joint

    Trail trail = {0}; // Initialize the trail

    while (!WindowShouldClose()) {
        // Update
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            target = GetMousePosition();
            AddPointToTrail(&trail, target);
        }

        // Calculate inverse kinematics
        CalculateIK(target, origin, &angle1, &angle2);

        // Calculate the position of the joints and end effector
        Vector2 joint1 = {
            origin.x + LINK1_LENGTH * cosf(angle1),
            origin.y + LINK1_LENGTH * sinf(angle1)
        };
        Vector2 endEffector = {
            joint1.x + LINK2_LENGTH * cosf(angle1 + angle2),
            joint1.y + LINK2_LENGTH * sinf(angle1 + angle2)
        };

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the trail of the end effector
        for (int i = 0; i < trail.size - 1; i++) {
            DrawLine((int)trail.positions[i].x, (int)trail.positions[i].y, 
                     (int)trail.positions[i + 1].x, (int)trail.positions[i + 1].y, BLACK);
        }

        // Draw the base point (origin)
        DrawCircle((int)origin.x, (int)origin.y, 10, BLUE);

        // Draw the first link
        DrawLine((int)origin.x, (int)origin.y, (int)joint1.x, (int)joint1.y, BLACK);

        // Draw the second link
        DrawLine((int)joint1.x, (int)joint1.y, (int)endEffector.x, (int)endEffector.y, BLACK);

        // Draw the target
        DrawCircle((int)target.x, (int)target.y, 10, RED);

        // Draw the end effector
        DrawCircle((int)endEffector.x, (int)endEffector.y, 10, GREEN);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
    
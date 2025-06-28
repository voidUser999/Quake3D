#include "raylib.h"
#include "raymath.h"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Raylib Quake-Style FPS Starter");
    DisableCursor();  // Lock and hide cursor

    Camera3D camera = { 0 };

    Vector3 camPos = { 0.0f, 2.0f, 6.0f };  //player head 
    Vector3 camTarget = { 0.0f, 2.0f, 5.0f }; //where player looking at 
    Vector3 camUp = { 0.0f, 1.0f, 0.0f };  

    camera.position = camPos;
    camera.target = camTarget;
    camera.up = camUp;
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Movement
        Vector3 forward = Vector3Subtract(camera.target, camera.position);
        forward.y = 0.0f;
        forward = Vector3Normalize(forward);
        Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));

        if (IsKeyDown(KEY_W)) camera.position = Vector3Add(camera.position, Vector3Scale(forward, 0.1f));
        if (IsKeyDown(KEY_S)) camera.position = Vector3Subtract(camera.position, Vector3Scale(forward, 0.1f));
        if (IsKeyDown(KEY_A)) camera.position = Vector3Subtract(camera.position, Vector3Scale(right, 0.1f));
        if (IsKeyDown(KEY_D)) camera.position = Vector3Add(camera.position, Vector3Scale(right, 0.1f));

        // Mouse look
        Vector2 mouseDelta = GetMouseDelta();
        float sensitivity = 0.003f;
        float yaw = -mouseDelta.x * sensitivity;
        float pitch = -mouseDelta.y * sensitivity;

        Matrix rotationYaw = MatrixRotateY(yaw);
        Vector3 direction = Vector3Subtract(camera.target, camera.position);
        direction = Vector3Transform(direction, rotationYaw);

        Vector3 rightAxis = Vector3Normalize(Vector3CrossProduct(direction, camera.up));
        Matrix rotationPitch = MatrixRotate(rightAxis, pitch);
        direction = Vector3Transform(direction, rotationPitch);

        camera.target = Vector3Add(camera.position, direction);

        // Drawing
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(camera);

        Vector3 groundPos = { 0.0f, 0.0f, 0.0f };
        Vector2 groundSize = { 100.0f, 100.0f };
        DrawPlane(groundPos, groundSize, DARKGRAY);  // Ground

        Vector3 cube1 = { 0.0f, 1.0f, 0.0f };
        Vector3 cube2 = { -4.0f, 1.0f, 4.0f };
        Vector3 cube3 = { 4.0f, 1.0f, -4.0f };
        DrawCube(cube1, 2.0f, 2.0f, 2.0f, RED);     // Center cube
        DrawCube(cube2, 2.0f, 2.0f, 2.0f, GREEN);   // Another cube
        DrawCube(cube3, 2.0f, 2.0f, 2.0f, BLUE);    // Another cube

        EndMode3D();

        DrawText("WASD to move, Mouse to look", 10, 10, 20, BLACK);
        DrawText("ESC to exit", 10, 35, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

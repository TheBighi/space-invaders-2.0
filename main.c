#include "raylib.h"
#include <stdio.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;


    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 + 180 };
    Vector2 middlePos =  { (float)screenWidth/2, (float)screenHeight/2 };

    Vector2 bullets[100] = {};

    int indice = 0;

    void insertIntoBullets(Vector2 ballPos){
        Vector2 pos = { ballPos.x, (float)screenHeight/2 };
        bullets[indice] = pos;
        indice++;
    }

    Vector2 emptyVector = {0,0}

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------\

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key if u want to exit please 
    {
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 5.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 5.0f;

        if (IsKeyDown(KEY_SPACE)) insertIntoBullets(ballPosition);

        if (ballPosition.x < 20) {
            ballPosition.x = 20;
        }

        if (ballPosition.x > 780){
            ballPosition.x = 780;
        }

        for (int i = 0; i < 100; i++){
            if (bullets[i] != emptyVector){
                DrawCircleV(bullets[i], 5, GRAY);
            }
        }


        BeginDrawing();

            //updateBullets();

            ClearBackground(BLACK);

            DrawText("Use right arrow and lkeft arrow to move.", 190, 200, 20, WHITE);

            DrawCircleV(ballPosition, 20, GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
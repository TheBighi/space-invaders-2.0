#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BULLETS_TOTAL 255
#define ENEMIES_TOTAL 10000
#define BULLET_RADIUS 5
#define ENEMY_RADIUS 15

#define ENTROPY 100000

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

const int screenWidth = 800;
const int screenHeight = 450;

Vector2 emptyVector = {0,0};

int timer = 0;

Vector2 bullets[BULLETS_TOTAL] = { 0 };

Vector2 enemies[ENEMIES_TOTAL] = { 0 };

void insertIntoBullets(Vector2 ballPos){
        for (int i = 0; i < BULLETS_TOTAL; i++) {
            if (bullets[i].x == emptyVector.x && bullets[i].y == emptyVector.y) {
                Vector2 pos = { ballPos.x, ballPos.y };
                bullets[i] = pos;
                return;
            }
        }
}

void insertEnemy(){
    for (int i = 0; i < ENEMIES_TOTAL; i++) {
        if (enemies[i].x == emptyVector.x && enemies[i].y == emptyVector.y) {
            int randomX = rand() % 800;
            int randomY = rand() % 200 + 100;
            enemies[i] = (Vector2){ .x = randomX, .y = randomY};
            return;
        }
    }
}

int main(void){

    srand(ENTROPY);

    // Initialization
    //-------------------------------------------------------------------------------------


    InitWindow(screenWidth, screenHeight, "SPACE INVADERS");

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 + 180 };
    Vector2 middlePos =  { (float)screenWidth/2, (float)screenHeight/2 };


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------\


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key if u want to exit please 
    {   

        timer++;

        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 5.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 5.0f;

        if (IsKeyPressed(KEY_SPACE)) insertIntoBullets(ballPosition);

        if (timer == 100) {
            insertEnemy();
            timer = 0;
        }

        if (ballPosition.x < 20.f) {
            ballPosition.x = 20;
        }

        if (ballPosition.x > 780.f) {
            ballPosition.x = 780;
        }

        for (int i = 0; i < BULLETS_TOTAL; i++) {
            bullets[i].y -= 5.0f; 
        }

        for (int i = BULLETS_TOTAL - 1; i >= 0; i--) {
            if (bullets[i].y <= 0){
                bullets[i] = emptyVector;
            }
        }


        for (int i = 0; i < BULLETS_TOTAL; i++) {
            for (int j = 0; j < ENEMIES_TOTAL; j++) {
                float E_BDistX = enemies[j].x - bullets[i].x;
                float E_BDisty = enemies[j].y - bullets[i].y;
                float distTotal = sqrtf(E_BDisty * E_BDisty + E_BDistX * E_BDistX);
                if (distTotal < ENEMY_RADIUS + BULLET_RADIUS) {
                    bullets[i] = emptyVector;
                    enemies[j] = emptyVector;
                }
            }
        }

        for (int i = 0; i < ENEMIES_TOTAL; i++) {
            if (enemies[i].x != emptyVector.x && enemies[i].y != emptyVector.y) { // SLOPPPPPPP. EI KANNATA NEEGREID KES SIHUKEST PASKA TEEVAD!!!!
                float dx, dy, m;
                
                const float c = 2.0f; // ENEMY KIIRUS SA FUCKING JEEGER!!!!!

                dx = ballPosition.x - enemies[i].x;
                dy = ballPosition.y - enemies[i].y;
                m = sqrtf(dx * dx + dy * dy);

                if (m > 0) {
                    dx = (dx / m) * c;
                    dy = (dy / m) * c;

                    enemies[i].x += dx;
                    enemies[i].y += dy;
                }
            }
        }

        BeginDrawing();

            ClearBackground(BLACK);

            DrawText("Use right arrow and left arrow to move.", 200, 10, 20, WHITE);

            DrawCircleV(ballPosition, 20, GREEN);


            for (int i = 0; i < BULLETS_TOTAL; i++) {
                if (bullets[i].x != emptyVector.x && bullets[i].y != emptyVector.y) {
                    DrawCircleV(bullets[i], BULLET_RADIUS, GRAY);
                }
            }

            for (int i = 0; i < ENEMIES_TOTAL; i++) {
                if (enemies[i].x != emptyVector.x && enemies[i].y != emptyVector.y) {
                    DrawCircleV(enemies[i], ENEMY_RADIUS, RED);
                }
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
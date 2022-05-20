/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/
#include "raylib.h"
#include "screens.h"
#include "cstdio"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

Vector2 TransitionCoordinate(double sita, double rho){
    return (Vector2){rho*cos(sita),rho*sin(sita)};
}

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    world = new World();
    framesCounter = 0;
    finishScreen = 0;
    world->tiger.initTiger(0);
    world->rope.initRope();
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
    if (world->points < 0){
        // Game over
        finishScreen = 1;
    }
    else if (world->currentStage == MAX_STAGE){
        // Passed
        finishScreen = 1;
    }
    else{
        world->updateWorld();
    }
    return;
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(const World* world, Shader shader)
{
    // TODO: Draw GAMEPLAY screen here!
    ClearBackground(RAYWHITE);

        BeginShaderMode(shader);

            DrawTexture(world->texture[0], world->texture[0].width, 0, WHITE);
            DrawTexture(world->texture[0], 0, 0, WHITE);
            DrawTexture(world->texture[0], 0, world->texture[0].height, WHITE);
            DrawTexture(world->texture[0], world->texture[0].width, world->texture[0].height, WHITE);
            DrawTexture(world->texture[0], 0, 2*world->texture[0].height, WHITE);
            DrawTexture(world->texture[0], world->texture[0].width, 2*world->texture[0].height, WHITE);

        EndShaderMode();
        // printf("*************,%d",world->Earth_sita);
            DrawTexturePro(world->texture[1], world->sourceRec, world->destRec, world->origin, (float)world->Earth_sita, WHITE);




            Rectangle frameRec = {0.0f,0.0f,(float)world->texture[2].width/6, (float)world->texture[2].height};
            frameRec.x = (float)(world->tiger.position)*(float)world->texture[2].width/6;
            Vector2 tiger_origin = TransitionCoordinate(world->tiger.sita,world->tiger.r+EARTH_RADIUS);
            Rectangle destRec = { EARTH_POSX, EARTH_POSY, (float)world->texture[2].width/6, (float)world->texture[2].height };
            DrawTexturePro(world->texture[2], frameRec, destRec, (Vector2){(float)world->texture[2].width/12,world->tiger.r+EARTH_RADIUS}, 0,WHITE);
            // world->tiger->sita;
            // world->tiger->r;(float)world->texture[2].width/3,(float)world->texture[2].height*2
            // world->tiger->pos;






    // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    // DrawTextEx(font, "GAMEPLAY SCREEN / YYYY", (Vector2){ 20, 10 }, font.baseSize*3.0f, 4, MAROON);
    // DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

}

void DrawStartScreen(const World* world)
{
    DrawRectangle(0,0, GetScreenHeight(),GetScreenHeight(),PURPLE);
}

void DrawFinishScreen(const World* world)
{
    DrawRectangle(0,0, GetScreenHeight(),GetScreenHeight(),PURPLE);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    delete world;
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}
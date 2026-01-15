#include "GameEngine.h"


void GameEngine::Init()
{

    InitWindow(screenWidth, screenHeight, "GameEngine");

    SetTargetFPS(60);

    Log::print("Ventana inicialziada");
}

void GameEngine::Update()
{
    //Actualizacion de las variables, etc.
}

void GameEngine::Draw()
{
    
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Testeo", 190, 200, 20, LIGHTGRAY);

    EndDrawing();


}

void GameEngine::Run()
{
    while (!WindowShouldClose())    
    {
        Update();
        Draw();
    }

}

void GameEngine::ShutDown()
{
    CloseWindow();
}

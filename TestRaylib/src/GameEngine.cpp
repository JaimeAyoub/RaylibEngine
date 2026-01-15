#include "GameEngine.h"


GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::Init()
{

    InitWindow(screenWidth, screenHeight, "GameEngine");

    SetTargetFPS(60);
    Ball bolita;
    Log::print("Ventana inicialziada");
}

void GameEngine::Update()
{
    
    if (IsMouseButtonPressed(0))
    {
        bolitas.emplace_back();
    }

    if (!bolitas.empty())
    {
        for (Ball& b : bolitas)
        {
            b.UpdateBall();
        }
    }
}

void GameEngine::Draw()
{
    
    BeginDrawing();

    ClearBackground(RAYWHITE);
   
    DrawText("Testeo", 190, 50, 20, LIGHTGRAY);


    if (!bolitas.empty())
    {
        for (Ball& b : bolitas)
        {
            b.DrawBall();
        }
    }

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

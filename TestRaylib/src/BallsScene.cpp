#include "BallsScene.h"

void BallsScene::Load()
{
    button = { 350,50,100,50 };
    buttonPressed = false;
    Name = "BallScene";
}

void BallsScene::UnLoad()
{
    for (Ball* b : bolitas)
    {
        delete b;
    }
    bolitas.clear();
}

void BallsScene::Update()
{
    if (IsMouseButtonPressed(0))
    {
        bolitas.emplace_back(new Ball());
    }

    if (!bolitas.empty())
    {
        for (Ball* b : bolitas)
        {
            b->UpdateBall();
        }
    }
    PressButton();
}

void BallsScene::Draw()
{
    DrawRectangleRec(button, buttonPressed ? RED : DARKGRAY);

	DrawText("Click en alguna parte de la pantalla para aparecer bolitas."
		, (GetScreenWidth() / 2) - 200, 15, 15, BLACK);

    DrawText("Volver a MainMenu", button.x + 2.5f, button.y + 20, 10, WHITE);

    if (!bolitas.empty())
    {
        for (Ball* b : bolitas)
        {
            b->DrawBall();
        }
    }

}

void BallsScene::PressButton()
{
    if ((CheckCollisionPointRec(GetMousePosition(), button)) && IsMouseButtonPressed(0))
    {
        buttonPressed = true;
    }
    
}

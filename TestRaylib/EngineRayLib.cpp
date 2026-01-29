
#include "GameEngine.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


int main(void)
{
    GameEngine engine;
    engine.Init();
    engine.Run();
    engine.ShutDown();
    return 0;
}

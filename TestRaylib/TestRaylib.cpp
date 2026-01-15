// TestRaylib.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "GameEngine.h"

GameEngine engine;

int main(void)
{
    engine.Init();
    engine.Run();
    engine.ShutDown();
    return 0;
}

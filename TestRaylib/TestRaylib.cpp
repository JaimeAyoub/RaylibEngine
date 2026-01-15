// TestRaylib.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "GameEngine.h"


int main(void)
{
GameEngine engine;
    engine.Init();
    engine.Run();
    engine.ShutDown();
    return 0;
}

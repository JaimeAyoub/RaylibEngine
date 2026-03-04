#include "BallsScene.h"
#include <fstream>
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

BallsScene::BallsScene()
{
    eventManager.Suscribe(this, &BallsScene::EventLoadMsg);
   
    
 /*   std::ifstream f("assets/json/PruebaJSON.json");

    if (f.is_open()) {
        printf("Archivo Abierto \n");
        json data = json::parse(f);
        std::string type = data["type"];
        printf("Tipo de objeto : %s \n", type.c_str());
    }
    else
        printf("Valio verga, NO SE CARGO \n");*/

}

void BallsScene::Load()
{
    jointDef = b2DefaultDistanceJointDef();
    jointDef2 = b2DefaultDistanceJointDef();

    pivot = physicsSystem.makeCircle("Bolita2", "Ball", { 50, 100 }, 50, false);
    pivot2 = physicsSystem.makeCircle("Bolita2", "Ball", { 500, 100 }, 50, false);
    cir = physicsSystem.makeCircle("Bolita", "Ball", { 450, 200 }, 30, true);

    jointDef2.bodyIdA = pivot2->body;
    jointDef2.bodyIdB = cir->body;


    jointDef.bodyIdA = pivot->body;
    jointDef.bodyIdB = cir->body;
    

    // Ambos anclajes en el centro de sus respectivas bolas
    jointDef.localAnchorA = { 0, 0 };
    jointDef.localAnchorB = { 0, 0 };

    jointDef2.localAnchorA = { 0, 0 };
    jointDef2.localAnchorB = { 0, 0 };
    //-----------------------------------------

    jointDef.length = 200.0f;

    jointDef.enableSpring = true;
    jointDef.hertz = 2.0f;
    jointDef.dampingRatio = 0.5f;

    jointDef2.length = 200.0f;

    jointDef2.enableSpring = true;
    jointDef2.hertz = 2.0f;
    jointDef2.dampingRatio = 0.5f;

     myJointId = b2CreateDistanceJoint(physicsSystem.ReturnWorld(), &jointDef);
     myJointId2 = b2CreateDistanceJoint(physicsSystem.ReturnWorld(), &jointDef2);


    boxDef.pos = { 400,600 };
    boxDef.isDynamic = false;
    boxDef.name = "Suelo";
    boxDef.size = { 800,40 };


    button = { 350,50,100,50 };
    buttonPressed = false;
    Name = "BallScene";
    LoadBallsEvent event;
    eventManager.emit(event);
    texPrueba = LoadTexture("assets/textures/Kirbo.png");
    //texture = resourceManager.getTexture("Kirbo.png");
    music = resourceManager.getMusic("Spark-Man.ogg");
    PlayMusicStream(*music);
    addEntity(pivot);
    addEntity(pivot2);
    addEntity(cir);

    

    

    addEntity(physicsSystem.makeBox(boxDef));



    eventManager.Suscribe<CollisionEvent>(this, &BallsScene::onCollision);
    for (int i = 0; i < 4; i++)
    {
        BodyData current = boxDef;

        current.pos.y = boxDef.pos.y - i * boxDef.size.y;
        addEntity(physicsSystem.makeBox(current));
    }
    
}

void BallsScene::UnLoad()
{
    for (Ball* b : bolitas)
    {
        delete b;
    }
    bolitas.clear();
    StopMusicStream(*music);
}

void BallsScene::Update()
{
    
    UpdateMusicStream(*music);
 
       
        if (IsMouseButtonPressed(0))
        {
            if (!isDrawingLine)
            {
                lineStartPos = GetMousePosition();
                isDrawingLine = true;
            }

        }
        if (IsMouseButtonReleased(0))
        {
            isDrawingLine = false;
        }

        b2Vec2 pivot2Pos = b2Body_GetWorldPoint(pivot2->body, jointDef2.localAnchorA);
        b2Vec2 circle2 = b2Body_GetWorldPoint(cir->body, jointDef.localAnchorB);
        Vector2 collision;
        if (isDrawingLine)
        {
            if (CheckCollisionLines({ pivot2Pos.x,pivot2Pos.y }, { circle2.x,circle2.y },
                lineStartPos, GetMousePosition(), &collision))
            {
         
                    if (b2Joint_IsValid(myJointId2) == true)
                    {
                        b2DestroyJoint(myJointId2);
                        myJointId2 = b2_nullJointId;
                    }

            }
     }

       

   

        //Para eliminar los puntos.

   /*     if (b2Joint_IsValid(myJointId) == false)
        {
            b2DestroyJoint(myJointId2);
            myJointId2 = b2_nullJointId;
        }
        if (b2Joint_IsValid(myJointId) == true)
        {
            b2DestroyJoint(myJointId);
            myJointId = b2_nullJointId;
        }*/

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

    b2Vec2 pivotPos = b2Body_GetWorldPoint(pivot->body, jointDef.localAnchorA);
    b2Vec2 pivot2Pos = b2Body_GetWorldPoint(pivot2->body, jointDef2.localAnchorA);
    b2Vec2 circle2 = b2Body_GetWorldPoint(cir->body, jointDef.localAnchorB);

    if (b2Joint_IsValid(myJointId) == true )
    {

         DrawLineV({ pivotPos.x,pivotPos.y }, { circle2.x, circle2.y }, RED);
       
    }
    if (b2Joint_IsValid(myJointId2) == true)
    {
        DrawLineV({ pivot2Pos.x,pivot2Pos.y }, { circle2.x, circle2.y }, RED);
    }
    
    //DrawTexture(*texture, 250, 250, WHITE);
    if (!bolitas.empty())
    {
        for (Ball* b : bolitas)
        {
            b->DrawBall();
        }
    }
    LoadBallsEvent event;

    if (GuiButton(rectangle, "#191#Boton testeo")) {
        eventManager.emit(event);
    }
    if (showMsg)
    {
        int result = GuiMessageBox({ rectangle2 },
            "#191#Ventana", "Elige que ventana quieres abrir!", "Cerrar");

        if (result >= 1) showMsg = false;
    }
    if (isDrawingLine)
    {
        
        DrawLineV(lineStartPos, GetMousePosition(), BLACK);

    }
    

}

void BallsScene::PressButton()
{
    if ((CheckCollisionPointRec(GetMousePosition(), button)) && IsMouseButtonPressed(0))
    {
        buttonPressed = true;
    }
    
}

void BallsScene::EventLoadMsg(const LoadBallsEvent& m)
{
    Log::print(m.msg);
}

void BallsScene::onCollision(const CollisionEvent& event)
{
    Log::print("¡Colisión detectada entre " + event.A->getName());
}


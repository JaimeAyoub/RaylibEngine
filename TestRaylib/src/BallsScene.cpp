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


	pivot = physicsSystem.makeCircle("Bolita2", "Ball", { 50, 100 }, 50, false);
	pivot2 = physicsSystem.makeCircle("Bolita2", "Ball", { 500, 100 }, 50, false);
	cir = physicsSystem.makeCircle("Bolita", "Ball", { 450, 200 }, 30, true);

	auto joint = physicsSystem.makeJoint(pivot, cir);
	auto joint2 = physicsSystem.makeJoint(pivot2, cir);


	jointsVector.push_back(joint);
	jointsVector.push_back(joint2);






	boxDef.pos = { 600,450 };
	boxDef.isDynamic = false;
	boxDef.name = "Goal";
	boxDef.size = { 80,10 };


	button = { 350,350,100,50 };
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
	for (auto& joint : jointsVector)
	{
		if (b2Joint_IsValid(joint->jointId) == true)
		{
			physicsSystem.DeleteJoint(joint->jointId);
		}
	}
	jointsVector.clear();
	StopMusicStream(*music);
	isDrawingLine = false;
	isWin = false;
	isDefeat = false;
	Clear();
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


	if (isDrawingLine && !jointsVector.empty())
	{
		Vector2 collision;
		for (auto& joint : jointsVector)
		{
			if (CheckCollisionLines(joint->pivot->pos,cir->pos,
				lineStartPos, GetMousePosition(), &collision))
			{
				if (b2Joint_IsValid(joint->jointId) == true) 
				{
					physicsSystem.DeleteJoint(joint->jointId);
				}

			}
		}
		
	}

	if (cir->pos.y > 700 && isDefeat == false)
	{
		Log::print("Se cayo la bola");
		isDefeat = true;
	}







	PressButton();

}

void BallsScene::Draw()
{
	if (isWin == true)
	{
		DrawRectangleRec(button, buttonPressed ? RED : DARKGRAY);

		DrawText("WIN"
			, (GetScreenWidth() / 2) - 200, 15, 50, BLACK);

		DrawText("Volver a MainMenu", button.x + 2.5f, button.y + 20, 10, WHITE);
	}

	if (isDefeat == true)
	{
		DrawRectangleRec(button, buttonPressed ? RED : DARKGRAY);

		DrawText("Perdiste, tonto"
			, (GetScreenWidth() / 2) - 200, 15, 50, BLACK);

		DrawText("Volver a MainMenu", button.x + 2.5f, button.y + 20, 10, WHITE);
	}
	

	if (!jointsVector.empty())
	{
		for (auto& joint : jointsVector)
		{
			if (b2Joint_IsValid(joint->jointId) == true) {
				DrawLineV(joint->pivot->pos, cir->pos,BLACK);
			}
		}
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
	if (event.A->getName() == "Goal")
	{
		isWin = true;
	}
	else
	{
		Log::print("¡Colisión detectada entre " + event.A->getName());
	}
}




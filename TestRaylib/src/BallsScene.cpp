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

	cir = physicsSystem.makeCircle("Bolita", "Ball", { 450, 200 }, 30, true);



	boxDef.pos = { 600,450 };
	boxDef.isDynamic = false;
	boxDef.name = "Goal";
	boxDef.size = { 80,10 };

	pivotDef.name = "Pivote";
	pivotDef.isDynamic = false;
	pivotDef.pos = { 50,100 };
	pivotDef.radius = 50;

	pivotDef2.name = "Pivote2";
	pivotDef2.isDynamic = false;
	pivotDef2.pos = { 500,100 };
	pivotDef2.radius = 50;





	button = { 350,350,100,50 };
	buttonPressed = false;
	Name = "BallScene";
	LoadBallsEvent event;
	eventManager.emit(event);
	texPrueba = LoadTexture("assets/textures/Kirbo.png");

	auto joint1 = std::make_shared<Joint>(physicsSystem.makeJoint(pivotDef, cir));
	auto joint2 = std::make_shared<Joint>(physicsSystem.makeJoint(pivotDef2, cir));

	jointsVector.push_back(joint1);
	jointsVector.push_back(joint2);


	addEntity(joint1);
	addEntity(joint2);
	addEntity(cir);
	addEntity(joint1->jointData->pivot);
	addEntity(joint2->jointData->pivot);




	//texture = resourceManager.getTexture("Kirbo.png");
	//music = resourceManager.getMusic("Spark-Man.ogg");
	//PlayMusicStream(*music);


	BindRayLib();

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

	if (music != nullptr)
	{
		StopMusicStream(*music);

	}
	UnloadTexture(texPrueba);

	isDrawingLine = false;
	isWin = false;
	isDefeat = false;
	Clear();
	eventManager.Unsubscribe<LoadBallsEvent>(this);
	eventManager.Unsubscribe<CollisionEvent>(this);
}

void BallsScene::Update()
{

	if (luaUpdate)
	{
		luaUpdate();
	}
	if (music != nullptr)
	{
		UpdateMusicStream(*music);
	}


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
		for (auto& joint : jointsVector)
		{
			joint->checkCut(lineStartPos, GetMousePosition());
		}
	}

	if (cir->pos.y > 700 && isDefeat == false && isWin == false)
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
	if (luaDraw)
	{
		luaDraw();
	}

	if (isDefeat == true)
	{
		DrawRectangleRec(button, buttonPressed ? RED : DARKGRAY);

		DrawText("Perdiste, tonto"
			, (GetScreenWidth() / 2) - 200, 15, 50, BLACK);

		DrawText("Volver a MainMenu", button.x + 2.5f, button.y + 20, 10, WHITE);
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

void BallsScene::BindRayLib()
{
	lua.open_libraries(sol::lib::base, sol::lib::table, sol::lib::math);
	sol::table rl = lua.create_named_table("rl");

	rl.set_function("draw_circle", [](float x, float y, float r,
		sol::optional<Color> c) {
			Color color = c.value_or(MAROON);
			Vector2 center = { x,y };
			DrawCircleV(center, r, color);
		});
	rl.set_function("mouse_pressed", &IsMouseButtonPressed);
	rl.set_function("mouse_x", &GetMouseX);
	rl.set_function("mouse_y", &GetMouseY);
	//rl.set_function("to_world"), [&](float sx, float sy) {
	//	Vector2 world = GetScreenToWorld2D({ sx,sy }, cam);
	//	return std::make_tuple(world.x, world.y);
	//	});
	rl.set_function("print", [](std::string message) {
		std::cout << "[LUA]: " << message << std::endl;
		});
	rl["maroon"] = MAROON;
	auto result = lua.script_file("assets/scripts/play_scene.lua");
	if (result.valid()) {
		luaUpdate = lua["update"];
		luaDraw = lua["draw"];
		std::cout << "Script cargado y funciones vinculadas." << std::endl;
	}
	else
	{
		sol::error err = result;
		std::cerr << "LUA ERROR: " << err.what() << std::endl;
	}
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






#include "BallsScene.h"
#include <fstream>
#include "include/nlohmann/json.hpp"

using json = nlohmann::json;

BallsScene::BallsScene()
{
	eventManager.Suscribe(this, &BallsScene::EventLoadMsg);

	std::ifstream f("assets/json/currentLevel.json");
	if (f.is_open()) {
		json data = json::parse(f);
		currentLevel = data.value("currentLevel", 1); // si no existe, empieza en 1
		printf("Nivel cargado: %d\n", currentLevel);
	}
	else {
		currentLevel = 1; // primera vez que se abre el juego
		printf("No hay save, empezando desde nivel 1\n");
	}


}

void BallsScene::Load()
{

	isWin = false;

	std::string path = "assets/json/Level" + std::to_string(currentLevel) + ".json";
	NextLevel(path);
	button = { 350,350,100,50 };
	buttonPressed = false;
	Name = "BallScene";
	LoadBallsEvent event;
	eventManager.emit(event);
	texPrueba = LoadTexture("assets/textures/Kirbo.png");

	BindRayLib();

	eventManager.Suscribe<CollisionEvent>(this, &BallsScene::onCollision);


}

void BallsScene::UnLoad()
{
//Descargamos assets
	if (music != nullptr)
	{
		StopMusicStream(*music);
		music = nullptr;

	}
	UnloadTexture(texPrueba);
//---------------------------
//Descargamos vector y objetos
	jointsVector.clear();
	Clear();
	cir = nullptr;
//------------------------------
	luaUpdate = sol::function{};
	luaDraw = sol::function{};
//------------------------------------
	isDrawingLine = false;
	isDefeat = false;
	isWin = false;
	buttonPressed = false;

	eventManager.Unsubscribe<LoadBallsEvent>(this);
	eventManager.Unsubscribe<CollisionEvent>(this);

	json j;
	j["currentLevel"] = currentLevel;

	std::ofstream file("assets/json/currentLevel.json");
	file << std::setw(4) << j << std::endl;
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
	if (cir != nullptr && cir->pos.y > 700 && isDefeat == false && isWin == false)
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

		DrawText("Next level", button.x + 2.5f, button.y + 20, 10, WHITE);
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

		DrawText("Reset", button.x + 2.5f, button.y + 20, 10, WHITE);
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

		if (isWin)
			FinishLevel();
		else if (isDefeat)
			RestartLevel();
	}

}

void BallsScene::EventLoadMsg(const LoadBallsEvent& m)
{
	Log::print(m.msg);
}

void BallsScene::FinishLevel()
{
	if (isLoadingNextLevel) return;
	isLoadingNextLevel = true;
	if (currentLevel < 3) //Cap para que no siga incrementando niveles que no existen.
	{
		currentLevel++;

	}
	else if (currentLevel >= 3)
	{
		currentLevel = 1;
	}
	UnLoad();
	Load();

	isLoadingNextLevel = false;
}

void BallsScene::NextLevel(std::string path) //Funcion para que se cargue el siguiente nivel
{
	std::ifstream f(path);
	if (f.is_open()) {
		printf("Archivo Abierto \n");
		json data = json::parse(f);
		printf("Cargando Nivel: %d\n", currentLevel);
		if (data.contains("bola")) {   // Cargamos la bola
			auto& b = data["bola"];
			float x = data["bola"].value("posX", 0.0f);
			float y = data["bola"].value("posY", 0.0f);
			float radius = data["bola"].value("radius", 0.0f);

			cir = physicsSystem.makeCircle("Bolita", "Ball", { x, y }, radius, true);
			addEntity(cir);
		}
		if (data.contains("winBox"))
		{
			auto& w = data["winBox"];  //Cargamos la caja que tiene que colisionar para ganar
			boxDef.name = w.value("name", "Goal");
			boxDef.isDynamic = w.value("isDynamic", false);
			boxDef.pos = { w.value("posX",0.0f),
				w.value("posY",0.0f) };
			boxDef.size = { w.value("width",0.0f),
				w.value("height",0.0f) };
			for (int i = 0; i < 4; i++) 
			{
				BodyData current = boxDef;
				current.pos.y = boxDef.pos.y - i * boxDef.size.y;
				addEntity(physicsSystem.makeBox(current));
			}
		}
		if (data.contains("pivotes") && data["pivotes"].is_array()) {  // Cargamos todos los pivotes

			for (const auto& item : data["pivotes"]) {
				pivotDef.name = item.value("type", "Pivote");
				pivotDef.isDynamic = item.value("isDynamic", false);
				pivotDef.pos = { item.value("posX",0.0f),item.value("posY",0.0f) };
				pivotDef.radius = item.value("radius", 0.0f);

				auto joint = std::make_shared<Joint>(physicsSystem.makeJoint(pivotDef, cir));

				jointsVector.push_back(joint);
				addEntity(joint);
				addEntity(joint->jointData->pivot);
			}

		}


	}
	else {

		printf("Valio mangos, NO SE CARGO \n");
	}
}

void BallsScene::RestartLevel()
{
	UnLoad();
	Load();
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






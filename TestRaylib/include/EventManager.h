#pragma once
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <functional>
#include <algorithm>
class EventManager
{
public:
	using Callback = std::function<void(const void*)>; //Esto se ejecuta cuando se emite un evento

	using Listener = std::pair<void*, Callback>; //Objeto + accion asociada.

	//Singleton
	static EventManager& instance() {
		static EventManager instance;
		return instance;
	}
	//--------------

	//Registrar el objeto que escuchara el evento
	template<typename Event, typename Object>
	void Suscribe(Object* object, void(Object::* method)(const Event&)) {
		auto eventType = std::type_index(typeid(Event)); //Tipo del evento
		Callback callback = [object, method](const void* evt) { //Callback = apuntador a funcion miembro
			const Event* event = static_cast<const Event*>(evt); // Convertir evento generico
			(object->*method)(*event);							// Ejecutar metodo del objeto
			};


		listeners[eventType].push_back({ object,callback });
	}

	//Cancelar suscripcion de un objeto

	template <typename Event>
	void Unsubscribe(void* object) {
		auto eventType = std::type_index(typeid(Event));
		auto it = listeners.find(eventType);
		if (it == listeners.end()) return;

		auto& list = it->second;
		list.erase(std::remove_if(list.begin(), list.end(),
			[object](const Listener& l) {return l.first == object; }),
			list.end());
	}

	//Para emitir un evento

	template<typename Event>
	void emit(const Event& event) {
		auto eventType = std::type_index(typeid(Event));
		auto it = listeners.find(eventType);
		if (it == listeners.end()) return;

		for (const Listener& l : it->second)
			l.second(&event);
	}


private:
	std::unordered_map<std::type_index, std::vector<Listener>> listeners;
};







